/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

/*GOTO*/
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <future>
#include <thread>
#include <iomanip>
#include <mutex>
#include <algorithm> 
#include <random>
#include <string>
#include <future>
#include <sstream>
#include <vector>
#include <execution>
#include <string.h>
#include <semaphore>
#include <set>
#include <functional>
#include <termios.h>

#include "../include/bruteforce.h"
#include "../include/getopt.h"
#include "../include/callbacks.h"
#include "../include/files.h"
#include "../include/generation.h"
#include "../include/other.h"
#include "../include/scanner.h"
#include "../include/target.h"
#include "../include/prints.h"
#include "../include/synscan.h"
#include "../include/netutils.h"
#include "../include/services.h"

#include "../modules/include/requests.h"
#include "../modules/include/title.h"
#include "../modules/include/redirect.h"
#include "../modules/include/ftpinfo.h"
#include "../modules/include/smtpinfo.h"

#include "../config/nescaopts.h"
#include "../ncping/include/icmpping.h"
#include "../ncping/include/tcpping.h"
#include "../ncsock/include/ncread.h"

#define VERSION "20230626"
#define DELIMITER ','

std::mutex mtx;
checking_finds cfs;
brute_ftp_data bfd_;
ip_utils _iu;
dns_utils dus;
services_nesca sn;
arguments_program argp; // config
nesca_prints np;

void 
help_menu(void);
void
init_bruteforce();
void 
processing_tcp_scan_ports(std::string ip, int port, int result);
std::string 
format_percentage(double procents);
void 
check_files(const char* path, const char* path1);
int
scan_port(const char* ip, std::vector<int>ports, const int timeout_ms, const int source_port);
void 
checking_default_files(void);
bool
process_ping(std::string ip);
void 
parse_args(int argc, char** argv);
void
pre_check();
void
print_results(std::string ip);

const struct option long_options[] = {
        {"threads", required_argument, 0, 'T'},
        {"timeout", required_argument, 0, 't'},
        {"import-ip", required_argument, 0, 23},
        {"import-cidr", required_argument, 0, 3},
        {"import-range", required_argument, 0, 32},
        {"random-ip", required_argument, 0, 5},
        {"brute-login", required_argument, 0, 12},
        {"brute-pass", required_argument, 0, 11},
        {"ping-log", required_argument, 0, 90},
        {"brute-log", required_argument, 0, 30},
        {"brute-verbose", required_argument, 0, 31},
        {"thread-on-port", no_argument, 0, 48},
        {"no-brute", required_argument, 0, 44},
        {"brute-only", required_argument, 0, 46},
        {"brute-timeout", required_argument, 0, 47},
        {"sftp-brute-known-hosts", no_argument, 0, 45},
        {"dns-scan", required_argument, 0, 19},
        {"dns-length", required_argument, 0, 20},
        {"dns-dict", required_argument, 0, 21},
        {"txt", required_argument, 0, 22},
        {"TP", required_argument, 0, 57},
        {"debug", no_argument, 0, 27},
        {"er", no_argument, 0, 28},
        {"no-get-path", no_argument, 0, 50},
        {"path-log", no_argument, 0, 53},
        {"import-color", required_argument, 0, 54},
        {"null", no_argument, 0, 91},
        {"fin", no_argument, 0, 92},
        {"xmas", no_argument, 0, 93},
        {"fix-get-path", no_argument, 0, 52},
        {"on-http-response", no_argument, 0, 51},
        {"recv-timeout", required_argument, 0, 101},
        {"no-ping", no_argument, 0, 29},
        {"no-proc", no_argument, 0, 95},
        {"no-color", no_argument, 0, 26},
        {"log-set", required_argument, 0, 24},
        {"packet-trace", no_argument, 0, 96},
        {"scan-db", no_argument, 0, 59},
        {"scan-debug", no_argument, 0, 60},
        {"res-time", no_argument, 0, 61},
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {"ports", no_argument, 0, 'p'},
        {"db", no_argument, 0, 7},
        {"error", no_argument, 0, 25},
        {"response-code", no_argument, 0, 35},
        {"http-request", no_argument, 0, 56},
        {"gen-ipv4", no_argument, 0, 36},
        {"host-test", required_argument, 0, 34},
        {"icmp-ping", required_argument, 0, 37},
        {"gen-count", required_argument, 0, 38},
        {"redirect", no_argument, 0, 55},
        {"gen-ipv6", required_argument, 0, 39},
        {"icmp-timeout", required_argument, 0, 49},
        {0,0,0,0}
    };
const char* short_options = "hvt:T:p:";

const char* run; // for help menu

void
pre_check(){
    logo();

    if (argp.import_color_scheme){
        np.import_color_scheme(argp.path_color_scheme, np.config_values);
        np.processing_color_scheme(np.config_values);
	   std::cout << np.main_nesca_out("NESCA4", "COLORSCHEME_DATA", 5, "STATE", "", "OK","") << std::endl;
    }

    if (argp.info_version){
	   np.gray_nesca_on();
	   std::cout << np.print_get_time(get_time());
	   std::cout << "[VERSION]:";
	   np.golder_rod_on();
	   std::cout << VERSION << std::endl;
	   np.gray_nesca_on();
	   std::cout << np.print_get_time(get_time());
	   std::cout << "[INFO]:";
	   np.sea_green_on();
	   std::cout << "https://github.com/oldteamhost/nesca4" << std::endl;
	   np.reset_colors();
	   np.gray_nesca_on();
	   std::cout << np.print_get_time(get_time());
	   std::cout << "[NB]:";
	   np.golder_rod_on();
	   std::cout << "Don`t read \"do_not_read.txt\"" << std::endl;
	   np.reset_colors();
	   std::cout << std::endl;
	   exit(0);
    }
    if (!check_file("./resources/nesca-services")){
	   std::cout << np.main_nesca_out("NESCA4", "SERVICES_DATA", 5, "status", "", "FAILED","") << std::endl;
    }
    else {
	   sn.init_services();
	   std::cout << np.main_nesca_out("NESCA4", "SERVICES_DATA", 5, "status", "", "OK","") << std::endl;
    }

    if (check_ansi_support() != true){
        std::cout << "You terminal don`t support ansi colors!\n";
        std::cout << "Colors disable!\n";
        np.disable_colors();
    }

    if (argp.print_help_menu){
        help_menu();
        exit(0);
    }

    if (!check_root_perms()){
        np.nlog_error("SYN scan only sudo run!\n");
        exit(1);
    }


    if (np.save_file){
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm* tm = std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(tm, "%d.%m.%Y");
        std::string date_str = oss.str();
        write_line(np.file_path_save, "\n\nNESCA4:[" + date_str + "]:[" + get_time() + "]-------------------------------\n");    
    }
}

