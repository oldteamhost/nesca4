// NESCA4
// by oldteam & lomaster
// license GPL-3.0
// 

#include <cstdio>
#include <iostream>
#include <bitset>
#include <getopt.h>
#include <ostream>
#include <mutex>
#include <thread>
#include <random>
#include <string>
#include <cstring>
#include <sstream>
#include <string.h>
#include <curl/curl.h>
#include <libssh/libssh.h>
#include <vector>
#include <fstream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#endif

#define VERSION "1183-build lomaster & oldteam"
#define DELIMITER ','

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
int dns_scan(std::string domain, std::string domain_1level);
std::vector<int> tcp_scan_ports(const std::vector<std::string>& ips, const std::vector<int>& ports, int timeout_ms);

// func curl
double measure_ping_time(const char* node, int port);
long get_response_code(const char *node);
std::string get_html_title(std::string node);
std::vector<std::string> brute_ftp(const std::string& ip, const std::vector<std::string>& logins, const std::vector<std::string>& passwords);
std::vector<std::string> brute_sftp(const std::string& ip, const std::vector<std::string>& logins, const std::vector<std::string>& passwords);
void check_net(void);

// files
std::vector<std::string> write_file(const std::string& filename);
int write_line(std::string, std::string line);
bool check_file(const char* path);
int get_count_lines(const char* path);
void parallel_dns_scan(int thread_count, int domain_count, const std::string& domain);
void checking_default_files(void);

// other
std::string generate_random_str(int len, std::string dictionary);
std::vector<std::string> cidr_to_ips(const std::vector<std::string>& cidr_list);
void delay_ms(int milliseconds);
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
        std::vector<int> ports;

        bool random_ip;
        int log_set = 100;
        bool dns_scan;
        bool ip_scan;
        bool ip_cidr_scan;
        bool debug;
        bool txt;
        int random_ip_count;
        int dns_scan_domain_count = 5;
        int timeout_ms = 55;
        int _threads = 1;
        bool timeout;
        int random_version = 4;
        bool brute;
};
arguments_program argp;

