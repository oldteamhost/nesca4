// NESCA4
// by oldteam & lomaster
// license GPL-3.0
// // // // // // // // // 
#include <iostream>
#include <chrono>
#include <future>
#include <thread>
#include <iomanip>
#include <getopt.h>
#include <mutex>
#include <algorithm> 
#include <random>
#include <string>
#include <future>
#include <sstream>
#include <vector>
#include <string.h>

#include "../include/bruteforce.h"
#include "../include/callbacks.h"
#include "../include/files.h"
#include "../include/generation.h"
#include "../include/networktool.h"
#include "../include/other.h"
#include "../include/scanner.h"
#include "../include/target.h"
#include "../include/prints.h"
#include "../include/synscan.h"
#include "../include/nescaping.h"
#include "../include/netutils.h"
#include "../include/services.h"

#include "../modules/include/requests.h"
#include "../modules/include/title.h"
#include "../modules/include/redirect.h"
#include "../modules/include/ftpinfo.h"

#define VERSION "2023-05-25v"
#define DELIMITER ','

std::mutex mtx;
checking_finds cfs;
brute_ftp_data bfd_;
icmp_ping ipn;
udp_ping up;
udp_ping udpp;
syn_scan ss;
ip_utils _iu;
dns_utils dus;
services_nesca sn;

// main
void 
help_menu(void);
void 
processing_tcp_scan_ports(const std::string& ip, const std::vector<int>& ports, int timeout_ms);
void 
check_files(const char* path, const char* path1);
void 
checking_default_files(void);
void 
parse_args(int argc, char** argv);
void
pre_check();

class arguments_program{
    public:
        int fuck_yeah = 0;
        int scanning_count = 3;
        std::string ports_temp;
        std::string domain_1level;
        std::vector<std::string> hosts_test;
        std::string txt_save;
        std::string tcp_ping_mode;
        std::string dns_dictionary = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

        std::vector<std::string> _ip;
        std::vector<std::string> ip_cidr;
        std::vector<std::string> ip_range;
        std::vector<std::string> dns;

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
        int timeout_ms = 100;
        int _threads = 100;
        int connection_timeout_sec;
        int recv_timeout_sec;

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
        bool syn_debug;

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
        bool display_response_time;

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
        bool get_redirect;
        bool thread_on_port;
        bool response_code_test;
        bool tcp_ping_test;
        bool http_request;
        bool generate_ipv4_test;
        bool generate_ipv6_test;
};
arguments_program argp;
nesca_prints np;

const struct option long_options[] = {
        {"threads", required_argument, 0, 'T'},
        {"timeout", required_argument, 0, 't'},
        {"import-ip", required_argument, 0, 23},
        {"import-cidr", required_argument, 0, 3},
        {"import-range", required_argument, 0, 32},
        {"random-ip", required_argument, 0, 5},
        {"brute-login", required_argument, 0, 12},
        {"brute-pass", required_argument, 0, 11},
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
        {"debug", no_argument, 0, 27},
        {"on-get-dns", no_argument, 0, 8},
        {"er", no_argument, 0, 28},
        {"no-get-path", no_argument, 0, 50},
        {"path-log", no_argument, 0, 53},
        {"import-color", required_argument, 0, 54},
        {"scan-count", required_argument, 0, 1},
        {"fix-get-path", no_argument, 0, 52},
        {"on-http-response", no_argument, 0, 51},
        {"no-ping", no_argument, 0, 29},
        {"no-color", no_argument, 0, 26},
        {"log-set", required_argument, 0, 24},
        {"syn-db", no_argument, 0, 59},
        {"syn-debug", no_argument, 0, 60},
        {"sss-timeout", required_argument, 0, 57},
        {"ssr-timeout", required_argument, 0, 58},
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
        {"icmp-rtimeout", required_argument, 0, 43},
        {"icmp-packs", required_argument, 0, 41},
        {0,0,0,0}
    };
const char* short_options = "hvt:T:p:";

const char* run; // for help menu

