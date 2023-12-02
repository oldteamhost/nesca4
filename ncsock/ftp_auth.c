/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ftp.h"
#include "include/socket.h"
#include "include/strbase.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int
ftp_auth(const char* ip, int port, const char* login, const char* pass,
        int verbose, int timeout_ms)
{
  /*run session aka connect to ftp server*/
  int sockfd = session_run(ip, port, timeout_ms, verbose);
  if (sockfd == -1){
      return -1;
  }

  char send_buf[CMD_BUFFER];
  char response_buffer[CMD_BUFFER];

  /*create login command for send ftp*/
  snprintf(send_buf, CMD_BUFFER, "USER %s\r\n", login);

  /*send login*/
  int send_login = session_packet(sockfd, response_buffer, send_buf, verbose, timeout_ms);
  send_login = atoi(response_buffer);

  if (send_login == FTP_REPLY_READY || send_login == FTP_REPLY_LOGGEDIN) {
    /*ftp server no password*/
    close(sockfd);
    return 0;
  }
  else if (send_login != FTP_REPLY_NEEDPASS) {
    /*ftp server not ask password*/
    close(sockfd);
    return -1;
  }
  else if (send_login == FTP_REPLY_SERVICEUNAVAIL) {
    close(sockfd);
    return -1;
  }

  /* clean buffers for second sent */
  memset(send_buf, 0, CMD_BUFFER);
  memset(response_buffer, 0, CMD_BUFFER);

  /*create password command for send ftp*/
  snprintf(send_buf, CMD_BUFFER, "PASS %s\r\n", pass);

  /*send password*/
  int send_pass = session_packet(sockfd, response_buffer, send_buf, verbose, timeout_ms);
  send_pass = atoi(response_buffer);

  if (send_pass != FTP_REPLY_LOGGEDIN && send_pass != FTP_REPLY_OKAY) /*failed password*/ {
    close(sockfd);
    return -1;
  }
  else if (send_pass == FTP_REPLY_SERVICEUNAVAIL) {
    close(sockfd);
    return -1;
  }

  close(sockfd);
  return 0; /*successful auth*/
}
