/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int ip6_send(struct ethtmp *eth, int fd, const struct sockaddr_in6 *dst,
             const u8 *pkt, u32 pktlen)
{
  return (IP6_SEND_ETH_OR_SD(fd, eth, (struct sockaddr*)dst, pkt, pktlen));
}
