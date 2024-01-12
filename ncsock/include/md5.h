/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef NOTGNU_MD5_H
#define NOTGNU_MD5_H

#include <sys/cdefs.h>
#include <bits/wordsize.h>
#include <stdio.h>
#include <bits/endian.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

#define UINT_MAX_32_BITS \
  4294967295U

typedef u32 md5_uint32;
typedef uintptr_t md5_uintptr;

struct md5_ctx
{
  md5_uint32 A;
  md5_uint32 B;
  md5_uint32 C;
  md5_uint32 D;

  md5_uint32 total[2];
  md5_uint32 buflen;
  union
  {
    char buffer[128];
    md5_uint32 buffer32[32];
  };
};

__BEGIN_DECLS

/* encrypt buf to md5 (void) */
void *md5(const void *buf, size_t buflen);

/* encrypt buf to md5 string (char) */
char *md5str(const void *buf, size_t buflen);

void md5_init_ctx(struct md5_ctx *ctx);
void md5_process_block(const void *buffer, size_t len, struct md5_ctx *ctx);
void md5_process_bytes(const void *buffer, size_t len, struct md5_ctx *ctx);
void *md5_finish_ctx(struct md5_ctx *ctx, void *resbuf);
void *md5_read_ctx(const struct md5_ctx *ctx, void *resbuf);
void *md5_buffer(const char *buffer, size_t len, void *resblock);

__END_DECLS

#endif
