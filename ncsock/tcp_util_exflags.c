/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"

struct tcp_flags tcp_util_exflags(u8 type)
{
  struct tcp_flags tpf;
  memset(&tpf, 0, sizeof(struct tcp_flags));

  tpf.rst = 0;
  tpf.ack = 0;
  switch (type) {
    case TCP_SYN_PACKET:
      tpf.syn = 1;
      tpf.fin = 0;
      tpf.psh = 0;
      tpf.urg = 0;
      break;
    case TCP_XMAS_PACKET:
      tpf.syn = 0;
      tpf.fin = 1;
      tpf.psh = 1;
      tpf.urg = 1;
      break;
    case TCP_FIN_PACKET:
      tpf.syn = 0;
      tpf.fin = 1;
      tpf.psh = 0;
      tpf.urg = 0;
      break;
    case TCP_NULL_PACKET:
      tpf.syn = 0;
      tpf.fin = 0;
      tpf.psh = 0;
      tpf.urg = 0;
      break;
    case TCP_WINDOW_PACKET:
    case TCP_ACK_PACKET:
      tpf.syn = 0;
      tpf.fin = 0;
      tpf.psh = 0;
      tpf.urg = 0;
      tpf.ack = 1;
      break;
    case TCP_MAIMON_PACKET:
      tpf.syn = 0;
      tpf.fin = 1;
      tpf.psh = 0;
      tpf.urg = 0;
      tpf.ack = 1;
      break;
    case TCP_PSH_PACKET:
      tpf.syn = 0;
      tpf.fin = 0;
      tpf.psh = 1;
      tpf.urg = 0;
      tpf.ack = 0;
      break;
  }
  return tpf;
}
