/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#ifndef NESCATESTING_H
#define NESCATESTING_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "../ncsock/include/ip.h"
#include "../ncsock/include/tcp.h"
#include "../ncsock/include/udp.h"
#include "../ncsock/include/icmp.h"
#include "../ncsock/include/igmp.h"

/* language */
#define MAIN        "main"
#define DELAY       "delay"
#define IPHEADER    "ip_header"
#define TCPHEADER   "tcp_header"
#define ICMPHEADER  "icmp_header"
#define IGMPHEADER  "igmp_header"
#define UDPHEADER   "udp_header"
#define DELAY_TOKEN_2          2
#define IPHEADER_TOKEN_4       4
#define TCPHEADER_TOKEN_5      5
#define ICMPHEADER_TOKEN_6     6
#define IGMPHEADER_TOKEN_7     7
#define UDPHEADER_TOKEN_8      8
#define MAIN_TOKEN_9           9
#define VALUE_TYPE_CUSTOM 1
#define VALUE_TYPE_RANDOM 2
#define VALUE_TYPE_AUTO   3
#define VALUE_TYPE_NONE   4
#define VALUE_AUTO        "auto"
#define VALUE_RANDOM      "random"
#define VALUE_NONE        "none"
#define DELAY_LINE "WAIT"
#define SEND_PACKET_LINE ">>[]"
#define RECV_PACKET_LINE "[]<<"
#define WHILE_LINE "while"
#define KEY_PROTOCOL "p"
#define KEY_PROTOCOL_1 "proto"
#define KEY_PROTOCOL_2 "protocol"
#define KEY_COUNT "c"
#define KEY_COUNT_1 "n"
#define KEY_COUNT_2 "num"
#define KEY_COUNT_3 "count"
#define KEY_DELAY "d"
#define KEY_DELAY_1 "w"
#define KEY_DELAY_2 "delay"
#define KEY_DELAY_3 "wait"
#define KEY_IPHEADER "ip"
#define KEY_TCPHEADER "tcp"
#define KEY_UDPHEADER "udp"
#define KEY_ICMPHEADER "icmp"
#define KEY_IGMPHEADER "igmp"
#define DELAY_TOKEN 1
#define SEND_PACKET_TOKEN 2
#define RECV_PACKET_TOKEN 3
#define WHILE_TOKEN 4

/* preprocessor */
#define INCLUDE  1
#define TYPE_1   "include"

struct headerpreset
{
  std::string iphdr;
  std::string tcphdr;
  std::string icmphdr;
  std::string igmphdr;
  std::string udphdr;
};

struct headerline
{
  std::string key;
  std::string value;
  int valuetype;
};

struct delayline
{
  int numpackage;
  long long delay;
};

struct delaypreset
{
  std::vector<delayline> delays;
};

struct blockpreset
{
  int blocktype;
  std::string keyword;
  std::vector<std::string> lines;
  size_t end, start;
};

struct whileblock
{
  size_t i;
  size_t start, end;
};

struct sendpktline
{
  size_t count;
  std::string protocol;
  std::string delay;
  struct headerpreset hp;
};

struct temppayload
{
  const char *data;
  u16 datalen;
};

struct temp_ip_header
{
  int ihl;       /* header length */
  int version;   /* ip proto version */
  int tos;       /* type of service */
  int tot_len;   /* total length */
  int ident;     /* identificator */
  int frag_off;  /* fragment offset */
  int ttl;       /* time to live */
  int protocol;  /* see addr.h */
  int check;     /* 16 bit checksum */
  u32 saddr;     /* source ip address */
  u32 daddr;     /* dest ip address */

  u8 *ipopt;
  int ipoptlen;

  int mtu;
};

struct temp_tcp_header
{
  int th_sport;  /* Source port. */
  int th_dport;  /* Destination port. */
  u32 th_seq;    /* Sequence number. */
  u32 th_ack;    /* Acknowledgement number. */
  int th_off;    /* Data offset. */
  int th_x2;     /* (unused). */
  int th_win;    /* Window. */
  int th_sum;    /* Checksum. */
  int th_urp;    /* Urgent pointer. */
  u8  th_flags;  /* TCP flags. */
  struct temppayload tp;

};

