/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"

extern u16 ip6_pseudoheader_check(const struct in6_addr *saddr, const struct in6_addr *daddr, u8 nxt, u32 len, const void *hstart);

extern u8 *build_ip6_pkt(const struct in6_addr *source, const struct in6_addr *victim, u8 tc, u32 flowlabel,
    u8 nexthdr, int hoplimit, const char *data, u16 datalen, u32 *plen);

u8 *build_tcp6_pkt(const struct in6_addr *source, const struct in6_addr *victim, u8 tc, u32 flowlabel,
    u8 hoplimit, u16 sport, u16 dport, u32 seq, u32 ack, u8 reserved, u8 flags, u16 window, u16 urp,
    const u8 *tcpopt, int tcpoptlen, const char *data, u16 datalen, u32 *packetlen, bool badsum)
{
  struct tcp_header *tcp;
  u32 tcplen;
  u8 *packet;

  tcp = (struct tcp_header*) build_tcp(sport, dport, seq, ack, reserved, flags, window, urp, tcpopt, tcpoptlen, data, datalen, &tcplen);
  tcp->th_sum = ip6_pseudoheader_check(source, victim, IPPROTO_TCP, tcplen, tcp);
  if (badsum)
    --tcp->th_sum;
  packet = build_ip6_pkt(source, victim, tc, flowlabel, IPPROTO_TCP, hoplimit, (char *) tcp, tcplen, packetlen);

  free(tcp);
  return packet;
}
