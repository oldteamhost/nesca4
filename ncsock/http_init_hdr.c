/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void http_init_hdr(struct _http_header *h, const char *field,
                   const char *value)
{
  h->field = strdup(field);
  h->value = strdup(value);
  h->nxt = NULL;
}
