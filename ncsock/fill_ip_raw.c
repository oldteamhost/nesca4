/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int fill_ip_raw(struct ip_header *ip, int packetlen, const u8 *ipopt,
    int ipoptlen, int tos, int id, int off, int ttl, int p, u32 saddr, u32 daddr)
{
  ip->version = 4;
  ip->ihl = 5 + (ipoptlen / 4);
  ip->tos = tos;
  ip->tot_len = htons(packetlen);
  ip->ident = htons(id);
  ip->frag_off = htons(off);
  ip->ttl = ttl;
  ip->protocol = p;
  ip->saddr = saddr;
  ip->daddr = daddr;

  if (ipoptlen)
    memcpy((u8 *) ip + sizeof(struct ip_header), ipopt, ipoptlen);

  ip->check = 0;
  ip->check = ip_cksum_add((u16*)ip, sizeof(struct ip_header) + ipoptlen, 0);

  return (sizeof(struct ip_header) + ipoptlen);
}
