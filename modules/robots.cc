/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "include/robots.h"
#include "../../ncsock/include/http.h"
#include <sstream>

std::string
get_robots_txt(const std::string& ip, int port)
{
  http_header hh;
  hh.user_agent = "ncsock";
  hh.content_len = 0;
  hh.content_type = "";
  hh.method = "GET";
  hh.path = "/";
  hh.dest_host = ip.c_str();

  char response_buffer[4096];
  send_http_request(ip.c_str(), port, 1200, &hh, response_buffer, sizeof(response_buffer));

  std::string result = response_buffer;
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
  http_header hh;
  hh.user_agent = "ncsock";
  hh.content_len = 0;
  hh.content_type = "";
  hh.method = "GET";
  hh.path = "/";
  hh.dest_host = ip.c_str();

  char response_buffer[4096];
  send_http_request(ip.c_str(), port, 1200, &hh, response_buffer, sizeof(response_buffer));

  std::string result = response_buffer;
  std::istringstream stream(result);
  std::string line;
  while (std::getline(stream, line)) {
    if (line.find("200") != std::string::npos) {
      return result;
    }
  }
  return "n/a";
}
