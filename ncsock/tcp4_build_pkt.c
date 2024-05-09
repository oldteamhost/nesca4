/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"
#include "include/tcp.h"

u8 *tcp4_build_pkt(u32 src, u32 dst, u8 ttl, u16 id, u8 tos, bool df,
                   const u8 *ipopt, int ipoptlen, u16 srcport, u16 dstport,
                   u32 seq, u32 ack, u8 reserved, u8 flags, u16 win, u16 urp,
                   const u8 *opt, int optlen, const char *data, u16 datalen,
                   u32 *pktlen, bool badsum)
{
  struct tcp_hdr *tcp;
  u32 tcplen;
  u8 *pkt;

  tcp = (struct tcp_hdr*)tcp_build(srcport, dstport, seq, ack, reserved, flags, win, urp,
      opt, optlen, data, datalen, &tcplen);
  tcp->th_sum = ip4_pseudocheck(src, dst, IPPROTO_TCP, tcplen, tcp);
  if (badsum)
    --tcp->th_sum;

  pkt = ip4_build(src, dst, IPPROTO_TCP, ttl, id, tos, df, ipopt, ipoptlen,
      (char*)tcp, tcplen, pktlen);

  free(tcp);
  return pkt;
}
