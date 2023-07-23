/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/requests.h"
#include <cstdio>
#include <unistd.h>
#include "../include/callbacks.h"
#include <curl/curl.h>

std::string 
send_http_request(const std::string& node, int port) {
	curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();
    if (curl){
        std::string buffer;
		std::string headerBuffer;
        curl_easy_setopt(curl, CURLOPT_URL, node.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_request);
		curl_easy_setopt(curl, CURLOPT_PORT, port);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64; rv:35.0) Gecko/20100101 Firefox/35.0");
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerBuffer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2L);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {return "";}

        curl_easy_cleanup(curl);
        curl_global_cleanup();

		std::string response = headerBuffer + buffer;
        return response;
    }
    return "";
}

int
get_response_code(const std::string& node, int port){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == EOF){return -1;}

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
    if (result == EOF) {
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
