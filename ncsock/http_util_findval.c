/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

char *http_util_findval(struct _http_header *h, const char* field)
{
  struct _http_header *curhdr;
  curhdr = h;

  while (curhdr) {
    if (strcmp(curhdr->field, field) == 0)
      return curhdr->value;
    curhdr = curhdr->nxt;
  }
  return NULL;
}
