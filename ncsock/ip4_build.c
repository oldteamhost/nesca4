/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

u8 *ip4_build(u32 src, u32 dst, u8 proto, int ttl, u16 id, u8 tos,
	      bool df, const u8 *opt, int optlen, const char *data,
	      u16 datalen, u32 *pktlen)
{
  struct ip4_hdr *ip;
  int packetlen = 0;
  u8 *pkt;

  packetlen = sizeof(struct ip4_hdr) + optlen + datalen;
  pkt = (u8*)malloc(packetlen);
  if (!pkt)
    return NULL;
  ip = (struct ip4_hdr *)pkt;
  assert(optlen % 4 == 0);

  ip4_hdr(ip, packetlen, opt, optlen, tos, id,
      df ? IP4_DF : 0, ttl, proto, src, dst);

  if (data && datalen)
    memcpy((u8*) ip + sizeof(struct ip4_hdr) + optlen, data, datalen);

  *pktlen = packetlen;
  return pkt;
}
