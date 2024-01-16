/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef NCSOCK_SOCKET_H
#define NCSOCK_SOCKET_H

#include <sys/cdefs.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include "types.h"

#define CMD_BUFFER 4096

__BEGIN_DECLS

int     session(const char* dst, u16 port, int timeout_ms, u8* packet, size_t len);
ssize_t session_packet(int fd, u8* packet, ssize_t len, const char* message);
int     session_run(const char* dest_ip, int port, int timeout_ms, int verbose);
u8      *sendproto_command(int fd, const char* command);

__END_DECLS

#endif
