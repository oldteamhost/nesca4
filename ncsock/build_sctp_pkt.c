/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/sctp.h"
#include "include/ip.h"

u8 *build_sctp_pkt(u32 saddr, u32 daddr, int ttl, u16 ipid, u8 tos,
    bool df, u8 *ipopt, int ipoptlen, u16 sport, u16 dport, u32 vtag,
    char *chunks, int chunkslen, const char *data, u16 datalen,
    u32 *packetlen, bool adler32sum, bool badsum)
{
  u8 *packet, *sctp;
  u32 sctplen;

  sctp = build_sctp(sport, dport, vtag, chunks, chunkslen, data, datalen, &sctplen, adler32sum, badsum);
  packet = build_ip_pkt(saddr, daddr, IPPROTO_SCTP, ttl, ipid, tos, df,
      ipopt, ipoptlen, (char*)sctp, sctplen, packetlen);

  free(sctp);
  return packet;
}
