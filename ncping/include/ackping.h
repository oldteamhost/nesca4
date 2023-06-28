#ifndef ACK_PING_H
#define ACK_PING_H
#include "../../include/synscan.h"
#include "../../ncsock/include/ncread.h"

double
tcp_ack_ping(const char* ip, const char* source_ip, int timeout_ms);

#endif
