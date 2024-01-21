/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"

void macstr(eth_addr_t *eth, char* mac)
{
  sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
      eth->data[0], eth->data[1], eth->data[2],
      eth->data[3], eth->data[4], eth->data[5]);
}
