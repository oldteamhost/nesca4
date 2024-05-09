/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/sctp.h"
#include "include/ip.h"

u8 *sctp4_build_pkt(u32 src, u32 dst, int ttl, u16 ipid, u8 tos, bool df,
                    u8 *ipopt, int ipoptlen, u16 srcport, u16 dstport, u32 vtag,
                    char *chunks, int chunkslen, const char *data, u16 datalen,
                    u32 *pktlen, bool adler32sum, bool badsum)
{
  u8 *pkt, *sctp;
  u32 sctplen;

  sctp = sctp_build(srcport, dstport, vtag, chunks, chunkslen, data,
      datalen, &sctplen, adler32sum, badsum);
  pkt = ip4_build(src, dst, IPPROTO_SCTP, ttl, ipid,
      tos, df, ipopt, ipoptlen, (char*)sctp, sctplen, pktlen);

  free(sctp);
  return pkt;
}
