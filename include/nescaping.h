#ifndef NESCAPING_H
#define NESCAPING_H
#include "../include/netutils.h"
#include "../include/other.h"
#include <stdint.h>
#include <thread>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <cstring>
#include <signal.h>
#include <time.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#include <fcntl.h>

/*Классический пинг, но сейчас много 
сайтов начинают уже блокировать его запросы.
Источники: 
 * https://datatracker.ietf.org/doc/html/rfc792
 * https://gist.github.com/bugparty/ccba5744ba8f1cece5e0
*/

class icmp_ping{
private:
    int ttl_val = 54;
    long double rtt_msec = 0;
    int addr_len;
    static constexpr int packet_size = 64;

    struct icmp_packet{
        struct iphdr ip;
        struct icmphdr hdr;
        char msg[packet_size-sizeof(struct icmphdr)];
    };

    uint16_t 
    RFC792_csum(unsigned char* buffer, unsigned int length);
    bool 
    send_ping(int ping_sockfd, struct sockaddr_in *ping_addr,
                const char *rev_host, long double* rtt_msec_buffer);
public:
    int ping_timeout = 100;
    const char* source_ip;
    int recv_timeout = 340;
    int packets = 4;

    int
    ping(const char* ip, long double* buffer);
};

class udp_ping{
public:
    int ping_udp(const std::string & ip, int timeout, double& buffer);
};

#endif
