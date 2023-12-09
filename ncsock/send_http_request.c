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


#define IS_NULL_OR_EMPTY(str) \
  ((str == NULL) || (*str == '\0'))

void ext_path(const char *url, char *path)
{
  const char *ptr = strstr(url, "://");
  if (ptr != NULL) {
    ptr += 3;
    ptr = strchr(ptr, '/');
    if (ptr != NULL)
      strcpy(path, ptr);
    else
      strcpy(path, "/");
  }
  else
    strcpy(path, url);
}

#define REQUEST_LEN 6554543
int send_http_request(const char* ip, const int port, const int timeout_ms,
    struct http_header* header, char* response_buffer, size_t buffer_size)
{
  struct sockaddr_in server_addr;
  char* newpath = NULL;
  int sockfd, send_req, find, count;
  bool aee = false;
  struct timeval timeout;
  const char *respath;
  char request[REQUEST_LEN];
  char path[65535];
  size_t response_length = 0, bytes_received, len;
  char* newurl = NULL;

  const char* http_prefix = "http://";
  const char* https_prefix = "https://";

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip, &server_addr.sin_addr);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    return -1;

  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;

  if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) == -1)
    goto fail;

  if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout)) == -1)
    goto fail;

  if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    goto fail;

  if (IS_NULL_OR_EMPTY(header->path))
    header->path = "/";

  if (header->path != NULL && header->path[0] == '.')
    memmove((void*)header->path, (void*)(header->path + 1), strlen(header->path));

  for (const char *ptr = header->path; *ptr != '\0'; ++ptr) {
    if (*ptr == '/') {
      ++count;
      if (count == 4) {
        if (*(ptr + 1) != '\0')
          aee = true;
        break;
      }
    }
  }

  if (aee) {
    ext_path(header->path, path);
    respath = path;
  }
  else {
    if (find_word(header->path, "http://") == 0 || find_word(header->path, "https://") == 0) {
      newurl = clean_url(header->path);
      if (newurl)
        header->dest_host = newurl;
      respath = "/";
    }
    else {
      if (header->path[0] != '/') {
        len = strlen(header->path) + 2;
        newpath = (char *)malloc(len);
        if (newpath) {
          newpath[0] = '/';
          strcpy(newpath + 1, header->path);
          respath = newpath;
        }
      }
      else
        respath = header->path;
    }
  }

  /*
  printf("%s %s HTTP/1.1\r\n"
                                    "Host: %s\r\n"
                                    "User-Agent: %s\r\n"
                                    "Content-Type: %s\r\n"
                                    "Content-Length: %lu\r\n"
                                    "Connection: close\r\n"
                                    "Authorization: Basic %s\r\n\r\n",
  header->method,
  respath, header->dest_host, header->user_agent, header->content_type, header->content_len, header->auth_header);
  */

  snprintf(request, REQUEST_LEN, "%s %s HTTP/1.1\r\n"
                                    "Host: %s\r\n"
                                    "User-Agent: %s\r\n"
                                    "Content-Type: %s\r\n"
                                    "Content-Length: %lu\r\n"
                                    "Connection: close\r\n"
                                    "Authorization: Basic %s\r\n\r\n",
  header->method,
  respath, header->dest_host, header->user_agent, header->content_type, header->content_len, header->auth_header);


  send_req = send(sockfd, request, strlen(request), 0);

  if (newpath)
    free(newpath);
  if (newurl)
    free(newurl);

  if (send_req == -1)
    goto fail;

  while ((bytes_received = recv(sockfd, response_buffer + response_length, buffer_size - response_length - 1, 0)) > 0) {
    if (response_length + bytes_received >= buffer_size - 1)
      break;
    response_length += bytes_received;
  }

  response_buffer[response_length] = '\0';

  close(sockfd);
  return response_length;

fail:
  close(sockfd);
  return -1;
}
