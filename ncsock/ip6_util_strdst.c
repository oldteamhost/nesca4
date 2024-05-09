/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int ip6_util_strdst(const char* dns, char* ipbuf, size_t buflen)
{
  struct addrinfo hints;
  struct addrinfo* addrinfo_result;
  struct sockaddr_in6* addr;
  const char* ip;
  int res;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;

  res = getaddrinfo(dns, NULL, &hints, &addrinfo_result);
  if (res != 0) {
    strncpy(ipbuf, "n/a", buflen);
    return -1;
  }
  addr = (struct sockaddr_in6*)addrinfo_result->ai_addr;
  ip = inet_ntop(AF_INET6, &(addr->sin6_addr), ipbuf, buflen);
  if (ip == NULL) {
    strncpy(ipbuf, "n/a", buflen);
    freeaddrinfo(addrinfo_result);
    return -1;
  }

  freeaddrinfo(addrinfo_result);
  return 0;
}

