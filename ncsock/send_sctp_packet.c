/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/sctp.h"
#include "include/ip.h"
#include "include/utils.h"

int send_sctp_packet(struct ethtmp *eth, int fd, const u32 saddr, const u32 daddr, int ttl, bool df,
		     u8 *ipops, int ipoptlen, u16 sport, u16 dport, char *chunks, int chunkslen, u32 vtag,
		     const char *data, u16 datalen, int fragscan, bool adler32sum, bool badsum)
{
  struct sockaddr_storage dst;
  struct sockaddr_in *dst_in;
  u32 packetlen;
  int res = -1;
  u8 *packet;

  packet = build_sctp_pkt(saddr, daddr, ttl, random_u16(),
      0, df, ipops, ipoptlen, sport, dport, vtag, chunks,
      chunkslen, data, datalen, &packetlen,
      adler32sum, badsum);
  if (!packet)
    return -1;

  memset(&dst, 0, sizeof(dst));
  dst_in = (struct sockaddr_in*)&dst;
  dst_in->sin_family = AF_INET;
  dst_in->sin_addr.s_addr = daddr;
  res = send_ip_packet(eth, fd, &dst, fragscan, packet, packetlen);

  free(packet);
  return res;
}

