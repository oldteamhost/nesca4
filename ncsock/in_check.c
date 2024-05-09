/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

u16 in_check(u16 *ptr, int nbytes)
{
  int sum;
  sum = ip_check_add(ptr, nbytes, 0);
  return ip_check_carry(sum);
}

