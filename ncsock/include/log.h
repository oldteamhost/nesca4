/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef LOG_HEADER_
#define LOG_HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <stdnoreturn.h>

/*
 * Copyright (c) 1993 [OpenBSD libc *err* *warn* code.]
 * The Regents of the University of California.
 * All rights reserved.
 */

__BEGIN_DECLS

noreturn void err(int eval, const char *fmt, ...);
void warn(const char *fmt, ...);
noreturn void errx(int eval, const char *fmt, ...);
void warnx(const char *fmt, ...);

__END_DECLS

#endif
