/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

unsigned char *_base64_decode(const char *input, size_t *output_length)
{
  size_t length = strlen(input);
  if (length % 4 != 0)
    return NULL;

  size_t padding = 0;
  if (length > 0 && input[length - 1] == '=')
    padding++;

  if (length > 1 && input[length - 2] == '=')
    padding++;

  *output_length = (length / 4) * 3 - padding;
  unsigned char *decoded_data = (unsigned char *)malloc(*output_length);

  if (!decoded_data)
    return NULL;

  size_t i = 0, j = 0;
  while (i < length) {
    unsigned char a = input[i]     == '=' ? 0 : strchr(base64_dict, input[i])     - base64_dict;
    unsigned char b = input[i + 1] == '=' ? 0 : strchr(base64_dict, input[i + 1]) - base64_dict;
    unsigned char c = input[i + 2] == '=' ? 0 : strchr(base64_dict, input[i + 2]) - base64_dict;
    unsigned char d = input[i + 3] == '=' ? 0 : strchr(base64_dict, input[i + 3]) - base64_dict;

    decoded_data[j++] = (a << 2) | (b >> 4);
    decoded_data[j++] = (b << 4) | (c >> 2);
    decoded_data[j++] = (c << 6) | d;

    i += 4;
  }

  return decoded_data;
}
