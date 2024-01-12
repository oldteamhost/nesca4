/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"

void to_lower(char* str)
{
  int i;
  for (i = 0; str[i]; i++)
    str[i] = tolower((u8)str[i]);
}
