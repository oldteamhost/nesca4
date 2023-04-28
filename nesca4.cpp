// NESCA4
// by oldteam & lomaster
// license GPL-3.0
// // // // // // // // // 

#include <cstdio>
#include <iostream>
#include <bitset>
#include <getopt.h>
#include <netdb.h>
#include <ostream>
#include <mutex>
#include <thread>
#include <algorithm> 
#include <random>
#include <string>
#include <cstring>
#include <sstream>
#include <string.h>
#include <curl/curl.h>
#include <vector>
#include <fstream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#endif

#define VERSION "1165-build"
#define DELIMITER ','

std::string logo_red = "\033[38;2;255;100;100m";
std::string gray_nesca = "\033[38;2;112;112;112m";
std::string golder_rod = "\033[38;2;218;165;32m";
std::string sea_green = "\033[38;2;60;179;113;4m";
std::string green_html = "\033[38;2;45;235;65m";
std::string red_html = "\033[38;2;240;50;55m";
std::string yellow_html = "\033[38;2;240;215;75m";

std::string reset_color = "\033[0m";

std::mutex mtx;

// main
void help_menu(void);

// curl write
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata);
size_t write_callback_plus(char* buf, size_t size, size_t nmemb, void* up);
size_t write_callback_http(char* ptr, size_t size, size_t nmemb, void* userdata);
size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp);
size_t clear_callback(void *buffer, size_t size, size_t nmemb, void *userp);

// scan
std::string get_dns_ip(const char* ip);
int tcp_scan_port(const char *ip, int port, int timeout_ms);
void processing_tcp_scan_ports(const std::string& ip, const std::vector<int>& ports, int timeout_ms);
int dns_scan(std::string domain, std::string domain_1level);
std::vector<int> tcp_scan_ports(const std::vector<std::string>& ips, const std::vector<int>& ports, int timeout_ms);

// func curg
double measure_ping_time(const char* node, int port);
long get_response_code(const char *node);
std::string get_html_title(std::string node);
std::vector<std::string> brute_ftp(const std::string& ip, const std::vector<std::string>& logins, const std::vector<std::string>& passwords);
void check_net(void);

// files
std::vector<std::string> write_file(const std::string& filename);
int write_line(std::string, std::string line);
bool check_file(const char* path);
int get_count_lines(const char* path);
void checking_default_files(void);

// other
std::string generate_random_str(int len, std::string dictionary);
std::vector<std::string> cidr_to_ips(const std::vector<std::string>& cidr_list);
bool check_ansi_support(void);
void delay_ms(int milliseconds);
void print_logo(void);
const char* get_time();
const char* generate_ipv6(int num_octets);
const char* generate_ipv4(void);

// program
std::vector<int> split_string_int(const std::string& str, char delimiter);
std::vector<std::string> split_string_string(const std::string& str, char delimiter);

class arguments_program{
    public:
        std::string ip_temp;
        std::string ip_range_temp;
        std::string ports_temp;
        std::string domain_1level;
        std::string txt_save;
        std::string dns_dictionary = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

        std::vector<std::string> _ip;
        std::vector<std::string> ip_cidr;
        std::vector<std::string> logins;
        std::vector<std::string> passwords;

        const char* path_cidr;
        const char* path_ips;
        std::vector<int> ports;

        bool random_ip;
        int log_set = 200;
        bool dns_scan;
        bool print_help_menu;
        bool ip_scan;
        bool ip_cidr_scan;
        bool debug;
        bool warning_threads;
        bool txt;
        bool color_off;
        int random_ip_count;
        int threads_temp;
        int dns_scan_domain_count = 5;
        int timeout_ms = 300;
        int _threads = 20;
        bool timeout;
        int random_version = 4;
        bool print_errors;
        bool brute;
};
arguments_program argp;

