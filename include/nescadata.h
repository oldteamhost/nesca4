/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
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

struct datastring
{
  const char *data;
  uint32_t datalen;
};

struct datastring initdata(const std::string &data);

struct _portlist_
{
  uint16_t port;
  short state;
};

struct _nescadata_
{
  char ip[16];         /* IP адрес не может быть больше 16 байт */
  double rtt;          /* Время ответа хоста, после ping-а */
  bool rtt_init;       /* Иногда ping может просто skip-утся поэтому нужен флаг для отслежки этого */
  std::string dns;     /* DNS который указал пользователь при вызове ./nesca4 google.com */
  std::string new_dns; /* DNS который получила nesca */
  std::string html;    /* Результат send_http_request() */
  std::string redirect;/* Перенаправление */

  /* Собственно сюда идут все порты во время сканирования */
  std::vector<_portlist_> ports;
};

class NESCADATA {
  private:
    std::vector<_nescadata_> all_data;
    std::vector<std::string> temp_ips_group;
    _nescadata_* get_data_block(const std::string& ip);
    void delete_data_block(const std::string& ip);
  public:
    void add_html(const std::string& ip, const std::string& html);
    std::string get_html(const std::string& ip);
    void sort_ips_rtt(void);

    void add_redirect(const std::string& ip, const std::string& redirect);
    std::string get_redirect(const std::string& ip);

    short get_port_state(const std::string& ip, uint16_t port);
    bool find_port_status(const std::string& ip, short state);

    void update_data_from_ips(const std::vector<std::string>& updated_ips);
    void set_new_dns(const std::string& ip, const std::string& new_dns);
    std::vector<uint16_t> get_port_list(const std::string& ip, short state);
    void add_port(const std::string& ip, uint16_t port, short state);
    void set_dns(const std::string& ip, const std::string& dns);
    void negatives_hosts(const std::vector<std::string> ips);
    void set_rtt(const std::string& ip, double rtt);
    void add_ip(const std::string& ip);
    std::string get_new_dns(const std::string& ip);
    std::string get_dns(const std::string& ip);
    double get_rtt(const std::string& ip);
    std::vector<std::string> get_all_ips(void);
    void remove_duplicates(void);
    void clean_ports(void);

    std::vector<std::string> current_group;
    int group_size = 0, group_rate = 0, max_group_size = 0;
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
