/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include "include/types.h"

char *_base64_encode(const unsigned char *input, size_t length)
{
  char *encoded_data;
  size_t i = 0, j = 0;
  u8 a, b, c;

  encoded_data = (char *)malloc(((length + 2) / 3) * 4 + 1);
  if (!encoded_data)
    return NULL;

  while (i < length) {
    a = i < length ? input[i++] : 0;
    b = i < length ? input[i++] : 0;
    c = i < length ? input[i++] : 0;

    encoded_data[j++] = base64_dict[a >> 2];
    encoded_data[j++] = base64_dict[((a & 3) << 4) | (b >> 4)];
    encoded_data[j++] = base64_dict[((b & 15) << 2) | (c >> 6)];
    encoded_data[j++] = base64_dict[c & 63];
  }

  while (j % 4 != 0)
    encoded_data[j++] = '=';

  encoded_data[j] = '\0';
  return encoded_data;
}
