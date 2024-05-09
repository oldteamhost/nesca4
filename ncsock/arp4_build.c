/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/arp.h"
#include "include/eth.h"
#include <netinet/in.h>

u8 *arp4_build(u16 hdr, u16 pro, u8 hln, u8 pln, u16 op, eth_addr_t sha,
               ip4_addreth_t spa, eth_addr_t tha, ip4_addreth_t tpa,
               u32 *pktlen)
{
  struct arp_hdr *arp;
  int packetlen;
  u8* pkt;

  packetlen = sizeof(struct arp_hdr);
  pkt = (u8*)malloc(packetlen);
  if (!pkt)
    return NULL;
  arp = (struct arp_hdr*)pkt;

  arp->hdr = htons(hdr);
  arp->pro = htons(pro);
  arp->hln = hln;
  arp->pln = pln;
  arp->op  = htons(op);

  memcpy(arp->data,     sha.data,  ETH_ADDR_LEN);
  memcpy(arp->data+6,   spa.data,  IP4_ADDR_LEN);
  memcpy(arp->data+10,  tha.data,  ETH_ADDR_LEN);
  memcpy(arp->data+16,  tpa.data,  IP4_ADDR_LEN);

  *pktlen = packetlen;
  return pkt;
}
