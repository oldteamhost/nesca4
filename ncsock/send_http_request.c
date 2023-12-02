/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

int send_http_request(const char* ip, const int port, const int timeout_ms,
    const struct http_header* header, char* response_buffer, size_t buffer_size)
{
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip, &server_addr.sin_addr);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    return -1;

  struct timeval timeout;
  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;
  if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) == -1) {
    close(sockfd);
    return -1;
  }

  if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    close(sockfd);
    return -1;
  }

  char request[1024];
  snprintf(request, sizeof(request), "%s %s HTTP/1.1\r\n"
                                    "Host: %s\r\n"
                                    "User-Agent: %s\r\n"
                                    "Content-Type: %s\r\n"
                                    "Content-Length: %lu\r\n"
                                    "Connection: close\r\n"
                                    "Authorization: Basic %s\r\n\r\n",
  header->method,
  header->path, header->dest_host, header->user_agent, header->content_type, header->content_len, header->auth_header);

  int send_req = send(sockfd, request, strlen(request), 0);
  if (send_req == -1) {
    close(sockfd);
    return -1;
  }

  size_t response_length = 0;
  ssize_t bytes_received;

  while ((bytes_received = recv(sockfd, response_buffer + response_length, buffer_size - response_length - 1, 0)) > 0)
    response_length += bytes_received;

  response_buffer[response_length] = '\0';

  close(sockfd);
  return response_length;
}
