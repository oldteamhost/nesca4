/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

#include <ctype.h>
#include "include/strbase.h"
void get_http_title(const char* http_header, char* title_buffer, size_t buffer_size)
{
  const char* title_tag_open = "<title>";
  const char* title_tag_close = "</title>";
  const char* current_position = http_header;
  const char* title_start = NULL;
  const char* title_end = NULL;
  int title_length;

  while ((title_start = strstr(current_position, title_tag_open)) != NULL) {
    title_start += strlen(title_tag_open);
    title_end = strstr(title_start, title_tag_close);

    if (title_end != NULL) {
      title_length = title_end - title_start;

      strncpy(title_buffer, title_start, title_length);
      title_buffer[title_length] = '\0';
      remove_specials(title_buffer);
      break;
    }
    current_position = title_start + 1;
  }

  if (title_start == NULL || title_end == NULL)
    strncpy(title_buffer, "n/a", buffer_size);
}
