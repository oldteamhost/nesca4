/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef NOTGNU_SHA256_H
#define NOTGNU_SHA256_H

#include <sys/cdefs.h>
#include <bits/wordsize.h>
#include <bits/endian.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

struct sha256_ctx
{
  u32 H[8];
  union
  {
    u64 total64;
#define TOTAL64_low (1 - (__BYTE_ORDER == __LITTLE_ENDIAN))
#define TOTAL64_high (__BYTE_ORDER == __LITTLE_ENDIAN)
    u32 total[2];
  };
  u32 buflen;
  union
  {
    char buffer[128];
    u32 buffer32[32];
    u64 buffer64[16];
  };
};

__BEGIN_DECLS

/* encrypt buf to md5 (void) */
void *sha256(const void *buf, size_t buflen);

/* encrypt buf to md5 string (char) */
char *sha256str(const void *buf, size_t buflen);

void sha256_init_ctx(struct sha256_ctx *ctx);
void sha256_process_bytes(const void *buffer, size_t len, struct sha256_ctx *ctx);
void sha256_process_block(const void *buffer, size_t len, struct sha256_ctx *ctx);
void *sha256_finish_ctx(struct sha256_ctx *ctx, void *resbuf);

__END_DECLS

#endif

