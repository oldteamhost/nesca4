/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/igmp.h"

#ifndef MIN
  #define MIN(a,b) ((a) <= (b) ? (a) : (b))
#endif

u8 *build_igmp_pkt(const u32 saddr, const u32 daddr, u16 ttl, u16 ipid, u8 tos, bool df,
    u8 *ipopt, int ipoptlen, u8 type, u8 code, const char *data, u16 datalen, u32 *packetlen, bool badsum)
{
  struct igmp_header igmp;
  u32 *datastart = (u32 *)igmp.data;
  int dlen = sizeof(igmp.data);
  int igmplen = 0;
  char *pkt = (char *)&igmp;

  igmp.type = type;
  igmp.code = code;

  switch (type) {
    case 0x11:
    case 0x12:
    case 0x16:
    case 0x17:
    case 0x22:
      igmplen = 8;
      break;
  }

  if (datalen > 0) {
    igmplen += MIN(dlen, datalen);
    if (data == NULL)
      memset(datastart, 0, MIN(dlen, datalen));
    else
      memcpy(datastart, data, MIN(dlen, datalen));
  }

  igmp.check = 0;
  igmp.check = in_cksum((unsigned short *) pkt, igmplen);

  if (badsum)
    --igmp.check;

  return build_ip_pkt(saddr, daddr, IPPROTO_IGMP, ttl, ipid, tos, df, ipopt, ipoptlen, pkt, igmplen, packetlen);
}
