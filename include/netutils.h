#ifndef NET_UTILS_H
#define NET_UTILS_H

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>

#include "../modules/include/easysock.h"

class dns_utils{
public:
    const char* 
    get_dns_by_ip(const char* ip, int port);
    const char* 
    get_ip_by_dns(const char* dns);
    std::vector<std::string>
    get_all_ips_by_dns(const char* dns);
};

class ip_utils{
public:
    const char* 
    get_local_ip();
};

#endif
