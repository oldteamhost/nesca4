/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/icmp.h"
#include "include/ip.h"

#ifndef MIN
  #define MIN(a,b) ((a) <= (b) ? (a) : (b))
#endif

u8 *build_icmp_pkt(const u32 saddr, const u32 daddr, int ttl, u16 ipid, u8 tos, bool df, u8 *ipopt,
    int ipoptlen, u16 seq, u16 id, u8 ptype, u8 pcode, const char *data, u16 datalen, u32 *plen, bool badsum)
{
  struct icmp4_header icmphdr;
  int dlen = 0, icmplen = 0;
  u8 *datastart;
  char *ping;

  datastart = icmphdr.data;
  dlen = sizeof(icmphdr.data);
  ping = (char*)&icmphdr;

  icmphdr.type = ptype;
  icmphdr.code = pcode;

  if (ptype == 8)
    icmplen = 8;
  else if (ptype == 13 && pcode == 0) {
    icmplen = 20;
    memset(datastart, 0, 12);
    datastart += 12;
    dlen -= 12;
  }
  else if (ptype == 17 && pcode == 0) {
    icmplen = 12;
    memset(datastart, 0, 4);
    datastart += 4;
    dlen -= 4;
  }

  if (datalen > 0) {
    icmplen += MIN(dlen, datalen);
    if (!data)
      memset(datastart, 0, MIN(dlen, datalen));
    else
      memcpy(datastart, data, MIN(dlen, datalen));
  }

  icmphdr.id = htons(id);
  icmphdr.seq = htons(seq);
  icmphdr.checksum = 0;
  icmphdr.checksum = in_cksum((u16*)ping, icmplen);

  if (badsum)
    --icmphdr.checksum;

  return build_ip_pkt(saddr, daddr, IPPROTO_ICMP, ttl,
      ipid, tos, df, ipopt, ipoptlen, ping, icmplen, plen);
}
