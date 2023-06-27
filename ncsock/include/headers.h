/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef NCSOCK_HEADERS_H
#define NCSOCK_HEADERS_H
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string.h>
#include <netinet/ip_icmp.h>

#ifdef __cplusplus
extern "C" {
#endif

struct tcp_flags{
    uint32_t syn; /*Synchronize sequence numbers.*/
    uint32_t ack; /*Acknowledgment field significant.*/
    uint32_t rst; /*Reset the connection.*/
    uint32_t fin; /*No more data from sender.*/
    uint32_t psh; /*Push Function*/
    uint32_t urg; /*Urgent Pointer field significant*/
};

/*Checksum for:
 * RFC793  IP
 * RFC1071 TCP
 * RFC768  UDP
 * RFC792  ICMP
*/
uint16_t
checksum_16bit(const uint16_t* data, int length);

/*Fill IP header.*/
void
fill_ip_header(struct iphdr* ip_header, const char* source_ip, const char* dest_ip, uint16_t packet_length,
	   uint8_t protocol, uint16_t identification, uint16_t flags_fragoffset, uint8_t ttl,
	   uint8_t ihl, uint8_t version, uint8_t tos);

/*Fill TCP header.
 * Flags set in struct tcp_flags!*/
void
fill_tcp_header(struct tcphdr* tcp_header, uint16_t source_port, uint16_t dest_port, uint32_t seq_num, uint32_t ack_num,
	   uint16_t window_size, uint16_t urgent_ptr, uint8_t doff, uint8_t res1, struct tcp_flags flags);

/*Fill IMCP header.
 * Flags set in struct tcp_flags!*/
void 
fill_icmp_header(struct icmp* icmp_header, uint8_t type, uint8_t code,
	   uint16_t identifier, uint16_t sequence);

#ifdef __cplusplus
}
#endif

#endif
