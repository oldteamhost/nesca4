/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

char *http_parse_url_from_js(const char *buf)
{
  char* search_str = "window.location.href = \"";
  char* end_str = "\"";
  char* res = NULL;
  char* start_pos = strstr(buf, search_str);
  char* end_pos = NULL;
  int len = 0;

  if (start_pos) {
    start_pos += strlen(search_str);
    end_pos = strstr(start_pos, end_str);
    if (end_pos) {
      len = end_pos - start_pos;
      res = (char*)malloc(len + 1);
      if (res) {
        strncpy(res , start_pos, len);
        res[len] = '\0';
      }
    }
  }

  return res;
}
