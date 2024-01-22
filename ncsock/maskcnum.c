/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "include/utils.h"

u8 maskcnum(u8 *from)
{
  u8 i, n;
  u8 x;

  for (n = i = 0; from[i] == 0xFF; i++)
    n+= 8;
  for (x = from[i]; (x & 0x80) == 0x80; x <<= 1)
    n++;
  
  return n;
}
