/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

u8 *build_ip6_pkt(const struct in6_addr *source, const struct in6_addr *victim, u8 tc, u32 flowlabel,
    u8 nexthdr, int hoplimit, const char *data, u16 datalen, u32 *plen)
{
  u8 *packet;

  if (hoplimit == -1)
    hoplimit = generate_random_u32(23, 37);

  *plen= sizeof(struct ip6_hdr) + datalen;
  packet = (u8 *) malloc(*plen);
  if (!packet)
    return NULL;

  ip6_pack_hdr(packet, tc, flowlabel, datalen, nexthdr, hoplimit, *source, *victim);
  memcpy(packet + sizeof(struct ip6_hdr), data, datalen);

  return packet;
}
