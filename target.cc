/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "include/target.h"

/*Тут создаётся группа путём перемешения из всех IP.
 * Именно перемешения, я думаю это лучшее что можно было сделать.*/
void group_scan::create_group(std::vector<std::string>& ips, std::unordered_map<std::string, double> rtts)
{
  /*Сортировка по возрастанию времени ответа.*/
  std::sort(ips.begin(), ips.end(), [&rtts](const std::string& a, const std::string& b){return rtts[a] < rtts[b];});
  for (int i = 1; i <= group_size && !ips.empty(); i++) {
    current_group.push_back(std::move(ips[0]));
    ips.erase(ips.begin());
  }
}

void group_scan::increase_group(void)
{
  group_size += group_rate;
}

void group_scan::clean_group(void) {current_group.clear();}

std::vector<std::string>
range_to_ips(const std::vector<std::string>& ip_ranges)
{
  std::vector<std::string> result;
  for (const auto& range : ip_ranges) {
    std::istringstream iss(range);
    std::string start_ip_str, end_ip_str;
    std::getline(iss, start_ip_str, '-');
    std::getline(iss, end_ip_str);

    unsigned int start_ip = 0;
    unsigned int end_ip = 0;
    int octet = 0;
    for (std::istringstream ss(start_ip_str); std::getline(ss, start_ip_str, '.'); ++octet) {
      start_ip |= (std::stoi(start_ip_str) << ((3 - octet) * 8));
    }
    octet = 0;
    for (std::istringstream ss(end_ip_str); std::getline(ss, end_ip_str, '.'); ++octet) {
      end_ip |= (std::stoi(end_ip_str) << ((3 - octet) * 8));
    }
    for (unsigned int i = start_ip; i <= end_ip; ++i) {
      std::stringstream ss;
      ss << ((i >> 24) & 0xFF) << '.' << ((i >> 16) & 0xFF) << '.' << ((i >> 8) & 0xFF) << '.' << (i & 0xFF);
      result.push_back(ss.str());
    }
  }
  return result;
}

std::vector<std::string>
cidr_to_ips(const std::vector<std::string>& cidr_list)
{
  std::vector<std::string> ipAddresses;
  for (const std::string& cidr : cidr_list) {
    std::string networkAddress = cidr.substr(0, cidr.find('/'));
    int subnetMaskBits = std::stoi(cidr.substr(cidr.find('/') + 1));

    std::vector<unsigned long long int> octets;
    std::string octetString;
    std::stringstream networkAddressStream(networkAddress);

    while (std::getline(networkAddressStream, octetString, '.')) {
      octets.push_back(std::strtoull(octetString.c_str(), nullptr, 10));
    }

    unsigned long long int ipAddress = 0;

    for (auto octet : octets) {
      ipAddress = (ipAddress << 8) | octet;
    }

    std::bitset<32> subnetMask((0xFFFFFFFFUL << (32 - subnetMaskBits)) & 0xFFFFFFFFUL);
    ipAddress &= subnetMask.to_ulong();

    for (unsigned long long int i = 0; i < (1ULL << (32 - subnetMaskBits)); i++) {
      std::stringstream ipAddressStream;
      ipAddressStream << ((ipAddress >> 24) & 0xFF) << '.' << ((ipAddress >> 16) & 0xFF) << '.' << ((ipAddress >> 8) & 0xFF) << '.' << (ipAddress & 0xFF);
      ipAddresses.push_back(ipAddressStream.str());
      ipAddress++;
    }
  }

  return ipAddresses;
}

std::vector<int>
split_string_int(const std::string& str, char delimiter)
{
  std::vector<int> result;
  std::stringstream ss(str);
  std::string token;
  while (std::getline(ss, token, delimiter)) {
    result.push_back(std::stoi(token));
  }
  return result;
}

std::vector<std::string>
split_string_string(const std::string& str, char delimiter)
{
  std::vector<std::string> result;
  size_t pos = 0, found;
  std::string token;
  while ((found = str.find_first_of(delimiter, pos)) != std::string::npos) {
    token = str.substr(pos, found - pos);
    result.push_back(token);
    pos = found + 1;
  }
  result.push_back(str.substr(pos));
  return result;
}

std::vector<std::string>
convert_dns_to_ip(const std::vector<std::string>& dns_vector)
{
  std::vector<std::string> ip_vector;
  for (const auto& dns : dns_vector) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(dns.c_str(), NULL, &hints, &res);
    if (status != 0) {continue;}

    struct sockaddr_in* addr = (struct sockaddr_in*) res->ai_addr;
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr->sin_addr), ip_str, INET_ADDRSTRLEN);
    ip_vector.push_back(ip_str);
    freeaddrinfo(res);
  }
  return ip_vector;
}
