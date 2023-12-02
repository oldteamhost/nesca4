/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/dns.h"

void get_ip(const char* dns, char* ip_buffer, size_t buffer_size)
{
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  struct addrinfo* addrinfo_result;
  int res = getaddrinfo(dns, NULL, &hints, &addrinfo_result);
  if (res != 0) {
    strncpy(ip_buffer, "n/a", buffer_size);
    return;
  }

  struct sockaddr_in* addr = (struct sockaddr_in*)addrinfo_result->ai_addr;
  const char* ip = inet_ntoa(addr->sin_addr);

  strncpy(ip_buffer, ip, buffer_size);
  ip_buffer[buffer_size - 1] = '\0';

  freeaddrinfo(addrinfo_result);
}
