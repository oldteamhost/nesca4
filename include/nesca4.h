/*
 *
 *  d8b   db d88888b .d8888.  .o88b.  .d8b.    NESCA4 - Многопоточный linux сканер портов,
 *  888o  88 88'     88'  YP d8P  Y8 d8' `8b   с точностью nmap-а, обработкой nesca3 брутфорсом
 *  88V8o 88 88ooooo `8bo.   8P      88ooo88   самых популярных протоколов и сканированием DNS.
 *  88 V8o88 88~~~~~   `Y8b. 8b      88~~~88
 *  88  V888 88.     db   8D Y8b  d8 88   88   Был сделан с вдохновением от nesca3 & nmap.
 *  VP   V8P Y88888P `8888Y'  `Y88P' YP   YP   by oldteam & lomaster.
 *
 *  license GPL-3.0                            Github - [https://github.com/oldteamhost/nesca4]
 *  Сделано от души 2023.                      Telegram - [https://t.me/+Ft1ABe8P8Tc1YzZi]
 *
 *  PS: Перечислять все возможности тут я не буду.
 *  Прочитать о том что умеет nesca4 и как это разрабатывалось
 *  читайте в resources/do_not_read.txt
 *
 *  Структура кода:
 *  01. Вся работа с сетью находится в ncsock/
 *     ^ (даже брутфорс: RVI, HTTP, FTP, SMTP, RTSP)
 *  02. nesca4.cc - вся обработка, сканирование, и т.д находиться тут.
 *  03. bruteforce.cc - функция для брутфорса в потоках, другие брутфорсы которых нету в ncsock/(hikvision).
 *  04. files.cc - работа с файлами.
 *  04. html.cc - функции для сохранения в html.
 *  05. nescalog.cc - для вывода лога и прочих его сохранений, помимо html.
 *  06. nescathread.cc - пул потоков.
 *  07. portscan.cc - функция для определения статуса порта.
 *  08. target.cc - функции для работы с группами, и для конвертирований, и настройки целей.
 *  09. services.cc - для парсинга и работы с resources/nesca-services.
 *  10. scanner.cc - для получения характеристик.
 *  11. other.cc - прочие функции.
 *
 *  Screenshots not save!:
 *  cd nesca4 && sudo chmod u+rwx,g+r,o+r utils/
 *
 *  Для компиляции без библиотек, нужно зайти в файл `config/compile.h`, и закомментировать,
 *  или удалить строчку отвечающую за библиотеку, без которой вы хотите скомпилировать:
 *  #define HAVE_HIKVISION
 *  #define HAVE_NODE_JS
 *
*/

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <chrono>
#include <future>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <iomanip>
#include <mutex>
#include <algorithm>
#include <random>
#include <string>
#include <future>
#include <sstream>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <vector>

#include "bruteforce.h"
#include "files.h"
#include "other.h"
#include "scanner.h"
#include "target.h"
#include "html.h"
#include "nescalog.h"
#include "portscan.h"
#include "services.h"
#include "nescathread.h"

#include "../modules/include/negatives.h"

#include "../config/nescaopts.h"
#include "../ncsock/include/icmp4.h"
#include "../ncsock/include/base.h"
#include "../ncbase/include/getopt.h"
#include "../ncbase/include/json.h"
#include "../ncbase/include/base64.h"
#include "../ncsock/include/bruteforce.h"
#include "../ncbase/include/binary.h"
#include "../config/compile.h"
#include "../ncsock/include/tcp.h"
#include "../ncsock/include/http.h"
#include "../ncsock/include/dns.h"
#include "../ncsock/include/strbase.h"
#include "../ncsock/include/ftp.h"
#include "../ncsock/include/smtp.h"

/*Угадайте?*/
#define VERSION "20230921"

void help_menu(void);
void version_menu(void);
void init_bruteforce(void);
void processing_tcp_scan_ports(std::string ip, int port, int result);
std::string format_percentage(double procents);
void check_files(const char* path, const char* path1);
void fix_time(double time);

int
scan_ports(const std::string& ip, std::vector<int>ports, const int timeout_ms);

void checking_default_files(void);
bool process_ping(std::string ip);
void parse_args(int argc, char** argv);
void pre_check(void);
void process_port(const std::string& ip, std::vector<uint16_t> ports, int port_type);
void get_dns_thread(std::string ip);
int count_map_vector(const std::unordered_map<std::string, std::vector<int>>& map, const std::string& key);
int traceroute(std::string ip, int jumps);
std::vector<std::string> resolv_hosts(std::vector<std::string> hosts);