int main(int argc, char** argv){

    run = argv[0];

    if (argc <= 1){
        help_menu();
        return 1;
    }

    parse_args(argc, argv);
    pre_check();

    if (optind < argc){
        size_t cidr = std::string(argv[optind]).find("/");
        size_t range = std::string(argv[optind]).find("-");

        if (cidr != std::string::npos){
            argp.ip_cidr_scan = true;
            argp.ip_cidr = split_string_string(argv[optind], DELIMITER);
        }
        else if (range != std::string::npos){
            argp.ip_range_scan = true;
            argp.ip_range = split_string_string(argv[optind], DELIMITER);
        }
        else {
            argp.dns = split_string_string(argv[optind], DELIMITER);        
            if (dns_or_ip(argp.dns[0])){
                argp.ip_scan = true;
                argp._ip = convert_dns_to_ip(argp.dns);
            }
            else {
                argp.ip_scan = true;
                argp._ip = split_string_string(argv[optind], DELIMITER);
            }
        }
    }

    if (argp.host_testing){
        // Код ответа
        if (argp.response_code_test){
            for (auto& host : argp.hosts_test){
                std::ostringstream strs;
                strs << get_response_code(host, 80);
                std::string code = strs.str();
                std::cout << np.main_nesca_out("TT", host, 3, "C", "", code, "") << std::endl;
            }

        }
        // HTTP запрос
        if (argp.http_request){
            for (auto& host : argp.hosts_test){
                np.golder_rod_on(); /**/ std::cout << send_http_request(host, 80); /**/ np.reset_colors(); 
                std::cout << np.main_nesca_out("TT", "[^]:HTTP REQUEST " + host, 2,
                "", "", "", "") << std::endl;
            }

        }
        // Получение путей
        if (argp.get_redirect){
            for (auto& host : argp.hosts_test){
                bool status_path;
			 std::string redirect = "N/A";
                std::string html = send_http_request(host, 80);
                redirect = parse_redirect(html, html, host, true, 80);
                std::cout << np.main_nesca_out("TT", host, 3, "R", "", redirect, "") << std::endl;
            }
        }

        // Пинг
        if (argp.tcp_ping_test){
            double ping_time_temp;
            double ping_temp;
            if (argp.tcp_ping_mode == "live" || argp.tcp_ping_mode == "1"){
			 for (;;){
				process_ping(argp.hosts_test[0]);
                    std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 3,
                    "rtt", "", "ms", "") << std::endl;
			 }
            }
            else if (argp.tcp_ping_mode == "default" || argp.tcp_ping_mode == "0") {
                for (auto& host : argp.hosts_test){
				bool icmp_ping = process_ping(host);

                    if (icmp_ping){
                        std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 3,
                        "rtt", "", "ms", "") << std::endl;
                    }
                }
            }
            else {
                np.nlog_custom("TT", argp.hosts_test[0] + " ping mode not found! Only (0,1) ala (default, live)",2);
           }
        }
        return 0;
    }

    /*Режим генерации*/
    if (argp.generation_test){
        if (argp.generate_ipv4_test){
            for (int i = 1; i <= argp.generate_count; i++){
                std::cout << np.main_nesca_out("TT", generate_ipv4(), 3,
                        "", "", "", "") << std::endl;
            }
        }
        if (argp.generate_ipv6_test){
            for (int i = 1; i <= argp.generate_count; i++){
                std::cout << np.main_nesca_out("TT", generate_ipv6(argp.octets), 3,
                        "", "", "", "") << std::endl;
            }
        }
        return 0;
    }

    /*Предупреждение о потоках*/
    if (argp.warning_threads){
        char what;
        np.nlog_custom("WARNING","You set "+ std::to_string(argp.threads_temp) + 
                " threads this can severely overload a weak cpu, are you sure you want to continue (y,n): ", 2);
        std::cin >> what;
        std::cout << std::endl;

        if (what != 'y'){
            return 0;
        }
        else {
            argp._threads = argp.threads_temp;
        }
    }

    checking_default_files();
    std::cout << std::endl;

    /*Начало DNS сканирования.*/
    if (argp.dns_scan){
        argp.timeout_ms = 100;
        std::mutex mtx;
	   std::cout << np.main_nesca_out("NESCA4", "Starting "+std::to_string(argp._threads)+" threads...", 5, "on", "", "DNS","") << std::endl << std::endl;
        for (int i = 0; i < argp._threads; i++) {

            std::thread([&](){
                for (;;) {
                    std::string random_ = generate_random_str(argp.dns_scan_domain_count, argp.dns_dictionary);
                    std::string result = random_ + argp.domain_1level;
                    std::string ip = dus.get_ip_by_dns(result.c_str());
				if (ip == "-1"){
				    if (argp.debug){
					   np.nlog_custom("BA", result + " [FaILEd]\n",2);
				    }
				    continue;
				}
                    std::string result_print;
				int ping = process_ping(ip.c_str());
                    std::string html = send_http_request(ip, 80);
                    if (ping == -1) {
                        if (argp.debug) {
                            std::lock_guard<std::mutex> lock(mtx);
                            np.nlog_custom("BA", result + " [FaILEd]\n",2);
                        }
                    }
                    else {
                        std::lock_guard<std::mutex> lock(mtx);
                        std::cout << np.main_nesca_out("BA", "http://" + result, 3, "T", "", get_http_title(html), "") << std::endl;
                    }
				delay_ms(argp.timeout_ms);
                }
            }).detach();

            if (argp.timeout){
                delay_ms(argp.timeout_ms);
            }
        }
        std::getchar();
        std::cout << np.main_nesca_out("NN", "Stoping threads...", 0, "", "", "", "") << std::endl;
    }


    /*Тут начинаеться само сканирование, брутфорс и всё остальное.
	* nesca 4*/
    

    init_bruteforce();

    std::vector<std::string> result;

    // получение ip компютера
    argp.source_ip = _iu.get_local_ip();
   
    /*Установка цели из аргумента.*/
    if (argp.ip_scan_import || argp.ip_scan){
        result = argp._ip;
    } 
    else if (argp.ip_range_scan || argp.ip_range_scan_import){
        std::vector<std::string> range_convert = range_to_ips(argp.ip_range);
        result = range_convert;
    }
    else if (argp.ip_cidr_scan_import || argp.ip_cidr_scan){
        std::vector<std::string> cidr_convert = cidr_to_ips(argp.ip_cidr);
        result = cidr_convert;
    }
    else if (argp.random_ip){
        argp.ip_scan = true;
        for (int i = 0; i < argp.random_ip_count; i++){
            std::string random_temp = generate_ipv4();
            result.push_back(random_temp);
        }
    }

    std::vector<std::string> result_main; // ip для сканирования
    int ip_count = 0;
    int flag_desing = 0;
    
    /*Пинг сканирования*/
    if (!argp.ping_off) {
	   std::cout << np.main_nesca_out("NESCA4", "PING_SCAN", 5, "timeout", "threads", std::to_string(argp.icmp_ping_timeout), std::to_string(argp.threads_ping)) << std::endl;

        int threads_ping = argp.threads_ping;  // Количество потоков
        int ips_per_thread = result.size() / threads_ping;
        int ip_count_ping = 0;

        std::vector<std::future<std::pair<bool, std::string>>> futures;
        auto result_iter = result.begin();

        while (result_iter != result.end()) {
            int remaining_tasks = std::distance(result_iter, result.end());
            int tasks_to_execute = std::min(threads_ping, remaining_tasks);

            for (int i = 0; i < tasks_to_execute; ++i) {
                std::string ip = *result_iter;
                futures.push_back(std::async(std::launch::async, [ip]() -> std::pair<bool, std::string> {
                    bool ping = process_ping(ip);
                    return std::make_pair(ping, ip);
                }));

                ++result_iter;
            }

            for (auto& future : futures) {
                auto result = future.get();
                bool ping = result.first;
                std::string ip = result.second;

                if (ping) {
                    result_main.push_back(ip);

                    if (argp.display_response_time) {
                        std::cout << np.main_nesca_out("PING", ip, 1, "opt: result: mode:", "rtt", "", "ms") << std::endl;
                    }
                }
            }

            futures.clear();
            ip_count_ping += tasks_to_execute;

            if (ip_count_ping % argp.ping_log == 0) {
                double procents = (static_cast<double>(ip_count_ping) / result.size()) * 100;
                std::string _result = format_percentage(procents);

                std::cout << np.main_nesca_out("^NESCAPINGLOG", std::to_string(ip_count_ping) + " out of " + std::to_string(result.size()) + " IPs", 4, "P", "", _result + "%", "") << std::endl;
            }
        }

        int error_count = result.size() - result_main.size();
        // std::cout << np.main_nesca_out("NESCA4", "FINISH ping", 5, "success", "errors", std::to_string(result_main.size()), std::to_string(error_count)) << std::endl;
    }

    if (argp.ping_off){
	   result_main = result;
    }

    /*Определение метода.*/
    if (argp.fin_scan ||
       argp.xmas_scan ||
	  argp.null_scan){np.nlog_custom("WARNING", "XMAS | FIN | NULL scan, results may be inaccurate!\n", 2);}

    if (argp.fin_scan){argp.fin_scan = true;}
    else if (argp.null_scan){argp.null_scan = true;}
    else if (argp.xmas_scan){argp.xmas_scan = true;}

    if (argp.fin_scan){
	   /*#cleanCode*/
	   std::cout << np.main_nesca_out("NESCA4", "START_FIN_SCAN", 5, "targets", "threads", std::to_string(result_main.size()), std::to_string(argp._threads)) << std::endl;}else if (argp.null_scan){std::cout << np.main_nesca_out("NESCA4", "START_NULL_SCAN", 5, "targets", "threads", std::to_string(result_main.size()), std::to_string(argp._threads)) << std::endl;}else if (argp.xmas_scan){std::cout << np.main_nesca_out("NESCA4", "START_XMAS_SCAN", 5, "targets", "threads", std::to_string(result_main.size()), std::to_string(argp._threads)) << std::endl;}else {std::cout << np.main_nesca_out("NESCA4", "START_SYN_SCAN", 5, "targets", "threads", std::to_string(result_main.size()), std::to_string(argp._threads)) << std::endl;}

    /*Само сканирование.*/
    long long size = result_main.size();

    std::vector<std::future<int>> futures;
    std::set<std::string> processed_ip;
    int skipped_ip = 0;

    for (const auto& ip : result_main) {
	   if (processed_ip.count(ip) > 0) {
		  skipped_ip++;
		  continue;
	   }

	   processed_ip.insert(ip);
	   int source_port = generate_port();

	   ip_count++;

	   if (ip_count % argp.log_set == 0){
		  double procents = (static_cast<double>(ip_count) / size) * 100;
		  std::string result = format_percentage(procents);
		  std::cout << np.main_nesca_out("^NESCASYNLOG", std::to_string(ip_count) + " out of " + std::to_string(size) + " IPs", 4, "P", "", result + "%", "") << std::endl;
	   }

	   std::future<int> fut = std::async(std::launch::async, scan_port, ip.c_str(), argp.ports, argp.timeout_ms, source_port);
	   futures.push_back(std::move(fut));

	   if (futures.size() >= argp._threads){
            int main_scan = futures.front().get();
            futures.erase(futures.begin());
        }
    }
    for (auto& fut : futures){
	   int main_scan = fut.get();
    }
    std::cout << np.main_nesca_out("NESCA4", "FINISH_SCAN", 5, "success", "errors", std::to_string(argp.fuck_yeah), std::to_string(argp.error_fuck)) << std::endl;


    for (auto& ip : processed_ip){
	   if (argp.success_target.count(ip) > 0 || argp.debug){
		  std::string dns = dus.get_dns_by_ip(ip.c_str(),4445);
		  double time_ms;
		  if (argp.rtts.count(ip) > 0){time_ms = argp.rtts.at(ip);} 
		  else {time_ms = -1.0;}
		  std::cout << std::endl << np.main_nesca_out("READY", ip, 5, "rDNS", "RTT", dns, std::to_string(time_ms)) << std::endl;
	   }

	   print_results(ip);
    }
    if (skipped_ip > 0){
	   std::cout << std::endl << np.main_nesca_out("NESCA4", "Missed "+std::to_string(skipped_ip)+" identical IPs", 5, "status", "", "OK", "") << std::endl;
    }

    argp.success_target.clear();
    argp.error_target.clear();
    argp.filtered_target.clear();
    argp.closed_target.clear();

    /*Конец*/

    return 0;
}
void
print_results(std::string ip){
    auto it = argp.success_target.find(ip);
    if (it != argp.success_target.end()) {
    const std::vector<int>& second_element = argp.success_target[ip];
	   for (size_t i = 0; i < second_element.size(); ++i) {
		  processing_tcp_scan_ports(ip, second_element[i], PORT_OPEN);
	   }
    }

    auto it1 = argp.error_target.find(ip);
    if (it1 != argp.error_target.end()) {
    const std::vector<int>& second_element = argp.error_target[ip];
	   for (size_t i = 0; i < second_element.size(); ++i) {
		  processing_tcp_scan_ports(ip, second_element[i], PORT_ERROR);
	   }
    }

    auto it2 = argp.filtered_target.find(ip);
    if (it2 != argp.filtered_target.end()) {
    const std::vector<int>& second_element = argp.filtered_target[ip];
	   for (size_t i = 0; i < second_element.size(); ++i) {
		  processing_tcp_scan_ports(ip, second_element[i], PORT_FILTER);
	   }
    }
	   
    auto it3 = argp.closed_target.find(ip);
    if (it3 != argp.closed_target.end()) {
    const std::vector<int>& second_element = argp.closed_target[ip];
	   for (size_t i = 0; i < second_element.size(); ++i) {
		  processing_tcp_scan_ports(ip, second_element[i], PORT_CLOSED);
	   }
    }
}

