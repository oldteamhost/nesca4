/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef SMTP_H
#define SMTP_H

#include <stdio.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/cdefs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "types.h"

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

__BEGIN_DECLS

void get_smtp_version(const char* ip, u16 port, int timeout_ms,
    u8* version_buffer, size_t len);

__END_DECLS

#endif
