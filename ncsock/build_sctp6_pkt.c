/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/sctp.h"
#include "include/ip.h"

u8 *build_sctp6_pkt(const struct in6_addr *source, const struct in6_addr *victim,
    u8 tc, u32 flowlabel, u8 hoplimit, u16 sport, u16 dport,
    u32 vtag, char *chunks, int chunkslen, const char *data,
    u16 datalen, u32 *packetlen, bool adler32sum, bool badsum)
{
  u8 *packet, *sctp;
  u32 sctplen;

  sctp = build_sctp(sport, dport, vtag, chunks, chunkslen, data, datalen,
      &sctplen, adler32sum, badsum);
  packet = build_ip6_pkt(source, victim, tc, flowlabel, IPPROTO_SCTP,
      hoplimit, (char*)sctp, sctplen, packetlen);

  free(sctp);
  return packet;
}
