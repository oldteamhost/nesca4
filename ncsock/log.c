/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 
 * Copyright (c) 1993 [OpenBSD libc *err* *warn* code.]
 * The Regents of the University of California.
 * All rights reserved.
 */

#include "include/log.h"

noreturn void err(int eval, const char *fmt, ...)
{
  va_list ap;
  
  va_start(ap, fmt);
  if (fmt) {
    (void)vfprintf(stderr, fmt, ap);
    (void)fprintf(stderr, ": ");
  }
  va_end(ap);
  (void)fprintf(stderr, "%s\n", strerror(errno));
  
  exit(eval);
}

void warn(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  if (fmt) {
    (void)vfprintf(stderr, fmt, ap);
    (void)fprintf(stderr, ": ");
  }
  va_end(ap);
  
  (void)fprintf(stderr, "%s\n", strerror(errno));
}

noreturn void errx(int eval, const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  if (fmt)
    (void)vfprintf(stderr, fmt, ap);
  (void)fputc('\n', stderr);
  va_end(ap);
  
  exit(eval);
}

void warnx(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  if (fmt)
    (void)vfprintf(stderr, fmt, ap);
  (void)fputc('\n', stderr);
  
  va_end(ap);
}
