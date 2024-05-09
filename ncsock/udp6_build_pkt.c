/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/udp.h"
#include "include/ip.h"

u8 *udp6_build_pkt(const struct in6_addr *src, const struct in6_addr *dst,
                   u8 tc, u32 flowlabel, u8 hoplimit, u16 srcport, u16 dstport,
                   const char *data, u16 datalen, u32 *pktlen, bool badsum)
{
  struct udp_hdr *udp;
  u32 udplen;
  u8 *pkt;

  udp = (struct udp_hdr*)udp_build(srcport, dstport, data, datalen, &udplen);
  udp->check = ip6_pseudocheck(src, dst, IPPROTO_UDP, udplen, udp);
  if (badsum)
    udp->check = 0xffff;

  pkt = ip6_build(src, dst, tc, flowlabel, IPPROTO_UDP, hoplimit,
      (char*)udp, udplen, pktlen);

  free(udp);
  return pkt;
}
