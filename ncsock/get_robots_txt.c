/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

int get_robots_txt(const char* ip, const int port, const int timeout_ms)
{
#include "include/socket.h"
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
  char* response_buffer = (char*)malloc(CMD_BUFFER);
  if (response_buffer == NULL)
    return -1;

  int result = send_http_request(ip, port, timeout_ms, &hh, response_buffer, CMD_BUFFER);
  if (result == -1) {
    free(response_buffer);
    return -1;
  }

  int code = parse_http_response_code(response_buffer);
  if (code == 200) {
    free(response_buffer);
    return 0;
  }

  free(response_buffer);
  return -1;
}
