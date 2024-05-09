/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "include/eth.h"

u8 *eth_build(eth_addr_t src, eth_addr_t dst, u16 type, const char *data,
              u16 datalen, u32 *pktlen)
{
  struct eth_hdr *eth;
  u32 packetlen;
  u8 *pkt;

  packetlen = ETH_HDR_LEN + datalen;
  pkt = (u8*)malloc(packetlen);
  if (!pkt)
    return NULL;
  eth = (struct eth_hdr*)pkt;

  memset(eth, 0, ETH_HDR_LEN);
  eth->dst  = dst;
  eth->src  = src;
  eth->type = htons(type);
  
  if (data && datalen)
    memcpy((u8*)eth + ETH_HDR_LEN,
	   data, datalen);

  *pktlen = packetlen;
  return pkt;
}
