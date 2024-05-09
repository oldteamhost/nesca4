/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/sctp.h"
#include "include/ip.h"

u8 *sctp6_build_pkt(const struct in6_addr *src, const struct in6_addr *dst,
                    u8 tc, u32 flowlabel, u8 hoplimit, u16 srcport, u16 dstport,
                    u32 vtag, char *chunks, int chunkslen, const char *data,
                    u16 datalen, u32 *pktlen, bool adler32sum, bool badsum)
{
  u8 *pkt, *sctp;
  u32 sctplen;

  sctp = sctp_build(srcport, dstport, vtag, chunks, chunkslen, data, datalen,
      &sctplen, adler32sum, badsum);
  pkt = ip6_build(src, dst, tc, flowlabel, IPPROTO_SCTP,
      hoplimit, (char*)sctp, sctplen, pktlen);

  free(sctp);
  return pkt;
}
