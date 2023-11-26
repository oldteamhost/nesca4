/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef MT19937_H
#define MT19937_H

#include "types.h"
#include <sys/cdefs.h>

#define MT19937_N 624
#define MT19937_M 397

#define MT19937_UPPER_MASK 0x80000000
#define MT19937_LOWER_MASK 0x7FFFFFFF

__BEGIN_DECLS

void mt19937_seed(u32 seed);
u32 mt19937_random(void);
u32 generate_seed_u32(void);
u32 generate_random_u32(u32 min, u32 max);

__END_DECLS

#endif
