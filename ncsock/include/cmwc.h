/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CMWC_HEADER
#define CMWC_HEADER

#include "types.h"
#include <sys/cdefs.h>

#define PHI 0x9e3779b9

__BEGIN_DECLS

void cmwc_seed(u64 seed);
u64  cmwc_random(void);

__END_DECLS

#endif
