/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

u8 *http_remove_html(u8* packet)
{
  char* start;
  u8* newpack;

  start = strstr((char*)packet, "\r\n\r\n");
  if (!start)
    return NULL;

  newpack = (u8*)malloc((size_t)(start - (char*)packet) + 1);
  if (!newpack)
    return NULL;

  strncpy((char*)newpack, (char*)packet, (size_t)(start - (char*)packet));
  newpack[start - (char*)packet] = '\0';

  return newpack;
}
