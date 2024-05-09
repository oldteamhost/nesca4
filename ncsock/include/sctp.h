/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef SCTP_HEADER
#define SCTP_HEADER

#include <netinet/in.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/cdefs.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "types.h"
#include "mt19937.h"
#include "../include/eth.h"
#include <bits/wordsize.h>

#define SCTP_HDR_LEN 12
#define SCTP_DATA               0x00
#define SCTP_INIT               0x01
#define SCTP_INIT_ACK           0x02
#define SCTP_SACK               0x03
#define SCTP_HEARTBEAT          0x04
#define SCTP_HEARTBEAT_ACK      0x05
#define SCTP_ABORT              0x06
#define SCTP_SHUTDOWN           0x07
#define SCTP_SHUTDOWN_ACK       0x08
#define SCTP_ERROR              0x09
#define SCTP_COOKIE_ECHO        0x0a
#define SCTP_COOKIE_ACK         0x0b
#define SCTP_ECNE               0x0c
#define SCTP_CWR                0x0d
#define SCTP_SHUTDOWN_COMPLETE  0x0e
#define SCTP_AUTH               0x0f /* RFC 4895 */
#define SCTP_ASCONF_ACK         0x80 /* RFC 5061 */
#define SCTP_PKTDROP            0x81 /* draft-stewart-sctp-pktdrprep-08 */
#define SCTP_PAD                0x84 /* RFC 4820 */
#define SCTP_FORWARD_TSN        0xc0 /* RFC 3758 */
#define SCTP_ASCONF             0xc1 /* RFC 5061 */
#define SCTP_TYPEFLAG_REPORT 1
#define SCTP_TYPEFLAG_SKIP   2

struct sctp_hdr
{
  u16 srcport; /* source port */
  u16 dstport; /* dest port*/
  u32 vtag;    /* verification tag */
  u32 check;   /* checksum */
};

struct sctp_chunk_hdr
{
  u8  type;
  u8  flags;
  u16 len;
};

struct sctp_chunk_hdr_init
{
  struct sctp_chunk_hdr chunkhdr;
  u32 itag;  /* Initiate Tag */
  u32 arwnd; /* Advertised Receiver Window Credit */
  u16 nos;   /* Number of Outbound Streams */
  u16 nis;   /* Number of Inbound Streams */
  u32 itsn;  /* Initial TSN */
};

struct sctp_chunk_header_cookie_echo { struct sctp_chunk_hdr chunkhdr; };

#define sctp_pack_chunk_header(hdr, _type, _flags, _len)                       \
  do {                                                                         \
    struct sctp_chunk_hdr *sctp_pack_chp = (struct sctp_chunk_hdr *)(hdr);     \
    sctp_pack_chp->type = _type;                                               \
    sctp_pack_chp->flags = _flags;                                             \
    sctp_pack_chp->len = htons(_len);                                          \
  } while (0)

#define sctp_pack_chunkhdr_cookie_echo(hdr, type, flags, length)               \
  do {                                                                         \
    struct sctp_chunk_header_cookie_echo *sctp_pack_chip =                     \
        (struct sctp_chunk_header_cookie_echo *)(hdr);                         \
    sctp_pack_chunk_header(sctp_pack_chip, type, flags, length);               \
  } while (0)

#define sctp_pack_chunkhdr_init(hdr, __type, __flags, __len, __itag, __arwnd,  \
                                __nos, __nis, __itsn)                          \
  do {                                                                         \
    struct sctp_chunk_hdr_init *sctp_pack_chip =                               \
        (struct sctp_chunk_hdr_init *)(hdr);                                   \
    sctp_pack_chunk_header(sctp_pack_chip, __type, __flags, __len);            \
    sctp_pack_chip->itag = htonl(__itag);                                      \
    sctp_pack_chip->arwnd = htonl(__arwnd);                                    \
    sctp_pack_chip->nos = htons(__nos);                                        \
    sctp_pack_chip->nis = htons(__nis);                                        \
    sctp_pack_chip->itsn = htonl(__itsn);                                      \
  } while (0)

__BEGIN_DECLS

u8 *sctp_build(u16 srcport, u16 dstport, u32 vtag, const char *chunks,
               int chunkslen, const char *data, u16 datalen, u32 *pktlen,
               bool adler32sum, bool badsum);
u8 *sctp4_build_pkt(u32 src, u32 dst, int ttl, u16 ipid, u8 tos, bool df,
                    u8 *ipopt, int ipoptlen, u16 srcport, u16 dstport, u32 vtag,
                    char *chunks, int chunkslen, const char *data, u16 datalen,
                    u32 *pktlen, bool adler32sum, bool badsum);
u8 *sctp6_build_pkt(const struct in6_addr *src, const struct in6_addr *dst,
                    u8 tc, u32 flowlabel, u8 hoplimit, u16 srcport, u16 dstport,
                    u32 vtag, char *chunks, int chunkslen, const char *data,
                    u16 datalen, u32 *pktlen, bool adler32sum, bool badsum);
int sctp4_send_pkt(struct ethtmp *eth, int fd, const u32 src, const u32 dst,
                   int ttl, bool df, u8 *ipops, int ipoptlen, u16 srcport,
                   u16 dstport, char *chunks, int chunkslen, u32 vtag,
                   const char *data, u16 datalen, int mtu, bool adler32sum,
                   bool badsum);

__END_DECLS


#endif

