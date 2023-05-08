#include "include/scanner.h"
#include "include/networktool.h"
#include "include/other.h"
#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <cerrno>
#include <vector>

#include <boost/asio.hpp>

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

checking_finds cf;

void close_socket(int sock){
    #ifdef _WIN32
    closesocket(sock);
    WSACleanup();
    #else
    close(sock);
    #endif
}

int create_socket() {
    int sock;

#ifdef _WIN32
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return -1;
    }

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

void set_non_blocking(int sock) {
#ifdef _WIN32
    u_long iMode = 1;
    if (ioctlsocket(sock, FIONBIO, &iMode) != NO_ERROR) {
        perror("ioctlsocket");
        return;
    }
#else
    int flags = fcntl(sock, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        return;
    }

    flags |= O_NONBLOCK;
    if (fcntl(sock, F_SETFL, flags) == -1) {
        perror("fcntl");
        return;
    }
#endif
}

int tcp_scan_port(const std::string& ip, int port, int timeout_ms) {
    const char* addr = ip.c_str();
    struct sockaddr_in addr_s;
    struct timeval tv;

    int so_error;
    int fd=-1;

    struct timespec tstart={0,0}, tend={0,0};
    struct pollfd fds[1];

    addr_s.sin_family = AF_INET;
    addr_s.sin_addr.s_addr = inet_addr(addr);
    addr_s.sin_port = htons(port);

    clock_gettime(CLOCK_MONOTONIC, &tstart);

    fd = create_socket();
    set_non_blocking(fd);

    int rc = connect(fd, (struct sockaddr *)&addr_s, sizeof(addr_s));

    if (rc == 0) {
        clock_gettime(CLOCK_MONOTONIC, &tend);
        close_socket(fd);
        return PORT_OPEN;
    }
    else if (rc == -1 && errno == EINPROGRESS) {
        fds[0].fd = fd;
        fds[0].events = POLLOUT;

        tv.tv_sec = timeout_ms / 1000;
        tv.tv_usec = (timeout_ms % 1000) * 1000;

        rc = poll(fds, 1, timeout_ms);
        if (rc > 0) {
            socklen_t len = sizeof(so_error);
            getsockopt(fd, SOL_SOCKET, SO_ERROR, &so_error, &len);
            if (so_error == 0) {
                clock_gettime(CLOCK_MONOTONIC, &tend);
                close_socket(fd);
                return PORT_OPEN;
            }
            else {
                close_socket(fd);
                return PORT_FILTERED;
            }
        }
        else if (rc == 0) {
            close_socket(fd);
            return PORT_CLOSED;
        }
    }

    close_socket(fd);
    return PORT_ERROR;
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
    return "no";
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
    return "no";
}
