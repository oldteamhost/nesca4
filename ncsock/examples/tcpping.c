/*
 * NCSOCK-EXAMPLE
 * tcpping.c (by oldteam & lomaster) 
 * license GPL-2.0
 *   Сделано от души 2023-09-11
*/

#define ACK_PING

#include "../include/tcp.h"
#define SOURCE_PORT_DEFAULT 3343
#define DEST_PORT_DEFAULT 80
int timeout_ms = 1000, ttl = 64;

#include "../include/base.h"
#include <stdio.h>

#ifdef ACK_PING
  int type_tcp_packet = ACK_PACKET;
#elif defined(SYN_PING)
  int type_tcp_packet = SYN_PACKET;
#else
  int type_tcp_packet = ACK_PACKET;
#endif

void usage(char* run)
{
  printf("Usage: %s <ip> <timeout> <ttl>\n", run);
  exit(0);
}

int main(int argc, char** argv)
{
  if (argc <= 1) {usage(argv[0]);}

  if(!check_root_perms()) {
    puts("Only sudo run!");
    return 1;
  }

  if (argc > 2 && argv[2] != NULL) {
    timeout_ms = atoi(argv[2]);
  }
  if (argc > 3 && argv[3] != NULL) {
    ttl = atoi(argv[3]);
  }

  puts("Welcome to TCP ping (ncsock)");

  for (;;) {
    double rtt = tcp_ping(type_tcp_packet, argv[1], get_local_ip(), DEST_PORT_DEFAULT, SOURCE_PORT_DEFAULT, timeout_ms, ttl);
    if (rtt == -1) {
      puts("Error for more on (PRINT_ERRORS in ncsockopt.h)");
    }
    else {
      printf("ip=%s dest_port=%d ttl=%d rtt=%0.2fms\n",argv[1], DEST_PORT_DEFAULT, ttl, rtt);
    }

    usleep(300000); /*300ms*/
  }

}