bool
process_ping(std::string ip){
    // Обычный через connect 
    /*
    bool tcp_ping = connect_tcp_ping(ip.c_str(), 80, argp.tcp_ping_timeout);
    if (tcp_ping){
	   return true;
    }
    */

    // 3 Метода ICMP пинга
    delay_ms(argp.icmp_ping_timeout);
    double icmp_casual = icmp_ping(ip.c_str(), 1, 1000, 8, 0, 64);
    if (icmp_casual != PING_ERROR){
	   argp.rtts[ip] = icmp_casual;
	   return true;
    }
    else {
	   double icmp_rev = icmp_ping(ip.c_str(), 1, 1000, 13, 0, 64);
	   if (icmp_rev != PING_ERROR){
		  argp.rtts[ip] = icmp_rev;
		  return true;
	   }
	   else {
		  int icmp_rev1 = icmp_ping(ip.c_str(), 1, 1000, 15, 0, 64);
		  if (icmp_rev1 != PING_ERROR){
		      argp.rtts[ip] = icmp_rev1;
			 return true;
		  }
	   }
    }

    return false;
}

int errors_files = 0;

void check_files(const char* path, const char* path1){
       if (!check_file(path)){
		 std::cout << std::endl;
           np.nlog_error(std::string(path) + " (" + std::to_string(get_count_lines(path)) + ") entries");
		 errors_files++;
       }else if (!check_file(path1)){
		 std::cout << std::endl;
		 np.nlog_error(std::string(path1) + " (" + std::to_string(get_count_lines(path1)) + ") entries");
		 errors_files++;
       }
}

