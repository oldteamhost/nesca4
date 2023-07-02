#ifndef ACK_PING_H
#define ACK_PING_H
#include "../../include/portscan.h"
#include "../../include/generation.h"
#include "../../ncsock/include/ncread.h"

double
tcp_ack_ping(const char* ip, const char* source_ip, int dest_port, int timeout_ms, int ttl);

#endif
