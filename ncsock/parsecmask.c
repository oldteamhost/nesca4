/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"
#define min(a, b) ((a) < (b) ? (a) : (b))

int parsecmask(int v, char *from, u8 *to)
{
  u8 m;
  int i;
#include <errno.h>
  errno = 0;
  m = strtoul(from, NULL, 0);
  if (errno != 0)
    return -1;
  
  for (i = 0; i < min(m/8, v); i++)
    to[i] = 0xFF;
  
  to[i] = 0xFF << (8-m%8);
  
  return 0;
}
