/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/arp.h"
#include "include/eth.h"
#include <netinet/in.h>

u8 *arp4_build_pkt(eth_addr_t ethsrc, eth_addr_t ethdst, u16 hdr, u16 pro,
                   u8 hln, u8 pln, u16 op, eth_addr_t sha, ip4_addreth_t spa,
                   eth_addr_t tha, ip4_addreth_t tpa, u32 *pktlen)
{
  struct arp_hdr *arp;
  u32 arplen;
  u8 *pkt;

  arp = (struct arp_hdr*)arp4_build(hdr, pro, hln,
      pln, op, sha, spa, tha, tpa, &arplen);
  pkt = eth_build(ethsrc, ethdst, ETH_TYPE_ARP, (char*)arp, arplen,
      pktlen);

  free(arp);
  return pkt;
}
