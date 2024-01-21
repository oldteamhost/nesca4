/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include <stdio.h>

#define RECV_MAX_PACKET_LEN_HTTP 655355
bool auth_http_basic(int fd, const char* ip, const char* path,
    const char* user, const char* pass)
{
  u8 packet[RECV_MAX_PACKET_LEN_HTTP];
  struct http_response response;
  struct http_request request;
  int temp = 0;

  init_http_request(&request, "GET", "", "", 0, path, 0, 0);
  add_http_header(&request, "Host", ip);
  add_http_header(&request, "User-Agent", "oldteam");
  add_http_header(&request, "Accept", "*/*");
  add_http_header(&request, "Connection", "close");
  add_http_basicauth(&request, user, pass);

  temp = send_http_packet(fd, &request);
  free_http_request(&request);
  if (temp == -1)
    return false;

  temp = recv_http_packet(fd, &response, packet, RECV_MAX_PACKET_LEN_HTTP);
  if (temp == -1)
    return false;

  if (response.code == 200)
    return true;
  return false;
}
