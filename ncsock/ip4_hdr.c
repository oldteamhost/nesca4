/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int ip4_hdr(struct ip4_hdr *ip, int pktlen, const u8 *opt, int optlen,
            int tos, int id, int off, int ttl, int proto, u32 src, u32 dst)
{
  ip->version = 4;
  ip->ihl = 5 + (optlen / 4);
  ip->tos = tos;
  ip->totlen = htons(pktlen);
  ip->id = htons(id);
  ip->off = htons(off);
  ip->ttl = ttl;
  ip->proto = proto;
  ip->src = src;
  ip->dst = dst;

  if (optlen)
    memcpy((u8*)ip + sizeof(struct ip4_hdr), opt, optlen);

  ip->check = 0;
  ip->check = ip_check_add((u16*)ip, sizeof(struct ip4_hdr) + optlen, 0);

  return (sizeof(struct ip4_hdr) + optlen);
}
