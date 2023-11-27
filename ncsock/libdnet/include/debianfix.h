/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef DEBAIN_FIX_HEADER
#define DEBAIN_FIX_HEADER

#include <stdint.h>
#include <stdio.h>

typedef uint64_t u64;

u64 _strlcpy(char* dst, const char* src, u64 dlen);
u64 strlcat(char* dst, const char* src, u64 siz);

#endif
