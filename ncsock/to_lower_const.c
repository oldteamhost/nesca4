/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"

void to_lower_const(const char* input, char* output)
{
  int i;
  for (i = 0; input[i]; i++)
    output[i] = tolower((u8)input[i]);
  output[i] = '\0';
}
