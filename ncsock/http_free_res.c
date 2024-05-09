/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void http_free_res(struct http_response *r)
{
  if (r->phrase)
    free(r->phrase);
  http_free_hdr(r->hdr);
}
