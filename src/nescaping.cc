#include "../include/nescaping.h"
#include <mutex>

std::mutex fuck_send;
std::mutex fuck_buf;

uint16_t 
icmp_ping::RFC792_csum(unsigned char* buffer, unsigned int length){
    unsigned short *ptr = reinterpret_cast<unsigned short *>(buffer);
     unsigned int sum=0;
     unsigned short result;
              
     for ( sum = 0; length > 1; length -= 2 ){
        sum += *ptr++;
     }
     if ( length == 1 ){
         sum += *reinterpret_cast<unsigned char*>(ptr);
     }

     sum = (sum >> 16) + (sum & 0xFFFF);
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
      int msg_count = 0;

      struct timeval tv_out;
      tv_out.tv_sec = recv_timeout / 1000;
      tv_out.tv_usec = (recv_timeout % 1000) * 1000;

      int enable = 1;
      if (setsockopt(ping_sockfd, IPPROTO_IP, IP_HDRINCL, &enable, sizeof(enable)) < 0){
          return false;
      }

      if (setsockopt(ping_sockfd, SOL_SOCKET, SO_RCVTIMEO,
                    (const char*)&tv_out, sizeof tv_out) != 0){
          return false;
      }

      for (int i = 0; i < packets; i++){
          memset(&pckt, 0, sizeof(pckt));

          /*Решил добавить создание IP заголовка, хоть 
          это не обязательно, но мне так спокойней.*/          
          pckt.ip.version = 4;
          pckt.ip.ihl = 5;
          pckt.ip.tos = 0;
          pckt.ip.tot_len = htons(sizeof(struct icmp_packet));
          pckt.ip.id = htons(getpid());
          pckt.ip.frag_off = 0;
          pckt.ip.ttl = ttl_val;
          pckt.ip.protocol = IPPROTO_ICMP;
          pckt.ip.saddr = inet_addr(source_ip); // Отправитель
          pckt.ip.daddr = ping_addr->sin_addr.s_addr;
          pckt.ip.check = 0;
          pckt.ip.check = RFC792_csum(reinterpret_cast<unsigned char*>(&pckt.ip), sizeof(struct iphdr));

          int one = 1;
          const int *val = &one;

          if (setsockopt (ping_sockfd, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0){
              return false;
          }

          /*Заполнение ICMP заголовка.*/
          pckt.hdr.type = ICMP_ECHO;
          pckt.hdr.code = 0;
          pckt.hdr.checksum = 0;
          pckt.hdr.un.echo.id = getpid();

          for ( i = 0; i < sizeof(pckt.msg)-1; i++ )
              pckt.msg[i] = i+'0';

          pckt.msg[0] = 0;
          pckt.hdr.un.echo.sequence = msg_count++;

          pckt.hdr.checksum = 0;
          pckt.hdr.checksum = RFC792_csum(reinterpret_cast<unsigned char*>(&pckt), sizeof(pckt));

          delay_ms(ping_timeout);
          clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

          if (sendto(ping_sockfd, &pckt, sizeof(struct icmp_packet), 0, (struct sockaddr*) ping_addr, sizeof(*ping_addr)) <= 0){
              return false;
          }

          addr_len=sizeof(r_addr);

          if (recvfrom(ping_sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr*)&r_addr, reinterpret_cast<socklen_t*>(&addr_len)) <= 0) {
              return false;
          }

          clock_gettime(CLOCK_MONOTONIC_RAW, &time_end);

          double timeElapsed = ((double)(time_end.tv_nsec -
                          time_start.tv_nsec))/1000000.0;
          rtt_msec = (time_end.tv_sec-time_start.tv_sec) * 1000.0+ timeElapsed;

          if (pckt.hdr.type != 8 && pckt.hdr.code != 0){
              return false;
          }
          if (*rtt_msec_buffer < 0.01){
              return false;
          }

          /*Приходиться использовать mutex, без него вообще нету контроля.*/
          std::lock_guard<std::mutex> lock_buf(fuck_buf);
          *rtt_msec_buffer = rtt_msec;
      }
      return true;
}

