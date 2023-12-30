/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef TCP_HEADER
#define TCP_HEADER

#include <netinet/in.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/cdefs.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "types.h"
#include "mt19937.h"
#include "../libdnet/include/ip6.h"
#include "../libdnet/include/eth.h"
#include "../libdnet/include/ip.h"
#include <bits/wordsize.h>

__BEGIN_DECLS

struct tcp_header
{
  u16 th_sport;  /* Source port. */
  u16 th_dport;  /* Destination port. */
  u32 th_seq;    /* Sequence number. */
  u32 th_ack;    /* Acknowledgement number. */
#if __BYTE_ORDER == __LITTLE_ENDIAN
  u8  th_x2:4;   /* (unused). */
  u8  th_off:4;  /* Data offset. */
#else
  u8  th_off:4;  /* Data offset. */
  u8  th_x2:4;   /* (unused). */
#endif
  u8  th_flags;  /* TCP flags. */
  u16 th_win;    /* Window. */
  u16 th_sum;    /* Checksum. */
  u16 th_urp;    /* Urgent pointer. */
};

struct tcp_flags
{
#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
#define TH_CWR 0x80
#define TH_ECE 0x40
  u8 syn; /* Synchronize sequence numbers. */
  u8 ack; /* Acknowledgment field significant. */
  u8 rst; /* Reset the connection. */
  u8 fin; /* No more data from sender. */
  u8 psh; /* Push Function. */
  u8 urg; /* Urgent Pointer field significant. */
  u8 cwr; /* Congestion Window reduced. */
  u8 ece; /* Explicit Congestion notification echo. */
};

u8 *build_tcp(u16 sport, u16 dport, u32 seq, u32 ack, u8 reserved, u8 flags,
    u16 window, u16 urp, const u8 *tcpopt, int tcpoptlen, const char *data, u16 datalen, u32 *packetlen);

u8 *build_tcp_pkt(u32 saddr, u32 daddr, u8 ttl, u16 ipid, u8 tos,
  bool df, const u8 *ipopt, int ipoptlen, u16 sport, u16 dport, u32 seq, u32 ack, u8 reserved, u8 flags, u16 window,
  u16 urp, const u8 *tcpopt, int tcpoptlen, const char *data, u16 datalen, u32 *packetlen);

u8 *build_tcp6_pkt(const struct in6_addr *source, const struct in6_addr *victim, u8 tc, u32 flowlabel,
  u8 hoplimit, u16 sport, u16 dport, u32 seq, u32 ack, u8 reserved, u8 flags, u16 window, u16 urp,
  const u8 *tcpopt, int tcpoptlen, const char *data, u16 datalen, u32 *packetlen);

struct tcp_flags set_flags(uint8_t type);
struct tcp_flags str_set_flags(const char *flags);
u8 set_tcp_flags(struct tcp_flags *tf);

#define SYN_PACKET            1
#define XMAS_PACKET           2
#define FIN_PACKET            3
#define NULL_PACKET           4
#define ACK_PACKET            5
#define WINDOW_PACKET         6
#define MAIMON_PACKET         7
#define PSH_PACKET            8

int send_tcp_packet(int fd, const u32 saddr, const u32 daddr, int ttl, bool df,
    u8 *ipops, int ipoptlen, u16 sport, u16 dport, u32 seq, u32 ack, u8 reserved, u8 flags, u16 window, u16 urp,
    u8 *options, int optlen, const char *data, u16 datalen, int fragscan);

int fast_send_tcp(int fd, const char* saddr, const char* daddr, int ttl, u16 dport, u8 flags,
    const char* data, u16 datalen);

double tcp_ping(int type, const char* ip, const char* source_ip, int dest_port,
    int source_port, u16 window, u32 ack, int timeout_ms, int ttl, u8 *ipops,
    int ipoptlen, const char *data, u16 datalen, int fragscan);

__END_DECLS

#endif
