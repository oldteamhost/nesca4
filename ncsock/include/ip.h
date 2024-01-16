/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef IP_HEADER
#define IP_HEADER

#include "types.h"
#include "../include/eth.h"
#include "mt19937.h"
#include "tcp.h"
#include "udp.h"
#include <netdb.h>
#include <netinet/in.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/cdefs.h>
#include <sys/socket.h>
#include "tcp.h"

struct ip_header
{
#define MAX_IHL_LEN 60
  u8  ihl:4;     /* header length */
#define IP_VERSION 4
  u8  version:4; /* ip proto version */
#define DEFAULT_TOS 0
  u8  tos;       /* type of service */
  u16 tot_len;   /* total length */
  u16 ident;     /* identificator */
#define IP_RF 0x8000  /* reserved fragment flag */
#define IP_DF 0x4000  /* dont fragment flag */
#define IP_MF 0x2000  /* more fragments flag */
#define IP_DM 0x1fff  /* mask for fragmenting bits */
#define IP_OFFMASK 0x1fff /* mask for fragment offset */
  u16 frag_off;  /* fragment offset */
#define MAX_TTL 255
#define DEFAULT_TTL 121
  u8  ttl;       /* time to live */
  u8  protocol;  /* see addr.h */
  u16 check;     /* 16 bit checksum */
  u32 saddr;     /* source ip address */
  u32 daddr;     /* dest ip address */
};

#define IP6_ADDR_LEN  16
#define IP6_ADDR_BITS 128
#define IP6_HDR_LEN   40  /* IPv6 header length */
#define IP6_LEN_MAX   65535  /* non-jumbo payload */
#define IP6_LEN_MIN   IP6_HDR_LEN
#define IP6_MTU_MIN   1280  /* minimum MTU (1024 + 256) */

typedef struct ip6_addr {
  u8 data[IP6_ADDR_LEN];
} ip6_addr_t;

#define ip6_vfc  ip6_ctlun.ip6_un2_vfc
#define ip6_flow ip6_ctlun.ip6_un1.ip6_un1_flow
#define ip6_plen ip6_ctlun.ip6_un1.ip6_un1_plen
#define ip6_nxt  ip6_ctlun.ip6_un1.ip6_un1_nxt /* IP_PROTO_* */
#define ip6_hlim ip6_ctlun.ip6_un1.ip6_un1_hlim

#define IP6_ADDR_UNSPEC							\
  "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define IP6_ADDR_LOOPBACK						\
  "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01"

#define IP6_VERSION      0x60
#define IP6_VERSION_MASK 0xf0  /* ip6_vfc version */
#define IP6_HLIM_DEFAULT 64
#define IP6_HLIM_MAX     255

#define ip6_pack_hdr(hdr, fc, fl, plen, nxt, hlim, src, dst) do {	\
    struct ip6_hdr *ip6 = (struct ip6_hdr *)(hdr);			\
    ip6->ip6_flow = htonl(((uint32_t)(fc) << 20) |			\
			  (0x000fffff & (fl)));				\
    ip6->ip6_vfc = (IP6_VERSION | ((fc) >> 4));				\
    ip6->ip6_plen = htons((plen));					\
    ip6->ip6_nxt = (nxt); ip6->ip6_hlim = (hlim);			\
    memmove(&ip6->ip6_src, &(src), IP6_ADDR_LEN);			\
    memmove(&ip6->ip6_dst, &(dst), IP6_ADDR_LEN);			\
  } while (0);

struct ip6_hdr {
  union {
    struct ip6_hdr_ctl {
      u32 ip6_un1_flow; /* 20 bits of flow ID */
      u16 ip6_un1_plen; /* payload length */
      u8 ip6_un1_nxt;   /* next header */
      u8 ip6_un1_hlim;  /* hop limit */
    } ip6_un1;
    u8 ip6_un2_vfc; /* 4 bits version, top 4 bits class */
  } ip6_ctlun;
  ip6_addr_t ip6_src;
  ip6_addr_t ip6_dst;
};

