/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#ifndef TARGET_H
#define TARGET_H

#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <algorithm>

class group_scan {
public:
  int group_size, group_rate, max_group_size;
  std::vector<std::string> current_group;

  void create_group(std::vector<std::string>& ips, std::unordered_map<std::string, double> rtts);
  void increase_group(void);
  void clean_group(void);
};

std::vector<std::string> cidr_to_ips(const std::vector<std::string>& cidr_list);
std::vector<std::string> range_to_ips(const std::vector<std::string>& ip_ranges);
std::vector<std::string> convert_dns_to_ip(const std::vector<std::string>& dns_vector);
std::vector<int> split_string_int(const std::string& str, char delimiter);
std::vector<std::string> split_string_string(const std::string& str, char delimiter);

#endif
