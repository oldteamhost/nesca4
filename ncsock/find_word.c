/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"

int find_word(const char* buffer, const char* word)
{
  int i;
  int buffer_length = strlen(buffer);
  int word_length = strlen(word);
  char buffer_lower[4096];
  char word_lower[256];

  if (word_length > buffer_length)
    return -1;

  strcpy(buffer_lower, buffer);
  to_lower(buffer_lower);

  strcpy(word_lower, word);
  to_lower(word_lower);

  for (i = 0; i <= buffer_length - word_length; i++)
    if (strncmp(buffer_lower + i, word_lower, word_length) == 0)
      return i;

  return -1;
}
