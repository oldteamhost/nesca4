/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/strbase.h"
#include <stdlib.h>

char* generate_random_str(int len, const char* dictionary)
{
  int dict_len, i;
  char *result;

  mt19937_seed(generate_seed());
  result = (char*)malloc(len + 1);
  if (!result)
    return NULL;

  dict_len = strlen(dictionary);
  for (i = 0; i < len; i++)
    result[i] = dictionary[mt19937_random() % dict_len];

  result[len] = '\0';
  return result;
}
