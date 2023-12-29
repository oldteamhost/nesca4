/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"

u8 set_tcp_flags(struct tcp_flags *tf)
{
  u8 flags = 0;
  if (!tf)
    return -1;

  if (tf->syn)
    flags |= TH_SYN;
  if (tf->ack)
    flags |= TH_ACK;
  if (tf->fin)
    flags |= TH_FIN;
  if (tf->rst)
    flags |= TH_RST;
  if (tf->urg)
    flags |= TH_URG;
  if (tf->psh)
    flags |= TH_PSH;
  if (tf->cwr)
    flags |= TH_CWR;
  if (tf->ece)
    flags |= TH_ECE;

  return flags;
}

