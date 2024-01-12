/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include "include/socket.h"
#include <unistd.h>

int sendfast_http_request(const char* ip, u16 port, const char* path,
    int timeout_ms, struct http_response *r, u8 *packet, ssize_t len)
{
  struct http_request req;
  u8 temp[4096];
  int fd, a = -1;

  init_http_request(&req, "GET", "", "", 0, path, 0, 0);
  add_http_header(&req, "Host", ip);
  add_http_header(&req, "User-Agent", "oldteam");
  add_http_header(&req, "Connection", "close");

  fd = session(ip, port, timeout_ms, temp, sizeof(temp));
  if (fd == -1)
    return a;
  a = send_http_packet(fd, &req);
  free_http_request(&req);
  if (a == -1) {
    close(fd);
    return a;
  }
  a = recv_http_packet(fd, r, packet, len);

  close(fd);
  return a;
}
