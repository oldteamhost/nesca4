/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"

int fast_send_tcp(int fd, const char* saddr, const char* daddr, int ttl, u16 dport, u8 flags, const char* data, u16 datalen)
{
  return send_tcp_packet(NULL, fd, inet_addr(saddr), inet_addr(daddr), ttl, false, 0, 0,
      generate_random_u32(49151, 65535), dport, generate_random_u32(1, 4294967294),
      0, 0, flags, 1024, 0, NULL, 0, data, datalen, 0, false);
}
