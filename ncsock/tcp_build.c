/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"

  u8 *tcp_build(u16 srcport, u16 dstport, u32 seq, u32 ack, u8 reserved, u8 flags,
              u16 win, u16 urp, const u8 *opt, int optlen, const char *data,
              u16 datalen, u32 *pktlen)
{
  struct tcp_hdr *tcp;
  u8 *pkt;

  *pktlen = sizeof(*tcp) + optlen + datalen;
  pkt = (u8*)malloc(*pktlen);
  if (!pkt)
    return NULL;
  tcp = (struct tcp_hdr*)pkt;

  memset(tcp, 0, sizeof(*tcp));
  tcp->th_sport = htons(srcport);
  tcp->th_dport = htons(dstport);
  tcp->th_off   = 5 + (optlen / 4);
  tcp->th_flags = flags;

  if (seq)
    tcp->th_seq = htonl(seq);

  if (ack)
    tcp->th_ack = htonl(ack);

  if (reserved)
    tcp->th_x2 = reserved & 0x0F;

  if (win)
    tcp->th_win = htons(win);
  else
    tcp->th_win = htons(1024);

  if (urp)
    tcp->th_urp = htons(urp);

  if (optlen)
    memcpy(pkt + sizeof(*tcp), opt, optlen);
  if (data && datalen)
    memcpy(pkt + sizeof(*tcp) + optlen, data, datalen);

  tcp->th_sum = 0;
  return pkt;
}
