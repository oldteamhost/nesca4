/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef NCSOCK_BASE_H
#define NCSOCK_BASE_H

/*Support c++.*/
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

const char* get_local_ip(void);

#ifdef __cplusplus
}
#endif

#endif
