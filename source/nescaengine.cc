/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "../include/nescaengine.h"
#include "../ncsock/include/strbase.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <netinet/in.h>
#include <limits.h>
#include "../ncsock/include/eth.h"
#include "../ncsock/include/sctp.h"
#include "../ncsock/libdnet/include/ip6.h"
#include <chrono>
#include <sys/socket.h>
#include <unistd.h>

u8 *tcp_probe(NESCADATA *n, const ipnesca_t dst, u16 dport, u8 type, u32 *packetlen)
{
  u8 *res = NULL;
  bool df = true;
  u8 tcpflags = 0;
  u16 destport;

  switch (type) {
    case TCP_PING_ACK:
      tcpflags = TH_ACK;
      destport = n->ack_dest_port;
      break;
    case TCP_PING_SYN:
      tcpflags = TH_SYN;
      destport = n->syn_dest_port;
      break;
    default:
      tcpflags = n->tcpflags;
      destport = dport;
      break;
  }

  if (!n->customsport)
    n->sport = generate_rare_port();
  if (!n->customttl)
    n->ttl = generate_random_u32(64, 121);

  if (n->frag_mtu > 0)
    df = false;

  res = build_tcp_pkt(n->src, dst, n->ttl, random_u16(), 0, df,
      n->ip_options, n->ipoptslen, n->sport, destport, random_u32(),
      0, 0, tcpflags, n->windowlen, 0, NULL, 0, n->pd.data,
      n->pd.datalen, packetlen, n->badsum);

  return res;
}

u8 *icmp_probe(NESCADATA *n, const ipnesca_t dst, u8 type, u32 *packetlen)
{
  u8 *res = NULL;
  bool df = true;
  u8 icmptype;

  if (!n->customttl)
    n->ttl = generate_random_u32(64, 121);

  switch (type) {
    case ICMP_PING_ECHO:
      icmptype = ICMP_ECHO;
      break;
    case ICMP_PING_INFO:
      icmptype = ICMP_INFO_REQUEST;
      break;
    case ICMP_PING_TIME:
      icmptype = ICMP_TIMESTAMP;
      break;
  }

  if (n->frag_mtu > 0)
    df = false;

  res = build_icmp_pkt(n->src, dst, n->ttl, random_u16(), 0, df,
      n->ip_options, n->ipoptslen, random_u16(), random_u16(),
      icmptype, 0, n->pd.data, n->pd.datalen, packetlen, n->badsum);

  return res;
}

u8 *sctp_probe(NESCADATA *n, const ipnesca_t dst, u16 dport, u8 type, u32 *packetlen)
{
  u8 *res = NULL;
  bool df = true;
  char *chunk = NULL;
  int chunklen = 0;
  u32 vtag = 0;

  if (!n->customsport)
    n->sport = generate_rare_port();
  if (!n->customttl)
    n->ttl = generate_random_u32(64, 121);

  switch (type) {
    case SCTP_INIT_PING:
      dport = n->sctpport;
    case SCTP_INIT_SCAN:
      chunklen = sizeof(struct sctp_chunk_header_init);
      chunk = (char*)malloc(chunklen);
      sctp_pack_chunkhdr_init(chunk, 0x01, 0, chunklen, random_u32(), 32768, 10, 2048, random_u32());
      break;
    case SCTP_COOKIE_SCAN:
      chunklen = sizeof(struct sctp_chunk_header_cookie_echo) + 4;
      chunk = (char*)malloc(chunklen);
      *((u32*)((char*)chunk + sizeof(struct sctp_chunk_header_cookie_echo))) = random_u32();
      sctp_pack_chunkhdr_cookie_echo(chunk, 0x0a, 0, chunklen);
      vtag = random_u32();
      break;
  }

  if (n->frag_mtu > 0)
    df = false;

  res = build_sctp_pkt(n->src, dst, n->ttl,
    random_u16(), 0, df, n->ip_options, n->ipoptslen, n->sport, dport, vtag, chunk,
    chunklen, n->pd.data, n->pd.datalen, packetlen, true, n->badsum);

  if (chunk)
    free(chunk);
  return res;
}

u8 *udp_probe(NESCADATA *n, const ipnesca_t dst, u16 dport, u8 type, u32 *packetlen)
{
  u8 *res = NULL;
  bool df = true;

  if (type == UDP_PING)
    dport = n->udpport;

  if (!n->customsport)
    n->sport = generate_rare_port();
  if (!n->customttl)
    n->ttl = generate_random_u32(64, 121);

  if (n->frag_mtu > 0)
    df = false;

  res = build_udp_pkt(n->src, dst, n->ttl, random_u16(), 0, df, n->ip_options, n->ipoptslen,
      n->sport, dport, n->pd.data, n->pd.datalen, packetlen, n->badsum);

  return res;
}

