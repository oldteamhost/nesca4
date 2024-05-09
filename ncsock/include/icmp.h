/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef ICMP_HEADER
#define ICMP_HEADER

#include "types.h"
#include "../include/eth.h"
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
#include "ip.h"

#define ICMP6_COMMON_HEADER_LEN     4
#define ICMP6_REDIRECT_LEN          (ICMP6_COMMON_HEADER_LEN + 36)
#define ICMP6_MAX_MESSAGE           (ICMP6_REDIRECT_LEN - ICMP6_COMMON_HEADER_LEN)
#define ICMP4_DEST_UNREACH  3   /*Destination Unreachable*/
#define ICMP4_NET_UNREACH   0   /*Network Unreachable*/
#define ICMP4_HOST_UNREACH  1   /*Host Unreachable*/
#define ICMP4_PROT_UNREACH  2   /*Protocol Unreachable*/
#define ICMP4_PORT_UNREACH  3   /*Port Unreachable*/
#define ICMP4_FRAG_NEEDED   4   /*Fragmentation Needed/DF set*/
#define ICMP4_SR_FAILED     5   /*Source Route failed*/
#define ICMP4_PARAMETERPROB  12 /*Parameter Problem*/
#define ICMP4_POINTINDIC_ER  0  /*Pointer indicates the error.*/
#define ICMP4_TIME_EXCEEDED  11 /*Time Exceeded*/
#define ICMP4_EXC_TTL        0  /*TTL count exceeded*/
#define ICMP4_EXC_FRAGTIME   1  /*Fragment Reass time exceeded*/
#define ICMP4_REDIRECT       5  /*Redirect (change route)*/
#define ICMP4_REDIR_NET      0  /*Redirect Net*/
#define ICMP4_REDIR_HOST     1  /*Redirect Host*/
#define ICMP4_REDIR_NETTOS   2  /*Redirect Net for TOS*/
#define ICMP4_REDIR_HOSTTOS  3  /*Redirect Host for TOS*/
#define ICMP4_ECHO           8  /*Echo Request*/
#define ICMP4_EXT_ECHO       42 /*Exceeded Echo*/
#define ICMP4_ECHOREPLY      0  /*Echo Reply*/
#define ICMP4_EXT_ECHOREPLY  43 /*Exceeded Echo Reply*/
#define ICMP4_TIMESTAMP      13 /*Timestamp Request*/
#define ICMP4_TIMESTAMPREPLY 14 /*Timestamp Reply*/
#define ICMP4_INFO_REQUEST   15 /*Information Request*/
#define ICMP4_INFO_REPLY     16 /*Information Reply*/
#define ICMP4_PAYLOAD_MAXLEN 1500

struct icmp4_hdr
{
  u8  type;
  u8  code;
  u16 check;
  u16 id;
  u16 seq;
  u8  data[ICMP4_PAYLOAD_MAXLEN];
};

struct icmp6_hdr
{
  u8  type;
  u8  code;
  u16 check;
  u8  data[ICMP6_MAX_MESSAGE];
};


struct icmp6_msg_echo
{
  u16 icmpv6_id;
  u16 icmpv6_seq;
  u8  icmpv6_data __flexarr;
};

struct icmp6_msg_nd
{
  uint32_t   icmpv6_flags;
  ip6_addr_t icmpv6_target;
  uint8_t    icmpv6_option_type;
  uint8_t    icmpv6_option_length;
  eth_addr_t icmpv6_mac;
};

union icmp6_msg
{
  struct icmp6_msg_echo echo;
  struct icmp6_msg_nd nd;
};

__BEGIN_DECLS

u8 *icmp4_build_pkt(const u32 src, const u32 dst, int ttl, u16 ipid, u8 tos,
                    bool df, u8 *ipopt, int ipoptlen, u16 seq, u16 id, u8 type,
                    u8 code, const char *data, u16 datalen, u32 *pktlen,
                    bool badsum);
u8 *icmp6_build_pkt(const struct in6_addr *src, const struct in6_addr *dst,
                    u8 tc, u32 flowlabel, u8 hoplimit, u16 seq, u16 id, u8 type,
                    u8 code, const char *data, u16 datalen, u32 *pktlen,
                    bool badsum);
int icmp4_send_pkt(struct ethtmp *eth, int fd, const u32 src, const u32 dst,
                   int ttl, bool df, u8 *ipops, int ipoptlen, u32 seq, u8 code,
                   u8 type, const char *data, u16 datalen, int mtu,
                   bool badsum);
double icmp4_qprc_ping(const char *dst, const char *src, int timeoutms,
                       int type, int code, int seq, int ttl, u8 *ipops,
                       int ipoptlen, const char *data, u16 datalen, int mtu,
                       bool badsum);

__END_DECLS

#endif

