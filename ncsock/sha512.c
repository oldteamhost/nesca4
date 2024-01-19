/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "include/sha512.h"

#if __BYTE_ORDER == __LITTLE_ENDIAN
  #include <bits/byteswap.h>
  #define SWAP(n) __bswap_64 (n)
#else
  #define SWAP(n) (n)
#endif

static const unsigned char fillbuf[128] = { 0x80, 0 /* , 0, 0, ...  */ };

void *sha512(const void *buf, size_t buflen)
{
  struct sha512_ctx ctx;
  sha512_init_ctx(&ctx);

  sha512_process_bytes(buf, buflen, &ctx);

  void *encrypted_buffer = malloc(64);
  if (!encrypted_buffer)
    return NULL;

  sha512_finish_ctx(&ctx, encrypted_buffer);
  return encrypted_buffer;
}

char *sha512str(const void *buf, size_t buflen)
{
  void *encrypted_buffer = sha512(buf, buflen);
  if (!encrypted_buffer)
    return NULL;

  char *hex_str = malloc(129);
  if (hex_str == NULL) {
    free(encrypted_buffer);
    return NULL;
  }

  for (int i = 0; i < 64; i++) {
    sprintf(hex_str + (i * 2), "%02x", ((u8*)encrypted_buffer)[i]);
  }
  hex_str[128] = '\0';

  free(encrypted_buffer);
  return hex_str;
}

#include <stdint.h>
static const u64 K[80] =
{
  UINT64_C (0x428a2f98d728ae22), UINT64_C (0x7137449123ef65cd),
  UINT64_C (0xb5c0fbcfec4d3b2f), UINT64_C (0xe9b5dba58189dbbc),
  UINT64_C (0x3956c25bf348b538), UINT64_C (0x59f111f1b605d019),
  UINT64_C (0x923f82a4af194f9b), UINT64_C (0xab1c5ed5da6d8118),
  UINT64_C (0xd807aa98a3030242), UINT64_C (0x12835b0145706fbe),
  UINT64_C (0x243185be4ee4b28c), UINT64_C (0x550c7dc3d5ffb4e2),
  UINT64_C (0x72be5d74f27b896f), UINT64_C (0x80deb1fe3b1696b1),
  UINT64_C (0x9bdc06a725c71235), UINT64_C (0xc19bf174cf692694),
  UINT64_C (0xe49b69c19ef14ad2), UINT64_C (0xefbe4786384f25e3),
  UINT64_C (0x0fc19dc68b8cd5b5), UINT64_C (0x240ca1cc77ac9c65),
  UINT64_C (0x2de92c6f592b0275), UINT64_C (0x4a7484aa6ea6e483),
  UINT64_C (0x5cb0a9dcbd41fbd4), UINT64_C (0x76f988da831153b5),
  UINT64_C (0x983e5152ee66dfab), UINT64_C (0xa831c66d2db43210),
  UINT64_C (0xb00327c898fb213f), UINT64_C (0xbf597fc7beef0ee4),
  UINT64_C (0xc6e00bf33da88fc2), UINT64_C (0xd5a79147930aa725),
  UINT64_C (0x06ca6351e003826f), UINT64_C (0x142929670a0e6e70),
  UINT64_C (0x27b70a8546d22ffc), UINT64_C (0x2e1b21385c26c926),
  UINT64_C (0x4d2c6dfc5ac42aed), UINT64_C (0x53380d139d95b3df),
  UINT64_C (0x650a73548baf63de), UINT64_C (0x766a0abb3c77b2a8),
  UINT64_C (0x81c2c92e47edaee6), UINT64_C (0x92722c851482353b),
  UINT64_C (0xa2bfe8a14cf10364), UINT64_C (0xa81a664bbc423001),
  UINT64_C (0xc24b8b70d0f89791), UINT64_C (0xc76c51a30654be30),
  UINT64_C (0xd192e819d6ef5218), UINT64_C (0xd69906245565a910),
  UINT64_C (0xf40e35855771202a), UINT64_C (0x106aa07032bbd1b8),
  UINT64_C (0x19a4c116b8d2d0c8), UINT64_C (0x1e376c085141ab53),
  UINT64_C (0x2748774cdf8eeb99), UINT64_C (0x34b0bcb5e19b48a8),
  UINT64_C (0x391c0cb3c5c95a63), UINT64_C (0x4ed8aa4ae3418acb),
  UINT64_C (0x5b9cca4f7763e373), UINT64_C (0x682e6ff3d6b2b8a3),
  UINT64_C (0x748f82ee5defb2fc), UINT64_C (0x78a5636f43172f60),
  UINT64_C (0x84c87814a1f0ab72), UINT64_C (0x8cc702081a6439ec),
  UINT64_C (0x90befffa23631e28), UINT64_C (0xa4506cebde82bde9),
  UINT64_C (0xbef9a3f7b2c67915), UINT64_C (0xc67178f2e372532b),
  UINT64_C (0xca273eceea26619c), UINT64_C (0xd186b8c721c0c207),
  UINT64_C (0xeada7dd6cde0eb1e), UINT64_C (0xf57d4f7fee6ed178),
  UINT64_C (0x06f067aa72176fba), UINT64_C (0x0a637dc5a2c898a6),
  UINT64_C (0x113f9804bef90dae), UINT64_C (0x1b710b35131c471b),
  UINT64_C (0x28db77f523047d84), UINT64_C (0x32caab7b40c72493),
  UINT64_C (0x3c9ebe0a15c9bebc), UINT64_C (0x431d67c49c100d4c),
  UINT64_C (0x4cc5d4becb3e42b6), UINT64_C (0x597f299cfc657e2a),
  UINT64_C (0x5fcb6fab3ad6faec), UINT64_C (0x6c44198c4a475817)
};

