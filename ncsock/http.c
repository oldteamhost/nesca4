/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
*/

#include "include/http.h"
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

int send_http_request(const char* ip, const int port, const int timeout_ms,
    const struct http_header* header, char* response_buffer, size_t buffer_size)
{
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip, &server_addr.sin_addr);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
#ifdef PRINT_ERRORS
    perror("send_http_request/create_socket");
#endif
    return -1;
  }

  struct timeval timeout;
  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;
  if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) == -1) {
#ifdef PRINT_ERRORS
    perror("send_http_request/set_timeout");
#endif
    close(sockfd);
    return -1;
  }

  if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
#ifdef PRINT_ERRORS
    perror("send_http_request/connect_to_host");
#endif
    close(sockfd);
    return -1;
  }

  char request[1024];
  snprintf(request, sizeof(request), "%s %s HTTP/1.1\r\n"
                                    "Host: %s\r\n"
                                    "User-Agent: %s\r\n"
                                    "Content-Type: %s\r\n"
                                    "Content-Length: %lu\r\n"
                                    "Connection: close\r\n"
                                    "Authorization: Basic %s\r\n\r\n",
  header->method,
  header->path, header->dest_host, header->user_agent, header->content_type, header->content_len, header->auth_header);

  int send_req = send(sockfd, request, strlen(request), 0);
  if (send_req == -1)
  {
#ifdef PRINT_ERRORS
    perror("send_http_request/send_packet");
#endif
    close(sockfd);
    return -1;
  }

#ifdef PACKET_TRACE
  printf("TCP_HTTP & SENT %lu bytes on %s: method=%s host=%s user-agent=%s content-type=%s content-len=%lu\n",
      sizeof(&header), ip, header->method, header->dest_host, header->user_agent, header->content_type, header->content_len);
#endif

  size_t response_length = 0;
  ssize_t bytes_received;

  while ((bytes_received = recv(sockfd, response_buffer + response_length, buffer_size - response_length - 1, 0)) > 0) {
    response_length += bytes_received;
  }

#ifdef PACKET_TRACE
  printf("TCP_HTTP & RCVD %lu bytes from %s\n",
      sizeof(response_buffer), ip);
#endif

  response_buffer[response_length] = '\0';

  close(sockfd);
  return response_length;
}

char* set_basic_auth(const char* user, const char* pass)
{
#include <string.h>
  int combined_length = strlen(user) + 1 + strlen(pass) + 1;
  char combined[combined_length];
  sprintf(combined, "%s:%s", user, pass);
  unsigned char *combined_bytes = (unsigned char *)combined;
  size_t combined_length_bytes = strlen(combined);
  char *base64_encoded = _base64_encode(combined_bytes, combined_length_bytes);

  return base64_encoded;
}

#include <ctype.h>
#include "include/strbase.h"
void get_http_title(const char* http_header, char* title_buffer, size_t buffer_size)
{
  char* title_tag_open = "<title>";
  char* title_tag_close = "</title>";

  char *title_start = strstr(http_header, title_tag_open);
  if (title_start == NULL) {
    strncpy(title_buffer, "n/a", buffer_size);
    return;
  }

  title_start += strlen(title_tag_open);

  char *title_end = strstr(title_start, title_tag_close);
  if (title_end == NULL) {
    strncpy(title_buffer, "n/a", buffer_size);
    return;
  }

  int title_length = title_end - title_start;
  strncpy(title_buffer, title_start, buffer_size);

  for (int i = 0; i < title_length; i++) {
    char c = title_buffer[i];
    if (isalnum(c) || isspace(c)) {
      title_buffer[i] = c;
    }
    else {
      title_buffer[i] = ' ';
    }
  }

  title_buffer[title_length] = '\0';
  remove_specials(title_buffer);
}

int basic_http_auth(const char* ip, const int port, const int timeout_ms,
      const char* path, const char* user, const char* pass)
{
  struct http_header hh;
  hh.auth_header = set_basic_auth(user, pass);
  hh.method = "GET";
  hh.path = path;
  hh.dest_host = ip;
  hh.content_len = 0;
  hh.content_type = "";
  hh.user_agent = "ncsock";

  char response_buffer[4096];
  int send = send_http_request(ip, port, timeout_ms, &hh, response_buffer, sizeof(response_buffer));
  free(hh.auth_header);
  if (send < 0){
    return -1;
  }

  int code = parse_http_response_code(response_buffer);
  if (code != 200) {
    return FAILED_AUTH;
  }

  return SUCCESS_AUTH;
}

