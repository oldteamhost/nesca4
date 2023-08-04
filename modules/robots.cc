#include "include/robots.h"

std::string
get_robots_txt(const std::string& ip, int port)
{
    std::string result = send_http_request_no_curl(ip, "/robots.txt", port);
    std::istringstream stream(result);
    std::string line;
    while (std::getline(stream, line)) {
        if (line.find("200") != std::string::npos) {
            return result;
        }
    }
    return "n/a";
}

std::string
get_sitemap_xml(const std::string& ip, int port)
{
    std::string result = send_http_request_no_curl(ip, "/sitemap.xml", port);
    std::istringstream stream(result);
    std::string line;
    while (std::getline(stream, line)) {
        if (line.find("200") != std::string::npos) {
            return result;
        }
    }
    return "n/a";
}
