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

void
scan_debug_log(std::string mes, bool debug){
    if (debug){
	   np2.nlog_custom("SCAN", mes, 1);
	   fflush(stdout);
    }
}

int 
nesca_scan(struct nesca_scan_opts *ncot, const char* ip, int port, int timeout_ms){
    char datagram[SEND_BUFFER_SIZE];
    memset(datagram, 0, SEND_BUFFER_SIZE);

    struct sockaddr_in dest;
    struct pseudo_header psh;
    bool debug = ncot->debug;

    struct iphdr *iph_send = (struct iphdr*)datagram;
    struct tcphdr *tcph_send = (struct tcphdr*)(datagram + sizeof (struct iphdr));

    scan_debug_log("IP is: "+std::string(ip)+"\n", debug);
    scan_debug_log("Source IP is: "+std::string(ncot->source_ip)+"\n", debug);
    scan_debug_log("Port is: "+std::to_string(port)+"\n", debug);
    scan_debug_log("Source Port is: "+std::to_string(ncot->source_port)+"\n", debug);
    scan_debug_log("Seq is: "+std::to_string(ncot->seq)+"\n", debug);

    /*Таймаут, он реально помогает и очень сильно влияет.*/
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms));

    if (debug){
	   np2.nlog_custom("", "===============================SEND===============================\n", 0);
    }
    /*Создание raw сокета, для более глубокой работы
    с сокетом.*/
    scan_debug_log("Creation RAW sock on SEND.\n", debug);
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock < 0){
	   scan_debug_log("FAILED creation RAW sock on SEND.\n", debug);
       return PORT_ERROR;
    }

    /*Сообщаем ядру, что не нужно генерировать IP заголовок
	* потому что мы сами его сделали.*/
    int set_hdrincl = set_socket_hdrincl(sock);
    if (set_hdrincl == -1){
	   close(sock);
	   return PORT_ERROR;
    }

    tcp_flags tpf;
    tpf.rst = 0;
    tpf.ack = 0;
    
    if (ncot->scan_type == SYN_SCAN){
	   tpf.syn = 1;
	   tpf.fin = 0;
	   tpf.psh = 0;
	   tpf.urg = 0;
    }else if (ncot->scan_type == XMAS_SCAN){
	   tpf.syn = 0;
	   tpf.fin = 1;
	   tpf.psh = 1;
	   tpf.urg = 1;
    }else if (ncot->scan_type == FIN_SCAN){
	   tpf.syn = 0;
	   tpf.fin = 1;
	   tpf.psh = 0;
	   tpf.urg = 0;
    }else if (ncot->scan_type == NULL_SCAN){
	   tpf.syn = 0;
	   tpf.fin = 0;
	   tpf.psh = 0;
	   tpf.urg = 0;
    }else if (ncot->scan_type == ACK_SCAN || ncot->scan_type == WINDOW_SCAN){
	   tpf.syn = 0;
	   tpf.fin = 0;
	   tpf.psh = 0;
	   tpf.urg = 0;
       tpf.ack = 1;
	}else if (ncot->scan_type == MAIMON_SCAN){
	   tpf.syn = 0;
	   tpf.fin = 1;
	   tpf.psh = 0;
	   tpf.urg = 0;
       tpf.ack = 1;
	}

    /*Заполнение TCP заголовка.*/
    scan_debug_log("Fill TCP header.\n", debug);

    fill_tcp_header(tcph_send, ncot->source_port, port, ncot->seq, 0, WINDOWS_SIZE, 0,
		  5, 0, tpf);

    /*Заполнение IP заголовка.*/
    scan_debug_log("Fill IP header.\n", debug);

    fill_ip_header(iph_send, ncot->source_ip, ip, sizeof(struct iphdr) + sizeof(struct tcphdr),
		        IPPROTO_TCP, ncot->seq, IP_DF, ncot->ttl, 5, 4, 0);

    scan_debug_log("Calculate sum for IP header.\n", debug);

    int check_sum_ip = checksum_16bit((unsigned short *)datagram, iph_send->tot_len >> 1); 
    iph_send->check = check_sum_ip;

    scan_debug_log("IP cheksum is: "+std::to_string(check_sum_ip)+"\n", debug);
    scan_debug_log("IP length is: "+std::to_string(sizeof(struct iphdr)+ sizeof(struct tcphdr))+"\n", debug);

    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(ip);

    /*Заполнение фейкового TCP заголовка, для расчёта
	* контрольной суммы, тем самым обманывая хост.*/
    scan_debug_log("Fill fake TCP header.\n", debug);
    psh.source_address = iph_send->saddr;
    psh.dest_address = dest.sin_addr.s_addr; 
    psh.placeholder = 0;
    psh.protocol = iph_send->protocol;
    psh.tcp_length = htons(sizeof(struct tcphdr));
    memcpy(&psh.tcp, tcph_send, sizeof(struct tcphdr));

    scan_debug_log("Calculate sum for TCP header.\n", debug);

    /*Заполнение контрольной суммы пакета для
    tcp заголовка*/
    int check_sum_tcp = checksum_16bit((unsigned short*)&psh, sizeof(struct pseudo_header));
    tcph_send->check = check_sum_tcp;
    scan_debug_log("TCP cheksum is: "+std::to_string(tcph_send->check)+"\n", debug);

    /*Отправка TCP пакета.*/
    scan_debug_log("Send TCP packet.\n", debug);
    int send_size = sizeof(struct iphdr)+sizeof(struct tcphdr);
    ssize_t send = sendto(sock, datagram, send_size, 0,
		  (struct sockaddr*)&dest, sizeof(dest));
    if (send == -1){
	   scan_debug_log("FAILED Send TCP packet.\n", debug);
	   close(sock);
	   return PORT_ERROR;
    }

    close(sock);
    return PORT_OPEN;
}

int
get_port_status(unsigned char* buffer, bool no_syn, bool ack_scan, bool window_scan, bool maimon_scan){
    struct iphdr *iph = (struct iphdr*)buffer;
    unsigned short iphdrlen = (iph->ihl) * 4;

    /*Если пакет именно TCP.*/
    if (iph->protocol != 6){return PORT_ERROR;}
    struct tcphdr *tcph = (struct tcphdr*)((char*)buffer + iphdrlen);

    /*Обработка пакета, писалась используя
    эти статьи:
	* https://nmap.org/book/synscan.html
	* https://nmap.org/man/ru/man-port-scanning-techniques.html
	* https://nmap.org/book/scan-methods-window-scan.html
	* https://nmap.org/book/scan-methods-maimon-scan.html*/
	if (maimon_scan){
		if (tcph->th_flags == 0x04){
			return PORT_CLOSED;
		}
		else {
			return PORT_OPEN_OR_FILTER;
		}
	}
	if (window_scan){
		if (tcph->th_flags == 0x04){
			if (tcph->window > 0){
				return PORT_OPEN;
			}
			else {
				return PORT_CLOSED;
			}
		}
		else {
			return PORT_FILTER;
		}
	}
    if (no_syn){
	   switch (tcph->th_flags) {
		  case 0x04:{
			 return PORT_CLOSED;
		  }
		  default:
	   		return PORT_OPEN;
	   }
    }else if (ack_scan){
	   switch (tcph->th_flags) {
		  case 0x04:{
			 return PORT_NO_FILTER;
		  }
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
