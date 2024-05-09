/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/icmp.h"
#include "include/ip.h"

u8 *icmp6_build_pkt(const struct in6_addr *src, const struct in6_addr *dst,
                    u8 tc, u32 flowlabel, u8 hoplimit, u16 seq, u16 id, u8 type,
                    u8 code, const char *data, u16 datalen, u32 *pktlen,
                    bool badsum)
{
  struct icmp6_hdr *icmpv6;
  union icmp6_msg *msg;
  u32 icmplen;
  char *pkt;
  u8 *ipv6;

  pkt = (char*)malloc(sizeof(*icmpv6) + sizeof(*msg) + datalen);
  if (!pkt)
    return NULL;
  icmpv6 = (struct icmp6_hdr*)pkt;
  msg = (union icmp6_msg*)(pkt + sizeof(*icmpv6));

  memset(icmpv6, 0, sizeof(*icmpv6));
  icmplen = sizeof(*icmpv6);
  icmpv6->type = type;
  icmpv6->code = code;

#define ICMP6_ECHO 128
  if (type == ICMP6_ECHO) {
    msg->echo.icmpv6_seq = htons(seq);
    msg->echo.icmpv6_id = htons(id);
    icmplen += sizeof(msg->echo);
  }

  memcpy(pkt + icmplen, data, datalen);
  icmplen += datalen;

  icmpv6->check = 0;
  icmpv6->check = ip6_pseudocheck(src, dst, IPPROTO_ICMPV6,
      icmplen, icmpv6);
  if (badsum)
    icmpv6->check--;

  ipv6 = ip6_build(src, dst, tc, flowlabel, IPPROTO_ICMPV6,
      hoplimit, pkt, icmplen, pktlen);

  free(pkt);
  return ipv6;
}
