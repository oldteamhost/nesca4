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

#include "include/tcp.h"
#include <netinet/in.h>
#include <unistd.h>

uint16_t
generate_ident(void){
	static int initialized = 0;
    if (!initialized) {
        srand(clock());
        initialized = 1;
    }
    unsigned int seq_res = rand() % 65536;
    return seq_res;
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
    tcp_header->check = 0;

	/*Flags are set from the tcp_flags structure.*/
    tcp_header->syn = flags.syn;
    tcp_header->ack = flags.ack;
    tcp_header->rst = flags.rst;
    tcp_header->fin = flags.fin;
    tcp_header->psh = flags.psh;
    tcp_header->urg = flags.urg;
    tcp_header->ece = flags.ece;
    tcp_header->cwr = flags.cwr;
}

struct tcp_flags
set_flags(uint8_t packet_preset)
{
	struct tcp_flags tpf;
	tpf.rst = 0;
    tpf.ack = 0;
	switch (packet_preset) {
    case SYN_PACKET:
        tpf.syn = 1;
        tpf.fin = 0;
        tpf.psh = 0;
        tpf.urg = 0;
        break;
    case XMAS_PACKET:
        tpf.syn = 0;
        tpf.fin = 1;
        tpf.psh = 1;
        tpf.urg = 1;
        break;
    case FIN_PACKET:
        tpf.syn = 0;
        tpf.fin = 1;
        tpf.psh = 0;
        tpf.urg = 0;
        break;
    case NULL_PACKET:
        tpf.syn = 0;
        tpf.fin = 0;
        tpf.psh = 0;
        tpf.urg = 0;
        break;
    case WINDOW_PACKET:
    case ACK_PACKET:
        tpf.syn = 0;
        tpf.fin = 0;
        tpf.psh = 0;
        tpf.urg = 0;
        tpf.ack = 1;
        break;
    case MAIMON_PACKET:
        tpf.syn = 0;
        tpf.fin = 1;
        tpf.psh = 0;
        tpf.urg = 0;
        tpf.ack = 1;
        break;
	}

	return tpf;
}

int 
send_tcp_packet(struct tcp_packet_opts *tpo, const char* ip, const int port, const int delay_ms){
    char datagram[SEND_BUFFER_SIZE];
    memset(datagram, 0, SEND_BUFFER_SIZE);

    struct sockaddr_in dest;
    struct pseudo_header psh;

    struct ip_header *iph_send = (struct ip_header*)datagram;
    struct tcp_header *tcph_send = (struct tcp_header*)(datagram + sizeof(struct ip_header));

	/*Delay, default = 0.*/
	struct timespec ts;
    ts.tv_sec = delay_ms / 1000;
    ts.tv_nsec = (delay_ms % 1000) * 1000000;
    nanosleep(&ts, NULL);

	/*Creation sock.*/
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock == -1) {
#ifdef PRINT_ERRORS
		perror("send_tcp_packet/create-socket-error");
#endif
		return -1;
	}

	/*Let the kernel know that we are sending our IP header 
	 * and we don't need to generate it.*/
    int one = 1;
    const int *val = &one;
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0)
	{
#ifdef PRINT_ERRORS
		perror("send_tcp_packet/setsockopt-error(IP_HDRINCL)");
#endif
		close(sock);
        return -1;
    }
#define DOFF 5
#define RES1 0
#define ACK_NUM 0
#define URG_PTR 0
	/*Fill TCP header.*/
    fill_tcp_header(tcph_send, tpo->source_port, port, tpo->seq, ACK_NUM, WINDOWS_SIZE, URG_PTR,
		  DOFF, RES1, tpo->tcpf);

	/*Calculate the packet size.*/
	const uint16_t packet_length = sizeof(struct ip_header) + sizeof(struct tcp_header);

	/*Fill IP header.*/
    fill_ip_header(iph_send, tpo->source_ip, ip, packet_length,
		        IPPROTO_TCP, generate_ident(), IP_DF, tpo->ttl, 5, 4, 0);

	/*Calculate IP header checksum.*/
    const uint16_t check_sum_ip = checksum_16bit((unsigned short *)datagram, iph_send->tot_len >> 1); 
    iph_send->check = check_sum_ip;

	/*Set target for sendto.*/
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(ip);

	/*Fille pseudo_header for calc fake checksum.*/
    psh.source_address = iph_send->saddr;
    psh.dest_address = dest.sin_addr.s_addr; 
    psh.placeholder = 0;
    psh.protocol = iph_send->protocol;
    psh.tcp_length = htons(sizeof(struct tcp_header));
    memcpy(&psh.tcp, tcph_send, sizeof(struct tcp_header));

	/*Calculate fake checksum.*/
    const uint16_t check_sum_tcp = checksum_16bit((unsigned short*)&psh, sizeof(struct pseudo_header));
    tcph_send->check = check_sum_tcp;

	/*Send TCP packet.*/
    const int send = sendto(sock, datagram, packet_length, 0,
		  (struct sockaddr*)&dest, sizeof(dest));
    if (send == -1)
	{
#ifdef PRINT_ERRORS
		perror("send_tcp_packet/sendto-error");
#endif
	   close(sock);
	   return -1;
    }
