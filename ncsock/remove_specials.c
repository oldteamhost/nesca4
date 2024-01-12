/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"

void remove_specials(char* buffer)
{
  int len = strlen(buffer);
  int i, j = 0;

  for (i = 0; i < len; i++) {
    if (buffer[i] != '\r' && buffer[i] != '\n' && buffer[i] != '\t')
      buffer[j++] = buffer[i];
  }

  buffer[j] = '\0';
}
