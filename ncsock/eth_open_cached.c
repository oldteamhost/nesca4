/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * Copyright (c) [2000] Dug Song <dugsong@monkey.org>
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/eth.h"

static char etht_cache_device_name[64];
static eth_t *etht_cache_device = NULL;

eth_t *eth_open_cached(const char *device)
{
  if (!strcmp(device, etht_cache_device_name))
    return etht_cache_device;

  if (*etht_cache_device_name) {
    eth_close(etht_cache_device);
    etht_cache_device_name[0] = '\0';
    etht_cache_device = NULL;
  }
  etht_cache_device = eth_open(device);
  if (etht_cache_device)
    snprintf(etht_cache_device_name,
	     sizeof(etht_cache_device_name), "%s", device);
  
  return etht_cache_device;
}

void eth_close_cached(void)
{
  if (etht_cache_device) {
    eth_close(etht_cache_device);
    etht_cache_device = NULL;
    etht_cache_device_name[0] = '\0';
  }
  return;
}
