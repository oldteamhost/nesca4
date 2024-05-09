/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void http_free_req(struct http_request *r)
{
  http_free_uri(&r->uri);
  http_free_hdr(r->hdr);
}

