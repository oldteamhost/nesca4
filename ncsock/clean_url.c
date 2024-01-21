/* LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"
#include <stdlib.h>

char* clean_url(const char* url)
{
  char* dns = NULL;
  const char* http_prefix = "http://";
  const char* https_prefix = "https://";
  size_t dnslen;
  char* slash_pos;

  if (strncmp(url, https_prefix, strlen(https_prefix)) == 0)
    url += strlen(https_prefix);
  else if (strncmp(url, http_prefix, strlen(http_prefix)) == 0)
    url += strlen(http_prefix);

  slash_pos = strchr(url, '/');
  if (slash_pos != NULL) {
    dnslen = slash_pos - url;
    dns = malloc(dnslen + 1);
    strncpy(dns, url, dnslen);
    dns[dnslen] = '\0';
  }
  else
    dns = strdup(url);

  return dns;
}
