/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

char* parse_parent_location(const char* html)
{
  const char* search_str = "parent.location=\"";
  const char* search_str2 = "parent.location='";
  const char* end_str = "\"";
  const char* end_str2 = "\'";
  char* result = NULL;
  const char *start_pos;
  const char *end_pos;
  size_t length;

  start_pos = strstr(html, search_str);
  if (start_pos == NULL)
    start_pos = strstr(html, search_str2);

  if (start_pos != NULL) {
    start_pos += strlen(search_str);
    end_pos = strstr(start_pos, end_str);
    if (end_pos == NULL)
      end_pos = strstr(start_pos, end_str2);
    if (end_pos != NULL) {
      length = end_pos - start_pos;
      result = (char*)malloc(length + 1);
      if (result != NULL) {
        strncpy(result, start_pos, length);
        result[length] = '\0';
      }
    }
  }

  return result;
}

