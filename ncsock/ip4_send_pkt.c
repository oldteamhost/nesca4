/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"
#include "include/utils.h"

int ip4_send_pkt(int fd, u32 src, u32 dst, u16 ttl, u8 proto, bool df,
                 const u8 *opt, int optlen, const char *data, u16 datalen,
                 int mtu)
{
  struct sockaddr_in dst_in;
  u32 pktlen;
  int res = -1;
  u8 *pkt;

  pkt = ip4_build(src, dst, proto, ttl, random_u16(), 5, df,
      opt, optlen, data, datalen, &pktlen);
  if (!pkt)
    return -1;

  memset(&dst_in, 0, sizeof(struct sockaddr_in));
  dst_in.sin_addr.s_addr = dst;
  dst_in.sin_port = 0;
  dst_in.sin_family = AF_INET;

  res = ip4_send(NULL, fd, &dst_in, mtu, pkt, pktlen);

  free(pkt);
  return res;
}

