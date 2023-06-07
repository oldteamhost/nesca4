#ifndef HTTPTITLE_H
#define HTTPTITLE_H
#include <string>
#include <iostream>
#include <cstring>
#include <curl/curl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define HTTPTITLE_ERROR "N/A"

// basic only direct get (socket)
std::string
get_http_title(std::string &html_content);

// all get (libcurl)
std::string
get_http_title_pro(std::string& node);

#endif