const char* run;

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

    print_logo();

    run = argv[0];
    const char* short_options = "hvt:T:p:";
    const struct option long_options[] = {

        {"threads", required_argument, 0, 'T'},
        {"timeout", required_argument, 0, 't'},

        {"ip", required_argument, 0, 1},
        {"cidr", required_argument, 0, 2},
        {"import-ip", required_argument, 0, 23},
        {"import-cidr", required_argument, 0, 3},

        {"random-vn", required_argument, 0, 4},
        {"random-ip", required_argument, 0, 5},

        {"ftp-pass", required_argument, 0, 11},
        {"ftp-login", required_argument, 0, 12},
        {"ssh-login", required_argument, 0, 13},
        {"ssh-pass", required_argument, 0, 14},

        {"dns-scan", required_argument, 0, 19},
        {"dns-length", required_argument, 0, 20},
        {"dns-dict", required_argument, 0, 21},
        {"txt", required_argument, 0, 22},
        {"debug", no_argument, 0, 27},
        {"er", no_argument, 0, 28},
        {"no-color", no_argument, 0, 26},
        {"log-set", required_argument, 0, 24},

        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {"ports", no_argument, 0, 'p'},

        {"dns-off", no_argument, 0, 17},
        {"db", no_argument, 0, 7},
        {"error", no_argument, 0, 25},
        {"ftp-brute", no_argument, 0, 9},
        {"ssh-brute", no_argument, 0, 10},
        {"ft", no_argument, 0, 18},
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
                if (argp.ports_temp == "all"){
                    std::vector<int> _ports;

                    for (int i = 0; i < 65536; i++) {
                        _ports.push_back(i);
                    }

                    argp.ports = _ports;
                }
                else if (argp.ports_temp == "top100"){
                    argp.ports = {80, 443, 22, 21, 25, 3389, 110, 143, 53, 445, 139, 3306, 8080, 
                        1723, 111, 995, 993, 5900, 1025, 587, 8888, 199, 1720, 465, 548, 113, 81,
                        6001, 10000, 514, 5060, 179, 1026, 23, 8443, 8000, 444, 1433, 1900, 2001,
                        1027, 49152, 2049, 1028, 1029, 5901, 32768, 1434, 3283, 5800, 389, 53, 17988,
                        106, 5666, 1725, 465, 995, 548, 7, 123, 389, 113, 37, 427, 8001, 427, 1726,
                        49153, 2002, 515, 1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039,
                        1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049, 1050, 1051, 1052,
                        1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061, 1062, 1063, 1064, 1065,
                        1066, 1067, 1068, 1069, 1070, 1071, 1072, 1073, 1074, 1075, 1076, 1077};
                }
                else if (argp.ports_temp == "top50"){
                    argp.ports = {80, 443, 22, 21, 25, 3389, 110, 143, 53, 445, 139, 3306, 8080, 1723,
                        111, 995, 993, 5900, 1025, 587, 8888, 199, 1720, 465, 548, 113, 81, 6001, 10000,
                        514, 5060, 179, 1026, 23, 8443, 8000, 444, 1433, 1900, 2001, 1027, 49152, 2049, 1028, 1029, 5901, 32768, 1434, 3283}; 
                }
                else if (argp.ports_temp == "nesca"){
                    argp.ports = {};
                }
                else {
                    argp.ports = split_string_int(argp.ports_temp, DELIMITER);
                }
                break;
            }
            case 1:
            {
                argp.ip_temp = optarg; argp.ip_scan = true;
                argp._ip = split_string_string(argp.ip_temp, DELIMITER);
                break;
            }
            case 2:
            {
                argp.ip_range_temp = optarg; 
                argp.ip_cidr_scan = true;
                argp.ip_cidr = split_string_string(argp.ip_range_temp, DELIMITER);
                break;
            }
            case 3:
            {
               argp.ip_cidr_scan = true;
               argp.path_cidr = optarg;
               break;
            }
           case 5:
                argp.random_ip = true;
                argp.random_ip_count = atoi(optarg); 
                break;
           case 7:
                argp.debug = true;
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
               argp.ip_scan = true;
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
               yellow_html = ""; break;
           }
           case 27:
               argp.debug = true;
               break;
           case 28:
               argp.print_errors = true;
               break;
        }
    }

    if (argp.print_help_menu){
        help_menu();
        return 0;
    }

    if (argp.warning_threads){
        char what;
        std::cout << red_html;
        std::cout << "[" << get_time() << "]" << "[WARING] You set " << argp.threads_temp << " threads, this can severely overload a weak cpu, are you sure you want to continue? (y,n): ";
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

    argp.logins = write_file("passwd/logins.txt");
    argp.passwords = write_file("passwd/passwords.txt");

    std::cout << green_html;
    std::cout << "[" << get_time() << "]" << "[OK] Starting " << argp._threads << " threads...\n\n";
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
                            std::string result_print_color = gray_nesca + "[" + std::string(get_time()) + "] [BA] " + sea_green + result + reset_color + gray_nesca + " T: " + golder_rod + get_html_title(result) + reset_color;
                            std::string result_txt = "[" + std::string(get_time()) + "] [BA] " + result + " T: " + get_html_title(result);
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
    std::vector<std::string> result;
    
    if (argp.ip_scan){
        result = argp._ip;
    } 
    else if (argp.ip_cidr_scan){
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
            std::string result_print = "[" + std::string(get_time()) + "][NB] " + std::to_string(ip_count) + " out of " + std::to_string(size) + " IPs scanned.";
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

std::vector<std::string>write_file(const std::string& filename){
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

std::string get_dns_ip(const char* ip){
    struct addrinfo hints, *result = nullptr;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status;
#ifdef _WIN32
    WSADATA wsaData;
    if ((status = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
        std::cerr << "WSAStartup failed with error: " << status << std::endl;
        return "";
    }
#endif

    if ((status = getaddrinfo(ip, nullptr, &hints, &result)) != 0) {
        std::cerr << "getaddrinfo failed with error: " << status << std::endl;
#ifdef _WIN32
        WSACleanup();
#endif
        return "";
    }

    char hostname[NI_MAXHOST] = "";
    if ((status = getnameinfo(result->ai_addr, result->ai_addrlen, hostname, NI_MAXHOST, nullptr, 0, 0)) != 0) {
        std::cerr << "getnameinfo failed with error: " << status << std::endl;
        freeaddrinfo(result);
#ifdef _WIN32
        WSACleanup();
#endif
        return "";
    }

    freeaddrinfo(result);

#ifdef _WIN32
    WSACleanup();
#endif

    return hostname;
}

int tcp_scan_port(const char *ip, int port, int timeout_ms){
    int sock;
    struct sockaddr_in target;
    struct timeval timeout;
    fd_set fds;

    #ifdef _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != 0) {
        return -1;
    }
    #endif

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        return -3;
    }

    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr(ip);
    target.sin_port = htons(port);

    int ip_bin = inet_pton(AF_INET, ip, &target.sin_addr);

    if (ip_bin == 0){
        return -2;
    }

    #ifndef _WIN32
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
    #endif

    int ret = connect(sock, (struct sockaddr *)&target, sizeof(target));

    if (ret == 0) {
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
        return 0;
    }

    if (ret < 0 && errno != EINPROGRESS) {
        if (errno == ECONNREFUSED) {
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
            return 2;
        }
    }

    FD_ZERO(&fds);
    FD_SET(sock, &fds);

    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

    if (FD_ISSET(sock, &fds) && timeout.tv_sec <! 0 && timeout.tv_usec <! 0){
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
        return -4;
    }

    ret = select(sock + 1, NULL, &fds, NULL, &timeout);

    if (ret == -1){
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
        return -5;
    }

    if (ret == 0) {  
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
        return 1;
    }

    if (ret < 0) {
        if (errno == EAGAIN) {
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
            return 2;
        }

        if (errno == ECONNREFUSED) {
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
        return 1;

        }
        else {
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
            return -3;
        }

    }

    int err = 0;
    socklen_t len = sizeof(err);
    getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &len);

    if (err == 0 && FD_ISSET(sock, &fds)) {
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
        return 0;
    }

#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
    return 1;
}

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    return size * nmemb;
}

