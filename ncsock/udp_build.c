/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/udp.h"

u8 *udp_build(u16 srcport, u16 dstport, const char *data, u16 datalen, u32 *pktlen)
{
  struct udp_hdr *udp;
  u8 *pkt;

  *pktlen = sizeof(*udp) + datalen;
  pkt = (u8*)malloc(*pktlen);
  if (!pkt)
    return NULL;
  udp = (struct udp_hdr*)pkt;

  memset(udp, 0, sizeof(*udp));
  udp->srcport = htons(srcport);
  udp->dstport = htons(dstport);
  udp->len     = htons(*pktlen);

  if (data && datalen)
    memcpy(pkt + sizeof(*udp), data, datalen);

  udp->check = 0;
  return pkt;
}
