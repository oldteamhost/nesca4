/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void http_print_uri(struct uri *u)
{
  if (u->scheme)
    printf("scheme: %s\n", u->scheme);
  if (u->host)
    printf("host: %s\n", u->host);
  printf("port: %d\n", u->port);
  if (u->path)
    printf("path: %s\n", u->path);
}
