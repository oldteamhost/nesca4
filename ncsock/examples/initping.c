/*
 * LIBNCSOCK & NESCA4 & INITPING
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include <stdnoreturn.h>
#include "../include/sctp.h"
#include "../include/readpkt.h"
#include "../include/utils.h"

noreturn void usage(char** argv)
{
  printf("Usage: %s [ip] [port] [timeout_ms]\n", argv[0]);
  exit(0);
}

int main(int argc, char** argv)
{
  struct timespec start_time, end_time;
  struct sctp_header *sctph = NULL;
  u8 *packet, *sendpacket;
  struct sockaddr_in dst;
  struct readfiler rf;
  char *chunk = NULL;
  int chunklen = 0;
  u32 packetlen;
  double rtt;
  int fd, i;
  char *src;

  if (argc < 3 + 1)
    usage(argv);

  if (!check_root_perms())
    printf("Only <sudo> run!\n");

  src = get_local_ip();

  dst.sin_addr.s_addr = inet_addr(argv[1]);
  dst.sin_family = AF_INET;
  rf.protocol = IPPROTO_SCTP;
  rf.ip = (struct sockaddr_storage*)&dst;

  fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  if (fd == -1)
    return -1;

  for (i = 0; i < 10; i++) {
    /* SEND PACKET */
    chunklen = sizeof(struct sctp_chunk_header_init);
    chunk = (char*)malloc(chunklen);
    sctp_pack_chunkhdr_init(chunk, SCTP_INIT, 0, chunklen, random_u32(), 32768, 10, 2048, random_u32());
    sendpacket = build_sctp_pkt(inet_addr(src), dst.sin_addr.s_addr,
        121, random_u16(), 0, false, NULL, 0, generate_rare_port(),
        atoi(argv[2]), 0, chunk, chunklen, NULL, 0, &packetlen, false, false);
    if (chunk)
      free(chunk);
    send_ip4_packet(NULL, fd, &dst, 0, sendpacket, packetlen);

    /* RECV PACKET */
    packet = (u8 *)calloc(RECV_BUFFER_SIZE, sizeof(u8));
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    if (read_packet(&rf, atoi(argv[3]), &packet) != -1)
      sctph = (struct sctp_header*)(packet +
          sizeof(struct eth_header) + sizeof(struct ip_header));
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    free(packet);

    /* READ PACKET */
    if (sctph)
        rtt = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
          (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
    else
      rtt = -1;

    /* PRINT INFO */
    printf("SCTPINIT PING [%d pkt]: dst (%s), port=%s, timeout=%s, rtt=[%0.1f]ms\n",
        i, argv[1], argv[2], argv[3], rtt);
    delayy(300);
  }

  close(fd);
  free(src);

  return 0;
}
