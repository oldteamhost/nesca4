/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/icmpproto.h"

int 
send_icmp_packet(struct sockaddr_in* addr, int type,
				int code, int ident, int seq, int ttl){
	int fd_ = fd(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd_ == EOF){return -1;}
	if (setsockopt(fd_, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0){fuck_fd(fd_);return -1;}

	struct icmp4_header icmp;
	memset(&icmp, 0, sizeof(icmp));

	fill_icmp_header(&icmp, type, code, 0, ident, seq);
	strncpy(icmp.magic, MAGIC, MAGIC_LEN);
	icmp.checksum = htons(checksum_16bit_icmp((unsigned char*)&icmp, sizeof(icmp)));

	const int bytes = sendto(fd_, &icmp, sizeof(icmp), 0,(struct sockaddr*)addr, sizeof(*addr));
    if (bytes == EOF) {
		fuck_fd(fd_);
        return -1;
    }
	fuck_fd(fd_);
	return 0;
}

int 
recv_icmp_packet(const char* dest_ip, int timeout_ms, int type,
				int code, int identm){

	int fd_ = fd(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd_ == EOF){return -1;}

    char buffer[1500];
    struct sockaddr_in peer_addr;
	memset(&peer_addr, 0, sizeof(peer_addr));

	/*Установка таймаута на сокет*/
	int result = set_socket_timeout(fd_, timeout_ms, 1, 1);
	if (result < 0) {
		fuck_fd(fd_);
    	return -1;
	}

    int addr_len = sizeof(peer_addr);
    auto start_time = std::chrono::steady_clock::now();
	for (;;){
    	int bytes = recvfrom(fd_, buffer, sizeof(buffer), 0,(struct sockaddr*)&peer_addr, (socklen_t *)&addr_len);
		if (bytes == EOF) {
			/*Сработал таймаут.*/
			if (errno == EAGAIN || errno == EWOULDBLOCK){
				fuck_fd(fd_);
				return -1;
			}
			/*Просто ошибка.*/
			fuck_fd(fd_);
        	return -1;
    	}
		/*Получение IP заголовка.*/
		struct ip_header *iph = (struct ip_header*)buffer;

		/*Поулучение из него IP отправителя.*/
	   	struct sockaddr_in source;
	   	memset(&source, 0, sizeof(source));
	   	source.sin_addr.s_addr = iph->saddr;
		struct in_addr dest; dest.s_addr = inet_addr(dest_ip);

		if (source.sin_addr.s_addr != dest.s_addr){
		  	auto current_time = std::chrono::steady_clock::now();
		  	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
		  	if (elapsed_time >= timeout_ms) {
				fuck_fd(fd_);
			 	return -1;
		  	}
			continue;
		}
		else {
			struct icmp4_header* icmp = (struct icmp4_header*)(buffer + 20);
			if (type == ICMP_ECHO){
				if (icmp->type == ICMP_ECHOREPLY){
					fuck_fd(fd_);
					return 0;
				}
			}
			if (type == ICMP_TIMESTAMP){
				if (icmp->type == ICMP_TIMESTAMPREPLY){
					fuck_fd(fd_);
					return 0;
				}
			}
			if (type == ICMP_INFO_REQUEST){
				if (icmp->type == ICMP_INFO_REPLY){
					fuck_fd(fd_);
					return 0;
				}
			}
		}
		break;
	}

	fuck_fd(fd_);
	return -1;
}
