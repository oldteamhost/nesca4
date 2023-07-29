/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef ACK_PING_H
#define ACK_PING_H
#include "../../ncsock/include/tcp.h"
#include "../../include/generation.h"
#include <mutex>

double
tcp_ack_ping(const char* ip, const char* source_ip, int dest_port, int source_port, int timeout_ms, int ttl);

#endif
