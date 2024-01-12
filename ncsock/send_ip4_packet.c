/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"
#include <stdio.h>

int send_ip4_packet(struct ethtmp *eth, int fd, const struct sockaddr_in *dst, int fragscan, const u8 *packet, u32 plen)
{
  struct ip_header *ip;
  int res;

  ip = (struct ip_header *)packet;
  assert(packet);
  assert((int)plen > 0);

  if (fragscan && !(ntohs(ip->frag_off) & IP_DF) && (plen - ip->ihl * 4 > (u32)fragscan))
    res = send_frag_ip_packet(fd, dst, packet, plen, fragscan);
  else
    res = SEND_IP_PACKET_ETH_OR_SD(fd, eth, dst, packet, plen);

  return res;
}
