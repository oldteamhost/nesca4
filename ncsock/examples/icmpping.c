/*
 * NCSOCK-EXAMPLE
 * icmpping.c (by oldteam & lomaster) 
 * license GPL-2.0
 *   Сделано от души 2023-09-11
*/

#define ECHO_PING
#include "../include/icmp4.h"
int timeout_ms = 1000, ttl = 64, icmp_seq = 1;

#ifdef ECHO_PING
  int type_icmp_packet = ICMP_ECHO;
#elif defined(TIMESTAMP_PING)
  int type_icmp_packet = ICMP_TIMESTAMP;
#elif defined(INFO_REQUEST_PING)
  int type_icmp_packet = ICMP_INFO_REQUEST;
#else
  int type_icmp_packet = ICMP_ECHO;
#endif

#include <stdlib.h>
#include "../include/base.h"

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

  puts("Welcome to ICMP ping (ncsock)");

  for (;;) {
    double rtt = icmp_ping(argv[1], timeout_ms, type_icmp_packet, 0, ++icmp_seq, ttl);

    if (rtt == -1) {
      puts("Error for more on (PRINT_ERRORS in ncsockopt.h)");
    }
    else if (rtt == ICMP_DEST_UNREACH) {
      puts("ICMP_DEST_UNREACH");
    }
    else if (rtt == ICMP_TIME_EXCEEDED) {
      puts("ICMP_TIME_EXCEEDED");
    }
    else if (rtt == ICMP_PARAMETERPROB) {
      puts("ICMP_PARAMETERPROB");
    }
    else if (rtt == ICMP_REDIRECT) {
      puts("ICMP_REDIRECT");
    }
    else {
      printf("ip=%s icmp_seq=%d ttl=%d rtt=%0.2fms\n",argv[1], icmp_seq, ttl, rtt);
    }
    usleep(300000); /*300ms*/
  }

  return 0;
}
