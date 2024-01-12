/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int send_frag_ip_packet(int fd, const struct sockaddr_in *dst, const u8 *packet, u32 plen, u32 mtu)
{
  int fdatalen = 0, res = 0, fragment = 0;
  struct ip_header *ip;
  int headerlen;
  u32 datalen;
  u8 *fpacket;

  ip = (struct ip_header*)packet;
  headerlen = ip->ihl* 4;
  datalen = plen - headerlen;

  assert(headerlen <= (int)plen);
  /* sanity check (RFC791) */
  assert(headerlen >= 20 && headerlen <= 60);
  assert(mtu > 0 && mtu % 8 == 0);

  if (datalen <= mtu)
    return send_ip_raw(fd, dst, packet, plen);

  fpacket = (u8*)malloc(headerlen + mtu);
  memcpy(fpacket, packet, headerlen + mtu);
  ip = (struct ip_header*)fpacket;

  for (fragment = 1; fragment * mtu < datalen + mtu; fragment++) {
    fdatalen = (fragment * mtu <= datalen ? mtu : datalen % mtu);
    ip->tot_len = htons(headerlen + fdatalen);
    ip->frag_off = htons((fragment - 1) * mtu / 8);
    if ((fragment - 1) * mtu + fdatalen < datalen)
      ip->frag_off |= htons(IP_MF);
    ip->check = 0;
    ip->check = in_cksum((u16*) ip, headerlen);
    if (fragment > 1)
      memcpy(fpacket + headerlen, packet + headerlen + (fragment - 1) * mtu, fdatalen);
    res = send_ip_raw(fd, dst, fpacket, ntohs(ip->tot_len));
    if (res == -1)
      break;
  }

  free(fpacket);
  return res;
}
