/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef SYN_SCAN_H
#define SYN_SCAN_H

#include <iostream>
#include <cstdint>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string>
#include <random>
#include <netdb.h>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <mutex>
#include <netinet/in.h>
#include <vector>

#include "../include/prints.h"
#include "../include/other.h"

#define SEND_BUFFER_SIZE 2048
#define RECV_BUFFER_SIZE 2048

#define IP_HEADER_TTL 122
#define WINDOWS_SIZE  32768

#define PORT_OPEN   0
#define PORT_CLOSED 1
#define PORT_FILTER 2
#define PORT_ERROR -1

#define SYN_SCAN  1
#define XMAS_SCAN 2
#define FIN_SCAN  3
#define NULL_SCAN 4
#define ACK_PING  5

/*Опции для nesca_scan.*/
struct nesca_scan_opts{
    int scan_type;
    int source_port;
    bool debug;
    const char* source_ip;
    unsigned int seq;
};

/*Для расчёта фейковой контрольной суммы
 * CAPEC-287: TCP SYN Scan*/
struct pseudo_header{
   uint32_t source_address;
   uint32_t dest_address;
   uint8_t placeholder;
   uint8_t protocol;
   uint16_t tcp_length;
   struct tcphdr tcp;
};

/*Главная функция по сканированию.*/
int 
nesca_scan(struct nesca_scan_opts *ncot ,const char* ip, int port, int timeout_ms);

/*Более простой вывод лога.*/
void
scan_debug_log(std::string mes, bool debug);

/*Определение статуса порта.*/
int
get_port_status(unsigned char* buffer, bool no_syn);

#endif