void
pre_check(){
    if (check_ansi_support() != true){
        std::cout << "You terminal don`t support ansi colors!\n";
        std::cout << "Colors disable!\n";
        np.disable_colors();
    }

    if (argp.print_help_menu){
        help_menu();
        exit(0);
    }

    if (argp.syn_debug){
        ss.debug = true;
    }

    if (!check_root_perms()){
        np.nlog_error("SYN scan only sudo run!\n");
        exit(1);
    }

    if (argp.import_color_scheme){
        np.import_color_scheme(argp.path_color_scheme, np.config_values);
        np.processing_color_scheme(np.config_values);
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
    ipn.source_ip = _iu.get_local_ip();

}

int main(int argc, char** argv){
    sn.init_services();
    logo();
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

    /*Режим тестирования кое как работает.*/
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
                    // get headers
                    std::string headers = (host), code = send_http_request(host, 80), redirect = "N/A";
                    np.nlog_custom("LOG", "1 method: parse_location\n", 2);
                    std::string html = send_http_request(host, 80);

                    redirect = parse_redirect(html, headers, host, true, 80);

                    std::cout << np.main_nesca_out("TT", host, 3, "R", "", redirect, "") << std::endl;
            }
        }

        // Пинг
        if (argp.tcp_ping_test){
            long double ping_time_temp;
            double ping_temp;
            if (argp.tcp_ping_mode == "live" || argp.tcp_ping_mode == "1"){
                for (;;){
                    ping_temp = ipn.ping(argp.hosts_test[0].c_str(), &ping_time_temp);
                    
                    if (ping_temp != -1){
                        std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 3,
                                "rtt", "", std::to_string(ping_time_temp)+"ms", "") << std::endl;
                    }
                    else {
                        std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 3,
                                "rtt", "", "down", "") << std::endl;
                    }
                    delay_ms(argp.timeout_ms);
                }
            }
            else if (argp.tcp_ping_mode == "default" || argp.tcp_ping_mode == "0") {
                for (auto& host : argp.hosts_test){
                    ping_temp = ipn.ping(host.c_str(), &ping_time_temp);

                    if (ping_temp != -1){
                        std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 3,
                                "rtt", "", std::to_string(ping_time_temp)+"ms", "") << std::endl;
                    }
                    else {
                        std::cout << np.main_nesca_out("TT", argp.hosts_test[0], 3,
                                "rtt", "", "down", "") << std::endl;

                        // Delay
                        delay_ms(argp.timeout_ms);
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
    np.nlog_trivial("Starting " + std::to_string(argp._threads) + " threads...\n\n");

    /*Начало DNS сканирования.*/
    if (argp.dns_scan){
        argp.timeout_ms = 100;
        std::mutex mtx;
        for (int i = 0; i < argp._threads; i++) {

            std::thread([&](){
                for (;;) {
                    std::string random_ = generate_random_str(argp.dns_scan_domain_count, argp.dns_dictionary);
                    std::string result = "http://" + random_ + argp.domain_1level;
                    std::string ip = dus.get_ip_by_dns(result.c_str());
                    std::string html = send_http_request(ip, 80);

                    std::string result_print;
                    int test = dns_scan("http://" + random_, argp.domain_1level);
                    if (test == 0) {
                        if (argp.debug) {
                            std::lock_guard<std::mutex> lock(mtx);
                            np.nlog_custom("BA", result + " [FaILEd]\n",2);
                        }
                    }
                    else {
                        std::lock_guard<std::mutex> lock(mtx);
                        std::cout << np.main_nesca_out("BA", result, 3, "T", "", get_http_title(html), "") << std::endl;
                    }
                }
            }).detach();

            if (argp.timeout){
                delay_ms(argp.timeout_ms);
            }
        }
        std::getchar();
        std::cout << np.main_nesca_out("NN", "Stoping threads...", 0, "", "", "", "") << std::endl;
    }

    /*Загрузка логинов и паролей.*/
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

    /*Начало сканирования*/
    ss.source_ip = _iu.get_local_ip();
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
    std::vector<std::future<void>> futures;

    long long ip_count = 0;
    long long size = result.size();

    for (const auto& ip : result) {
        futures.emplace_back(std::async(std::launch::async, processing_tcp_scan_ports, ip, argp.ports, argp.timeout_ms));
        ip_count++;

        if (ip_count % argp.log_set == 0){
            np.nlog_custom("LOG", std::to_string(ip_count) + " out of " + std::to_string(size) + " IPs scanned\n", 1);
        }

        if (ip_count % argp._threads == 0) {
            for (auto& f : futures) {
                f.get();
            }
            futures.clear();
        }
    }
    for (auto& f : futures) {
        f.get();
    }
    if (argp.fuck_yeah < 1){
        np.nlog_custom("NB", "If you are sure that at least something there is open, then try increasing the timeout, or reduce the number of threads.\n", 1);
    }
    /*Конец*/

    return 0;
}

void check_files(const char* path, const char* path1){
       if (check_file(path)){
            np.nlog_trivial(std::string(path) + " (" + std::to_string(get_count_lines(path)) + ") entries\n");
       }
       else {
            np.nlog_error(std::string(path) + " (" + std::to_string(get_count_lines(path)) + ") entries\n");
       }
       if (check_file(path1)){
            np.nlog_trivial(std::string(path1) + " (" + std::to_string(get_count_lines(path1)) + ") entries\n");
       }
       else {
            np.nlog_error(std::string(path1) + " (" + std::to_string(get_count_lines(path1)) + ") entries\n");
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
       }
    }

    check_files(argp.path_ftp_login.c_str(), argp.path_ftp_pass.c_str());
    check_files(argp.path_sftp_login.c_str(), argp.path_sftp_pass.c_str());
    check_files(argp.path_http_login.c_str(), argp.path_http_pass.c_str());
    check_files(argp.path_rtsp_login.c_str(), argp.path_rtsp_pass.c_str());
    check_files(argp.path_hikvision_login.c_str(), argp.path_hikvision_pass.c_str());
}

