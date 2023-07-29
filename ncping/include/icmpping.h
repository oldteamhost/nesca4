/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef ICMP_PING_H
#define ICMP_PING_H
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <chrono>
#include "../../ncsock/include/icmp4.h"

/*Классический IMCP пинг.
 * По всем многим типам.*/

double
icmp_ping(const char* dest_ip, int timeout_ms, int type, int code, int seq, int ttl);

#endif
