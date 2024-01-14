/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/debianfix.h"

size_t _strlcpy(char *dst, const char *src, size_t dlen)
{
#ifdef OLD
  const char *osrc = src;
  u64 nleft = dlen;
  if (nleft != 0)
    while (--nleft != 0)
      if ((*dst++ = *src++) == '\0')
        break;
  if (nleft == 0) {
    if (dlen != 0)
      *dst = '\0';
    while (*src++);
  }
  return(src - osrc - 1);
#endif
  
  register char *d = dst;
  register const char *s = src;
  register size_t n = dlen;

  if (n != 0 && --n != 0) {
    do {
      if ((*d++ = *s++) == 0)
	break;
    } while (--n != 0);
  }
  if (n == 0) {
    if (dlen != 0)
      *d = '\0';
    while (*s++);
  }
  
  return(s - src - 1);	
}
