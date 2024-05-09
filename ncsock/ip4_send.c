/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int ip4_send(struct ethtmp *eth, int fd, const struct sockaddr_in *dst, int mtu,
             const u8 *pkt, u32 pktlen)
{
  struct ip4_hdr *ip;
  int res;

  ip = (struct ip4_hdr*)pkt;
  assert(pkt);
  assert((int)pktlen > 0);

  if (mtu && !(ntohs(ip->off) & IP4_DF) && (pktlen - ip->ihl * 4 > (u32)mtu))
    res = ip4_send_frag(fd, dst, pkt, pktlen, mtu);
  else
    res = IP4_SEND_ETH_OR_SD(fd, eth, dst, pkt, pktlen);

  return res;
}
