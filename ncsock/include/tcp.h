/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
 * -----------------------------------------------------------
 * tcp.h - This file contains structures, constants, and
 * functions for working with TCP protocol. Support threads.
 * -----------------------------------------------------------
*/

#ifndef NCSOCK_TCP_H
#define NCSOCK_TCP_H

/*Support c++.*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>

/*Compile opts*/
#include "ncsockopt.h"

typedef	uint32_t tcp_seq;
struct tcp_header
{
	union
	{
    	struct
		{
			uint16_t th_sport;	/*Source port */
			uint16_t th_dport;	/*Destination port */
			tcp_seq th_seq;		/*Sequence number */
			tcp_seq th_ack;		/*Acknowledgement number */
			uint8_t th_off:4;	/*Data offset */
			uint8_t th_x2:4;	/*(unused) */
			uint8_t th_flags;   /*TCP flags.*/
			uint16_t th_win;	/*Window */
			uint16_t th_sum;	/*Checksum */
			uint16_t th_urp;	/*Urgent pointer */
    	};
    	struct
		{
			uint16_t source;
			uint16_t dest;
			uint32_t seq;
			uint32_t ack_seq;
#define TH_FIN	0x01
#define TH_SYN	0x02
#define TH_RST	0x04
#define TH_PUS	0x08
#define TH_ACK	0x10
#define TH_URG	0x20
			uint16_t res1:4;
			uint16_t doff:4;

			uint8_t fin:1;
			uint8_t syn:1;
			uint8_t rst:1;
			uint8_t psh:1;
			uint8_t ack:1;
			uint8_t urg:1;
			uint8_t cwr:1;
			uint8_t ece:1;
			uint8_t res2:2;

			uint8_t window;
			uint16_t check;
			uint16_t urg_ptr;
    	};
	};
};

struct tcp_flags
{
    uint8_t syn; /*Synchronize sequence numbers.*/
    uint8_t ack; /*Acknowledgment field significant.*/
    uint8_t rst; /*Reset the connection.*/
    uint8_t fin; /*No more data from sender.*/
    uint8_t psh; /*Push Function*/
    uint8_t urg; /*Urgent Pointer field significant*/
    uint8_t cwr; /*Congestion Window reduced.*/
    uint8_t ece; /*Explicit Congestion notification echo*/
};

/*To calculate the fake checksum.
 * Source: CAPEC-287: TCP SYN Scan*/
struct pseudo_header
{
   uint32_t source_address;
   uint32_t dest_address;
   uint8_t placeholder;
   uint8_t protocol;
   uint16_t tcp_length;
   struct tcp_header tcp;
};

/*Function to populate the TCP header above.*/
void
fill_tcp_header(struct tcp_header* tcp_header, uint16_t source_port, uint16_t dest_port,
		uint32_t seq_num, uint32_t ack_num, uint16_t window_size, uint16_t urgent_ptr,
		uint8_t doff, uint8_t res1, struct tcp_flags flags);

/*Structure containing options for the "send_tcp_packet"
 * function.*/
struct tcp_packet_opts
{
    int source_port;
    const char* source_ip;
    unsigned int seq;
    int ttl;
/*Prepackage Presets.*/
#define SYN_PACKET            1
#define XMAS_PACKET           2
#define FIN_PACKET            3
#define NULL_PACKET           4
#define ACK_PACKET            5
#define WINDOW_PACKET         6
#define MAIMON_PACKET         7
	struct tcp_flags tcpf;
};

#include "ip4.h"
#define SEND_BUFFER_SIZE      2048
#define RECV_BUFFER_SIZE      2048
#define WINDOWS_SIZE          1024

/*Function for setting flags, per the preset above.*/
struct tcp_flags
set_flags(uint8_t packet_preset);

/*Function for random ident generation.*/
uint16_t
generate_ident(void);

/*Function for sending a TCP packet to a specified IP.
 * Using CAPEC-287, to calculate a fake checksum It is
 * intended for testing, but it is also suitable for real
 * programs. It works well in threads.*/
int 
send_tcp_packet(struct tcp_packet_opts *tpo, const char* ip, const int port, const int delay_ms);

/*The function for receiving TCP packet, as well as icmp
 * function uses packet sorting, and is made to work
 * in a large number of threads.*/
int
recv_tcp_packet(const char* dest_ip, int recv_timeout_ms, unsigned char **buffer);

/*An example of using the send and receive packet functions above, in the form of
 * creating an TCP ping using 2 methods:
 * TCP SYN, TCP ACK.*/
double
tcp_ping(int type, const char* ip, const char* source_ip, int dest_port, int source_port, int timeout_ms, int ttl);

/*Sources:
 * https://www.ietf.org/rfc/rfc793.txt
 * netinet/tcp.h
*/

#ifdef __cplusplus
}
#endif

#endif
