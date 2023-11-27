/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/udp.h"

#include <stdlib.h>
#include <string.h>
#include <netdb.h>

extern u16 ip4_pseudoheader_check(u32 saddr, u32 daddr, u8 proto, u16 len, const void *hstart);
extern u8 *build_ip_pkt(u32 saddr, u32 daddr, u8 proto, int ttl,
    u16 ipid, u8 tos, bool df, const u8 *ipopt, int ipoptlen, const char *data, u16 datalen, u32 *plen);

u8 *build_udp(u16 sport, u16 dport, const char *data, u16 datalen, u32 *packetlen)
{
  struct udp_header *udp;
  u8 *packet;

  *packetlen = sizeof(*udp) + datalen;
  packet = (u8 *) malloc(*packetlen);
  if (!packet)
    return NULL;
  udp = (struct udp_header*) packet;

  memset(udp, 0, sizeof(*udp));
  udp->uh_sport = htons(sport);
  udp->uh_dport = htons(dport);

  udp->ulen = htons(*packetlen);
  if (data && datalen)
    memcpy(packet + sizeof(*udp), data, datalen);

  udp->check = 0;

  return packet;
}

u8 *build_udp_pkt(const u32 saddr, const u32 daddr,
    int ttl, u16 ipid, u8 tos, bool df, u8 *ipopt, int ipoptlen, u16 sport, u16 dport,
    const char *data, u16 datalen, u32 *packetlen)
{
  struct udp_header *udp;
  u32 udplen;
  u8 *ip;

  udp = (struct udp_header*) build_udp(sport, dport, data, datalen, &udplen);
  udp->check = ip4_pseudoheader_check(saddr, daddr, IPPROTO_UDP, udplen, udp);
  ip = build_ip_pkt(saddr, daddr, IPPROTO_UDP, ttl, ipid, tos, df, ipopt, ipoptlen, (char *) udp, udplen, packetlen);
  free(udp);

  return ip;
}
