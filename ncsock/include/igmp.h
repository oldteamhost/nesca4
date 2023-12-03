/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef IGMP_HEADER
#define IGMP_HEADER

#include "types.h"
#include "ip.h"
#include <sys/cdefs.h>

struct igmp_header
{
  u8 type;
  u8 code;
  u16 check;
  u32 var;
  u8 data[1500];
};

__BEGIN_DECLS

u8 *build_igmp_pkt(const u32 saddr, const u32 daddr, u16 ttl, u16 ipid, u8 tos, bool df,
    u8 *ipopt, int ipoptlen, u8 type, u8 code, const char *data, u16 datalen, u32 *packetlen);

int send_igmp_packet(int fd, const u32 saddr, const u32 daddr, int ttl, bool df, u8 *ipops, int ipoptlen,
    u16 ident, u8 tos, u8 type, u8 code, const char *data, u16 datalen, int fragscan);

__END_DECLS

#endif
