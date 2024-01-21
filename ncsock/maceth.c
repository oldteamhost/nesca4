/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"
#include <stdio.h>

void maceth(const char* mac, eth_addr_t *eth)
{
  char hexbyte[3];
  int i = 0 ;

  if (!mac || !eth)
    return;

  hexbyte[2] = '\0';
  for (i = 0; i < ETH_ADDR_LEN; ++i) {
    while (*mac && !isxdigit(*mac))
      ++mac;
    strncpy(hexbyte, mac, 2);
    sscanf(hexbyte, "%hhx", &eth->data[i]);
    mac += 2;
  }
}
