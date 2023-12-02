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
  while (*haystack) {
    bool match = true;
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
  char* location_str;
  if (type_location == DEFAULT_LOCATION){
    location_str = "Location:";
  }
  else if (type_location == CONTENT_LOCATION) {
    location_str = "Content-Location:";
  }

  char* end_str = "\r\n";
  char* result = NULL;

  char* location_it = case_insensitive_strstr(http_header, location_str);
  if (location_it != NULL) {
    location_it += strlen(location_str);
    char* end_it = strstr(location_it, end_str);
    if (end_it != NULL) {
      int length = end_it - location_it;
      result = (char*)malloc(length + 1);
      if (result != NULL) {
        strncpy(result, location_it, length);
        result[length] = '\0';

        char* src = result;
        char* dest = result;
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

  return result;
}

