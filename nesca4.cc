// NESCA4
// by oldteam & lomaster
// license GPL-3.0
// // // // // // // // // 

#include <cstddef>
#include <iostream>
#include <chrono>
#include <future>
#include <netdb.h>
#include <sys/stat.h>
#include <thread>
#include <getopt.h>
#include <mutex>
#include <algorithm> 
#include <random>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>

#include "include/bruteforce.h"
#include "include/callbacks.h"
#include "include/files.h"
#include "include/generation.h"
#include "include/networktool.h"
#include "include/other.h"
#include "include/scanner.h"
#include "include/target.h"
#include "include/prints.h"

#define VERSION "2022-05-03v"
#define DELIMITER ','

std::mutex mtx;
checking_finds cfs;
brute_ftp_data bfd_;

// main
void help_menu(void);
void processing_tcp_scan_ports(const std::string& ip, const std::vector<int>& ports, int timeout_ms);
void check_files(const char* path, const char* path1);
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

        std::vector<std::string> hikvision_logins;
        std::vector<std::string> hikvision_passwords;

        const char* path_range;
        const char* path_cidr;
        const char* path_ips;
        const char* path_color_scheme;

        std::string path_ftp_login = "passwd/ftp_logins.txt";
        std::string path_ftp_pass = "passwd/ftp_passwords.txt";

        std::string path_sftp_login = "passwd/sftp_logins.txt";
        std::string path_sftp_pass = "passwd/sftp_passwords.txt";

        std::string path_rtsp_login = "passwd/rtsp_logins.txt";
        std::string path_rtsp_pass = "passwd/rtsp_passwords.txt";

        std::string path_http_login = "passwd/http_logins.txt";
        std::string path_http_pass = "passwd/http_passwords.txt";

        std::string path_hikvision_login = "passwd/hikvision_logins.txt";
        std::string path_hikvision_pass = "passwd/hikvision_passwords.txt";

        int random_ip_count;
        int octets;
        int generate_count;
        int brute_timeout_ms = 10;
        int log_set = 1000;
        int threads_temp;
        int dns_scan_domain_count = 5;
        int timeout_ms = 165;
        int _threads = 100;

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
        bool get_response;
        bool html;
        bool color_off;

        bool ftp_brute_log;
        bool sftp_brute_log;
        bool rtsp_brute_log;
        bool http_brute_log;

        bool hikvision_brute_log;

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
        bool off_hikvision_brute;
        bool off_http_brute;

        bool ftp_only;
        bool no_get_path;
        bool get_path_log;
        bool sftp_only;
        bool hikvision_only;
        bool import_color_scheme;
        bool http_only;
        bool fix_get_path;
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
nesca_prints np;

const char* run; // for help menu

int main(int argc, char** argv){
    if (check_ansi_support() != true){
        std::cout << "You terminal don`t support ansi colors!\n";
        np.disable_colors();
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
        {"path-log", no_argument, 0, 53},
        {"import-color", required_argument, 0, 54},
        {"fix-get-path", no_argument, 0, 52},
        {"on-http-response", no_argument, 0, 51},
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
                    else if (what[i] == "all"){
                        argp.ftp_brute_log = true;
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
                   else if (what[i] == "all"){
                       argp.off_ftp_brute = true;
                       argp.off_sftp_brute = true;
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
                   else if (what[i] == "all"){
                       argp.sftp_only = true;
                       argp.ftp_only = true;
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
        }
    }
    if (argp.import_color_scheme){
        np.import_color_scheme(argp.path_color_scheme, np.config_values);
        np.processing_color_scheme(np.config_values);
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
            std::cout << np.main_nesca_out("TT", argp.hosts_test[i], 3, "C", "", code, "") << std::endl;
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
                            std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 3, "P", "", ping+"ms", "") << std::endl;
                        }
                    }
                    else {
                        if (ping_temp == -2){
                            std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 1, "", "", "info check failed!", "") << std::endl;
                        }
                        else if (ping_temp == -3){
                            std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 1, "", "", "connection failed!", "") << std::endl;
                        }

                        std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 1, "P", "", "down", "") << std::endl;
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
                            std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 3, "P", "", ping+"ms", "") << std::endl;
                        }
                    }

                    else {
                        std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 3, "P", "", "down", "") << std::endl;

                        if (ping_temp == -2){
                            std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 1, "", "", "info check failed!", "") << std::endl;
                        }
                        else if (ping_temp == -3){
                            std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 1, "", "", "connection failed!", "") << std::endl;
                        }
                        delay_ms(argp.timeout_ms);
                    }
                }
            }
            else {
                std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 1, "", "", "ping mode not found! Only (0,1) aka (default, live)", "");
           }
        }
        return 0;
    }
    if (argp.generation_test){
        if (argp.generate_ipv4_test){
            for (int i = 1; i <= argp.generate_count; i++){
                std::cout << np.main_nesca_out("TT", generate_ipv4(), 3, "", "", "", "");
            }
        }
        if (argp.generate_ipv6_test){
            for (int i = 1; i <= argp.generate_count; i++){
                std::cout << np.main_nesca_out("TT", generate_ipv6(argp.octets), 3, "", "", "", "");
            }
        }
        return 0;
    }

    if (argp.warning_threads){
        char what;
        std::cout << np.main_nesca_out("WARING", "You set " + std::to_string(argp.threads_temp) +
                                      " threads this can severely overload a weak cpu, are you sure you want to continue? (y,n): ", 1, "", "", "", "");
        std::cin >> what;

        if (what != 'y'){
            return 0;
        }
        else {
            argp._threads = argp.threads_temp;
        }
    }

    checking_default_files();

    std::cout << np.main_nesca_out("OK", "Starting " + std::to_string(argp._threads) + " threads...", 0, "", "", "", "") << std::endl << std::endl;

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
                            std::cout << np.main_nesca_out("BA", result + " FAILED", 3, "", "", "", "") << std::endl;

                        }
                    }
                    else {
                        std::lock_guard<std::mutex> lock(mtx);
                        std::cout << np.main_nesca_out("BA", result, 3, "T", "", get_html_title(result), "") << std::endl;
                    }
                }
            }).detach();
            if (argp.timeout)
                delay_ms(argp.timeout_ms);
        }
        std::getchar();
        std::cout << np.main_nesca_out("NN", "Stoping threads...", 0, "", "", "", "") << std::endl;
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

    argp.hikvision_logins = write_file(argp.path_hikvision_login);
    argp.hikvision_passwords = write_file(argp.path_hikvision_pass);

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
            std::cout << np.main_nesca_out("NB", std::to_string(ip_count) + " out of " + std::to_string(size) + " IPs scanned", 2, "", "", "", "") << std::endl;
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

void check_files(const char* path, const char* path1){
       if (check_file(path)){
            std::cout << np.main_nesca_out("OK", std::string(path) + " (" + std::to_string(get_count_lines(path)) +
                                          ") entries ", 0, "", "", "", "") << std::endl;
       }
       else {
            std::cout << np.main_nesca_out("FAILED", std::string(path) + " (" + std::to_string(get_count_lines(path)) + ") entries ", 2, "", "", "", "") << std::endl;
       }
       if (check_file(path1)){
            std::cout << np.main_nesca_out("OK", std::string(path1) + " (" + std::to_string(get_count_lines(path1)) +
                                          ") entries ", 0, "", "", "", "") << std::endl;
       }
       else {
            std::cout << np.main_nesca_out("FAILED", std::string(path1) + " (" + std::to_string(get_count_lines(path1)) + ") entries ", 2, "", "", "", "") << std::endl;
       }
}
void checking_default_files(void){
    const char* path0 = "ip.txt";

    if (argp.ip_cidr_scan_import){
       if (check_file(argp.path_cidr)){
            if (argp.ip_cidr_scan){
                std::cout << np.main_nesca_out("OK", std::string(argp.path_cidr) + " (" +
                                              std::to_string(get_count_lines(argp.path_cidr)) + ") entries ", 0, "", "", "", "") << std::endl;
            }
            argp.ip_cidr = write_file(argp.path_cidr);  
       }
       else {
            std::cout << np.main_nesca_out("FAILED", std::string(argp.path_cidr) + " (" +
                                          std::to_string(get_count_lines(argp.path_cidr)) + ") entries ", 2, "", "", "", "") << std::endl;
       }
    }

    if (argp.ip_range_scan_import){
        if (check_file(argp.path_range)){
            if (argp.ip_range_scan){
                std::cout << np.main_nesca_out("OK", std::string(argp.path_range) + " (" +
                                              std::to_string(get_count_lines(argp.path_range)) + ") entries ", 0, "", "", "", "") << std::endl;
            }
            argp.ip_range = write_file(argp.path_range);
        }
        else {
            std::cout << np.main_nesca_out("FAILED", std::string(argp.path_range) + " (" +
                                          std::to_string(get_count_lines(argp.path_range)) + ") entries ", 2, "", "", "", "") << std::endl;
        }
    }

    if (argp.ip_scan_import){
       if (check_file(argp.path_ips)){
            std::cout << np.main_nesca_out("OK", std::string(argp.path_ips) + " (" + std::to_string(get_count_lines(argp.path_ips)) +
                                          ") entries ", 0, "", "", "", "") << std::endl;
            argp._ip = write_file(argp.path_ips);  
       }
       else {
            std::cout << np.main_nesca_out("FAILED", std::string(argp.path_ips) + " (" + std::to_string(get_count_lines(argp.path_ips)) + ") entries ", 2, "", "", "", "") << std::endl;
       }
    }

    check_files(argp.path_ftp_login.c_str(), argp.path_ftp_pass.c_str());
    check_files(argp.path_sftp_login.c_str(), argp.path_sftp_pass.c_str());
    check_files(argp.path_http_login.c_str(), argp.path_http_pass.c_str());
    check_files(argp.path_rtsp_login.c_str(), argp.path_rtsp_pass.c_str());
    check_files(argp.path_hikvision_login.c_str(), argp.path_hikvision_pass.c_str());
}

// Welcome to HELL :)
// 
void processing_tcp_scan_ports(const std::string& ip, const std::vector<int>& ports, int timeout_ms){
    for (const auto& port : ports) {
        int result = tcp_scan_port(ip.c_str(), port, timeout_ms);
        
        if (result == 0) {
            std::string result = ip + ":" + std::to_string(port);
            std::string brute_temp;
            std::string result_print;

            if (port == 80 || port == 81 || port == 8080 || port == 8081 || port == 8888 || port == 8008){

                if (argp.ping_off != true){
                    double temp_ping = measure_ping_time(ip.c_str(), port);

                    if (temp_ping == -1 || temp_ping == -2){
                        return;
                    }
                }

                bool status_path = false;

                result.insert(0, "http://");
                std::string code = send_http_request(ip);
                std::string headers = get_headers("http://" + ip);
                std::string redirect;
                std::string default_result = "http://" + ip + ":" + std::to_string(port) + "/";

                if (argp.no_get_path != true){

                    if (argp.get_path_log){
                        std::cout << np.main_nesca_out("LOG", "1 method: parse_location", 2, "", "", "", "") << std::endl;
                    }
                    // getting method 1 location
                    std::string path_location = parse_location(headers);
                    if (path_location.length() > 1){
                        status_path = true;
                        if (argp.fix_get_path){
                            status_path = true;
                            redirect = path_location;
                        }
                        else {
                            std::string paste_;
                            size_t finding0 = path_location.find("http://");
                            size_t finding1 = path_location.find("https://");
                            size_t finding2 = path_location.find(":" + std::to_string(port));
    
                            if (finding1 != std::string::npos || finding0 != std::string::npos){
                                if (finding2 == std::string::npos){
                                    redirect = path_location;
                                }
                            }
                            else {
                                if (path_location[0] != '/'){
                                    paste_ = "http://" + ip + ":" + std::to_string(port) + "/" + path_location;
                                }
                                else {
                                    paste_ = "http://" + ip + ":" + std::to_string(port) + path_location;
                                }
                                redirect.insert(0, paste_);
                                redirect = paste_;
                            }
                        }
                    }
                    else {
                        status_path = false;
                    }

                    if (status_path != true) {
                        if (argp.get_path_log){
                            std::cout << np.main_nesca_out("LOG", "2 method: parse_http_equiv", 2, "", "", "", "") << std::endl;
                        }
                        std::string path_http = parse_content_from_meta("http://" + code);
                        if (path_http.length() > 1){
                            if (argp.fix_get_path){
                                status_path = true;
                                redirect = path_http;
                            }
                            else {
                                status_path = true;
                                std::string paste_;

                                size_t finding0 = path_http.find("http://");
                                size_t finding1 = path_http.find("https://");
                                size_t finding2 = path_http.find(":" + std::to_string(port));

                                if (finding1 != std::string::npos || finding0 != std::string::npos){
                                    if (finding2 == std::string::npos){
                                        redirect = path_http;
                                    }
                                }
                                else {
                                    if (path_http[0] != '/'){
                                        paste_ = "http://" + ip + ":" + std::to_string(port) + "/" + path_http;
                                    }
                                    else {
                                        paste_ = "http://" + ip + ":" + std::to_string(port) + path_http;
                                    }
                                    redirect.insert(0, paste_);
                                    redirect = paste_;
                                }
                            }
                        }
                        else {
                            status_path = false;
                        }
                    }
                    if (status_path != true){
                        // getting method 3 from js
                        if (argp.get_path_log){
                            std::cout << np.main_nesca_out("LOG", "3 method: parse_window.location.href", 2, "", "", "", "") << std::endl;
                        }
                        std::string path_js = parse_url_from_js(code);
                        if (path_js.length() > 3){
                            if (argp.fix_get_path){
                                status_path = true;
                                redirect = path_js;
                            }
                            else {
                                status_path = true;

                                std::string paste_;

                                // clean redirect    
                                size_t finding0 = path_js.find("http://");
                                size_t finding1 = path_js.find("https://");
                                size_t finding2 = path_js.find(":" + std::to_string(port));

                                if (finding1 != std::string::npos || finding0 != std::string::npos){
                                    if (finding2 == std::string::npos){
                                        redirect = path_js;
                                    }
                                }
                                else {
                                    if (path_js[0] != '/'){
                                        paste_ = "http://" + ip + ":" + std::to_string(port) + "/" + path_js;
                                    }
                                    else {
                                        paste_ = "http://" + ip + ":" + std::to_string(port) + path_js;
                                    }
                                    redirect.insert(0, paste_);
                                    redirect = paste_;
                                }
                            }
                        }
                        else {
                            status_path = false;
                        }
                    }
                    if (status_path != true){
                        // getting method 4 from content location
                        if (argp.get_path_log){
                            std::cout << np.main_nesca_out("LOG", "3 method: parse_content_location", 2, "", "", "", "") << std::endl;
                        }
                        std::string path_content_location = parse_content_location(headers);
                        if (path_content_location.length() > 1){
                                if (argp.fix_get_path){
                                    status_path = true;
                                    redirect = path_content_location;
                                }
                                else {
                                status_path = true;
                                std::string paste_;
                                size_t finding0 = path_content_location.find("http://");
                                size_t finding1 = path_content_location.find("https://");
                                size_t finding2 = path_content_location.find(":" + std::to_string(port));

                                if (finding1 != std::string::npos || finding0 != std::string::npos){
                                    if (finding2 == std::string::npos){
                                        redirect = path_content_location;
                                    }
                                }
                                else {
                                    if (path_content_location[0] != '/'){
                                        paste_ = "http://" + ip + ":" + std::to_string(port) + "/" + path_content_location;
                                    }
                                    else {
                                        paste_ = "http://" + ip + ":" + std::to_string(port) + path_content_location;
                                    }
                                    redirect.insert(0, paste_);
                                    redirect = paste_;
                                }
                            }
                        }
                        else {
                            status_path = false;
                        }
                    }
                }
              
                std::string dns;

                // brute http axis
                std::lock_guard<std::mutex> guard(mtx);
                std::string temp_check_axis = cfs.check_axis_camera(redirect);
                if (argp.off_http_brute != true && temp_check_axis != "no" && argp.no_get_path != true){
                    std::cout <<  np.main_nesca_out("AXIS", ip + " [BRUTEFORCE]", 2, "", "", "", "") << std::endl;

                    brute_temp = threads_brute_http(redirect, argp.http_logins, argp.http_passwords,
                             argp.http_brute_log, argp.http_brute_verbose, argp.brute_timeout_ms);

                }
                if (argp.http_only){
                    if (brute_temp.length() > 1){
                        result_print = np.main_nesca_out("HTTP", "http://" + brute_temp + ip + ":" + std::to_string(port), 3, "T", "", get_html_title(ip), "");
                    }
                }
                else {
                   result_print = np.main_nesca_out("HTTP", "http://" + brute_temp + ip + ":" + std::to_string(port), 3, "T", "", get_html_title(ip), "");
                }

                std::cout << result_print << std::endl;

                // print paths
                if (argp.no_get_path != true && redirect.length() != default_result.length()){
                    std::string redirect_result =  np.main_nesca_out("^", "Redirect to: " + redirect, 2, "", "", "", "");
                    std::string redirect_result_txt =  np.main_nesca_out("^", "Redirect to: " + redirect, 31, "", "", "", "");
                    if (argp.fix_get_path){
                            if (redirect.length() != 0){
                                std::cout << redirect_result << std::endl;
                            }
                    }
                    else {
                        if (redirect.length() != default_result.length()){
                            if (redirect.length() != 0){
                                std::cout << redirect_result << std::endl;
                            }
                        }
                    }
                }

                // print response
                if (argp.get_response){
                    std::string result_code =  np.main_nesca_out("TT", code, 2, "", "", "", "");
                    std::cout << result_code << std::endl;
                }
            }
            else if (port == 20 || port == 21){
                std::lock_guard<std::mutex> guard(mtx);

                if (argp.off_ftp_brute != true){
                    std::cout <<  np.main_nesca_out("FTP", ip + " [BRUTEFORCE]", 2, "", "", "", "") << std::endl;

                    brute_temp = threads_brute_ftp(ip, argp.ftp_logins, argp.ftp_passwords, argp.ftp_brute_log, argp.ftp_brute_verbose, argp.brute_timeout_ms);

                    if (argp.ftp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("FTP", "ftp://" + brute_temp + result, 3, "D", "", get_ftp_response_code(ip, std::to_string(port), bfd_.get_success_login(), bfd_.get_success_pass()), "");
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("FTP", "ftp://" + brute_temp + result, 3, "D", "", get_ftp_response_code(ip, std::to_string(port), bfd_.get_success_login(), bfd_.get_success_pass()), "");
                    }
                }
                else {
                    result_print = np.main_nesca_out("FTP", "ftp://" + brute_temp + result, 3, "D", "", get_ftp_response_code(ip, std::to_string(port), bfd_.get_success_login(), bfd_.get_success_pass()), "");
                }
                
                std::cout << result_print << std::endl;

            }
            else if (port == 22){
                std::lock_guard<std::mutex> guard(mtx);

                if (argp.off_sftp_brute != true){
                    std::cout <<  np.main_nesca_out("SFTP", ip + " [BRUTEFORCE]", 2, "", "", "", "") << std::endl;

                    brute_temp = threads_brute_ssh(ip, argp.sftp_logins, argp.sftp_passwords, argp.sftp_brute_log, argp.sftp_brute_verbose,
                                                  argp.sftp_using_know_hosts, argp.brute_timeout_ms);

                    if (argp.sftp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("SFTP", "sftp://" + brute_temp + result, 3, "", "", "", "");
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("SFTP", "sftp://" + brute_temp + result, 3, "", "", "", "");
                    }
                }
                else {
                    result_print = np.main_nesca_out("SFTP", "sftp://" + result, 3, "", "", "", "");
                }

                std::cout << result_print << std::endl;
            }
            else if (port == 554){
                std::lock_guard<std::mutex> guard(mtx);
                std::string path_yes = "";

                if (argp.off_rtsp_brute != true){

                    std::vector<std::string> rtsp_paths = {"/Streaming/Channels/101", "/h264/ch01/main/av_stream", 
                                                          "/cam/realmonitor?channel=1&subtype=0","/live/main",
                                                           "/av0_0", "/mpeg4/ch01/main/av_stream"};

                    std::cout <<  np.main_nesca_out("RTSP", ip + " [BRUTEFORCE]", 2, "", "", "", "") << std::endl;

                    for (auto& path : rtsp_paths){
                        brute_temp = threads_brute_rtsp(ip+path, argp.rtsp_logins, argp.rtsp_passwords, argp.rtsp_brute_log, argp.rtsp_brute_verbose,
                                                   argp.brute_timeout_ms);
                        if (brute_temp.length() > 1){
                            path_yes = path;
                        }
                    }

                    if (argp.rtsp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("RTSP", "rtsp://" + brute_temp + result + path_yes, 3, "", "", "", "");
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("RTSP", "rtsp://" + brute_temp + result + path_yes, 3, "", "", "", "");
                    }
                }
                else {
                    result_print = np.main_nesca_out("RTSP", "rtsp://" + result, 3, "", "", "", "");
                }

                std::cout << result_print << std::endl;
            }
            else if (port == 8000){
                std::lock_guard<std::mutex> guard(mtx);

                if (argp.off_sftp_brute != true){
                    std::cout <<  np.main_nesca_out("HIKVISION", ip + " [BRUTEFORCE]", 2, "", "", "", "") << std::endl;

                    brute_temp = threads_brute_hikvision(ip, argp.sftp_logins, argp.sftp_passwords, argp.sftp_brute_log,
                                                  argp.brute_timeout_ms);

                    if (argp.hikvision_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("HIKVISION", "" + brute_temp + result, 3, "", "", "", "");
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("HIKVISION", "" + brute_temp + result, 3, "", "", "", "");
                    }
                }
                else {
                    result_print = np.main_nesca_out("HIKVISION", "" + result, 3, "", "", "", "");
                }

                std::cout << result_print << std::endl;
            }
            else{
                std::string result = ip + ":" + std::to_string(port);
                std::string result_print = np.main_nesca_out("BA", result, 3, "", "", "", "");
                
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            }
        }
        else if (result == -1 || result == -2 || result == -3){
            if (argp.print_errors){
                std::string result_print = np.main_nesca_out("NB", ip, 3, "ERROR", "", std::to_string(result), "");
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            }
        }
        else if (result == 1) {
            if (argp.debug){
                std::string result_print = np.main_nesca_out("DB", ip, 3, "CLOSED", "", std::to_string(port), "");
                std::string result_txt = np.main_nesca_out("DB", ip, 31, "CLOSED", "", std::to_string(port), "");
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            }
        }
        else if (result == 2){
            if (argp.debug){
                std::string result_print = np.main_nesca_out("DB", ip, 3, "FILTER", "", std::to_string(port), "");
                std::string result_txt = np.main_nesca_out("DB", ip, 31, "FILTER", "", std::to_string(port), "");
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            }
        }
    }
}
// You live?

void help_menu(void){
    np.golder_rod_on();
    std::cout << "usage: " << run << " [flags]\n";
    np.reset_colors();

    np.sea_green_on();
    std::cout << "\narguments target:" << std::endl;
    np.reset_colors();
    std::cout << "  -ip <1,2,3>            Set ip target.\n";
    std::cout << "  -cidr <1,2,3>          Set cidr target.\n";
    std::cout << "  -range <1,2,3>         Set range target.\n";
    std::cout << "  -import-ip <path>      Set ips on target from file.\n";
    std::cout << "  -import-cidr <path>    Set cidr on target from file.\n";
    std::cout << "  -import-range <path>   Set range on target from file.\n";
    std::cout << "  -random-ip <count>     Set random ips target.\n";

    np.sea_green_on();
    std::cout << "\narguments ports:" << std::endl;
    np.reset_colors();
    std::cout << "  -ports, -p <1,2,3>     Set ports on scan.\n";
    std::cout << "     - example ports:    all, nesca, top100, top50\n";

    np.sea_green_on();
    std::cout << "\narguments speed:" << std::endl;
    np.reset_colors();
    std::cout << "  -threads, -T <count>   Set threads for scan.\n";
    std::cout << "  -timeout, -t <ms>      Set timeout for scan.\n";

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
    std::cout << "  -tcp-ping <mode>       Get response time from host, modes (live) or (default).\n";

    np.sea_green_on();
    std::cout << "\narguments generation:" << std::endl;
    np.reset_colors();
    std::cout << "  -gen-count <count>     Set count for generation.\n";
    std::cout << "  -gen-ipv6 <octets>     Generate ip version 6.\n";
    std::cout << "  -gen-ipv4              Generate ip version 4.\n";
}
