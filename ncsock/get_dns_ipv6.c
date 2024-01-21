/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/dns.h"
#include <stdio.h>

void get_dns_ipv6(const char* ip, int port, char* dns_buffer, size_t buffer_size)
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

  if (inet_pton(AF_INET6, ip, &addr) != 1)
    goto fail;

  sa.sin6_addr = addr;
  sa.sin6_port = htons(port);

  sock = socket(AF_INET6, SOCK_STREAM, 0);
  if (sock == -1)
    goto fail;

  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  res = getnameinfo((struct sockaddr*)&sa, sizeof(sa), host, sizeof(host), NULL, 0, NI_NAMEREQD);
  close(sock);
  if (res == -1)
    goto fail;
  if (strlen(host) >= buffer_size)
    goto fail;

  strncpy(dns_buffer, host, buffer_size);
  dns_buffer[buffer_size - 1] = '\0';

  return;
fail:
  strncpy(dns_buffer, "n/a", buffer_size);
  return;
}