size_t write_callback_plus(char* buf, size_t size, size_t nmemb, void* up){
    size_t realsize = size * nmemb;
    std::string* str = (std::string*) up;
    str->append(buf, realsize);
    return realsize;
}

size_t write_callback_http(char* ptr, size_t size, size_t nmemb, void* userdata){
    ((std::string*)userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp){
    return size * nmemb;
}

size_t clear_callback(void *buffer, size_t size, size_t nmemb, void *userp){
    return size * nmemb;
}

long get_response_code(const char *node){
    CURL *curl = curl_easy_init();

    if (!curl) {
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_URL, node);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, clear_callback);
    CURLcode res = curl_easy_perform(curl);

    long response_code = 0;

    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    }

    else {
        return -1;
    }

    curl_easy_cleanup(curl);
    return response_code;
}

void check_net(void){
   int temp = get_response_code("google.com");

   if (temp == 0){
        printf("ERROR: net connection failed");
        exit(1);
   }
}
double measure_ping_time(const char* node, int port){
    double total_time = 0.0;
    CURL *curl = curl_easy_init();
    if(curl) {
        char node_with_port[256];
        snprintf(node_with_port, 256, "%s:%d", node, port);
        
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_URL, node_with_port);
        
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 60L);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);
        curl_easy_setopt(curl, CURLOPT_ACCEPTTIMEOUT_MS, 500L);
        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 1L);
        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 5L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 3000L);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, curl_callback);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1L);
        curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 300L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        
        CURLcode res = curl_easy_perform(curl);
        if(res == CURLE_OK) {
            res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);
            if(res != CURLE_OK) {
                curl_easy_cleanup(curl);
                return -2;
            }
        } 
        else {
            curl_easy_cleanup(curl);
            return -1;
        }
    }
    curl_easy_cleanup(curl);
    return total_time;
}

