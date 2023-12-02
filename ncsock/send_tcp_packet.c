/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"

extern int send_ip_packet(int fd, const struct sockaddr_storage *dst,
    int fragscan, const u8 *packet, u32 plen);

int send_tcp_packet(int fd, const u32 saddr, const u32 daddr, int ttl, bool df,
    u8 *ipops, int ipoptlen, u16 sport, u16 dport, u32 seq, u32 ack, u8 reserved, u8 flags, u16 window, u16 urp,
    u8 *options, int optlen, const char *data, u16 datalen, int fragscan)
{
  struct sockaddr_storage dst;
  struct sockaddr_in *dst_in;
  u32 packetlen;
  int res = -1;

  u8 *packet = build_tcp_pkt(saddr, daddr, ttl, generate_random_u32(10, 9999), IP_TOS_DEFAULT, df,
    ipops, ipoptlen, sport, dport, seq, ack, reserved, flags, window, urp, options, optlen, data, datalen, &packetlen);

  if (!packet)
    return -1;

  memset(&dst, 0, sizeof(dst));
  dst_in = (struct sockaddr_in *) &dst;
  dst_in->sin_family = AF_INET;
  dst_in->sin_addr.s_addr = daddr;
  res = send_ip_packet(fd, &dst, fragscan, packet, packetlen);

  free(packet);
  return res;
}