int main(int argc, char** argv){
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
        {"ssl-login", required_argument, 0, 13},
        {"ssl-pass", required_argument, 0, 14},

        {"dns-scan", required_argument, 0, 19},
        {"dns-length", required_argument, 0, 20},
        {"dns-dict", required_argument, 0, 21},
        {"txt", required_argument, 0, 22},
        {"log-set", required_argument, 0, 24},

        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {"ports", no_argument, 0, 'p'},

        {"ping-off", no_argument, 0, 15},
        {"cf", no_argument, 0, 16},
        {"dns-off", no_argument, 0, 17},
        {"db", no_argument, 0, 7},
        {"ftp-brute", no_argument, 0, 9},
        {"ssl-brute", no_argument, 0, 10},
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
                help_menu();
                return 0;
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
                else if (argp.ports_temp == "100"){
                    argp.ports = {80, 443, 22, 21, 25, 3389, 110, 143, 53, 445, 139, 3306, 8080, 
                        1723, 111, 995, 993, 5900, 1025, 587, 8888, 199, 1720, 465, 548, 113, 81,
                        6001, 10000, 514, 5060, 179, 1026, 2000, 8443, 8000, 444, 1433, 1900, 2001,
                        1027, 49152, 2049, 1028, 1029, 5901, 32768, 1434, 3283, 5800, 389, 53, 17988,
                        106, 5666, 1725, 465, 995, 548, 7, 123, 389, 113, 37, 427, 8001, 427, 1726,
                        49153, 2002, 515, 1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039,
                        1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049, 1050, 1051, 1052,
                        1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061, 1062, 1063, 1064, 1065,
                        1066, 1067, 1068, 1069, 1070, 1071, 1072, 1073, 1074, 1075, 1076, 1077};
                }
                else if (argp.ports_temp == "50"){
                    argp.ports = {80, 443, 22, 21, 25, 3389, 110, 143, 53, 445, 139, 3306, 8080, 1723,
                        111, 995, 993, 5900, 1025, 587, 8888, 199, 1720, 465, 548, 113, 81, 6001, 10000,
                        514, 5060, 179, 1026, 2000, 8443, 8000, 444, 1433, 1900, 2001, 1027, 49152, 2049, 1028, 1029, 5901, 32768, 1434, 3283}; 
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
                argp.ip_cidr = write_file(optarg);  

                if (check_file(optarg)){
                    std::cout << "[" << get_time() << "]" << "[OK] " << optarg << " (" << get_count_lines(optarg) << ") entries" << std::endl;
                }
                else {
                    std::cout << "[" << get_time() << "] " << "[-] " << optarg << " (" << get_count_lines(optarg) << ") entries" << std::endl;
                }
                break;
            }
            case 4:
            {
                if (atoi(optarg) == 6){
                    argp.random_version = 6;
                }
                else if (atoi(optarg) == 4){
                    argp.random_version = 4;
                }
                else {
                    std::cout << "random-vn: only 4, or 6.\n";
                    return 0;
                }
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
                argp._threads = atoi(optarg);
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
               argp._ip = write_file(optarg);

               if (check_file(optarg)){
                   std::cout << "[" << get_time() << "]" << "[OK] " << optarg << " (" << get_count_lines(optarg) << ") entries" << std::endl;
               }
               else {
                   std::cout << "[" << get_time() << "] " << "[-] " << optarg << " (" << get_count_lines(optarg) << ") entries" << std::endl;
               }
               break;
           }
           case 24:
              argp.log_set = atoi(optarg);
              break;
        }
    }

            checking_default_files();

            argp.logins = write_file("passwd/logins.txt");
            argp.passwords = write_file("passwd/passwords.txt");

            std::cout << "[" << get_time() << "]" << "[OK] Starting " << argp._threads << " threads...\n\n";

        // start dns_scan
        if (argp.dns_scan){
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
                                result_print = "[" + std::string(get_time()) + "][BA] " + result + " FAILED";
                                std::string *result_printp = &result_print;
                                if (argp.txt){
                                    int temp = write_line(argp.txt_save, *result_printp);
                                }
                                std::cout << result_print << std::endl;
                        }
                    }
                    else {
                        std::lock_guard<std::mutex> lock(mtx);
                            result_print = "[" + std::string(get_time()) + "][BA] " + result + " T: \"" + get_html_title(result) + "\"";
                            std::string *result_printp = &result_print;
                            if (argp.txt){
                                int temp = write_line(argp.txt_save, *result_printp);
                            }
                            std::cout << result_print << std::endl;
                    }
                }
            }).detach();
            if (argp.timeout)
                delay_ms(argp.timeout_ms);
        }
        std::getchar();
        std::cout << "\nStoping threads...\n";
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
    }
    
    int ip_count = 0;
    int ip_temp = 0;

    for (const auto& ip : result) {
        int size = result.size();

        if (ip_count % argp.log_set == 0){
            std::string result_print = "[" + std::string(get_time()) + "][NB] " + std::to_string(ip_count) + " out of " + std::to_string(size) + " IPs scanned.";
            std::cout << result_print << std::endl;
        }
 
        for (const auto& port : argp.ports) {
            int result = tcp_scan_port(ip.c_str(), port, argp.timeout_ms);

            if (result == 0) {
                if (port == 80 || port == 8080 || port == 8081 || port == 8888){
                    std::string result = "http://" + ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][HTTP] " + result + " T: \"" + get_html_title(ip) + "\"";
                    std::cout << result_print << std::endl;
                }

                if (port == 20 || port == 21){
                    std::string result = "ftp://" + ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][FTP] " + result;
                    std::cout << result_print << std::endl;
                }
                if (port == 7){
                    std::string result = ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][ECHO] " + result;
                    std::cout << result_print << std::endl;
                }
                if (port == 25565){
                    std::string result = ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][MINECRAFT] " + result;
                    std::cout << result_print << std::endl;
                }
                if (port == 143){
                    std::string result = ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][IMAP] " + result;
                    std::cout << result_print << std::endl;
                }
                if (port == 22){
                    std::string result = "sftp://" + ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][SSH] " + result;
                    std::cout << result_print << std::endl;
                }
                if (port == 53){
                    std::string result = ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][DNS] " + result;
                    std::cout << result_print << std::endl;
                }
                if (port == 443){
                    std::string result = "https://" + ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][HTTPS] " + result + " T: \"" + get_html_title(ip) + "\"";
                    std::cout << result_print << std::endl;
                }
                if (port == 8000){
                    std::string result = ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][HIKVISION] " + result;
                    std::cout << result_print << std::endl;
                }
                if (port == 23){
                    std::string result = ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][TELNET] " + result;
                    std::cout << result_print << std::endl;
                }
                if (port == 25){
                    std::string result = ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][SMTP] " + result;
                    std::cout << result_print << std::endl;
                }
                if (port == 113){
                    std::string result = ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][AUTH] " + result;
                    std::cout << result_print << std::endl;
                }
                if (port == 37777){
                    std::string result = ip + ":" + std::to_string(port);
                    std::string result_print = "[" + std::string(get_time()) + "][RVI] " + result;
                    std::cout << result_print << std::endl;
                }

                /*
                if (port == 21 || port == 20){
                    std::vector<std::string> result = brute_sftp(ip, argp.logins, argp.passwords);

                    if (result.empty()) {
                        std::cout << "Unable to connect to server\n";
                    } 
                    else {
                        std::cout << "Successfully connected to server with credentials:\n";
                        std::cout << "Login: " << result[0] << "\n";
                        std::cout << "Password: " << result[1] << "\n";
                    }
                }
                */

            } 
            else if (result == 1) {
                if (argp.debug){
                    std::cout << ip << " closed " << port << std::endl;
                }
                // closed
            } 
            else if (result == 2) {
                if (argp.debug){
                    std::cout << ip << " filter " << port << std::endl;
                }
            } 
            else {
                if (argp.debug){
                    std::cout << ip << " error " << port << std::endl;
                }
            }

        }
        ip_count++;
    }
    // end tcp_scan_port
    return 0;

   /* 
    for (const auto& line : argp._ip){
        double responce_time = measure_ping_time(line.c_str(), 80);

        if (responce_time != -1){
            if (responce_time != 2){
                std::cout << "Status: access | Ping: " << responce_time << "ms\n";
            }
        }
        else {
             std::cout << "Status: failed | Ping: " << responce_time << "ms\t    | ";
             if (responce_time == -2){
                std::cout << "Error: info check!\n";
             }
             else if (responce_time == EOF){
                std::cout << "Error: connection failed!\n";
            }
        }

        std::string lol = get_dns_ip(line.c_str());
        std::cout << lol << std::endl;
        int scan = tcp_scan_port(line.c_str(), 21, 100);

        if (scan == 0){
            printf("Port %d is open on %s\n", 21, line.c_str());
        }
        if (scan == 2){
            printf("Port %d is filter on %s\n", 21, line.c_str());
        }
        if (scan == 1){
            printf("Port %d is closed on %s\n", 21, line.c_str());
        }


        std::vector<std::string> successful_creds = brute_ftp(line, argp.logins, argp.passwords);

        if (!successful_creds.empty()) {
        std::cout << "Successful login and password: " << successful_creds[0] << std::endl;
        } else {
            std::cout << "Could not find a valid login and password combination" << std::endl;
        }

    }

    std::vector<std::string> result = brute_sftp(ip, logins, passwords);

    if (result.empty()) {
        std::cout << "Unable to connect to server\n";
    } else {
        std::cout << "Successfully connected to server with credentials:\n";
        std::cout << "Login: " << result[0] << "\n";
        std::cout << "Password: " << result[1] << "\n";
    }

    return 0;
    */
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
        return -3;
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
        close(sock);
        #ifdef _WIN32
        WSACleanup();
        #endif
        return 0;
    }

    if (ret < 0 && errno != EINPROGRESS) {
        if (errno == ECONNREFUSED) {
            close(sock);
            #ifdef _WIN32
            WSACleanup();
            #endif
            return 2;
        }
    }

    FD_ZERO(&fds);
    FD_SET(sock, &fds);

    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

    ret = select(sock + 1, NULL, &fds, NULL, &timeout);

    if (ret == 0) {
        close(sock);
        #ifdef _WIN32
        WSACleanup();
        #endif
        return 1;
    }

    if (ret < 0) {
        if (errno == EAGAIN) {
            close(sock);
            #ifdef _WIN32
            WSACleanup();
            #endif
            return 2;
        }

        if (errno == ECONNREFUSED) {
            close(sock);
            #ifdef _WIN32
            WSACleanup();
            #endif
            return 1;
        }
        else {
            close(sock);
            #ifdef _WIN32
            WSACleanup();
            #endif
            return -3;
        }
    }

    int err = 0;
    socklen_t len = sizeof(err);
    getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &len);

    if (err == 0 && FD_ISSET(sock, &fds)) {
        close(sock);
        #ifdef _WIN32
        WSACleanup();
        #endif
        return 0;
    }

    close(sock);
    #ifdef _WIN32
    WSACleanup();
    #endif
    return 1;
}