void 
checking_default_files(void){
    const char* path0 = "ip.txt";

    if (argp.ip_cidr_scan_import){
       if (check_file(argp.path_cidr)){
            if (argp.ip_cidr_scan){
                np.nlog_trivial(std::string(argp.path_cidr) + " (" + std::to_string(get_count_lines(argp.path_cidr)) + ") entries\n");
            }
            argp.ip_cidr = write_file(argp.path_cidr);  
       }
       else {
            np.nlog_error(std::string(argp.path_cidr) + " (" + std::to_string(get_count_lines(argp.path_cidr)) + ") entries\n");
		  errors_files++;
       }
    }

    if (argp.ip_range_scan_import){
        if (check_file(argp.path_range)){
            if (argp.ip_range_scan){
                np.nlog_trivial(std::string(argp.path_range) + " (" + std::to_string(get_count_lines(argp.path_range)) 
                                + ") entries\n");
            }
            argp.ip_range = write_file(argp.path_range);
        }
        else {
            np.nlog_error(std::string(argp.path_range) + " (" + std::to_string(get_count_lines(argp.path_range)) 
                            + ") entries\n");
		  errors_files++;
        }
    }

    if (argp.ip_scan_import){
       if (check_file(argp.path_ips)){
            np.nlog_trivial(std::string(argp.path_ips) + " (" + std::to_string(get_count_lines(argp.path_ips)) 
                            + ") entries\n");
            argp._ip = write_file(argp.path_ips);  
       }
       else {
            np.nlog_error(std::string(argp.path_ips) + " (" + std::to_string(get_count_lines(argp.path_ips)) 
                            + ") entries\n");
		  errors_files++;
       }
    }

    // Чек паролей и логинов
    check_files(argp.path_ftp_login.c_str(), argp.path_ftp_pass.c_str());
    check_files(argp.path_sftp_login.c_str(), argp.path_sftp_pass.c_str());
    check_files(argp.path_http_login.c_str(), argp.path_http_pass.c_str());
    check_files(argp.path_rtsp_login.c_str(), argp.path_rtsp_pass.c_str());
    check_files(argp.path_smtp_login.c_str(), argp.path_smtp_pass.c_str());
    check_files(argp.path_hikvision_login.c_str(), argp.path_hikvision_pass.c_str());

    if (errors_files == 0){
	   std::cout << np.main_nesca_out("NESCA4", "BRUTEFORCE_DATA", 5, "status", "", "OK","");
    }
    else {
	   std::cout << np.main_nesca_out("NESCA4", "BRUTEFORCE_DATA", 5, "status", "ERRORS", "FAILED", std::to_string(errors_files));
    }
}

void
print_port_state(int status, int port, std::string service){
    np.gray_nesca_on();
    std::cout << "[&][REPORT]:";
    np.green_html_on();
    std::cout << std::to_string(port) << "/tcp"; 
    np.gray_nesca_on();
    std::cout << " STATE: ";
    if (status == PORT_OPEN){
	   np.green_html_on();
	   std::cout << "open"; 
    }
    else if (status == PORT_CLOSED){
	   std::cout << "closed"; 
    }
    else if (status == PORT_FILTER){
	   np.yellow_html_on();
	   std::cout << "filtered"; 
    }
    else if (status == PORT_ERROR){
	   np.red_html_on();
	   std::cout << "error"; 
    }
    np.gray_nesca_on();
    std::cout << " SERVICE: ";
    np.green_html_on();
    std::cout << service << std::endl;
    np.reset_colors();
}

