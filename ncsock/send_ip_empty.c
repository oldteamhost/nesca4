/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"
#include "include/mt19937.h"
#include "include/utils.h"
#include <netinet/in.h>

int send_ip_empty(int sock, u32 saddr, u32 daddr, u16 ttl, u8 proto, bool df, const u8 *ipopt, int ipoptlen,
    const char* data, u16 datalen, int fragscan)
{
  struct sockaddr_in dst_in;
  u32 packetlen;
  int res = -1;
  u8 *packet;

  packet = build_ip_pkt(saddr, daddr, proto, ttl, random_u16(), 5, df,
      ipopt, ipoptlen, data, datalen, &packetlen);
  if (!packet)
    return -1;

  memset(&dst_in, 0, sizeof(struct sockaddr_in));
  dst_in.sin_addr.s_addr = daddr;
  dst_in.sin_port = 0;
  dst_in.sin_family = AF_INET;

  res = send_ip4_packet(NULL, sock, &dst_in, fragscan, packet, packetlen);

  free(packet);
  return res;
}

