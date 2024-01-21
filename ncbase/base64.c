/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "include/base64.h"

char *base64_encode(const unsigned char *input, size_t length)
{
  char *encoded_data = (char *)malloc(((length + 2) / 3) * 4 + 1);
  if (!encoded_data)
    return NULL;

  size_t i = 0, j = 0;
  while (i < length) {
    unsigned char a = i < length ? input[i++] : 0;
    unsigned char b = i < length ? input[i++] : 0;
    unsigned char c = i < length ? input[i++] : 0;

    encoded_data[j++] = base64_chars[a >> 2];
    encoded_data[j++] = base64_chars[((a & 3) << 4) | (b >> 4)];
    encoded_data[j++] = base64_chars[((b & 15) << 2) | (c >> 6)];
    encoded_data[j++] = base64_chars[c & 63];
  }

  while (j % 4 != 0)
    encoded_data[j++] = '=';

  encoded_data[j] = '\0';
  return encoded_data;
}

unsigned char
*base64_decode(const char *input, size_t *output_length)
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
    unsigned char a = input[i]     == '=' ? 0 : strchr(base64_chars, input[i])     - base64_chars;
    unsigned char b = input[i + 1] == '=' ? 0 : strchr(base64_chars, input[i + 1]) - base64_chars;
    unsigned char c = input[i + 2] == '=' ? 0 : strchr(base64_chars, input[i + 2]) - base64_chars;
    unsigned char d = input[i + 3] == '=' ? 0 : strchr(base64_chars, input[i + 3]) - base64_chars;

    decoded_data[j++] = (a << 2) | (b >> 4);
    decoded_data[j++] = (b << 4) | (c >> 2);
    decoded_data[j++] = (c << 6) | d;

    i += 4;
  }

  return decoded_data;
}
