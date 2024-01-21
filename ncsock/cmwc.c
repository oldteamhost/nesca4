/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/cmwc.h"

static u64 Q[4096], c = 362436;
void cmwc_seed(u64 seed)
{
  int i;
  
  Q[0] = seed;
  Q[1] = seed + PHI;
  Q[2] = seed + PHI + PHI;
  
  for (i = 3; i < 4096; i++)
    Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
}

u64 cmwc_random(void)
{
  u64 x, r = 0xfffffffe;
  u64 t, a = 18782LL;
  static u64 i = 4095;
  
  i = (i + 1) & 4095;
  t = a * Q[i] + c;
  c = (t >> 32);
  x = t + c;
  
  if (x < c) {
    x++;
    c++;
  }
  
  return (Q[i] = r - x);
}
