/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
 * -----------------------------------------------------------
 * ip4.h - This file contains structures, constants, and
 * functions for working with IP protocol version 4. 
 * -----------------------------------------------------------
*/

#ifndef IP_4_H
#define IP_4_H

/* Support c++. */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

struct ip_header
{
    uint8_t ihl:4;
    uint8_t version:4;
    uint8_t tos:1;
    uint16_t tot_len;
    uint16_t id;
/* To fragment an IP packet. */
#define	IP_RF 0x8000			  /* Reserved fragment flag. */
#define	IP_DF 0x4000			  /* Dont fragment flag. */
#define	IP_MF 0x2000			  /* More fragments flag. */
#define	IP_OFFMASK 0x1fff		/* Mask for fragmenting bits. */
    uint16_t frag_off;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t check;
    uint32_t saddr;
    uint32_t daddr;
};

/* Function for calculating checksum for IP & TCP packets. */
uint16_t checksum_16bit(const uint16_t* data, int length);

/* Function to populate the IP header above. */
void 
fill_ip_header(struct ip_header* ip_header, const char* source_ip, const char* dest_ip, uint16_t packet_length,
                    uint8_t protocol, uint16_t identification, uint16_t flags_fragoffset, uint8_t ttl,
                    uint8_t ihl, uint8_t version, uint8_t tos);

/* Sources:
 * https://datatracker.ietf.org/doc/html/rfc791
 * netinet/ip.h
*/

#ifdef __cplusplus
}
#endif

#endif
