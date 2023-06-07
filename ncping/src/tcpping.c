#include "../include/tcpping.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int
connect_tcp_ping(const char* ip, int port, int timeout_ms){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
	   return PING_ERROR;
    }

    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags < 0) {
        close(sockfd);
	   return PING_ERROR;
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
        close(sockfd);
	   return PING_ERROR;
    }

    // Установка адреса назначения
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &(server_address.sin_addr)) <= 0) {
        close(sockfd);
	   return PING_ERROR;
    }

    struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        close(sockfd);
	   return PING_ERROR;
    }

    int result = connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address));

    if (result == 0 || errno == ECONNREFUSED) {
        close(sockfd);
	   return PING_ERROR;
    } 
    else if (errno == EINPROGRESS) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(sockfd, &fds);

        result = select(sockfd + 1, NULL, &fds, NULL, &timeout);
        if (result > 0) {
            close(sockfd);
		  return PING_ERROR;
        }
    }

    close(sockfd);
    return PING_ERROR;
}
