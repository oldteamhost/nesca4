/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/smtp.h"
#include "include/socket.h"
#include "include/utils.h"

void smtp_qprc_version(const char* dst, u16 dstport, int timeoutms,
    u8* verbuf, size_t buflen)
{
  session(dst, dstport, timeoutms, (u8*)verbuf, buflen);
  remove_specials((char*)verbuf);
}