#ifdef PACKET_TRACE
	printf("TCP & SENT %d bytes on %s: ttl=%d ident=%d window=%d seq=%d sum=%d\n",
			packet_length, ip, iph_send->ttl, iph_send->id, tcph_send->window, tcph_send->seq, iph_send->check);
#endif

    close(sock);
    return 0;
}

int
recv_tcp_packet(const char* dest_ip, int recv_timeout_ms, unsigned char **buffer)
{
	/*Set target.*/
	struct in_addr dest;
    dest.s_addr = inet_addr(dest_ip);

	/*Temporary buffer*/
    unsigned char* read_buffer = *buffer;

	/*Creation sock.*/
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock == -1)
	{
#ifdef PRINT_ERRORS
		perror("recv_tcp_packet/create-socket-error");
#endif
        return -1;
    }

	/*Set timeout on socket.*/
    struct timeval timeout;
    timeout.tv_sec = recv_timeout_ms / 1000;
    timeout.tv_usec = (recv_timeout_ms % 1000) * 1000;
	int result = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
    if (result == -1)
	{
#ifdef PRINT_ERRORS
		perror("recv_tcp_packet/setsockopt-error(timeout)");
#endif
		/*Timeout.*/
        close(sock);
        return -1;
    }

    struct sockaddr saddr;
    time_t start_time = time(NULL);

	/*Infinite loop, on accepting all ICMP packets.*/
    for (;;)
	{
		/*Updating the IP size with each new packet.*/
    	int saddr_size = sizeof(saddr);
        int data_size = recvfrom(sock, read_buffer, RECV_BUFFER_SIZE, 0, &saddr, (socklen_t*)&saddr_size);
        if (data_size == -1)
		{
#ifdef PRINT_ERRORS
		perror("recv_tcp_packet/recvfrom-error");
#endif
            close(sock);
            return -1;
        }

		/*Creating an IP stub to verify packet sorting.*/
        struct ip_header* iph = (struct ip_header*)read_buffer;
        unsigned short iphdrlen = (iph->ihl) * 4;
        if (iphdrlen < 20){close(sock);return -1;}

		/*Obtains the sender's IP from the RECEIVED packet.*/
        struct sockaddr_in source;
        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = iph->saddr;

		/*Comparing the IP from the received packet with the IP
		 * to which the packet was sent.*/
        if (source.sin_addr.s_addr != dest.s_addr)
		{
            time_t current_time = time(NULL);
            int elapsed_time = (int)(current_time - start_time) * 1000;

			/*Timeout on a windowless loop where packets are received.*/
            if (elapsed_time >= recv_timeout_ms)
			{
#ifdef PRINT_ERRORS
	printf("recv_tcp_packet/timeout: a timeout on the packet receiving loop has occurred.\n");
#endif
                close(sock);
                return -1;
            }
            continue;
        } else
		{
#ifdef PACKET_TRACE
    struct tcp_header* tcph = (struct tcp_header*)read_buffer;
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(source.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
	printf("TCP & RCVD %d bytes from %s: ttl=%d ident=%d window=%d seq=%d sum=%d\n",
			(int)sizeof(&iph)+(int)sizeof(&tcph), ip_str, iph->ttl, iph->id, tcph->window, tcph->seq, iph->check);
#endif

			/*Succes read, fill bufer.*/
            *buffer = read_buffer;
            close(sock);
            return 0;
        }
    }

    /*Ну ок :)*/
    close(sock);
    return -1;
}

#include <pthread.h>
double
tcp_ping(int type, const char* ip, const char* source_ip, int dest_port, int source_port, int timeout_ms, int ttl)
{
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

	double response_time = -1;
	struct tcp_packet_opts ncops;
	ncops.source_ip = source_ip;
	ncops.seq = generate_ident()*2;
	ncops.ttl = ttl;
	ncops.source_port = source_port;
	ncops.tcpf = set_flags(type);

    /*Send TCP packet.*/
	int send = send_tcp_packet(&ncops, ip, dest_port, 0);
	if (send == EOF){return -1;}

    /*Create buffer on recv TCP packet.*/
    pthread_mutex_lock(&mutex);
	unsigned char *buffer = (unsigned char *)calloc(RECV_BUFFER_SIZE, sizeof(unsigned char));
    pthread_mutex_unlock(&mutex);

    /*Start time for recv packet.*/
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    /*Recv TCP packet.*/
	int read = recv_tcp_packet(ip, timeout_ms, &buffer);
	if (read != 0)
	{
        pthread_mutex_lock(&mutex);
		free(buffer);
        pthread_mutex_unlock(&mutex);
		return -1;
	}
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    struct ip_header *iph = (struct ip_header*)buffer;
    unsigned short iphdrlen = (iph->ihl) * 4;
    if (iph->protocol != 6) {return -1;}
    struct tcp_header *tcph = (struct tcp_header*)((char*)buffer + iphdrlen);

    if (type == SYN_PACKET){
	    if (tcph->th_flags != 0)
	    {
            /*End time, and calc differense.*/
            response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
                            (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
	    }
    }
    else {
	    if (tcph->th_flags == TH_RST)
	    {
            /*End time, and calc differense.*/
            response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
                            (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
	    }
    }

    pthread_mutex_lock(&mutex);
	free(buffer);
    pthread_mutex_unlock(&mutex);
	return response_time;
}
