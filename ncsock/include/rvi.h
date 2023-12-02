/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RVI_H
#define RVI_H 

#ifdef __cplusplus
extern "C" {
#endif

#include "socket.h"
#include <netdb.h>

int
rvi_auth(const char* ip, int port, const char* login, const char* pass,
    int verbose, int timeout_ms);

#ifdef __cplusplus
}
#endif
#endif
