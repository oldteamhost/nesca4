/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef ETH_HEADER
#define ETH_HEADER

#include <netinet/in.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/cdefs.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "types.h"
#include "mt19937.h"
#include "../libdnet/include/ip6.h"
#include "../libdnet/include/eth.h"
#include "../libdnet/include/ip.h"
#include <bits/wordsize.h>

__BEGIN_DECLS

struct eth_header
{
  eth_addr_t dst;  /* dest addr */
  eth_addr_t src;  /* source addr */
  u16        type; /* payload type */
};

u8 *build_eth(eth_addr_t saddr, eth_addr_t daddr, u16 type,
    const char* data, u16 datalen, u32 *plen);

__END_DECLS


#endif
