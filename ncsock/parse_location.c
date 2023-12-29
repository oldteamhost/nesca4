/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include "include/strbase.h"

#include <stdbool.h>
char* case_insensitive_strstr(const char* haystack, const char* needle)
{
  bool match;
  while (*haystack) {
    match = true;
    for (size_t i = 0; needle[i]; i++) {
      if (tolower(haystack[i]) != tolower(needle[i])) {
        match = false;
        break;
      }
    }
    if (match)
      return (char*)haystack;
    haystack++;
  }
  return NULL;
}

char* parse_location(const char* http_header, int type_location)
{
  int len = 0;
  char* location_str = NULL;
  char* end_str = NULL;
  char* res = NULL;
  char* src = NULL;
  char* dest = NULL;
  char* location_it = NULL;
  char* end_it = NULL;

  if (type_location == DEFAULT_LOCATION)
    location_str = "Location:";
  else if (type_location == CONTENT_LOCATION)
    location_str = "Content-Location:";

  end_str = "\r\n";
  res = NULL;

  location_it = case_insensitive_strstr(http_header, location_str);
  if (location_it) {
    location_it += strlen(location_str);
    end_it = strstr(location_it, end_str);
    if (end_it) {
      len = end_it - location_it;
      res = (char*)malloc(len + 1);
      if (res != NULL) {
        strncpy(res, location_it, len);
        res[len] = '\0';
        src = res;
        dest = res;
        while (*src) {
          if (!isspace((unsigned char)*src)) {
            *dest = *src;
            dest++;
          }
          src++;
        }
        *dest = '\0';
      }
    }
  }

  return res;
}

