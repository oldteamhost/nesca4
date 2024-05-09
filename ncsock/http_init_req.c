/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void http_init_req(struct http_request *r, const char *method,
                       const char *scheme, const char *host, u8 port,
                       const char *path, u64 contentlen, u64 trasflen)
{
  strncpy(r->method, method, sizeof(r->method) - 1);
  r->method[sizeof(r->method) - 1] = '\0';

  http_init_uri(&r->uri, scheme, host, port, path);

  r->contentlen = contentlen;
  r->transflen = trasflen;
  r->hdr = NULL;
}
