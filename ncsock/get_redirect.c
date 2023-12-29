/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/http.h"

void get_redirect(const char* http_content, char* redirect_buffer, size_t buffer_size)
{
  char* content;
  char* content_location;
  char* http_equiv;
  char* window_js;
  char* parent_location;

  content = parse_location(http_content, DEFAULT_LOCATION);
  if (content != NULL) {
    strncpy(redirect_buffer, content, buffer_size - 1);
    redirect_buffer[buffer_size - 1] = '\0';
    free(content);
    return;
  }

  content_location = parse_location(http_content, CONTENT_LOCATION);
  if (content_location != NULL) {
    strncpy(redirect_buffer, content_location, buffer_size - 1);
    redirect_buffer[buffer_size - 1] = '\0';
    free(content_location);
    return;
  }

  http_equiv = parse_http_equiv(http_content);
  if (http_equiv != NULL) {
    strncpy(redirect_buffer, http_equiv, buffer_size - 1);
    redirect_buffer[buffer_size - 1] = '\0';
    free(http_equiv);
    return;
  }

  window_js = parse_url_from_js(http_content);
  if (window_js != NULL) {
    strncpy(redirect_buffer, window_js, buffer_size - 1);
    redirect_buffer[buffer_size - 1] = '\0';
    free(window_js);
    return;
  }

  parent_location = parse_parent_location(http_content);
  if (parent_location != NULL) {
    strncpy(redirect_buffer, parent_location, buffer_size - 1);
    redirect_buffer[buffer_size - 1] = '\0';
    free(parent_location);
    return;
  }

  redirect_buffer[0] = '\0';
}
