/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

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

u8 *build_sctp(u16 sport, u16 dport, u32 vtag, const char *chunks,
    int chunkslen, const char *data, u16 datalen, u32 *packetlen,
    bool adler32sum, bool badsum)
{
  struct sctp_header *sctp;
  u8 *packet;

  *packetlen = sizeof(*sctp) + chunkslen + datalen;
  packet = (u8 *)malloc(*packetlen);
  sctp = (struct sctp_header *)packet;

  sctp->sport = htons(sport);
  sctp->dport = htons(dport);
  sctp->vtag = htonl(vtag);
  sctp->check = 0;

  if (chunks)
    memcpy(packet + sizeof(*sctp), chunks, chunkslen);

  if (data)
    memcpy(packet + sizeof(*sctp) + chunkslen, data, datalen);

  if (adler32sum)
    sctp->check = htonl(adler32(packet, *packetlen));
  else
    sctp->check = htonl(adler32(packet, *packetlen));

  if (badsum)
    --sctp->check;

  return packet;
}