#define _IP_ADDR_LEN        4    /* IP address length */
#define IP_TTL_DEFAULT      64   /* default ttl, RFC 1122, RFC 1340 */
#define IP_TTL_MAX          255  /* maximum ttl */
#define IP_TOS_DEFAULT      0x00 /* default */
#define IP_TOS_LOWDELAY     0x10 /* low delay */
#define IP_TOS_THROUGHPUT   0x08 /* high throughput */
#define IP_TOS_RELIABILITY  0x04 /* high reliability */
#define IP_TOS_LOWCOST      0x02 /* low monetary cost - XXX */
#define IP_TOS_ECT          0x02 /* ECN-capable transport */
#define IP_TOS_CE           0x01 /* congestion experienced */

#define  ip_cksum_carry(x)			\
  (x = (x >> 16) + (x & 0xffff),		\
   (~(x + (x >> 16)) & 0xffff))

typedef struct ip_addreth_addr
{
  u8 data[_IP_ADDR_LEN];
} ip_addreth_t;

__BEGIN_DECLS

int fill_ip_raw(struct ip_header *ip, int packetlen, const u8 *ipopt,
                int ipoptlen, int tos, int id, int off, int ttl, int p,
                u32 saddr, u32 daddr);

u8 *build_ip_pkt(u32 saddr, u32 daddr, u8 proto, int ttl, u16 ipid, u8 tos,
                 bool df, const u8 *ipopt, int ipoptlen, const char *data,
                 u16 datalen, u32 *plen);

u8 *build_ip6_pkt(const struct in6_addr *source, const struct in6_addr *victim,
                  u8 tc, u32 flowlabel, u8 nexthdr, int hoplimit,
                  const char *data, u16 datalen, u32 *plen);

int ip_cksum_add(const void *buf, size_t len, int cksum);
unsigned long _crc32c(u8 *buf, int len);
u16 in_cksum(u16 *ptr, int nbytes);

u16 ip4_pseudoheader_check(u32 saddr, u32 daddr, u8 proto, u16 len,
                           const void *hstart);

u16 ip6_pseudoheader_check(const struct in6_addr *saddr,
                           const struct in6_addr *daddr, u8 nxt, u32 len,
                           const void *hstart);

int send_frag_ip_packet(int fd, const struct sockaddr_in *dst, const u8 *packet,
                        u32 plen, u32 mtu);

int send_ip_raw(int fd, const struct sockaddr_in *dst, const u8 *packet,
                u32 plen);

int send_ip_eth(struct ethtmp *eth, const u8 *packet, u32 plen);
int send_ip6_eth(struct ethtmp *eth, const u8 *packet, u32 plen);

#define SEND_IP_PACKET_ETH_OR_SD(fd, eth, dst, packet, packetlen)	\
  ((eth) ? send_ip_eth((eth), (packet), (packetlen)) :			\
   send_ip_raw((fd), (dst), (packet), (packetlen)))
#define SEND_IP6_PACKET_ETH_OR_SD(fd, eth, dst, packet, packetlen)	\
  ((eth) ? send_ip6_eth((eth), (packet), (packetlen))			\
   : sendto((fd), (packet), (packetlen), 0, (dst), sizeof(*dst)))

int send_ip4_packet(struct ethtmp *eth, int fd, const struct sockaddr_in *dst,
                    int fragscan, const u8 *packet, u32 plen);

int send_ip6_packet(struct ethtmp *eth, int fd, const struct sockaddr_in6 *dst,
                    const u8 *packet, u32 plen);

int send_ip_packet(struct ethtmp *eth, int fd,
                   const struct sockaddr_storage *dst, int fragscan,
                   const u8 *packet, u32 plen);

int send_ip_empty(int sock, u32 saddr, u32 daddr, u16 ttl, u8 proto, bool df,
                  const u8 *ipopt, int ipoptlen, const char *data, u16 datalen,
                  int fragscan);
__END_DECLS

#endif
