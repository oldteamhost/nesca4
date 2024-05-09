/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

int http_qprc_robots_txt(const char *dst, const int dstport, const int timeoutms)
{
  struct http_response r;
  u8 temp[65535];

  if (httpreq_qprc_pkt(dst, dstport, "/robots.txt", timeoutms, &r, temp, sizeof(temp)) == -1)
    return -1;
  if (r.code == 200)
    return 0;
  return -1;
}
