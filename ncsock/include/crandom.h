/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "types.h"
#include <limits.h>
#include <sys/cdefs.h>

/* Linear congruential */
#define	TYPE_0  0
#define	BREAK_0 8
#define	DEG_0   0
#define	SEP_0   0

/* x**7 + x**3 + 1 */
#define	TYPE_1  1
#define	BREAK_1 32
#define	DEG_1   7
#define	SEP_1   3

/* x**15 + x + 1 */
#define	TYPE_2  2
#define	BREAK_2 64
#define	DEG_2   15
#define	SEP_2   1

/* x**31 + x**3 + 1 */
#define	TYPE_3  3
#define	BREAK_3 128
#define	DEG_3   31
#define	SEP_3   3

/* x**63 + x + 1 */
#define	TYPE_4  4
#define	BREAK_4 256
#define	DEG_4   63
#define	SEP_4   1

#define MAX_TYPES 5

__BEGIN_DECLS

long int c_random(void);
void     c_srandom(u32 x);

void *c_initstate(u32 seed, void *argstate, unsigned long n);
void *c_setstate(void *argstate);

__END_DECLS
