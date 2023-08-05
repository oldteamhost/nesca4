/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/requests.h"

std::string
send_http_request_no_curl(const std::string& node, std::string path, int port)
{
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, node.c_str(), &server_addr.sin_addr);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        return "Error: Failed to create socket.";
    }

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(sockfd);
        return "Error: Failed to connect to host.";
    }

    std::ostringstream request;
    request << "GET " << path << " HTTP/1.1\r\n";
    request << "Host: " << node << "\r\n";
    request << "Connection: close\r\n\r\n";

    std::string response;
    send(sockfd, request.str().c_str(), request.str().length(), 0);

    int timeout = set_socket_timeout(sockfd, 1200, 1, 1);

    char buffer[1024];
    ssize_t bytes_received;
    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        response += buffer;
    }

    close(sockfd);
    return response;
}
