/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/debianfix.h"

u64 _strlcpy(char* dst, const char* src, u64 dlen)
{
  const char *osrc = src;
  u64 nleft = dlen;

  if (nleft != 0) {
    while (--nleft != 0) {
      if ((*dst++ = *src++) == '\0')
        break;
    }
  }
  if (nleft == 0) {
    if (dlen != 0)
      *dst = '\0';
    while (*src++);
  }

  return(src - osrc - 1);
}
