/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/igmp.h"

int send_igmp_packet(int fd, const u32 saddr, const u32 daddr, int ttl, bool df, u8 *ipops, int ipoptlen,
    u16 ident, u8 tos, u8 type, u8 code, const char *data, u16 datalen, int fragscan)
{
  struct sockaddr_storage dst;
  struct sockaddr_in *dst_in;
  u32 packetlen;
  int res = -1;

  u8 *packet = build_igmp_pkt(saddr, daddr, ttl, ident, tos, df, ipops, ipoptlen,
      type, code, data, datalen, &packetlen);

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