void sha512_init_ctx(struct sha512_ctx *ctx)
{
  ctx->H[0] = UINT64_C (0x6a09e667f3bcc908);
  ctx->H[1] = UINT64_C (0xbb67ae8584caa73b);
  ctx->H[2] = UINT64_C (0x3c6ef372fe94f82b);
  ctx->H[3] = UINT64_C (0xa54ff53a5f1d36f1);
  ctx->H[4] = UINT64_C (0x510e527fade682d1);
  ctx->H[5] = UINT64_C (0x9b05688c2b3e6c1f);
  ctx->H[6] = UINT64_C (0x1f83d9abfb41bd6b);
  ctx->H[7] = UINT64_C (0x5be0cd19137e2179);

  ctx->total[0] = ctx->total[1] = 0;
  ctx->buflen = 0;
}

void sha512_process_bytes(const void *buffer, size_t len, struct sha512_ctx *ctx)
{
  if (ctx->buflen != 0) {
    size_t left_over = ctx->buflen;
    size_t add = 256 - left_over > len ? len : 256 - left_over;

    memcpy (&ctx->buffer[left_over], buffer, add);
    ctx->buflen += add;

    if (ctx->buflen > 128) {
      sha512_process_block (ctx->buffer, ctx->buflen & ~127, ctx);
      ctx->buflen &= 127;
      memcpy (ctx->buffer, &ctx->buffer[(left_over + add) & ~127],
      ctx->buflen);
    }

    buffer = (const char *) buffer + add;
    len -= add;
  }
  if (len >= 128) {
    #define UNALIGNED_P(p) (((uintptr_t) p) % sizeof (u64) != 0)
    if (UNALIGNED_P(buffer)) {
      while (len > 128) {
        sha512_process_block (memcpy (ctx->buffer, buffer, 128), 128, ctx);
        buffer = (const char *) buffer + 128;
        len -= 128;
      }
    }
    else {
      sha512_process_block (buffer, len & ~127, ctx);
      buffer = (const char *) buffer + (len & ~127);
      len &= 127;
    }
  }

  if (len > 0) {
    size_t left_over = ctx->buflen;

    memcpy (&ctx->buffer[left_over], buffer, len);
    left_over += len;
    if (left_over >= 128) {
      sha512_process_block (ctx->buffer, 128, ctx);
      left_over -= 128;
      memcpy (ctx->buffer, &ctx->buffer[128], left_over);
    }
    ctx->buflen = left_over;
  }
}

