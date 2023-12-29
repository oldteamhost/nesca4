/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include "include/types.h"

char* set_basic_auth(const char* user, const char* pass)
{
  char combined[strlen(user) + 1 + strlen(pass) + 1];
  int len = 0;
  u8 *bytes = NULL;

  sprintf(combined, "%s:%s", user, pass);
  bytes = (u8*)combined;

  return (_base64_encode(bytes, strlen(combined)));
}
