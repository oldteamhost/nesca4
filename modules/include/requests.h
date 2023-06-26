#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

#define HTTPREQUEST_ERROR "HTTPREQUEST: error"

std::string 
send_http_request(const std::string& node, int port);

int
get_response_code(const std::string& node, int port);

#endif
