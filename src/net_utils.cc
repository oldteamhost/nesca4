#include "../include/net_utils.h"
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <netinet/in.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#endif

void 
main_utils::close_socket(int sock){
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
}

int 
main_utils::create_socket(){
    int sock;
#ifdef _WIN32
    init_winsock();

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Failed to create socket: %d\n", WSAGetLastError());
        close_socket(sock);
        WSACleanup();
        return -1;
    }
#else
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Failed to create socket\n");
        close_socket(sock);
        return -1;
    }
#endif

    return sock;
}

void 
main_utils::init_winsock(){
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize winsock" << std::endl;
        return 1;
    }
#endif
}

const char*
dns_utils::get_dns_by_ip(const char* ip, int port){
    struct in_addr addr;
    if (inet_pton(AF_INET, ip, &addr) != 1) {
        return "get_dns_by_ip: Invalid IP address";
    }

    int sock = main_utils::create_socket();
    if (sock == -1) {
        return "get_dns_by_ip: Could not create socket";
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr = addr;
    sa.sin_port = htons(port);

    char host[NI_MAXHOST];
    int res = getnameinfo((struct sockaddr*)&sa, sizeof(sa), host, sizeof(host), NULL, 0, NI_NAMEREQD);
    if (res != 0) {
        main_utils::close_socket(sock);
        return "get_dns_by_ip: Could not resolve DNS";
    }

    char* dns_name = new char[strlen(host) + 1];
    strcpy(dns_name, host);
    main_utils::close_socket(sock);
    return dns_name;
}

const char* 
dns_utils::get_ip_by_dns(const char* dns){
    int sock = main_utils::create_socket();

    if (sock == -1){
        return "get_ip_by_dns: Could not create socket";
    }

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(dns, NULL, &hints, &res);

    if (status != 0){
        main_utils::close_socket(sock);
        return "get_dns_by_ip: Could failed getting ip";
    }

    struct sockaddr_in *addr = (struct sockaddr_in *)res->ai_addr;
    const char* ip = inet_ntoa(addr->sin_addr);

    freeaddrinfo(res);

    main_utils::close_socket(sock);
    return ip;
}

std::vector<std::string> dns_utils::get_all_ips_by_dns(const char* dns){

#ifdef _WIN32
    main_utils::init_winsock();
#endif

    std::vector<std::string> ip_addresses;
    struct addrinfo* result;

    int status = getaddrinfo(dns, nullptr, nullptr, &result);
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return ip_addresses;
    }

    struct addrinfo* current = result;

    while (current != nullptr) {
        char ip_address[INET6_ADDRSTRLEN];
        void* addr;

        if (current->ai_family == AF_INET) {
            struct sockaddr_in* addr_in = reinterpret_cast<struct sockaddr_in*>(current->ai_addr);
            addr = &(addr_in->sin_addr);
        } 
        else {
            struct sockaddr_in6* addr_in6 = reinterpret_cast<struct sockaddr_in6*>(current->ai_addr);
            addr = &(addr_in6->sin6_addr);
        }

        #ifdef _WIN32
            inet_ntop(current->ai_family, addr, ip_address, INET6_ADDRSTRLEN);
        #else
            inet_ntop(current->ai_family, addr, ip_address, sizeof(ip_address));
        #endif
        std::string ip_str(ip_address);
        if (std::find(ip_addresses.begin(), ip_addresses.end(), ip_str) == ip_addresses.end()) {
            ip_addresses.push_back(ip_str);
        }

        current = current->ai_next;
    }

    freeaddrinfo(result);

#ifdef _WIN32
    WSACleanup();
#endif

    return ip_addresses;
}
int
main_utils::create_raw_socket(std::string protocol){
    int sock;
#ifdef _WIN32
    init_winsock();
#endif
    if (protocol == "tcp"){
        sock = socket (AF_INET, SOCK_RAW, IPPROTO_TCP);
    }
    else if (protocol == "icmp"){
        sock = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP);
    }

    if (sock < 0){
        return -1;
    }

    return sock;
}

const char*
ip_utils::get_local_ip(){
    struct sockaddr_in serv;
    static char buffer[100];
    socklen_t namelen;

    int sock = main_utils::create_socket();
    if (sock < 0){
        return "-1";
    }

    const char *kGoogleDnsIp = "8.8.8.8";
    int dns_port = 53;

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(kGoogleDnsIp);
    serv.sin_port = htons(dns_port);

    int err = connect(sock, (const struct sockaddr*)&serv, sizeof(serv));
    if (err < 0){
        main_utils::close_socket(sock);
        return "-1";
    }

    struct sockaddr_in name;
    namelen = sizeof(name);
    memset(&name, 0, sizeof(name));
    if (getsockname(sock, (struct sockaddr*)&name, &namelen)){
        main_utils::close_socket(sock);
        return "-1";
    }

    const char *p = inet_ntop(AF_INET, &name.sin_addr, buffer, sizeof(buffer));
    main_utils::close_socket(sock);
    return p;
}












