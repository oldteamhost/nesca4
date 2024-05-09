/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"
#include "include/sctp.h"

static unsigned long update_adler32(unsigned long adler, u8 *buf, int len)
{
#define ADLER32_BASE 65521
  unsigned long s1, s2;
  int n;

  s1 = adler & 0xffff;
  s2 = (adler >> 16) & 0xffff;

  for (n = 0; n < len; n++) {
    s1 = (s1 + buf[n]) % ADLER32_BASE;
    s2 = (s2 + s1)% ADLER32_BASE;
  }

  return ((s2 << 16) + s1);
}

static unsigned long adler32(u8 *buf, int len) {
  return (update_adler32(1L, buf, len));
}

u8 *sctp_build(u16 srcport, u16 dstport, u32 vtag, const char *chunks,
               int chunkslen, const char *data, u16 datalen, u32 *pktlen,
               bool adler32sum, bool badsum)
{
  struct sctp_hdr *sctp;
  u8 *pkt;

  *pktlen = sizeof(*sctp) + chunkslen + datalen;
  pkt = (u8*)malloc(*pktlen);
  sctp = (struct sctp_hdr*)pkt;

  memset(sctp, 0, sizeof(*sctp));
  sctp->srcport = htons(srcport);
  sctp->dstport = htons(dstport);
  sctp->vtag  = htonl(vtag);
  sctp->check = 0;

  if (chunks)
    memcpy(pkt + sizeof(*sctp), chunks, chunkslen);
  if (data)
    memcpy(pkt + sizeof(*sctp) + chunkslen, data, datalen);

  /* RFC 2960 originally defined Adler32 checksums, which was later
   * revised to CRC32C in RFC 3309 and RFC 4960 respectively.
   * Nmap uses CRC32C by default, unless --adler32 is given. */
  if (adler32sum)
    sctp->check = htonl(adler32(pkt, *pktlen));
  else
    sctp->check = htonl(__crc32c(pkt, *pktlen));

  if (badsum)
    --sctp->check;

  return pkt;
}