// Welcome to HELL :)
// > Я сам не понимаю что тут написано, но работает правильно.
void 
processing_tcp_scan_ports(std::string ip, int port, int result){
        if (result == PORT_OPEN) {
		  np.gray_nesca_on();
		  if (argp.no_proc){
			 print_port_state(PORT_OPEN, port, sn.probe_service(port));
			 return;
		  }

            std::string result = ip + ":" + std::to_string(port);
            std::string brute_temp;
            std::string result_print;

            if (port == 80 || port == 81 || port == 8080 ||
			 port == 8081 || port == 8888 || port == 8008){
			 print_port_state(PORT_OPEN, port, "HTTP");
                result.insert(0, "http://");
                bool status_path = false;

                std::string redirect;
                std::string default_result = "http://" + ip + ":" + std::to_string(port) + "/";
                std::string html = send_http_request(ip, port);

                if (argp.no_get_path != true){ /*Получение перенаправления.*/
                    if (argp.fix_get_path){redirect = parse_redirect(html, html, ip, false, port);}
                    else {redirect = parse_redirect(html, html, ip, true, port);}
                }

			 /*Брутфорс AXIS камер.*/
                std::string temp_check_axis = cfs.check_axis_camera(redirect); // check axis redirect
                if (argp.off_http_brute != true && temp_check_axis != "no" && argp.no_get_path != true){
				np.yellow_html_on();
				std::cout << "[>][AXIS]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();

                    brute_temp = threads_brute_http("http://" + ip + redirect, argp.http_logins, argp.http_passwords,
                             argp.http_brute_log, argp.http_brute_verbose, argp.brute_timeout_ms);
                }

			 /*Получение заголовка.*/
                std::string http_title_result = get_http_title(html);
			 if (http_title_result == HTTPTITLE_ERROR){http_title_result = get_http_title_pro(ip);}

			 /*Удаление переносов из заголовка.*/
                http_title_result.erase(std::remove(http_title_result.begin(), http_title_result.end(), '\r'), http_title_result.end());
                http_title_result.erase(std::remove(http_title_result.begin(), http_title_result.end(), '\n'), http_title_result.end());

                result_print = np.main_nesca_out("BA", "http://" + brute_temp + ip + ":" + std::to_string(port), 3, "T", "", http_title_result, "");

                if (argp.http_only){if (brute_temp.length() > 1)
				{result_print = np.main_nesca_out("BA", "http://" + brute_temp + ip + ":" + std::to_string(port),
					   3, "T", "", http_title_result, "");}}


                std::cout << result_print << std::endl;

			 /*Вывод перенаправления.*/
                if (argp.no_get_path != true && redirect.length() != default_result.length()){
                    if (argp.fix_get_path){
                            if (redirect.length() != 0){
						  np.gray_nesca_on();
						  std::cout << "[^][REDIRT]:";
						  np.yellow_html_on();
						  std::cout << redirect + "\n";
						  np.reset_colors();
                            }
                    }
                    else {
                        if (redirect.length() != default_result.length()){
                            if (redirect.length() != 0){
						  np.gray_nesca_on();
						  std::cout << "[^][REDIRT]:";
						  np.yellow_html_on();
						  std::cout << redirect + "\n";
						  np.reset_colors();
                            }
                        }
                    }
                }

			 /*Вывод ответа http.*/
                if (argp.get_response){
                    std::string result_code =  np.main_nesca_out("TT", html, 2, "", "", "", "");
                    std::cout << result_code << std::endl;}
            }
            else if (port == 20 || port == 21){
			 print_port_state(PORT_OPEN, port, "FTP");
                std::lock_guard<std::mutex> guard(mtx);

			 std::string ftp_version = get_ftp_description(ip, std::to_string(port), bfd_.get_success_login(), bfd_.get_success_pass());

                if (argp.off_ftp_brute != true){
				np.yellow_html_on();
				std::cout << "[>][FTP]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();

                    brute_temp = threads_brute_ftp(ip, port, argp.ftp_logins, argp.ftp_passwords, argp.ftp_brute_log,
                            argp.ftp_brute_verbose, argp.brute_timeout_ms);

                    if (argp.ftp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("BA", "ftp://" + brute_temp + result, 3, "D", "",
                                    ftp_version ,"");
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("BA", "ftp://" + brute_temp + result, 3, "D", "",
                                ftp_version, "");
                    }
                }
                else {
                    result_print = np.main_nesca_out("BA", "ftp://" + brute_temp + result, 3, "D", "",
                            ftp_version, "");
                }
                
                std::cout << result_print << std::endl;
            }
            else if (port == 22){
			 print_port_state(PORT_OPEN, port, "SSH");
                std::lock_guard<std::mutex> guard(mtx);

                if (argp.off_sftp_brute != true){
				np.yellow_html_on();
				std::cout << "[>][SSH]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();

                    brute_temp = threads_brute_ssh(ip, port, argp.sftp_logins, argp.sftp_passwords, argp.sftp_brute_log,
                        argp.sftp_brute_verbose, argp.sftp_using_know_hosts, argp.brute_timeout_ms);

                    if (argp.sftp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("BA", "sftp://" + brute_temp + result, 3, "", "", "", "");
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("BA", "sftp://" + brute_temp + result, 3, "", "", "", "");
                    }
                }
                else {
                    result_print = np.main_nesca_out("BA", "sftp://" + result, 3, "", "", "", "");
                }

                std::cout << result_print << std::endl;
            }
            else if (port == 554){
			 print_port_state(PORT_OPEN, port, "RTSP");
                std::lock_guard<std::mutex> guard(mtx);
                std::string path_yes = "";

                if (argp.off_rtsp_brute != true){

                    std::vector<std::string> rtsp_paths = {"/Streaming/Channels/101", "/h264/ch01/main/av_stream", 
                                                          "/cam/realmonitor?channel=1&subtype=0","/live/main",
                                                           "/av0_0", "/mpeg4/ch01/main/av_stream"};

				np.yellow_html_on();
				std::cout << "[>][RTSP]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();

                    for (auto& path : rtsp_paths){
                        brute_temp = threads_brute_rtsp(ip+path, argp.rtsp_logins, argp.rtsp_passwords, argp.rtsp_brute_log, argp.rtsp_brute_verbose,
                                                   argp.brute_timeout_ms);
                        if (brute_temp.length() > 1){
                            path_yes = path;
                        }
                    }

                    if (argp.rtsp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("BA", "rtsp://" + brute_temp + result + path_yes, 3, "", "", "", "");
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("BA", "rtsp://" + brute_temp + result + path_yes, 3, "", "", "", "");
                    }
                }
                else {
                    result_print = np.main_nesca_out("BA", "rtsp://" + result, 3, "", "", "", "");
                }

                std::cout << result_print << std::endl;
            }
            else if (port == 8000){
			 print_port_state(PORT_OPEN, port, "HIKVISION");
                std::lock_guard<std::mutex> guard(mtx);

                if (argp.off_hikvision_brute != true){
				np.yellow_html_on();
				std::cout << "[>][HIKVISION]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();
                    brute_temp = threads_brute_hikvision(ip, argp.hikvision_logins, argp.hikvision_passwords, argp.hikvision_brute_log,
                                                  argp.brute_timeout_ms);

                    if (argp.hikvision_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("BA", "" + brute_temp + result, 3, "", "", "", "");
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("BA", "" + brute_temp + result, 3, "", "", "", "");
                    }
                }
                else {
                    result_print = np.main_nesca_out("BA", "" + result, 3, "", "", "", "");
                }

                std::cout << result_print << std::endl;
            }
            else if (port == 443){
			 print_port_state(PORT_OPEN, port, "HTTPS");
                std::string result_print = np.main_nesca_out("BA", "https://" + result, 3, "", "", "", "");
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            } else if (port == 25){
			 print_port_state(PORT_OPEN, port, "SMTP");
                std::lock_guard<std::mutex> guard(mtx);
			 std::string responce_220 = smtp_get_220_response(ip, port, 0);

                if (argp.off_sftp_brute != true){
				np.yellow_html_on();
				std::cout << "[>][SMTP]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();

                    brute_temp = threads_brute_smtp(ip, port, argp.smtp_logins, argp.smtp_passwords, argp.smtp_brute_log,
                        argp.smtp_brute_verbose, argp.brute_timeout_ms);


                    if (argp.sftp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("BA", "smtp://" + brute_temp + result, 3, "D", "", responce_220, "");
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("BA", "smtp://" + brute_temp + result, 3, "D", "", responce_220, "");
                    }
                }
                else {
                    result_print = np.main_nesca_out("BA", "smtp://" + result, 3, "", "", responce_220, "");
                }

                std::cout << result_print << std::endl;
		  }
            else{
                std::lock_guard<std::mutex> guard(mtx);
			 print_port_state(PORT_OPEN, port, sn.probe_service(port));
            }
        }
        else if (result == -1){
            if (argp.print_errors){
                std::lock_guard<std::mutex> guard(mtx);
			 print_port_state(PORT_ERROR, port, sn.probe_service(port));
            }
        }
        else if (result == 2){
            if (argp.debug){
                std::lock_guard<std::mutex> guard(mtx);
			 print_port_state(PORT_FILTER, port, sn.probe_service(port));
            }
        }
        else if (result == 1) {
            if (argp.debug){
                std::lock_guard<std::mutex> guard(mtx);
			 print_port_state(PORT_CLOSED, port, sn.probe_service(port));
            }
        }
}
// You live?

