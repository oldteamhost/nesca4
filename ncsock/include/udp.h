/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef UDP_HEADER
#define UDP_HEADER

#include "types.h"
#include <stdbool.h>
#include "../libdnet/include/ip6.h"
#include "../libdnet/include/eth.h"
#include "../libdnet/include/ip.h"
#include <netdb.h>
#include <netinet/in.h>
#include <sys/cdefs.h>

#define UDP_HDR_LEN 8

__BEGIN_DECLS

struct udp_header
{
  u16 uh_sport; /* source port */
  u16 uh_dport; /* destination port */
  u16 ulen;     /* udp length (including header) */
  u16 check;    /* udp checksum */
};

u8 *build_udp(u16 sport, u16 dport, const char *data, u16 datalen, u32 *packetlen);

u8 *build_udp_pkt(const u32 saddr, const u32 daddr,
    int ttl, u16 ipid, u8 tos, bool df, u8 *ipopt, int ipoptlen, u16 sport, u16 dport,
    const char *data, u16 datalen, u32 *plen, bool badsum);

u8 *build_udp6_pkt(const struct in6_addr *source, const struct in6_addr *victim, u8 tc,
    u32 flowlabel, u8 hoplimit, u16 sport, u16 dport, const char *data, u16 datalen,
    u32 *plen, bool badsum);

int send_udp_packet(int fd, const u32 saddr, const u32 daddr, int ttl, u16 ipid,
  u8 *ipopt, int ipoptlen, u16 sport, u16 dport, bool df, const char *data, u16 datalen,
  int fragscan, bool badsum);

__END_DECLS

#endif
