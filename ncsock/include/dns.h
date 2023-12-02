/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef DNS_H
#define DNS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

void get_dns(const char* ip, int port, char* dns_buffer, size_t buffer_size);
void get_ip(const char* dns, char* ip_buffer, size_t buffer_size);

#define THIS_IS_DNS 0
#define THIS_IS_IP4 1
int dns_or_ip(const char* node);

#ifdef __cplusplus
}
#endif

#endif
