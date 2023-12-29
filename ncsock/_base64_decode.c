/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include "include/types.h"

u8 *_base64_decode(const char *input, size_t *output_length)
{
  size_t i = 0, j = 0, length = 0, padding = 0;
  u8 *decoded_data;
  u8 a, b, c, d;

  length = strlen(input);
  if (length % 4 != 0)
    return NULL;

  if (length > 0 && input[length - 1] == '=')
    padding++;
  if (length > 1 && input[length - 2] == '=')
    padding++;

  *output_length = (length / 4) * 3 - padding;
  decoded_data = (u8*)malloc(*output_length);

  if (!decoded_data)
    return NULL;

  while (i < length) {
    a = input[i]     == '=' ? 0 : strchr(base64_dict, input[i])     - base64_dict;
    b = input[i + 1] == '=' ? 0 : strchr(base64_dict, input[i + 1]) - base64_dict;
    c = input[i + 2] == '=' ? 0 : strchr(base64_dict, input[i + 2]) - base64_dict;
    d = input[i + 3] == '=' ? 0 : strchr(base64_dict, input[i + 3]) - base64_dict;

    decoded_data[j++] = (a << 2) | (b >> 4);
    decoded_data[j++] = (b << 4) | (c >> 2);
    decoded_data[j++] = (c << 6) | d;

    i += 4;
  }

  return decoded_data;
}
