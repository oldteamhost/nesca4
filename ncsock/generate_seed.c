/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/strbase.h"
#include <time.h>

unsigned int generate_seed(void)
{
  struct timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
    return -1;

  unsigned int seed = (unsigned int)(ts.tv_sec * 1000000000ULL + ts.tv_nsec);
  return seed;
}
