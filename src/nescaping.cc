#include "../include/nescaping.h"

std::mutex fuck;
unsigned short calculate_checksum(unsigned short *ptr, int nbytes) {
    unsigned long sum;
    unsigned short oddbyte;
    unsigned short answer;

    sum = 0;
    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }

    if (nbytes == 1) {
        oddbyte = 0;
        *((u_char *)&oddbyte) = *(u_char *)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = (unsigned short)~sum;

    return answer;
}

bool icmp_ping::ping(const char* address, int count, int timeout) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(address);

    //std::lock_guard<std::mutex> guard(fuck);
    int sockfd = create_raw_sock("icmp");
    if (sockfd == -1) {
        return false;
    }

    int ttl = 64;
    int result = setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
    if (result < 0) {
	   return false;
    }

    int seq = 0;
    for (int i = 0; i < count; i++) {
        seq++;
        if (send_packet(sockfd, addr, seq) && receive_packet(sockfd, addr, seq, timeout)) {
            last_time = get_time();
        } else{
		  close(sockfd);
		  return false;
	   }
    }

    close(sockfd);
    return true;
}

double icmp_ping::get_last_time() {
    return last_time;
}

bool icmp_ping::send_packet(int sockfd, struct sockaddr_in addr, int seq) {
        char packet[64];
        memset(packet, 0, sizeof(packet));

        struct icmp* icmp_hdr = (struct icmp*) packet;
	   /*Ставим именно ICMP_ECHO aka 8 type, потому что
	   мы шлём ECHO пакет, а в ответ должны получить ICMP_ECHOREPLY
	   пакет. Это значит что нам ответили.*/
	   if (type == 1){
		  icmp_hdr->icmp_type = ICMP_ECHO;
	   }
	   else if (type == 2){
		  icmp_hdr->icmp_type = 13;
	   }
	   else if (type == 3){
		  icmp_hdr->icmp_type = 15;
	   }
        icmp_hdr->icmp_code = 0;
        icmp_hdr->icmp_id = getpid() & 0xffff;
        icmp_hdr->icmp_seq = seq;
        icmp_hdr->icmp_cksum = 0;
        icmp_hdr->icmp_cksum = checksum((unsigned short*) icmp_hdr, sizeof(struct icmp));

        start_time = std::chrono::high_resolution_clock::now();

        if (sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
            return false;
        }

        return true;
}

bool icmp_ping::receive_packet(int sockfd, struct sockaddr_in addr, int seq, int timeout) {
        char packet[64];
        memset(packet, 0, sizeof(packet));

        struct sockaddr_in from_addr;
        socklen_t from_len = sizeof(from_addr);

        fd_set read_set;
        FD_ZERO(&read_set);
        FD_SET(sockfd, &read_set);

        struct timeval tv;
        tv.tv_sec = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;

        int n = select(sockfd + 1, &read_set, NULL, NULL, &tv);
        if (n < 0) {
            return false;
        } else if (n == 0) {
            return false;
        }

        if (recvfrom(sockfd, packet, sizeof(packet), 0, (struct sockaddr*) &from_addr, &from_len) < 0) {
            return false;
        }

        struct iphdr* ip_hdr = (struct iphdr*) packet;
        struct icmp* icmp_hdr = (struct icmp*) (packet + (ip_hdr->ihl << 2));

	   /*Трушная обработка (CASUAL МЕТОД)*/
	   if (type == 1){
		  if (icmp_hdr->icmp_type == ICMP_ECHOREPLY){
			 end_time = std::chrono::high_resolution_clock::now();
			 return true;
		  }
	   }
	   /*Запрос на временную метку, тоже может действовать как проверка хоста.*/
	   else if (type == 2){
		  if (icmp_hdr->icmp_type == 14){
			 end_time = std::chrono::high_resolution_clock::now();
			 return true;
		  }
	   }
	   /*Адрес источника, тоже неплохо для проверки доступности.*/
	   else if (type == 3){
		  if (icmp_hdr->icmp_type == 16){
			 end_time = std::chrono::high_resolution_clock::now();
			 return true;
		  }
	   }

        return false;
}


unsigned short icmp_ping::checksum(unsigned short* buf, int len) {
    unsigned long sum = 0;
    while (len > 1) {
        sum += *buf++;
        len -= 2;
    }
    if (len == 1) {
        sum += *(unsigned char*) buf;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (unsigned short) ~sum;
}

double icmp_ping::get_time() {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    return (double) duration.count() / 1000;
}

bool
tcp_ping::ping(const char* ip, int port, int timeout_ms){
    int sockfd = create_sock("tcp");
    if (sockfd == -1) {
        return false;
    }

    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags < 0) {
        close(sockfd);
        return false;
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
        close(sockfd);
        return false;
    }

    // Установка адреса назначения
    struct sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &(server_address.sin_addr)) <= 0) {
        close(sockfd);
        return false;
    }

    struct timeval timeout{};
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        close(sockfd);
        return false;
    }

    int result = connect(sockfd, reinterpret_cast<struct sockaddr*>(&server_address), sizeof(server_address));

    if (result == 0 || errno == ECONNREFUSED) {
        close(sockfd);
        return true;
    } 
    else if (errno == EINPROGRESS) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(sockfd, &fds);

        result = select(sockfd + 1, nullptr, &fds, nullptr, &timeout);
        if (result > 0) {
            close(sockfd);
            return true;
        }
    }

    close(sockfd);
    return false;
}

