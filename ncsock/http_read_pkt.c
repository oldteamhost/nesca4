/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

struct http_response http_read_pkt(u8 *response)
{
  u8* packet = NULL;
  struct http_response res;
  struct _http_header *hdr = NULL;
  char *statusline = NULL, *headerline = NULL,
       *value = NULL, *colon = NULL;

  res.hdr = NULL;
  res.code = 0;
  res.contentlen = 0;
  res.phrase = NULL;

  packet = http_remove_html(response);
  if (!packet)
    return res;

  statusline = strtok((char *)packet, "\r\n");
  sscanf(statusline, "HTTP/1.1 %d %ms", &res.code, &res.phrase);

  headerline = strtok(NULL, "\r\n");
  while (headerline && headerline[0] != '\0') {
    if (headerline[0] == '\r' || headerline[0] == '\n')
      break;
    colon = strchr(headerline, ':');
    if (colon) {
      *colon = '\0';
      value = colon + 1;
      while (*value == ' ' || *value == '\t')
        value++;
      struct _http_header *newhdr = (struct _http_header *)malloc(sizeof(struct _http_header));
      newhdr->field = strdup(headerline);
      newhdr->value = strdup(value);
      newhdr->nxt = res.hdr;
      res.hdr = newhdr;
    }
    headerline = strtok(NULL, "\r\n");
  }
  res.contentlen = 0;
  hdr = res.hdr;
  while (hdr) {
    if (strcmp(hdr->field, "Content-Length") == 0) {
      sscanf(hdr->value, "%lu", &res.contentlen);
      break;
    }
    hdr = hdr->nxt;
  }

  if (packet)
    free(packet);
  return res;
}