/*Для обработки портов класс на паттерне Strategy Pattern.*/
class ports_strategy{
public:
  virtual ~ports_strategy() {}
  virtual void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
  const std::string& protocol, int port, arguments_program& argp, nesca_prints& np) = 0;

  std::string brute_temp;
  std::string http_title;
  std::string type_target;
  std::string content_base64;
  std::string screenshot_base64_cam;
  std::string screenshot_base64;
  std::string result_print;
};

/*Подклассы с обработкой.*/
class ftp_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np) override;};

class hikvision_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np) override;};

class rvi_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np) override;};

class https_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np) override;};

class rtsp_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np) override;};

class smtp_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np) override;};

class http_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np) override;};

class else_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np) override;};

/*Аргументы.*/
const struct
option long_options[] = {
  /*45, 19, 20, 21, 79, 78, 46, 22*/
  {"threads", required_argument, 0, 'T'},
  {"delay", required_argument, 0, 'd'},
  {"import", required_argument, 0, 23},
  {"find", required_argument, 0, 19},
  {"random-ip", required_argument, 0, 5},
  {"brute-login", required_argument, 0, 12},
  {"brute-pass", required_argument, 0, 11},
  {"ping-log", required_argument, 0, 90},
  {"my-life-my-rulez", no_argument, 0, 53},
  {"brute-log", required_argument, 0, 30},
  {"brute-verbose", required_argument, 0, 31},
  {"thread-on-port", no_argument, 0, 48},
  {"no-brute", required_argument, 0, 44},
  {"brute-timeout", required_argument, 0, 47},
  {"negatives", required_argument, 0, 76},
  {"TP", required_argument, 0, 57},
  {"debug", no_argument, 0, 27},
  {"er", no_argument, 0, 28},
  {"no-get-path", no_argument, 0, 50},
  {"import-color", required_argument, 0, 54},
  {"null", no_argument, 0, 91},
  {"fin", no_argument, 0, 92},
  {"xmas", no_argument, 0, 93},
  {"http-response", no_argument, 0, 51},
  {"scan-timeout", required_argument, 0, 101},
  {"no-ping", no_argument, 0, 29},
  {"no-proc", no_argument, 0, 95},
  {"no-color", no_argument, 0, 26},
  {"log-set", required_argument, 0, 24},
  {"packet-trace", no_argument, 0, 96},
  {"no-resolv", no_argument, 0, 59},
  {"help", no_argument, 0, 'h'},
  {"version", no_argument, 0, 'v'},
  {"ports", no_argument, 0, 'p'},
  {"db", no_argument, 0, 7},
  {"error", no_argument, 0, 25},
  {"html", required_argument, 0, 'l'},
  {"TD", required_argument, 0, 52},
  {"PS", required_argument, 0, 80},
  {"PA", required_argument, 0, 81},
  {"PE", no_argument, 0, 82},
  {"PI", no_argument, 0, 86},
  {"json", required_argument, 0, 43},
  {"PM", no_argument, 0, 87},
  {"source-port", required_argument, 0, 36},
  {"ttl", required_argument, 0, 37},
  {"robots", no_argument, 0, 67},
  {"hikshots", required_argument, 0, 35},
  {"sitemap", no_argument, 0, 68},
#ifdef HAVE_NODE_JS
  {"screenshots", required_argument, 0, 's'},
  {"ss-timeout", required_argument, 0, 41},
  {"ns-track", no_argument, 0, 39},
#endif
  {"max-group", required_argument, 0, 38},
  {"min-group", required_argument, 0, 60},
  {"rate-group", required_argument, 0, 61},
  {"exclude", required_argument, 0, 62},
  {"excludefile", required_argument, 0, 63},
  {"max-ping", no_argument, 0, 88},
  {"random-dns", required_argument, 0, 32},
  {"source-ip", required_argument, 0, 34},
  {"ack", no_argument, 0, 89},
  {"window", no_argument, 0, 94},
  {"maimon", no_argument, 0, 97},
  {"resol-delay", required_argument, 0, 40},
  {"speed", required_argument, 0, 'S'},
  {"resol-port", required_argument, 0, 33},
  {"ping-timeout", required_argument, 0, 49},
  {0,0,0,0}
};
