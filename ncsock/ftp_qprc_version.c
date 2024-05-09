/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ftp.h"
#include "include/socket.h"
#include "include/utils.h"

void ftp_qprc_version(const char* dst, u16 dstport, int timeoutms,
    u8* verbuf, ssize_t buflen)
{
  session(dst, dstport, timeoutms, verbuf, buflen);
  remove_specials((char*)verbuf);
}
