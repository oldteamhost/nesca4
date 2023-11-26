/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
 * -----------------------------------------------------------
 * http.h - It contains, constants and functions
 * for working with http protocol.
 * -----------------------------------------------------------
*/

#ifndef HTTP_H
#define HTTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

/* Compile opts */
#include "ncsockopt.h"

struct http_header
{
  const char* dest_host;
  const char* method;
  const char* path;
  const char* user_agent;
  const char* content_type;
  unsigned long content_len;
  char* auth_header;
};

static const char
base64_dict[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int send_http_request(const char* ip, const int port, const int timeout_ms,
      const struct http_header* header, char* response_buffer, size_t buffer_size);

char* set_basic_auth(const char* user, const char* pass);

      #define SUCCESS_AUTH 0
      #define FAILED_AUTH -1
int basic_http_auth(const char* ip, const int port, const int timeout_ms,
      const char* path, const char* user, const char* pass);

int get_robots_txt(const char* ip, const int port, const int timeout_ms);
int get_sitemap_xml(const char* ip, const int port, const int timeout_ms);

void get_redirect(const char* http_content, char* redirect_buffer, size_t buffer_size);
void get_http_title(const char* http_header, char* title_buffer, size_t buffer_size);
int parse_http_response_code(const char* http_content);

char* parse_url_from_js(const char* html);

        #define DEFAULT_LOCATION 0
        #define CONTENT_LOCATION 1
char* parse_location(const char* http_header, int type_location);
char* parse_http_equiv(const char* html);

char *_base64_encode(const unsigned char *input, size_t length);
unsigned char *_base64_decode(const char *input, size_t *output_length);

#ifdef __cplusplus
}
#endif

#endif
