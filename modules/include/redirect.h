#ifndef REDIRECT_H
#define REDIRECT_H
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#define REDIRECT_ERROR -1

std::string
parse_http_equiv(std::string& html);

std::string 
parse_url_from_js(std::string& html);

std::string 
parse_content_location(std::string& header);

std::string 
parse_location(std::string& header);

std::string 
process_redirect(const std::string& path, const std::string& ip, int port);

std::string
parse_redirect(std::string& html, std::string &header, const std::string& ip, bool fix, int port);

#endif
