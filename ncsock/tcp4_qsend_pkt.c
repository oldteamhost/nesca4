/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"
#include "include/utils.h"

int tcp4_qsend_pkt(int fd, const char *src, const char *dst, int ttl,
                   u16 dstport, u8 flags, const char *data, u16 datalen)
{
  return tcp4_send_pkt(NULL, fd, inet_addr(src), inet_addr(dst), ttl, false, 0, 0,
                       random_srcport(), dstport, random_u32(), 0, 0, flags, 1024,
		       0, NULL, 0, data, datalen, 0, false);
  

}
