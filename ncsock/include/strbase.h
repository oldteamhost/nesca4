/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef STRBASE_H
#define STRBASE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include "mt19937.h"

#define IS_NULL_OR_EMPTY(str) \
  ((str == NULL) || (*str == '\0'))

#include <sys/time.h>
#define U64_SEED() ({                     \
  struct timeval t;                       \
  gettimeofday(&t, NULL);                 \
  ((uint64_t)t.tv_sec << 32) | t.tv_usec; \
})

int find_word(const char* buffer, const char* word);
char* clean_url(const char* url);
void remove_specials(char* buffer);
void to_lower(char* str);

/* Function for random ident generation. */
unsigned int generate_seed(void);
unsigned int random_num(unsigned int min, unsigned int max);

#define DEFAULT_DICTIONARY "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
char* generate_random_str(int len, const char* dictionary);

u32 generate_ident(void);
u16 generate_checksum(void);
u16 generate_rare_port(void);
u32 generate_seq(void);
const char* generate_ipv4(void);

#ifdef __cplusplus
}
#endif

#endif
