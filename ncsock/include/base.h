/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef NCSOCK_BASE_H
#define NCSOCK_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define CIDR  0
#define IPv4  1
#define RANGE 2
#define _URL_ 3
#define DNS   4
#define IPv6  5
int this_is(const char* node);
const char* get_this_is(int type);

int check_root_perms(void);
void delayy(int ms);
const char* get_time();
void get_current_date(char* formatted_date, size_t max_length);

/* calculation */
#define OUTRAGEOUS_SPEED 5
#define FIERCE_SPEED     4
#define FAST_SPEED       3
#define BALANCED_SPEED   2
#define NOT_SPEED        1
int calculate_timeout(double rtt, int speed);
int calculate_threads(int speed, int len);
int calculate_ping_timeout(int speed);

#ifdef __cplusplus
}
#endif

#endif
