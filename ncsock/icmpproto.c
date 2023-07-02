#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip_icmp.h>
#include <poll.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "include/icmpproto.h"

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
	if (fd== -1){return -1;}

	/*Устанока таймаута на recvfrom.*/
    struct pollfd poll_fds[1];
    poll_fds[0].fd = fd;
    poll_fds[0].events = POLLIN;
    int poll_result = poll(poll_fds, 1, timeout_ms);
    if (poll_result == -1) {
	   /*Poll не смогла чё-то сделать.*/
	   close(fd);
	   return -1;
    }else if (poll_result == 0) {
	   /*Вышел таймаут на recvfrom.*/
	   close(fd);
	   return -1;
    }

    char buffer[1500];
    struct sockaddr_in peer_addr;
    int addr_len = sizeof(peer_addr);

	struct timespec start_time, current_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

	for (;;){
    	int bytes = recvfrom(fd, buffer, sizeof(buffer), 0,(struct sockaddr*)&peer_addr, (socklen_t *)&addr_len);
    	if (bytes == -1) {
        	if (errno == EAGAIN || errno == EWOULDBLOCK) {
				close(fd);
            	return -1;
        	}
			close(fd);
        	return -1;
    	}
		struct iphdr *iph = (struct iphdr*)buffer;
		unsigned short iphdrlen = (iph->ihl) * 4;

		/*Поулучение из него IP отправителя.*/
	   	struct sockaddr_in source;
	   	memset(&source, 0, sizeof(source));
	   	source.sin_addr.s_addr = iph->saddr;
		struct in_addr dest; dest.s_addr = inet_addr(dest_ip);

		if (source.sin_addr.s_addr != dest.s_addr){
			clock_gettime(CLOCK_MONOTONIC, &current_time);
			long elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000 +
                            (current_time.tv_nsec - start_time.tv_nsec) / 1000000;
			if (elapsed_time >= timeout_ms) {
            	break;
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
			if (ntohs(icmp->ident) != identm){close(fd); return 0;}
			close(fd);
			return 0;
		}
	}

	close(fd);
	return -1;
}
