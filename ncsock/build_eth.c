/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/eth.h"
#include "libdnet/include/eth.h"

u8 *build_eth(eth_addr_t saddr, eth_addr_t daddr, u16 type,
    const char* data, u16 datalen, u32 *plen)
{
  struct eth_header *eth;
  int packetlen;
  u8 *packet;

  packetlen = sizeof(struct eth_header) + datalen;
  packet = (u8*)malloc(packetlen);
  if (!packet)
    return NULL;
  eth = (struct eth_header *)packet;

  eth->src = saddr;
  eth->dst = daddr;
  eth->type = htons(type);

  if (data && datalen)
    memcpy((u8 *)eth + sizeof(struct eth_header), data, datalen);

  *plen = packetlen;
  return packet;
}