int dns_scan(std::string domain, std::string domain_1level){
    std::string result = domain + domain_1level;

     double responce_time = measure_ping_time(result.c_str(), 80);
     if (responce_time != -1){
         if (responce_time != 2){
             if (responce_time != EOF){
                 return 1; // success
             }
         }
     }
     else {
         return 0; // failed
    }

    return -1; // error
}

std::string get_html_title(std::string node){
    CURL* curl = curl_easy_init();

    if (curl == nullptr) {
        return "N/A";
    }

    if (!curl) {
        curl_easy_cleanup(curl);
        return "N/A";
    }

    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_URL, node.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_http);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        return "N/A";
    }

    char* content_type;
    res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type);

    if (res != CURLE_OK || content_type == nullptr) {
        curl_easy_cleanup(curl);
        return "N/A";
    }

    std::string title_tag_open = "<title>";
    std::string title_tag_close = "</title>";

    size_t title_start = response_string.find(title_tag_open);
    if (title_start == std::string::npos) {
        curl_easy_cleanup(curl);
        return "N/A";
    }
    title_start += title_tag_open.length();

    size_t title_end = response_string.find(title_tag_close, title_start);
    if (title_end == std::string::npos) {
        curl_easy_cleanup(curl);
        return "N/A";
    }

    std::string title = response_string.substr(title_start, title_end - title_start);
    std::string return_value = "\"" + title + "\"";
    curl_easy_cleanup(curl);
    return return_value;
}

std::vector<std::string> brute_ftp(const std::string& ip, const std::vector<std::string>& logins, const std::vector<std::string>& passwords){
    std::vector<std::string> result;

    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

        curl_easy_setopt(curl, CURLOPT_USERNAME, "");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "");

    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");

        curl_easy_setopt(curl, CURLOPT_FTPPORT, "-");
        curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 30L);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
        curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, 1L);
        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 1L);
        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 30L);

        std::string url = "ftp://" + ip;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        for (const auto& login : logins) {
            for (const auto& password : passwords) {
                curl_easy_setopt(curl, CURLOPT_USERNAME, login.c_str());
                curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());

                CURLcode res = curl_easy_perform(curl);
                if (res == CURLE_OK) {
                    result.push_back(login + " - " + password);
                    break;
                }
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_easy_cleanup(curl);
    return result;
}

const char* generate_ipv6(int num_octets){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 65535);

    static char ip[40];
    std::stringstream ss;
    for (int i = 0; i < num_octets; i++) {
        ss << std::hex << distrib(gen);
        if (i < num_octets - 1) ss << ":";
    }
    std::string ip_str = ss.str();
    strcpy(ip, ip_str.c_str());
    return ip;
}

const char* generate_ipv4(void){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);

    static char ip[16];
    std::stringstream ss;
    for (int i = 0; i < 4; i++) {
        ss << distrib(gen);
        if (i < 3) ss << ".";
    }
    std::string ip_str = ss.str();
    strcpy(ip, ip_str.c_str());
    return ip;
}

std::string generate_random_str(int len, std::string dictionary){
    std::string result;

    std::random_device rd;
    std::mt19937 engine(rd());

    std::uniform_int_distribution<int> dist(0, dictionary.length() - 1);

    for (int i = 0; i < len; i++) {
        result += dictionary[dist(engine)];
    }

    return result;
}

bool check_file(const char* path){
    std::ifstream file(path);
    return file.good();
}

int get_count_lines(const char* path){
    std::ifstream file(path);
    int count = 0;
    std::string line;

    while (std::getline(file, line)) {
        ++count;
    }

    return count;
}

