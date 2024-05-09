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

u8 *icmp4_build_pkt(const u32 src, const u32 dst, int ttl, u16 ipid, u8 tos,
                    bool df, u8 *ipopt, int ipoptlen, u16 seq, u16 id, u8 type,
                    u8 code, const char *data, u16 datalen, u32 *pktlen,
                    bool badsum)
{
  struct icmp4_hdr icmphdr;
  int dlen = 0, icmplen = 0;
  u8 *datastart;
  char *ping;

  datastart = icmphdr.data;
  dlen = sizeof(icmphdr.data);
  ping = (char*)&icmphdr;

  icmphdr.type = type;
  icmphdr.code = code;

  if (type == 8)
    icmplen = 8;
  else if (type == 13 && code == 0) {
    icmplen = 20;
    memset(datastart, 0, 12);
    datastart += 12;
    dlen -= 12;
  }
  else if (type == 17 && code == 0) {
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
  icmphdr.check = 0;
  icmphdr.check = in_check((u16*)ping, icmplen);

  if (badsum)
    --icmphdr.check;

  return ip4_build(src, dst, IPPROTO_ICMP, ttl,
      ipid, tos, df, ipopt, ipoptlen, ping, icmplen, pktlen);
}
