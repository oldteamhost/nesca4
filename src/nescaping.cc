#include "../include/nescaping.h"

std::mutex fuck;

bool icmp_ping::ping(const char* address, int count, int timeout) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(address);

    std::lock_guard<std::mutex> guard(fuck);
    int sockfd = create_raw_sock("icmp");
    if (sockfd == -1) {
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
        icmp_hdr->icmp_type = ICMP_ECHO;
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

        if (icmp_hdr->icmp_type == ICMP_ECHOREPLY && icmp_hdr->icmp_id == (getpid() & 0xffff) && icmp_hdr->icmp_seq == seq) {
            end_time = std::chrono::high_resolution_clock::now();
            return true;
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
