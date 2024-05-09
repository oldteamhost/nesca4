/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

char *http_parse_parent_location(const char *buf)
{
  const char* search_str = "parent.location=\"";
  const char* search_str2 = "parent.location='";
  const char* end_str = "\"";
  const char* end_str2 = "\'";
  char* result = NULL;
  const char *start_pos = NULL;
  const char *end_pos = NULL;
  size_t length = 0;

  start_pos = strstr(buf, search_str);
  if (!start_pos)
    start_pos = strstr(buf, search_str2);
  if (start_pos) {
    start_pos += strlen(search_str);
    end_pos = strstr(start_pos, end_str);
    if (!end_pos)
      end_pos = strstr(start_pos, end_str2);
    if (end_pos) {
      length = end_pos - start_pos;
      result = (char*)malloc(length + 1);
      if (result) {
        strncpy(result, start_pos, length);
        result[length] = '\0';
      }
    }
  }

  return result;
}

