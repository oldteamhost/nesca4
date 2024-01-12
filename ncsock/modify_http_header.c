/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void modify_http_header(struct http_request *r, const char *field,
    const char *newvalue)
{
  struct _http_header *curhdr;
  curhdr = r->hdr;
  while (curhdr) {
    if (!strcmp(curhdr->field, field)) {
      free(curhdr->value);
      curhdr->value = strdup(newvalue);
      return;
    }
    curhdr = curhdr->nxt;
  }
  add_http_header(r, field, newvalue);
}