#include "../ncsock/include/eth.h"
#include "../ncsock/include/arp.h"
#include "../ncsock/include/utils.h"
u8 *arp_probe(NESCADATA *n, const ipnesca_t dst, u8 type, u32 *packetlen)
{
  u8 *res = NULL;
  eth_addr_t src;
  ip_addreth_t daddr, saddr;
  eth_addr_t dest, dest1;

  /* mac dest eth header*/
  memcpy(dest.data, ETH_ADDR_BROADCAST, ETH_ADDR_LEN);
  /* mac dest arp header*/
  memcpy(dest1.data, "\x00\x00\x00\x00\x00\x00", ETH_ADDR_LEN);
  /* mac source */
  maceth(n->srcmac, &src);
  /* ip source */
  memcpy(saddr.data, &n->src, sizeof(saddr.data));
  /* ip dest */
  memcpy(daddr.data, &dst, sizeof(daddr.data));

  res = build_arp_pkt(src, dest, ARP_HRD_ETH, ARP_PRO_IP, ETH_ADDR_LEN, _IP_ADDR_LEN,
    ARP_OP_REQUEST, src, saddr, dest1, daddr, packetlen);

  return res;
}

int nescasocket(void)
{
  return (socket(AF_INET, SOCK_RAW, IPPROTO_RAW));
}

bool readping(NESCADATA *n, const ipnesca_t dst, u8 *packet, u8 type)
{
  u8 icmptype;
  u8 tcpflags = 0;
  struct tcp_header *tcp;
  struct icmp4_header *icmp;

  if (type == ICMP_PING_ECHO || type == ICMP_PING_TIME || type == ICMP_PING_INFO) {
    icmp = (struct icmp4_header *)(packet + sizeof(struct eth_header) + sizeof(struct ip_header));
    icmptype = icmp->type;

    if (type == ICMP_PING_TIME && icmptype == ICMP_TIMESTAMPREPLY)
      return true;
    if (type == ICMP_PING_ECHO && icmptype == ICMP_ECHOREPLY)
      return true;
    if (type == ICMP_PING_INFO && icmptype == ICMP_INFO_REPLY)
      return true;
  }

  if (type == TCP_PING_ACK || type == TCP_PING_SYN) {
    tcp = (struct tcp_header*)(packet + sizeof(struct eth_header) + sizeof(struct ip_header));
    tcpflags = tcp->th_flags;

    if (type == TCP_PING_ACK && tcpflags == TH_RST)
      return true;
    if (type == TCP_PING_SYN && tcpflags != 0)
      return true;
  }

  if (type == SCTP_INIT_PING) {
    struct sctp_header *sctp = (struct sctp_header*)(packet + sizeof(struct eth_header) + sizeof(struct ip_header));
    if (sctp->sport)
      return true;
  }

  if (type == UDP_PING) {
    struct ip_header *ip = (struct ip_header*)(packet + sizeof(struct eth_header));
    if (ip->protocol == IPPROTO_ICMP) {
      struct icmp4_header *icmp = (struct icmp4_header*)(packet + sizeof(struct eth_header) + sizeof(struct ip_header));
      if (icmp->type == 3 && icmp->code == 3)
        return true;
    }
    if (ip->protocol == IPPROTO_UDP)
      return true;
  }

  return false;
}

#ifndef SCTP_INIT
  #define SCTP_INIT 0x01
#endif
#ifndef SCTP_INIT_ACK
  #define SCTP_INIT_ACK 0x02
#endif
#ifndef SCTP_ABORT
  #define SCTP_ABORT 0x06
#endif

