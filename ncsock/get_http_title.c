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
  char* title_tag_open = "<title>";
  char* title_tag_close = "</title>";

  char *title_start = strstr(http_header, title_tag_open);
  if (title_start == NULL) {
    strncpy(title_buffer, "n/a", buffer_size);
    return;
  }

  title_start += strlen(title_tag_open);

  char *title_end = strstr(title_start, title_tag_close);
  if (title_end == NULL) {
    strncpy(title_buffer, "n/a", buffer_size);
    return;
  }

  int title_length = title_end - title_start;
  strncpy(title_buffer, title_start, buffer_size);

  for (int i = 0; i < title_length; i++) {
    char c = title_buffer[i];
    if (isalnum(c) || isspace(c))
      title_buffer[i] = c;
    else
      title_buffer[i] = ' ';
  }

  title_buffer[title_length] = '\0';
  remove_specials(title_buffer);
}
