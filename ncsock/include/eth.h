/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * Copyright (c) [2000] Dug Song <dugsong@monkey.org>
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef ETH_HEADER
#define ETH_HEADER

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
#include <sys/types.h>
#include <sys/ioctl.h>
#if __GLIBC__ >= 2 && __GLIBC_MINOR >= 1
  #include <netpacket/packet.h>
  #include <net/ethernet.h>
#else
  #include <asm/types.h>
  #include <linux/if_packet.h>
  #include <linux/if_ether.h>
#endif
#include <net/if.h>
#include "types.h"
#include "mt19937.h"
#include <bits/wordsize.h>

#define ETH_ADDR_LEN  6
#define ETH_ADDR_BITS 48
#define ETH_TYPE_LEN  2
#define ETH_CRC_LEN   4
#define ETH_HDR_LEN   14

#define ETH_LEN_MIN   64   /* minimum frame length with CRC */
#define ETH_LEN_MAX   1518 /* maximum frame length with CRC */

#define ETH_MTU (ETH_LEN_MAX - ETH_HDR_LEN - ETH_CRC_LEN)
#define ETH_MIN (ETH_LEN_MIN - ETH_HDR_LEN - ETH_CRC_LEN)

#define ETH_TYPE_PUP        0x0200 /* PUP protocol */
#define ETH_TYPE_IP         0x0800 /* IP protocol */
#define ETH_TYPE_ARP        0x0806 /* address resolution protocol */
#define ETH_TYPE_REVARP     0x8035 /* reverse addr resolution protocol */
#define ETH_TYPE_8021Q      0x8100 /* IEEE 802.1Q VLAN tagging */
#define ETH_TYPE_IPV6       0x86DD /* IPv6 protocol */
#define ETH_TYPE_MPLS       0x8847 /* MPLS */
#define ETH_TYPE_MPLS_MCAST 0x8848 /* MPLS Multicast */
#define ETH_TYPE_PPPOEDISC  0x8863 /* PPP Over Ethernet Discovery Stage */
#define ETH_TYPE_PPPOE      0x8864 /* PPP Over Ethernet Session Stage */
#define ETH_TYPE_LOOPBACK   0x9000 /* used to test interfaces */

#define ETH_IS_MULTICAST(ea) \
  (*(ea) & 0x01) /* is address mcast/bcast? */

#define ETH_ADDR_BROADCAST \
  "\xff\xff\xff\xff\xff\xff"

#define eth_pack_hdr(h, _dst, _src, _type) do {             \
  struct eth_header *eth_pack_p = (struct eth_header*)(h);  \
  memmove(&eth_pack_p->dst, &(_dst), ETH_ADDR_LEN);         \
  memmove(&eth_pack_p->src, &(_src), ETH_ADDR_LEN);         \
  eth_pack_p->type = htons(_type);                          \
} while (0)

#define MAC_STRING_TO_ADDR(mac_str)                         \
  ({                                                        \
    eth_addr_t addr_var;                                    \
    const char mac_str_[] = mac_str;                        \
    for (int i = 0; i < ETH_ADDR_LEN; ++i)                  \
      sscanf(mac_str_ + i * 3, "%2hhx", &addr_var.data[i]); \
    addr_var;                                               \
  })

#define MAC_ADDR_STRING_FORMAT "%02x:%02x:%02x:%02x:%02x:%02x"
#define PRINT_MAC_ADDR(addr)                                \
  printf(MAC_ADDR_STRING_FORMAT "\n",                       \
      (addr).data[0], (addr).data[1], (addr).data[2],       \
      (addr).data[3], (addr).data[4], (addr).data[5])

struct eth_handle
{
  int                fd;
  struct ifreq       ifr;
  struct sockaddr_ll sll;
};
typedef struct eth_handle eth_t;

typedef struct eth_addr {
  u8 data[ETH_ADDR_LEN];
} eth_addr_t;

struct eth_info
{
  char  srcmac[6];
  char  dstmac[6];
  eth_t *ethsd;
  char  devname[16];
};

struct ethtmp
{
  eth_t *ethsd;
  eth_addr_t dst;
  eth_addr_t src;
};

struct eth_header
{
  eth_addr_t dst;  /* dst addr */
  eth_addr_t src;  /* src addr */
  u16 type;        /* payload type */
};

__BEGIN_DECLS

u8 *build_eth(eth_addr_t src, eth_addr_t dst, u16 type,
    const char *data, u16 datalen, u32 *plen);
eth_t   *eth_open(const char *device);
ssize_t  eth_send(eth_t *e, const void *buf, size_t len);
eth_t   *eth_close(eth_t *e);

__END_DECLS

#endif