void checking_default_files(void){
    const char* path0 = "ip.txt";
    const char* path1 = "passwd/logins.txt";
    const char* path2 = "passwd/passwords.txt";

    if (argp.ip_cidr_scan){
       if (check_file(argp.path_cidr)){
            std::cout << green_html;
            if (argp.ip_cidr_scan){
                std::cout << "[" << get_time() << "]" << "[OK] " << argp.path_cidr << " (" << get_count_lines(argp.path_cidr) << ") entries" << std::endl;
            }
            else {
                std::cout << "[" << get_time() << "]" << "[OK] " << argp.path_cidr << " (" << get_count_lines(argp.path_cidr) << ") entries" << std::endl;
            }
            argp.ip_cidr = write_file(argp.path_cidr);  
       }
       else {
            std::cout << yellow_html;
            std::cout << "[" << get_time() << "]" << "[FAILED] " << argp.path_cidr << " (" << get_count_lines(argp.path_cidr) << ") entries" << std::endl;
            std::cout << reset_color;
       }
    }

    if (argp.ip_scan){
       if (check_file(argp.path_ips)){
            std::cout << green_html;
            std::cout << "[" << get_time() << "]" << "[OK] " << argp.path_ips << " (" << get_count_lines(argp.path_ips) << ") entries" << std::endl;
            argp._ip = write_file(argp.path_ips);  
       }
       else {
            std::cout << yellow_html;
            std::cout << "[" << get_time() << "]" << "[FAILED] " << argp.path_ips << " (" << get_count_lines(argp.path_ips) << ") entries" << std::endl;
            std::cout << reset_color;
       }
    }

    if (check_file(path1)){
       std::cout << green_html;
       std::cout << "[" << get_time() << "]" << "[OK] " << path1 << " (" << get_count_lines(path1) << ") entries" << std::endl;
    }
    else {
        std::cout << yellow_html;
        std::cout << "[" << get_time() << "]" << "[FAILED] " << path1 << " (" << get_count_lines(path1) << ") entries" << std::endl;
        std::cout << reset_color;
    }
    if (check_file(path2)){
        std::cout << green_html;
        std::cout << "[" << get_time() << "]" << "[OK] " << path2 << " (" << get_count_lines(path2) << ") entries" << std::endl;
    }
    else {
        std::cout << yellow_html;
        std::cout << "[" << get_time() << "]" << "[FAILED] " << path2 << " (" << get_count_lines(path2) << ") entries" << std::endl;
        std::cout << reset_color;
    }
    std::cout << reset_color;
}

int write_line(std::string path, std::string line){
    std::ofstream outfile;
    outfile.open(path, std::ios_base::app);
    if (!outfile.is_open()){
        return -1;
    }

    outfile << line << std::endl;

    if (outfile.fail()){
         return -2;
    }

    outfile.close();
    if (outfile.fail()){
        return -3;
    }

    return 0;
}

const char* get_time(){
    time_t rawtime;
    struct tm * timeinfo;
    static char time_str[9];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(time_str, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return time_str;
}

void delay_ms(int milliseconds){
#ifdef _WIN32
    Sleep(milliseconds);
#else
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#endif
}

std::vector<std::string> cidr_to_ips(const std::vector<std::string>& cidr_list) {
  std::vector<std::string> ipAddresses;

  for (const std::string& cidr : cidr_list) {
    std::string networkAddress = cidr.substr(0, cidr.find('/'));
    int subnetMaskBits = std::stoi(cidr.substr(cidr.find('/') + 1));
    
    std::vector<unsigned long long int> octets;
    std::string octetString;
    std::stringstream networkAddressStream(networkAddress);

    while (std::getline(networkAddressStream, octetString, '.')) {
      octets.push_back(std::strtoull(octetString.c_str(), nullptr, 10));
    }
    
    unsigned long long int ipAddress = 0;

    for (auto octet : octets) {
      ipAddress = (ipAddress << 8) | octet;
    }

    std::bitset<32> subnetMask((0xFFFFFFFFUL << (32 - subnetMaskBits)) & 0xFFFFFFFFUL);
    ipAddress &= subnetMask.to_ulong();

    for (unsigned long long int i = 0; i < (1ULL << (32 - subnetMaskBits)); i++) {
      std::stringstream ipAddressStream;
      ipAddressStream << ((ipAddress >> 24) & 0xFF) << '.' << ((ipAddress >> 16) & 0xFF) << '.' << ((ipAddress >> 8) & 0xFF) << '.' << (ipAddress & 0xFF);
      ipAddresses.push_back(ipAddressStream.str());
      ipAddress++;
    }
  }

  return ipAddresses;
}

std::vector<int> split_string_int(const std::string& str, char delimiter){
    std::vector<int> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        result.push_back(std::stoi(token));
    }
    return result;
}

