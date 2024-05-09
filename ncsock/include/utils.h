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
#include <sys/time.h>

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

#define U64_SEED() ({                     \
  struct timeval t;                       \
  gettimeofday(&t, NULL);                 \
  ((uint64_t)t.tv_sec << 32) | t.tv_usec; \
})

#define DEFAULT_DICTIONARY \
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

__BEGIN_DECLS

int this_is(const char *node);
int getipv4(const char *node, char *res, u8 reslen);
  
int   check_root_perms(void);
void  delayy(int ms);
void  get_current_date(char* formatted_date, size_t max_length);
int   calculate_timeout(double rtt, int speed);
int   calculate_threads(int speed, int len);
int   calculate_ping_timeout(int speed);
char *get_active_interface_name(char* buffer, size_t len);
int   get_gateway_ip(char* buf, size_t len);
int   get_local_mac(const char *dev, char *mac_address);
void  maceth(const char *mac, eth_addr_t *eth);
void  macstr(eth_addr_t *eth, char* mac);
int   parse_ipopts(const char *txt, u8 *data, int datalen,
		   int* firsthopoff, int* lasthopoff, char *errstr,
		   size_t errstrlen);
void  parse_tcpopts(u8 *optp, int len, char *result, int bufsize);
u8   *hexbin(char *str, size_t *outlen);
int   find_word(const char* buffer, const char* word);
char *clean_url(const char* url);
void  remove_specials(char* buffer);
void  to_lower(char* str);
void to_lower_const(const char *input, char *output);
u32   random_num_u32(u32 min, u32 max);
u32   random_seed_u32(void);
char *random_str(int len, const char *dictionary);
u16   random_check(void);
u16   random_srcport(void);
u32   random_u32(void);
u16   random_u16(void);
u8    random_u8(void);
const char *random_ip4(void);
const char *get_time(void);
const char *get_this_is(int type);

#define USED(x) ((void)(x))
#define Z(x) (memset((x), '\0', sizeof(x)))

#define parseip4(from, to)                                                     \
  ({                                                                           \
    char *p = from;                                                            \
    int i;                                                                     \
    for (i = 0; i < 4 && *p; i++) {                                            \
      to[i] = strtoul(p, &p, 0);                                               \
      p++;                                                                     \
    }                                                                          \
    to[i] = '\0';                                                              \
    (i == 4) ? 4 : -1;                                                         \
  })

#define parseip6(from, to)                                                     \
  ({                                                                           \
    USED(from);                                                                \
    USED(to);                                                                  \
    16;                                                                        \
  })

#define parseip(from, to) (strchr(from, '.') ? parseip4(from, to) : parseip6(from, to))

#define maskfromip(v, ip, mask)                                                \
  do {                                                                         \
    USED(v);                                                                   \
    USED(ip);                                                                  \
    USED(mask);                                                                \
  } while (0)

inline char *ip4str(u8 *from, char *to) {
  sprintf(to, "%d.%d.%d.%d", from[0], from[1], from[2], from[3]);
  return to;
}

inline char *ip6str(u8 *from, char *to) {
  USED(from), USED(to);
  return to;
}

#define ipstr(v, from, to) ((v == 4) ? ip4str(from, to) : ip6str(from, to))

int   parsecmask(int v, char *from, u8 *to);
int   parsecidr(char *cidr, u8 *ip, u8 *mask);
int   parseipmask(char *ip, char *mask, u8 *pip, u8 *pmask);
u8    maskcnum(u8 *from);
char *cidrstr(int v, u8 *ip, u8 *mask, char *to);

#define ip4num(pip)                                                            \
  (((u32)(pip[3]) << 0) | ((u32)(pip[2]) << 8) | ((u32)(pip[1]) << 16) |       \
   ((u32)(pip[0]) << 24))

__END_DECLS

#endif

