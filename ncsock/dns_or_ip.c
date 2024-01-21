/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/dns.h"

int dns_or_ip(const char* node)
{
  struct sockaddr_in sa4;
  struct sockaddr_in6 sa6;

  if (inet_pton(AF_INET, node, &(sa4.sin_addr)) == 1)
    return AF_INET;
  if (inet_pton(AF_INET6, node, &(sa6.sin6_addr)) == 1)
    return AF_INET6;

  return THIS_IS_DNS;
}
