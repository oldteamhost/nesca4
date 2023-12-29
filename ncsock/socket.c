/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/socket.h"
#include <unistd.h>

int session_run(const char* dest_ip, int port, int timeout_ms, int verbose)
{
  struct timeval timeout;
  struct sockaddr_in server_addr;
  int sockfd, r;
  char response_buffer[CMD_BUFFER];

  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
    return -1;

  if (inet_pton(AF_INET, dest_ip, &server_addr.sin_addr) <= 0)
    goto fail;
  if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
    goto fail;
  if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    goto fail;

  r = recv(sockfd, response_buffer, CMD_BUFFER - 1, 0);
  if (r == -1)
    goto fail;

  if (verbose) {
    response_buffer[r] = '\0';
    printf("VERBOSE  %s", response_buffer);
  }

  return sockfd;
fail:
  close(sockfd);
  return -1;
}

void session_run_buf(const char* dest_ip, int port, int timeout_ms, char* buffer, size_t buffer_size)
{
  struct timeval timeout;
  struct sockaddr_in server_addr;
  int sockfd, r;

  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
    return;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, dest_ip, &server_addr.sin_addr) <= 0)
    goto fail;
  if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
    goto fail;
  if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    goto fail;

  r = recv(sockfd, buffer, buffer_size - 1, 0);
  close(sockfd);
  if (r == -1)
    return;

  buffer[r] = '\0';
fail:
  close(sockfd);
  return;
}

int
session_packet(int sockfd, char* response_buffer, const char* message, int verbose, int timeout_ms)
{
  int s, r;

  s = send(sockfd, message, strlen(message), 0);
  if (s == -1)
    return -1;
  r = recv(sockfd, response_buffer, CMD_BUFFER - 1, 0);
  if (r == -1)
    return -1;

  response_buffer[r] = '\0';
  if (verbose)
    printf("VERBOSE  %s", response_buffer);

  return r;
}
