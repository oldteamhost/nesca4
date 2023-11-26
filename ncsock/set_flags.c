/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"

struct tcp_flags
set_flags(uint8_t packet_preset)
{
  struct tcp_flags tpf;
  memset(&tpf, 0, sizeof(struct tcp_flags));

  tpf.rst = 0;
  tpf.ack = 0;
  switch (packet_preset) {
    case SYN_PACKET:
      tpf.syn = 1;
      tpf.fin = 0;
      tpf.psh = 0;
      tpf.urg = 0;
      break;
    case XMAS_PACKET:
      tpf.syn = 0;
      tpf.fin = 1;
      tpf.psh = 1;
      tpf.urg = 1;
      break;
    case FIN_PACKET:
      tpf.syn = 0;
      tpf.fin = 1;
      tpf.psh = 0;
      tpf.urg = 0;
      break;
    case NULL_PACKET:
      tpf.syn = 0;
      tpf.fin = 0;
      tpf.psh = 0;
      tpf.urg = 0;
      break;
    case WINDOW_PACKET:
    case ACK_PACKET:
      tpf.syn = 0;
      tpf.fin = 0;
      tpf.psh = 0;
      tpf.urg = 0;
      tpf.ack = 1;
      break;
    case MAIMON_PACKET:
      tpf.syn = 0;
      tpf.fin = 1;
      tpf.psh = 0;
      tpf.urg = 0;
      tpf.ack = 1;
      break;
  }
  return tpf;
}
