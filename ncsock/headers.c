/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/headers.h"

uint16_t checksum_16bit(const uint16_t* data, int length)
{
    uint32_t sum = 0;
    while (length > 1)
	{
        sum += *data++;
        length -= 2;
    }
    if (length == 1) {sum += *((uint8_t*)data);}

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return (uint16_t)~sum;
}

uint16_t
checksum_16bit_icmp(unsigned char* buffer, int bytes)
{
    uint32_t checksum = 0;
    unsigned char* end = buffer + bytes;

    if (bytes % 2 == 1){end = buffer + bytes - 1;checksum += (*end) << 8;}

    while (buffer < end)
	{
        checksum += buffer[0] << 8;
        checksum += buffer[1];
        buffer += 2;
    }

    uint32_t carray = checksum >> 16;
    while (carray)
	{
        checksum = (checksum & 0xffff) + carray;
        carray = checksum >> 16;
    }

    checksum = ~checksum;
    return checksum & 0xffff;
}

void fill_ip_header(struct ip_header* ip_header, const char* source_ip, const char* dest_ip, uint16_t packet_length,
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

void fill_tcp_header(struct tcp_header* tcp_header, uint16_t source_port, uint16_t dest_port, uint32_t seq_num, uint32_t ack_num,
                     uint16_t window_size, uint16_t urgent_ptr, uint8_t doff, uint8_t res1, struct tcp_flags flags)
{
    memset(tcp_header, 0, sizeof(struct tcp_header));
    tcp_header->source = htons(source_port);
    tcp_header->dest = htons(dest_port);
    tcp_header->seq = htonl(seq_num);
    tcp_header->ack_seq = htonl(ack_num);
    tcp_header->window = htons(window_size);
    tcp_header->urg_ptr = htons(urgent_ptr);
    tcp_header->doff = doff;
    tcp_header->res1 = res1;
    tcp_header->syn = flags.syn;
    tcp_header->ack = flags.ack;
    tcp_header->rst = flags.rst;
    tcp_header->fin = flags.fin;
    tcp_header->psh = flags.psh;
    tcp_header->urg = flags.urg;
    tcp_header->check = 0;
}

void
fill_icmp_header(struct icmp4_header* icmp4_header, uint8_t type, uint8_t code, uint16_t checksum,
		uint16_t ident, uint16_t seq)
{
	icmp4_header->checksum = checksum;
	icmp4_header->ident = htons(ident);
	icmp4_header->code = code;
	icmp4_header->type = type;
	icmp4_header->seq = htons(seq);
}
