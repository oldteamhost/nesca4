/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include "include/types.h"
#include <stdio.h>

void set_basic_auth(const char* user, const char* pass, char* res)
{
  char combined[strlen(user) + 1 + strlen(pass) + 1];
  char* encoded_result = NULL;
  sprintf(combined, "%s:%s", user, pass);

  encoded_result = _base64_encode((u8*)combined, strlen(combined));
  if (encoded_result) {
    strcpy(res, encoded_result);
    free(encoded_result);
  }
}
