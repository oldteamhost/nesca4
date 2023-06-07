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

#include "../include/synscan.h"
#include "../ncsock/include/headers.h"
#include "../ncsock/include/socket.h"
#include "../ncsock/include/other.h"

nesca_prints nspr;
bool no_syn_scan;
struct in_addr dest_ip;

unsigned int
generate_seq(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(0, 4294967295);
    unsigned int seq_res = dis(gen);
    return seq_res;
}

void
scan_debug_log(std::string mes, bool debug){
    if (debug){
	   nspr.nlog_custom("SCAN", mes, 1);
	   fflush(stdout);
    }
}

int 
nesca_scan(struct nesca_scan_opts *ncot ,const char* ip, int port, int timeout_ms){
    unsigned int seq_res = generate_seq(); 

    char datagram[SEND_BUFFER_SIZE];
    memset(datagram, 0, SEND_BUFFER_SIZE);

    struct sockaddr_in dest;
    struct pseudo_header psh;

    struct iphdr *iph_send = (struct iphdr*)datagram;
    struct tcphdr *tcph_send = (struct tcphdr*)(datagram + sizeof (struct iphdr));

    bool debug = ncot->debug;

    scan_debug_log("IP is: "+std::string(ip)+"\n", debug);
    scan_debug_log("Source IP is: "+std::string(ncot->source_ip)+"\n", debug);
    scan_debug_log("Port is: "+std::to_string(port)+"\n", debug);
    scan_debug_log("Source Port is: "+std::to_string(ncot->source_port)+"\n", debug);
    scan_debug_log("Seq is: "+std::to_string(seq_res)+"\n", debug);

    /*Таймаут, он реально помогает и очень сильно влияет.*/
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms));

    if (debug){
	   nspr.nlog_custom("", "===============================SEND===============================\n", 0);
    }
    /*Создание raw сокета, для более глубокой работы
    с сокетом.*/
    scan_debug_log("Creation RAW sock on SEND.\n", debug);
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock == -1){
	   scan_debug_log("FAILED creation RAW sock on SEND.\n", debug);
        return PORT_ERROR;
    }

    /*Для обработки пакета.*/
    dest_ip.s_addr = inet_addr(ip);

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
	   no_syn_scan = false;
    }
    else if (ncot->scan_type == XMAS_SCAN){
	   tpf.syn = 0;
	   tpf.fin = 1;
	   tpf.psh = 1;
	   tpf.urg = 1;
    }
    else if (ncot->scan_type == FIN_SCAN){
	   tpf.syn = 0;
	   tpf.fin = 1;
	   tpf.psh = 0;
	   tpf.urg = 0;
    }
    else if (ncot->scan_type == NULL_SCAN){
	   tpf.syn = 0;
	   tpf.fin = 0;
	   tpf.psh = 0;
	   tpf.urg = 0;
    }

    /*Заполнение TCP заголовка.*/
    scan_debug_log("Fill TCP header.\n", debug);

    fill_tcp_header(tcph_send, ncot->source_port, port, seq_res, 0, WINDOWS_SIZE, 0,
		  5, 0, tpf);

    /*Заполнение IP заголовка.*/
    scan_debug_log("Fill IP header.\n", debug);

    fill_ip_header(iph_send, ncot->source_ip, ip, sizeof(struct iphdr) + sizeof(struct tcphdr),
		        IPPROTO_TCP, seq_res+2, IP_DF, IP_HEADER_TTL, 5, 4, 0);

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
    // int result = recv_packet(ncot->recv_timeout_ms, debug, no_syn_scan);

    return PORT_OPEN;
}

