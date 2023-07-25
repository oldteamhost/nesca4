/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/icmpping.h"

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
	if (ret == EOF) {return -1;}

	std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
	ret = recv_icmp_packet(dest_ip, timeout_ms, type, code, ident);
	if (ret == EOF) {return -1;}
	std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

	std::chrono::duration<double, std::milli> elapsed_ms = end_time - start_time;
	response_time = elapsed_ms.count();

	/* Источник - https://nmap.org/man/ru/man-host-discovery.html*/
    /* Источник - https://gist.github.com/bugparty/ccba5744ba8f1cece5e0*/
    /* Источник - https://datatracker.ietf.org/doc/html/rfc792*/

	return response_time;
};