std::vector<int> tcp_scan_ports(const std::vector<std::string>& ips, const std::vector<int>& ports, int timeout_ms) {
    std::vector<int> results;
    for (const auto& ip : ips) {
        for (const auto& port : ports) {
            int result = tcp_scan_port(ip.c_str(), port, timeout_ms);
            results.push_back(result);
        }
    }
    return results;
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
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 5000L);
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
        return "";
    }

    if (!curl) {
        curl_easy_cleanup(curl);
        return "";
    }

    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_URL, node.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_http);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        return "";
    }

    char* content_type;
    res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type);

    if (res != CURLE_OK || content_type == nullptr) {
        curl_easy_cleanup(curl);
        return "";
    }

    std::string title_tag_open = "<title>";
    std::string title_tag_close = "</title>";

    size_t title_start = response_string.find(title_tag_open);
    if (title_start == std::string::npos) {
        curl_easy_cleanup(curl);
        return "";
    }
    title_start += title_tag_open.length();

    size_t title_end = response_string.find(title_tag_close, title_start);
    if (title_end == std::string::npos) {
        curl_easy_cleanup(curl);
        return "";
    }

    std::string title = response_string.substr(title_start, title_end - title_start);
    curl_easy_cleanup(curl);
    return title;
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

std::vector<std::string> brute_sftp(const std::string& ip, const std::vector<std::string>& logins, const std::vector<std::string>& passwords){
    std::vector<std::string> result;
    ssh_session ssh = ssh_new();

    if (!ssh) {
        return result;
    }

    ssh_options_set(ssh, SSH_OPTIONS_HOST, ip.c_str());
    ssh_options_set(ssh, SSH_OPTIONS_USER, "");
    ssh_options_set(ssh, SSH_OPTIONS_LOG_VERBOSITY, SSH_LOG_NONE);
    ssh_options_set(ssh, SSH_OPTIONS_STRICTHOSTKEYCHECK, 0);
    ssh_options_set(ssh, SSH_OPTIONS_PORT_STR, "22");

    int rc = ssh_connect(ssh);
    if (rc != SSH_OK) {
        ssh_disconnect(ssh);
        ssh_free(ssh);
        return result;
    }

    for (const auto& login : logins) {
        for (const auto& password : passwords) {
            rc = ssh_userauth_password(ssh, login.c_str(), password.c_str());
            if (rc == SSH_AUTH_SUCCESS) {
                result.push_back(login);
                result.push_back(password);
                ssh_disconnect(ssh);
                ssh_free(ssh);
                return result;
            }
        }
    }

    ssh_disconnect(ssh);
    ssh_free(ssh);
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

    if (check_file(path1)){
       std::cout << "[" << get_time() << "]" << "[OK] " << path1 << " (" << get_count_lines(path1) << ") entries" << std::endl;
    }
    else {
        std::cout << "[" << get_time() << "]" << "[FAILED] " << path1 << " (" << get_count_lines(path1) << ") entries" << std::endl;
    }
    if (check_file(path2)){
        std::cout << "[" << get_time() << "]" << "[OK] " << path2 << " (" << get_count_lines(path2) << ") entries" << std::endl;
    }
    else {
        std::cout << "[" << get_time() << "]" << "[FAILED] " << path2 << " (" << get_count_lines(path2) << ") entries" << std::endl;
    }
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
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
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

void help_menu(void){
    puts("Hello");
}
