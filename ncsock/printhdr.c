/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/readpkt.h"
#include <stdio.h>

void print_ipdr(const struct ip4_hdr *iphdr)
{
  printf("Version: %u\n", (unsigned int)iphdr->version);
  printf("Header Length: %u bytes\n", (unsigned int)(iphdr->ihl * 4));
  printf("Type of Service: %u\n", (unsigned int)iphdr->tos);
  printf("Total Length: %u bytes\n", ntohs(iphdr->totlen));
  printf("Identification: %u\n", ntohs(iphdr->id));
  printf("Flags: %c%c%c\n",
      (iphdr->off & IP4_RF) ? 'R' : '-',
      (iphdr->off & IP4_DF) ? 'D' : '-',
      (iphdr->off & IP4_MF) ? 'M' : '-');
  printf("Fragment Offset: %u\n", (unsigned int)(iphdr->off & IP4_OFFMASK));
  printf("Time to Live: %u\n", (unsigned int)iphdr->ttl);
  printf("Protocol: %u\n", (unsigned int)iphdr->proto);
  printf("Header Checksum: 0x%04X\n", ntohs(iphdr->check));
  printf("Source IP Address: %s\n", inet_ntoa(*(struct in_addr*)&iphdr->src));
  printf("Destination IP Address: %s\n", inet_ntoa(*(struct in_addr*)&iphdr->dst));
}

void print_tcphdr(const struct tcp_hdr *tcphdr)
{
  printf("Source Port: %u\n", ntohs(tcphdr->th_sport));
  printf("Destination Port: %u\n", ntohs(tcphdr->th_dport));
  printf("Sequence Number: %u\n", ntohl(tcphdr->th_seq));
  printf("Acknowledgment Number: %u\n", ntohl(tcphdr->th_ack));
  printf("Data Offset: %u bytes\n", (unsigned int)(tcphdr->th_x2 * 4));
  printf("Flags: ");
  printf("URG:%d ACK:%d PSH:%d RST:%d SYN:%d FIN:%d CWR:%d ECE:%d\n",
           (tcphdr->th_flags & TCP_FLAG_URG) ? 1 : 0,
           (tcphdr->th_flags & TCP_FLAG_ACK) ? 1 : 0,
           (tcphdr->th_flags & TCP_FLAG_PSH) ? 1 : 0,
           (tcphdr->th_flags & TCP_FLAG_RST) ? 1 : 0,
           (tcphdr->th_flags & TCP_FLAG_SYN) ? 1 : 0,
           (tcphdr->th_flags & TCP_FLAG_FIN) ? 1 : 0,
           (tcphdr->th_flags & TCP_FLAG_CWR) ? 1 : 0,
           (tcphdr->th_flags & TCP_FLAG_ECE) ? 1 : 0);
  printf("Window Size: %u\n", ntohs(tcphdr->th_win));
  printf("Checksum: 0x%04X\n", ntohs(tcphdr->th_sum));
  printf("Urgent Pointer: %u\n", ntohs(tcphdr->th_urp));
}

void print_udphdr(const struct udp_hdr *udphdr)
{
  printf("Source Port: %u\n", ntohs(udphdr->srcport));
  printf("Destination Port: %u\n", ntohs(udphdr->dstport));
  printf("Length: %u bytes\n", ntohs(udphdr->len));
  printf("Checksum: 0x%04X\n", ntohs(udphdr->check));
}

void print_icmphdr(const struct icmp4_hdr *icmphdr)
{
  printf("Type: %u\n", ntohs(icmphdr->type));
  printf("Code: %u\n", ntohs(icmphdr->code));
  printf("Ident: %u\n", ntohs(icmphdr->id));
  printf("Seq %u\n", ntohs(icmphdr->seq));
  printf("Checksum: 0x%04X\n", ntohs(icmphdr->check));
}

void print_payload(const u8 *payload, int len)
{
  for (int i = 0; i < len; ++i)
    printf("%02X ", payload[i]);
  putchar('\n');
}

void print_payload_ascii(const u8 *payload, int len)
{
  for (int i = 0; i < len; ++i) {
    if (payload[i] >= 32 && payload[i] <= 126)
      printf("%c", payload[i]);
    else
      printf(".");
  }
  putchar('\n');
}
