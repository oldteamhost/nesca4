/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/socket.h"

#define ERROR  -1
#define SUCCESS 0

int session_run(const char* dest_ip, int port, int timeout_ms, int verbose)
{
#ifdef PACKET_TRACE
  printf("TCP & CONNECT: ip=%s port=%d timeout_ms=%d verbose=%d\n", dest_ip, port, timeout_ms, verbose);
#endif

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
#ifdef PRINT_ERRORS
    perror("Error creating socket");
#endif
    return -1;
  }
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, dest_ip, &server_addr.sin_addr) <= 0) {
#ifdef PRINT_ERRORS
    perror("Invalid address");
#endif
    close(sockfd);
    return -1;
  }

  struct timeval timeout;
  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;

  if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
#ifdef PRINT_ERRORS
    perror("Error setting receive timeout");
#endif
    close(sockfd);
    return -1;
  }

  if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
#ifdef PRINT_ERRORS
    perror("Connection failed");
#endif
    close(sockfd);
    return -1;
  }

  /*mandatory package acceptance*/
  char response_buffer[CMD_BUFFER];
  ssize_t bytes_received = recv(sockfd, response_buffer, CMD_BUFFER - 1, 0);

  if (bytes_received == -1) {
#ifdef PRINT_ERRORS
    perror("Error receiving response");
#endif
    close(sockfd);
    return -1;
  }

  if (verbose) {
    response_buffer[bytes_received] = '\0';
    printf("VERBOSE  %s", response_buffer);
  }

  return sockfd;
}

void session_run_buf(const char* dest_ip, int port, int timeout_ms, char* buffer, size_t buffer_size)
{
#ifdef PACKET_TRACE
  printf("TCP & CONNECT: ip=%s port=%d timeout_ms=%d\n", dest_ip, port, timeout_ms);
#endif

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
#ifdef PRINT_ERRORS
    perror("session_run_buf/create-socket");
#endif
    return;
  }
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, dest_ip, &server_addr.sin_addr) <= 0) {
#ifdef PRINT_ERRORS
    perror("session_run_buf/invalid-address");
#endif
    close(sockfd);
    return;
  }

  struct timeval timeout;
  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;

  if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
#ifdef PRINT_ERRORS
    perror("session_run_buf/set-timeout");
#endif
    close(sockfd);
    return;
  }

  if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
#ifdef PRINT_ERRORS
    perror("session_run_buf/connection");
#endif
    close(sockfd);
    return;
  }

  /*mandatory package acceptance*/
  ssize_t bytes_received = recv(sockfd, buffer, buffer_size - 1, 0);

  if (bytes_received == -1) {
#ifdef PRINT_ERRORS
    perror("session_run_buf/receiving-response");
#endif
    close(sockfd);
    return;
  }

  buffer[bytes_received] = '\0';
  close(sockfd);
}

int
session_packet(int sockfd, char* response_buffer, const char* message, int verbose, int timeout_ms)
{
#ifdef PACKET_TRACE
  printf("TCP_CONNECT & SENT: message=%s", message);
#endif

  int bytes_sent = send(sockfd, message, strlen(message), 0);
  if (bytes_sent == -1) {
#ifdef PRINT_ERRORS
    perror("session_packet/send");
#endif
    return -1;
  }

  int bytes_received = recv(sockfd, response_buffer, CMD_BUFFER - 1, 0);
  if (bytes_received == -1) {
    if (errno == EWOULDBLOCK || errno == EAGAIN) {
#ifdef PRINT_ERRORS
      perror("session_packet/timeout");
#endif
    }
    else {
#ifdef PRINT_ERRORS
      perror("session_packet/recv");
#endif
    }
    return -1;
  }

  response_buffer[bytes_received] = '\0';
  if (verbose) {
    printf("VERBOSE  %s", response_buffer);
  }

  return bytes_received;
}
