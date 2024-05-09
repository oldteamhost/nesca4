/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef ARP_HEADER
#define ARP_HEADER

#include <netinet/in.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/cdefs.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <bits/wordsize.h>

#include "ip.h"
#include "types.h"
#include "mt19937.h"
#include "../include/eth.h"

#define ARP_HRD_ETH       0x0001 /* ethernet hardware */
#define ARP_HRD_IEEE802   0x0006 /* IEEE 802 hardware */
#define ARP_PRO_IP        0x0800 /* IP protocol */
#define ARP_OP_REQUEST    1      /* request to resolve ha given pa */
#define ARP_OP_REPLY      2      /* response giving hardware address */
#define ARP_OP_REVREQUEST 3      /* request to resolve pa given ha */
#define ARP_OP_REVREPLY   4      /* response giving protocol address */
#define ARP_HEADER_LEN    8
#define ARP_ETHIP_LEN     20

struct arp_hdr
{
  u16 hdr; /* fmt hardware addr */
  u16 pro; /* fmt protocol addr */
  u8  hln; /* len hardware addr */
  u8  pln; /* len protocol addr */
  u16 op;  /* operation */
  u8  data[20];
};

__BEGIN_DECLS

u8 *arp4_build(u16 hdr, u16 pro, u8 hln, u8 pln, u16 op, eth_addr_t sha,
               ip4_addreth_t spa, eth_addr_t tha, ip4_addreth_t tpa,
               u32 *pktlen);
u8 *arp4_build_pkt(eth_addr_t ethsrc, eth_addr_t ethdst, u16 hdr, u16 pro,
                   u8 hln, u8 pln, u16 op, eth_addr_t sha, ip4_addreth_t spa,
                   eth_addr_t tha, ip4_addreth_t tpa, u32 *pktlen);
int arp4req_qsend_pkt(eth_t *eth, eth_addr_t ethsrc, ip4_addreth_t ipsrc,
                      ip4_addreth_t ipdst);

__END_DECLS

#endif

