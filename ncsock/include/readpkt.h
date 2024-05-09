/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef READPKT_HEADER
#define READPKT_HEADER
#include "igmp.h"
#include "types.h"
#include "ip.h"
#include "eth.h"
#include "arp.h"
#include "tcp.h"
#include "udp.h"
#include "icmp.h"
#include <sys/cdefs.h>
#include <sys/socket.h>

#define RECV_BUFFER_SIZE 65535

__BEGIN_DECLS

struct readfiler
{
  struct sockaddr_storage *ip;
  u8  protocol;
  u8  second_protocol;
};

int read_packet(struct readfiler *rf, int recv_timeout_ms, u8 **buffer);

struct ip4_hdr*   ext_iphdr(u8 *buf);
struct tcp_hdr*  ext_tcphdr(u8 *buf);
struct udp_hdr*  ext_udphdr(u8 *buf);
struct icmp4_hdr* ext_icmphdr(u8 *buf);
struct igmp_hdr* ext_igmphdr(u8 *buf);
int                 ext_payload(u8 *buf, u8 *rbuf);

void print_ipdr(const struct ip4_hdr *iphdr);
void print_tcphdr(const struct tcp_hdr *tcphdr);
void print_udphdr(const struct udp_hdr *udphdr);
void print_icmphdr(const struct icmp4_hdr *icmphdr);
void print_payload(const u8 *payload, int len);
void print_payload_ascii(const u8 *payload, int len);

__END_DECLS


#endif


