/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/icmp.h"
#include "include/ip.h"
#include "include/utils.h"
#include <stdlib.h>

int send_icmp_packet(struct ethtmp *eth, int fd, const u32 saddr, const u32 daddr, int ttl, bool df, u8 *ipops, int ipoptlen,
    u32 seq, u8 code, u8 type, const char *data, u16 datalen, int fragscan, bool badsum)
{
  struct sockaddr_storage dst;
  struct sockaddr_in *dst_in;
  u32 packetlen;
  int res = -1;
  u8 *packet;

  packet = build_icmp_pkt(saddr, daddr, ttl, random_u16(), 0, df, ipops, ipoptlen,
      seq, random_u16(), type, code, data, datalen, &packetlen, badsum);
  if (!packet)
    return -1;

  memset(&dst, 0, sizeof(dst));
  dst_in = (struct sockaddr_in *) &dst;
  dst_in->sin_family = AF_INET;
  dst_in->sin_addr.s_addr = daddr;
  res = send_ip_packet(eth, fd, &dst, fragscan, packet, packetlen);

  free(packet);
  return res;
}
