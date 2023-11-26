/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"

extern u16 ip4_pseudoheader_check(u32 saddr, u32 daddr, u8 proto, u16 len, const void *hstart);

extern u8 *build_ip_pkt(u32 saddr, u32 daddr, u8 proto, int ttl, u16 ipid,
    u8 tos, bool df, const u8 *ipopt, int ipoptlen, const char *data, u16 datalen, u32 *plen);

u8 *build_tcp_pkt(u32 saddr, u32 daddr, u8 ttl, u16 ipid, u8 tos,
    bool df, const u8 *ipopt, int ipoptlen, u16 sport, u16 dport, u32 seq, u32 ack, u8 reserved, u8 flags, u16 window,
    u16 urp, const u8 *tcpopt, int tcpoptlen, const char *data, u16 datalen, u32 *packetlen)
{
  struct tcp_header *tcp;
  u32 tcplen;
  u8 *ip;

  tcp = (struct tcp_header*)build_tcp(sport, dport, seq, ack, reserved, flags, window, urp, tcpopt, tcpoptlen, data, datalen, &tcplen);
  tcp->th_sum = ip4_pseudoheader_check(saddr, daddr, IPPROTO_TCP, tcplen, tcp);
  ip = build_ip_pkt(saddr, daddr, IPPROTO_TCP, ttl, ipid, tos, df, ipopt, ipoptlen, (char *) tcp, tcplen, packetlen);

  free(tcp);
  return ip;
}
