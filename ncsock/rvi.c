/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
*/

#include "include/rvi.h"

const unsigned char headerRVI[32] = {
  0xa0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
  0x61, 0x64, 0x6d, 0x69, 0x6e, 0x00, 0x00, 0x00,
  0x61, 0x64, 0x6d, 0x69, 0x6e, 0x00, 0x00, 0x00,
  0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0xa1, 0xaa
};

const unsigned char loginRVIHeaderStart[8] = {
  0xa0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00
};

const unsigned char loginRVIHeaderEnd[8] = {
  0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0xa1, 0xaa
};

int
rvi_auth(const char* ip, int port, const char* login, const char* pass,
        int verbose, int timeout_ms)
{
  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);

  if (inet_pton(AF_INET, ip, &(sa.sin_addr)) != 1) {
    struct hostent* host = gethostbyname(ip);
    if (host == 0) {return -1;}
  }

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (connect(sock, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
    close(sock);
    return -1;
  }

  struct timeval timeout;
  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;
  if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
#ifdef PRINT_ERRORS
    perror("Error setting receive timeout");
#endif
    close(sock);
    return -1;
  }

  char new_login_packet[32] = {0};
  memcpy(new_login_packet, loginRVIHeaderStart, sizeof(loginRVIHeaderStart));
  memcpy(new_login_packet + 8, login, strlen(login));
  memcpy(new_login_packet + 16, pass, strlen(pass));
  memcpy(new_login_packet + 24, loginRVIHeaderEnd, sizeof(loginRVIHeaderEnd));

  const int s = send(sock, new_login_packet, sizeof(new_login_packet), 0);
  if (s < 0) {close(sock); return -1;}

  char buff[100] = {0};
  int bytes_received = recv(sock, buff, sizeof(buff), 0);
  if (bytes_received == -1) {return -1;} else {return bytes_received;}

  if (buff[9] == 0x08) {
    return 0;
  }

  return -1;
}
