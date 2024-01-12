/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void free_http_request(struct http_request *r)
{
  free_uri(&r->uri);
  free_http_header(r->hdr);
}

