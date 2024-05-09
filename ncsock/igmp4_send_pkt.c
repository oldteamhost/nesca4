/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/igmp.h"
#include "include/ip.h"

int igmp4_send_pkt(struct ethtmp *eth, int fd, const u32 src, const u32 dst,
                   int ttl, bool df, u8 *ipops, int ipoptlen, u16 ipid, u8 tos,
                   u8 type, u8 code, const char *data, u16 datalen, int mtu,
                   bool badsum)
{
  struct sockaddr_storage _dst;
  struct sockaddr_in *dst_in;
  u32 packetlen;
  int res = -1;
  u8 *packet;

  packet = igmp4_build_pkt(src, dst, ttl, ipid, tos, df, ipops,
      ipoptlen, type, code, data, datalen, &packetlen, badsum);
  if (!packet)
    return -1;

  memset(&_dst, 0, sizeof(_dst));
  dst_in = (struct sockaddr_in*)&_dst;
  dst_in->sin_family = AF_INET;
  dst_in->sin_addr.s_addr = dst;
  res = ip_send(eth, fd, &_dst, mtu, packet, packetlen);

  free(packet);
  return res;
}
