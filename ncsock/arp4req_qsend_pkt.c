/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/arp.h"
#include "include/eth.h"
#include "include/eth.h"
#include <stdlib.h>

int arp4req_qsend_pkt(eth_t *eth, eth_addr_t ethsrc, ip4_addreth_t ipsrc,
                      ip4_addreth_t ipdst)
{
  u32 pktlen;
  u8 *pkt;
  int res;

  pkt = arp4_build_pkt(ethsrc, MAC_STRING_TO_ADDR(ETH_ADDR_BROADCAST),
      ARP_HRD_ETH, ARP_PRO_IP, ETH_ADDR_LEN, IP4_ADDR_LEN,
      ARP_OP_REQUEST, ethsrc, ipsrc, MAC_STRING_TO_ADDR("\x00\x00\x00\x00\x00\x00"),
      ipdst, &pktlen);
  if (!pkt)
    return -1;

  res = eth_send(eth, pkt, pktlen);

  free(pkt);
  return res;
}
