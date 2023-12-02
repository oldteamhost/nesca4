/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/strbase.h"

void to_lower(char* str)
{
  for (int i = 0; str[i]; i++)
    str[i] = tolower((unsigned char)str[i]);
}
