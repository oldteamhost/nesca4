#ifndef HTTPTITLE_H
#define HTTPTITLE_H
#include <string>
#include <iostream>
#include <cstring>
#include <curl/curl.h>

#define HTTPTITLE_VERSION 0.2
#define HTTPTITLE_ERROR "N/A"

// basic only direct get (socket)
std::string
get_http_title(std::string &html_content);

// all get (libcurl)
std::string
get_http_title_pro(std::string& node);

#endif
