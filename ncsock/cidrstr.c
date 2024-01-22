/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "include/utils.h"

char *cidrstr(int v, u8 *ip, u8 *mask, char *to)
{
  int n;
  
  n = strlen(ipstr(v, ip, to));
  sprintf(to+n, "/%d", maskcnum(mask));
  
  return to;
}
