/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/dns.h"

void dns_util_getip6(const char* dst, int srcport, char* dnsbuf, size_t buflen)
{
  struct in6_addr addr;
  int sock, res;
  char host[NI_MAXHOST];
  struct timeval timeout;
  struct sockaddr_in6 sa;

  memset(&sa, 0, sizeof(sa));
  sa.sin6_family = AF_INET6;

  timeout.tv_sec = 600;
  timeout.tv_usec = 0;

  if (inet_pton(AF_INET6, dst, &addr) != 1)
    goto fail;

  sa.sin6_addr = addr;
  sa.sin6_port = htons(srcport);

  sock = socket(AF_INET6, SOCK_STREAM, 0);
  if (sock == -1)
    goto fail;

  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  res = getnameinfo((struct sockaddr*)&sa, sizeof(sa), host, sizeof(host), NULL, 0, NI_NAMEREQD);
  close(sock);
  if (res == -1)
    goto fail;
  if (strlen(host) >= buflen)
    goto fail;

  strncpy(dnsbuf, host, buflen);
  dnsbuf[buflen - 1] = '\0';

  return;
fail:
  strncpy(dnsbuf, "n/a", buflen);
  return;
}
