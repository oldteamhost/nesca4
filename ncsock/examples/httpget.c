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

  init_http_request(&r, "GET", "", "", 0, "/", 0, 0);
  add_http_header(&r, "Connection", "close");
  add_http_header(&r, "Host", argv[1]);
  add_http_header(&r, "User-Agent", argv[3]);

  fd = session(argv[1], atoi(argv[2]), 2000, NULL, 0);
  if (fd == -1)
    return -1;

  send_http_packet(fd, &r);
  recv_http_packet(fd, &res, response, CMD_BUFFER);
  printf("%s\n", response);

  free_http_request(&r);
  close(fd);
}