// Welcome to HELL :)
// > Я сам не понимаю что тут написано, но работает правильно.
void 
processing_tcp_scan_ports(const std::string& ip, const std::vector<int>& ports, int timeout_ms){
    int flag = 0;
    int yeah_flag = 0;
    for (int i = 0; i < argp.scanning_count; i++){
        if (yeah_flag == 1){
            break;
        }

        for (const auto& port : ports) {
        int result = ss.syn_scan_port(ip.c_str(), port, timeout_ms);

        long double time_ms;
        int temp_ping = ipn.ping(ip.c_str(), &time_ms);
        if (argp.ping_off != true && flag < 1){
            if (argp.display_response_time && time_ms > 0){
                std:: cout << np.main_nesca_out("PING", ip , 3,
                "rtt", "", std::to_string(time_ms)+"ms", "") << std::endl;
            }
            if (temp_ping != 0){
                return;
            }
            flag++;
        }

        if (result == 0) {
            yeah_flag = 1;
            argp.fuck_yeah++;
            std::string result = ip + ":" + std::to_string(port);
            std::string brute_temp;
            std::string result_print;
     
            if (port == 80 || port == 81 || port == 8080 || port == 8081 || port == 8888 || port == 8008){
                std::lock_guard<std::mutex> guard(mtx);
                bool status_path = false;

                // Add protocol
                result.insert(0, "http://");

                std::string redirect;

                // for check length
                std::string default_result = "http://" + ip + ":" + std::to_string(port) + "/";

                // get page code
                std::string html = send_http_request(ip, port);

                // get redirect
                if (argp.no_get_path != true){
                    if (argp.fix_get_path){
                        redirect = parse_redirect(html, html, ip,false, port);
                    }
                    else {
                        redirect = parse_redirect(html, html, ip,true, port);
                    }
                }

                // brute http axis
                std::string temp_check_axis = cfs.check_axis_camera(redirect); // check axis redirect
                if (argp.off_http_brute != true && temp_check_axis != "no" && argp.no_get_path != true){
                    np.nlog_custom("AXIS", ip + " [BRUTEFORCE]\n",1);
                    brute_temp = threads_brute_http(redirect, argp.http_logins, argp.http_passwords,
                             argp.http_brute_log, argp.http_brute_verbose, argp.brute_timeout_ms);
                }

                // get redirect
                std::string http_title_result = get_http_title(html);

                // clear answer
                http_title_result.erase(std::remove(http_title_result.begin(), http_title_result.end(), '\r'), http_title_result.end());
                http_title_result.erase(std::remove(http_title_result.begin(), http_title_result.end(), '\n'), http_title_result.end());
                
                // print only success brute result
                if (argp.http_only){
                    if (brute_temp.length() > 1){
                        result_print = np.main_nesca_out("HTTP", "http://" + brute_temp + ip + ":" + std::to_string(port), 3, "T", "", http_title_result, "");
                    }
                }
                else {
                    if (argp.no_get_dns != true){
                        result_print = np.main_nesca_out("HTTP", "http://" + brute_temp + ip + ":" + std::to_string(port), 3, "T", "", http_title_result, "");
                    }
                    else {
                        result_print = np.main_nesca_out("HTTP", "http://" + brute_temp + ip + ":" + std::to_string(port), 3, "T", "DNS", http_title_result, get_dns_ip(ip.c_str()));
                    }
                }

                // print
                std::cout << result_print << std::endl;

                // GOTO print redirect
                if (argp.no_get_path != true && redirect.length() != default_result.length()){
                    if (argp.fix_get_path){
                            if (redirect.length() != 0){
                                np.nlog_custom("^", "Redirect to: " + redirect + "\n",1);
                            }
                    }
                    else {
                        if (redirect.length() != default_result.length()){
                            if (redirect.length() != 0){
                                np.nlog_custom("^", "Redirect to: " + redirect + "\n",1);
                            }
                        }
                    }
                }

                // print response
                if (argp.get_response){
                    std::string result_code =  np.main_nesca_out("TT", html, 2, "", "", "", "");
                    std::cout << result_code << std::endl;
                }
            }
            else if (port == 20 || port == 21){
                std::lock_guard<std::mutex> guard(mtx);

                if (argp.off_ftp_brute != true){
                    np.nlog_custom("FTP", ip + " [BRUTEFORCE]\n",1);

                    brute_temp = threads_brute_ftp(ip, argp.ftp_logins, argp.ftp_passwords, argp.ftp_brute_log,
                            argp.ftp_brute_verbose, argp.brute_timeout_ms);

                    if (argp.ftp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("FTP", "ftp://" + brute_temp + result, 3, "D", "",
                                    get_ftp_description(ip, std::to_string(port),
                                    bfd_.get_success_login(), bfd_.get_success_pass()), "");
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("FTP", "ftp://" + brute_temp + result, 3, "D", "",
                                get_ftp_description(ip, std::to_string(port),
                                bfd_.get_success_login(), bfd_.get_success_pass()), "");
                    }
                }
                else {
                    result_print = np.main_nesca_out("FTP", "ftp://" + brute_temp + result, 3, "D", "",
                            get_ftp_description(ip, std::to_string(port),
                            bfd_.get_success_login(), bfd_.get_success_pass()), "");
                }
                
                std::cout << result_print << std::endl;

            }
            else if (port == 22){
                std::lock_guard<std::mutex> guard(mtx);

                if (argp.off_sftp_brute != true){
                    np.nlog_custom("SFTP", ip + " [BRUTEFORCE]\n",1);

                    brute_temp = threads_brute_ssh(ip, argp.sftp_logins, argp.sftp_passwords, argp.sftp_brute_log,
                        argp.sftp_brute_verbose, argp.sftp_using_know_hosts, argp.brute_timeout_ms);

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

                    np.nlog_custom("RTSP", ip + " [BRUTEFORCE]\n",1);

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

                if (argp.off_hikvision_brute != true){
                    np.nlog_custom("HIKVISION", ip + " [BRUTEFORCE]\n",1);

                    brute_temp = threads_brute_hikvision(ip, argp.hikvision_logins, argp.hikvision_passwords, argp.hikvision_brute_log,
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
            else if (port == 25){
                std::string result_print = np.main_nesca_out("SMTP", result, 3, "", "", "", "");
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            }
            else if (port == 53){
                std::string result_print = np.main_nesca_out("DNS", result, 3, "", "", "", "");
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            }
            else if (port == 143){
                std::string result_print = np.main_nesca_out("IMAP", result, 3, "", "", "", "");
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            }
            else if (port == 443){
                std::string result_print = np.main_nesca_out("HTTPS", "https://" + result, 3, "", "", "", "");
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            }
            else{
                std::string result_print = np.main_nesca_out(sn.probe_service(port), result, 3, "", "", "", "");
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
        else if (result == 2){
            if (argp.debug){
                std::string result_print = np.main_nesca_out("DB", ip, 3, "FILTER", "", std::to_string(port), "");
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            }
        }
        else if (result == 1) {
            if (argp.debug){
                std::string result_print = np.main_nesca_out("DB", ip, 3, "CLOSED", "", std::to_string(port), "");
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            }
        }
   }
    }
}
// You live?

void 
help_menu(void){
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
    std::cout << "\narguments syn_scan:" << std::endl;
    np.reset_colors();
    std::cout << "  -ports, -p <1,2,3>     Set ports on scan.\n";
    std::cout << "     - example ports:    all, nesca, top100, top50\n";
    std::cout << "  -sss-timeout           Set timeout for send packet on port.\n";
    std::cout << "  -ssr-timeout           Set timeout for getting packet on port.\n";
    std::cout << "  -syn-db, syn-debug     Display verbose info for syn port scan.\n";

    np.sea_green_on();
    std::cout << "\narguments ping:" << std::endl;
    np.reset_colors();
    std::cout << "  -icmp-timeout <ms>     Set timeout for icmp ping.\n";
    std::cout << "  -icmp-rtimeout <ms>    Set timeout for send icmp packet.\n";
    std::cout << "  -icmp-packs <count>    Set count icmp packets for send.\n";
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
                std::cout << VERSION << std::endl;
                return;
                break;
            case 'p':
            {
                argp.ports_temp = optarg;
                argp.ports = write_ports(argp.ports_temp);
                if (argp.ports[0] == -1){
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
            case 1:
                argp.scanning_count = atoi(optarg);
                break;
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
           case 41:
               ipn.packets = atoi(optarg);
               break;
           case 43:
               ipn.recv_timeout = atoi(optarg);
               break;
           case 49:
               ipn.ping_timeout = atoi(optarg);
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
           case 56:
               argp.http_request = true;
               break;
           case 57:
               argp.recv_timeout_sec = atoi(optarg);
               break;
           case 58:
               argp.connection_timeout_sec = atoi(optarg);
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
        }
    }
}
