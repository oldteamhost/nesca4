/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

int basic_http_auth(const char* ip, const int port, const int timeout_ms,
      const char* path, const char* user, const char* pass)
{
  struct http_header hh;
  char response_buffer[4096];
  int send, code;

  hh.auth_header = set_basic_auth(user, pass);
  hh.method = "GET";
  hh.path = path;
  hh.dest_host = ip;
  hh.content_len = 0;
  hh.content_type = "";
  hh.user_agent = "ncsock";

  send = send_http_request(ip, port, timeout_ms, &hh, response_buffer, sizeof(response_buffer));
  free(hh.auth_header);
  if (send == -1)
    return -1;
  code = parse_http_response_code(response_buffer);
  if (code != 200)
    return FAILED_AUTH;

  return SUCCESS_AUTH;
}

