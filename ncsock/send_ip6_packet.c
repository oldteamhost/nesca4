/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"
#include <sys/socket.h>

int send_ip6_packet(int fd, const struct sockaddr_in6 *dst, const u8 *packet, u32 plen)
{
  return sendto(fd, packet, plen, 0, (struct sockaddr *)dst, sizeof(*dst));
}
