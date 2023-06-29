#ifndef ACK_PING_H
#define ACK_PING_H
#include "../../include/portscan.h"
#include "../../include/generation.h"
#include "../../ncsock/include/ncread.h"

#define DEFAULT_SEND_PORT 80

double
tcp_ack_ping(const char* ip, const char* source_ip, int timeout_ms);

#endif
