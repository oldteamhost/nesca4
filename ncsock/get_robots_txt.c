/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

int get_robots_txt(const char* ip, const int port, const int timeout_ms)
{
  int res, code;
  char* buf = NULL;
  struct http_header hh;

  hh.user_agent = "ncsock";
  hh.content_len = 0;
  hh.content_type = "";
  hh.method = "GET";
  hh.path = "/robots.txt";
  hh.dest_host = ip;
  hh.auth_header = "";

  /* it is not necessary to allocate memory for this function,
   * but it is better to do it when getting the whole page into
   * the buffer */
  buf = (char*)malloc(4096);
  if (!buf)
    return -1;

  res = send_http_request(ip, port, timeout_ms, &hh, buf, 4096);
  if (res == -1)
    goto fail;

  code = parse_http_response_code(buf);
  if (code == 200)
    goto ok;

  goto fail;
fail:
  free(buf);
  return -1;
ok:
  free(buf);
  return 0;
}
