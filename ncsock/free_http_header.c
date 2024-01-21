/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include <stdio.h>

void free_http_header(struct _http_header *h)
{
  if (!h)
    return;
  if (h->field)
    free(h->field);
  if (h->value)
    free(h->value);
  if (h->nxt)
    free_http_header(h->nxt);
}

