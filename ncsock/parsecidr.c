/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "include/utils.h"

int parsecidr(char *cidr, u8 *ip, u8 *mask)
{
  char *p;
  int v;
  
  p = strchr(cidr, '/');
  v = parseip(cidr, ip);
  if (v == -1) return -1;
  
  if (parsecmask(v, p+1, mask) == -1)
    return -1;
  
  return v;
}
