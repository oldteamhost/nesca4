/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/icmp.h"
#include "include/ip.h"
#include "libdnet/include/icmp.h"
#include <stdlib.h>

u8 *build_icmp6_pkt(const struct in6_addr *saddr, const struct in6_addr *daddr, u8 tc, u32 flowlabel,
    u8 hoplimit, u16 seq, u16 id, u8 ptype, u8 pcode, const char *data, u16 datalen, u32 *plen)
{
  char *packet;
  struct icmp6_header *icmpv6;
  union icmpv6_msg *msg;
  unsigned int icmplen;
  u8 *ipv6;

  packet = (char *) malloc(sizeof(*icmpv6) + sizeof(*msg) + datalen);
  icmpv6 = (struct icmp6_header *) packet;
  msg = (union icmpv6_msg *) (packet + sizeof(*icmpv6));

  icmplen = sizeof(*icmpv6);
  icmpv6->type = ptype;
  icmpv6->code = pcode;

#define ICMP6_ECHO 128
  if (ptype == ICMP6_ECHO) {
    msg->echo.icmpv6_seq = htons(seq);
    msg->echo.icmpv6_id = htons(id);
    icmplen += sizeof(msg->echo);
  }

  memcpy(packet + icmplen, data, datalen);
  icmplen += datalen;

  icmpv6->checksum = 0;
  icmpv6->checksum = ip6_pseudoheader_check(saddr, daddr, IPPROTO_ICMPV6, icmplen, icmpv6);

  ipv6 = build_ip6_pkt(saddr, daddr, tc, flowlabel, IPPROTO_ICMPV6, hoplimit,
                        packet, icmplen, plen);

  free(packet);
  return ipv6;
}
