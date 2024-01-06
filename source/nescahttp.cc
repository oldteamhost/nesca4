/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "../include/nescahttp.h"
#include <mutex>

#define HTTP_BUFLEN 65535

extern std::mutex fuck;

struct http_header initheader(const std::string& path, const std::string &host,
    const std::string &useragent, const std::string &method)
{
  http_header hh;
  memset(&hh, 0, sizeof(struct http_header));

  hh.user_agent = useragent.c_str();
  hh.method = method.c_str();
  hh.path = path.c_str();
  hh.dest_host = host.c_str();
  hh.auth_header = NULL;
  hh.content_type = NULL;
  hh.content_len = 0;

  return hh;
}

char* updsend_http(struct http_header *hh, const std::string& ip,
    const u16 port, const int timeout_ms)
{
  const char *respath;
  const char *reshost;
  char path[HTTP_BUFLEN];
  char *newurl = NULL;
  char *newpath = NULL;
  char *resbuf = NULL;
  const char* ptr;
  int len = 0;
  bool aee;

  if (IS_NULL_OR_EMPTY(hh->path))
    hh->path = "/";

  respath = hh->path;
  reshost = hh->dest_host;

  if (hh->path != NULL && hh->path[0] == '.')
    memmove((void*)hh->path, (void*)(hh->path + 1), strlen(hh->path));
  for (ptr = hh->path; *ptr != '\0'; ++ptr) {
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
    ptr = strstr(hh->path, "://");
    if (ptr != NULL) {
      ptr += 3;
      ptr = strchr(ptr, '/');
      if (ptr != NULL)
        strcpy(path, ptr);
      else
        strcpy(path, "/");
    }
    else
      strcpy(path, hh->path);
    respath = path;
  }
  else {
    if (find_word(hh->path, "http://") == 0 || find_word(hh->path, "https://") == 0) {
      newurl = clean_url(hh->path);
      if (newurl)
        reshost = newurl;
      respath = "/";
    }
    else {
      if (hh->path[0] != '/') {
        len = strlen(hh->path) + 2;
        fuck.lock();
        newpath = (char *)malloc(len);
        fuck.unlock();
        if (newpath) {
          newpath[0] = '/';
          strcpy(newpath + 1, hh->path);
          respath = newpath;
        }
      }
    }
  }

  hh->path      = respath;
  hh->dest_host = reshost;

  fuck.lock();
  resbuf = new char[HTTP_BUFLEN];
  fuck.unlock();
  send_http_request(ip.c_str(), port, timeout_ms, hh, resbuf, HTTP_BUFLEN);

  fuck.lock();
  if (newpath)
    free(newpath);
  if (newurl)
    free(newurl);
  fuck.unlock();

  return resbuf;
}

void send_http(struct http_header *hh, NESCADATA &nd, const std::string& ip,
  const u16 port, const int timeout_ms)
{
  std::string res, dns;
  char resbuf[HTTP_BUFLEN];
  char redirect[HTTP_BUFLEN];
  char *newbuf = NULL;

  dns = nd.get_dns(ip);
  if (!dns.empty())
    hh->dest_host = dns.c_str();

  send_http_request(ip.c_str(), port, timeout_ms, hh, resbuf, HTTP_BUFLEN);
  res = resbuf;

  get_redirect(resbuf, redirect, HTTP_BUFLEN);

  if (!std::string(redirect).empty()) {
    fuck.lock();
      nd.add_redirect(ip, redirect);
    fuck.unlock();
    hh->path = redirect;
    newbuf = updsend_http(hh, ip.c_str(), port, timeout_ms);
  }

  if (newbuf) {
    res = std::string(newbuf);
    fuck.lock();
      delete[] newbuf;
    fuck.unlock();
  }
  if (res.empty())
    res = "empty";

  fuck.lock();
    nd.add_html(ip, res);
  fuck.unlock();
}
