/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef NCSOCK_HEADERS_H
#define NCSOCK_HEADERS_H
#include <arpa/inet.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	IP_RF      0x8000			/*Reserved fragment flag*/
#define	IP_DF      0x4000			/*Dont fragment flag*/
#define	IP_MF      0x2000			/*More fragments flag*/
#define	IP_OFFMASK 0x1fff		    /*Mask for fragmenting bits*/

/*IP заголовок для IPv4.*/
struct ip_header{
    unsigned int ihl:4;
    unsigned int version:4;
    uint8_t tos;
    uint16_t tot_len;
    uint16_t id;
    uint16_t frag_off;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t check;
    uint32_t saddr;
    uint32_t daddr;
};

#define TH_FIN	0x01
#define TH_SYN	0x02
#define TH_RST	0x04
#define TH_PUS	0x08
#define TH_ACK	0x10
#define TH_URG	0x20

typedef	uint32_t tcp_seq;

/*TCP заголовок.*/
struct tcp_header {
	union {
    	struct{
			uint16_t th_sport;	/*Source port */
			uint16_t th_dport;	/*Destination port */
			tcp_seq th_seq;		/*Sequence number */
			tcp_seq th_ack;		/*Acknowledgement number */
			uint8_t th_off:4;	/*Data offset */
			uint8_t th_x2:4;	/*(unused) */
			uint8_t th_flags;
			uint16_t th_win;	/*Window */
			uint16_t th_sum;	/*Checksum */
			uint16_t th_urp;	/*Urgent pointer */
    	};
    	struct{
			uint16_t source;
			uint16_t dest;
			uint32_t seq;
			uint32_t ack_seq;
			uint16_t res1:4;
			uint16_t doff:4;
			uint16_t fin:1;
			uint16_t syn:1;
			uint16_t rst:1;
			uint16_t psh:1;
			uint16_t ack:1;
			uint16_t urg:1;
			uint16_t res2:2;
			uint16_t window;
			uint16_t check;
			uint16_t urg_ptr;
    	};
	};
};

/*TCP флаги.*/
struct tcp_flags{
    uint32_t syn; /*Synchronize sequence numbers.*/
    uint32_t ack; /*Acknowledgment field significant.*/
    uint32_t rst; /*Reset the connection.*/
    uint32_t fin; /*No more data from sender.*/
    uint32_t psh; /*Push Function*/
    uint32_t urg; /*Urgent Pointer field significant*/
};

#define ICMP_ECHOREPLY		0	/*Echo Reply*/
#define ICMP_ECHO		    8	/*Echo Request*/
#define ICMP_TIMESTAMP		13	/*Timestamp Request*/
#define ICMP_TIMESTAMPREPLY	14	/*Timestamp Reply*/
#define ICMP_INFO_REQUEST	15	/*Information Request*/
#define ICMP_INFO_REPLY		16	/*Information Reply*/

#define MAGIC "1234567890"
#define MAGIC_LEN 11

struct icmp4_header{
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t ident;
    uint16_t seq;
    char magic[MAGIC_LEN];
};

/*Checksum for:
 * RFC793  IP
 * RFC1071 TCP
 * RFC768  UDP
 * RFC792  ICMP
*/
uint16_t
checksum_16bit(const uint16_t* data, int length);

uint16_t
checksum_16bit_icmp(unsigned char* buffer, int bytes);

/*Fill IP header.*/
void
fill_ip_header(struct ip_header* ip_header, const char* source_ip, const char* dest_ip, uint16_t packet_length,
	   uint8_t protocol, uint16_t identification, uint16_t flags_fragoffset, uint8_t ttl,
	   uint8_t ihl, uint8_t version, uint8_t tos);

/*Fill ICMP header.*/
void
fill_icmp_header(struct icmp4_header* icmp4_header, uint8_t type, uint8_t code, uint16_t checksum,
		uint16_t ident, uint16_t seq);

/*Fill TCP header.
 * Flags set in struct tcp_flags!*/
void
fill_tcp_header(struct tcp_header* tcp_header, uint16_t source_port, uint16_t dest_port, uint32_t seq_num, uint32_t ack_num,
	   uint16_t window_size, uint16_t urgent_ptr, uint8_t doff, uint8_t res1, struct tcp_flags flags);

#ifdef __cplusplus
}
#endif

#endif
