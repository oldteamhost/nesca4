/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/icmp.h"
#include "include/igmp.h"
#include "include/readpkt.h"
#include <netinet/if_ether.h>
#include <netinet/in.h>

struct ip_header* ext_iphdr(u8 *buf)
{
  struct ip_header *iphdr;
  iphdr = (struct ip_header*)(buf + sizeof(struct ethhdr));
  return iphdr;
}

struct tcp_header* ext_tcphdr(u8 *buf)
{
  struct tcp_header *tcphdr;
  tcphdr = (struct tcp_header*)(buf + sizeof(struct ethhdr) + sizeof(struct ip_header));
  return tcphdr;
}

struct udp_header* ext_udphdr(u8 *buf)
{
  struct udp_header *udphdr;
  udphdr = (struct udp_header *)(buf + sizeof(struct ethhdr) + sizeof(struct ip_header));
  return udphdr;
}

struct icmp4_header* ext_icmphdr(u8 *buf)
{
  struct icmp4_header *icmphdr;
  icmphdr = (struct icmp4_header *)(buf + sizeof(struct ethhdr) + sizeof(struct ip_header));
  return icmphdr;
}

struct igmp_header* ext_igmphdr(u8 *buf)
{
  struct igmp_header *igmphdr;
  igmphdr = (struct igmp_header *)(buf + sizeof(struct ethhdr) + sizeof(struct ip_header));
  return igmphdr;
}

int ext_payload(u8 *buf, u8 *rbuf)
{
  int hdrsize, paylsize = -1;
  struct ethhdr *eth_header = (struct ethhdr *)buf;

  if (ntohs(eth_header->h_proto) == ETH_P_IP) {
    struct ip_header *iphdr = (struct ip_header*)(buf + sizeof(struct ethhdr));
    if (iphdr->protocol == IPPROTO_TCP) {
      struct tcp_header *tcphdr = (struct tcp_header *)(buf + sizeof(struct ethhdr) + sizeof(struct ip_header));
      hdrsize = tcphdr->th_x2;
      paylsize = ntohs(iphdr->tot_len) - (sizeof(struct ip_header) + hdrsize * 4);
      memcpy(rbuf, buf + sizeof(struct ethhdr) + sizeof(struct ip_header) + hdrsize * 4, paylsize);
    }
    else if (iphdr->protocol == IPPROTO_UDP) {
      struct udp_header *udphdr = (struct udp_header*)(buf + sizeof(struct ethhdr) + sizeof(struct ip_header));
      hdrsize = sizeof(struct udp_header);
      paylsize = ntohs(udphdr->ulen) - hdrsize;
      memcpy(rbuf, buf + sizeof(struct ethhdr) + sizeof(struct ip_header) + hdrsize, paylsize);
    }
    else if (iphdr->protocol == IPPROTO_ICMP) {
      struct icmp4_header *icmphdr = (struct icmp4_header*)(buf + sizeof(struct ethhdr) + sizeof(struct ip_header));
      hdrsize = sizeof(struct icmp4_header);
      paylsize = ntohs(iphdr->tot_len) - (sizeof(struct ip_header) + hdrsize);
      memcpy(rbuf, buf + sizeof(struct ethhdr) + sizeof(struct ip_header), paylsize);
    }
  }

  return paylsize;
}
