#include <arpa/inet.h>
#include <iostream>
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
#include "../ncsock/include/icmpproto.h"

double
icmp_ping(const char* dest_ip, int timeout_ms, int type, int code, int seq, int ttl){
	double response_time = -1;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
    addr.sin_port = 0;
	memset(&addr, 0, sizeof(addr));

    if (inet_aton(dest_ip, (struct in_addr*)&addr.sin_addr.s_addr) == 0){return -1;};
    int ident = getpid();

	int ret = send_icmp_packet(&addr, type, code, ident, seq, ttl);
	if (ret == -1){return -1;}

	struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

	ret = recv_icmp_packet(dest_ip, timeout_ms, type, code, ident);
	if (ret == -1){return -1;}

	struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);

	response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0; 
    response_time += (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

	/* Источник - https://nmap.org/man/ru/man-host-discovery.html*/
    /* Источник - https://gist.github.com/bugparty/ccba5744ba8f1cece5e0*/
    /* Источник - https://datatracker.ietf.org/doc/html/rfc792*/

	return response_time;
};


