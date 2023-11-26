/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"
#include "include/strbase.h"
#include "include/readpkt.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

double tcp_ping(int type, const char* ip, const char* source_ip, int dest_port, int source_port, int timeout_ms, int ttl)
{
  double response_time = -1;
  struct timespec start_time, end_time;
  struct tcp_flags tf;
  struct readfiler rf;
  int sock, send, read;
  u32 seq;
  u8 flags;

  u32 saddr = inet_addr(source_ip);
  u32 daddr = inet_addr(ip);
  rf.dest_ip = ip;
  rf.protocol = IPPROTO_TCP;

  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  seq = generate_seq();
  tf = set_flags(type);
  flags = set_tcp_flags(&tf);

  sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

  send = send_tcp_packet(sock, saddr, daddr, ttl, false, 0, 0, source_port, dest_port, seq, 0, 0, flags, 1024, 0, 0, 0, NULL, 0, 0);
  close(sock);
  if (send == EOF)
    return -1;

  pthread_mutex_lock(&mutex);
  unsigned char *buffer = (unsigned char *)calloc(4096, sizeof(unsigned char));
  pthread_mutex_unlock(&mutex);

  clock_gettime(CLOCK_MONOTONIC, &start_time);

  read = read_packet(&rf, timeout_ms, &buffer);
  if (read != 0) {
    pthread_mutex_lock(&mutex);
    free(buffer);
    pthread_mutex_unlock(&mutex);
    return -1;
  }

  clock_gettime(CLOCK_MONOTONIC, &end_time);
  struct tcp_header *tcph = ext_tcphdr(buffer);

  if (type == SYN_PACKET) {
    if (tcph->th_flags != 0) {
      response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
          (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
    }
  }
  else {
    if (tcph->th_flags == TH_RST) {
        response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
          (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
    }
  }

  pthread_mutex_lock(&mutex);
  free(buffer);
  pthread_mutex_unlock(&mutex);

  return response_time;
}
