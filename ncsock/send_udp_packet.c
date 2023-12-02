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

extern int send_ip_packet(int fd, const struct sockaddr_storage *dst,
    int fragscan, const u8 *packet, u32 plen);

int send_udp_packet(int fd, const u32 saddr, const u32 daddr, int ttl, u16 ipid,
  u8 *ipopt, int ipoptlen, u16 sport, u16 dport, bool df, const char *data, u16 datalen, int fragscan)
{
  struct sockaddr_storage dst;
  struct sockaddr_in *dst_in;
  unsigned int packetlen;
  int res = -1;
  u8 *packet = build_udp_pkt(saddr, daddr, ttl, ipid, IP_TOS_DEFAULT, df, ipopt, ipoptlen, sport, dport, data, datalen, &packetlen);

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
