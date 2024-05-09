/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_PACKET_SIZE 65535
u8 *http_build_pkt(struct http_request *request, const char *data,
		     ssize_t datalen, ssize_t *pktlen)
{
  struct _http_header *curhdr = NULL;
  ssize_t offset = 0;
  u8 *packet = NULL;

  packet = (u8 *)malloc(MAX_PACKET_SIZE);
  if (!packet)
    return NULL;
  if (request->uri.scheme && request->uri.scheme[0] != '\0')
    offset = snprintf((char *)packet, MAX_PACKET_SIZE,
      "%s %s://", request->method, request->uri.scheme);
  else
    offset = snprintf((char *)packet, MAX_PACKET_SIZE,
      "%s ", request->method);
  if (request->uri.host && request->uri.host[0] != '\0')
    offset += snprintf((char *)packet + offset, MAX_PACKET_SIZE - offset,
      "%s", request->uri.host);
  if (request->uri.port != 0 &&
    !(request->uri.scheme != NULL && strcmp(request->uri.scheme, "http") == 0 && request->uri.port == 80) &&
    !(request->uri.scheme != NULL && strcmp(request->uri.scheme, "https") == 0 && request->uri.port == 443)) {
    offset += snprintf((char *)packet + offset, MAX_PACKET_SIZE - offset, ":%d", request->uri.port);
  }
  if (request->uri.path)
    offset += snprintf((char *)packet + offset, MAX_PACKET_SIZE - offset,
      "%s HTTP/1.1\r\n", request->uri.path);
  else
    offset += snprintf((char *)packet + offset, MAX_PACKET_SIZE - offset,
      " HTTP/1.1\r\n");
  curhdr = request->hdr;
  while (curhdr) {
    offset += snprintf((char *)packet + offset, MAX_PACKET_SIZE - offset,
      "%s: %s\r\n", curhdr->field, curhdr->value);
    curhdr = curhdr->nxt;
  }
  if (datalen)
    offset += snprintf((char *)packet + offset, MAX_PACKET_SIZE - offset, "Content-Length: %zd\r\n", datalen);
  offset += snprintf((char *)packet + offset, MAX_PACKET_SIZE - offset, "\r\n");
  if (data && datalen) {
    memcpy(packet + offset, data, datalen);
    offset += datalen;
  }

  *pktlen = offset;
  return packet;
}
