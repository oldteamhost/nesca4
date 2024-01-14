/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/arp.h"
#include "include/eth.h"
#include <netinet/in.h>

u8 *build_arp(u16 hdr, u16 pro, u8 hln, u8 pln,
    u16 operation, eth_addr_t sha, ip_addreth_t spa,
    eth_addr_t tha, ip_addreth_t tpa, u32 *plen)
{
  struct arp_header *arp;
  int packetlen;
  u8* packet;

  packetlen = sizeof(struct arp_header);
  packet = (u8*)malloc(packetlen);
  if (!packet)
    return NULL;
  arp = (struct arp_header *)packet;

  arp->hdr = htons(hdr);
  arp->pro = htons(pro);
  arp->hln = hln;
  arp->pln = pln;
  arp->op  = htons(operation);

  memcpy(arp->data,     sha.data,  ETH_ADDR_LEN);
  memcpy(arp->data+6,   spa.data,  _IP_ADDR_LEN);
  memcpy(arp->data+10,  tha.data,  ETH_ADDR_LEN);
  memcpy(arp->data+16,  tpa.data,  _IP_ADDR_LEN);

  *plen = packetlen;
  return packet;
}
