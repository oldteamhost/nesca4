#include <iostream>

// tcp ping
double measure_ping_time(const char* node, int port);
// get dns
std::string get_dns_ip(const char* ip);
// get response code
long get_response_code(const char *node);
// get http title
std::string get_html_title(std::string node);


