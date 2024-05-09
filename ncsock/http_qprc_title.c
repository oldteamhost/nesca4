/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"
#include <ctype.h>
#include <stdlib.h>
#include "include/utils.h"

 void http_qprc_title(const char *h, char *titlebuf,
		      size_t buflen)
{
  const char *title_tag_close = "</title>";
  const char *title_tag_open = "<title";
  const char *title_start;
  const char *title_end;
  size_t title_length;
  char* html = NULL;

  html = (char*)malloc(strlen(h) + 1);
  to_lower_const(h, html);
  title_start = strstr(html, title_tag_open);

  if (title_start != NULL) {
    title_start = strchr(title_start, '>');
    if (title_start != NULL) {
      title_start += 1;
      title_end = strstr(title_start, title_tag_close);
      if (title_end != NULL) {
        title_length = title_end - title_start;
        strncpy(titlebuf, title_start, title_length);
        titlebuf[title_length] = '\0';
        remove_specials(titlebuf);
        if (html)
          free(html);
        return;
      }
    }
  }
  if (html)
    free(html);
  strncpy(titlebuf, "n/a", buflen);
}
