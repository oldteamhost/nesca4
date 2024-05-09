/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * Copyright (c) [2000] Dug Song <dugsong@monkey.org>
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/eth.h"

ssize_t eth_send(eth_t *e, const void *buf, size_t len)
{
  struct eth_hdr *eth;

  eth = (struct eth_hdr*)buf;
  e->sll.sll_protocol = eth->type;

  return (sendto(e->fd, buf, len, 0,
        (struct sockaddr*)&e->sll, sizeof(e->sll)));
}
