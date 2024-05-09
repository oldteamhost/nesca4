/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"

struct tcp_flags tcp_util_str_setflags(const char *flags)
{
  struct tcp_flags res;
  int i;
  
  memset(&res, 0, sizeof(struct tcp_flags));
  for (i = 0; flags[i] != '\0'; ++i) {
    switch (flags[i])
    {
      case 's':
      case 'S':
        res.syn = 1;
        break;
      case 'a':
      case 'A':
        res.ack = 1;
        break;
      case 'r':
      case 'R':
        res.rst = 1;
        break;
      case 'f':
      case 'F':
        res.fin = 1;
        break;
      case 'p':
      case 'P':
        res.psh = 1;
        break;
      case 'u':
      case 'U':
        res.urg = 1;
        break;
      case 'c':
      case 'C':
        res.cwr = 1;
        break;
      case 'e':
      case 'E':
        res.ece = 1;
        break;
    }
  }
  return res;
}