void 
help_menu(void){
    logo();
    np.golder_rod_on();
    std::cout << "usage: " << run << " [target 1,2,3] [flags]\n";
    np.reset_colors();

    np.sea_green_on();
    std::cout << "\narguments target:" << std::endl;
    np.reset_colors();
    std::cout << "  -import-ip <path>      Set ip on target from file.\n";
    std::cout << "  -import-cidr <path>    Set cidr on target from file.\n";
    std::cout << "  -import-range <path>   Set range on target from file.\n";
    std::cout << "  -random-ip <count>     Set random ip target.\n";

    np.sea_green_on();
    std::cout << "\narguments speed:" << std::endl;
    np.reset_colors();
    std::cout << "  -scan-count <count>    Set the number of repeat scans.\n";
    std::cout << "  -threads, -T <count>   Set threads for scan.\n";
    std::cout << "  -timeout, -t <ms>      Set timeout for scan.\n";

    np.sea_green_on();
    std::cout << "\narguments port_scan:" << std::endl;
    np.reset_colors();
    std::cout << "  -fin                   Using FIN scan.\n";
    std::cout << "  -xmas                  Using XMAS scan.\n";
    std::cout << "  -null                  Using TCP NULL scan.\n\n";
    std::cout << "  -ports, -p <1,2,3>     Set ports on scan.\n";
    std::cout << "  -recv-timeout <ms>     Set timeout for getting packet on port.\n";
    std::cout << "  -scan-db, scan-debug   Display verbose info for syn port scan.\n";

    np.sea_green_on();
    std::cout << "\narguments ping:" << std::endl;
    np.reset_colors();
    std::cout << "  -icmp-timeout <ms>     Set timeout for icmp ping.\n";
    std::cout << "  -no-ping               Off ping.\n";

    np.sea_green_on();
    std::cout << "\narguments bruteforce:" << std::endl;
    np.reset_colors();
    std::cout << "  -brute-login <ss,path> Set path for <ss> logins.\n";
    std::cout << "  -brute-pass <ss,path>  Set path for <ss> passwords.\n";
    std::cout << "  -brute-timeout <ms>    Edit brute timout.\n";
    std::cout << "  -brute-only <ss,2>     Display only success <ss> bruteforce.\n";
    std::cout << "  -no-brute <ss,2>       Disable <ss> bruteforce.\n";

    np.sea_green_on();
    std::cout << "\narguments other bruteforce:" << std::endl;
    np.reset_colors();
    std::cout << "  -brute-verbose <ss,2>  Display bruteforce <ss> all info.\n";
    std::cout << "  -brute-log <ss,2>      Display bruteforce <ss> info.\n";
    std::cout << "  -sftp-brute-known-hosts Reading known_host for connection.\n";

    np.sea_green_on();
    std::cout << "\narguments dns-scan:" << std::endl;
    np.reset_colors();
    std::cout << "  -dns-scan <.dns>       On dns-scan and set domain 1 level.\n";
    std::cout << "  -dns-length <count>    Edit length generating domain.\n";
    std::cout << "  -dns-dict <dict>       Edit dictionary for generation.\n";

    np.sea_green_on();
    std::cout << "\narguments output:" << std::endl;
    np.reset_colors();
    std::cout << "  -db, -debug            On debug mode, save and display not even working hosts.\n";
    std::cout << "  -er, -error            On display errors.\n";
    std::cout << "  -no-proc               Only scan.\n";
    std::cout << "  -packet-trace          Display packet_trace.\n";
    std::cout << "  -no-get-path           Disable getting paths.\n";
    std::cout << "  -path-log              Display paths method log.\n";
    std::cout << "  -fix-get-path          Display paths no processing (original).\n";
    std::cout << "  -on-get-dns            On get dns for scanning ports.\n";
    std::cout << "  -on-http-response      On print response from port 80.\n";
    std::cout << "  -log-set <count>       Change change the value of ips after which, will be displayed information about how much is left.\n";
    std::cout << "  -txt <path>            Save result to text document.\n";
    np.sea_green_on();
    std::cout << "\narguments colors:" << std::endl;
    np.reset_colors();
    std::cout << "  -no-color              Disable colors.\n";
    std::cout << "  -import-color <path>   Import color scheme from file.\n";

    np.sea_green_on();
    std::cout << "\narguments testing:" << std::endl;
    np.reset_colors();
    std::cout << "  -host-test <1,2,3>     Set host for testing.\n";
    std::cout << "  -response-code         Get response code from host.\n";
    std::cout << "  -redirect              Get redirect from host.\n";
    std::cout << "  -http-request          Send http request from host.\n";
    std::cout << "  -icmp-ping <mode>      Get response time from host, modes (live) or (default).\n";

    np.sea_green_on();
    std::cout << "\narguments generation:" << std::endl;
    np.reset_colors();
    std::cout << "  -gen-count <count>     Set count for generation.\n";
    std::cout << "  -gen-ipv6 <octets>     Generate ip version 6.\n";
    std::cout << "  -gen-ipv4              Generate ip version 6.\n";
}
void 
parse_args(int argc, char** argv){
    int rez;
    int option_index = 0;

    while ((rez = getopt_long_only(argc, argv, short_options, long_options, &option_index)) != EOF) {
        switch (rez) {
            case 'h':
                argp.print_help_menu = true;
                break;
            case 'v':
			 argp.info_version = true;
                break;
            case 'p':
            {
                argp.ports_temp = optarg;
                argp.ports = write_ports(argp.ports_temp);
                if (argp.ports[0] == EOF){
                    size_t pos = argp.ports_temp.find(",");
                    size_t pos1 = argp.ports_temp.find("-");

                    if (pos1 != std::string::npos){
                        argp.ports = parse_range(optarg);
                    }
                    else {
                        argp.ports = split_string_int(optarg, DELIMITER);
                    }
                }
                break;
            }
            case 3:
            {
               argp.ip_cidr_scan_import = true;
               argp.path_cidr = optarg;
               break;
            }
           case 12:
           {
               std::vector<std::string> what = split_string_string(optarg, DELIMITER);
               std::transform(what[0].begin(), what[0].end(), what[0].begin(), [](unsigned char c) {
                    return std::tolower(c);
               });
               const char* what_convert = what[1].c_str();
               if (what[0] == "ftp"){
                    argp.path_ftp_login = what_convert;
               }
               else if (what[0] == "sftp"){
                   argp.path_sftp_login = what_convert;
               }
               else if (what[0] == "rtsp"){
                   argp.path_rtsp_login = what_convert;
               }
               else if (what[0] == "http"){
                   argp.path_http_login = what_convert;
               }
               else if (what[0] == "smtp"){
			    argp.path_smtp_login = what_convert;
               }
               else if (what[0] == "hikvision"){
                   argp.path_hikvision_login = what_convert;
               }
               else {
                   break;
              }

               break;
           }
           case 11:
           {
               std::vector<std::string> what = split_string_string(optarg, DELIMITER);
               std::transform(what[0].begin(), what[0].end(), what[0].begin(), [](unsigned char c) {
                    return std::tolower(c);
               });
               const char* what_convert = what[1].c_str();
               if (what[0] == "ftp"){
                    argp.path_ftp_pass = what_convert;
               }
               else if (what[0] == "sftp"){
                   argp.path_sftp_pass = what_convert;
               }
               else if (what[0] == "rtsp"){
                   argp.path_rtsp_pass = what_convert;
               }
               else if (what[0] == "http"){
                   argp.path_http_pass = what_convert;
               }
               else if (what[0] == "smtp"){
			    argp.path_smtp_pass = what_convert;
               }
               else if (what[0] == "hikvision"){
                   argp.path_hikvision_pass = what_convert;
               }
               else {
                   break;
              }
               break;
           }
           case 30:
           {
               std::vector<std::string> what = split_string_string(optarg, DELIMITER);
                for (int i = 0; i < what.size(); i++){
                    std::transform(what[i].begin(), what[i].end(), what[i].begin(), [](unsigned char c) {
                        return std::tolower(c);
                    });
                    if (what[i] == "ftp"){
                        argp.ftp_brute_log = true;
                    }
                    else if (what[i] == "sftp"){
                        argp.sftp_brute_log = true;
                    }
                    else if (what[i] == "rtsp"){
                        argp.rtsp_brute_log = true;
                    }
                    else if (what[i] == "http"){
                        argp.http_brute_log = true;
                    }
                    else if (what[i] == "hikvision"){
                        argp.hikvision_brute_log = true;
                    }
                    else if (what[i] == "smtp"){
				    argp.smtp_brute_log = true;
                    }
                    else if (what[i] == "all"){
                        argp.ftp_brute_log = true;
				    argp.smtp_brute_log = true;
                        argp.sftp_brute_log = true;
                        argp.rtsp_brute_log = true;
                        argp.http_brute_log = true;
                        argp.hikvision_brute_log = true;
                    }
                    else {
                        break;
                    }
                }

                break;
           }
           case 31:
           {
                std::vector<std::string> what = split_string_string(optarg, DELIMITER);

                for (int i = 0; i < what.size(); i++){
                    std::transform(what[i].begin(), what[i].end(), what[i].begin(), [](unsigned char c) {
                        return std::tolower(c);
                    });
                    if (what[i] == "ftp"){
                        argp.ftp_brute_verbose = true;
                    }
                    else if (what[i] == "sftp"){
                        argp.sftp_brute_verbose = true;
                    }
                    else if (what[i] == "rtsp"){
                        argp.rtsp_brute_verbose = true;
                    }
                    else if (what[i] == "http"){
                        argp.http_brute_verbose = true;
                    }
                    else if (what[i] == "smtp"){
				    argp.smtp_brute_verbose = true;
                    }
                    else if (what[i] == "all"){
                        argp.ftp_brute_verbose = true;
                        argp.sftp_brute_verbose = true;
				    argp.smtp_brute_verbose = true;
                        argp.rtsp_brute_verbose = true;
                        argp.http_brute_verbose = true;
                    }
                    else {
                        break;
                    }
                }

               break;
           }
           case 44:
           {
               std::vector<std::string> what = split_string_string(optarg, DELIMITER);

               for (int i = 0; i < what.size(); i++){
                    std::transform(what[i].begin(), what[i].end(), what[i].begin(), [](unsigned char c) {
                        return std::tolower(c);
                    });
                   if (what[i] == "ftp"){
                       argp.off_ftp_brute = true;
                   }
                   else if (what[i] == "sftp"){
                       argp.off_sftp_brute = true;
                   }
                   else if (what[i] == "rtsp"){
                       argp.off_rtsp_brute = true;
                   }
                   else if (what[i] == "http"){
                       argp.off_http_brute = true;
                   }
                   else if (what[i] == "hikvision"){
                       argp.off_hikvision_brute = true;
                   }
                   else if (what[i] == "smtp"){
				   argp.off_smtp_brute = true;
                   }
                   else if (what[i] == "all"){
                       argp.off_ftp_brute = true;
                       argp.off_sftp_brute = true;
				   argp.off_smtp_brute = true;
                       argp.off_rtsp_brute = true;
                       argp.off_http_brute = true;
                       argp.off_hikvision_brute = true;
                   }
                   else {
                       break;
                   }
               }

               break;
           }
           case 46:
           {
               std::vector<std::string> what = split_string_string(optarg, DELIMITER);

               for (int i = 0; i < what.size(); i++){
                    std::transform(what[i].begin(), what[i].end(), what[i].begin(), [](unsigned char c) {
                        return std::tolower(c);
                    });
                   if (what[i] == "ftp"){
                       argp.ftp_only = true;
                   }
                   else if (what[i] == "sftp"){
                       argp.sftp_only = true;
                   }
                   else if (what[i] == "rtsp"){
                       argp.rtsp_only = true;
                   }
                   else if (what[i] == "http"){
                       argp.http_only = true;
                   }
                   else if (what[i] == "hikvision"){
                       argp.hikvision_only = true;
                   }
                   else if (what[i] == "smtp"){
				   argp.smtp_only = true;
                   }
                   else if (what[i] == "all"){
                       argp.sftp_only = true;
                       argp.ftp_only = true;
				   argp.smtp_only = true;
                       argp.rtsp_only = true;
                       argp.http_only = true;
                       argp.hikvision_only = true;
                   }
                   else {
                       break;
                   }
               }
               break;
           }
           case 47:
               argp.brute_timeout_ms = atoi(optarg);
               break;
           case 48:
               argp.thread_on_port = true;
               break;
           case 32:
               argp.ip_range_scan_import = true;
               argp.path_range = optarg;
               break;
           case 5:
                argp.random_ip = true;
                argp.random_ip_count = atoi(optarg); 
                break;
           case 7:
                argp.debug = true;
                break;
           case 45:
                argp.sftp_using_know_hosts = true;
                break;
          case 't':
                argp.timeout = true;
                argp.timeout_ms = atoi(optarg);
                break;
          case 'T':
                if (atoi(optarg) >= 200){
                    argp.warning_threads = true;
                    argp.threads_temp = atoi(optarg);
                }
                else {
                    argp._threads = atoi(optarg);
                }
                break;

           case 19:
                argp.dns_scan = true;
                argp.domain_1level = optarg;
                break;
           case 20:
                argp.dns_scan = true;
                argp.dns_scan_domain_count = atoi(optarg);
                break;
           case 21:
                argp.dns_dictionary = optarg;
                break;
           case 22:
                np.save_file = true;
                np.file_path_save = optarg;
                break;
           case 23:
           {
               argp.ip_scan_import = true;
               argp.path_ips = optarg;
               break;
           }
           case 24:
              argp.log_set = atoi(optarg);
              break;
           case 25:
              argp.print_errors = true;
              break;
           case 26:
           {
               np.disable_colors();
               break;
           }
           case 27:
               argp.debug = true;
               break;
           case 28:
               argp.print_errors = true;
               break;
           case 29:
               argp.ping_off = true;
               break;
           case 34:
               argp.host_testing = true;
               argp.hosts_test = split_string_string(optarg, DELIMITER);
               break;
           case 35:
               argp.response_code_test = true;
               break;
           case 36:
               argp.generation_test = true;
               argp.generate_ipv4_test = true;
               break;
           case 37:
               argp.tcp_ping_test = true;
               argp.tcp_ping_mode = optarg;
               break;
           case 38:
               argp.generate_count = atoi(optarg);
               break;
           case 39:
           {
               argp.generation_test = true;
               argp.generate_ipv6_test = true;
               argp.octets = atoi(optarg);
               break;
           }
           case 49:
		     argp.icmp_ping_timeout = atoi(optarg);
               break;
           case 50:
               argp.no_get_path = true;
               break;
           case 51:
               argp.get_response = true;
               break;
           case 52:
               argp.fix_get_path = true;
               break;
           case 53:
               argp.get_path_log = true;
               break;
           case 54:
               argp.import_color_scheme = true;
               argp.path_color_scheme = optarg;
               break;
           case 55:
               argp.get_redirect = true;
               break;
           case 57:
			argp.threads_ping = atoi(optarg);
               break;
           case 56:
               argp.http_request = true;
               break;
           case 59:
               argp.syn_debug = true;
               break;
           case 60:
               argp.syn_debug = true;
               break;
           case 61:
               argp.display_response_time = true;
               break;
	      case 90:
			argp.ping_log = atoi(optarg);
		     break;
	      case 91:
			argp.null_scan = true;
			argp.type = 4;
			break;
	      case 92:
			argp.fin_scan = true;
			argp.type = 3;
			break;
	      case 93:
			argp.xmas_scan = true;
			argp.type = 2;
			break;
	      case 95:
			argp.no_proc = true;
			break;
	      case 96:
			argp.packet_trace = true;
			break;
	      case 101:
			argp.custom_recv_timeout_ms = true;
			argp.recv_timeout_ms = atoi(optarg);
			break;
        }
    }
}
void
init_bruteforce(){
    argp.ftp_logins = write_file(argp.path_ftp_login);
    argp.ftp_passwords = write_file(argp.path_ftp_pass);

    argp.sftp_logins = write_file(argp.path_sftp_login);
    argp.sftp_passwords = write_file(argp.path_sftp_pass);

    argp.rtsp_logins = write_file(argp.path_rtsp_login);
    argp.rtsp_passwords = write_file(argp.path_rtsp_pass);

    argp.http_logins = write_file(argp.path_http_login);
    argp.http_passwords = write_file(argp.path_http_pass);

    argp.hikvision_logins = write_file(argp.path_hikvision_login);
    argp.hikvision_passwords = write_file(argp.path_hikvision_pass);

    argp.smtp_logins = write_file(argp.path_smtp_login);
    argp.smtp_passwords = write_file(argp.path_smtp_pass);
}

