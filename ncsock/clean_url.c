/* LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/strbase.h"
#include <stdlib.h>

char* clean_url(const char* url)
{
  const char *https_prefix = "https://";
  const char *http_prefix = "http:///";
  const char *http_prefix_alt = "http://";
  char *modified_url;
  u64 url_length;

  if (strncmp(url, https_prefix, strlen(https_prefix)) == 0)
    url += strlen(https_prefix);
  else if (strncmp(url, http_prefix, strlen(http_prefix)) == 0)
    url += strlen(http_prefix);
  else if (strncmp(url, http_prefix_alt, strlen(http_prefix_alt)) == 0)
    url += strlen(http_prefix_alt);

  url_length = strlen(url);

  if (url_length > 0 && url[url_length - 1] == '/') {
    modified_url = (char*)malloc(url_length);
    strncpy(modified_url, url, url_length - 1);
    modified_url[url_length - 1] = '\0';

    return modified_url;
  }

  return strdup(url);
}

