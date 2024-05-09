/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"
#include "include/ip.h"
#include "include/utils.h"

int tcp4_send_pkt(struct ethtmp *eth, int fd, const u32 src, const u32 dst,
                  int ttl, bool df, u8 *ipops, int ipoptlen, u16 srcport,
                  u16 dstport, u32 seq, u32 ack, u8 reserved, u8 flags, u16 win,
                  u16 urp, u8 *opt, int optlen, const char *data, u16 datalen,
                  int mtu, bool badsum)
{
  struct sockaddr_storage _dst;
  struct sockaddr_in *dst_in;
  u32 pktlen;
  int res = -1;
  u8 *pkt;

  pkt = tcp4_build_pkt(src, dst, ttl, random_u16(), IP_TOS_DEFAULT,
		       df, ipops, ipoptlen, srcport, dstport, seq,
		       ack, reserved, flags, win, urp, opt, optlen,
		       data, datalen, &pktlen, badsum);
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
