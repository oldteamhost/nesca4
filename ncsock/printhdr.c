/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/readpkt.h"
#include <stdio.h>

void print_ipdr(const struct ip_header *iphdr)
{
  printf("Version: %u\n", (unsigned int)iphdr->version);
  printf("Header Length: %u bytes\n", (unsigned int)(iphdr->ihl * 4));
  printf("Type of Service: %u\n", (unsigned int)iphdr->tos);
  printf("Total Length: %u bytes\n", ntohs(iphdr->tot_len));
  printf("Identification: %u\n", ntohs(iphdr->ident));
  printf("Flags: %c%c%c\n",
      (iphdr->frag_off & IP_RF) ? 'R' : '-',
      (iphdr->frag_off & IP_DF) ? 'D' : '-',
      (iphdr->frag_off & IP_MF) ? 'M' : '-');
  printf("Fragment Offset: %u\n", (unsigned int)(iphdr->frag_off & IP_OFFMASK));
  printf("Time to Live: %u\n", (unsigned int)iphdr->ttl);
  printf("Protocol: %u\n", (unsigned int)iphdr->protocol);
  printf("Header Checksum: 0x%04X\n", ntohs(iphdr->check));
  printf("Source IP Address: %s\n", inet_ntoa(*(struct in_addr*)&iphdr->saddr));
  printf("Destination IP Address: %s\n", inet_ntoa(*(struct in_addr*)&iphdr->daddr));
}

void print_tcphdr(const struct tcp_header *tcphdr)
{
  printf("Source Port: %u\n", ntohs(tcphdr->th_sport));
  printf("Destination Port: %u\n", ntohs(tcphdr->th_dport));
  printf("Sequence Number: %u\n", ntohl(tcphdr->th_seq));
  printf("Acknowledgment Number: %u\n", ntohl(tcphdr->th_ack));
  printf("Data Offset: %u bytes\n", (unsigned int)(tcphdr->th_x2 * 4));
  printf("Flags: ");
  printf("URG:%d ACK:%d PSH:%d RST:%d SYN:%d FIN:%d CWR:%d ECE:%d\n",
           (tcphdr->th_flags & TH_URG) ? 1 : 0,
           (tcphdr->th_flags & TH_ACK) ? 1 : 0,
           (tcphdr->th_flags & TH_PSH) ? 1 : 0,
           (tcphdr->th_flags & TH_RST) ? 1 : 0,
           (tcphdr->th_flags & TH_SYN) ? 1 : 0,
           (tcphdr->th_flags & TH_FIN) ? 1 : 0,
           (tcphdr->th_flags & TH_CWR) ? 1 : 0,
           (tcphdr->th_flags & TH_ECE) ? 1 : 0);
  printf("Window Size: %u\n", ntohs(tcphdr->th_win));
  printf("Checksum: 0x%04X\n", ntohs(tcphdr->th_sum));
  printf("Urgent Pointer: %u\n", ntohs(tcphdr->th_urp));
}

void print_udphdr(const struct udp_header *udphdr)
{
  printf("Source Port: %u\n", ntohs(udphdr->uh_sport));
  printf("Destination Port: %u\n", ntohs(udphdr->uh_dport));
  printf("Length: %u bytes\n", ntohs(udphdr->ulen));
  printf("Checksum: 0x%04X\n", ntohs(udphdr->check));
}
