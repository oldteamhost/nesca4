/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/arp.h"
#include "include/eth.h"
#include "include/utils.h"
#include "include/eth.h"
#include <stdlib.h>

int send_arpreq_packet(eth_t *eth, eth_addr_t ethsrc,
    ip_addreth_t ipsrc, ip_addreth_t ipdst, u16 operation)
{
  u32 packetlen;
  u8 *packet;
  int res;

  packet = build_arp_pkt(ethsrc, MAC_STRING_TO_ADDR(ETH_ADDR_BROADCAST),
      ARP_HRD_ETH, ARP_PRO_IP, ETH_ADDR_LEN, _IP_ADDR_LEN,
      operation, ethsrc, ipsrc, MAC_STRING_TO_ADDR("\x00\x00\x00\x00\x00\x00"),
      ipdst, &packetlen);
  if (!packet)
    return -1;

  res = eth_send(eth, packet, packetlen);

  free(packet);
  return res;
}
