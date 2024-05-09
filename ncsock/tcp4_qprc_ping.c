/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"
#include "include/utils.h"
#include "include/readpkt.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

double tcp4_qprc_ping(int type, const char *src, const char *dst, int dstport,
                      int srcport, u16 win, u32 ack, int timeoutms, int ttl,
                      u8 *ipops, int ipoptlen, const char *data, u16 datalen,
                      int mtu, bool badsum)
{
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  double response_time = -1;
  struct sockaddr_in _dst;
  struct timespec start_time, end_time;
  struct tcp_hdr *tcph;
  struct tcp_flags tf;
  struct readfiler rf;
  int sock = -1, send = -1, read = -1;
  u32 seq;
  u8 flags;
  bool df = true;

  if (mtu)
    df = false;

  u32 saddr = inet_addr(src);
  u32 daddr = inet_addr(dst);

  _dst.sin_family = AF_INET;
  _dst.sin_addr.s_addr = daddr;

  rf.ip = (struct sockaddr_storage*)&_dst;
  rf.protocol = IPPROTO_TCP;

  seq = random_u32();
  tf = tcp_util_exflags(type);
  flags = tcp_util_setflags(&tf);

  sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  if (sock == -1)
    return -1;
  send = tcp4_send_pkt(NULL, sock, saddr, daddr, ttl, df, ipops, ipoptlen,
      srcport, dstport, seq, ack, 0, flags, win, 0, 0, 0, data,
      datalen, mtu, badsum);

  pthread_mutex_lock(&mutex);
  close(sock);
  pthread_mutex_unlock(&mutex);
  if (send == -1)
    return -1;

  pthread_mutex_lock(&mutex);
  u8 *buffer = (u8 *)calloc(RECV_BUFFER_SIZE, sizeof(u8));
  pthread_mutex_unlock(&mutex);

  clock_gettime(CLOCK_MONOTONIC, &start_time);
  read = read_packet(&rf, timeoutms, &buffer);
  if (read == -1) {
    pthread_mutex_lock(&mutex);
    free(buffer);
    pthread_mutex_unlock(&mutex);
    return -1;
  }
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  tcph = ext_tcphdr(buffer);

  pthread_mutex_lock(&mutex);
  free(buffer);
  pthread_mutex_unlock(&mutex);

  if (type == TCP_SYN_PACKET) {
    if (tcph->th_flags != 0)
      response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
          (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
  }
  else {
    if (tcph->th_flags == TCP_FLAG_RST)
        response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
          (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
  }

  return response_time;
}
