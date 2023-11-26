/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
*/

#ifndef SMTP_H
#define SMTP_H

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

/* SMTP Response codes */
#define SMTP_REPLY_READY           220
#define SMTP_REPLY_COMPLETED       250
#define SMTP_REPLY_STARTTLS        220
#define SMTP_REPLY_AUTH_REQUIRED   334
#define SMTP_REPLY_AUTH_SUCCESS    235
#define SMTP_REPLY_AUTH_FAILED     535
#define SMTP_REPLY_MAIL_OKAY       250
#define SMTP_REPLY_RCPT_OKAY       250
#define SMTP_REPLY_DATA_OKAY       354
#define SMTP_REPLY_QUIT_OKAY       221
#define SMTP_REPLY_SERVER_ERROR    421
#define SMTP_REPLY_COMMAND_ERROR   500
#define SMTP_REPLY_AUTH_DISABLE    503
#define SMTP_REPLY_PARAM_ERROR     501
#define SMTP_REPLY_AUTH_ERROR      535
#define SMTP_REPLY_TRANSACTION_FAILED 554

/* Function for authorization on ftp server, uses 2 previous
 * functions, can work in threads.*/
int
smtp_auth(const char* ip, int port, const char* login, const char* pass,
        int verbose, int timeout_ms);

void get_smtp_version(const char* ip, const int port, const int timeout_ms,
    char* version_buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif
