/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include <arpa/inet.h>
#include <cstdio>
#include <ctime>
#include <libssh/libssh.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <string>
#include <sys/types.h>
#include <thread>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>

#include "include/portscan.h"
#include "ncsock/include/ncread.h"
#include "ncsock/include/headers.h"
#include "ncsock/include/socket.h"
#include "ncsock/include/other.h"
#include "include/generation.h"

nesca_prints np2;

int 
nesca_scan(struct nesca_scan_opts *ncot, const char* ip, int port, int timeout_ms){
    char datagram[SEND_BUFFER_SIZE];
    memset(datagram, 0, SEND_BUFFER_SIZE);

    struct sockaddr_in dest;
    struct pseudo_header psh;

    struct iphdr *iph_send = (struct iphdr*)datagram;
    struct tcphdr *tcph_send = (struct tcphdr*)(datagram + sizeof (struct iphdr));

	/*Задержка по стандартку 0.*/
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms));

    /*Создание raw сокета, для более глубокой работы
    с сокетом.*/
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock < 0){return PORT_ERROR;}

    /*Сообщаем ядру, что не нужно генерировать IP заголовок
	* потому что мы сами его сделали.*/
    int set_hdrincl = set_socket_hdrincl(sock);
    if (set_hdrincl == EOF){close(sock);return PORT_ERROR;}

    /*Заполнение TCP заголовка.*/
    fill_tcp_header(tcph_send, ncot->source_port, port, ncot->seq, 0, WINDOWS_SIZE, 0,
		  5, 0, ncot->tcpf);

	uint16_t packet_length = sizeof(struct iphdr) + sizeof(struct tcphdr);

    fill_ip_header(iph_send, ncot->source_ip, ip, packet_length,
		        IPPROTO_TCP, generate_ident(), IP_DF, ncot->ttl, 5, 4, 0);

	/*Расчёт контрольной суммы для IP заголовка.*/
    uint16_t check_sum_ip = checksum_16bit((unsigned short *)datagram, iph_send->tot_len >> 1); 
    iph_send->check = check_sum_ip;

    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(ip);

    /*Заполнение фейкового TCP заголовка, для расчёта
	* контрольной суммы, тем самым обманывая хост.*/
    psh.source_address = iph_send->saddr;
    psh.dest_address = dest.sin_addr.s_addr; 
    psh.placeholder = 0;
    psh.protocol = iph_send->protocol;
    psh.tcp_length = htons(sizeof(struct tcphdr));
    memcpy(&psh.tcp, tcph_send, sizeof(struct tcphdr));

    /*Заполнение контрольной суммы пакета для
    tcp заголовка, на основе псевдо.*/
    uint16_t check_sum_tcp = checksum_16bit((unsigned short*)&psh, sizeof(struct pseudo_header));
    tcph_send->check = check_sum_tcp;

    /*Отправка TCP пакета.*/
    ssize_t send = sendto(sock, datagram, packet_length, 0,
		  (struct sockaddr*)&dest, sizeof(dest));
    if (send == EOF){
	   close(sock);
	   return PORT_ERROR;
    }

	if (ncot->packet_trace == true){
		std::string source_ip = ncot->source_ip;
		std::string dest_ip = ip;
		np2.nlog_packet_trace("SENT", "TCP", source_ip, dest_ip, ncot->source_port, port, "", iph_send->ttl, iph_send->id,
				WINDOWS_SIZE, ncot->seq, packet_length);
	}

    close(sock);
    return PORT_OPEN;
}

/*Обработка пакета, писалась используя
* эти статьи:
* https://nmap.org/book/synscan.html
* https://nmap.org/man/ru/man-port-scanning-techniques.html
* https://nmap.org/book/scan-methods-window-scan.html
* https://nmap.org/book/scan-methods-maimon-scan.html
*/

int
get_port_status(unsigned char* buffer, int scan_type){
    struct iphdr *iph = (struct iphdr*)buffer;
    uint16_t iphdrlen = (iph->ihl) * 4;

    /*Если пакет именно TCP.*/
    if (iph->protocol != 6){return PORT_ERROR;}
    struct tcphdr *tcph = (struct tcphdr*)((char*)buffer + iphdrlen);

	if (scan_type == MAIMON_SCAN){
		if (tcph->th_flags == 0x04){return PORT_CLOSED;}
		else {return PORT_OPEN_OR_FILTER;}
	}
	if (scan_type == WINDOW_SCAN){
		if (tcph->th_flags == 0x04){
			if (tcph->window > 0){return PORT_OPEN;}
			else {return PORT_CLOSED;}
		}
		else {return PORT_FILTER;}
	}
    if (scan_type == FIN_SCAN || scan_type == XMAS_SCAN
			|| scan_type == NULL_SCAN){
	   switch (tcph->th_flags) {
		  case 0x04:{return PORT_CLOSED;}
		  default:
	   		return PORT_OPEN;
	   }
    }else if (scan_type == ACK_SCAN){
	   switch (tcph->th_flags) {
		  case 0x04:{return PORT_NO_FILTER;}
		  default:
	   		return PORT_FILTER;
	   }
	}
    else {
	   switch (tcph->th_flags) {
		  case 0x12:{
			 /*SYN + ACK
			 * Если хост ответил флагом ack и послал syn
			 значит порт считаеться открытым.*/
			 return PORT_OPEN;
		  }
		  case 0x1A:{
			 /*SYN + ACK + PSH
			 * Если хост ответил флагом ack и psh затем  послал syn
			 значит порт считаеться открытым, и готовым для
			 передачи данных*/
			 return PORT_OPEN;
		  }
		  case 0x04:{
			 /*RST
			 * Если хост послал только флаг rst
			 aka сброс соеденения, то считаеться что порт
			 закрыт.*/
			 return PORT_CLOSED;
		  }
		  default:{
			 /*Если ответа от хоста вообще не было то считаеться
			 что подлкючение не удалось, порт фильтруеться.*/
			 return PORT_FILTER;
		  }
	   }
    }
}

struct tcp_flags
set_flags(int scan_type){
	tcp_flags tpf;
	tpf.rst = 0;
    tpf.ack = 0;
	switch (scan_type) {
    case SYN_SCAN:
        tpf.syn = 1;
        tpf.fin = 0;
        tpf.psh = 0;
        tpf.urg = 0;
        break;
    case XMAS_SCAN:
        tpf.syn = 0;
        tpf.fin = 1;
        tpf.psh = 1;
        tpf.urg = 1;
        break;
    case FIN_SCAN:
        tpf.syn = 0;
        tpf.fin = 1;
        tpf.psh = 0;
        tpf.urg = 0;
        break;
    case NULL_SCAN:
        tpf.syn = 0;
        tpf.fin = 0;
        tpf.psh = 0;
        tpf.urg = 0;
        break;
    case ACK_SCAN:
    case WINDOW_SCAN:
        tpf.syn = 0;
        tpf.fin = 0;
        tpf.psh = 0;
        tpf.urg = 0;
        tpf.ack = 1;
        break;
    case MAIMON_SCAN:
        tpf.syn = 0;
        tpf.fin = 1;
        tpf.psh = 0;
        tpf.urg = 0;
        tpf.ack = 1;
        break;
	}

	return tpf;
}
