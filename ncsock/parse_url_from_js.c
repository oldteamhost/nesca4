/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

char* parse_url_from_js(const char* html)
{
  char* search_str = "window.location.href = \"";
  char* end_str = "\"";
  char* result = NULL;
  char* start_pos = strstr(html, search_str);

  if (start_pos != NULL) {
    start_pos += strlen(search_str);
    char* end_pos = strstr(start_pos, end_str);

    if (end_pos != NULL) {
      int length = end_pos - start_pos;
      result = (char*)malloc(length + 1);

      if (result != NULL) {
        strncpy(result, start_pos, length);
        result[length] = '\0';
      }
    }
  }
  return result;
}
