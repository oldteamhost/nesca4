/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <signal.h>

int http_send_pkt(int fd, struct http_request *r)
{
  ssize_t packetlen = 0;
  u8 *packet;
  int res;

  packet = http_build_pkt(r, NULL, 0, &packetlen);
  if (!packet)
    return -1;
  res = send(fd, packet, packetlen, MSG_NOSIGNAL);

  free(packet);
  return res;
}
