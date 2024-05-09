/*
 * LIBNCSOCK & NESCA4 & HTTPGET
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include <stdnoreturn.h>
#include "../include/http.h"
#include "../include/socket.h"

noreturn void usage(char** argv)
{
  printf("Usage: %s [ip] [port] [user-agent]\n", argv[0]);
  exit(0);
}

int main(int argc, char** argv)
{
  struct http_response res;
  u8 response[CMD_BUFFER];
  struct http_request r;
  int fd;

  if (argc < 3 + 1)
    usage(argv);

  http_init_req(&r, "GET", "", "", 0, "/", 0, 0);
  http_add_hdr(&r, "Connection", "close");
  http_add_hdr(&r, "Host", argv[1]);
  http_add_hdr(&r, "User-Agent", argv[3]);

  fd = session(argv[1], atoi(argv[2]), 2000, NULL, 0);
  if (fd == -1)
    return -1;

  http_send_pkt(fd, &r);
  http_recv_pkt(fd, &res, response, CMD_BUFFER);
  printf("%s\n", response);

  http_free_req(&r);
  close(fd);
}

