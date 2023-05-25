#include "../include/networktool.h"
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>

std::string
get_dns_ip(const char* ip){
    struct sockaddr_in sa{};
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(ip);

    char host[NI_MAXHOST];
    int result = getnameinfo((struct sockaddr*)&sa, sizeof(sa), host, sizeof(host), nullptr, 0, NI_NAMEREQD);
    if (result !=0 ){
        return "ERROR";
    }

    return host;
}
