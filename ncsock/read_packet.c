/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

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
  struct in_addr dest;
  dest.s_addr = inet_addr(rf->dest_ip);
  unsigned char* read_buffer = *buffer;
  struct sockaddr_in source;
  int sock, read, elapsed_time;
  time_t start_time, current_time;

  sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if (sock == -1)
    return -1;

  struct timeval timeout;
  timeout.tv_sec = recv_timeout_ms / 1000;
  timeout.tv_usec = (recv_timeout_ms % 1000) * 1000;

  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));

  start_time = time(NULL);
  for (;;) {
    read = recv(sock, read_buffer, RECV_BUFFER_SIZE, 0);
    if (read == -1) {
      close(sock);
      return -1;
    }

    struct ip_header *iph = ext_iphdr(read_buffer);
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;

    if (source.sin_addr.s_addr != dest.s_addr) {
      current_time = time(NULL);
      elapsed_time = (int)(current_time - start_time) * 1000;

      if (elapsed_time >= recv_timeout_ms) {
        close(sock);
        return -1;
      }
      if (iph->protocol != rf->protocol)
        continue;

      continue;
    }
    else {
      *buffer = read_buffer;
      close(sock);
      return 0;
    }
  }

  /*Ну ок :)*/
  close(sock);
  return -1;
}
