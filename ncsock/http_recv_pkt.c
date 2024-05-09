/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

int http_recv_pkt(int fd, struct http_response *r, u8 *packet,
		  ssize_t packetlen)
{
  size_t reslen = 0, received;

  while ((received = recv(fd, packet + reslen, packetlen - reslen - 1, 0)) != -1 && received != 0) {
    reslen += received;
    if (reslen >= packetlen - 1)
      break;
  }
  packet[reslen] = '\0';
  if (strlen((char*)packet) > 0)
    *r = http_read_pkt(packet);

  return received;
}