int
recv_packet(int recv_timeout_ms, bool debug){
    /*Создания нового сокета для обработки ответа.*/
    if (debug){
	   nspr.nlog_custom("", "===============================RECV===============================\n", 0);
    }
    scan_debug_log("Creation RAW sock for recv.\n", debug);
    int sock_recv = socket(AF_INET, SOCK_RAW, IPPROTO_TCP); 
    if (sock_recv == -1){
	   scan_debug_log("FAILED Creation RAW sock for recv.\n", debug);
        return PORT_ERROR;
    }

    /*Буфер с ответом.*/
    unsigned char *buffer = (unsigned char *)calloc(RECV_BUFFER_SIZE, sizeof(unsigned char));
    if (buffer == NULL){
	   scan_debug_log("FAILED Memory allocation.\n", debug);
	   close(sock_recv);
	   return PORT_ERROR;
    }




    struct pollfd poll_fds[1];
    poll_fds[0].fd = sock_recv;
    poll_fds[0].events = POLLIN;

    int poll_result = poll(poll_fds, 1, recv_timeout_ms);
    if (poll_result == -1) {
	   free(buffer);
	   return PORT_ERROR;
    } 
    else if (poll_result == 0) {
	   free(buffer);
	   // Баг что выдаёт наогда это.
	   return PORT_FILTER;
    }





    /*Получение пакета в буфер.*/
    scan_debug_log("Getting packet in buffer.\n", debug);

    struct sockaddr saddr;
    int saddr_size = sizeof saddr;

    auto start_time = std::chrono::steady_clock::now();
    for (; ;){
	   ssize_t data_size = recvfrom(sock_recv, buffer, RECV_BUFFER_SIZE, 0, &saddr, (socklen_t *)&saddr_size);
	   if (data_size == -1){
		  scan_debug_log("FAILED Getting packet in buffer.\n", debug);
		  free(buffer);
		  close(sock_recv);
		  return PORT_ERROR;
	   }

	   struct iphdr *iph = (struct iphdr*)buffer;
	   unsigned short iphdrlen = (iph->ihl) * 4;
	   if (iphdrlen < 20){
		  free(buffer);
		  close(sock_recv);
		  return PORT_ERROR;
	   }

	   /*Если протокол полученного пакета равен TCP.*/
	   if (iph->protocol == 6){ 
		  /*Извлечение ответа*/
		  scan_debug_log("Getting answer.\n", debug);

		  /*Получение самого пакета в структуру.*/
		  struct tcphdr *tcph = (struct tcphdr*)(buffer + iphdrlen);
		  struct sockaddr_in source;

		  /*Получение, IP отправителя.*/
		  memset(&source, 0, sizeof(source));
		  source.sin_addr.s_addr = iph->saddr;

		  /*IP получателя несходиться с IP отправителя.
		   * Один из главных процессов.*/
		  if (source.sin_addr.s_addr != dest_ip.s_addr){
			 auto current_time = std::chrono::steady_clock::now();
			 auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();

			 if (elapsed_time >= recv_timeout_ms) {
				free(buffer);
				close(sock_recv);
				return PORT_FILTER;
			 }
			 if (debug){
				nspr.nlog_error(">> A packet was received from the wrong host.\n");
			 }
			 continue;
		  }

		  if (debug){
			 if (tcph->syn != 0){
				nspr.nlog_custom("SCAN", "Flag SYN is: " + std::to_string(tcph->syn) + "\n", 0);
			 }
			 else {
				nspr.nlog_custom("SCAN", "Flag SYN is: " + std::to_string(tcph->syn) + "\n", 2);
			 }
			 if (tcph->ack != 0){
				nspr.nlog_custom("SCAN", "Flag ACK is: " + std::to_string(tcph->ack) + "\n", 0);
			 }
			 else {
				nspr.nlog_custom("SCAN", "Flag ACK is: " + std::to_string(tcph->ack) + "\n", 2);
			 }
			 if (tcph->rst != 0){
				nspr.nlog_custom("SCAN", "Flag RST is: " + std::to_string(tcph->rst) + "\n", 0);
			 }
			 else {
				nspr.nlog_custom("SCAN", "Flag RST is: " + std::to_string(tcph->rst) + "\n", 2);
			 }
		  }

		  int status = get_port_status(tcph->th_flags, no_syn_scan);
		  if (status != PORT_ERROR){
			 free(buffer);
			 close(sock_recv);
			 return status;
		  }else {
			 return PORT_ERROR;
		  }
	   }
    }

    /*В любом другом случае считаеться что выполнение
    функции кончилось ошибкой.*/
    free(buffer);
    close(sock_recv);
    return PORT_ERROR;
}

int
get_port_status(uint8_t flags, bool no_syn){
    /*Обработка пакета, писалась используя
    эту статью: https://nmap.org/book/synscan.html*/
    if (no_syn){
	   switch (flags) {
		  case 0x04:{
			 return PORT_CLOSED;
		  }
		  default:{
			 return PORT_OPEN;
		  }
	   }
    } 
    else {
	   switch (flags) {
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
