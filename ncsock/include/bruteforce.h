/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
*/

#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

struct bruteforce_opts
{
  const char* login;
  const char* pass;

  const char* http_path;
  const char* dest_ip;
#define HTTP_BRUTEFORCE 0
#define FTP_BRUTEFORCE 1
#define SMTP_BRUTEFORCE 2
#define RVI_BRUTEFORCE 3
#define RTSP_BRUTEFORCE 4
  uint8_t proto;
  int dest_port;
  int delay_ms;
};

int
ncsock_bruteforce(struct bruteforce_opts *bo);

#ifdef __cplusplus
}
#endif

#endif
