/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/udp.h"

#include <stdlib.h>
#include <string.h>
#include <netdb.h>

extern u16 ip6_pseudoheader_check(const struct in6_addr *saddr, const struct in6_addr *daddr, u8 nxt, u32 len, const void *hstart);
extern u8 *build_ip6_pkt(const struct in6_addr *source, const struct in6_addr *victim, u8 tc, u32 flowlabel,
    u8 nexthdr, int hoplimit, const char *data, u16 datalen, u32 *plen);

u8 *build_udp6_pkt(const struct in6_addr *source, const struct in6_addr *victim, u8 tc,
    u32 flowlabel, u8 hoplimit, u16 sport, u16 dport, const char *data, u16 datalen, u32 *plen)
{
  struct udp_header *udp;
  u32 udplen;
  u8 *ipv6;

  udp = (struct udp_header *) build_udp(sport, dport, data, datalen, &udplen);
  udp->check = ip6_pseudoheader_check(source, victim, IPPROTO_UDP, udplen, udp);
  ipv6 = build_ip6_pkt(source, victim, tc, flowlabel, IPPROTO_UDP, hoplimit, (char *) udp, udplen, plen);
  free(udp);

  return ipv6;
}
