/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int ip4_send_frag(int fd, const struct sockaddr_in *dst, const u8 *pkt,
                  u32 pktlen, u32 mtu)
{
  int fdatalen = 0, res = 0, fragment = 0, headerlen;
  struct ip4_hdr *ip;
  u32 datalen;
  u8 *fpkt;

  ip = (struct ip4_hdr*)pkt;
  headerlen = ip->ihl* 4;
  datalen = pktlen - headerlen;

  assert(headerlen <= (int)pktlen);
  assert(headerlen >= 20 && headerlen <= 60); /* sanity check (RFC791) */
  assert(mtu > 0 && mtu % 8 == 0);

  if (datalen <= mtu)
    return ip4_send_raw(fd, dst, pkt, pktlen);

  fpkt = (u8*)malloc(headerlen + mtu);
  memcpy(fpkt, pkt, headerlen + mtu);
  ip = (struct ip4_hdr*)fpkt;

  for (fragment = 1; fragment * mtu < datalen + mtu; fragment++) {
    fdatalen = (fragment * mtu <= datalen ? mtu : datalen % mtu);
    ip->totlen = htons(headerlen + fdatalen);
    ip->off = htons((fragment - 1) * mtu / 8);
    if ((fragment - 1) * mtu + fdatalen < datalen)
      ip->off |= htons(IP4_MF);
    ip->check = 0;
    ip->check = in_check((u16*) ip, headerlen);
    if (fragment > 1)
      memcpy(fpkt + headerlen, pkt + headerlen + (fragment - 1) * mtu, fdatalen);
    res = ip4_send_raw(fd, dst, fpkt, ntohs(ip->totlen));
    if (res == -1)
      break;
  }

  free(fpkt);
  return res;
}
