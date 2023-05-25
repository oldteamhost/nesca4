#ifndef HTTPTITLE_H
#define HTTPTITLE_H
#include <string>
#include <iostream>
#include <curl/curl.h>

#define HTTPTITLE_VERSION 0.1
#define HTTPTITLE_ERROR "N/A"

std::string
get_http_title(std::string &html_content);

#endif
