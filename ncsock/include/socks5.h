/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
*/

#ifndef SOCKS_5_H
#define SOCKS_5_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/* Compile opts */
#include "ncsockopt.h"

typedef struct
{
  const char *proxy_host;
  int proxy_port;
  const char *target_host;
  int target_port;
  int socket;
} socks_5_connection;

bool socks5_connect(socks_5_connection *connection);
bool socks5_send(socks_5_connection *connection, const char *data, size_t size);
void socks5_close(socks_5_connection *connection);

bool socks5_handshake(socks_5_connection *connection);
bool socks5_send_command(socks_5_connection *connection);
bool socks5_verify_response(socks_5_connection *connection);

double socks5_tcp_ping(const char* dest_ip, int port, const char* proxy_host, int proxy_port, int socket, int timeout_ms);

#ifdef __cplusplus
}
#endif

#endif

