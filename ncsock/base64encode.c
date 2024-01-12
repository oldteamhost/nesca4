/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void base64encode(const u8 *input, size_t len, char *res)
{
  size_t i = 0, j = 0;
  u8 a, b, c;

  while (i < len) {
    a = i < len ? input[i++] : 0;
    b = i < len ? input[i++] : 0;
    c = i < len ? input[i++] : 0;

    res[j++] = base64_dict[a >> 2];
    res[j++] = base64_dict[((a & 3) << 4) | (b >> 4)];
    res[j++] = base64_dict[((b & 15) << 2) | (c >> 6)];
    res[j++] = base64_dict[c & 63];
  }

  while (j % 4 != 0)
    res[j++] = '=';

  res[j] = '\0';
}
