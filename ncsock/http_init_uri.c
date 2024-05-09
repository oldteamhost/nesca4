/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void http_init_uri(struct uri *u, const char *scheme, const char *host, u16 port,
              const char *path)
{
  u->scheme = strdup(scheme);
  u->host   = strdup(host);
  u->port   = port;
  u->path   = strdup(path);
}
