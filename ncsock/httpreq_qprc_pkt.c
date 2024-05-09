/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include "include/socket.h"
#include <unistd.h>

int httpreq_qprc_pkt(const char *dst, u16 dstport, const char *path,
		      int timeoutms, struct http_response *r, u8 *buf,
		      ssize_t buflen)
{
  struct http_request req;
  u8 temp[4096];
  int fd, a = -1;

  http_init_req(&req, "GET", "", "", 0, path, 0, 0);
  http_add_hdr(&req, "Host", dst);
  http_add_hdr(&req, "User-Agent", "oldteam");
  http_add_hdr(&req, "Connection", "close");

  fd = session(dst, dstport, timeoutms, temp, sizeof(temp));
  if (fd == -1)
    return a;
  a = http_send_pkt(fd, &req);
  http_free_req(&req);
  if (a == -1) {
    close(fd);
    return a;
  }
  a = http_recv_pkt(fd, r, buf, buflen);

  close(fd);
  return a;
}
