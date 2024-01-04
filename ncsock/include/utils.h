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
#include <ctype.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "types.h"

#include "../libdnet/include/eth.h"

__BEGIN_DECLS

char* get_active_interface_name(void);
char* get_local_ip(void);
void maceth(const char *mac, eth_addr_t *eth);
void macstr(eth_addr_t *eth, char* mac);
int parse_ipopts(const char *txt, u8 *data, int datalen, int* firsthopoff,
    int* lasthopoff, char *errstr, size_t errstrlen);
void parse_tcpopts(u8 *optp, int len, char *result,
    int bufsize);
u8 *hexbin(char *str, size_t *outlen);

__END_DECLS

#endif

