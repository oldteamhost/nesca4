#include <arpa/inet.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/file.h>

#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/time.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <unistd.h>

#include "include/icmpping.h"
#include "../include/generation.h"
#include "../ncsock/include/headers.h"
#include "../ncsock/include/socket.h"
#include "../ncsock/include/other.h"
#include "../ncsock/include/ncread.h"

double
icmp_ping(const char* dest_ip, const char* source_ip, int timeout_ms, int type_ping){
	double response_time = -1;
	int send;

	if (type_ping == 1){send = send_icmp_packet(dest_ip, source_ip, timeout_ms, 8, 0, 64, 0);}
	else if (type_ping == 2){send = send_icmp_packet(dest_ip, source_ip, timeout_ms, 13, 0, 64, 0);}
	else if (type_ping == 2){send = send_icmp_packet(dest_ip, source_ip, timeout_ms, 15, 0, 64, 0);}
	if (send != 0){return -1;}

	char packet[64];
    memset(packet, 0, sizeof(packet));
	
	int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock == -1){return -1;}

	/*Установка таймаута.*/
    struct timeval timeout = calculate_timeout_in_ms(timeout_ms);
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);

    /*Ожидание ответа от хоста.*/
	struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    int select_result = select(sock + 1, &readfds, NULL, NULL, &timeout);
    switch (select_result) {
	   case -1:
		  /*Не удалось запустить select.*/
		  close(sock);
	      return -1;

	   case 0:
		  /*Если таймаут вышел.*/
		  close(sock);
	      return -1;

	   default:{
		  /*Принятие пакета от хоста, в буфер.*/
		  struct sockaddr saddr;
          int saddr_size = sizeof(saddr);
		  if (recvfrom(sock, packet, sizeof(packet), 0, &saddr, (socklen_t *)&saddr_size) < 0) {
			 close(sock);
			 return -1;
		  }
	   }
    }

	struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);

	response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0; 
    response_time += (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

	struct iphdr* ip_hdr = (struct iphdr*)packet;
    struct icmp* icmp_hdr = (struct icmp*)(packet + (ip_hdr->ihl << 2));

	if (type_ping == 1){
	   if (icmp_hdr->icmp_type == ICMP_ECHOREPLY) {
		  close(sock);
		  return response_time;
	   }
    }
	else if (type_ping == 2){
	   if (icmp_hdr->icmp_type == ICMP_TIMESTAMPREPLY) {
		  close(sock);
		  return response_time;
	   }
    }
	else if (type_ping == 3){
	   if (icmp_hdr->icmp_type == ICMP_INFO_REPLY) {
		  close(sock);
		  return response_time;
	   }
    }

	/* Источник - https://nmap.org/man/ru/man-host-discovery.html*/
    /* Источник - https://gist.github.com/bugparty/ccba5744ba8f1cece5e0*/
    /* Источник - https://datatracker.ietf.org/doc/html/rfc792*/

	return response_time;
}

int
send_icmp_packet(const char* dest_ip, const char* source_ip, int timeout_ms,
	             u_int8_t type, u_int8_t code, u_int8_t ttl, int seq){
    /*Создание сокета.*/
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock == -1){return -1;}

    int ident = generate_seq();
    struct timeval send_time, recv_time;
	int seq_ip_header = generate_seq();

    /*Установка цели.*/
    struct sockaddr_in whereto;
    memset(&whereto, 0, sizeof(struct sockaddr_in));
    whereto.sin_family = AF_INET;

    whereto.sin_addr.s_addr = inet_addr(dest_ip);
    static u_char outpack[4096];
    memset(outpack, 0, sizeof(outpack));
    struct iphdr *iph_send = (struct iphdr*)outpack;
	struct icmphdr *icmph = (struct icmphdr*)(outpack+sizeof(struct iphdr));

    /*Сообщаем ядру, что не нужно генерировать IP заголовок
	* потому что мы сами его сделали.*/
    int set_hdrincl = set_socket_hdrincl(sock);
    if (set_hdrincl == -1){close(sock);return -1;}

	/*Заполнение IP заголовка.*/
    fill_ip_header(iph_send, source_ip, dest_ip, sizeof(outpack),
		        IPPROTO_ICMP, seq_ip_header, IP_DF, ttl, 0, 4, 0);

	/*Расчёт контрольной суммы IP заголовка.*/
    int check_sum_ip = checksum_16bit((unsigned short *)outpack, sizeof(icmphdr)+ sizeof(outpack));
    iph_send->check = check_sum_ip;

    /*Создание и заполнение IMCP заголовка.*/
	icmph->type = type;
    icmph->code = code;
    icmph->un.echo.sequence = seq; 
    icmph->un.echo.id = generate_seq();
	icmph->checksum = 0;

    /*Расчёт контрольной суммы ICMP пакета.
	* Функция из ncsock/src/headers.c*/
    unsigned short *icmp_buffer = (unsigned short*)outpack;
    icmph->checksum = checksum_16bit(icmp_buffer, sizeof(struct icmphdr));

    /*Отправка пакета.*/
    int send = sendto(sock, outpack, sizeof(icmphdr) + sizeof(iphdr), 0, (struct sockaddr*)&whereto, sizeof(whereto));
    if (send == -1) {
		perror("sendto failed");
        close(sock);
        return -1;
    }

    return 0;
}
