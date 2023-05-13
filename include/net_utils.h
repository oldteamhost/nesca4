#ifndef NET_UTILS_H
#define NET_UTILS_H

#include <iostream>
#include <vector>

class main_utils{
public:
    static int create_socket();
    static int create_raw_socket();
    static void close_socket(int sock); 
    static void init_winsock();
};

class dns_utils{
public:
    const char* get_dns_by_ip(const char* ip, int port);
    const char* get_ip_by_dns(const char* dns);
    std::vector<std::string> get_all_ips_by_dns(const char* dns);

};

class ip_utils{
public:
    const char* get_local_ip();
};

#endif
