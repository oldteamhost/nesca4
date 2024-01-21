/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"

#define ROUTE_FILE "/proc/net/route"
#define BUF_SIZE 512
int get_gateway_ip(char* buf, size_t len)
{
  FILE *file;
  char line[BUF_SIZE];
  char iface[BUF_SIZE], dest[BUF_SIZE], gw[BUF_SIZE];
  u32 gw_addr;

  file = fopen(ROUTE_FILE, "r");
  if (!file)
    return -1;

  fgets(line, BUF_SIZE, file);
  while (fgets(line, BUF_SIZE, file)) {
    if (sscanf(line, "%s %s %s", iface, dest, gw) == 3) {
      if (strcmp(dest, "00000000") == 0 && strcmp(gw, "00000000") != 0) {
        sscanf(gw, "%X", &gw_addr);
        snprintf(buf, len, "%d.%d.%d.%d",
            gw_addr & 0xFF, (gw_addr >> 8) & 0xFF,
            (gw_addr >> 16) & 0xFF, (gw_addr >> 24) & 0xFF);
        fclose(file);
        return 0;
      }
    }
  }

  fclose(file);
  return -1;
}