int get_robots_txt(const char* ip, const int port, const int timeout_ms)
{
#include "include/socket.h"
  struct http_header hh;
  hh.user_agent = "ncsock";
  hh.content_len = 0;
  hh.content_type = "";
  hh.method = "GET";
  hh.path = "/robots.txt";
  hh.dest_host = ip;
  hh.auth_header = "";

  /* it is not necessary to allocate memory for this function,
   * but it is better to do it when getting the whole page into
   * the buffer */
  char* response_buffer = (char*)malloc(CMD_BUFFER);
  if (response_buffer == NULL) {
    return -1;
  }

  int result = send_http_request(ip, port, timeout_ms, &hh, response_buffer, CMD_BUFFER);
  if (result == -1) {
    free(response_buffer);
    return -1;
  }

  int code = parse_http_response_code(response_buffer);
  if (code == 200) {
    free(response_buffer);
    return 0;
  }
  free(response_buffer);
  return -1;
}

int get_sitemap_xml(const char* ip, const int port, const int timeout_ms)
{
  struct http_header hh;
  hh.user_agent = "ncsock";
  hh.content_len = 0;
  hh.content_type = "";
  hh.method = "GET";
  hh.path = "/sitemap.xml";
  hh.dest_host = ip;
  hh.auth_header = "";

  /* it is not necessary to allocate memory for this function,
   * but it is better to do it when getting the whole page into
   * the buffer */
  char* response_buffer = (char*)malloc(CMD_BUFFER);
  if (response_buffer == NULL) {
    return -1;
  }

  int result = send_http_request(ip, port, timeout_ms, &hh, response_buffer, CMD_BUFFER);
  if (result == -1) {
    free(response_buffer);
  }

  int code = parse_http_response_code(response_buffer);
  if (code == 200) {
    free(response_buffer);
    return 0;
  }

  free(response_buffer);
  return -1;
}

int parse_http_response_code(const char* http_content)
{
  int code = -1;
  const char* status = strstr(http_content, "HTTP/1.");
  if (status != NULL) {
    sscanf(status, "HTTP/1.%*d %d", &code);
  }

  return code;
}

void get_redirect(const char* http_content, char* redirect_buffer, size_t buffer_size)
{
  char* content = parse_location(http_content, DEFAULT_LOCATION);
  if (content != NULL) {
    strncpy(redirect_buffer, content, buffer_size - 1);
    redirect_buffer[buffer_size - 1] = '\0';
    free(content);
    return;
  }

  char* content_location = parse_location(http_content, CONTENT_LOCATION);
  if (content_location != NULL) {
    strncpy(redirect_buffer, content_location, buffer_size - 1);
    redirect_buffer[buffer_size - 1] = '\0';
    free(content_location);
    return;
  }

  char* http_equiv = parse_http_equiv(http_content);
  if (http_equiv != NULL) {
    strncpy(redirect_buffer, http_equiv, buffer_size - 1);
    redirect_buffer[buffer_size - 1] = '\0';
    free(http_equiv);
    return;
  }

  char* window_js = parse_url_from_js(http_content);
  if (window_js != NULL) {
    strncpy(redirect_buffer, window_js, buffer_size - 1);
    redirect_buffer[buffer_size - 1] = '\0';
    free(window_js);
    return;
  }

  redirect_buffer[0] = '\0';
}

char* parse_url_from_js(const char* html)
{
  char* search_str = "window.location.href = \"";
  char* end_str = "\"";
  char* result = NULL;
  char* start_pos = strstr(html, search_str);

  if (start_pos != NULL) {
    start_pos += strlen(search_str);
    char* end_pos = strstr(start_pos, end_str);

    if (end_pos != NULL) {
      int length = end_pos - start_pos;
      result = (char*)malloc(length + 1);

      if (result != NULL) {
        strncpy(result, start_pos, length);
        result[length] = '\0';
      }
    }
  }
  return result;
}

char* case_insensitive_strstr(const char* haystack, const char* needle)
{
  while (*haystack) {
    bool match = true;
    for (size_t i = 0; needle[i]; i++) {
      if (tolower(haystack[i]) != tolower(needle[i])) {
        match = false;
        break;
      }
    }
    if (match) {
      return (char*)haystack;
    }
    haystack++;
  }
  return NULL;
}

