/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

u16 ip6_pseudocheck(const struct in6_addr *src, const struct in6_addr *dst,
                    u8 nxt, u32 len, const void *hstart)
{
  struct pseudo
  {
    struct in6_addr src;
    struct in6_addr dst;
    u32 length;
    u8 z0, z1, z2;
    u8 nxt;
  } hdr;
  int sum;

  hdr.src = *src;
  hdr.dst = *dst;
  hdr.z0 = hdr.z1 = hdr.z2 = 0;
  hdr.length = htonl(len);
  hdr.nxt = nxt;

  sum = ip_check_add(&hdr, sizeof(hdr), 0);
  sum = ip_check_add(hstart, len, sum);
  sum = ip_check_carry(sum);

  /* RFC 2460: "Unlike IPv4, when UDP packets are originated by an IPv6 node,
     the UDP checksum is not optional.  That is, whenever originating a UDP
     packet, an IPv6 node must compute a UDP checksum over the packet and the
     pseudo-header, and, if that computation yields a result of zero, it must be
     changed to hex FFFF for placement in the UDP header." */
  if (nxt == IPPROTO_UDP && sum == 0)
    sum = 0xFFFF;

  return sum;
}
