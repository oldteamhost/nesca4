/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#ifndef NESC_ENGINE_HEADER
#define NESC_ENGINE_HEADER

#include "../ncsock/include/icmp.h"
#include "../ncsock/include/tcp.h"
#include "../ncsock/include/udp.h"
#include "../ncsock/include/ip.h"
#include "../include/nescalog.h"
#include "../config/nescaopts.h"
#include "nescadata.h"

#define ICMP_PING_ECHO            1
#define ICMP_PING_INFO            2
#define ICMP_PING_TIME            3
#define TCP_PING_SYN              4
#define TCP_PING_ACK              5
#define TCP_SYN_SCAN              6
#define TCP_XMAS_SCAN             7
#define TCP_FIN_SCAN              8
#define TCP_NULL_SCAN             9
#define TCP_ACK_SCAN              10
#define TCP_WINDOW_SCAN           11
#define TCP_MAIMON_SCAN           12
#define TCP_PSH_SCAN              13
#define SCTP_INIT_SCAN            14
#define SCTP_COOKIE_SCAN          15
#define SCTP_INIT_PING            16
#define UDP_PING                  17
#define UDP_SCAN                  18
#define ARP_PING                  19

#define PORT_OPEN             0
#define PORT_CLOSED           1
#define PORT_FILTER           2
#define PORT_ERROR           -1
#define PORT_OPEN_OR_FILTER   3
#define PORT_NO_FILTER        4

typedef u32 ipnesca_t;

int nescasocket(void);
u8 *tcp_probe(NESCADATA *n, const ipnesca_t dst, u16 dport, u8 type, u32 *packetlen);
u8 *icmp_probe(NESCADATA *n, const ipnesca_t dst, u8 type, u32 *packetlen);
u8 *sctp_probe(NESCADATA *n, const ipnesca_t dst, u16 dport, u8 type, u32 *packetlen);
u8 *udp_probe(NESCADATA *n, const ipnesca_t dst, u16 dport, u8 type, u32 *packetlen);
u8 *arp_probe(NESCADATA *n, const ipnesca_t dst, u8 type, u32 *packetlen);
u8* read_icmp_probe(NESCADATA *n, ipnesca_t dst, u8 type);
u8* read_tcp_probe(NESCADATA *n, ipnesca_t dst, u8 type);

ssize_t sendprobe(int fd, NESCADATA *n, const ipnesca_t dst, u16 dport, u8 type);
u8*     recvpacket(NESCADATA *n, ipnesca_t dst, u8 type, int timeout_ms, double *rtt);
bool    readping(NESCADATA *n, const ipnesca_t dst, u8 *packet, u8 type);
int     readscan(const ipnesca_t dst, u8 *packet, u8 type);

double nescaping(NESCADATA *n, ipnesca_t dst, u8 type);

#endif

