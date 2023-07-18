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

#include "../include/nescalog.h"
#include "../ncsock/include/headers.h"
#include "../include/other.h"

#define PORT_OPEN             0
#define PORT_CLOSED           1
#define PORT_FILTER           2
#define PORT_ERROR           -1
#define PORT_OPEN_OR_FILTER   3
#define PORT_NO_FILTER        4

#define SYN_SCAN              1
#define XMAS_SCAN             2
#define FIN_SCAN              3
#define NULL_SCAN             4
#define ACK_SCAN              5
#define WINDOW_SCAN           6
#define MAIMON_SCAN           7

#define SEND_BUFFER_SIZE      2048
#define RECV_BUFFER_SIZE      2048
#define WINDOWS_SIZE          1024

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

/*Опции для nesca_scan.
 * Основные опции я решил добавить в аргументы,
 * а другие долбануть в структуре, мне кажется
 * так будет лучше.*/
struct nesca_scan_opts{
    int source_port;
    const char* source_ip;
    unsigned int seq;
    int ttl;
	bool packet_trace;
	struct tcp_flags tcpf;
};

int /*Главная функция в сканирование, она отправляет TCP пакет.*/
nesca_scan(struct nesca_scan_opts *ncot ,const char* ip, int port, int timeout_ms);

struct tcp_flags /*Функция для установки TCP флагов.*/
set_flags(int scan_type);

int /*Определение статуса порта.*/
get_port_status(unsigned char* buffer, int scan_type);

#endif
