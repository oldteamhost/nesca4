/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include "include/strbase.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define REQUEST_LEN 6554543
int send_http_request(const char* ip, const int port, const int timeout_ms,
    struct http_header* header, char* response_buffer, size_t buffer_size)
{
  struct sockaddr_in server_addr;
  int sockfd, send_req;
  struct timeval timeout;
  char request[REQUEST_LEN];
  size_t response_length = 0, bytes_received;

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip, &server_addr.sin_addr);
  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    return -1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) == -1)
    goto fail;
  if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout)) == -1)
    goto fail;
  if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    goto fail;

  /*
  printf("%s %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "User-Agent: %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %lu\r\n"
        "Connection: close\r\n"
        "Authorization: Basic %s\r\n\r\n",
  header->method, header->path, header->dest_host, header->user_agent,
  header->content_type, header->content_len, header->auth_header);
  */

  snprintf(request, REQUEST_LEN,
      "%s %s HTTP/1.1\r\n"
      "Host: %s\r\n"
      "User-Agent: %s\r\n"
      "Content-Type: %s\r\n"
      "Content-Length: %lu\r\n"
      "Connection: close\r\n"
      "Authorization: Basic %s\r\n\r\n",
  header->method, header->path, header->dest_host, header->user_agent,
  header->content_type, header->content_len, header->auth_header);

  send_req = send(sockfd, request, strlen(request), 0);
  if (send_req == -1)
    goto fail;

  while ((bytes_received = recv(sockfd, response_buffer + response_length, buffer_size - response_length - 1, 0)) > 0) {
    if (response_length + bytes_received >= buffer_size - 1)
      break;
    response_length += bytes_received;
  }
  close(sockfd);
  response_buffer[response_length] = '\0';

  return response_length;
fail:
  close(sockfd);
  return -1;
}
