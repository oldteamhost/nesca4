/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef SOCKS_5_H
#define SOCKS_5_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/cdefs.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct
{
  const char *proxy_host;
  int proxy_port;
  const char *target_host;
  int target_port;
  int socket;
} socks_5_connection;

__BEGIN_DECLS

bool socks5_connect(socks_5_connection *connection);
bool socks5_send(socks_5_connection *connection,
    const char *data, size_t size);
void socks5_close(socks_5_connection *connection);
bool socks5_handshake(socks_5_connection *connection);
bool socks5_send_command(socks_5_connection *connection);
bool socks5_verify_response(socks_5_connection *connection);
double socks5_tcp_ping(const char* dest_ip, int port,
    const char* proxy_host, int proxy_port, int socket,
    int timeout_ms);

__END_DECLS

#endif

