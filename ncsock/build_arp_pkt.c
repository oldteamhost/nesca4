/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/arp.h"
#include "include/eth.h"
#include <netinet/in.h>

u8 *build_arp_pkt(eth_addr_t ethsrc, eth_addr_t ethdst,
    u16 hdr, u16 pro, u8 hln, u8 pln, u16 operation, eth_addr_t sha,
    ip_addreth_t spa, eth_addr_t tha, ip_addreth_t tpa, u32 *packetlen)
{
  struct arp_header *arp;
  u32 arplen;
  u8 *packet;

  arp = (struct arp_header*)build_arp(hdr, pro, hln,
      pln, operation, sha, spa, tha, tpa, &arplen);
  packet = build_eth(ethsrc, ethdst, ETH_TYPE_ARP, (char*)arp, arplen,
      packetlen);

  free(arp);
  return packet;
}
