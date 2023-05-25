#include "include/ftpinfo.h"

std::string get_ftp_description(std::string server, std::string port, std::string username, std::string password) {
    int sockfd = create_sock("tcp"); 
    if (sockfd == -1) {
        return FTP_ERROR;
    }

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(std::stoi(port));
    if (inet_pton(AF_INET, server.c_str(), &(server_addr.sin_addr)) <= 0) {
        close(sockfd);
        return FTP_ERROR;
    }

    if (connect(sockfd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        close(sockfd);
        return FTP_ERROR;
    }

    char buffer[2026];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytes_sent = send(sockfd, ("USER " + username + "\r\n").c_str(), strlen(("USER " + username + "\r\n").c_str()), 0);
    if (bytes_sent == -1) {
        close(sockfd);
        return FTP_ERROR;
    }

    bytes_sent = send(sockfd, ("PASS " + password + "\r\n").c_str(), strlen(("PASS " + password + "\r\n").c_str()), 0);
    if (bytes_sent == -1) {
        close(sockfd);
        return FTP_ERROR;
    }

    bytes_sent = send(sockfd, "QUIT\r\n", strlen("QUIT\r\n"), 0);
    if (bytes_sent == -1) {
        close(sockfd);
        return FTP_ERROR;
    }

    ssize_t bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received == -1) {
        close(sockfd);
        return FTP_ERROR;
    }

    close(sockfd);

    std::string response(buffer);
    size_t pos = response.find(' ');
    if (pos == std::string::npos) {
        return FTP_ERROR;
    }

    std::string response_description = response.substr(pos + 1);
    response_description = std::regex_replace(response_description, std::regex("\r"), "");
    response_description = std::regex_replace(response_description, std::regex("\n"), "");

    return response_description;
}

