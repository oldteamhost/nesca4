#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cstring>
#include "easysock.h"

#define HTTPREQUEST_VERSION 0.1
#define HTTPREQUEST_ERROR "HTTPREQUEST: error"

std::string 
send_http_request(const std::string& node, int port);

int
get_response_code(const std::string& node, int port);

std::string
get_headers(const std::string &node, int port);

#endif
