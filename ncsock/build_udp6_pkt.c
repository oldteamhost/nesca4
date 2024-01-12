/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/udp.h"
#include "include/ip.h"

u8 *build_udp6_pkt(const struct in6_addr *source, const struct in6_addr *victim, u8 tc,
    u32 flowlabel, u8 hoplimit, u16 sport, u16 dport, const char *data, u16 datalen,
    u32 *plen, bool badsum)
{
  struct udp_header *udp;
  u32 udplen;
  u8 *packet;

  udp = (struct udp_header*)build_udp(sport, dport, data, datalen, &udplen);
  udp->check = ip6_pseudoheader_check(source, victim, IPPROTO_UDP, udplen, udp);
  if (badsum)
    udp->check = 0xffff;

  packet = build_ip6_pkt(source, victim, tc, flowlabel, IPPROTO_UDP, hoplimit,
      (char*)udp, udplen, plen);

  free(udp);
  return packet;
}
