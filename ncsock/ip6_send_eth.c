/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int ip6_send_eth(struct ethtmp *eth, const u8 *pkt, u32 pktlen)
{
  u32 packetlen;
  eth_t *ethsd;
  u8 *ethframe;
  int res;

  ethframe = eth_build(eth->src, eth->dst, ETH_TYPE_IPV6,
      (char*)pkt, pktlen, &packetlen);
  if (!ethframe)
    return -1;

  if (!eth->ethsd)
    ethsd = eth_open_cached(eth->devname);
  else
    ethsd = eth->ethsd;
  res = eth_send(ethsd, ethframe, packetlen);

  free(ethframe);
  return res;
}
