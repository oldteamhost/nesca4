/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef IP_HEADER
#define IP_HEADER

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

__BEGIN_DECLS

struct ip_header
{
#define MAX_IHL_LEN 60
  u8  ihl:4;     /* header length */
#define IP_VERSION 4
  u8  version:4; /* ip proto version */
#define DEFAULT_TOS 0
  u8  tos;       /* type of service */
  u16 tot_len;   /* total length */
  u16 ident;     /* identificator */
#define IP_RF 0x8000  /* reserved fragment flag */
#define IP_DF 0x4000  /* dont fragment flag */
#define IP_MF 0x2000  /* more fragments flag */
#define IP_DM 0x1fff  /* mask for fragmenting bits */
  u16 frag_off;  /* fragment offset */
#define MAX_TTL 255
#define DEFAULT_TTL 121
  u8  ttl;       /* time to live */
  u8  protocol;  /* see addr.h */
  u16 check;     /* 16 bit checksum */
  u32 saddr;     /* source ip address */
  u32 daddr;     /* dest ip address */
};

#include "types.h"

/* create packet */
int fill_ip_raw(struct ip_header *ip, int packetlen, const u8 *ipopt,
    int ipoptlen, int tos, int id, int off, int ttl, int p, u32 saddr, u32 daddr);
u8 *build_ip_pkt(u32 saddr, u32 daddr, u8 proto, int ttl, u16 ipid,
    u8 tos, bool df, const u8 *ipopt, int ipoptlen, const char *data, u16 datalen, u32 *plen);
u8 *build_ip6_pkt(const struct in6_addr *source, const struct in6_addr *victim, u8 tc, u32 flowlabel,
    u8 nexthdr, int hoplimit, const char *data, u16 datalen, u32 *plen);

/* checksum */
u16 ip4_pseudoheader_check(u32 saddr, u32 daddr, u8 proto, u16 len, const void *hstart);
u16 ip6_pseudoheader_check(const struct in6_addr *saddr, const struct in6_addr *daddr, u8 nxt, u32 len, const void *hstart);
u16 in_cksum(u16 *ptr, int nbytes);

/* pre pre send packet */
int send_frag_ip_packet(int fd, const struct sockaddr_in *dst, const u8 *packet, u32 plen, u32 mtu);
int send_ip_raw(int fd, const struct sockaddr_in *dst, const u8 *packet, u32 plen);

/* pre send packet */
int send_ip4_packet(int fd, const struct sockaddr_in *dst, int fragscan, const u8 *packet, u32 plen);
int send_ip6_packet(int fd, const struct sockaddr_in6 *dst, const u8 *packet, u32 plen);

/* done func */
int send_ip_packet(int fd, const struct sockaddr_storage *dst, int fragscan, const u8 *packet, u32 plen);
int send_ip_empty(int sock, u32 saddr, u32 daddr, u16 ttl, u8 proto, bool df, const u8 *ipopt, int ipoptlen,
    const char* data, u16 datalen, int fragscan);

__END_DECLS

#endif
