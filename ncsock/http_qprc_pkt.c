/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include "include/socket.h"

int http_qprc_pkt(const char *dst, u16 dstport, int timeoutms,
                  struct http_request *r, struct http_response *res, u8 *buf,
                  ssize_t buflen)
{
  int fd, a;

  fd = session(dst, dstport, timeoutms, NULL, 0);
  if (fd == -1)
    return -1;

  a = http_send_pkt(fd, r);
  if (a == -1) {
    close(fd);
    return -1;
  }

  a = http_recv_pkt(fd, res, buf, buflen);
  close(fd);
  return a;
}
