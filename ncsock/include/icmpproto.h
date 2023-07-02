#ifndef ICMP_PROTO_H
#define ICMP_PROTO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#define MAGIC "1234567890"
#define MAGIC_LEN 11

struct icmp4_header{
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t ident;
    uint16_t seq;
    double sending_ts;
    char magic[MAGIC_LEN];
};

int 
send_icmp_packet(struct sockaddr_in* addr, int type,
				int code, int ident, int seq, int ttl);


/*ncread но для IMCP протокола.
 * и на C, принцип тот же.*/
int 
recv_icmp_packet(const char* dest_ip, int timeout_ms, int type,
				int code, int identm);

#ifdef __cplusplus
}
#endif

#endif
