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

#define IGMP_HOST_MEMBERSHIP_QUERY      0x11 /* membership query         */
#define IGMP_v1_HOST_MEMBERSHIP_REPORT  0x12 /* Ver. 1 membership report */
#define IGMP_DVMRP                      0x13 /* DVMRP routing message    */
#define IGMP_PIM                        0x14 /* PIMv1 message (historic) */
#define IGMP_v2_HOST_MEMBERSHIP_REPORT  0x16 /* Ver. 2 membership report */
#define IGMP_HOST_LEAVE_MESSAGE         0x17 /* Leave-group message     */
#define IGMP_MTRACE_REPLY               0x1e /* mtrace(8) reply */
#define IGMP_MTRACE_QUERY               0x1f /* mtrace(8) probe */
#define IGMP_v3_HOST_MEMBERSHIP_REPORT  0x22 /* Ver. 3 membership report */
#define IGMP_DO_NOTHING                 0 /* don't send a record */
#define IGMP_MODE_IS_INCLUDE            1 /* MODE_IN */
#define IGMP_MODE_IS_EXCLUDE            2 /* MODE_EX */
#define IGMP_CHANGE_TO_INCLUDE_MODE     3 /* TO_IN */
#define IGMP_CHANGE_TO_EXCLUDE_MODE     4 /* TO_EX */
#define IGMP_ALLOW_NEW_SOURCES          5 /* ALLOW_NEW */
#define IGMP_BLOCK_OLD_SOURCES          6 /* BLOCK_OLD */
#define IGMP_V3_QUERY_MINLEN 12
#define IGMP_V3_GENERAL_QUERY       1
#define IGMP_V3_GROUP_QUERY         2
#define IGMP_V3_GROUP_SOURCE_QUERY  3

struct igmp_hdr
{
  u8 type;
  u8 code;
  u16 check;
  u32 var;
  u8 data[1500];
};

#define IGMP_EXP(x)             (((x) >> 4) & 0x07)
#define IGMP_MANT(x)            ((x) & 0x0f)
#define IGMP_QRESV(x)           (((x) >> 4) & 0x0f)
#define IGMP_SFLAG(x)           (((x) >> 3) & 0x01)
#define IGMP_QRV(x)             ((x) & 0x07)

__BEGIN_DECLS

u8 *igmp4_build_pkt(const u32 src, const u32 dst, u16 ttl, u16 ipid, u8 tos,
                   bool df, u8 *ipopt, int ipoptlen, u8 type, u8 code,
                   const char *data, u16 datalen, u32 *pktlen, bool badsum);
int igmp4_send_pkt(struct ethtmp *eth, int fd, const u32 src, const u32 dst,
                   int ttl, bool df, u8 *ipops, int ipoptlen, u16 ipid, u8 tos,
                   u8 type, u8 code, const char *data, u16 datalen, int mtu,
                   bool badsum);

__END_DECLS

#endif
