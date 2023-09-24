/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#ifndef TARGET_H
#define TARGET_H

#include <cstdint>
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

struct _portlist_
{
  uint16_t port;
  short state;
};

struct _nescadata_
{
  char ip[16];
  double rtt;
  std::string dns;
  std::string new_dns;

  std::vector<_portlist_> ports;
};

class NESCADATA {
  private:
    std::vector<_nescadata_> all_data;
    _nescadata_* get_data_block(const std::string& ip);
  public:
    void update_data_from_ips(const std::vector<std::string>& updated_ips);
    void set_new_dns(const std::string& ip, const std::string& new_dns);
    std::vector<uint16_t> get_port_list(const std::string& ip, short state);
    void add_port(const std::string& ip, uint16_t port, short state);
    void set_dns(const std::string& ip, const std::string& dns);
    void set_rtt(const std::string& ip, double rtt);
    void add_ip(const std::string& ip);
    short get_port_state(const std::string& ip, uint16_t port);
    std::string get_new_dns(const std::string& ip);
    std::string get_dns(const std::string& ip);
    bool find_port_status(const std::string& ip, short state);
    double get_rtt(const std::string& ip);
    std::vector<std::string> get_all_ips(void);
    void clean_ports(void);

    std::vector<std::string> current_group;
    int group_size, group_rate, max_group_size;
    void create_group(void);
    void increase_group(void);
    void clean_group(void);
};

std::vector<std::string> cidr_to_ips(const std::vector<std::string>& cidr_list);
std::vector<std::string> range_to_ips(const std::vector<std::string>& ip_ranges);
std::vector<std::string> convert_dns_to_ip(const std::vector<std::string>& dns_vector);
std::vector<int> split_string_int(const std::string& str, char delimiter);
std::vector<std::string> split_string_string(const std::string& str, char delimiter);

#endif
