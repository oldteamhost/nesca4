/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/cdefs.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"

struct uri
{
  char *scheme;
  char *host;
  u16   port;
  char *path;
};

struct _http_header
{
  char *field;
  char *value;
  struct _http_header *nxt;
};

struct http_request
{
  char method[24];
  struct uri uri;
  struct _http_header *hdr;
  u64 contentlen;
  u64 transflen;
};

struct http_response
{
  int code;
  char *phrase;
  struct _http_header *hdr;
  u64 contentlen;
};

static const char base64_dict[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

__BEGIN_DECLS

void http_init_uri(struct uri *u, const char *scheme, const char *host, u16 port,
              const char *path);
void http_print_uri(struct uri *u);
void http_free_uri(struct uri *u);
void http_update_uri(struct uri *u, const char *scheme, const char *host, u16 port,
                const char *path);
void http_init_hdr(struct _http_header *h, const char *field,
                   const char *value);
void http_print_hdr(struct _http_header *h);
void http_free_hdr(struct _http_header *h);
void http_add_hdr(struct http_request *r, const char *field, const char *value);
void http_init_req(struct http_request *r, const char *method,
                       const char *scheme, const char *host, u8 port,
                       const char *path, u64 contentlen, u64 trasflen);
void http_print_req(struct http_request *r);
void http_free_req(struct http_request *r);
void http_print_res(struct http_response *r);
void http_free_res(struct http_response *r);
char *http_util_findval(struct _http_header *h, const char *field);
void http_modify_hdr(struct http_request *r, const char *field,
                     const char *newvalue);
void http_add_basiauth(struct http_request *h, const char *user,
                       const char *pass);
u8 *http_build_pkt(struct http_request *request, const char *data,
                   ssize_t datalen, ssize_t *pktlen);
u8 *http_remove_html(u8 *packet);
struct http_response http_read_pkt(u8 *response);
void http_qprc_title(const char *h, char *titlebuf,
                     size_t buflen);
char *http_parse_parent_location(const char *buf);
char *http_parse_url_from_js(const char *buf);
char *http_parse_http_equiv(const char *buf);
void http_qprc_redirect(struct _http_header *h, u8 *pkt, char *res,
                        ssize_t reslen);
void base64encode(const u8 *input, size_t len, char *res);
char *_base64_encode(const unsigned char *input, size_t length);
u8 *_base64_decode(const char *input, size_t *output_length);
int http_send_pkt(int fd, struct http_request *r);
int http_recv_pkt(int fd, struct http_response *r, u8 *packet,
                  ssize_t packetlen);
int httpreq_qprc_pkt(const char *dst, u16 dstport, const char *path,
                     int timeout_ms, struct http_response *r, u8 *buf,
                     ssize_t buflen);
int http_qprc_pkt(const char *dst, u16 dstport, int timeoutms,
                  struct http_request *r, struct http_response *res, u8 *buf,
                  ssize_t buflen);
bool http_basicauth(int fd, const char *dst, const char *path, const char *user,
                     const char *pass);
int http_qprc_robots_txt(const char *dst, const int dstport, const int timeoutms);
int http_qprc_sitemap_xml(const char *dst, const int dstport, const int timeoutms);

__END_DECLS

#endif