int
icmp_ping::ping(const char* ip, long double* buffer_time){
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock == -1){
        return -1;
    }

    struct sockaddr_in addr_con;
    addr_con.sin_family = AF_INET;
    addr_con.sin_port = 0;

    if(inet_pton(AF_INET, ip, &(addr_con.sin_addr)) <= 0){
       return -1;
    }

    long double _buffer_time;
    bool temp = send_ping(sock, &addr_con, ip, &_buffer_time);

    if (temp == false){
        return -1;
    }

    *buffer_time = _buffer_time;
    return 0;
}

int udp_ping::ping_udp(const std::string & ip, int timeout, double& buffer){
    int sock, n;
    unsigned int length;
    struct sockaddr_in server, from;
    struct addrinfo hints, *res;
    int status;

    std::cout << std::endl;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    struct timespec tv;
    tv.tv_sec = timeout / 1000;                // Секунды
    tv.tv_nsec = (timeout % 1000) * 1000000;      // Микросекунды

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv)) == -1) {
        perror("setsockopt");
        close(sock);
        return -1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    status = getaddrinfo(ip.c_str(), nullptr, &hints, &res);

    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        close(sock);
        return -1;
    }

    std::memcpy(&server.sin_addr, &((struct sockaddr_in*)res->ai_addr)->sin_addr, sizeof(struct in_addr));
    server.sin_family = AF_INET;
    server.sin_port = htons(45443); // Номер порта 7 - протокол Echo
    length = sizeof(struct sockaddr_in);

    freeaddrinfo(res);


    int loss_count = 0;
    int time_recorded = 0;
    double min = 0.0;
    double max = 0.0;
    double total = 0.0;

    for (int i = 0; i < 10; i++) {
        std::string pingString = "PING " + std::to_string(i) + " ";
        std::time_t rawtime = std::time(nullptr);
        std::tm* timeinfo = std::localtime(&rawtime);
        char timeString[9];
        std::strftime(timeString, sizeof(timeString), "%H:%M:%S", timeinfo);
        std::string bufferString = pingString + timeString + "\n";

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        
        n = sendto(sock, bufferString.c_str(), bufferString.length(), 0, (const struct sockaddr*)&server, length);
        if (n < 0) {
            perror("sendto");
            close(sock);
            return -1;
        }

        char recvBuffer[256 + 1];
        n = recvfrom(sock, recvBuffer, sizeof(recvBuffer) - 1, 0, (struct sockaddr*)&from, &length);
        if (n < 0) {
            loss_count++;
            std::cout << "Request timeout." << std::endl;
            continue;
        }

        std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> duration = stop - start;
        double accum = duration.count();

        if (time_recorded == 0) {
            max = accum;
            min = accum;
        }
        time_recorded = 1;
        if (accum > max) max = accum;
        if (accum < min) min = accum;
        total += accum;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "Ping Received From " << ip << ": \n\n";
        std::cout << "seq#=" << i << " \n\n";
        std::cout << "time=" << std::fixed << std::setprecision(3) << accum << " ms\n\n" << std::endl;
        std::memset(recvBuffer, 0, sizeof(recvBuffer));
    }

    int received = 10 - loss_count;
    double percent = (loss_count / 10.0) * 100.0;
    std::cout << "--- ping statistics ---" << std::endl;
    std::cout << "10 packets transmitted, " << received << " packets received, " << std::setprecision(0) << percent << "% packet loss" << std::endl;
    if (time_recorded == 1) {
        double avg = total / received;
        std::cout << "round-trip min/avg/max = " << std::setprecision(3) << min << "/" << avg << "/" << max << " ms" << std::endl;
    }
    std::cout << std::endl;

    close(sock);
    buffer = min; // Записываем время ответа в буфер
    return 0;
}
