/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include <stdio.h>
#include <stdlib.h>

void http_qprc_redirect(struct _http_header *h, u8 *pkt, char *res,
                        ssize_t reslen)
{
  char* tempres = NULL;

  tempres = http_util_findval(h, "Location");
  if (tempres)
    goto write;
  tempres = http_util_findval(h, "Content-Location");
  if (tempres)
    goto write;
  tempres = http_parse_http_equiv((char*)pkt);
  if (tempres)
    goto writefree;
  tempres = http_parse_url_from_js((char*)pkt);
  if (tempres)
    goto writefree;
  tempres = http_parse_parent_location((char*)pkt);
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
