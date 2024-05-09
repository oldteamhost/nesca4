/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/mt19937.h"

static u32 mt[MT19937_N];
static int mti = MT19937_N + 1;

void mt19937_seed(u32 seed)
{
  mt[0] = seed;
  for (mti = 1; mti < MT19937_N; mti++) {
    mt[mti] = 1812433253 * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti;
  }
  return;
}

u32 mt19937_random(void)
{
  int i;
  if (mti >= MT19937_N) {
    for (i = 0; i < MT19937_N - MT19937_M; i++) {
      u32 y = (mt[i] & MT19937_UPPER_MASK) | (mt[i + 1] & MT19937_LOWER_MASK);
      mt[i] = mt[i + MT19937_M] ^ (y >> 1) ^ ((y & 1) * 0x9908B0DF);
    }
    for (; i < MT19937_N - 1; i++) {
      u32 y = (mt[i] & MT19937_UPPER_MASK) | (mt[i + 1] & MT19937_LOWER_MASK);
      mt[i] = mt[i + MT19937_M - MT19937_N] ^ (y >> 1) ^ ((y & 1) * 0x9908B0DF);
    }
    u32 y = (mt[MT19937_N - 1] & MT19937_UPPER_MASK) | (mt[0] & MT19937_LOWER_MASK);
    mt[MT19937_N - 1] = mt[MT19937_M - 1] ^ (y >> 1) ^ ((y & 1) * 0x9908B0DF);
    mti = 0;
  }

  u32 y = mt[mti++];
  y ^= (y >> 11);
  y ^= ((y << 7) & 0x9D2C5680);
  y ^= ((y << 15) & 0xEFC60000);
  y ^= (y >> 18);

  return y;
}
