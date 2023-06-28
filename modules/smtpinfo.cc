#include "include/smtpinfo.h"

std::string smtp_get_220_response(const std::string& ip, int port, int verbose) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return SMTP_ERROR;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &(server_address.sin_addr)) <= 0) {
        close(sock);
        return SMTP_ERROR;
    }

    if (connect(sock, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) < 0) {
        close(sock);
        return SMTP_ERROR;
    }

    char buffer[1024];
    memset(buffer, 0, 1024);

    if (recv(sock, buffer, 1024 - 1, 0) < 0) {
        close(sock);
        return SMTP_ERROR;
    }

    if (verbose) {
        std::cout << buffer;
    }

    std::string response(buffer);
    size_t pos = response.find("220");
    if (pos != std::string::npos) {
        size_t end_pos = response.find("\r\n", pos);
        if (end_pos != std::string::npos) {
            response = response.substr(pos, end_pos - pos + 2);
		  response = response.substr(4);

		  response.erase(std::remove(response.begin(), response.end(), '\n'), response.end());
		  response.erase(std::remove(response.begin(), response.end(), '\r'), response.end());

        }
    } 
    else {
        response = SMTP_ERROR;
    }

    close(sock);

    return response;
}
