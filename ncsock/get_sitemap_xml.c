/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

int get_sitemap_xml(const char* ip, const int port, const int timeout_ms)
{
  struct http_response r;
  u8 temp[65535];

  if (sendfast_http_request(ip, port, "/sitemap.xml", timeout_ms, &r, temp, sizeof(temp)) == -1)
    return -1;
  if (r.code == 200)
    return 0;
  return -1;
}
