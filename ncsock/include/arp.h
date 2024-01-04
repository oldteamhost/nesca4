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
#include "ip.h"
#include "types.h"
#include "mt19937.h"
#include "../libdnet/include/ip6.h"
#include "../libdnet/include/eth.h"
#include "../libdnet/include/ip.h"
#include <bits/wordsize.h>

__BEGIN_DECLS

#define ARP_HEADER_LEN 8
#define ARP_ETHIP_LEN 20

struct arp_header
{
  u16 hdr; /* fmt hardware addr */
  u16 pro; /* fmt protocol addr */
  u8  hln; /* len hardware addr */
  u8  pln; /* len protocol addr */
  u16 op;  /* operation */
  u8 data[20];
};

#define ARP_HRD_ETH     0x0001 /* ethernet hardware */
#define ARP_HRD_IEEE802 0x0006 /* IEEE 802 hardware */
#define ARP_PRO_IP      0x0800 /* IP protocol */

#define ARP_OP_REQUEST    1 /* request to resolve ha given pa */
#define ARP_OP_REPLY      2 /* response giving hardware address */
#define ARP_OP_REVREQUEST 3 /* request to resolve pa given ha */
#define ARP_OP_REVREPLY   4 /* response giving protocol address */

u8 *build_arp(u16 hdr, u16 pro, u8 hln, u8 pln, u16 operation, eth_addr_t sha,
    ip_addreth_t spa, eth_addr_t tha, ip_addreth_t tpa, u32 *plen);

u8 *build_arp_pkt(eth_addr_t ethsaddr, eth_addr_t ethdaddr,
    u16 hdr, u16 pro, u8 hln, u8 pln, u16 operation, eth_addr_t sha,
    ip_addreth_t spa, eth_addr_t tha, ip_addreth_t tpa, u32 *packetlen);

int send_arpreq_packet(eth_t *eth, eth_addr_t saddr, ip_addreth_t ipsaddr,
    ip_addreth_t ipdaddr, u16 operation);

__END_DECLS

#endif

