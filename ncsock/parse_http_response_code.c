/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

int parse_http_response_code(const char* http_content)
{
  const char* status;
  int code = -1;

  status = strstr(http_content, "HTTP/1.");
  if (status != NULL)
    sscanf(status, "HTTP/1.%*d %d", &code);

  return code;
}
