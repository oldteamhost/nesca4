/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ftp.h"
#include "include/socket.h"
#include "include/strbase.h"

void get_ftp_version(const char* ip, const int port, const int timeout_ms, char* version_buffer, size_t buffer_size)
{
  session_run_buf(ip, port, timeout_ms, version_buffer, buffer_size);
  remove_specials(version_buffer);
}
