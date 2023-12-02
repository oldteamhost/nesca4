/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef FTP_H
#define FTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* Compile opts */
#include "ncsockopt.h"

/* FTP Response codes */
#define FTP_REPLY_OKAY            200
#define FTP_REPLY_FILESTATUS      213
#define FTP_REPLY_READY           220
#define FTP_REPLY_CLOSED          221
#define FTP_REPLY_LOGGEDIN        230
#define FTP_REPLY_SERVICEUNAVAIL  421
#define FTP_REPLY_NEEDPASS        331
#define FTP_REPLY_NEEDACCT        332
#define FTP_REPLY_PASSOKAY        230
#define FTP_REPLY_SYST            215
#define FTP_REPLY_FILEOKAY        250
#define FTP_REPLY_CREATED         257
#define FTP_REPLY_PASVMODE        227
#define FTP_REPLY_USEROKAY        331
#define FTP_REPLY_NOTFOUND        550
#define FTP_REPLY_NOPERM          550

/* Function for authorization on ftp server, uses 2 previous
 * functions, can work in threads.*/
int
ftp_auth(const char* ip, int port, const char* login, const char* pass,
        int verbose, int timeout_ms);

void get_ftp_version(const char* ip, const int port, const int timeout_ms,
    char* version_buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif

