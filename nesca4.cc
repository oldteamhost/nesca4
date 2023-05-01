// NESCA4
// by oldteam & lomaster
// license GPL-3.0
// // // // // // // // // 

#include <cstddef>
#include <iostream>
#include <chrono>
#include <future>
#include <netdb.h>
#include <thread>
#include <getopt.h>
#include <mutex>
#include <algorithm> 
#include <random>
#include <string>
#include <sstream>
#include <vector>

#include "include/bruteforce.h"
#include "include/callbacks.h"
#include "include/files.h"
#include "include/generation.h"
#include "include/networktool.h"
#include "include/other.h"
#include "include/scanner.h"
#include "include/target.h"

#define VERSION "1974-build"
#define DELIMITER ','

std::mutex mtx;
checking_finds cfs;

std::string logo_red = "\033[38;2;255;100;100m";
std::string gray_nesca = "\033[38;2;112;112;112m";
std::string golder_rod = "\033[38;2;218;165;32m";
std::string sea_green = "\033[38;2;60;179;113;4m";
std::string green_html = "\033[38;2;45;235;65m";
std::string red_html = "\033[38;2;240;50;55m";
std::string yellow_html = "\033[38;2;240;215;75m";
std::string reset_color = "\033[0m";

// main
void help_menu(void);
void processing_tcp_scan_ports(const std::string& ip, const std::vector<int>& ports, int timeout_ms);
void checking_default_files(void);

class arguments_program{
    public:
        std::string ports_temp;
        std::string domain_1level;
        std::vector<std::string> hosts_test;
        std::string txt_save;
        std::string tcp_ping_mode;
        std::string dns_dictionary = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

        std::vector<std::string> _ip;
        std::vector<std::string> ip_cidr;
        std::vector<std::string> ip_range;

        std::vector<std::string> ftp_logins;
        std::vector<std::string> ftp_passwords;

        std::vector<std::string> rtsp_logins;
        std::vector<std::string> rtsp_passwords;

        std::vector<std::string> sftp_logins;
        std::vector<std::string> sftp_passwords;

        std::vector<std::string> http_logins;
        std::vector<std::string> http_passwords;

        const char* path_range;
        const char* path_cidr;
        const char* path_ips;

        std::string path_ftp_login = "passwd/ftp_logins.txt";
        std::string path_ftp_pass = "passwd/ftp_passwords.txt";

        std::string path_sftp_login = "passwd/sftp_logins.txt";
        std::string path_sftp_pass = "passwd/sftp_passwords.txt";

        std::string path_rtsp_login = "passwd/rtsp_logins.txt";
        std::string path_rtsp_pass = "passwd/rtsp_passwords.txt";

        std::string path_http_login = "passwd/http_logins.txt";
        std::string path_http_pass = "passwd/http_passwords.txt";

        int random_ip_count;
        int octets;
        int generate_count;
        int brute_timeout_ms = 10;
        int log_set = 1000;
        int threads_temp;
        int dns_scan_domain_count = 5;
        int timeout_ms = 300;
        int _threads = 20;

        std::vector<int> ports;

        bool random_ip;
        bool dns_scan;
        bool print_help_menu;
        bool ip_scan_import;
        bool ip_scan;
        bool ip_cidr_scan;
        bool ip_cidr_scan_import;
        bool ip_range_scan;
        bool ip_range_scan_import;

        bool debug;
        bool warning_threads;
        bool ping_off;
        bool no_get_dns;
        bool txt;
        bool html;
        bool color_off;

        bool ftp_brute_log;
        bool sftp_brute_log;
        bool rtsp_brute_log;
        bool http_brute_log;

        bool ftp_brute_verbose;
        bool sftp_brute_verbose;
        bool rtsp_brute_verbose;
        bool http_brute_verbose;

        bool sftp_using_know_hosts;

        bool timeout;
        bool print_errors;
        bool off_ftp_brute;
        bool off_sftp_brute;
        bool off_rtsp_brute;
        bool off_http_brute;

        bool ftp_only;
        bool no_get_path;
        bool sftp_only;
        bool http_only;
        bool rtsp_only;

        bool generation_test;

        bool host_testing;
        bool thread_on_port;
        bool response_code_test;
        bool tcp_ping_test;
        bool generate_ipv4_test;
        bool generate_ipv6_test;
};
arguments_program argp;

const char* run; // for help menu

