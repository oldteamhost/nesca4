/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

#define RECV_MAX_PACKET_LEN_HTTP 655355
bool http_basicauth(int fd, const char *dst, const char *path, const char *user,
		    const char *pass)
{
  u8 packet[RECV_MAX_PACKET_LEN_HTTP];
  struct http_response response;
  struct http_request request;
  int temp = 0;

  http_init_req(&request, "GET", "", "", 0, path, 0, 0);
  http_add_hdr(&request, "Host", dst);
  http_add_hdr(&request, "User-Agent", "oldteam");
  http_add_hdr(&request, "Accept", "*/*");
  http_add_hdr(&request, "Connection", "close");
  http_add_hdr(&request, user, pass);

  temp = http_send_pkt(fd, &request);
  http_free_req(&request);
  if (temp == -1)
    return false;

  temp = http_recv_pkt(fd, &response, packet, RECV_MAX_PACKET_LEN_HTTP);
  if (temp == -1)
    return false;

  if (response.code == 200)
    return true;
  return false;
}
