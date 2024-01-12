/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <sys/cdefs.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "types.h"
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include "mt19937.h"
#include "../include/eth.h"

#define CIDR  0
#define IPv4  1
#define RANGE 2
#define _URL_ 3
#define DNS   4
#define IPv6  5
#define OUTRAGEOUS_SPEED 5
#define FIERCE_SPEED     4
#define FAST_SPEED       3
#define BALANCED_SPEED   2
#define NOT_SPEED        1

#define IS_NULL_OR_EMPTY(str) \
  ((str == NULL) || (*str == '\0'))

#include <sys/time.h>
#define U64_SEED() ({                     \
  struct timeval t;                       \
  gettimeofday(&t, NULL);                 \
  ((uint64_t)t.tv_sec << 32) | t.tv_usec; \
})

#define DEFAULT_DICTIONARY \
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

__BEGIN_DECLS

int   this_is(const char* node);
int   check_root_perms(void);
void  delayy(int ms);
void  get_current_date(char* formatted_date, size_t max_length);
int   calculate_timeout(double rtt, int speed);
int   calculate_threads(int speed, int len);
int   calculate_ping_timeout(int speed);
char *get_active_interface_name(char* buffer, size_t len);
char *get_local_ip(void);
char *get_local_ipv6(void);
void  maceth(const char *mac, eth_addr_t *eth);
void  macstr(eth_addr_t *eth, char* mac);
int   get_gateway_ip(char* buf, size_t len);
int   get_local_mac(const char *dev, char *mac_address);
int   parse_ipopts(const char *txt, u8 *data, int datalen,
          int* firsthopoff, int* lasthopoff, char *errstr,
          size_t errstrlen);
void  parse_tcpopts(u8 *optp, int len, char *result, int bufsize);
u8   *hexbin(char *str, size_t *outlen);
int   find_word(const char* buffer, const char* word);
char *clean_url(const char* url);
void  remove_specials(char* buffer);
void  to_lower(char* str);
void  to_lower_const(const char* input, char* output);
u32   generate_seed(void);
u32   random_num(u32 min, u32 max);
char *generate_random_str(int len, const char* dictionary);
u32   generate_ident(void);
u16   generate_checksum(void);
u16   generate_rare_port(void);
u32   generate_seq(void);
u32   random_u32(void);
u16   random_u16(void);
u8    random_u8(void);
const char* generate_ipv4(void);
const char* get_time();
const char* get_this_is(int type);

__END_DECLS

#endif

