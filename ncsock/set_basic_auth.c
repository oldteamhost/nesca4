/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

char* set_basic_auth(const char* user, const char* pass)
{
#include <string.h>
  int combined_length = strlen(user) + 1 + strlen(pass) + 1;
  char combined[combined_length];
  sprintf(combined, "%s:%s", user, pass);
  unsigned char *combined_bytes = (unsigned char *)combined;
  size_t combined_length_bytes = strlen(combined);
  char *base64_encoded = _base64_encode(combined_bytes, combined_length_bytes);

  return base64_encoded;
}
