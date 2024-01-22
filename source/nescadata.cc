
/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "../include/nescadata.h"
#include "../ncsock/include/types.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <unordered_set>

_nescadata_* NESCADATA::get_data_block(const std::string& ip)
{
  auto it = std::find_if(all_data.begin(), all_data.end(), [&ip](const _nescadata_& data) {
    return data.ip == ip;
  });
  if (it != all_data.end())
    return &(*it);

  return nullptr;
}

void NESCADATA::set_new_dns(const std::string& ip, const std::string& new_dns)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    data->new_dns = new_dns;
}

void NESCADATA::add_redirect(const std::string& ip, const std::string& redirect)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    data->redirect = redirect;
}

std::string NESCADATA::get_redirect(const std::string& ip)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    return data->redirect;
  return "n/a";
}

void NESCADATA::add_html(const std::string& ip, const std::string& html)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    data->html = html;
}

std::string NESCADATA::get_html(const std::string& ip)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    return data->html;
  return "n/a";
}

void NESCADATA::clean_ports(void)
{
  for (auto& data : all_data)
    data.ports.clear();
}

void NESCADATA::remove_duplicates(void)
{
  std::unordered_set<std::string> unique_ips;
  std::vector<_nescadata_> unique_data;

  for (const _nescadata_& data : all_data) {
    std::string ip = data.ip;

    if (unique_ips.find(ip) == unique_ips.end()) {
      unique_ips.insert(ip);
      unique_data.push_back(data);
    }
  }

  all_data = std::move(unique_data);
}

void NESCADATA::negatives_hosts(const std::vector<std::string> ips)
{
  std::unordered_set<std::string> ips_set(ips.begin(), ips.end());

  auto it = all_data.begin();
  while (it != all_data.end()) {
    std::string ip = it->ip;
    if (ips_set.find(ip) != ips_set.end())
      it = all_data.erase(it);
    else
      ++it;
  }
}

void print_nescadata_(const _nescadata_& data)
{
  std::cout << "ip address: " << data.ip << std::endl;
  puts ("--------------------------------------------");
  std::cout << "old dns: " << data.dns << std::endl;
  std::cout << "new dns: " << data.new_dns << std::endl;
  std::cout << "rtt flag: " << std::boolalpha << data.rtt_init << std::endl;
  std::cout << "rtt: " << data.rtt << std::endl;
  if (!data.html.empty())
    std::cout << "html code: true" << std::endl;
  else
    std::cout << "html code: false" << std::endl;
  std::cout << "redirect: " << data.redirect << std::endl;
  std::cout << "ports:" << std::endl;
  for (const auto& port : data.ports)
    std::cout << "  port: " << port.port << ", state: " << port.state << std::endl;
  puts ("--------------------------------------------");
}

void NESCADATA::print_datablock(const std::string &ip)
{
  _nescadata_* data = get_data_block(ip);
  print_nescadata_(*data);
}

void NESCADATA::printall_datablock(void)
{
  for (const auto& data : all_data)
    print_nescadata_(data);
}

void NESCADATA::add_port(const std::string& ip, uint16_t port, short state)
{
  _nescadata_* data = get_data_block(ip);
  if (data) {
    _portlist_ port_enty = {port, state};
    data->ports.push_back(port_enty);
  }
}

std::vector<std::string> NESCADATA::get_all_ips(void)
{
  std::vector<std::string> all_ips;
  for (const _nescadata_& data : all_data)
    all_ips.push_back(data.ip);

  return all_ips;
}

void NESCADATA::update_data_from_ips(const std::vector<std::string>& updated_ips)
{
  std::vector<_nescadata_> new_all_data;

  if (updated_ips.empty())
    return;

  for (const _nescadata_& data : all_data) {
    if (std::find(updated_ips.begin(), updated_ips.end(), data.ip) == updated_ips.end())
      new_all_data.push_back(data);
  }
  all_data = new_all_data;
}

void NESCADATA::set_dns(const std::string& ip, const std::string& dns)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    data->dns = dns;
}

void NESCADATA::set_rtt(const std::string& ip, double rtt)
{
  _nescadata_* data = get_data_block(ip);
  if (data) {
    data->rtt = rtt;
    data->rtt_init = true;
  }
}

bool NESCADATA::find_port_status(const std::string& ip, short state)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    for (const _portlist_& entry : data->ports)
      if (entry.state == state)
        return true;

  return false;
}

void NESCADATA::add_ip(const std::string& ip)
{
  _nescadata_ newdata;
  newdata.dns = "";
  newdata.rtt_init = false;
  newdata.rtt = 0.0;
  newdata.html = "";
  newdata.ports = {};
  newdata.new_dns = "";
  newdata.redirect = "";

  newdata.ip = ip;
  all_data.push_back(newdata);
}

std::vector<u16> NESCADATA::get_port_list(const std::string& ip, short state)
{
  _nescadata_* data = get_data_block(ip);
  std::vector<u16> port_list;

  if (data)
    for (const _portlist_& entry : data->ports)
      if (entry.state == state)
        port_list.push_back(entry.port);

  return port_list;
}

