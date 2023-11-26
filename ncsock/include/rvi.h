/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
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
