#include "../include/requests.h"

std::string 
send_http_request(const std::string& node, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {return HTTPREQUEST_ERROR;}

    struct addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    std::stringstream port_str;
    port_str << port;

    if (getaddrinfo(node.c_str(), port_str.str().c_str(), &hints, &res) != 0) {
        close(sockfd);
        return HTTPREQUEST_ERROR;
    }

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        close(sockfd);
        return HTTPREQUEST_ERROR;
    }

    std::stringstream request_stream;
    request_stream << "GET / HTTP/1.1\r\n";
    request_stream << "Host: " << node << "\r\n";
    request_stream << "Connection: close\r\n";
    request_stream << "\r\n";
    std::string request = request_stream.str();

    ssize_t bytesSent = send(sockfd, request.c_str(), request.length(), 0);
    if (bytesSent < 0) {
        close(sockfd);
        return HTTPREQUEST_ERROR;
    }

    struct pollfd fds[1];
    int timeout = 2000; /*2 секунды*/

    fds[0].fd = sockfd;
    fds[0].events = POLLIN;

    int result = poll(fds, 1, timeout);
    if (result == -1) {
        close(sockfd);
        return HTTPREQUEST_ERROR;
    } else if (result == 0) {
        close(sockfd);
        return HTTPREQUEST_ERROR;
    }

    std::string response_string;
    char buffer[4096];
    ssize_t bytesRead;

    while (true) {
        bytesRead = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead == -1) {
            close(sockfd);
            return HTTPREQUEST_ERROR;
        } else if (bytesRead == 0) {
            break;
        }
        buffer[bytesRead] = '\0';
        response_string += buffer;
    }

    close(sockfd);
    return response_string;
}

int
get_response_code(const std::string& node, int port){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){return -1;}

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, node.c_str(), &(server_addr.sin_addr)) <= 0) {
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(sockfd);
        return -1;
    }

    std::string request = "GET / HTTP/1.1\r\nHost: " + node + "\r\nConnection: close\r\n\r\n";
    if (send(sockfd, request.c_str(), request.length(), 0) < 0) {
        close(sockfd);
        return -1;
    }

    struct pollfd fds[1];
    int timeout = 2000; /*2 секунды*/
    fds[0].fd = sockfd;
    fds[0].events = POLLIN;

    int result = poll(fds, 1, timeout);
    if (result == -1) {
        close(sockfd);
        return -1;
    } else if (result == 0) {
        close(sockfd);
        return -1;
    }

    char buffer[2020];
    if (recv(sockfd, buffer, sizeof(buffer), 0) < 0) {
        close(sockfd);
        return -1;
    }

    std::string response(buffer);
    std::size_t pos = response.find("HTTP/1.1");
    if (pos == std::string::npos) {
        close(sockfd);
        return -1;
    }

    int code = std::stoi(response.substr(pos + 9, 3));

    close(sockfd);
    return code;
}
