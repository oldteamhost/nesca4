#include <iostream>
#include <vector>

// cidr to ips
std::vector<std::string> cidr_to_ips(const std::vector<std::string>& cidr_list);
// range to ips
std::vector<std::string> range_to_ips(const std::vector<std::string>& ip_ranges);
// split int 
std::vector<int> split_string_int(const std::string& str, char delimiter);
// split string
std::vector<std::string> split_string_string(const std::string& str, char delimiter);

