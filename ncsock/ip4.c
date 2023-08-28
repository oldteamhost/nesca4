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

#include "include/ip4.h"

uint16_t checksum_16bit(const uint16_t* data, int length)
{
  uint32_t sum = 0;
  while (length > 1) {
    sum += *data++;
    length -= 2;
  }
  if (length == 1) {sum += *((uint8_t*)data);}
  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);

  return (uint16_t)~sum;
}

void 
fill_ip_header(struct ip_header* ip_header, const char* source_ip, const char* dest_ip, uint16_t packet_length,
                    uint8_t protocol, uint16_t identification, uint16_t flags_fragoffset, uint8_t ttl,
                    uint8_t ihl, uint8_t version, uint8_t tos)
{
  memset(ip_header, 0, sizeof(struct ip_header));
  ip_header->saddr = inet_addr(source_ip);
  ip_header->daddr = inet_addr(dest_ip);
  ip_header->tot_len = htons(packet_length);
  ip_header->protocol = protocol;
  ip_header->id = htons(identification);
  ip_header->frag_off = htons(flags_fragoffset);
  ip_header->ttl = ttl;
  ip_header->ihl = ihl;
  ip_header->version = version;
  ip_header->tos = tos;
  ip_header->check = 0;
}
