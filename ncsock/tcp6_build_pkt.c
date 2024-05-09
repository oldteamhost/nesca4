/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"
#include "include/ip.h"

u8 *tcp6_build_pkt(const struct in6_addr *src, const struct in6_addr *dst,
                   u8 tc, u32 flowlabel, u8 hoplimit, u16 srcport, u16 dstport,
                   u32 seq, u32 ack, u8 reserved, u8 flags, u16 win, u16 urp,
                   const u8 *opt, int optlen, const char *data, u16 datalen,
                   u32 *pktlen, bool badsum)
{
  struct tcp_hdr *tcp;
  u32 tcplen;
  u8 *pkt;

  tcp = (struct tcp_hdr*)tcp_build(srcport, dstport, seq, ack, reserved, flags, win, urp,
      opt, optlen, data, datalen, &tcplen);
  tcp->th_sum = ip6_pseudocheck(src, dst, IPPROTO_TCP, tcplen, tcp);
  if (badsum)
    --tcp->th_sum;

  pkt = ip6_build(src, dst, tc, flowlabel, IPPROTO_TCP, hoplimit,
      (char*)tcp, tcplen, pktlen);

  free(tcp);
  return pkt;
}
