/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
 * -----------------------------------------------------------
 * icmp4.c - It contains structures, constants and functions
 * for working with ICMP protocol. Obsolete message types and
 * really nerdy codes have been removed from here.
 * -----------------------------------------------------------
*/

#include "include/icmp4.h"
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

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

void
fill_icmp_header(struct icmp4_header* icmp4_header, uint8_t type, uint8_t code, uint16_t checksum,
		uint16_t ident, uint16_t seq)
{
	icmp4_header->checksum = checksum;
	icmp4_header->ident = htons(ident);
	icmp4_header->code = code;
	icmp4_header->type = type;
	icmp4_header->seq = htons(seq);
	/*Magic this is packet buffer.*/
}

int 
send_icmp_packet(struct sockaddr_in* addr, int type,
				int code, int ident, int seq, int ttl){

	/*Create IPPROTO_ICMP sock raw.*/
	int fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd == -1)
	{
#ifdef PRINT_ERRORS
		perror("send_icmp_packet/create-socket");
#endif
		return -1;
	}

	/*Set ttl on socket.*/
	if (setsockopt(fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
	{
#ifdef PRINT_ERRORS
		perror("send_icmp_packet/setsockopt(TTL)");
#endif
		close(fd);
		return -1;
	}

	/*Create and clean ICMP header.*/
	struct icmp4_header icmp; memset(&icmp, 0, sizeof(icmp));

	/*Fill ICMP header*/
	fill_icmp_header(&icmp, type, code, 0, ident, seq);

	/*Fill ICMP buffer.*/
	strncpy(icmp.magic, MAGIC, MAGIC_LEN);

	uint16_t checksum = htons(checksum_16bit_icmp((unsigned char*)&icmp, sizeof(icmp)));
	icmp.checksum = checksum;

	/*Send packet.*/
	const int bytes = sendto(fd, &icmp, sizeof(icmp), 0,(struct sockaddr*)addr, sizeof(*addr));
    if (bytes == -1)
	{
#ifdef PRINT_ERRORS
		perror("send_icmp_packet/sendto");
#endif
		close(fd);
        return -1;
    }

#ifdef PACKET_TRACE
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(addr->sin_addr), ip_str, INET_ADDRSTRLEN);
	printf("ICMP & SENT %d bytes on %s: ttl=%d ident=%d type=%d code=%d icmp_seq=%d sum=%d\n",
			(int)sizeof(icmp), ip_str, ttl, ident, type, code, seq, checksum);
#endif

	close(fd);
	return 0;
}

int 
recv_icmp_packet(const char* dest_ip, int timeout_ms, int type,
				int code)
{
	int fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (fd == -1)
	{
#ifdef PRINT_ERRORS
		perror("recv_icmp_packet/create-socket");
#endif
        return -1;
    }

	/*Buffer for packet.*/
    char buffer[2048];
    struct sockaddr_in peer_addr;
    memset(&peer_addr, 0, sizeof(peer_addr));

	struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

	/*Set timeout on socket.*/
	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) == -1)
	{
#ifdef PRINT_ERRORS
		perror("recv_icmp_packet/setsockopt(recv-timeout)");
#endif
		close(fd);
		return -1;
	}

    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

	/*Infinite loop, on accepting all ICMP packets.*/
    for (;;)
	{
		/*Updating the IP size with each new packet.*/
    	int addr_len = sizeof(peer_addr);
        int bytes = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&peer_addr, (socklen_t *)&addr_len);
        if (bytes < 0)
		{
#ifdef PRINT_ERRORS
		perror("recv_icmp_packet/recvfrom");
#endif
			/*Timeout.*/
            if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
                close(fd);
                return -1;
            }
            close(fd);
            return -1;
        }
		/*Creating an IP stub to verify packet sorting.*/
        struct ip_header *iph = (struct ip_header*)buffer;

		/*Verification of the received packet's protocol.*/
		if (iph->protocol != IPPROTO_ICMP){close(fd);continue;}

		/*Obtains the sender's IP from the RECEIVED packet.*/
        struct sockaddr_in source;
        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = iph->saddr;
        struct in_addr dest; dest.s_addr = inet_addr(dest_ip);

		/*Comparing the IP from the received packet with the IP
		 * to which the packet was sent.*/
        if (source.sin_addr.s_addr != dest.s_addr)
		{
            struct timespec current_time;
            clock_gettime(CLOCK_MONOTONIC, &current_time);
            long elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000 + (current_time.tv_nsec - start_time.tv_nsec) / 1000000;

			/*Timeout on a windowless loop where packets are received.*/
            if (elapsed_time >= timeout_ms)
			{
#ifdef PRINT_ERRORS
	printf("recv_icmp_packet/timeout: a timeout on the packet receiving loop has occurred.\n");
#endif
            	close(fd);
                return -1;
            }
            continue;
        } else 
		{
			/*The packet was received, checking its type and code.*/
            struct icmp4_header* icmp = (struct icmp4_header*)(buffer + 20);

#ifdef PACKET_TRACE
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(source.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
	printf("ICMP & RCVD %d bytes from %s: ttl=%d ident=%d type=%d code=%d icmp_seq=%d sum=%d\n",
			(int)sizeof(&icmp), ip_str, iph->ttl, icmp->ident, icmp->type, icmp->code, icmp->seq, icmp->checksum);
#endif

            if (type == ICMP_ECHO)
			{
                if (icmp->type == ICMP_ECHOREPLY)
				{
            		close(fd);
                    return 0;
                }
            }
            if (type == ICMP_TIMESTAMP)
			{
                if (icmp->type == ICMP_TIMESTAMPREPLY)
				{
            		close(fd);
                    return 0;
                }
            }
            if (type == ICMP_INFO_REQUEST)
			{
                if (icmp->type == ICMP_INFO_REPLY)
				{
            		close(fd);
                    return 0;
                }
            }

			/*Checking for host errors.*/
			if (icmp->type == ICMP_DEST_UNREACH ||
				icmp->type == ICMP_TIME_EXCEEDED ||
				icmp->type == ICMP_PARAMETERPROB ||
				icmp->type == ICMP_REDIRECT){
#ifdef PRINT_ERRORS
	printf("recv_icmp_packet/wrong-packet: a packet with an error type was received: code=%d type=%d\n", icmp->code, icmp->type);
#endif
    			close(fd);
				return icmp->code;
			}
        }
        break;
    }

#ifdef PRINT_ERRORS
	puts("Other error");
#endif
    close(fd);
    return -1;
}

double
icmp_ping(const char* dest_ip, int timeout_ms, int type, int code, int seq, int ttl)
{
	double response_time = -1;
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
    addr.sin_port = 0;

    if (inet_aton(dest_ip, (struct in_addr*)&addr.sin_addr.s_addr) == 0){return -1;};
    int ident = getpid();

    /*Send ICMP packet.*/
	int ret = send_icmp_packet(&addr, type, code, ident, seq, ttl);
	if (ret == EOF) {return -1;}

    /*Start time for recv packet.*/
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    /*Recv ICMP_PACKET*/
	ret = recv_icmp_packet(dest_ip, timeout_ms, type, code);
	if (ret == EOF) {return -1;}

    /*End time, and calc differense.*/
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

	/*Source - https://nmap.org/man/ru/man-host-discovery.html*/
    /*Source - https://gist.github.com/bugparty/ccba5744ba8f1cece5e0*/
    /*Source - https://datatracker.ietf.org/doc/html/rfc792*/

	return response_time;
}


