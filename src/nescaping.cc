#include "../include/nescaping.h"

uint16_t 
icmp_ping::RFC792_csum(unsigned char* buffer, unsigned int length){
     unsigned short *ptr = (unsigned short *)buffer;
     unsigned int sum=0;
     unsigned short result;
              
     for ( sum = 0; length > 1; length -= 2 ){
        sum += *ptr++;
     }
     if ( length == 1 ){
        sum += *(unsigned char*)ptr;
     }
     sum = (sum >> 16) + (sum & 0xFFFF);
     sum += (sum >> 16);
     result = ~sum;
     return result;
}

bool 
icmp_ping::send_ping(int ping_sockfd, struct sockaddr_in *ping_addr,
            const char *ping_ip, long double* rtt_msec_buffer){

      struct icmp_packet pckt;
      struct sockaddr_in r_addr;
      struct timespec time_start, time_end, tfs;
      long double rtt_msec=0, total_msec=0;

      struct timeval tv_out;
      tv_out.tv_sec = recv_timeout / 1000;
      tv_out.tv_usec = (recv_timeout % 1000) * 1000;

      clock_gettime(CLOCK_MONOTONIC, &tfs);

      if (setsockopt(ping_sockfd, SOL_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) != 0){
          return false;
      }

      setsockopt(ping_sockfd, SOL_SOCKET, SO_RCVTIMEO,
                    (const char*)&tv_out, sizeof tv_out);

      for (int i = 0; i < packets; i++){
          memset(&pckt, 0, sizeof(pckt));

          pckt.hdr.type = 8;
          pckt.hdr.un.echo.id = getpid();

          memset(pckt.msg, '0', sizeof(pckt.msg)-1);

          pckt.msg[0] = 0;
          pckt.hdr.un.echo.sequence = 0;

          pckt.hdr.checksum = 0;
          pckt.hdr.checksum = RFC792_csum(reinterpret_cast<unsigned char*>(&pckt), sizeof(pckt));

          clock_gettime(CLOCK_MONOTONIC, &time_start);

          delay_ms(ping_timeout);
          if ( sendto(ping_sockfd, &pckt, sizeof(pckt), 0,
                          (struct sockaddr*) ping_addr,
                          sizeof(*ping_addr)) <= 0){
              return false;
          }

          addr_len=sizeof(r_addr);

          if (recvfrom(ping_sockfd, &pckt, sizeof(pckt), 0,
                          (struct sockaddr*)&r_addr, reinterpret_cast<socklen_t*>(&addr_len)) <= 0){
              return false;
          }

          clock_gettime(CLOCK_MONOTONIC, &time_end);
          double timeElapsed = ((double)(time_end.tv_nsec -
                          time_start.tv_nsec))/1000000.0;
          rtt_msec = (time_end.tv_sec-time_start.tv_sec) * 1000.0+ timeElapsed;

          if (pckt.hdr.type != 8 && pckt.hdr.code != 0){
              return false;
          }

          *rtt_msec_buffer = rtt_msec;
      }
      return true;
}

int
icmp_ping::ping(const char* ip, long double* buffer_time){
    int sock = main_utils::create_raw_socket("icmp");
    if (sock == -1){
        return -1;
    }

    struct sockaddr_in addr_con;
    addr_con.sin_family = AF_INET;
    if(inet_pton(AF_INET, ip, &(addr_con.sin_addr)) <= 0){
       return -1;
    }
    addr_con.sin_port = 0;

    long double _buffer_time;
    bool temp = send_ping(sock, &addr_con, ip, &_buffer_time);

    if (temp == false){
        return -1;
    }

    *buffer_time = _buffer_time;
    return 0;
}
