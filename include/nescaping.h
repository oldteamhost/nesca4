#ifndef NESCAPING_H
#define NESCAPING_H
#include <stdint.h>
#include "../include/net_utils.h"
#include <signal.h>
#include <time.h>
#include <iostream>
#include <cstring>
#ifdef _WIN32
#else
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#endif

/*Классический пинг, но сейчас много 
сайтов начинают уже блокировать его запросы.
Источники: 
 * https://datatracker.ietf.org/doc/html/rfc792
 * https://gist.github.com/bugparty/ccba5744ba8f1cece5e0
*/

#define ICMP_PING_PACKET_SIZE 64
#define ICMP_PING_SLEEP_RATE 400000
#define ICMP_RECV_TIMEOUT_MS 2000

class icmp_ping{
private:
    int ttl_val = 57;
    long double rtt_msec = 0;
    int addr_len;

    struct icmp_packet{
        struct icmphdr hdr;
        char msg[ICMP_PING_PACKET_SIZE-sizeof(struct icmphdr)];
    };

public:
    uint16_t 
    RFC792_csum(unsigned char* buffer, unsigned int length);
    bool 
    send_ping(int ping_sockfd, struct sockaddr_in *ping_addr,
                const char *rev_host, long double* rtt_msec_buffer);
    int
    ping(const char* ip, long double* buffer);
    

};



#endif
