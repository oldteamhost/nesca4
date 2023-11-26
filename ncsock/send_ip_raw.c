/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int send_ip_raw(int fd, const struct sockaddr_in *dst, const u8 *packet, u32 plen)
{
  int res;
  struct sockaddr_in sock;
  struct ip_header *ip = (struct ip_header*)packet;
  struct tcp_header *tcp;
  struct udp_header *udp;

  assert(fd >= 0);
  sock = *dst;

  if (plen >= 20) {
    if (ip->protocol == IPPROTO_TCP && plen >= (unsigned int) ip->ihl * 4 + 20) {
      tcp = (struct tcp_header*) ((u8 *) ip + ip->ihl * 4);
      sock.sin_port = tcp->th_dport;
    }
    else if (ip->protocol == IPPROTO_UDP && plen >= (unsigned int) ip->ihl  * 4 + 8) {
      udp = (struct udp_header*) ((u8 *) ip + ip->ihl * 4);
      sock.sin_port = udp->uh_dport;
    }
  }

  res = sendto(fd, packet, plen, 0, (struct sockaddr *) &sock, (int) sizeof(struct sockaddr_in));
  return res;
}
