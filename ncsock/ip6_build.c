/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

u8 *ip6_build(const struct in6_addr *src, const struct in6_addr *dst, u8 tc,
              u32 flowlabel, u8 nexthdr, int hoplimit, const char *data,
              u16 datalen, u32 *pktlen)
{
  u8 *pkt;
  
  *pktlen= sizeof(struct ip6_hdr) + datalen;
  pkt = (u8*)malloc(*pktlen);
  if (!pkt)
    return NULL;

  ip6_hdr(pkt, tc, flowlabel, datalen, nexthdr,
      hoplimit, *src, *dst);
  memcpy(pkt + sizeof(struct ip6_hdr), data, datalen);

  return pkt;
}