int main(int argc, char** argv){

    if (check_ansi_support() != true){
        std::cout << "You terminal don`t support ansi colors!\n";
        logo_red = "";
        gray_nesca = "";
        golder_rod = "";
        sea_green =  "";
        green_html = "";
        red_html =  "";
        yellow_html = "";
    }

    logo();
    run = argv[0];

    const char* short_options = "hvt:T:p:";
    const struct option long_options[] = {

        {"threads", required_argument, 0, 'T'},
        {"timeout", required_argument, 0, 't'},

        {"ip", required_argument, 0, 1},
        {"cidr", required_argument, 0, 2},
        {"range", required_argument, 0, 33},
        {"import-ip", required_argument, 0, 23},
        {"import-cidr", required_argument, 0, 3},
        {"import-range", required_argument, 0, 32},

        {"random-ip", required_argument, 0, 5},

        {"brute-login", required_argument, 0, 12},
        {"brute-pass", required_argument, 0, 11},

        {"brute-log", required_argument, 0, 30},
        {"brute-verbose", required_argument, 0, 31},
        {"thread-on-port", no_argument, 0, 48},
        {"brute-off", required_argument, 0, 44},
        {"brute-only", required_argument, 0, 46},
        {"brute-timeout", required_argument, 0, 47},

        {"sftp-brute-known-hosts", no_argument, 0, 45},

        {"dns-scan", required_argument, 0, 19},
        {"dns-length", required_argument, 0, 20},
        {"dns-dict", required_argument, 0, 21},
        {"txt", required_argument, 0, 22},
        {"debug", no_argument, 0, 27},
        {"on-get-dns", no_argument, 0, 8},
        {"er", no_argument, 0, 28},
        {"no-get-path", no_argument, 0, 50},
        {"no-ping", no_argument, 0, 29},
        {"no-color", no_argument, 0, 26},
        {"log-set", required_argument, 0, 24},

        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {"ports", no_argument, 0, 'p'},

        {"db", no_argument, 0, 7},
        {"error", no_argument, 0, 25},

        {"response-code", no_argument, 0, 35},
        {"gen-ipv4", no_argument, 0, 36},
        {"host-test", required_argument, 0, 34},
        {"tcp-ping", required_argument, 0, 37},
        {"gen-count", required_argument, 0, 38},
        {"gen-ipv6", required_argument, 0, 39},
        {0,0,0,0}
    };

    if (argc <= 1){
        help_menu();
        return 1;
    }

    int rez;
    int option_index = 0;

    while ((rez = getopt_long_only(argc, argv, short_options, long_options, &option_index)) != EOF) {
        switch (rez) {
            case 'h':
                argp.print_help_menu = true;
                break;
            case 'v':
                std::cout << VERSION << std::endl;
                return 0;
                break;
            case 'p':
            {
                argp.ports_temp = optarg;
                argp.ports = write_ports(argp.ports_temp);
                if (argp.ports[0] == -1){
                    argp.ports = split_string_int(optarg, DELIMITER);
                }
                break;
            }
            case 1:
            {
                argp.ip_scan = true;
                argp._ip = split_string_string(optarg, DELIMITER);
                break;
            }
            case 2:
            {
                argp.ip_cidr_scan = true;
                argp.ip_cidr = split_string_string(optarg, DELIMITER);
                break;
            }
            case 3:
            {
               argp.ip_cidr_scan_import = true;
               argp.path_cidr = optarg;
               break;
            }
           case 8:
               argp.no_get_dns = true;
               break;
           case 12:
           {
               std::vector<std::string> what = split_string_string(optarg, DELIMITER);
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
               else {
                   break;
              }

               break;
           }
           case 11:
           {
               std::vector<std::string> what = split_string_string(optarg, DELIMITER);
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
               else {
                   break;
              }
               break;
           }
           case 30:
           {
               std::vector<std::string> what = split_string_string(optarg, DELIMITER);
                for (int i = 0; i < what.size(); i++){
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
                    else if (what[i] == "all"){
                        argp.ftp_brute_log = true;
                        argp.sftp_brute_log = true;
                        argp.rtsp_brute_log = true;
                        argp.http_brute_log = true;
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
                    else if (what[i] == "all"){
                        argp.ftp_brute_verbose = true;
                        argp.sftp_brute_verbose = true;
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
                   else if (what[i] == "all"){
                       argp.off_ftp_brute = true;
                       argp.off_sftp_brute = true;
                       argp.off_rtsp_brute = true;
                       argp.off_http_brute = true;
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
                   else if (what[i] == "all"){
                       argp.sftp_only = true;
                       argp.ftp_only = true;
                       argp.rtsp_only = true;
                       argp.http_only = true;
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
           case 33:
               argp.ip_range_scan = true;
               argp.ip_range = split_string_string(optarg, DELIMITER);
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
                argp.txt = true;
                argp.txt_save = optarg;
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
               logo_red = "";
               gray_nesca = "";
               golder_rod = "";
               sea_green =  "";
               green_html = "";
               red_html =  "";
               yellow_html = ""; 
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
           case 50:
               argp.no_get_path = true;
               break;
        }
    }

    if (argp.print_help_menu){
        help_menu();
        return 0;
    }

    if (argp.host_testing){
        if (argp.response_code_test){
            for (int i = 0; i < argp.hosts_test.size(); i++){
            std::ostringstream strs;
            strs << get_response_code(argp.hosts_test[i].c_str());
            std::string code = strs.str();
            std::string result_print = gray_nesca + "[" + std::string(get_time()) + "][TT]:" + sea_green + argp.hosts_test[i] + reset_color + gray_nesca + " C: " + golder_rod + code + reset_color;
            std::cout << result_print << std::endl;
            }
        }
        if (argp.tcp_ping_test){
            if (argp.tcp_ping_mode == "live" || argp.tcp_ping_mode == "1"){
                for (;;){
                    std::ostringstream strs;
                    double ping_temp = measure_ping_time(argp.hosts_test[0].c_str(), 80);
                    strs << ping_temp;
                    std::string ping = strs.str();
                    if (ping_temp != -1){
                        if (ping_temp != -2){
                            std::string result_print = gray_nesca + "[" + std::string(get_time()) + "][TT]:" + sea_green + argp.hosts_test[0] + reset_color + gray_nesca + " P: " + golder_rod + ping + "ms" + reset_color;
                            std::cout << result_print << std::endl;
                        }
                    }
                    else {
                        std::cout << red_html;
                        std::string result_print;
                        result_print = "[" + std::string(get_time()) + "][TT]:" + argp.hosts_test[0] + " P: down";

                        if (ping_temp == -2){
                            result_print = "[" + std::string(get_time()) + "][TT][ERROR]: info check failed!";
                        }
                        else if (ping_temp == -3){
                            result_print = "[" + std::string(get_time()) + "][TT][ERROR]: connection failed!!";
                        }

                        std::cout << result_print << std::endl;
                        std::cout << reset_color;
                    }
                    delay_ms(argp.timeout_ms);
                }
            }
            else if (argp.tcp_ping_mode == "default" || argp.tcp_ping_mode == "0") {
                for (int i = 0; i < argp.hosts_test.size(); i++){
                    std::ostringstream strs;
                    double ping_temp = measure_ping_time(argp.hosts_test[i].c_str(), 80);
                    strs << ping_temp;
                    std::string ping = strs.str();

                    if (ping_temp != -1){
                        if (ping_temp != -2){
                            std::string result_print = gray_nesca + "[" + std::string(get_time()) + "][TT]:" + sea_green + argp.hosts_test[i] + reset_color + gray_nesca + " P: " + golder_rod + ping + "ms" + reset_color;
                            std::cout << result_print << std::endl;
                        }
                    }

                    else {
                        std::cout << red_html;
                        std::string result_print;
                        result_print = "[" + std::string(get_time()) + "][TT]:" + argp.hosts_test[i] + " P: down";

                        if (ping_temp == -2){
                            result_print = "[" + std::string(get_time()) + "][TT][ERROR]: info check failed!";
                        }
                        else if (ping_temp == -3){
                            result_print = "[" + std::string(get_time()) + "][TT][ERROR]: connection failed!!";
                        }

                        std::cout << result_print << std::endl;
                        std::cout << reset_color;
                        delay_ms(argp.timeout_ms);
                    }
                }
            }
            else {
                std::string result_print = "[" + std::string(get_time()) + "][TT][ERROR]: ping mode not found! Only (0,1) aka (default, live).";
                std::cout << red_html;
                std::cout << result_print << std::endl;
                std::cout << reset_color;
           }
        }
        return 0;
    }
    if (argp.generation_test){
        if (argp.generate_ipv4_test){
            for (int i = 1; i <= argp.generate_count; i++){
                std::string result_print = gray_nesca + "[" + std::string(get_time()) + "][TT]:" + reset_color + sea_green + generate_ipv4() + reset_color;
                std::cout << result_print << std::endl;
            }
        }
        if (argp.generate_ipv6_test){
            for (int i = 1; i <= argp.generate_count; i++){
                std::string result_print = gray_nesca + "[" + std::string(get_time()) + "][TT]:" + reset_color + sea_green + generate_ipv6(argp.octets) + reset_color;
                std::cout << result_print << std::endl;
            }
        }
        return 0;
    }

    if (argp.warning_threads){
        char what;
        std::cout << red_html;
        std::cout << "[" << get_time() << "]" << "[WARING]:You set " << argp.threads_temp << " threads, this can severely overload a weak cpu, are you sure you want to continue? (y,n): ";

        std::cin >> what;
        std::cout << reset_color;

        if (what != 'y'){
            return 0;
        }
        else {
            argp._threads = argp.threads_temp;
        }
    }

    checking_default_files();

    std::cout << green_html;
    std::cout << "[" << get_time() << "]" << "[OK]:Starting " << argp._threads << " threads...\n\n";
    std::cout << reset_color;

        // start dns_scan
        if (argp.dns_scan){
            argp.timeout_ms = 100;
            std::mutex mtx;
            for (int i = 0; i < argp._threads; i++) {
            std::thread([&](){
                for (;;) {
                    std::string random_ = generate_random_str(argp.dns_scan_domain_count, argp.dns_dictionary);
                    std::string result = "http://" + random_ + argp.domain_1level;
                    std::string result_print;

                    int test = dns_scan("http://" + random_, argp.domain_1level);

                    if (test == 0) {
                        if (argp.debug) {
                            std::lock_guard<std::mutex> lock(mtx);
                            result_print = "[" + std::string(get_time()) + "] [BA] " + result + " FAILED";
                            std::string *result_printp = &result_print;

                            if (argp.txt){
                                int temp = write_line(argp.txt_save, *result_printp);
                            }

                            std::cout << yellow_html;
                            std::cout << result_print << std::endl;
                            std::cout << reset_color;
                        }
                    }
                    else {
                        std::lock_guard<std::mutex> lock(mtx);
                        std::string result_print_color = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + result + reset_color + gray_nesca + " T: " + golder_rod + get_html_title(result) + reset_color;
                        std::string result_txt = "[" + std::string(get_time()) + "][BA]:" + result + " T: " + get_html_title(result);
                        std::string *result_printp = &result_txt;
                        if (argp.txt){
                            int temp = write_line(argp.txt_save, *result_printp);
                        }
                        std::cout << result_print_color << std::endl;
                    }
                }
            }).detach();
            if (argp.timeout)
                delay_ms(argp.timeout_ms);
        }
        std::getchar();
        std::cout << green_html;
        std::cout << "\nStoping threads...\n";
        std::cout << reset_color;
    }
    // end dns_scan

    // start tcp_scan_port

    argp.ftp_logins = write_file(argp.path_ftp_login);
    argp.ftp_passwords = write_file(argp.path_ftp_pass);

    argp.sftp_logins = write_file(argp.path_sftp_login);
    argp.sftp_passwords = write_file(argp.path_sftp_pass);

    argp.rtsp_logins = write_file(argp.path_rtsp_login);
    argp.rtsp_passwords = write_file(argp.path_rtsp_pass);

    argp.http_logins = write_file(argp.path_http_login);
    argp.http_passwords = write_file(argp.path_http_pass);

    std::vector<std::string> result;
    
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

    std::vector<std::thread> threads;

    long ip_count = 0;
    int size = result.size();
    for (const auto& ip : result) {
        threads.emplace_back(processing_tcp_scan_ports, ip, argp.ports, argp.timeout_ms);
        ip_count++;

        if (ip_count % argp.log_set == 0){
            std::lock_guard<std::mutex> lock(mtx);
            std::string result_print = "[" + std::string(get_time()) + "][NB]:" + std::to_string(ip_count) + " out of " + std::to_string(size) + " IPs scanned.";
            std::cout << yellow_html;
            std::cout << result_print << std::endl;
            std::cout << reset_color;
        }

        if (ip_count % argp._threads == 0) {
            for (auto& t : threads) {
                t.join();
            }
            threads.clear();
        }
    }
    for (auto& t : threads) {
        t.join();
    }
    // end tcp_scan_port

    return 0;
}

void checking_default_files(void){
    const char* path0 = "ip.txt";

    if (argp.ip_cidr_scan_import){
       if (check_file(argp.path_cidr)){
            std::cout << green_html;
            if (argp.ip_cidr_scan){
                std::cout << "[" << get_time() << "]" << "[OK]:" << argp.path_cidr << " (" << get_count_lines(argp.path_cidr) << ") entries" << std::endl;
            }
            else {
                std::cout << "[" << get_time() << "]" << "[OK]:" << argp.path_cidr << " (" << get_count_lines(argp.path_cidr) << ") entries" << std::endl;
            }
            argp.ip_cidr = write_file(argp.path_cidr);  
       }
       else {
            std::cout << yellow_html;
            std::cout << "[" << get_time() << "]" << "[FAILED]:" << argp.path_cidr << " (" << get_count_lines(argp.path_cidr) << ") entries" << std::endl;
            std::cout << reset_color;
       }
    }

    if (argp.ip_range_scan_import){
        if (check_file(argp.path_range)){
            std::cout << green_html;

            if (argp.ip_range_scan){
                std::cout << "[" << get_time() << "]" << "[OK]:" << argp.path_range << " (" << get_count_lines(argp.path_range) << ") entries" << std::endl;
            }
            else {
                std::cout << "[" << get_time() << "]" << "[OK]:" << argp.path_range << " (" << get_count_lines(argp.path_range) << ") entries" << std::endl;
            }
            argp.ip_range = write_file(argp.path_range);
        }
        else {
            std::cout << yellow_html;
            std::cout << "[" << get_time() << "]" << "[FAILED]:" << argp.path_range << " (" << get_count_lines(argp.path_range) << ") entries" << std::endl;
            std::cout << reset_color;
        }
    }

    if (argp.ip_scan_import){
       if (check_file(argp.path_ips)){
            std::cout << green_html;
            std::cout << "[" << get_time() << "]" << "[OK]:" << argp.path_ips << " (" << get_count_lines(argp.path_ips) << ") entries" << std::endl;
            argp._ip = write_file(argp.path_ips);  
       }
       else {
            std::cout << yellow_html;
            std::cout << "[" << get_time() << "]" << "[FAILED]:" << argp.path_ips << " (" << get_count_lines(argp.path_ips) << ") entries" << std::endl;
            std::cout << reset_color;
       }
    }

    if (check_file(argp.path_ftp_login.c_str())){
       std::cout << green_html;
       std::cout << "[" << get_time() << "]" << "[OK]:FTP logins loaded (" << get_count_lines(argp.path_ftp_login.c_str()) << ") entries" << std::endl;
       std::cout << reset_color;
    }
    else {
        std::cout << yellow_html;
        std::cout << "[" << get_time() << "]" << "[FAILED]:" << argp.path_ftp_login << " (" << get_count_lines(argp.path_ftp_login.c_str()) << ") entries" << std::endl;
        std::cout << reset_color;
    }
    if (check_file(argp.path_ftp_pass.c_str())){
        std::cout << green_html;
        std::cout << "[" << get_time() << "]" << "[OK]:FTP passwords loaded (" << get_count_lines(argp.path_ftp_pass.c_str()) << ") entries" << std::endl;
        std::cout << reset_color;
    }
    else {
        std::cout << yellow_html;
        std::cout << "[" << get_time() << "]" << "[FAILED]:" << argp.path_ftp_pass << " (" << get_count_lines(argp.path_ftp_pass.c_str()) << ") entries" << std::endl;
        std::cout << reset_color;
    }
    if (check_file(argp.path_http_login.c_str())){
       std::cout << green_html;
       std::cout << "[" << get_time() << "]" << "[OK]:HTTP logins loaded (" << get_count_lines(argp.path_http_login.c_str()) << ") entries" << std::endl;
       std::cout << reset_color;
    }
    else {
        std::cout << yellow_html;
        std::cout << "[" << get_time() << "]" << "[FAILED]:" << argp.path_http_login << " (" << get_count_lines(argp.path_http_login.c_str()) << ") entries" << std::endl;
        std::cout << reset_color;
    }
    if (check_file(argp.path_http_pass.c_str())){
       std::cout << green_html;
       std::cout << "[" << get_time() << "]" << "[OK]:HTTP passwords loaded (" << get_count_lines(argp.path_http_pass.c_str()) << ") entries" << std::endl;
       std::cout << reset_color;
    }
    else {
        std::cout << yellow_html;
        std::cout << "[" << get_time() << "]" << "[FAILED]:" << argp.path_http_pass << " (" << get_count_lines(argp.path_http_pass.c_str()) << ") entries" << std::endl;
        std::cout << reset_color;
    }

    if (check_file(argp.path_sftp_login.c_str())){
       std::cout << green_html;
       std::cout << "[" << get_time() << "]" << "[OK]:SSH logins loaded (" << get_count_lines(argp.path_sftp_login.c_str()) << ") entries" << std::endl;
       std::cout << reset_color;
    }
    else {
        std::cout << yellow_html;
        std::cout << "[" << get_time() << "]" << "[FAILED]:" << argp.path_sftp_login << " (" << get_count_lines(argp.path_sftp_login.c_str()) << ") entries" << std::endl;
        std::cout << reset_color;
    }
    if (check_file(argp.path_sftp_pass.c_str())){
       std::cout << green_html;
       std::cout << "[" << get_time() << "]" << "[OK]:SSH passwords loaded (" << get_count_lines(argp.path_sftp_pass.c_str()) << ") entries" << std::endl;
       std::cout << reset_color;
    }
    else {
        std::cout << yellow_html;
        std::cout << "[" << get_time() << "]" << "[FAILED]:" << argp.path_sftp_pass << " (" << get_count_lines(argp.path_sftp_pass.c_str()) << ") entries" << std::endl;
        std::cout << reset_color;
    }
    std::cout << reset_color;

    if (check_file(argp.path_rtsp_login.c_str())){
       std::cout << green_html;
       std::cout << "[" << get_time() << "]" << "[OK]:RTSP logins loaded (" << get_count_lines(argp.path_rtsp_login.c_str()) << ") entries" << std::endl;
       std::cout << reset_color;
    }
    else {
        std::cout << yellow_html;
        std::cout << "[" << get_time() << "]" << "[FAILED]:" << argp.path_rtsp_login << " (" << get_count_lines(argp.path_rtsp_login.c_str()) << ") entries" << std::endl;
        std::cout << reset_color;
    }
    if (check_file(argp.path_rtsp_pass.c_str())){
       std::cout << green_html;
       std::cout << "[" << get_time() << "]" << "[OK]:RTSP passwords loaded (" << get_count_lines(argp.path_rtsp_pass.c_str()) << ") entries" << std::endl;
       std::cout << reset_color;
    }
    else {
        std::cout << yellow_html;
        std::cout << "[" << get_time() << "]" << "[FAILED]:" << argp.path_rtsp_pass << " (" << get_count_lines(argp.path_rtsp_pass.c_str()) << ") entries" << std::endl;
        std::cout << reset_color;
    }
    std::cout << reset_color;
}

void processing_tcp_scan_ports(const std::string& ip, const std::vector<int>& ports, int timeout_ms){
    for (const auto& port : ports) {
        int result = tcp_scan_port(ip.c_str(), port, timeout_ms);
        if (result == 0) {
            if (port == 80 || port == 81 || port == 8080 || port == 8081 || port == 8888 || port == 8008){

                if (argp.ping_off != true){
                    double temp_ping = measure_ping_time(ip.c_str(), port);

                    if (temp_ping == -1 || temp_ping == -2){
                        return;
                    }
                }

                std::string result = "http://" + ip + ":" + std::to_string(port);
                std::string redirect;
                if (argp.no_get_path != true){
                    // getting method 1 from content location:
                    std::string path = get_paths_from_ip_address(ip);

                    if (path.length() > 1){
                        redirect = "http://" + ip + ":" + std::to_string(port) + path;
                    }
                    else {
                        // getting method 2 from http-equiv
                        std::string code = send_http_request(ip);
                        std::string path1 = parse_content_from_meta(code);
                        std::string paste_;

                        if (path1.length() > 1) {
                            redirect = parse_content_from_meta("http://" + code);

                            // clean redirect    
                            std::vector<std::string> pos_clean = {"http://", "https://", ip};
                            size_t finding0 = redirect.find("http://");
                            size_t finding1 = redirect.find("https://");
                            size_t finding2 = redirect.find("ip");

                            if (finding1 == std::string::npos && finding1 == std::string::npos && finding2 == std::string::npos){
                                if (redirect[0] != '/'){
                                    paste_ = "http://" + ip + ":" + std::to_string(port) + "/";
                                }
                                else {
                                    paste_ = "http://" + ip + ":" + std::to_string(port);
                                }

                                redirect.insert(0, paste_);
                            }
                        }
                    }

                    std::string axis_camera = cfs.check_axis_camera(path);
                    std::string basic_auth = cfs.check_basic_auth(path);

                    if (basic_auth.length() > 1 || axis_camera.length() > 1){
                    }
                   // threads_brute_http(result, argp.http_logins, argp.http_passwords, argp.http_brute_log, argp.http_brute_verbose, argp.brute_timeout_ms);
                }
              
                std::string result_print;
                if (argp.no_get_dns){
                    result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + result + reset_color + gray_nesca + " T: " + golder_rod + get_html_title(ip) + reset_color + gray_nesca + " D: " + sea_green + get_dns_ip(ip.c_str()) + reset_color;
                }
                else {
                    result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + result + reset_color + gray_nesca + " T: " + golder_rod + get_html_title(ip) + reset_color;
                }
                std::string result_txt = "[" + std::string(get_time()) + "][BA]:" + result + " T: " + get_html_title(ip);

                std::lock_guard<std::mutex> guard(mtx);
                if (argp.txt){
                    int temp = write_line(argp.txt_save, result_txt);
                }
                std::cout << result_print << std::endl;
                if (argp.no_get_path != true && redirect.length() != result.length()){
                    if (redirect.length() != 0){
                        std::cout << yellow_html;
                        std::cout << "[" << get_time() << "][^] Redirect to: " << redirect << std::endl;
                        std::cout << reset_color;
                    }
                }
            }
            else if (port == 20 || port == 21){
                std::lock_guard<std::mutex> guard(mtx);

                std::string result = ip + ":" + std::to_string(port);
                std::string result_print_brute;
                std::string result_txt;
                std::string brute_temp;
                std::string result_print;

                if (argp.off_ftp_brute != true){
                    result_print_brute = "[" + std::string(get_time()) + "][FTP]:" + ip + " [BRUTEFORCE]";

                    std::cout << yellow_html;
                    std::cout << result_print_brute << std::endl;
                    std::cout << reset_color;

                    brute_temp = threads_brute_ftp(ip, argp.ftp_logins, argp.ftp_passwords, argp.ftp_brute_log, argp.ftp_brute_verbose, argp.brute_timeout_ms);
                    result_txt = "[" + std::string(get_time()) + "][FTP]:" + brute_temp + result;
                }
                else {
                    result_txt = "[" + std::string(get_time()) + "][FTP]:" + result;
                }
                if (argp.off_ftp_brute != true){
                    if (argp.ftp_only){
                        if (brute_temp.length() > 1){
                            result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + brute_temp + result + reset_color;
                        }
                    }
                    else {
                        result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + brute_temp + result + reset_color + "\n";
                    }
                }
                else {
                    result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + result + reset_color;
                }
                if (argp.txt){
                    int temp = write_line(argp.txt_save, result_txt);
                }


                std::cout << result_print;

            }
            else if (port == 22){
                std::lock_guard<std::mutex> guard(mtx);

                std::string result = ip + ":" + std::to_string(port);
                std::string result_print_brute;
                std::string result_txt;
                std::string brute_temp;
                std::string result_print;

                if (argp.off_sftp_brute != true){
                    result_print_brute = "[" + std::string(get_time()) + "][SFTP]:" + ip + " [BRUTEFORCE]";

                    std::cout << yellow_html;
                    std::cout << result_print_brute << std::endl;
                    std::cout << reset_color;

                    brute_temp = threads_brute_ssh(ip, argp.sftp_logins, argp.sftp_passwords, argp.sftp_brute_log, argp.sftp_brute_verbose, argp.sftp_using_know_hosts, argp.brute_timeout_ms);
                    result_txt = "[" + std::string(get_time()) + "][SFTP]:" + brute_temp + result;
                }
                else {
                    result_txt = "[" + std::string(get_time()) + "][SFTP]:" + result;
                }
                if (argp.off_sftp_brute != true){
                    if (argp.sftp_only){
                        if (brute_temp.length() > 1){
                            result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + brute_temp + result + reset_color;
                        }
                    }
                    else {
                        result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + brute_temp + result + reset_color + "\n";
                    }
                }
                else {
                    result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + result + reset_color + "\n";
                }
                if (argp.txt){
                    int temp = write_line(argp.txt_save, result_txt);
                }

                std::cout << result_print;
            }
            else if (port == 554){
                std::lock_guard<std::mutex> guard(mtx);

                std::string result = ip + ":" + std::to_string(port);
                std::string result_print_brute;
                std::string result_txt;
                std::string brute_temp;
                std::string result_print;

                if (argp.off_rtsp_brute != true){
                    result_print_brute = "[" + std::string(get_time()) + "][RTSP]:" + ip + " [BRUTEFORCE]";

                    std::cout << yellow_html;
                    std::cout << result_print_brute << std::endl;
                    std::cout << reset_color;
                    brute_temp = threads_brute_rtsp(ip, argp.rtsp_logins, argp.rtsp_passwords, argp.rtsp_brute_log, argp.rtsp_brute_verbose, argp.brute_timeout_ms);
                    result_txt = "[" + std::string(get_time()) + "][RTSP]:" + brute_temp + result;
                }
                else {
                    result_txt = "[" + std::string(get_time()) + "][RTSP]:" + result;
                }
                if (argp.off_rtsp_brute != true){
                    if (argp.rtsp_only){
                        if (brute_temp.length() > 1){
                            result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + brute_temp + result + reset_color;
                        }
                    }
                    else {
                        result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + brute_temp + result + reset_color + "\n";
                    }
                }
                else {
                    result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + result + reset_color;
                }
                if (argp.txt){
                    int temp = write_line(argp.txt_save, result_txt);
                }

                std::cout << result_print;
            }
            else{
                std::string result = ip + ":" + std::to_string(port);
                std::string result_print = gray_nesca + "[" + std::string(get_time()) + "][BA]:" + sea_green + result + reset_color;
                std::string result_txt = "[" + std::string(get_time()) + "][BA]:" + result;
                
                std::lock_guard<std::mutex> guard(mtx);
                if (argp.txt){
                    int temp = write_line(argp.txt_save, result_txt);
                }

                std::cout << result_print << std::endl;
            }
        }
        else if (result == -1 || result == -2 || result == -3){
            if (argp.print_errors){
                std::string result_print = "[" + std::string(get_time()) + "][NB]:" + ip + " [ERROR]: " + std::to_string(result);
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << red_html;
                std::cout << result_print << std::endl;
                std::cout << reset_color;
            }
        }
        else if (result == 1) {
            if (argp.debug){
                std::string result_txt = "[" + std::string(get_time()) + "][DB]:" + ip + ":" + std::to_string(port) + " [CLOSED]";
                std::string result_print = gray_nesca + "[" + std::string(get_time()) + "][DB]:" + yellow_html + ip + ":" + std::to_string(port) + " [CLOSED]" + reset_color;
                std::lock_guard<std::mutex> guard(mtx);
                if (argp.txt){
                    int temp = write_line(argp.txt_save, result_txt);
                }
                std::cout << result_print << std::endl;
            }
        }
        else if (result == 2){
            if (argp.debug){
                std::string result_txt = "[" + std::string(get_time()) + "][DB]:" + ip + ":" + std::to_string(port) + " [FILTER]";
                std::string result_print = gray_nesca + "[" + std::string(get_time()) + "][DB]:" + yellow_html + ip + ":" + std::to_string(port) + " [FILTER]" + reset_color;
                std::lock_guard<std::mutex> guard(mtx);

                std::cout << result_print << std::endl;
            }
        }
    }
}

void help_menu(void){
    std::cout << golder_rod;
    std::cout << "usage: " << run << " [flags]\n";
    std::cout << reset_color;

    std:: cout << sea_green;
    std::cout << "\narguments target:" << std::endl;
    std::cout << reset_color;
    std::cout << "  -ip <1,2,3>            Set ip target.\n";
    std::cout << "  -cidr <1,2,3>          Set cidr target.\n";
    std::cout << "  -range <1,2,3>         Set range target.\n";
    std::cout << "  -import-ip <path>      Set ips on target from file.\n";
    std::cout << "  -import-cidr <path>    Set cidr on target from file.\n";
    std::cout << "  -import-range <path>   Set range on target from file.\n";
    std::cout << "  -random-ip <count>     Set random ips target.\n";

    std::cout << sea_green;
    std::cout << "\narguments ports:" << std::endl;
    std::cout << reset_color;
    std::cout << "  -ports, -p <1,2,3>     Set ports on scan.\n";
    std::cout << "     - example ports:    all, nesca, top100, top50\n";

    std::cout << sea_green;
    std::cout << "\narguments speed:" << std::endl;
    std::cout << reset_color;
    std::cout << "  -threads, -T <count>   Set threads for scan.\n";
    std::cout << "  -timeout, -t <ms>      Set timeout for scan.\n";

    std::cout << sea_green;
    std::cout << "\narguments bruteforce:" << std::endl;
    std::cout << reset_color;
    std::cout << "  -brute-login <ss,path> Set path for <ss> logins.\n";
    std::cout << "  -brute-pass <ss,path>  Set path for <ss> passwords.\n";
    std::cout << "  -brute-timeout <ms>    Edit brute timout.\n";
    std::cout << "  -brute-only <ss,2>     Display only success <ss> bruteforce.\n";
    std::cout << "  -no-brute <ss,2>       Disable <ss> bruteforce.\n";

    std::cout << sea_green;
    std::cout << "\narguments other bruteforce:" << std::endl;
    std::cout << reset_color;
    std::cout << "  -brute-verbose <ss,2>  Display bruteforce <ss> all info.\n";
    std::cout << "  -brute-log <ss,2>      Display bruteforce <ss> info.\n";
    std::cout << "  -sftp-brute-known-hosts Reading known_host for connection.\n";

    std::cout << sea_green;
    std::cout << "\narguments dns-scan:" << std::endl;
    std::cout << reset_color;
    std::cout << "  -dns-scan <.dns>       On dns-scan and set domain 1 level.\n";
    std::cout << "  -dns-length <count>    Edit length generating domain.\n";
    std::cout << "  -dns-dict <dict>       Edit dictionary for generation.\n";

    std::cout << sea_green;
    std::cout << "\narguments output:" << std::endl;
    std::cout << reset_color;
    std::cout << "  -db, -debug            On debug mode, save and display not even working hosts.\n";
    std::cout << "  -er, -error            On display errors.\n";
    std::cout << "  -no-color              Disable colors.\n";
    std::cout << "  -no-get-path           Disable getting paths.\n";
    std::cout << "  -on-get-dns            On get dns for scanning ports.\n";
    std::cout << "  -log-set <count>       Change change the value of ips after which, will be displayed information about how much is left.\n";
    std::cout << "  -txt <path>            Save result to text document.\n";

    std::cout << sea_green;
    std::cout << "\narguments testing:" << std::endl;
    std::cout << reset_color;
    std::cout << "  -host-test <1,2,3>     Set host for testing.\n";
    std::cout << "  -response-code         Get response code from host.\n";
    std::cout << "  -tcp-ping <mode>       Get response time from host, modes (live) or (default).\n";

    std::cout << sea_green;
    std::cout << "\narguments generation:" << std::endl;
    std::cout << reset_color;
    std::cout << "  -gen-count <count>     Set count for generation.\n";
    std::cout << "  -gen-ipv6 <octets>     Generate ip version 6.\n";
    std::cout << "  -gen-ipv4              Generate ip version 4.\n";
}
