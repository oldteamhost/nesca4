/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int send_ip_eth(struct ethtmp *eth, const u8 *packet, u32 plen)
{
  u32 packetlen;
  u8 *ethframe;
  int res;

  ethframe = build_eth(eth->src, eth->dst, ETH_TYPE_IP,
      (char*)packet, plen, &packetlen);
  if (!ethframe)
    return -1;
  res = eth_send(eth->ethsd, ethframe, packetlen);

  free(ethframe);
  return res;
}
