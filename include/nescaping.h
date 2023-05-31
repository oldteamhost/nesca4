#ifndef NESCAPING_H
#define NESCAPING_H

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <mutex>

#include "../include/other.h"
#include "../modules/include/easysock.h"
#include "../include/synscan.h"

/*Классический пинг, но сейчас много 
сайтов начинают уже блокировать его запросы.
Источники: 
 * https://datatracker.ietf.org/doc/html/rfc792
 * https://gist.github.com/bugparty/ccba5744ba8f1cece5e0
*/
class icmp_ping{
public:
    bool 
    ping(const char* address, int count, int timeout);
    double 
    get_last_time();
    int type = 1;

private:
    bool
    send_packet(int sockfd, struct sockaddr_in addr, int seq);
    bool 
    receive_packet(int sockfd, struct sockaddr_in addr, int seq, int timeout);
    unsigned short
    checksum(unsigned short* buf, int len);
    double
    get_time();

    std::chrono::high_resolution_clock::time_point start_time, end_time;
    double last_time;
};

class udp_ping{
private:
    
public:
    bool
    ping(std::string host, double* response_buf, int timeout_ms);
};

class tcp_ping{
public:
    const char* source_ip;
    bool
    ping(const char* ip, int port, int timeout_ms);
    bool
    ack_ping(const char* ip, int port, int timeout_ms);
private:
};

#endif
