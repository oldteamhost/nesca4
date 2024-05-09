/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void http_free_uri(struct uri *u)
{
  if (!u)
    return;
  if (u->scheme)
    free(u->scheme);
  if (u->host)
    free(u->host);
  if (u->path)
    free(u->path);
}
