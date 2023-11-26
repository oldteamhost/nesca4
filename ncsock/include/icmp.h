/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef ICMP_HEADER
#define ICMP_HEADER

#include "types.h"
#include "../libdnet/include/ip6.h"
#include "../libdnet/include/eth.h"
#include "../libdnet/include/ip.h"
#include "mt19937.h"
#include "tcp.h"
#include "udp.h"
#include <netdb.h>
#include <netinet/in.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/cdefs.h>
#include "tcp.h"

#define ICMP6_COMMON_HEADER_LEN     4
#define ICMP6_REDIRECT_LEN          (ICMP6_COMMON_HEADER_LEN + 36)
#define ICMP6_MAX_MESSAGE           (ICMP6_REDIRECT_LEN - ICMP6_COMMON_HEADER_LEN)

/* Destination Unreachable Message */
#define ICMP_DEST_UNREACH  3   /*Destination Unreachable*/
#define ICMP_NET_UNREACH   0   /*Network Unreachable*/
#define ICMP_HOST_UNREACH  1   /*Host Unreachable*/
#define ICMP_PROT_UNREACH  2   /*Protocol Unreachable*/
#define ICMP_PORT_UNREACH  3   /*Port Unreachable*/
#define ICMP_FRAG_NEEDED   4   /*Fragmentation Needed/DF set*/
#define ICMP_SR_FAILED     5   /*Source Route failed*/

/* Parameter Problem Message */
#define ICMP_PARAMETERPROB  12 /*Parameter Problem*/
#define ICMP_POINTINDIC_ER  0  /*Pointer indicates the error.*/

/* Time Exceeded Message */
#define ICMP_TIME_EXCEEDED  11 /*Time Exceeded*/
#define ICMP_EXC_TTL        0  /*TTL count exceeded*/
#define ICMP_EXC_FRAGTIME   1  /*Fragment Reass time exceeded*/

/* Redirect Message */
#define ICMP_REDIRECT       5 /*Redirect (change route)*/
#define ICMP_REDIR_NET      0 /*Redirect Net*/
#define ICMP_REDIR_HOST     1 /*Redirect Host*/
#define ICMP_REDIR_NETTOS   2 /*Redirect Net for TOS*/
#define ICMP_REDIR_HOSTTOS  3 /*Redirect Host for TOS*/

/* Echo Message */
#define ICMP_ECHO           8  /*Echo Request*/
#define ICMP_EXT_ECHO       42 /*Exceeded Echo*/
#define ICMP_ECHOREPLY      0  /*Echo Reply*/
#define ICMP_EXT_ECHOREPLY  43 /*Exceeded Echo Reply*/

/*Timestamp Message*/
#define ICMP_TIMESTAMP      13 /*Timestamp Request*/
#define ICMP_TIMESTAMPREPLY 14 /*Timestamp Reply*/

/*Information Message*/
#define ICMP_INFO_REQUEST   15 /*Information Request*/
#define ICMP_INFO_REPLY     16 /*Information Reply*/

__BEGIN_DECLS

struct icmp6_header
{
  u8 type;
  u8 code;
  u16 checksum;
  u8 data[ICMP6_MAX_MESSAGE];
};

struct icmp4_header
{
  u8 type;
  u8 code;
  u16 checksum;
  u16 id;
  u16 seq;
#define ICMP_MAX_PAYLOAD_LEN 1500
  u8 data[ICMP_MAX_PAYLOAD_LEN];
};

struct icmpv6_msg_echo
{
  u16 icmpv6_id;
  u16 icmpv6_seq;
  u8  icmpv6_data __flexarr;
};

struct icmpv6_msg_nd
{
  uint32_t   icmpv6_flags;
  ip6_addr_t icmpv6_target;
  uint8_t    icmpv6_option_type;
  uint8_t    icmpv6_option_length;
  eth_addr_t icmpv6_mac;
};


union icmpv6_msg
{
  struct icmpv6_msg_echo echo;
  struct icmpv6_msg_nd nd;
};

u8 *build_icmp_pkt(const u32 saddr, const u32 daddr, int ttl, u16 ipid, u8 tos, bool df, u8 *ipopt,
    int ipoptlen, u16 seq, u16 id, u8 ptype, u8 pcode, const char *data, u16 datalen, u32 *plen);

u8 *build_icmp6_pkt(const struct in6_addr *saddr, const struct in6_addr *daddr, u8 tc, u32 flowlabel,
    u8 hoplimit, u16 seq, u16 id, u8 ptype, u8 pcode, const char *data, u16 datalen, u32 *plen);

int send_icmp_packet(int fd, const u32 saddr, const u32 daddr, int ttl, bool df, u8 *ipops, int ipoptlen,
    u32 seq, u8 code, u8 type, const char *data, u16 datalen, int fragscan);

double icmp_ping(const char* dest_ip, const char* source_ip, int timeout_ms, int type,
    int code, int seq, int ttl, const char *data, u16 datalen, int fragscan);

__END_DECLS

#endif

