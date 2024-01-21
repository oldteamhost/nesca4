/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void add_http_header(struct http_request *r, const char *field,
    const char *value)
{
  struct _http_header *newhdr, *current;
  newhdr = (struct _http_header *)malloc(sizeof(struct _http_header));
  init_http_header(newhdr, field, value);

  if (!r->hdr)
    r->hdr = newhdr;
  else {
    current = r->hdr;
    while (current->nxt) {
      current = current->nxt;
    }
    current->nxt = newhdr;
  }
}
