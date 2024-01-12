/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void print_http_header(struct _http_header *h)
{
  if (h->field && h->value)
    printf("field: %s: %s\n", h->field, h->value);
  if (h->nxt)
    print_http_header(h->nxt);
}
