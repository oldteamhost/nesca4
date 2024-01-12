/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/udp.h"

u8 *build_udp(u16 sport, u16 dport, const char *data, u16 datalen, u32 *packetlen)
{
  struct udp_header *udp;
  u8 *packet;

  *packetlen = sizeof(*udp) + datalen;
  packet = (u8*)malloc(*packetlen);
  if (!packet)
    return NULL;
  udp = (struct udp_header*)packet;

  memset(udp, 0, sizeof(*udp));
  udp->uh_sport = htons(sport);
  udp->uh_dport = htons(dport);
  udp->ulen     = htons(*packetlen);

  if (data && datalen)
    memcpy(packet + sizeof(*udp), data, datalen);

  udp->check = 0;
  return packet;
}
