/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void http_print_req(struct http_request *r)
{
  puts("request:");
  printf("method: %s\n", r->method);
  printf("contentlen: %lu\n", r->contentlen);
  printf("transflen: %lu\n", r->transflen);
  putchar('\n');
  puts("uri:");
  http_print_uri(&r->uri);
  putchar('\n');
  puts("headers:");
  http_print_hdr(r->hdr);
}
