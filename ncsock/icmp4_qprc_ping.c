/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/icmp.h"
#include "include/readpkt.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

double icmp4_qprc_ping(const char *dst, const char *src, int timeoutms,
                       int type, int code, int seq, int ttl, u8 *ipops,
                       int ipoptlen, const char *data, u16 datalen, int mtu,
                       bool badsum)
{
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  struct timespec start_time, end_time;
  struct icmp4_hdr *icmphdr;
  struct readfiler rf;
  double response_time = -1;
  int sock, send, read;
  u32 saddr, daddr;
  bool df = true;
  struct sockaddr_in _dst;

  saddr = inet_addr(src);
  daddr = inet_addr(dst);

  _dst.sin_family = AF_INET;
  _dst.sin_addr.s_addr = daddr;

  rf.ip = (struct sockaddr_storage*)&_dst;
  rf.protocol = IPPROTO_ICMP;

  if (mtu)
    df = false;

  sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  if (sock == -1)
    return -1;
  send = icmp4_send_pkt(NULL, sock, saddr, daddr, ttl, df, ipops, ipoptlen, seq,
      code, type, data, datalen, mtu, badsum);
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
  icmphdr = ext_icmphdr(buffer);

  pthread_mutex_lock(&mutex);
  free(buffer);
  pthread_mutex_unlock(&mutex);

  if (type == ICMP4_ECHO)
    if (icmphdr->type != ICMP4_ECHOREPLY)
      return -1;

  if (type == ICMP4_TIMESTAMP)
    if (icmphdr->type != ICMP4_TIMESTAMPREPLY)
      return -1;

  if (type == ICMP4_INFO_REQUEST)
    if (icmphdr->type != ICMP4_INFO_REPLY)
      return -1;

  response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
                  (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

  /* Source - https://nmap.org/man/ru/man-host-discovery.html */
  /* Source - https://gist.github.com/bugparty/ccba5744ba8f1cece5e0 */
  /* Source - https://datatracker.ietf.org/doc/html/rfc792 */

  return response_time;
}