char* parse_location(const char* http_header, int type_location)
{
  char* location_str;
  if (type_location == DEFAULT_LOCATION){
    location_str = "Location:";
  }
  else if (type_location == CONTENT_LOCATION) {
    location_str = "Content-Location:";
  }

  char* end_str = "\r\n";
  char* result = NULL;

  char* location_it = case_insensitive_strstr(http_header, location_str);
  if (location_it != NULL) {
    location_it += strlen(location_str);
    char* end_it = strstr(location_it, end_str);
    if (end_it != NULL) {
      int length = end_it - location_it;
      result = (char*)malloc(length + 1);
      if (result != NULL) {
        strncpy(result, location_it, length);
        result[length] = '\0';

        char* src = result;
        char* dest = result;
        while (*src) {
          if (!isspace((unsigned char)*src)) {
            *dest = *src;
            dest++;
          }
          src++;
        }
        *dest = '\0';
      }
    }
  }

  return result;
}

char* parse_http_equiv(const char* html)
{
  char* htmll = strdup(html);
  char* meta_str = "<meta";
  char* http_equiv_str = "http-equiv=\"refresh\"";
  char* content_str = "content=\"";
  char* end_str = "\"";
  char* url = NULL;

  for (int i = 0; htmll[i]; i++) {
    htmll[i] = tolower(htmll[i]);
  }

  char* meta_it = strstr(htmll, meta_str);

  if (meta_it != NULL) {
    char* http_equiv_it = strstr(meta_it, http_equiv_str);
    if (http_equiv_it != NULL) {
      char* content_it = strstr(http_equiv_it, content_str);
      if (content_it != NULL) {
        content_it += strlen(content_str);
        char* end_it = strstr(content_it, end_str);
        if (end_it != NULL) {
          int length = end_it - content_it;
          url = (char*)malloc(length + 1);
          if (url != NULL) {
            strncpy(url, content_it, length);
            url[length] = '\0';
            char* src = url;
            char* dest = url;
            while (*src) {
              if (!isspace((unsigned char)*src)) {
                *dest = *src;
                dest++;
              }
              src++;
            }

            *dest = '\0';

            /* top prefixes */
            char* url_prefixes[] = {"0;url=", "1;url=", "2;url=", "0.0;url=", "12;url="};
            for (int i = 0; i < sizeof(url_prefixes) / sizeof(url_prefixes[0]); i++) {
              if (strncmp(url, url_prefixes[i], strlen(url_prefixes[i])) == 0) {
                memmove(url, url + strlen(url_prefixes[i]), strlen(url) - strlen(url_prefixes[i]) + 1);
              }
            }
          }
        }
      }
    }
  }

  free(htmll);
  return url;
}

char *_base64_encode(const unsigned char *input, size_t length)
{
  char *encoded_data = (char *)malloc(((length + 2) / 3) * 4 + 1);
  if (!encoded_data) {
    return NULL;
  }

  size_t i = 0, j = 0;
  while (i < length) {
    unsigned char a = i < length ? input[i++] : 0;
    unsigned char b = i < length ? input[i++] : 0;
    unsigned char c = i < length ? input[i++] : 0;

    encoded_data[j++] = base64_dict[a >> 2];
    encoded_data[j++] = base64_dict[((a & 3) << 4) | (b >> 4)];
    encoded_data[j++] = base64_dict[((b & 15) << 2) | (c >> 6)];
    encoded_data[j++] = base64_dict[c & 63];
  }

  while (j % 4 != 0) {
    encoded_data[j++] = '=';
  }

  encoded_data[j] = '\0';
  return encoded_data;
}

unsigned char *_base64_decode(const char *input, size_t *output_length)
{
  size_t length = strlen(input);
  if (length % 4 != 0) {
    return NULL;
  }
  size_t padding = 0;
  if (length > 0 && input[length - 1] == '=') {
    padding++;
  }
  if (length > 1 && input[length - 2] == '=') {
    padding++;
  }

  *output_length = (length / 4) * 3 - padding;
  unsigned char *decoded_data = (unsigned char *)malloc(*output_length);
  if (!decoded_data) {
    return NULL;
  }

  size_t i = 0, j = 0;
  while (i < length) {
    unsigned char a = input[i]     == '=' ? 0 : strchr(base64_dict, input[i])     - base64_dict;
    unsigned char b = input[i + 1] == '=' ? 0 : strchr(base64_dict, input[i + 1]) - base64_dict;
    unsigned char c = input[i + 2] == '=' ? 0 : strchr(base64_dict, input[i + 2]) - base64_dict;
    unsigned char d = input[i + 3] == '=' ? 0 : strchr(base64_dict, input[i + 3]) - base64_dict;

    decoded_data[j++] = (a << 2) | (b >> 4);
    decoded_data[j++] = (b << 4) | (c >> 2);
    decoded_data[j++] = (c << 6) | d;

    i += 4;
  }

  return decoded_data;
}
