#ifndef SYN_SCAN_H
#define SYN_SCAN_H

#include <iostream>
#include <cstdint>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string>
#include <random>
#include <netdb.h>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <mutex>
#include <netinet/in.h>
#include <vector>

#include "../modules/include/easysock.h"
#include "../include/prints.h"
#include "../include/other.h"

#define PORT_OPEN 0
#define PORT_CLOSED 1
#define PORT_FILTER 2
#define PORT_ERROR -1

struct pseudo_header{
   unsigned int source_address;
   unsigned int dest_address;
   unsigned char placeholder;
   unsigned char protocol;
   unsigned short tcp_length;
   struct tcphdr tcp;
};

static unsigned short csum(unsigned short *ptr,int nbytes);

class syn_scan{
public:
      bool debug = false;
	 bool fin = false;
	 bool null = false;
	 bool xmas = false;

      // GOTO
      int s_timeout;
      int r_timeout;
      //
      const char* source_ip;
      void
      create_ip_header(struct iphdr *iph, const char *source_ip, struct in_addr dest_ip);
	 static void
      set_tcp_flags(struct tcphdr* tcph, int syn, int ack, int fin, int rst, int urg, int phs);
      void 
      create_tcp_header(struct tcphdr* tcph, int port);
	 int
      get_port_status(uint8_t flags);
      int 
      syn_scan_port(const char* ip, int port, int timeout_ms);


};

#endif
