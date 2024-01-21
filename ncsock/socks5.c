/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/socks5.h"
#include "include/socket.h"
#include "include/types.h"
#include <sys/time.h>

bool socks5_connect(socks_5_connection *connection)
{
  struct sockaddr_in proxy_addr;

  connection->socket = socket(AF_INET, SOCK_STREAM, 0);
  if (connection->socket == -1)
    return false;

  proxy_addr.sin_family = AF_INET;
  proxy_addr.sin_port = htons(connection->proxy_port);
  proxy_addr.sin_addr.s_addr = inet_addr(connection->proxy_host);

  if (connect(connection->socket, (struct sockaddr*)&proxy_addr, sizeof(proxy_addr)) == -1)
    return false;
  if (!socks5_handshake(connection))
    return false;
  if (!socks5_send_command(connection))
    return false;
  if (!socks5_verify_response(connection))
    return false;

  return true;
}

bool socks5_send(socks_5_connection *connection, const char *data, size_t size)
{
  if (send(connection->socket, data, size, 0) == -1)
    return false;
  return true;
}

void socks5_close(socks_5_connection *connection)
{
  close(connection->socket);
}

bool socks5_handshake(socks_5_connection *connection)
{
  u8 handshake[] = {0x05, 0x01, 0x00};
  u8 handshake_response[2];

  if (send(connection->socket, handshake, sizeof(handshake), 0) == -1)
    return false;
  if (recv(connection->socket, handshake_response, sizeof(handshake_response), 0) == -1)
    return false;
  if (handshake_response[0] != 0x05 || handshake_response[1] != 0x00)
    return false;

  return true;
}

bool socks5_send_command(socks_5_connection *connection)
{
  size_t connect_command_len = 0;
  u8 connect_command[256];
  u16 target_port;

  connect_command[connect_command_len++] = 0x05; /* SOCKS version */
  connect_command[connect_command_len++] = 0x01; /* Connect command */
  connect_command[connect_command_len++] = 0x00; /* Reserved */
  connect_command[connect_command_len++] = 0x03; /* Domain name type */
  connect_command[connect_command_len++] = (u8)strlen(connection->target_host);

  memcpy(connect_command + connect_command_len, connection->target_host, strlen(connection->target_host));
  connect_command_len += strlen(connection->target_host);

  target_port = htons(connection->target_port);
  memcpy(connect_command + connect_command_len, &target_port, sizeof(target_port));
  connect_command_len += sizeof(target_port);

  if (send(connection->socket, connect_command, connect_command_len, 0) == -1)
    return false;

  return true;
}

bool socks5_verify_response(socks_5_connection *connection)
{
  u8 response[10];
  if (recv(connection->socket, response, sizeof(response), 0) == -1)
    return false;
  if (response[0] != 0x05 || response[1] != 0x00 || response[2] != 0x00)
    return false;

  return true;
}
double socks5_tcp_ping(const char* dest_ip, int port, const char* proxy_host, int proxy_port, int socket, int timeout_ms)
{
  int r;
  struct timeval start_time, end_time;
  double response_time = -1.0;
  struct timeval timeout;
  socks_5_connection connection;
  char response_buffer[CMD_BUFFER];

  connection.proxy_host = proxy_host;
  connection.socket = socket;
  connection.target_port = port;
  connection.proxy_port = proxy_port;
  connection.target_host = dest_ip;

  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;
  setsockopt(connection.socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

  if (socks5_connect(&connection)) {
    if (socks5_send(&connection, "ping", strlen("ping"))) {
      gettimeofday(&start_time, NULL);
      r = recv(connection.socket, response_buffer, sizeof(response_buffer), 0);
      gettimeofday(&end_time, NULL);
      if (r == -1)
        response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0
          + (end_time.tv_usec - start_time.tv_usec) / 1000.0;
    }
    socks5_close(&connection);
  }

  return response_time;
}