std::string 
format_percentage(double procents){
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << procents << "%";
    std::string result = oss.str();
    return result;
}

std::mutex ls;

int
scan_port(const char* ip, std::vector<int>ports, const int timeout_ms, const int source_port){
    struct nesca_scan_opts ncopts;
    ncopts.source_ip = argp.source_ip;
    ncopts.debug = argp.syn_debug;
    ncopts.scan_type = argp.type;
    ncopts.source_port = source_port;
    ncopts.seq = generate_seq();

    int recv_timeout_result;
    if (argp.custom_recv_timeout_ms){
	   recv_timeout_result = argp.recv_timeout_ms;
	   ncopts.recv_timeout_ms = recv_timeout_result;
    }
    else {
	   /*Расчёт таймаута для приёма данных
	   * самая простая формула, время ответа
	   * умножить на 4.*/
	   auto it = argp.rtts.find(ip);
	   if (it != argp.rtts.end()) {
		  double rtt_ping = argp.rtts.at(ip);
		  recv_timeout_result = rtt_ping * 4;
		  ncopts.recv_timeout_ms = recv_timeout_result;
	   } 
	   /*В другом случае по стандарту 600.*/
	   else {
		  recv_timeout_result = 600;
		  ncopts.recv_timeout_ms = recv_timeout_result;
	   }
    }
    for (const auto& port : ports){
	   /*Буфер для ответа.*/
	   ls.lock();
	   unsigned char *buffer = (unsigned char *)calloc(READ_BUFFER_SIZE, sizeof(unsigned char));
	   ls.unlock();

	   /*Отправка пакета.*/
	   int result = nesca_scan(&ncopts, ip, port, timeout_ms);
	   /*Лог.*/
	   if (argp.packet_trace){np.nlog_custom("SEND", "TCP >> "+ std::string(argp.source_ip)+
			 ":"+std::to_string(source_port)+" >> "+ std::string(ip)+":"+std::to_string(port)+"\n", 1);}

	   /*Если функция не вернула PORT_OPEN,
	    * Это означает что функция успешно выполнилась.*/
	   if (result != PORT_OPEN){
		  /*Значит была ошибка.*/
		  ls.lock();
		  free(buffer);
		  ls.unlock();

		  argp.error_target[ip].push_back(port);
		  argp.error_fuck++;
		  /*Переход к следующему порту.*/
		  continue;
	   }

	   /*В другом случае, запускается
	    * "Принятие пакета" или скорее его ожидание.*/
	   int read = ncread(ip, recv_timeout_result, &buffer, argp.syn_debug);
	   /*Лог.*/
	   if (argp.packet_trace){np.nlog_custom("RECV", "TCP >> "+ std::string(ip)+
			 ":"+std::to_string(port)+" >> "+ std::string(argp.source_ip)+":"+std::to_string(source_port)+"\n", 1);}


	   /*Если функция не получила пакет.*/
	   if (read != SUCCESS_READ){
		  /*Значит порт filtered.*/
		  ls.lock();
		  free(buffer);
		  ls.unlock();
		  argp.filtered_target[ip].push_back(port);
		  continue;
	   }

	   /*В другом случае идёт обработка пакета.
	    * И только на этом этапе мы получаем статус порта.*/
	   int port_status = get_port_status(buffer, false);

	   if (port_status == PORT_CLOSED){argp.closed_target[ip].push_back(port);}
	   else if (port_status == PORT_OPEN){argp.success_target[ip].push_back(port); argp.fuck_yeah++;}
	   else if (port_status == PORT_FILTER){argp.filtered_target[ip].push_back(port);}
	   else {argp.error_target[ip].push_back(port); argp.error_fuck++;}

	   /*Дальше уже операции что делать с этим портом.*/
	   ls.lock();
	   free(buffer);
	   ls.unlock();
    }
    return 0;
}

