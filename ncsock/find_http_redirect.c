/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include <stdio.h>
#include <stdlib.h>

void find_http_redirect(struct _http_header *h, u8 *packet,
    char* res, ssize_t reslen)
{
  char* tempres = NULL;

  tempres = find_http_value(h, "Location");
  if (tempres)
    goto write;
  tempres = find_http_value(h, "Content-Location");
  if (tempres)
    goto write;
  tempres = parse_http_equiv((char*)packet);
  if (tempres)
    goto writefree;
  tempres = parse_url_from_js((char*)packet);
  if (tempres)
    goto writefree;
  tempres = parse_parent_location((char*)packet);
  if (tempres)
    goto writefree;

  res[0] = '\0';
  return;

write:
  strncpy(res, tempres, reslen - 1);
  res[reslen - 1] = '\0';
  return;

writefree:
  strncpy(res, tempres, reslen - 1);
  res[reslen - 1] = '\0';
  if (tempres)
    free(tempres);
  return;
}
