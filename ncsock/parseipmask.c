/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "include/utils.h"

int parseipmask(char *ip, char *mask, u8 *pip, u8 *pmask)
{
  int v, v0;
  
  v  = parseip(ip, pip);
  v0 = parseip(mask, pmask);
  if (v == -1 || v0 == -1 || v != v0)
    return -1;
  
  return v;
}