std::vector<std::string> split_string_string(const std::string& str, char delimiter){
    std::vector<std::string> result;
    size_t pos = 0, found;
    std::string token;
    while ((found = str.find_first_of(delimiter, pos)) != std::string::npos)
    {
        token = str.substr(pos, found - pos);
        result.push_back(token);
        pos = found + 1;
    }
    result.push_back(str.substr(pos));
    return result;
}
void processing_tcp_scan_ports(const std::string& ip, const std::vector<int>& ports, int timeout_ms){
    for (const auto& port : ports) {
        int result = tcp_scan_port(ip.c_str(), port, timeout_ms);
        if (result == 0) {
            if (port == 80 || port == 8080 || port == 8081 || port == 8888){
                std::string result = ip + ":" + std::to_string(port);
                std::string result_print = gray_nesca + "[" + std::string(get_time()) + "] [BA] " + sea_green + result + reset_color + gray_nesca + " T: " + golder_rod + get_html_title(ip) + reset_color;
                std::string result_txt = "[" + std::string(get_time()) + "] [BA] " + result + " T: " + get_html_title(ip);

                std::lock_guard<std::mutex> guard(mtx);
                if (argp.txt){
                    int temp = write_line(argp.txt_save, result_txt);
                }
                std::cout << result_print << std::endl;
            }
            else {
                std::string result = ip + ":" + std::to_string(port);
                std::string result_print = gray_nesca + "[" + std::string(get_time()) + "] [BA] " + sea_green + result + reset_color;
                std::string result_txt = "[" + std::string(get_time()) + "] [BA] "+ result;
                
                if (argp.txt){
                    int temp = write_line(argp.txt_save, result_txt);
                }

                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;
            }

        }
        else if (result == -1 || result == -2 || result == -3){
            if (argp.print_errors){
                std::string result_print = "[" + std::string(get_time()) + "][NB] " + ip + " [ERROR]: " + std::to_string(result);
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << red_html;
                std::cout << result_print << std::endl;
                std::cout << reset_color;
            }
        }
        else {
            std::lock_guard<std::mutex> guard(mtx);
            std::string result_txt = "[" + std::string(get_time()) + "][DB] " + ip + ":" + std::to_string(port) + " [CLOSED]";
            std::string result_print = gray_nesca + "[" + std::string(get_time()) + "] [DB] " + red_html + ip + ":" + std::to_string(port) + " [CLOSED]" + reset_color;
            if (argp.debug){
                if (argp.txt){
                    int temp = write_line(argp.txt_save, result_txt);
                }
                std::cout << result_print << std::endl;
            }
        }
    }
}

bool check_ansi_support(void){
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return false;
    }

    if (dwMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)
    {
        return true;
    }

    return false;
    #else
    const char* envValue = std::getenv("TERM");
    if (envValue == nullptr)
    {
        return false;
    }

    return std::string(envValue).find("xterm") != std::string::npos;
    #endif
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
    std::cout << "  -import-ip <path>      Set ips on target from file.\n";
    std::cout << "  -import-cidr <path>    Set cidr on target from file.\n";
    std::cout << "  -random-ip <count>     Set random ips target.\n";

    std::cout << sea_green;
    std::cout << "\narguments ports:" << std::endl;
    std::cout << reset_color;
    std::cout << "  -ports, -p <1,2,3>     Set ports on scan.\n";

    std::cout << sea_green;
    std::cout << "\narguments speed:" << std::endl;
    std::cout << reset_color;
    std::cout << "  -threads, -T <count>   Set threads for scan.\n";
    std::cout << "  -timeout, -t <ms>      Set timeout for scan.\n";

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
    std::cout << "  -log-set <count>       Change change the value of ips after which, will be displayed information about how much is left.\n";
    std::cout << "  -txt <path>            Save result to text document.\n";
}

void print_logo(void){
    std::cout << "d8b   db d88888b .d8888.  .o88b.  .d8b.         j88D  \n";
    std::cout << "888o  88 88'     88'  YP d8P  Y8 d8' `8b       j8~88  \n"; 
    std::cout << "88V8o 88 88ooooo `8bo.   8P      88ooo88      j8' 88  \n";
    std::cout << "88 V8o88 88~~~~~   `Y8b. 8b      88~~~88      V88888D \n";
    std::cout << "88  V888 88.     db   8D Y8b  d8 88   88          88  \n";
    std::cout << "VP   V8P Y88888P `8888Y'  `Y88P' YP   YP          VP  \n";
    std::cout << reset_color;
    std::cout << std::endl;
}
