/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/smtp.h"
#include "include/socket.h"
#include "include/utils.h"

void get_smtp_version(const char* ip, u16 port, int timeout_ms, u8* version_buffer, size_t len)
{
  session(ip, port, timeout_ms, (u8*)version_buffer, len);
  remove_specials((char*)version_buffer);
}
