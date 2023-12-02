/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/dns.h"

int dns_or_ip(const char* node)
{
  struct sockaddr_in sa;
  return (inet_pton(AF_INET, node, &(sa.sin_addr)) == 1);
}
