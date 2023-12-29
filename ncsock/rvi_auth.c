/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/rvi.h"
#include <unistd.h>

const unsigned char headerRVI[32] = {
  0xa0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
  0x61, 0x64, 0x6d, 0x69, 0x6e, 0x00, 0x00, 0x00,
  0x61, 0x64, 0x6d, 0x69, 0x6e, 0x00, 0x00, 0x00,
  0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0xa1, 0xaa
};

const unsigned char loginRVIHeaderStart[8] = {
  0xa0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00
};

const unsigned char loginRVIHeaderEnd[8] = {
  0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0xa1, 0xaa
};

int
rvi_auth(const char* ip, int port, const char* login, const char* pass,
        int verbose, int timeout_ms)
{
  char new_login_packet[32] = {0};
  struct sockaddr_in sa;
  struct timeval timeout;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  struct hostent* host;
  char buff[100] = {0};
  int sock, s = 0, r =0;

  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;

  if (inet_pton(AF_INET, ip, &(sa.sin_addr)) != 1) {
    host = gethostbyname(ip);
    if (host == 0)
      return -1;
  }
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    return -1;
  if (connect(sock, (struct sockaddr*)&sa, sizeof(sa)) == -1)
    goto fail;
  if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
    goto fail;

  memcpy(new_login_packet, loginRVIHeaderStart, sizeof(loginRVIHeaderStart));
  memcpy(new_login_packet + 8, login, strlen(login));
  memcpy(new_login_packet + 16, pass, strlen(pass));
  memcpy(new_login_packet + 24, loginRVIHeaderEnd, sizeof(loginRVIHeaderEnd));

  s = send(sock, new_login_packet, sizeof(new_login_packet), 0);
  if (s == -1)
    goto fail;
  r = recv(sock, buff, 100, 0);
  if (r == -1)
    goto fail;

  close(sock);
  if (buff[9] == 0x08)
    return 0;
  return -1;
fail:
  close(sock);
  return -1;
}
