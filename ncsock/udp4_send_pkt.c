/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/udp.h"
#include "include/ip.h"

int udp4_send_pkt(struct ethtmp *eth, int fd, const u32 src, const u32 dst,
                  int ttl, u16 ipid, u8 *ipopt, int ipoptlen, u16 srcport,
                  u16 dstport, bool df, const char *data, u16 datalen, int mtu,
                  bool badsum)
{
  struct sockaddr_storage _dst;
  struct sockaddr_in *dst_in;
  int res = -1;
  u32 pktlen;
  u8 *pkt;

  pkt = udp4_build_pkt(src, dst, ttl, ipid, IP_TOS_DEFAULT, df, ipopt,
      ipoptlen, srcport, dstport, data, datalen, &pktlen, badsum);
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
