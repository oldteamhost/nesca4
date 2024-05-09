/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/sctp.h"
#include "include/ip.h"
#include "include/utils.h"

int sctp4_send_pkt(struct ethtmp *eth, int fd, const u32 src, const u32 dst,
                   int ttl, bool df, u8 *ipops, int ipoptlen, u16 srcport,
                   u16 dstport, char *chunks, int chunkslen, u32 vtag,
                   const char *data, u16 datalen, int mtu, bool adler32sum,
                   bool badsum)
{
  struct sockaddr_storage _dst;
  struct sockaddr_in *dst_in;
  int res = -1;
  u32 pktlen;
  u8 *pkt;

  pkt = sctp4_build_pkt(src, dst, ttl, random_u16(),
      0, df, ipops, ipoptlen, srcport, dstport, vtag, chunks,
      chunkslen, data, datalen, &pktlen,
      adler32sum, badsum);
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

