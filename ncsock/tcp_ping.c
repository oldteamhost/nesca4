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

double tcp_ping(int type, const char* ip, const char* source_ip, int dest_port,
    int source_port, int timeout_ms, int ttl, const char *data, u16 datalen, int fragscan)
{
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  double response_time = -1;
  struct timespec start_time, end_time;
  struct tcp_flags tf;
  struct readfiler rf;
  int sock = -1, send = -1, read = -1;
  u32 seq;
  u8 flags;
  bool df = true;

  if (fragscan)
    df = false;

  u32 saddr = inet_addr(source_ip);
  u32 daddr = inet_addr(ip);
  rf.dest_ip = ip;
  rf.protocol = IPPROTO_TCP;

  seq = generate_seq();
  tf = set_flags(type);
  flags = set_tcp_flags(&tf);

  sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  if (sock == -1)
    return -1;

  send = send_tcp_packet(sock, saddr, daddr, ttl, df, 0, 0, source_port, dest_port, seq, 0, 0, flags, 1024, 0, 0, 0, data, datalen, fragscan);

  pthread_mutex_lock(&mutex);
  close(sock);
  pthread_mutex_unlock(&mutex);

  if (send == EOF)
    return -1;

  pthread_mutex_lock(&mutex);
  u8 *buffer = (u8 *)calloc(RECV_BUFFER_SIZE, sizeof(u8));
  pthread_mutex_unlock(&mutex);

  clock_gettime(CLOCK_MONOTONIC, &start_time);

  read = read_packet(&rf, timeout_ms, &buffer);
  if (read == -1) {
    pthread_mutex_lock(&mutex);
    free(buffer);
    pthread_mutex_unlock(&mutex);
    return -1;
  }

  clock_gettime(CLOCK_MONOTONIC, &end_time);
  struct tcp_header *tcph = ext_tcphdr(buffer);

  pthread_mutex_lock(&mutex);
  free(buffer);
  pthread_mutex_unlock(&mutex);

  if (type == SYN_PACKET) {
    if (tcph->th_flags != 0)
      response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
          (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
  }
  else {
    if (tcph->th_flags == TH_RST)
        response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
          (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
  }

  return response_time;
}
