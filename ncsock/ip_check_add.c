/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

int ip_check_add(const void *buf, size_t len, int check)
{
  u16 *sp = (u16*)buf;
  int n, sn;

  sn = len / 2;
  n = (sn + 15) / 16;

  switch (sn % 16) {
  case 0: do {
    check += *sp++;
  case 15:
    check += *sp++;
  case 14:
    check += *sp++;
  case 13:
    check += *sp++;
  case 12:
    check += *sp++;
  case 11:
    check += *sp++;
  case 10:
    check += *sp++;
  case 9:
    check += *sp++;
  case 8:
    check += *sp++;
  case 7:
    check += *sp++;
  case 6:
    check += *sp++;
  case 5:
    check += *sp++;
  case 4:
    check += *sp++;
  case 3:
    check += *sp++;
  case 2:
    check += *sp++;
  case 1:
    check += *sp++;
    } while (--n > 0);
  }

  if (len & 1)
    check += htons(*(u_char *)sp << 8);

  return check;
}
