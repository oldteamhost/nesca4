/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/smtpinfo.h"

std::string smtp_get_220_response(const std::string& ip, int port, int verbose) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == EOF){return SMTP_ERROR;}

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &(server_address.sin_addr)) <= 0) {close(sock);return SMTP_ERROR;}
    if (connect(sock, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) < 0){close(sock);return SMTP_ERROR;}
	int timeout_ms = 1000;

	struct timeval timeout;
	timeout.tv_sec = timeout_ms / 1000;
	timeout.tv_usec = (timeout_ms % 1000) * 1000;
	int result = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	if (result < 0){close(sock);return "-1";}

    char buffer[1024];
    memset(buffer, 0, 1024);

    if (recv(sock, buffer, 1024 - 1, 0) < 0){close(sock);return SMTP_ERROR;}

    if (verbose){std::cout << buffer;}

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
    else {response = SMTP_ERROR;}

    close(sock);
    return response;
}
