/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int ip_send(struct ethtmp *eth, int fd, const struct sockaddr_storage *dst,
            int mtu, const u8 *pkt, u32 pktlen)
{
  struct ip4_hdr *ip;
  
  ip = (struct ip4_hdr*)pkt;
  if (pktlen < 1)
    return -1;

  if (ip->version == 4) {
    assert(dst->ss_family == AF_INET);
    return ip4_send(eth, fd, (struct sockaddr_in*)dst, mtu, pkt, pktlen);
  }
  else if (ip->version == 6) {
    assert(dst->ss_family == AF_INET6);
    return ip6_send(eth, fd, (struct sockaddr_in6*)dst, pkt, pktlen);
  }

  return -1;
}

