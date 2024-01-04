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
#include "../libdnet/include/ip6.h"
#include "../libdnet/include/eth.h"
#include "../libdnet/include/ip.h"
#include <bits/wordsize.h>

#define SCTP_HDR_LEN 12

__BEGIN_DECLS

struct sctp_header
{
  u16 sport; /* source port */
  u16 dport; /* dest port*/
  u32 vtag;  /* verification tag */
  u32 check; /* checksum */
};

struct sctp_chunk_header
{
  u8  type;
  u8  flags;
  u16 len;
};

#define sctp_pack_chunk_header(hdr, _type, _flags, _len) do {                  \
  struct sctp_chunk_header *sctp_pack_chp = (struct sctp_chunk_header*)(hdr);  \
  sctp_pack_chp->type = _type;                                                 \
  sctp_pack_chp->flags = _flags;                                               \
  sctp_pack_chp->len = htons(_len);                                            \
} while (0)

struct sctp_chunk_header_init
{
  struct sctp_chunk_header chunkhdr;
  u32 itag;  /* Initiate Tag */
  u32 arwnd; /* Advertised Receiver Window Credit */
  u16 nos;   /* Number of Outbound Streams */
  u16 nis;   /* Number of Inbound Streams */
  u32 itsn;  /* Initial TSN */
};

#define sctp_pack_chunkhdr_init(hdr, __type, __flags, __len, __itag, __arwnd, __nos,     \
    __nis, __itsn) do {                                                                  \
  struct sctp_chunk_header_init *sctp_pack_chip =                                        \
      (struct sctp_chunk_header_init*)(hdr);                                             \
  sctp_pack_chunk_header(sctp_pack_chip, __type, __flags, __len);                        \
  sctp_pack_chip->itag = htonl(__itag);                                                  \
  sctp_pack_chip->arwnd = htonl(__arwnd);                                                \
  sctp_pack_chip->nos = htons(__nos);                                                    \
  sctp_pack_chip->nis = htons(__nis);                                                    \
  sctp_pack_chip->itsn = htonl(__itsn);                                                  \
} while (0)

u8 *build_sctp(u16 sport, u16 dport, u32 vtag, const char *chunks,
    int chunkslen, const char *data, u16 datalen, u32 *packetlen,
    bool adler32sum, bool badsum);

u8 *build_sctp_pkt(u32 saddr, u32 daddr, int ttl, u16 ipid, u8 tos,
    bool df, u8 *ipopt, int ipoptlen, u16 sport, u16 dport, u32 vtag,
    char *chunks, int chunkslen, const char *data, u16 datalen,
    u32 *packetlen, bool adler32sum, bool badsum);

u8 *build_sctp6_pkt(const struct in6_addr *source, const struct in6_addr *victim,
    u8 tc, u32 flowlabel, u8 hoplimit, u16 sport, u16 dport,
    u32 vtag, char *chunks, int chunkslen, const char *data,
    u16 datalen, u32 *packetlen, bool adler32sum, bool badsum);

__END_DECLS


#endif

