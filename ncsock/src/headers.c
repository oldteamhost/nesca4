#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>
#include "../include/headers.h"

uint16_t checksum_16bit(const uint16_t* data, int length) {
    uint32_t sum = 0;
    while (length > 1) {
        sum += *data++;
        length -= 2;
    }
    if (length == 1){
        sum += *((uint8_t*)data);
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return (uint16_t)~sum;
}

void fill_ip_header(struct iphdr* ip_header, const char* source_ip, const char* dest_ip, uint16_t packet_length,
                    uint8_t protocol, uint16_t identification, uint16_t flags_fragoffset, uint8_t ttl,
                    uint8_t ihl, uint8_t version, uint8_t tos){
    memset(ip_header, 0, sizeof(struct iphdr));
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

void fill_tcp_header(struct tcphdr* tcp_header, uint16_t source_port, uint16_t dest_port, uint32_t seq_num, uint32_t ack_num,
                     uint16_t window_size, uint16_t urgent_ptr, uint8_t doff, uint8_t res1, struct tcp_flags flags){
    memset(tcp_header, 0, sizeof(struct tcphdr));
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

void fill_icmp_header(struct icmp* icmp_header, uint8_t type, uint8_t code,
                      uint16_t identifier, uint16_t sequence){
    memset(icmp_header, 0, sizeof(struct icmphdr));
    icmp_header->icmp_type = type;
    icmp_header->icmp_code = code;
    icmp_header->icmp_id = htons(identifier);
    icmp_header->icmp_seq = sequence; 
    icmp_header->icmp_cksum = 0;
}

