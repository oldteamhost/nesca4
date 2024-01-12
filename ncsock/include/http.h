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

void init_uri(struct uri *u, const char *scheme,
    const char *host, u16 port, const char *path);
void print_uri(struct uri *u);
void free_uri(struct uri *u);
void update_uri(struct uri *u, const char *scheme, const char *host,
    u16 port, const char *path);
void init_http_header(struct _http_header *h,
    const char *field, const char *value);
void print_http_header(struct _http_header *h);
void free_http_header(struct _http_header *h);
void init_http_request(struct http_request *r, const char* method,
    const char *scheme, const char *host, u8 port, const char *path,
    u64 contentlen, u64 trasflen);
void add_http_header(struct http_request *r, const char *field,
    const char *value);
void print_http_request(struct http_request *r);
void free_http_request(struct http_request *r);
void print_http_response(struct http_response *r);
void free_http_response(struct http_response *r);
char *find_http_value(struct _http_header *h, const char* field);
void modify_http_header(struct http_request *r, const char *field,
    const char *newvalue);
void add_http_basicauth(struct http_request *h, const char* user,
    const char* pass);
u8 *build_http_request_pkt(struct http_request *request,
    const char* data, ssize_t datalen, ssize_t *plen);
u8 *remove_html(u8* packet);
struct http_response read_http_request_pkt(u8 *response);
void get_http_title(const char* http_header,
    char* title_buffer, size_t buffer_size);
char *parse_parent_location(const char* html);
char *parse_url_from_js(const char* html);
char *parse_http_equiv(const char* html);
void find_http_redirect(struct _http_header *h, u8 *packet,
    char* res, ssize_t reslen);
void base64encode(const u8 *input, size_t len, char *res);
char *_base64_encode(const unsigned char *input, size_t length);
u8  *_base64_decode(const char *input, size_t *output_length);
int send_http_packet(int fd, struct http_request *r);
int recv_http_packet(int fd, struct http_response *r, u8 *packet,
    ssize_t packetlen);
int sendfast_http_request(const char* ip, u16 port, const char* path,
    int timeout_ms, struct http_response *r, u8 *packet, ssize_t len);
int sendfast_http_custom(const char* ip, u16 port, int timeout_ms,
    struct http_request *r, struct http_response *res, u8 *packet,
    ssize_t len);
bool auth_http_basic(int fd, const char* ip, const char* path,
    const char* user, const char* pass);
int get_robots_txt(const char* ip, const int port, const int timeout_ms);
int get_sitemap_xml(const char* ip, const int port, const int timeout_ms);

__END_DECLS

#endif
