/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include "include/socket.h"
#include <stdio.h>

int sendfast_http_custom(const char* ip, u16 port, int timeout_ms,
    struct http_request *r, struct http_response *res, u8 *packet,
    ssize_t len)
{
  int fd, a;

  fd = session(ip, port, timeout_ms, NULL, 0);
  if (fd == -1)
    return -1;

  a = send_http_packet(fd, r);
  if (a == -1) {
    close(fd);
    return -1;
  }

  a = recv_http_packet(fd, res, packet, len);
  close(fd);
  return a;
}
