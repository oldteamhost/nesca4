#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/http.h"
#include "../include/smtp.h"
#include "../include/base.h"
#include "../include/ftp.h"
#include "../include/strbase.h"
#include "../include/bruteforce.h"
#include "../include/dns.h"
#include "../include/socks5.h"
#include "../include/udp.h"
#include "../include/tcp.h"
#include "../include/socket.h"
#include "../include/ethernet.h"

int main()
{
  char *active_interface = get_active_interface_name();
    if (active_interface != NULL) {
        printf("Активный сетевой интерфейс: %s\n", active_interface);
        free(active_interface); // Освобождаем память после использования
    } else {
        printf("Активный сетевой интерфейс не найден.\n");
    }
  return 0;

  int read = -1;
  while (read == -1) {
    struct udp_packet_opts upo;
    upo.seq = generate_ident();
    upo.source_ip = get_local_ip();
    upo.source_port = generate_rare_port();
    upo.ttl = 121;

    int ___send = send_udp_packet(&upo, "8.8.8.8", 53, 200);
    if (___send == -1){
      printf("FUCK: %d", ___send);
      continue;
    }
  }

  return 0;

  int _this_is = this_is("187.134.177.0/24");
  int _this_is1 = this_is("187.134.177.0-187.134.177.255");
  int _this_is2 = this_is("google.com");
  int _this_is3 = this_is("142.250.74.142");
  int _this_is4 = this_is("https://4it.me/");
  printf("%s\n",get_this_is(_this_is));
  printf("%s\n",get_this_is(_this_is1));
  printf("%s\n",get_this_is(_this_is2));
  printf("%s\n",get_this_is(_this_is3));
  printf("%s\n",get_this_is(_this_is4));

  return 0;
  double dsf = 12.2;
  printf("%f\n",dsf);
  return 0;
  for (int i = 0; i < 10; i++){
    char* random_str = generate_random_str(10, DEFAULT_DICTIONARY);
    printf("Random String: %s\n", random_str);
    free(random_str);
  }
  for (int i = 0; i < 10; i++){
    int random = random_num(123123, 9999999);
    printf("%d\n",random);
  }
  for (int i = 0; i < 10; i++){
    const char* ip = generate_ipv4();
    printf("random_ipv4: %s\n", ip);
  }
  for (int i = 0; i < 10; i++){
    int random_port = generate_rare_port();
    printf("random_port: %d\n", random_port);
  }
  return 0;

  char dns[1024];
  get_dns("64.233.161.101", 3423, dns, sizeof(dns));
  printf("DNS for IP is %s\n", dns);

  char __ip[1024];
  get_ip(dns, __ip, sizeof(__ip));
  printf("IP for DNS is %s\n", __ip);

  return 0;

  string_vector* vec = create_string_vector();

  string_vector_add(vec, "Hello");
  string_vector_add(vec, "World");

  for (size_t i = 0; i < vec->size; i++) {
    printf("%s\n", vec->data[i]);
  }

  printf("%s\n", vec->data[0]);
  string_vector_free(vec);

  int_vector* vec1 = create_int_vector();

  int_vector_add(vec1, 10);
  int_vector_add(vec1, 4);
  int_vector_add(vec1, 7);

  for (size_t i = 0; i < vec1->size; i++) {
    printf("%d\n", vec1->data[i]);
  }

  int_vector_free(vec1);


  return 0;

  int timeout = calculate_timeout(20.5, 3);
  printf("%d\n",timeout);
  int timeout_ping = calculate_ping_timeout(4);
  printf("%d\n",timeout_ping);
  int sd = calculate_threads(4, 2322);
  printf("%d\n",sd);
  return 0;

  struct bruteforce_opts bo;
  bo.delay_ms = 0;
  bo.dest_ip = "62.182.120.106";
  bo.dest_port = 21;
  bo.login = "ftp";
  bo.pass = "12345";
  bo.proto = FTP_BRUTEFORCE;
  bo.http_path = "";

  int auth = ncsock_bruteforce(&bo);
  if (auth == 0) {
    printf("aeee\n");
  }

  return 0;

  struct http_header hh;
  hh.user_agent = "ncsock";
  hh.content_len = 0;
  hh.dest_host = "";
  hh.method = "GET";
  hh.path = "/";
  hh.content_type = "text/plain";
  hh.content_type = "";
  hh.auth_header = "";

  char response_buffer[4096];
  int send = send_http_request("64.233.165.102", 80, 2000, &hh, response_buffer, sizeof(response_buffer));
  if (send == -1) {
    printf("fuck\n");
  }
  char title[256];
  get_http_title(response_buffer, title, sizeof(title));
  printf("HTTP Title: %s\n", title);

  int code = parse_http_response_code(response_buffer);
  printf("%d\n",code);

  int kek = get_robots_txt("64.233.165.102", 80, 2000);
  printf("%d\n",kek);

  char redirect_buffer[256];
  get_redirect(response_buffer, redirect_buffer, sizeof(redirect_buffer));

  printf("redirect=%s\n",redirect_buffer);

  char version_buffer[4096];
  get_ftp_version("85.174.232.14", 21, 1000, version_buffer, sizeof(version_buffer));
  printf("version=%s\n", version_buffer);

  char _version_buffer[4096];
  get_smtp_version("66.94.104.124", 25, 1000, _version_buffer, sizeof(_version_buffer));
  printf("version-smtp=%s\n", _version_buffer);

#include <time.h>
  const char* ip = generate_ipv4();
  printf("random_ipv4: %s\n", ip);
  return 0;
}
