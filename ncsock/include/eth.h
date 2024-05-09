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

#define ETH_ADDR_LEN        6
#define ETH_ADDR_BITS       48
#define ETH_TYPE_LEN        2
#define ETH_CRC_LEN         4
#define ETH_HDR_LEN         14
#define ETH_LEN_MIN         64   /* minimum frame length with CRC */
#define ETH_LEN_MAX         1518   /* maximum frame length with CRC */
#define ETH_MTU             (ETH_LEN_MAX - ETH_HDR_LEN - ETH_CRC_LEN)
#define ETH_MIN             (ETH_LEN_MIN - ETH_HDR_LEN - ETH_CRC_LEN)
#define ETH_TYPE_IPV4       0x0800 /* Internet Protocol Version 4              */
#define ETH_TYPE_ARP        0x0806 /* Address Resolution Protocol              */
#define ETH_TYPE_FRAMERELAY 0x0808 /* Frame Relay ARP                          */
#define ETH_TYPE_PPTP       0x880B /* Point-to-Point Tunneling Protocol        */
#define ETH_TYPE_GSMP       0x880C /* General Switch Management Protocol       */
#define ETH_TYPE_RARP       0x8035 /* Reverse Address Resolution Protocol      */
#define ETH_TYPE_IPV6       0x86DD /* Internet Protocol Version 6              */
#define ETH_TYPE_MPLS       0x8847 /* MPLS                                     */
#define ETH_TYPE_MPS_UAL    0x8848 /* MPLS with upstream-assigned label        */
#define ETH_TYPE_MCAP       0x8861 /* Multicast Channel Allocation Protocol    */
#define ETH_TYPE_PPPOE_D    0x8863 /* PPP over Ethernet Discovery Stage        */
#define ETH_TYPE_PPOE_S     0x8864 /* PPP over Ethernet Session Stage          */
#define ETH_TYPE_CTAG       0x8100 /* Customer VLAN Tag Type                   */
#define ETH_TYPE_EPON       0x8808 /* Ethernet Passive Optical Network         */
#define ETH_TYPE_PBNAC      0x888E /* Port-based network access control        */
#define ETH_TYPE_STAG       0x88A8 /* Service VLAN tag identifier              */
#define ETH_TYPE_ETHEXP1    0x88B5 /* Local Experimental Ethertype             */
#define ETH_TYPE_ETHEXP2    0x88B6 /* Local Experimental Ethertype             */
#define ETH_TYPE_ETHOUI     0x88B7 /* OUI Extended Ethertype                   */
#define ETH_TYPE_PREAUTH    0x88C7 /* Pre-Authentication                       */
#define ETH_TYPE_LLDP       0x88CC /* Link Layer Discovery Protocol (LLDP)     */
#define ETH_TYPE_MACSEC     0x88E5 /* Media Access Control Security            */
#define ETH_TYPE_MVRP       0x88F5 /* Multiple VLAN Registration Protocol      */
#define ETH_TYPE_MMRP       0x88F6 /* Multiple Multicast Registration Protocol */
#define ETH_TYPE_FRRR       0x890D /* Fast Roaming Remote Request              */

#define ETH_IS_MULTICAST(ea) (*(ea) & 0x01) /* is address mcast/bcast? */
#define ETH_ADDR_BROADCAST "\xff\xff\xff\xff\xff\xff"
#define MAC_ADDR_STRING_FORMAT "%02x:%02x:%02x:%02x:%02x:%02x"

struct eth_handle { int fd; struct ifreq ifr; struct sockaddr_ll sll; };
typedef struct eth_handle eth_t;
typedef struct eth_addr { u8 data[ETH_ADDR_LEN]; } eth_addr_t;

struct ethtmp
{
  eth_t      *ethsd;
  eth_addr_t  dst;
  eth_addr_t  src;
  char        devname[16];
};

struct eth_hdr
{
  eth_addr_t dst;
  eth_addr_t src;
  u16        type;
};

#define eth_pack_hdr(h, _dst, _src, _type)                                     \
  do {                                                                         \
    struct eth_header *eth_pack_p = (struct eth_header *)(h);                  \
    memmove(&eth_pack_p->dst, &(_dst), ETH_ADDR_LEN);                          \
    memmove(&eth_pack_p->src, &(_src), ETH_ADDR_LEN);                          \
    eth_pack_p->type = htons(_type);                                           \
  } while (0)

#define MAC_STRING_TO_ADDR(mac_str)                                            \
  ({                                                                           \
    eth_addr_t addr_var;                                                       \
    const char mac_str_[] = mac_str;                                           \
    for (int i = 0; i < ETH_ADDR_LEN; ++i)                                     \
      sscanf(mac_str_ + i * 3, "%2hhx", &addr_var.data[i]);                    \
    addr_var;                                                                  \
  })

#define PRINT_MAC_ADDR(addr)                                                   \
  printf(MAC_ADDR_STRING_FORMAT "\n", (addr).data[0], (addr).data[1],          \
         (addr).data[2], (addr).data[3], (addr).data[4], (addr).data[5])
	 
__BEGIN_DECLS

u8 *eth_build(eth_addr_t src, eth_addr_t dst, u16 type, const char *data,
              u16 datalen, u32 *pktlen);
eth_t   *eth_open_cached(const char *device);
void     eth_close_cached(void);
eth_t   *eth_open(const char *device);
ssize_t  eth_send(eth_t *e, const void *buf, size_t len);
eth_t   *eth_close(eth_t *e);

__END_DECLS

#endif