void sha512_process_block(const void *buffer, size_t len, struct sha512_ctx *ctx)
{
  const u64 *words = buffer;
  size_t nwords = len / sizeof (u64);
  u64 a = ctx->H[0];
  u64 b = ctx->H[1];
  u64 c = ctx->H[2];
  u64 d = ctx->H[3];
  u64 e = ctx->H[4];
  u64 f = ctx->H[5];
  u64 g = ctx->H[6];
  u64 h = ctx->H[7];

#ifdef USE_TOTAL128
  ctx->total128 += len;
#else
  u64 lolen = len;
  ctx->total[TOTAL128_low] += lolen;
  ctx->total[TOTAL128_high] += ((len >> 31 >> 31 >> 2) + (ctx->total[TOTAL128_low] < lolen));
#endif

  while (nwords > 0) {
    u64 W[80];
    u64 a_save = a;
    u64 b_save = b;
    u64 c_save = c;
    u64 d_save = d;
    u64 e_save = e;
    u64 f_save = f;
    u64 g_save = g;
    u64 h_save = h;

    #define Ch(x, y, z) ((x & y) ^ (~x & z))
    #define Maj(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
    #define S0(x) (CYCLIC (x, 28) ^ CYCLIC (x, 34) ^ CYCLIC (x, 39))
    #define S1(x) (CYCLIC (x, 14) ^ CYCLIC (x, 18) ^ CYCLIC (x, 41))
    #define R0(x) (CYCLIC (x, 1) ^ CYCLIC (x, 8) ^ (x >> 7))
    #define R1(x) (CYCLIC (x, 19) ^ CYCLIC (x, 61) ^ (x >> 6))

    #define CYCLIC(w, s) ((w >> s) | (w << (64 - s)))
    for (unsigned int t = 0; t < 16; ++t) {
      W[t] = SWAP (*words);
      ++words;
    }

    for (unsigned int t = 16; t < 80; ++t) {
      W[t] = R1 (W[t - 2]) + W[t - 7] + R0 (W[t - 15]) + W[t - 16];
    }

    for (unsigned int t = 0; t < 80; ++t) {
      u64 T1 = h + S1 (e) + Ch (e, f, g) + K[t] + W[t];
      u64 T2 = S0 (a) + Maj (a, b, c);
      h = g;
      g = f;
      f = e;
      e = d + T1;
      d = c;
      c = b;
      b = a;
      a = T1 + T2;
    }

    a += a_save;
    b += b_save;
    c += c_save;
    d += d_save;
    e += e_save;
    f += f_save;
    g += g_save;
    h += h_save;

    nwords -= 16;
  }

  ctx->H[0] = a;
  ctx->H[1] = b;
  ctx->H[2] = c;
  ctx->H[3] = d;
  ctx->H[4] = e;
  ctx->H[5] = f;
  ctx->H[6] = g;
  ctx->H[7] = h;
}

void *sha512_finish_ctx(struct sha512_ctx *ctx, void *resbuf)
{
  u64 bytes = ctx->buflen;
  size_t pad;

#ifdef USE_TOTAL128
  ctx->total128 += bytes;
#else
  ctx->total[TOTAL128_low] += bytes;
  if (ctx->total[TOTAL128_low] < bytes)
    ++ctx->total[TOTAL128_high];
#endif

  pad = bytes >= 112 ? 128 + 112 - bytes : 112 - bytes;
  memcpy (&ctx->buffer[bytes], fillbuf, pad);

  ctx->buffer64[(bytes + pad + 8) / 8] = SWAP(ctx->total[TOTAL128_low] << 3);
  ctx->buffer64[(bytes + pad) / 8] = SWAP((ctx->total[TOTAL128_high] << 3) | (ctx->total[TOTAL128_low] >> 61));

  sha512_process_block (ctx->buffer, bytes + pad + 16, ctx);

  for (unsigned int i = 0; i < 8; ++i) {
    ((u64*) resbuf)[i] = SWAP (ctx->H[i]);
  }

  return resbuf;
}

