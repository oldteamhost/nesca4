/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
*/

#include "include/dns.h"

void get_dns(const char* ip, int port, char* dns_buffer, size_t buffer_size)
{
  struct in_addr addr;
  if (inet_pton(AF_INET, ip, &addr) != 1) {
    strncpy(dns_buffer, "n/a", buffer_size);
    return;
  }

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    strncpy(dns_buffer, "n/a", buffer_size);
    return;
  }

  struct timeval timeout;
  timeout.tv_sec = 600;
  timeout.tv_usec = 0;
  if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
    close(sock);
    strncpy(dns_buffer, "n/a", buffer_size);
    return;
  }

  struct sockaddr_in sa;
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_addr = addr;
  sa.sin_port = htons(port);

  char host[NI_MAXHOST];
  int res = getnameinfo((struct sockaddr*)&sa, sizeof(sa), host, sizeof(host), NULL, 0, NI_NAMEREQD);
  close(sock);

  if (res != 0) {
    strncpy(dns_buffer, "n/a", buffer_size);
    return;
  }

  strncpy(dns_buffer, host, buffer_size);
  dns_buffer[buffer_size - 1] = '\0';
}

void get_ip(const char* dns, char* ip_buffer, size_t buffer_size)
{
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  struct addrinfo* addrinfo_result;
  int res = getaddrinfo(dns, NULL, &hints, &addrinfo_result);
  if (res != 0) {
    strncpy(ip_buffer, "n/a", buffer_size);
    return;
  }

  struct sockaddr_in* addr = (struct sockaddr_in*)addrinfo_result->ai_addr;
  const char* ip = inet_ntoa(addr->sin_addr);

  strncpy(ip_buffer, ip, buffer_size);
  ip_buffer[buffer_size - 1] = '\0';

  freeaddrinfo(addrinfo_result);
}

int dns_or_ip(const char* node)
{
  struct sockaddr_in sa;
  return (inet_pton(AF_INET, node, &(sa.sin_addr)) == 1);
}
