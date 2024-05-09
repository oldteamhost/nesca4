/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * Copyright (c) [2000] Dug Song <dugsong@monkey.org>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "include/ip.h"
#include "include/utils.h"

int getipv4(const char *node, char *res, u8 reslen)
{
  const char *tres;
  char tbuf[16];
  char *turl;
  int is;
  
  is = this_is(node);

  if (is == IPv4) {
    tres = node;
    goto write;
  }
  else if (is == DNS) {
    if (ip4_util_strdst(node, tbuf, 16) != -1) {
      tres = tbuf;
      goto write;
    }
    goto fail;
  }
  else if (is == _URL_) {
    turl = clean_url(node);
    if (!turl)
      goto fail;
    if (ip4_util_strdst(turl, tbuf, 16) != -1) {
      tres = tbuf;
      goto write;
    }
    free(turl);
  }
  
 fail:
  return -1;
  
 write:
  strncpy(res, tres, reslen - 1);
  res[reslen - 1] = '\0';
  return 0;
}