int readscan(const ipnesca_t dst, u8 *packet, u8 type)
{
  if (type == SCTP_INIT_SCAN || type == SCTP_COOKIE_SCAN || type == SCTP_INIT_PING) {
    const struct sctp_header *sctp = (struct sctp_header*)(packet + sizeof(struct eth_header) + sizeof(struct ip_header));
    const struct sctp_chunk_header *chunk = (struct sctp_chunk_header*)((u8*)sctp + 12);

    if (type == SCTP_INIT_SCAN) {
      if (chunk->type == SCTP_INIT_ACK)
        return PORT_OPEN;
      else if (chunk->type == SCTP_ABORT)
        return PORT_CLOSED;
    }
    if (type == SCTP_COOKIE_SCAN)
      if (chunk->type == SCTP_ABORT)
        return PORT_CLOSED;
  }
  else if (type == UDP_SCAN) {
    struct ip_header *ip = (struct ip_header*)(packet + sizeof(struct eth_header));
    if (ip->protocol == IPPROTO_ICMP) {
      struct icmp4_header *icmp = (struct icmp4_header*)(packet + sizeof(struct eth_header) + sizeof(struct ip_header));
      if (icmp->type == 3 && icmp->code == 3)
        return PORT_CLOSED;
    }
    else if (ip->protocol == IPPROTO_UDP) /* its real? */
      return PORT_OPEN;
    else
      return PORT_FILTER;
  }
  else {
    const struct tcp_header *tcp;
    tcp = (struct tcp_header*)(packet + sizeof(struct eth_header) + sizeof(struct ip_header));

    switch (type) {
      case TCP_MAIMON_SCAN: {
        if (tcp->th_flags == 0x04)
          return PORT_CLOSED;
        return PORT_OPEN_OR_FILTER;
      }
      case TCP_PSH_SCAN:
      case TCP_FIN_SCAN:
      case TCP_XMAS_SCAN:
      case TCP_NULL_SCAN: {
        if (tcp->th_flags == 0x04)
          return PORT_CLOSED;
        return PORT_OPEN;
      }
      case TCP_WINDOW_SCAN: {
        if (tcp->th_flags == 0x04) {
          if (tcp->th_win > 0)
            return PORT_OPEN;
          else
            return PORT_CLOSED;
          return PORT_FILTER;
        }
      }
      case TCP_ACK_SCAN: {
        if (tcp->th_flags == 0x04)
          return PORT_NO_FILTER;
        return PORT_FILTER;
      }
      default: {
        switch (tcp->th_flags) {
          case 0x12:
            return PORT_OPEN;
          case 0x1A:
            return PORT_OPEN;
          case 0x04:
            return PORT_CLOSED;
          default:
            return PORT_FILTER;
        }
      }
    }
  }

  return PORT_ERROR;
}

u8* recvpacket(NESCADATA *n, ipnesca_t dst, u8 type, int timeout_ms, double *rtt)
{
  struct readfiler rf;
  struct sockaddr_in dest;
  int read = -1;
  u8 *res;
  u8 proto = 0;
  u8 secondproto = 0;

  switch (type) {
    case ICMP_PING_ECHO:
    case ICMP_PING_INFO:
    case ICMP_PING_TIME:
      proto = IPPROTO_ICMP;
      break;
    case SCTP_INIT_SCAN:
    case SCTP_INIT_PING:
    case SCTP_COOKIE_SCAN:
      proto = IPPROTO_SCTP;
      break;
    case UDP_PING:
    case UDP_SCAN:
      proto = IPPROTO_UDP;
      secondproto = IPPROTO_ICMP;
      break;
    default:
      proto = IPPROTO_TCP;
      break;
  }

  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = dst;
  rf.protocol = proto;
  rf.second_protocol = secondproto;
  rf.ip = (struct sockaddr_storage*)&dest;

  res = (u8*)calloc(RECV_BUFFER_SIZE, sizeof(u8));
  if (!res)
    return NULL;

  auto start_time = std::chrono::high_resolution_clock::now();
  read = read_packet(&rf, timeout_ms, &res);
  auto end_time = std::chrono::high_resolution_clock::now();
  if (read == -1) {
    free(res);
    return NULL;
  }
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

  *rtt = duration.count() / 1000.0;
  return res;
}

double nescaping(NESCADATA *n, ipnesca_t dst, u8 type)
{
  ssize_t send;
  double res;
  u8 *packet;
  int fd = 0;

  fd = nescasocket();
  if (fd == -1)
    return -1;
  send = sendprobe(fd, n, dst, 0, type);
  close(fd);
  if (send == -1)
    return -1;
  packet = recvpacket(n, dst, type, n->ping_timeout, &res);
  if (!packet)
    return -1;
  if (!readping(n, dst, packet, type))
    return -1;

  return res;
}

ssize_t sendprobe(int fd, NESCADATA *n, const ipnesca_t dst,
    u16 dport, u8 type)
{
  struct sockaddr_in dest;
  u32 packetlen;
  u8 *packet;

  dest.sin_addr.s_addr = dst;
  dest.sin_family = AF_INET;

  switch (type) {
    case ICMP_PING_ECHO:
    case ICMP_PING_INFO:
    case ICMP_PING_TIME:
      packet = icmp_probe(n, dst, type, &packetlen);
      break;
    case SCTP_COOKIE_SCAN:
    case SCTP_INIT_SCAN:
    case SCTP_INIT_PING:
      packet = sctp_probe(n, dst, dport, type, &packetlen);
      break;
    case UDP_PING:
    case UDP_SCAN:
      packet = udp_probe(n, dst, dport, type, &packetlen);
      break;
    case ARP_PING:
      packet = arp_probe(n, dst, type, &packetlen);
      break;
    default:
      packet = tcp_probe(n, dst, dport, type, &packetlen);
      break;
  }

  return (send_ip4_packet(fd, &dest, n->frag_mtu, packet, packetlen));
}
