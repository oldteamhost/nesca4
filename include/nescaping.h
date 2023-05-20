#ifndef NESCAPING_H
#define NESCAPING_H
#include "../include/netutils.h"
#include "../include/other.h"
#include <stdint.h>
#include <signal.h>
#include <time.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#include <fcntl.h>
#endif

/*Классический пинг, но сейчас много 
сайтов начинают уже блокировать его запросы.
Источники: 
 * https://datatracker.ietf.org/doc/html/rfc792
 * https://gist.github.com/bugparty/ccba5744ba8f1cece5e0
*/

class icmp_ping{
private:
    static constexpr int packet_size = 64;
    int ttl_val = 57;
    long double rtt_msec = 0;
    int addr_len;

    struct icmp_packet{
        struct icmphdr hdr;
        char msg[packet_size-sizeof(struct icmphdr)];
    };

public:
    int ping_timeout = 1000;
    int recv_timeout = 2000;
    int packets = 4;

   uint16_t 
    RFC792_csum(unsigned char* buffer, unsigned int length);
    bool 
    send_ping(int ping_sockfd, struct sockaddr_in *ping_addr,
                const char *rev_host, long double* rtt_msec_buffer);
    int
    ping(const char* ip, long double* buffer);
};

#endif
