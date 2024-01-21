/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"

#include <ifaddrs.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

int get_local_mac(const char *dev, char *mac_address)
{
  struct ifaddrs *ifap, *ifa;
  struct sockaddr_ll *sll;

  if (getifaddrs(&ifap) == -1)
    return -1;

  for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr != NULL && ifa->ifa_addr->sa_family == AF_PACKET) {
      sll = (struct sockaddr_ll *)ifa->ifa_addr;
      if (strcmp(ifa->ifa_name, dev) == 0) {
        snprintf(mac_address, 18, "%02X:%02X:%02X:%02X:%02X:%02X",
            sll->sll_addr[0], sll->sll_addr[1], sll->sll_addr[2],
            sll->sll_addr[3], sll->sll_addr[4], sll->sll_addr[5]);
        freeifaddrs(ifap);
        return 0;
      }
    }
  }

  freeifaddrs(ifap);
  return -1;
}
