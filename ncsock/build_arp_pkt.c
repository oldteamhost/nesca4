/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/arp.h"
#include "include/eth.h"
#include <netinet/in.h>

u8 *build_arp_pkt(eth_addr_t ethsaddr, eth_addr_t ethdaddr,
    u16 hdr, u16 pro, u8 hln, u8 pln, u16 operation, eth_addr_t sha,
    ip_addreth_t spa, eth_addr_t tha, ip_addreth_t tpa, u32 *packetlen)
{
  struct arp_header *arp;
  u32 arplen;
  u8 *packet;

  arp = (struct arp_header*)build_arp(ARP_HRD_ETH, ARP_PRO_IP, ETH_ADDR_LEN,
      _IP_ADDR_LEN, operation, sha, spa, tha, tpa, &arplen);
  packet = build_eth(ethsaddr, ethdaddr, ETH_TYPE_ARP, (char*)arp, arplen, packetlen);

  free(arp);
  return packet;
}
