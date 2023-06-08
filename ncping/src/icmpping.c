#include <arpa/inet.h>
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

#include "../include/icmpping.h"
#include "../../ncsock/include/headers.h"
#include "../../ncsock/include/other.h"

double
icmp_ping(const char* dest_ip, int count, int timeout_ms,
	   u_int8_t type, u_int8_t code, u_int8_t ttl){
    int count_packets = 0;
    int ident = getpid() & 0xFFFF;
    static u_char outpack[4096];
    memset(outpack, 0, sizeof(outpack));

    struct timeval send_time, recv_time;

    /*Создание сокета.*/
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        return PING_ERROR;
    }

    /*Установка TTL на сокет.*/
    if (setsockopt(sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
        close(sock);
        return PING_ERROR;
    }

    /*Установка цели.*/
    struct sockaddr_in whereto;
    memset(&whereto, 0, sizeof(struct sockaddr_in));
    whereto.sin_family = AF_INET;
    whereto.sin_addr.s_addr = inet_addr(dest_ip);

    /*Создание и заполнение IMCP заголовка.
	* Функция из ncsock/src/headers.c*/
    struct icmp *icp = (struct icmp*)outpack;
    fill_icmp_header(icp, type, code, ident, count_packets);

    /*Расчёт контрольной суммы ICMP пакета.
	* Функция из ncsock/src/headers.c*/
    unsigned short *icmp_buffer = (unsigned short*)outpack;
    icp->icmp_cksum = checksum_16bit(icmp_buffer, sizeof(struct icmp));

    /*Отправка пакетов.*/
    gettimeofday(&send_time, NULL);
    for (; count_packets < count; count_packets++) {
        int send = sendto(sock, outpack, sizeof(struct icmp), 0, (struct sockaddr*)&whereto, sizeof(struct sockaddr));
        if (send < 0) {
            close(sock);
            return PING_ERROR;
        }
	   /*С каждым новым отправленым пакетом seq должен расти на 1.*/
	   icp->icmp_seq = count_packets;
    }

    /*Буфер для ответа.*/
    char packet[64];
    memset(packet, 0, sizeof(packet));
    socklen_t len = sizeof(whereto);

    /*Установка таймаута.*/
    struct timeval timeout = calculate_timeout_in_ms(timeout_ms);
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);

    /*Ожидание ответа от хоста.*/
    int select_result = select(sock + 1, &readfds, NULL, NULL, &timeout);
    switch (select_result) {
	   case -1:
		  /*Не удалось запустить select.*/
		  close(sock);
		  return PING_ERROR;

	   case 0:
		  /*Если таймаут вышел.*/
		  close(sock);
		  return PING_ERROR;

	   default:{
		  /*Принятие пакета от хоста, в буфер.*/
		  if (recv(sock, packet, sizeof(packet), 0) < 0) {
			 close(sock);
			 return PING_ERROR;
		  }
		  gettimeofday(&recv_time, NULL);
	   }
    }
    /*Расчёт веремени ответа.*/
    double elapsed_time = (recv_time.tv_sec - send_time.tv_sec) * 1000.0;
    elapsed_time += (recv_time.tv_usec - send_time.tv_usec) / 1000.0;

    /*Структуры куда передаёться буфер ответа,
	* для дальнейшей обработки, ответа.*/
    struct iphdr* ip_hdr = (struct iphdr*)packet;
    struct icmp* icmp_hdr = (struct icmp*)(packet + (ip_hdr->ihl << 2));

    /*Casual обработка. Мы шлём пакет типа ICMP_ECHO, если хост доступен
	* получаем пакет типа ICMP_ECHOREPLY*/
    if (icp->icmp_type == ICMP_ECHO){
	   if (icmp_hdr->icmp_type == ICMP_ECHOREPLY) {
		  close(sock);
		  return elapsed_time;
	   }
    }
    /*Резервная обработка, шлём пакет типа ICMP_TIMESTAMP,
	* если хост доступен, получаем пакети типа ICMP_TIMESTAMPREPLY*/
    else if (icp->icmp_type == ICMP_TIMESTAMP){
	   if (icmp_hdr->icmp_type == ICMP_TIMESTAMPREPLY) {
		  close(sock);
		  return elapsed_time;
	   }
    }
    /*Ещё одна, шлём пакет типа ICMP_INFO_REQUEST,
	* если хост доступен, получаем пакет типа ICMP_INFO_REPLY*/
    else if (icp->icmp_type == ICMP_INFO_REQUEST){
	   if (icmp_hdr->icmp_type == ICMP_INFO_REPLY) {
		  close(sock);
		  return elapsed_time;
	   }
    }

    /* Источник - https://nmap.org/man/ru/man-host-discovery.html*/
    /* Источник - https://gist.github.com/bugparty/ccba5744ba8f1cece5e0*/
    /* Источник - https://datatracker.ietf.org/doc/html/rfc792*/

    close(sock);
    return PING_ERROR;
}
