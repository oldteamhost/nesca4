#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include "../include/eth.h"
#include "../include/ip.h"
#include "../include/utils.h"
#include "../include/icmp.h"

int main(void)
{
  /*
  struct ethtmp eth;
  struct sockaddr_in dst;
  u8 *packet;
  u32 packetlen;

  packet = build_icmp_pkt(inet_addr("192.168.1.35"), inet_addr("64.233.165.113"),
      121, random_u16(), 0, false, NULL, 0, 0, random_u16(), 8, 0,
      "", 0, &packetlen, false);

  strcpy(eth.devname, "enp7s0");
  eth.dst = MAC_STRING_TO_ADDR("04:bf:6d:0d:3a:50");
  eth.src = MAC_STRING_TO_ADDR("40:b0:76:47:8f:9a");
  eth.ethsd = NULL;

  dst.sin_addr.s_addr = inet_addr("64.233.165.113");
  dst.sin_family = AF_INET;

  printf("plen = %d\n", packetlen);
  send_ip4_packet(&eth, 0, &dst, 0, packet, packetlen);

  eth_close_cached();
  */

  char ip[16];
  
  getipv4("https://yandex.ru/", ip, 16);
  printf("res: %s\n", ip);
  
  return 0;
}

