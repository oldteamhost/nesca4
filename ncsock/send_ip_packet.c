/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int send_ip_packet(struct ethtmp *eth, int fd, const struct sockaddr_storage *dst, int fragscan, const u8 *packet, u32 plen)
{
  struct ip_header *ip;

  ip = (struct ip_header*)packet;
  if (plen < 1)
    return -1;

  if (ip->version == 4) {
    assert(dst->ss_family == AF_INET);
    return send_ip4_packet(eth, fd, (struct sockaddr_in*)dst, fragscan, packet, plen);
  }
  else if (ip->version == 6) {
    assert(dst->ss_family == AF_INET6);
    return send_ip6_packet(eth, fd, (struct sockaddr_in6*)dst, packet, plen);
  }

  return -1;
}

