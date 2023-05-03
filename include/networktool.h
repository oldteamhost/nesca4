#ifndef NETWORKTOOL_H
#define NETWORKTOOL_H

#include <iostream>
#include <string>

double measure_ping_time(const char* node, int port);
std::string get_dns_ip(const char* ip);
long get_response_code(const char *node);
std::string get_html_title(std::string node);
std::string send_http_request(std::string url);
std::string get_ftp_response_code(std::string server, std::string port, std::string username, std::string password);
std::string get_headers(const std::string node);

// get paths
std::string parse_content_from_meta(const std::string& html);
std::string parse_content_location(const std::string& header);
std::string parse_location(const std::string& header);
std::string get_paths_from_ip_address(const std::string& ip);
std::string parse_url_from_js(const std::string& html);

#endif
