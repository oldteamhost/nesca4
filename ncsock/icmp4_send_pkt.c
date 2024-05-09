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

int icmp4_send_pkt(struct ethtmp *eth, int fd, const u32 src, const u32 dst,
                   int ttl, bool df, u8 *ipops, int ipoptlen, u32 seq, u8 code,
                   u8 type, const char *data, u16 datalen, int mtu,
                   bool badsum)
{
  struct sockaddr_storage _dst;
  struct sockaddr_in *dst_in;
  int res = -1;
  u32 pktlen;
  u8 *pkt;

  pkt = icmp4_build_pkt(src, dst, ttl, random_u16(), 0, df, ipops, ipoptlen,
      seq, random_u16(), type, code, data, datalen, &pktlen, badsum);
  if (!pkt)
    return -1;

  memset(&_dst, 0, sizeof(_dst));
  dst_in = (struct sockaddr_in*)&_dst;
  dst_in->sin_family = AF_INET;
  dst_in->sin_addr.s_addr = dst;
  
  res = ip_send(eth, fd, &_dst, mtu, pkt, pktlen);

  free(pkt);
  return res;
}
