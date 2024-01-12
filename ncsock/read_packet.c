/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/eth.h"
#include "include/readpkt.h"
#include "include/ip.h"
#include "include/utils.h"
#include <linux/if_ether.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/if_ether.h>

#include <netinet/ip.h>
#include <netinet/tcp.h>

int read_packet(struct readfiler *rf, int recv_timeout_ms, u8 **buffer)
{
  struct sockaddr_in  *dest, source;
  struct sockaddr_in6 *dest6, source6;

  struct ip_header *iph;
  struct ip6_hdr *iph6;

  if (rf->ip->ss_family == AF_INET)
    dest = (struct sockaddr_in*)rf->ip;
  else if (rf->ip->ss_family == AF_INET6)
    dest6 = (struct sockaddr_in6*)rf->ip;

  unsigned char* read_buffer = *buffer;
  int sock, read, elapsed_time;
  time_t start_time, current_time;
  struct timeval timeout;
  bool fuckyeah = false;

  sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if (sock == -1)
    return -1;

  timeout.tv_sec = recv_timeout_ms / 1000;
  timeout.tv_usec = (recv_timeout_ms % 1000) * 1000;
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));

  start_time = time(NULL);
  for (;;) {
    read = recv(sock, read_buffer, RECV_BUFFER_SIZE, 0);
    if (read == -1)
      goto fail;

    if (rf->ip->ss_family == AF_INET) {
      iph = (struct ip_header*)(read_buffer + sizeof(struct ethhdr));
      memset(&source, 0, sizeof(source));
      source.sin_addr.s_addr = iph->saddr;
      if (source.sin_addr.s_addr == dest->sin_addr.s_addr)
        fuckyeah = true;
    }
    else if (rf->ip->ss_family == AF_INET6) {
      iph6 = (struct ip6_hdr*)(read_buffer + sizeof(struct ethhdr));
      memset(&source6, 0, sizeof(source6));
      memcpy(&source6.sin6_addr.s6_addr, iph6->ip6_src.data, sizeof(iph6->ip6_src.data));
      if (memcmp(&source6.sin6_addr, &dest6->sin6_addr, sizeof(struct in6_addr)) == 0)
        fuckyeah = true;
    }

    if (!fuckyeah) {
      current_time = time(NULL);
      elapsed_time = (int)(current_time - start_time) * 1000;
      if (elapsed_time >= recv_timeout_ms)
        goto fail;
      if (rf->protocol) {
        if (rf->ip->ss_family == AF_INET)
          if (iph->protocol != rf->protocol || iph->protocol != rf->second_protocol)
            continue;
        if (rf->ip->ss_family == AF_INET6)
          if (iph6->ip6_ctlun.ip6_un1.ip6_un1_nxt != rf->protocol || iph6->ip6_ctlun.ip6_un1.ip6_un1_nxt != rf->second_protocol)
            continue;
      }
      continue;
    }
    else {
      *buffer = read_buffer;
      close(sock);
      return 0;
    }
  }
  goto fail;

fail:
  /*Ну ок :)*/
  close(sock);
  return -1;
}
