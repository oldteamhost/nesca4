/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include <stdio.h>

void print_http_request(struct http_request *r)
{
  puts("request:");
  printf("method: %s\n", r->method);
  printf("contentlen: %lu\n", r->contentlen);
  printf("transflen: %lu\n", r->transflen);
  putchar('\n');
  puts("uri:");
  print_uri(&r->uri);
  putchar('\n');
  puts("headers:");
  print_http_header(r->hdr);
}
