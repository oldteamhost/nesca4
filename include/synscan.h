#ifndef SYN_SCAN_H
#define SYN_SCAN_H

#include <iostream>
#include <cstdint>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/tcp.h>

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

unsigned short csum(unsigned short *ptr,int nbytes);

class syn_scan{
public:
      bool debug = false;
      // GOTO
      int s_timeout = 10;
      int r_timeout = 10;
      //
      const char* source_ip;
      void 
      create_tcp_header(struct tcphdr* tcph, int port);
      int 
      syn_scan_port(const char* ip, int port, int timeout_ms);

};

#endif
