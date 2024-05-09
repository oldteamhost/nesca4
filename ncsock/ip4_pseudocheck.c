/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"
#include <netinet/in.h>

u16 ip4_pseudocheck(u32 src, u32 dst, u8 proto, u16 len, const void *hstart)
{
  struct pseudo
  {
    u32 src;
    u32 dst;
    u8 zero;
    u8 proto;
    u16 length;
  } hdr;
  int sum;

  hdr.src    = src;
  hdr.dst    = dst;
  hdr.zero   = 0;
  hdr.proto  = proto;
  hdr.length = htons(len);

  sum = ip_check_add(&hdr, sizeof(hdr), 0);
  sum = ip_check_add(hstart, len, sum);
  sum = ip_check_carry(sum);

  /* RFC 768: "If the computed  checksum  is zero,  it is transmitted  as all
   * ones (the equivalent  in one's complement  arithmetic).   An all zero
   * transmitted checksum  value means that the transmitter  generated  no
   * checksum" */
  if (proto == IPPROTO_UDP && sum == 0)
    sum = 0xFFFF;

  return sum;
}