struct temp_icmp4_header
{
  int type;
  int code;
  int checksum;
  int id;
  int seq;
  struct temppayload tp;
};

struct temp_udp_header
{
  int uh_sport; /* source port */
  int uh_dport; /* destination port */
  int ulen;     /* udp length (including header) */
  int check;    /* udp checksum */
  struct temppayload tp;
};

struct temp_igmp_header
{
  u8 type;
  int code;
  int check;
  u32 var;
  struct temppayload tp;
};

class _interdata_
{
  public:
    std::string path;
    size_t lines, characters;
    std::vector<std::string> data;
    struct blockpreset dotstart;

    std::unordered_map<std::string, delaypreset> delay_presets;
    std::unordered_map<std::string, temp_ip_header> iphdr_presets;
    std::unordered_map<std::string, temp_tcp_header> tcphdr_presets;
    std::unordered_map<std::string, temp_icmp4_header> icmphdr_presets;
    std::unordered_map<std::string, temp_udp_header> udphdr_presets;
    std::unordered_map<std::string, temp_igmp_header> igmphdr_presets;

};

#define REMOVE_WHITESPACE(str)                                               \
  do {                                                                       \
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end()); \
  } while(0)

class _importfile_
{
  private:
    _interdata_ *id;

  public:
    _importfile_(const std::string& path, _interdata_ *i);
    void display_fileinfo(void);
    void loadfile(void);
};

class _preprocessor_
{
  private:
    std::vector<size_t> playlines;
    _interdata_ *id;

  public:
    void getplaylines(void);
    int  check_directive(size_t line);
    void execute_include(size_t line);
    void execute_directives(void);
    void preprocessor(_interdata_ *i);
};

class _scanner_
{
  private:
    _interdata_ *id;

  public:
    int    get_token_type_block(size_t line);
    std::string get_type_block(int type);
    struct blockpreset parseblock(size_t line);

    struct delayline parsedelayline(std::string newline);

    void   get_delay_preset(struct blockpreset *bp);
    void   get_ip_header(struct blockpreset *bp);
    void   get_tcp_header(struct blockpreset *bp);
    void   get_icmp_header(struct blockpreset *bp);
    void   get_udp_header(struct blockpreset *bp);
    void   get_igmp_header(struct blockpreset *bp);
    void   getall(void);
    void   scanner(_interdata_ *i);
};

class _interpreter_ : public _scanner_
{
  private:
    _interdata_ *id;
    bool verbose = false;

  public:
    #define REMOVE_BRACKETS(str)                                        \
      do {                                                              \
        str.erase(std::remove(str.begin(), str.end(), '('), str.end()); \
        str.erase(std::remove(str.begin(), str.end(), ')'), str.end()); \
      } while (0)
    int  get_type_active(const std::string& newline);
    void interverbose(std::string element, std::string message);
    struct sendpktline get_send_options(const std::string& line);
    void checkoptions(u8 protocol, struct sendpktline *spl);
    u8*  sendip(int fd, struct sendpktline *spl, u32 *plen, struct sockaddr_in *dst);
    u8*  sendtcp(int fd, struct sendpktline *spl, u32 *plen, struct sockaddr_in *dst);
    u8*  sendudp(int fd, struct sendpktline *spl, u32 *plen, struct sockaddr_in *dst);
    u8*  sendicmp(int fd, struct sendpktline *spl, u32 *plen, u16 seq, struct sockaddr_in *dst);
    u8*  sendigmp(int fd, struct sendpktline *spl, u32 *plen, struct sockaddr_in *dst);
    void sendpacket(u8 proto, int fd, struct sendpktline *spl);
    void sendprobe(int fd, struct headerline hl);
    void execdelay();

    void interpreter(_interdata_ *i, bool verbose);
};

#endif

