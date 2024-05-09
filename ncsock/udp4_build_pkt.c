/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/udp.h"
#include "include/ip.h"

u8 *udp4_build_pkt(const u32 src, const u32 dst, int ttl, u16 ipid, u8 tos,
                   bool df, u8 *ipopt, int ipoptlen, u16 srcport, u16 dstport,
                   const char *data, u16 datalen, u32 *pktlen, bool badsum)
{
  struct udp_hdr *udp;
  u32 udplen;
  u8 *pkt;

  udp = (struct udp_hdr*)udp_build(srcport, dstport, data, datalen, &udplen);
  udp->check = ip4_pseudocheck(src, dst, IPPROTO_UDP, udplen, udp);
  if (badsum)
    udp->check = 0xffff;

  pkt = ip4_build(src, dst, IPPROTO_UDP, ttl, ipid, tos, df, ipopt,
      ipoptlen, (char*)udp, udplen, pktlen);

  free(udp);
  return pkt;
}
