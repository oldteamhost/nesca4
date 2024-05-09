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

struct ip4_hdr* ext_iphdr(u8 *buf)
{
  struct ip4_hdr *iphdr;
  iphdr = (struct ip4_hdr*)(buf + sizeof(struct ethhdr));
  return iphdr;
}

struct tcp_hdr* ext_tcphdr(u8 *buf)
{
  struct tcp_hdr *tcphdr;
  tcphdr = (struct tcp_hdr*)(buf + sizeof(struct ethhdr) + sizeof(struct ip4_hdr));
  return tcphdr;
}

struct udp_hdr* ext_udphdr(u8 *buf)
{
  struct udp_hdr *udphdr;
  udphdr = (struct udp_hdr *)(buf + sizeof(struct ethhdr) + sizeof(struct ip4_hdr));
  return udphdr;
}

struct icmp4_hdr* ext_icmphdr(u8 *buf)
{
  struct icmp4_hdr *icmphdr;
  icmphdr = (struct icmp4_hdr *)(buf + sizeof(struct ethhdr) + sizeof(struct ip4_hdr));
  return icmphdr;
}

struct igmp_hdr* ext_igmphdr(u8 *buf)
{
  struct igmp_hdr *igmphdr;
  igmphdr = (struct igmp_hdr *)(buf + sizeof(struct ethhdr) + sizeof(struct ip4_hdr));
  return igmphdr;
}

int ext_payload(u8 *buf, u8 *rbuf)
{
  int hdrsize, paylsize = -1;
  struct ethhdr *eth_header = (struct ethhdr *)buf;

  if (ntohs(eth_header->h_proto) == ETH_P_IP) {
    struct ip4_hdr *iphdr = (struct ip4_hdr*)(buf + sizeof(struct ethhdr));
    if (iphdr->proto == IPPROTO_TCP) {
      struct tcp_hdr *tcphdr = (struct tcp_hdr *)(buf + sizeof(struct ethhdr) + sizeof(struct ip4_hdr));
      hdrsize = tcphdr->th_x2;
      paylsize = ntohs(iphdr->totlen) - (sizeof(struct ip4_hdr) + hdrsize * 4);
      memcpy(rbuf, buf + sizeof(struct ethhdr) + sizeof(struct ip4_hdr) + hdrsize * 4, paylsize);
    }
    else if (iphdr->proto == IPPROTO_UDP) {
      struct udp_hdr *udphdr = (struct udp_hdr*)(buf + sizeof(struct ethhdr) + sizeof(struct ip4_hdr));
      hdrsize = sizeof(struct udp_hdr);
      paylsize = ntohs(udphdr->len) - hdrsize;
      memcpy(rbuf, buf + sizeof(struct ethhdr) + sizeof(struct ip4_hdr) + hdrsize, paylsize);
    }
    else if (iphdr->proto == IPPROTO_ICMP) {
      hdrsize = sizeof(struct icmp4_hdr);
      paylsize = ntohs(iphdr->totlen) - (sizeof(struct ip4_hdr) + hdrsize);
      memcpy(rbuf, buf + sizeof(struct ethhdr) + sizeof(struct ip4_hdr), paylsize);
    }
  }

  return paylsize;
}
