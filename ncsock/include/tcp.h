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
#include "../include/eth.h"

#ifdef ONLY_COMPILE
#include "../compile.h"
#endif

struct tcp_header
{
  u16 th_sport;  /* Source port. */
  u16 th_dport;  /* Destination port. */
  u32 th_seq;    /* Sequence number. */
  u32 th_ack;    /* Acknowledgement number. */
#if (defined(WORDS_BIGENDIAN))
  u8  th_off:4;  /* Data offset. */
  u8  th_x2:4;   /* (unused). */
#else
  u8  th_x2:4;   /* (unused). */
  u8  th_off:4;  /* Data offset. */
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
#define SYN_PACKET            6
#define XMAS_PACKET           7
#define FIN_PACKET            8
#define NULL_PACKET           9
#define ACK_PACKET            10
#define WINDOW_PACKET         11
#define MAIMON_PACKET         12
#define PSH_PACKET            13

#define TCP_HDR_LEN     20 /* base TCP header length */
#define TCP_OPT_LEN     2  /* base TCP option length */
#define TCP_OPT_LEN_MAX 40
#define TCP_HDR_LEN_MAX (TCP_HDR_LEN + TCP_OPT_LEN_MAX)

#define TCP_OPT_EOL         0 /* end of option list */
#define TCP_OPT_NOP         1 /* no operation */
#define TCP_OPT_MSS         2 /* maximum segment size */
#define TCP_OPT_WSCALE      3 /* window scale factor, RFC 1072 */
#define TCP_OPT_SACKOK      4 /* SACK permitted, RFC 2018 */
#define TCP_OPT_SACK        5 /* SACK, RFC 2018 */
#define TCP_OPT_ECHO        6 /* echo (obsolete), RFC 1072 */
#define TCP_OPT_ECHOREPLY   7 /* echo reply (obsolete), RFC 1072 */
#define TCP_OPT_TIMESTAMP   8 /* timestamp, RFC 1323 */
#define TCP_OPT_POCONN      9 /* partial order conn, RFC 1693 */
#define TCP_OPT_POSVC       10 /* partial order service, RFC 1693 */
#define TCP_OPT_CC          11 /* connection count, RFC 1644 */
#define TCP_OPT_CCNEW       12 /* CC.NEW, RFC 1644 */
#define TCP_OPT_CCECHO      13 /* CC.ECHO, RFC 1644 */
#define TCP_OPT_ALTSUM      14 /* alt checksum request, RFC 1146 */
#define TCP_OPT_ALTSUMDATA  15 /* alt checksum data, RFC 1146 */
#define TCP_OPT_SKEETER     16 /* Skeeter */
#define TCP_OPT_BUBBA       17 /* Bubba */
#define TCP_OPT_TRAILSUM    18 /* trailer checksum */
#define TCP_OPT_MD5         19 /* MD5 signature, RFC 2385 */
#define TCP_OPT_SCPS        20 /* SCPS capabilities */
#define TCP_OPT_SNACK       21 /* selective negative acks */
#define TCP_OPT_REC         22 /* record boundaries */
#define TCP_OPT_CORRUPT     23 /* corruption experienced */
#define TCP_OPT_SNAP        24 /* SNAP */
#define TCP_OPT_TCPCOMP     26 /* TCP compression filter */
#define TCP_OPT_MAX         27

struct tcp_opt
{
  u8 opt_type;        /* option type */
  u8 opt_len;         /* option length >= TCP_OPT_LEN */
  union tcp_opt_data
  {
    u16 mss;          /* TCP_OPT_MSS */
    u8 wscale;        /* TCP_OPT_WSCALE */
    u16 sack[19];     /* TCP_OPT_SACK */
    u32 echo;         /* TCP_OPT_ECHO{REPLY} */
    u32 timestamp[2]; /* TCP_OPT_TIMESTAMP */
    u32 cc;           /* TCP_OPT_CC{NEW,ECHO} */
    u8 cksum;         /* TCP_OPT_ALTSUM */
    u8 md5[16];       /* TCP_OPT_MD5 */
    u8 data8[TCP_OPT_LEN_MAX - TCP_OPT_LEN];
  } opt_data;
};

__BEGIN_DECLS

u8 *build_tcp(u16 sport, u16 dport, u32 seq, u32 ack, u8 reserved, u8 flags,
              u16 window, u16 urp, const u8 *tcpopt, int tcpoptlen,
              const char *data, u16 datalen, u32 *packetlen);

u8 *build_tcp_pkt(u32 saddr, u32 daddr, u8 ttl, u16 ipid, u8 tos, bool df,
                  const u8 *ipopt, int ipoptlen, u16 sport, u16 dport, u32 seq,
                  u32 ack, u8 reserved, u8 flags, u16 window, u16 urp,
                  const u8 *tcpopt, int tcpoptlen, const char *data,
                  u16 datalen, u32 *packetlen, bool badsum);

u8 *build_tcp6_pkt(const struct in6_addr *source, const struct in6_addr *victim,
                   u8 tc, u32 flowlabel, u8 hoplimit, u16 sport, u16 dport,
                   u32 seq, u32 ack, u8 reserved, u8 flags, u16 window, u16 urp,
                   const u8 *tcpopt, int tcpoptlen, const char *data,
                   u16 datalen, u32 *packetlen, bool badsum);

int send_tcp_packet(struct ethtmp *eth, int fd, const u32 saddr,
                    const u32 daddr, int ttl, bool df, u8 *ipops, int ipoptlen,
                    u16 sport, u16 dport, u32 seq, u32 ack, u8 reserved,
                    u8 flags, u16 window, u16 urp, u8 *options, int optlen,
                    const char *data, u16 datalen, int fragscan, bool badsum);

int fast_send_tcp(int fd, const char *saddr, const char *daddr, int ttl,
                  u16 dport, u8 flags, const char *data, u16 datalen);

double tcp_ping(int type, const char* ip, const char* source_ip, int dest_port,
		int source_port, u16 window, u32 ack, int timeout_ms, int ttl, u8 *ipops,
		int ipoptlen, const char *data, u16 datalen, int fragscan, bool badsum);

struct tcp_flags set_flags(uint8_t type);
struct tcp_flags str_set_flags(const char *flags);
u8 set_tcp_flags(struct tcp_flags *tf);

__END_DECLS

#endif
