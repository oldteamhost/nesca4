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

/*Классический IMCP пинг.
 * По всем типам и кодам.*/

double
icmp_ping(const char* dest_ip, int timeout_ms, int type, int code, int seq, int ttl);

#endif
