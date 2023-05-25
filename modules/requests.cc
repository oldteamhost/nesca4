#include "include/requests.h"

std::string 
send_http_request(const std::string& node, int port) {
    int sockfd = create_sock("tcp"); 
    if (sockfd < 0) {
        throw std::runtime_error("Failed to create socket.");
    }

    // Получение информации о хосте
    struct addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    std::stringstream port_str;
    port_str << port;

    if (getaddrinfo(node.c_str(), port_str.str().c_str(), &hints, &res) != 0) {
        close(sockfd);
        throw std::runtime_error("Failed to get address info.");
    }

    // Установка соединения
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        close(sockfd);
        return HTTPREQUEST_ERROR;
    }

    // Формирование HTTP-запроса
    std::stringstream request_stream;
    request_stream << "GET / HTTP/1.1\r\n";
    request_stream << "Host: " << node << "\r\n";
    request_stream << "Connection: close\r\n";
    request_stream << "\r\n";
    std::string request = request_stream.str();

    // Отправка HTTP-запроса
    ssize_t bytesSent = send(sockfd, request.c_str(), request.length(), 0);
    if (bytesSent < 0) {
        close(sockfd);
        throw std::runtime_error("Failed to send data.");
    }

    // Получение и обработка HTTP-ответа
    std::string response_string;
    char buffer[4026];
    ssize_t bytesRead;

    while ((bytesRead = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';
        response_string += buffer;
    }

    // Закрытие сокета
    close(sockfd);

    return response_string;
}

int
get_response_code(const std::string& node, int port){
    int sockfd = create_sock("tcp"); 
    if (sockfd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, node.c_str(), &(server_addr.sin_addr)) <= 0) {
        std::cerr << "Invalid IP address" << std::endl;
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sockfd);
        return -1;
    }

    // Отправляем HTTP-запрос
    std::string request = "GET / HTTP/1.1\r\nHost: " + node + "\r\nConnection: close\r\n\r\n";
    if (send(sockfd, request.c_str(), request.length(), 0) < 0) {
        std::cerr << "Failed to send request" << std::endl;
        close(sockfd);
        return -1;
    }

    // Получаем код ответа
    char buffer[2020];
    if (recv(sockfd, buffer, sizeof(buffer), 0) < 0) {
        std::cerr << "Failed to receive response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Извлекаем код ответа из HTTP-заголовка
    std::string response(buffer);
    std::size_t pos = response.find("HTTP/1.1");
    if (pos == std::string::npos) {
        std::cerr << "Invalid response" << std::endl;
        close(sockfd);
        return -1;
    }

    int code = std::stoi(response.substr(pos + 9, 3));

    // Закрываем соединение и возвращаем код ответа
    close(sockfd);
    return code;
}
