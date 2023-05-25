#include "include/easysock.h"

void close_sock(int sock){
    close(sock);
}

int create_sock(std::string protocol){
    int sock_temp;

    if (protocol == "tcp"){
        sock_temp = socket(AF_INET, SOCK_STREAM, 0);
    }
    else if (protocol == "udp"){
        sock_temp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }
    else if (protocol == "icmp"){
        sock_temp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    }
    else {
        return ERROR;
    }

    if (sock_temp == -1){
        return ERROR;
    }

    return sock_temp;
}

int create_raw_sock(std::string protocol){
    int sock_temp;

    if (protocol == "default"){
        sock_temp = socket(AF_INET, SOCK_RAW, 0);
    }
    else if (protocol == "tcp"){
        sock_temp = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    }
    else if (protocol == "udp"){
        sock_temp = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    }
    else if (protocol == "icmp"){
        sock_temp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    }
    else {
        return ERROR;
    }

    if (sock_temp == -1){
        return ERROR;
    }

    return sock_temp;
}
