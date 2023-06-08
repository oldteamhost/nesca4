#ifndef ICMP_PING_H
#define ICMP_PING_H
#include <stdio.h>
#include <sys/types.h>

#define PING_SUCCESS 0
#define PING_ERROR -1

#ifdef __cplusplus
extern "C" {
#endif

/*Классический IMCP пинг.
 * Поддерживает проверку по типам:
 * ICMP_ECHO,
 * ICMP_TIMESTAMP,
 * ICMP_INFO_REQUEST.*/

double
icmp_ping(const char* dest_ip, int count, int timeout_ms,
	   u_int8_t type, u_int8_t code, u_int8_t ttl);

#ifdef __cplusplus
}
#endif

#endif
