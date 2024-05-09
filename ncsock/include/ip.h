/*
 * LIBNCSOCK & NESCA4
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef IP_HEADER
#define IP_HEADER

#include <netdb.h>
#include <netinet/in.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/cdefs.h>
#include <sys/socket.h>

#include "tcp.h"
#include "types.h"
#include "mt19937.h"
#include "tcp.h"
#include "udp.h"
#include "../include/eth.h"
#ifdef ONLY_COMPILE
# include "../compile.h"
#endif

#define IP_TTL_DEFAULT      64      /* default ttl, RFC 1122, RFC 1340 */
#define IP_TTL_MAX          255     /* maximum ttl */
#define IP_TOS_DEFAULT      0x00    /* default */
#define IP_TOS_LOWDELAY     0x10    /* low delay */
#define IP_TOS_THROUGHPUT   0x08    /* high throughput */
#define IP_TOS_RELIABILITY  0x04    /* high reliability */
#define IP_TOS_LOWCOST      0x02    /* low monetary cost - XXX */
#define IP_TOS_ECT          0x02    /* ECN-capable transport */
#define IP_TOS_CE           0x01    /* congestion experienced */

#define IP4_ADDR_LEN        4       /* IP address length */
#define IP4_RF              0x8000  /* reserved fragment flag */
#define IP4_DF              0x4000  /* dont fragment flag */
#define IP4_MF              0x2000  /* more fragments flag */
#define IP4_DM              0x1fff  /* mask for fragmenting bits */
#define IP4_OFFMASK         0x1fff  /* mask for fragment offset */
#define IP4_IHL_MAX         60
#define IP4_VERSION         4

#define IP6_HDR_LEN         40      /* header length */
#define IP6_LEN_MAX         65535   /* non-jumbo payload */
#define IP6_MTU_MIN         1280    /* minimum MTU (1024 + 256) */
#define IP6_VERSION_MASK    0xf0    /* ip6_vfc version */
#define IP6_NXT             ip6_ctlun.ip6_un1.ip6_un1_nxt
#define IP6_ADDR_LEN        16
#define IP6_ADDR_BITS       128
#define IP6_LEN_MIN         IP6_HDR_LEN
#define IP6_VFC             ip6_ctlun.ip6_un2_vfc
#define IP6_FLOW            ip6_ctlun.ip6_un1.ip6_un1_flow
#define IP6_PKTLEN          ip6_ctlun.ip6_un1.ip6_un1_plen
#define IP6_HLIM            ip6_ctlun.ip6_un1.ip6_un1_hlim
#define IP6_VERSION         0x60

#define IP6_ADDR_UNSPEC                                                        \
  "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define IP6_ADDR_LOOPBACK                                                      \
  "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01"

typedef struct ip6_addr { u8 data[IP6_ADDR_LEN]; } ip6_addr_t;
typedef struct ip4_addreth_addr { u8 data[IP4_ADDR_LEN]; } ip4_addreth_t;

struct ip4_hdr
{
#if (defined(WORDS_BIGENDIAN))
  u8  version:4; /* ip proto version */
  u8  ihl:4;     /* header length */
#else
  u8  ihl:4;     /* header length */
  u8  version:4; /* ip proto version */
#endif
  u8  tos;       /* type of service */
  u16 totlen;    /* total length */
  u16 id;        /* identificator */
  u16 off;       /* fragment offset */
  u8  ttl;       /* time to live */
  u8  proto;     /* see addr.h */
  u16 check;     /* 16 bit checksum */
  u32 src;       /* source ip address */
  u32 dst;       /* dest ip address */
};

struct ip6_hdr
{
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

#define ip6_hdr(hdr, fc, fl, _pktlen, nxt, hlim, _src, _dst)                   \
  do {                                                                         \
    struct ip6_hdr *ip6 = (struct ip6_hdr *)(hdr);                             \
    ip6->IP6_FLOW = htonl(((u32)(fc) << 20) | (0x000fffff & (fl)));            \
    ip6->IP6_VFC = (IP6_VERSION | ((fc) >> 4));                                \
    ip6->IP6_PKTLEN = htons((_pktlen));						\
    ip6->IP6_NXT = (nxt);                                                      \
    ip6->IP6_HLIM = (hlim);                                                    \
    memmove(&ip6->ip6_src, &(_src), IP6_ADDR_LEN);                             \
    memmove(&ip6->ip6_dst, &(_dst), IP6_ADDR_LEN);                             \
  } while (0);

#define IP4_SEND_ETH_OR_SD(fd, eth, dst, pkt, pktlen)                          \
  ((eth) ? ip4_send_eth((eth), (pkt), (pktlen))                                \
         : ip4_send_raw((fd), (dst), (pkt), (pktlen)))
#define IP6_SEND_ETH_OR_SD(fd, eth, dst, pkt, pktlen)                          \
  ((eth) ? ip6_send_eth((eth), (pkt), (pktlen))                                \
         : sendto((fd), (pkt), (pktlen), 0, (dst), sizeof(*dst)))

__BEGIN_DECLS

u8 *ip4_build(u32 src, u32 dst, u8 proto, int ttl, u16 id, u8 tos, bool df,
              const u8 *opt, int optlen, const char *data, u16 datalen,
              u32 *pktlen);
u8 *ip6_build(const struct in6_addr *src, const struct in6_addr *dst, u8 tc,
              u32 flowlabel, u8 nexthdr, int hoplimit, const char *data,
              u16 datalen, u32 *pktlen);
int ip4_hdr(struct ip4_hdr *ip, int pktlen, const u8 *opt, int optlen,
            int tos, int id, int off, int ttl, int proto, u32 src, u32 dst);
int ip4_send(struct ethtmp *eth, int fd, const struct sockaddr_in *dst, int mtu,
             const u8 *pkt, u32 pktlen);
int ip6_send(struct ethtmp *eth, int fd, const struct sockaddr_in6 *dst,
             const u8 *pkt, u32 pktlen);
int ip_send(struct ethtmp *eth, int fd, const struct sockaddr_storage *dst,
            int mtu, const u8 *pkt, u32 pktlen);
int ip4_send_pkt(int fd, u32 src, u32 dst, u16 ttl, u8 proto, bool df,
                 const u8 *opt, int optlen, const char *data, u16 datalen,
                 int mtu); 
int ip4_send_frag(int fd, const struct sockaddr_in *dst, const u8 *pkt,
                  u32 pktlen, u32 mtu);
int ip_check_add(const void *buf, size_t len, int check);
unsigned long __crc32c(u8 *buf, int len);
u16 in_check(u16 *ptr, int nbytes);
#define ip_check_carry(x)                                                      \
  (x = (x >> 16) + (x & 0xffff), (~(x + (x >> 16)) & 0xffff))
u16 ip4_pseudocheck(u32 src, u32 dst, u8 proto, u16 len, const void *hstart);
u16 ip6_pseudocheck(const struct in6_addr *src, const struct in6_addr *dst,
                    u8 nxt, u32 len, const void *hstart);
int ip4_send_raw(int fd, const struct sockaddr_in *dst, const u8 *pkt,
                 u32 pktlen);
int ip4_send_eth(struct ethtmp *eth, const u8 *pkt, u32 pktlen);
int ip6_send_eth(struct ethtmp *eth, const u8 *pkt, u32 pktlen);

__END_DECLS

#endif
