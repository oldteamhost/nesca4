/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ftp.h"
#include "include/socket.h"
#include <stdio.h>
#include "include/utils.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

 bool ftp_qprc_auth(int fd, const char* login, const char* pass)
{
  char command[CMD_BUFFER];
  int rescode = 0;
  u8 *recvbuf = NULL;

  snprintf(command, CMD_BUFFER, "%s %s\r\n", C_USER, login);
  recvbuf = sendproto_command(fd, command);
  if (!recvbuf)
    goto fail;
  rescode = atoi((char*)recvbuf);

  if (rescode == R_220 || rescode == R_230)
    goto ok;
  if (rescode != R_331)
    goto fail;

  memset(command, 0, CMD_BUFFER);
  memset(recvbuf, 0, CMD_BUFFER);
  snprintf(command, CMD_BUFFER, "%s %s\r\n", C_PASS, pass);

  recvbuf = sendproto_command(fd, command);
  if (!recvbuf)
    goto fail;
  rescode = atoi((char*)recvbuf);

  if (rescode == R_230 || rescode == R_200)
    goto ok;

  goto fail;

fail:
  if (recvbuf)
    free(recvbuf);
  return false;

ok:
  if (recvbuf)
    free(recvbuf);
  return true;

}
