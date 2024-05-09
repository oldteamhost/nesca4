/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/tcp.h"

u8 tcp_util_setflags(struct tcp_flags *tf)
{
  u8 flags = 0;
  if (!tf)
    return -1;

  if (tf->syn)
    flags |= TCP_FLAG_SYN;
  if (tf->ack)
    flags |= TCP_FLAG_ACK;
  if (tf->fin)
    flags |= TCP_FLAG_FIN;
  if (tf->rst)
    flags |= TCP_FLAG_RST;
  if (tf->urg)
    flags |= TCP_FLAG_URG;
  if (tf->psh)
    flags |= TCP_FLAG_PSH;
  if (tf->cwr)
    flags |= TCP_FLAG_CWR;
  if (tf->ece)
    flags |= TCP_FLAG_ECE;

  return flags;
}

