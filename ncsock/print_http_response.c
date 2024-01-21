/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void print_http_response(struct http_response *r)
{
  puts("request:");
  printf("code: %d\n", r->code);
  printf("phrase: %s\n", r->phrase);
  printf("contentlen: %lu\n", r->contentlen);
  putchar('\n');
  puts("headers:");
  print_http_header(r->hdr);
}
