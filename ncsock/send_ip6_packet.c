/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"
#include <netinet/in.h>
#include <sys/socket.h>

int send_ip6_packet(struct ethtmp *eth, int fd, const struct sockaddr_in6 *dst, const u8 *packet, u32 plen)
{
  return (SEND_IP6_PACKET_ETH_OR_SD(fd, eth, (struct sockaddr*)dst, packet, plen));
}