short NESCADATA::get_port_state(const std::string& ip, uint16_t port)
{
  _nescadata_* data = get_data_block(ip);

  if (data)
    for (const _portlist_& entry : data->ports)
      if (entry.port == port)
        return entry.state;

  return -1;
}

std::string NESCADATA::get_new_dns(const std::string& ip)
{
  _nescadata_* data = get_data_block(ip);

  if (data)
    if (!data->new_dns.empty() && data->new_dns.length() > 1)
      return data->new_dns;

  return "n/a";
}

std::string NESCADATA::get_dns(const std::string& ip)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    return data->dns;

  return "n/a";
}

void NESCADATA::delete_data_block(const std::string& ip)
{
  all_data.erase(std::remove_if(all_data.begin(), all_data.end(), [&ip](const _nescadata_& data){
    return data.ip == ip;
  }), all_data.end());
}

double NESCADATA::get_rtt(const std::string& ip)
{
  _nescadata_* data = get_data_block(ip);

  if (data && data->rtt_init == true)
    return data->rtt;

  return -1;
}

void NESCADATA::sort_ips_rtt(std::vector<std::string>& ips)
{
  std::sort(ips.begin(), ips.end(), [this](const std::string& a, const std::string& b) {
    double rtt_a = get_rtt(a), rtt_b = get_rtt(b);
    return rtt_a < rtt_b;
  });
}

#include "../include/nescautils.h"
#include "../ncsock/include/utils.h"

static void numipv4(u32 n, u8 *ip)
{
  ip[0] = static_cast<u8>((n >> 24) & 0xFF);
  ip[1] = static_cast<u8>((n >> 16) & 0xFF);
  ip[2] = static_cast<u8>((n >> 8) & 0xFF);
  ip[3] = static_cast<u8>(n & 0xFF);
}

static std::vector<std::string> listips(const std::string &cidr)
{
#define V4 4
#define V6 16
  u8 pip[V6], pmask[V6], maxip[V6], tmp[V6];
  std::vector<std::string> result;
  int v, i;
  u32 n;

  v = parsecidr(const_cast<char*>(cidr.data()), pip, pmask);
  if (v == -1)
    return result;
  
  for (i = 0; i < v; i++)
    maxip[i] = (pip[i] & pmask[i]) | ~pmask[i];
  
  if (v == V4) {
    for (n = ip4num(pip); n <= ip4num(maxip); n++) {
      char ip[46];
      numipv4(n, tmp);
      result.push_back(ipstr(v, tmp, ip));
    }
  }
  
  return result;
}

std::string ipbin(const std::string &ip)
{
  std::stringstream ss(ip);
  std::string token, binip = "";
  int octet;
  
  while (std::getline(ss, token, '.')) {
    octet = std::stoi(token);
    binip += std::bitset<8>(octet).to_string();
  }
  
  return binip;
}

std::string rangetocidr(const std::string &ip_range)
{
  std::string start_ip, end_ip, binstart, binend;
  std::stringstream ss(ip_range);
  size_t prefixlen = 0, i;
  
  std::getline(ss, start_ip, '-');
  std::getline(ss, end_ip);
  
  binstart = ipbin(start_ip);
  binend = ipbin(end_ip);
  
  for (i = 0; i < binstart.size(); ++i) {
    if (binstart[i] == binend[i])
      ++prefixlen;
    else
      break;
  }
  
  return ((start_ip + "/" + std::to_string(prefixlen)));
}

std::vector<std::string> cidr_to_ips(const std::vector<std::string>& cidr_list)
{
  std::vector<std::string> res, ips;
  
  for (const auto& cidr : cidr_list) {
    ips = listips(cidr);
    res.insert(res.end(), ips.begin(), ips.end());
  }
  
  return res;
}

std::vector<std::string> range_to_ips(const std::vector<std::string>& ip_ranges)
{
  std::vector<std::string> tmp;
  
  for (const auto& range : ip_ranges)
    tmp.push_back(rangetocidr(range));

  return (cidr_to_ips(tmp));
}

std::vector<std::string> convert_dns_to_ip(const std::vector<std::string>& dns_vector)
{
  std::vector<std::string> ip_vector;
  struct addrinfo hints, *res;
  int status;
  char ip_str[INET_ADDRSTRLEN];
  struct sockaddr_in *addr;

  for (const auto& dns : dns_vector) {
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(dns.c_str(), NULL, &hints, &res);
    if (status != 0)
      continue;

    addr = (struct sockaddr_in*) res->ai_addr;
    inet_ntop(AF_INET, &(addr->sin_addr), ip_str, INET_ADDRSTRLEN);
    ip_vector.push_back(ip_str);
    freeaddrinfo(res);
  }

  return ip_vector;
}

std::vector<int> split_string_int(const std::string& str, char delimiter)
{
  std::vector<int> result;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delimiter))
    result.push_back(std::stoi(token));

  return result;
}

std::vector<std::string> split_string_string(const std::string& str, char delimiter)
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
