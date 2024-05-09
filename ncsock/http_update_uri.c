/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_update_uri(struct uri *u, const char *scheme, const char *host, u16 port,
     const char *path)
{
  if (scheme != NULL && strlen(scheme) > 0) {
    if (u->scheme)
      free(u->scheme);
    u->scheme = strdup(scheme);
  }
  if (host != NULL && strlen(host) > 0) {
    if (u->host)
      free(u->host);
    u->host   = strdup(host);
  }
  if (u->port)
    u->port   = port;
  if (path != NULL && strlen(path) > 0) {
    if (u->path)
      free(u->path);
    u->path   = strdup(path);
  }
}
