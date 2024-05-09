/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

#include <stdio.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

char *ip6_util_strsrc(void)
{
  struct ifaddrs *ifap, *ifa;
  struct sockaddr_in6 *sa6;
  char *localipv6 = NULL;

  if (getifaddrs(&ifap) == -1)
    return NULL;
  for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family != AF_INET6)
      continue;
    sa6 = (struct sockaddr_in6*)ifa->ifa_addr;
    if (!(ifa->ifa_flags & IFF_LOOPBACK)) {
      localipv6 = (char*)malloc(INET6_ADDRSTRLEN);
      inet_ntop(AF_INET6, &(sa6->sin6_addr), localipv6, INET6_ADDRSTRLEN);
      break;
    }
  }

  freeifaddrs(ifap);
  return localipv6;
}
