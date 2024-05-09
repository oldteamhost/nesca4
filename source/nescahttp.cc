/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "../include/nescahttp.h"
#include "../ncsock/include/utils.h"
#include <cstdlib>
#include <cstring>
#include <mutex>

#define HTTP_BUFLEN 65535
std::mutex fuck;

void prepare_redirect(const char* redirect, char* reshost, char* respath, ssize_t buflen)
{
  char *newurl = NULL;
  bool aee = false;
  const char *ptr, *hostend;
  int len = 0;

  if (IS_NULL_OR_EMPTY(redirect))
    redirect = "/";

  if (redirect[0] == '.')
    ++redirect;

  for (ptr = redirect; *ptr != '\0'; ++ptr){
    if (*ptr == '/') {
      ++len;
      if (len == 4) {
        if (*(ptr + 1) != '\0')
          aee = true;
        break;
      }
    }
  }
  if (aee) {
    ptr = strstr(redirect, "://");
    if (ptr) {
      ptr += 3;
      hostend = strchr(ptr, '/');
      if (!hostend)
        hostend = ptr + strlen(ptr);
      strncpy(reshost, ptr, hostend - ptr);
      reshost[hostend - ptr] = '\0';
      ptr = hostend;
      if (ptr)
        memmove((void*)redirect, ptr, strlen(ptr) + 1);
      else
        redirect = "/";
    }
    strncpy(respath, redirect,  buflen - 1);
    respath[buflen - 1] = '\0';
  }
  else {
    if (find_word(redirect, "http://") == 0 || find_word(redirect, "https://") == 0) {
      newurl = clean_url(redirect);
      if (newurl) {
        strncpy(reshost, newurl,  buflen - 1);
        reshost[buflen - 1] = '\0';
      }
      strncpy(respath, "/",  buflen - 1);
      respath[buflen - 1] = '\0';
    }
    else {
      if (redirect[0] != '/')
        snprintf(respath, HTTP_BUFLEN, "/%s", redirect);
    }
  }
  fuck.lock();
    if (newurl)
      free(newurl);
  fuck.unlock();
}

void send_http(struct http_request *r, NESCADATA &nd, const std::string& ip,
    const u16 port, const int timeout_ms)
{
  struct http_response response;
  std::string res, dns;
  u8 resbuf[HTTP_BUFLEN];
  char redirect[HTTP_BUFLEN];
  u8 newbuf[HTTP_BUFLEN];
  char respath[HTTP_BUFLEN];
  char reshost[HTTP_BUFLEN];

  dns = nd.get_dns(ip);
  if (!dns.empty())
    http_add_hdr(r, "Host", dns.c_str());
  else
    http_add_hdr(r, "Host", ip.c_str());

  http_qprc_pkt(ip.c_str(), port, timeout_ms, r, &response, resbuf, HTTP_BUFLEN);
  res = (char*)resbuf;

  http_qprc_redirect(response.hdr, resbuf, redirect, HTTP_BUFLEN);
  if (!std::string(redirect).empty()) {
    fuck.lock();
      nd.add_redirect(ip, redirect);
    fuck.unlock();
    prepare_redirect(redirect, reshost, respath, HTTP_BUFLEN);
    http_update_uri(&r->uri, "", "", 0, respath);
    http_modify_hdr(r, "Host", reshost);
    http_qprc_pkt(ip.c_str(), port, timeout_ms, r, &response, newbuf, HTTP_BUFLEN);
    res = std::string((char*)newbuf);
  }
  if (res.empty())
    res = "empty";

  fuck.lock();
    nd.add_html(ip, res);
  fuck.unlock();
}
