/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/arp.h"
#include "include/eth.h"
#include "include/utils.h"
#include "libdnet/include/eth.h"
#include <stdlib.h>

int send_arpreq_packet(eth_t *eth, eth_addr_t saddr, ip_addreth_t ipsaddr,
    ip_addreth_t ipdaddr, u16 operation)
{
  eth_addr_t dst, dst1;
  u8 *packet;
  u32 packetlen;
  int res;

  memcpy(dst.data, ETH_ADDR_BROADCAST, ETH_ADDR_LEN);
  memcpy(dst1.data, "\x00\x00\x00\x00\x00\x00", ETH_ADDR_LEN);

  packet = build_arp_pkt(saddr, dst, ARP_HRD_ETH, ARP_PRO_IP, ETH_ADDR_LEN, _IP_ADDR_LEN,
      operation, saddr, ipsaddr, dst1, ipdaddr, &packetlen);
  if (!packet)
    return -1;

  res = eth_send(eth, packet, packetlen);

  free(packet);
  return res;
}
