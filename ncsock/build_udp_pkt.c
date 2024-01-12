/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/udp.h"
#include "include/ip.h"

u8 *build_udp_pkt(const u32 saddr, const u32 daddr, int ttl, u16 ipid, u8 tos,
    bool df, u8 *ipopt, int ipoptlen, u16 sport, u16 dport, const char *data,
    u16 datalen, u32 *plen, bool badsum)
{
  struct udp_header *udp;
  u32 udplen;
  u8 *packet;

  udp = (struct udp_header*)build_udp(sport, dport, data, datalen, &udplen);
  udp->check = ip4_pseudoheader_check(saddr, daddr, IPPROTO_UDP, udplen, udp);
  if (badsum)
    udp->check = 0xffff;

  packet = build_ip_pkt(saddr, daddr, IPPROTO_UDP, ttl, ipid, tos, df, ipopt,
      ipoptlen, (char *) udp, udplen, plen);

  free(udp);
  return packet;
}
