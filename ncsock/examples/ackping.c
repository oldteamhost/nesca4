/*
 * LIBNCSOCK & NESCA4 & ACKPING
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include <stdnoreturn.h>
#include "../include/readpkt.h"
#include "../include/tcp.h"
#include "../include/utils.h"
#include "../include/log.h"

noreturn void usage(char** argv)
{
  printf("Usage: %s [ip] [port] [timeout_ms] [size (max 1400)]\n", argv[0]);
  exit(0);
}

int main(int argc, char** argv)
{
  struct timespec start_time, end_time;
  struct tcp_hdr *tcph = NULL;
  struct sockaddr_in dst;
  struct readfiler rf;
  double rtt;
  char *data, *src;
  u8 *packet;
  int fd, i;

  if (argc < 4 + 1)
    usage(argv);

  if (atoi(argv[4]) > 1400)
    usage(argv);

  if (!check_root_perms())
    errx(1, "Only <sudo> run!");

  data = random_str(atoi(argv[4]),
      DEFAULT_DICTIONARY);
  src = ip4_util_strsrc();

  dst.sin_addr.s_addr = inet_addr(argv[1]);
  dst.sin_family = AF_INET;
  rf.protocol = IPPROTO_TCP;
  rf.ip = (struct sockaddr_storage*)&dst;

  fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  if (fd == -1)
    return -1;

  for (i = 1; i <= 10; i++) {
    /* SEND PACKET */
    tcp4_send_pkt(NULL, fd, inet_addr(src), dst.sin_addr.s_addr, 121,
        false, NULL, 0, random_srcport(), atoi(argv[2]),
        random_u32(), 0, 0, TCP_FLAG_ACK, 1024, 0, NULL, 0, data,
        strlen(data), 0, false);

    /* RECV PACKET */
    packet = (u8 *)calloc(RECV_BUFFER_SIZE, sizeof(u8));
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    if (read_packet(&rf, atoi(argv[3]), &packet) != -1)
      tcph = ext_tcphdr(packet);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    free(packet);

    /* READ PACKET */
    if (tcph && tcph->th_flags == TCP_FLAG_RST)
        rtt = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
          (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
    else
      rtt = -1;

    /* PRINT INFO */
    printf("TCPACK PING [%d pkt]: dst (%s), port=%s, timeout=%s, payload=%s, rtt=[%0.1f]ms\n",
        i, argv[1], argv[2], argv[3], argv[4], rtt);
    delayy(300);
  }

  close(fd);
  free(data);
  free(src);

  return 0;
}
