/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
*/

#include "include/smtp.h"
#include "include/socket.h"
#include "include/http.h"
#include "include/strbase.h"
#include <string.h>
#include <unistd.h>

int
smtp_auth(const char* ip, int port, const char* login, const char* pass,
        int verbose, int timeout_ms)
{
#define __CLEAR_BUFFERS() \
  memset(send_buf, 0, CMD_BUFFER); \
  memset(response_buffer, 0, CMD_BUFFER)

  int sockfd = session_run(ip, port, timeout_ms, verbose);
  if (sockfd == -1) {return -1;}

  char send_buf[CMD_BUFFER];
  char response_buffer[CMD_BUFFER];

  snprintf(send_buf, CMD_BUFFER, "HELO localhost\r\n");

  int send_helo = session_packet(sockfd, response_buffer, send_buf, verbose, timeout_ms);
  if (send_helo == -1){
    close(sockfd);
    return -1;
  }

  __CLEAR_BUFFERS();

  snprintf(send_buf, CMD_BUFFER, "AUTH LOGIN\r\n");
  int send_command_login = session_packet(sockfd, response_buffer, send_buf, verbose, timeout_ms);
  if (send_command_login == -1){
    close(sockfd);
    return -1;
  }

  __CLEAR_BUFFERS();

  char* encoded_login = _base64_encode((unsigned char*)login, strlen(login));
  snprintf(send_buf, CMD_BUFFER, "%s\r\n", encoded_login);
  int send_login = session_packet(sockfd, response_buffer, send_buf, verbose, timeout_ms);
  free(encoded_login);
  if (send_login == -1){
    close(sockfd);
    return -1;
  }
  if (find_word(response_buffer, "503")){
    close(sockfd);
    return -1;
  }

  __CLEAR_BUFFERS();

  char* encoded_pass = _base64_encode((unsigned char*)pass, strlen(pass));
  snprintf(send_buf, CMD_BUFFER, "%s\r\n", encoded_pass);
  int send_pass = session_packet(sockfd, response_buffer, send_buf, verbose, timeout_ms);

  free(encoded_pass);
  close(sockfd);

  if (send_pass == -1){
    return -1;
  }

  if(find_word(response_buffer, "235")) {
    return 0;
  }

  return -1;
}

void get_smtp_version(const char* ip, const int port, const int timeout_ms,
    char* version_buffer, size_t buffer_size)
{
  session_run_buf(ip, port, timeout_ms, version_buffer, buffer_size);
  remove_specials(version_buffer);
}
