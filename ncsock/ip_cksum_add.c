/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int ip_cksum_add(const void *buf, size_t len, int cksum)
{
  u16 *sp = (u16*)buf;
  int n, sn;

  sn = len / 2;
  n = (sn + 15) / 16;

  switch (sn % 16) {
  case 0: do {
    cksum += *sp++;
  case 15:
    cksum += *sp++;
  case 14:
    cksum += *sp++;
  case 13:
    cksum += *sp++;
  case 12:
    cksum += *sp++;
  case 11:
    cksum += *sp++;
  case 10:
    cksum += *sp++;
  case 9:
    cksum += *sp++;
  case 8:
    cksum += *sp++;
  case 7:
    cksum += *sp++;
  case 6:
    cksum += *sp++;
  case 5:
    cksum += *sp++;
  case 4:
    cksum += *sp++;
  case 3:
    cksum += *sp++;
  case 2:
    cksum += *sp++;
  case 1:
    cksum += *sp++;
    } while (--n > 0);
  }

  if (len & 1)
    cksum += htons(*(u_char *)sp << 8);

  return cksum;
}
