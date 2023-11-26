/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
*/

#include "include/bruteforce.h"
#include "include/ftp.h"
#include "include/http.h"
#include "include/rvi.h"
#include "include/smtp.h"
#include "include/base.h"
#include <time.h>

#define CLEAR_RESULT___() \
  auth = -1;

int
ncsock_bruteforce(struct bruteforce_opts *bo)
{
  int auth = -1; delayy(bo->delay_ms);
  switch (bo->proto)
  {
    case RTSP_BRUTEFORCE:
    case HTTP_BRUTEFORCE:
    {
      auth = basic_http_auth(bo->dest_ip, bo->dest_port, 1200, bo->http_path, bo->login, bo->pass);
      if (auth == -1) {
        return -1;
      }
      CLEAR_RESULT___();
      auth = basic_http_auth(bo->dest_ip, bo->dest_port, 1200, bo->http_path, bo->login, bo->pass);
      if (auth == -1) {
        return -1;
      }
      break;
    }
    case FTP_BRUTEFORCE:
    {
      auth = ftp_auth(bo->dest_ip, bo->dest_port, bo->login, bo->pass, 0, 1200);
      if (auth == -1) {
        return -1;
      }
      CLEAR_RESULT___();
      auth = ftp_auth(bo->dest_ip, bo->dest_port, bo->login, bo->pass, 0, 1200);
      if (auth == -1) {
        return -1;
      }
      break;
    }
    case SMTP_BRUTEFORCE:
    {
      auth = smtp_auth(bo->dest_ip, bo->dest_port, bo->login, bo->pass, 0, 1200);
      if (auth == -1) {
        return -1;
      }
      CLEAR_RESULT___();
      auth = smtp_auth(bo->dest_ip, bo->dest_port, bo->login, bo->pass, 0, 1200);
      if (auth == -1) {
        return -1;
      }
      break;
    }
    case RVI_BRUTEFORCE:
    {
      auth = rvi_auth(bo->dest_ip, bo->dest_port, bo->login, bo->pass, 0, 1200);
      if (auth == -1) {
        return -1;
      }
      CLEAR_RESULT___();
      auth = rvi_auth(bo->dest_ip, bo->dest_port, bo->login, bo->pass, 0, 1200);
      if (auth == -1) {
        return -1;
      }
      break;
    }
  }

  return auth;
}
