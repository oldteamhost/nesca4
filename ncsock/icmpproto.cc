/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include <arpa/inet.h>
#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <poll.h>
#include <stdint.h>
#include <signal.h>
#include <chrono>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <mutex>
#include <unistd.h>
#include "include/icmpproto.h"

std::mutex fuck_icmp;

uint16_t calculate_checksum(unsigned char* buffer, int bytes){
    uint32_t checksum = 0;
    unsigned char* end = buffer + bytes;

    if (bytes % 2 == 1){end = buffer + bytes - 1;checksum += (*end) << 8;}

    while (buffer < end) {
        checksum += buffer[0] << 8;
        checksum += buffer[1];
        buffer += 2;
    }

    uint32_t carray = checksum >> 16;
    while (carray) {
        checksum = (checksum & 0xffff) + carray;
        carray = checksum >> 16;
    }

    checksum = ~checksum;
    return checksum & 0xffff;
}

int 
send_icmp_packet(struct sockaddr_in* addr, int type,
				int code, int ident, int seq, int ttl){

	int fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd== -1){return -1;}
	if (setsockopt(fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0){close(fd);return -1;}

	struct icmp4_header icmp;
	memset(&icmp, 0, sizeof(icmp));

	icmp.type = type;
    icmp.code = code;
    icmp.ident = htons(ident);
    icmp.seq = htons(seq);
	icmp.checksum = 0;
	strncpy(icmp.magic, MAGIC, MAGIC_LEN);
	icmp.checksum = htons(calculate_checksum((unsigned char*)&icmp, sizeof(icmp)));

	int bytes = sendto(fd, &icmp, sizeof(icmp), 0,(struct sockaddr*)addr, sizeof(*addr));
    if (bytes == -1) {
		close(fd);
        return -1;
    }

	close(fd);
	return 0;
}

int 
recv_icmp_packet(const char* dest_ip, int timeout_ms, int type,
				int code, int identm){
	int fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd == -1){return -1;}

    char buffer[1500];
    struct sockaddr_in peer_addr;
	memset(&peer_addr, 0, sizeof(peer_addr));

	/*Установка таймаута на сокет.
	 * Для RAW IMCP протокола это работает, я из-за этого потратил 2 недели :(*/
	struct timeval timeout;
	timeout.tv_sec = timeout_ms / 1000;
	timeout.tv_usec = (timeout_ms % 1000) * 1000;
	int result = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	if (result < 0) {
    	close(fd);
    	return -1;
	}

    int addr_len = sizeof(peer_addr);
    auto start_time = std::chrono::steady_clock::now();
	for (;;){
    	int bytes = recvfrom(fd, buffer, sizeof(buffer), 0,(struct sockaddr*)&peer_addr, (socklen_t *)&addr_len);
		if (bytes == -1) {
			/*Сработал таймаут.*/
			if (errno == EAGAIN || errno == EWOULDBLOCK){
				close(fd);
				return -1;
			}
			/*Просто ошибка.*/
			close(fd);
        	return -1;
    	}
		/*Получение IP заголовка.*/
		struct iphdr *iph = (struct iphdr*)buffer;

		/*Поулучение из него IP отправителя.*/
	   	struct sockaddr_in source;
	   	memset(&source, 0, sizeof(source));
	   	source.sin_addr.s_addr = iph->saddr;
		struct in_addr dest; dest.s_addr = inet_addr(dest_ip);

		if (source.sin_addr.s_addr != dest.s_addr){
		  	auto current_time = std::chrono::steady_clock::now();
		  	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
		  	if (elapsed_time >= timeout_ms) {
			 	close(fd);
			 	return -1;
		  	}
			continue;
		}
		else {
			struct icmp4_header* icmp = (struct icmp4_header*)(buffer + 20);
			if (type == ICMP_ECHO){
				if (icmp->type == ICMP_ECHOREPLY){
					close(fd);
					return 0;
				}
			}
			if (type == ICMP_TIMESTAMP){
				if (icmp->type == ICMP_TIMESTAMPREPLY){
					close(fd);
					return 0;
				}
			}
			if (type == ICMP_INFO_REQUEST){
				if (icmp->type == ICMP_INFO_REPLY){
					close(fd);
					return 0;
				}
			}
		}
		break;
	}

	close(fd);
	return -1;
}
