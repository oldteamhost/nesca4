#include "include/scanner.h"
#include "include/networktool.h"
#include <cstddef>
#include <vector>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
#include <errno.h>
#endif

checking_finds cf;

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

    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

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
        closesocket(sock); WSACleanup();
#else
        close(sock);
#endif
    return 1;
}

int dns_scan(std::string domain, std::string domain_1level){
    std::string result = domain + domain_1level;

     double response_time = measure_ping_time(result.c_str(), 80);
     if (response_time != -1){
         if (response_time != 2){
             if (response_time != EOF){
                 return 1; // success
             }
         }
     }
     else {
         return 0; // failed
    }

    return -1; // error
}

std::string checking_finds::check_axis_camera(std::string ip){
    bool status = false;

    for (auto& path : cf.axis_path){
        size_t pos = ip.find(path);
        if (pos != std::string::npos){
            status = true;
            return path;
        }
    }
    return "";
}

std::string checking_finds::check_basic_auth(std::string ip){
    bool status = false;

    for (auto& path : cf.basic_auth_paths){
        size_t pos = ip.find(path);
        if (pos != std::string::npos){
            status = true;
            return path;
        }
    }
    return "";
}
