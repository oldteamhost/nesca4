/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include <stdlib.h>

void free_http_response(struct http_response *r)
{
  if (r->phrase)
    free(r->phrase);
  free_http_header(r->hdr);
}
