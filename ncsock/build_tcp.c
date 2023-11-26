/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"

u8 *build_tcp(u16 sport, u16 dport, u32 seq, u32 ack, u8 reserved, u8 flags,
    u16 window, u16 urp, const u8 *tcpopt, int tcpoptlen, const char *data, u16 datalen, u32 *packetlen)
{
  struct tcp_header *tcp;
  u8 *packet;

  *packetlen = sizeof(*tcp) + tcpoptlen + datalen;
  packet = (u8 *) malloc(*packetlen);
  tcp = (struct tcp_header *) packet;

  memset(tcp, 0, sizeof(*tcp));
  tcp->th_sport = htons(sport);
  tcp->th_dport = htons(dport);

  if (seq)
    tcp->th_seq = htonl(seq);
  else if (flags & TH_SYN)
    seq = generate_random_u32(299, 3993943);

  if (ack)
    tcp->th_ack = htonl(ack);

  if (reserved)
    tcp->th_x2 = reserved & 0x0F;

  tcp->th_off = 5 + (tcpoptlen / 4);
  tcp->th_flags = flags;

  if (window)
    tcp->th_win = htons(window);
  else
    tcp->th_win = htons(1024);

  if (urp)
    tcp->th_urp = htons(urp);

  if (tcpoptlen)
    memcpy(packet + sizeof(*tcp), tcpopt, tcpoptlen);

  if (data && datalen)
    memcpy(packet + sizeof(*tcp) + tcpoptlen, data, datalen);

  tcp->th_sum = 0;

  return packet;
}
