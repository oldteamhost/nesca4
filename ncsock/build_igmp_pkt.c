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
  int dlen = 0, igmplen = 0;
  u32 *datastart;
  char *pkt;

  datastart = (u32*)igmp.data;
  dlen = sizeof(igmp.data);
  pkt = (char *)&igmp;

  igmp.type = type;
  igmp.code = code;

  switch (type) {
    case IGMP_HOST_MEMBERSHIP_QUERY:
    case IGMP_v1_HOST_MEMBERSHIP_REPORT:
    case IGMP_v2_HOST_MEMBERSHIP_REPORT:
    case IGMP_HOST_LEAVE_MESSAGE:
    case IGMP_v3_HOST_MEMBERSHIP_REPORT:
      igmplen = 8;
      break;
  }

  if (datalen > 0) {
    igmplen += MIN(dlen, datalen);
    if (!data)
      memset(datastart, 0, MIN(dlen, datalen));
    else
      memcpy(datastart, data, MIN(dlen, datalen));
  }

  igmp.check = 0;
  igmp.check = in_cksum((u16*)pkt, igmplen);

  if (badsum)
    --igmp.check;

  return build_ip_pkt(saddr, daddr, IPPROTO_IGMP, ttl,
      ipid, tos, df, ipopt, ipoptlen, pkt, igmplen, packetlen);
}
