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
#include <vector>
#include <set>

#include "bruteforce.h"
#include "files.h"
#include "generation.h"
#include "other.h"
#include "scanner.h"
#include "target.h"
#include "html.h"
#include "nescalog.h"
#include "portscan.h"
#include "netutils.h"
#include "services.h"
#include "nescathread.h"
#include "mathutils.h"

#include "../modules/include/requests.h"
#include "../modules/include/title.h"
#include "../modules/include/robots.h"
#include "../modules/include/redirect.h"
#include "../modules/include/negatives.h"
#include "../modules/include/ftpinfo.h"
#include "../modules/include/smtpinfo.h"

#include "../config/nescaopts.h"
#include "../ncsock/include/icmp4.h"
#include "../ncsock/include/base.h"
#include "../ncbase/include/getopt.h"
#include "../config/compile.h"

/*Угадайте?*/
#define VERSION "20230804"

void help_menu(void);
void version_menu(void);
void init_bruteforce(void);
void processing_tcp_scan_ports(std::string ip, int port, int result);
std::string format_percentage(double procents);
void check_files(const char* path, const char* path1);
void fix_time(double time);

int
scan_ports(const std::string& ip, std::vector<int>ports, const int timeout_ms);

int
probe_scan_ports(const std::string& ip, std::vector<int> ports, const int timeout_ms);

void checking_default_files(void);
bool process_ping(std::string ip);
void parse_args(int argc, char** argv);
void pre_check(void);
void print_results(std::string ip);
void get_dns_thread(std::string ip);
int traceroute(std::string ip, int jumps);
std::vector<std::string> resolv_hosts(std::vector<std::string> hosts);

/*Для обработки портов класс на паттерне Strategy Pattern.*/
class ports_strategy{
public:
	virtual ~ports_strategy() {}
	virtual void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
			const std::string& protocol, int port, arguments_program& argp, nesca_prints& np) = 0;
	std::string brute_temp;
	std::string result_print;
};

/*Подклассы с обработкой.*/
class ssh_strategy : public ports_strategy {
public:
	void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
			const std::string& protocol, int port, arguments_program& argp, nesca_prints& np) override;};

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
    {"threads", required_argument, 0, 'T'},
    {"delay", required_argument, 0, 'd'},
    {"import", required_argument, 0, 23},
    {"random-ip", required_argument, 0, 5},
    {"brute-login", required_argument, 0, 12},
    {"brute-pass", required_argument, 0, 11},
    {"ping-log", required_argument, 0, 90},
    {"my-life-my-rulez", no_argument, 0, 53},
    {"brute-log", required_argument, 0, 30},
    {"brute-verbose", required_argument, 0, 31},
    {"thread-on-port", no_argument, 0, 48},
    {"no-brute", required_argument, 0, 44},
    {"brute-only", required_argument, 0, 46},
    {"brute-timeout", required_argument, 0, 47},
    {"sftp-brute-known-hosts", no_argument, 0, 45},
    {"dns-scan", required_argument, 0, 19},
    {"negatives", required_argument, 0, 76},
    {"dns-length", required_argument, 0, 20},
    {"dns-dict", required_argument, 0, 21},
    {"txt", required_argument, 0, 22},
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
    {"PM", no_argument, 0, 87},
    {"source-port", required_argument, 0, 36},
    {"ttl", required_argument, 0, 37},
    {"pro-mode", no_argument, 0, 78},
    {"nesca3", no_argument, 0, 79},
    {"robots", no_argument, 0, 67},
    {"sitemap", no_argument, 0, 68},

    {"max-group", required_argument, 0, 38},
    {"min-group", required_argument, 0, 60},
    {"rate-group", required_argument, 0, 61},
    {"exclude", required_argument, 0, 62},
    {"excludefile", required_argument, 0, 63},

    {"max-ping", no_argument, 0, 88},
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
