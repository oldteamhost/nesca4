/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef UDP_HEADER
#define UDP_HEADER

#include <stdbool.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/cdefs.h>

#include "../include/eth.h"
#include "types.h"

#define UDP_HDR_LEN 8

struct udp_hdr
{
  u16 srcport; /* source port */
  u16 dstport; /* destination port */
  u16 len;     /* udp length (including header) */
  u16 check;   /* udp checksum */
};

__BEGIN_DECLS

u8 *udp_build(u16 srcport, u16 dstport, const char *data, u16 datalen,
              u32 *pktlen);
u8 *udp4_build_pkt(const u32 src, const u32 dst, int ttl, u16 ipid, u8 tos,
                   bool df, u8 *ipopt, int ipoptlen, u16 srcport, u16 dstport,
                   const char *data, u16 datalen, u32 *pktlen, bool badsum);
u8 *udp6_build_pkt(const struct in6_addr *src, const struct in6_addr *dst,
                   u8 tc, u32 flowlabel, u8 hoplimit, u16 srcport, u16 dstport,
                   const char *data, u16 datalen, u32 *pktlen, bool badsum);
int udp4_send_pkt(struct ethtmp *eth, int fd, const u32 src, const u32 dst,
                  int ttl, u16 ipid, u8 *ipopt, int ipoptlen, u16 srcport,
                  u16 dstport, bool df, const char *data, u16 datalen, int mtu,
                  bool badsum);

__END_DECLS

#endif
