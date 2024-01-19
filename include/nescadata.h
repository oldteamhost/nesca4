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
#include "../ncsock/include/types.h"

struct _portlist_
{
  u16 port;
  short state;
};

struct payload
{
  const char *data;
  u32 datalen;
};

struct _nescadata_
{
  std::string ip;
  double rtt;            /* Время ответа хоста, после ping-а */
  bool rtt_init;         /* Иногда ping может просто skip-утся поэтому
                            нужен флаг для отслежки этого */
  std::string dns;       /* DNS который указал пользователь при
                            вызове ./nesca4 google.com */
  std::string new_dns;   /* DNS который получила nesca */
  std::string html;      /* Результат send_http_request() */
  std::string redirect;  /* Перенаправление */

  /* Сами порты */
  std::vector<_portlist_> ports;
};

class NESCADATA {
  private:
    std::vector<_nescadata_> all_data;
    std::vector<std::string> temp_ips_group;
    _nescadata_* get_data_block(const std::string& ip);
    void         delete_data_block(const std::string& ip);

  public:
    std::vector<std::string> success_ping_ip;
    std::vector<std::string> failed_ping_ip;
    struct payload pd;

    char gateway_ip[16];
    char srcmac[18];
    const char* source_ip;
    char dev[512];
    u32 src;

    int ping_timeout = 600;

    int temp_ack_port = 0;
    int temp_syn_port = 0;
    int temp_udp_port = 0;
    int temp_sctp_port = 0;

    std::vector<int> ack_ping_ports = {80};
    std::vector<int> syn_ping_ports = {80};
    std::vector<int> sctp_ping_ports = {80};
    std::vector<int> udp_ping_ports = {53};

    int frag_mtu = 0;
    int sport = -1;

    int brute_timeout = -1;
    int brute_threads = 5;
    int brute_maxcon = 10;
    int brute_attempts = 2;

    bool badsum = false;
    bool adler32sum = false;
    bool customttl = false;
    bool customsport = false;

    u8 ip_options[256];
    int ipopts_first_hop_offset = 0,
        ipopts_last_hop_offset = 0, ipoptslen;

    u8 tcpflags;

    std::vector<std::string> ftp_logins;
    std::vector<std::string> ftp_passwords;
    std::vector<std::string> rtsp_logins;
    std::vector<std::string> rtsp_passwords;
    std::vector<std::string> sftp_logins;
    std::vector<std::string> sftp_passwords;
    std::vector<std::string> http_logins;
    std::vector<std::string> http_passwords;
    std::vector<std::string> hikvision_logins;
    std::vector<std::string> hikvision_passwords;
    std::vector<std::string> smtp_logins;
    std::vector<std::string> smtp_passwords;
    std::vector<std::string> rvi_logins;
    std::vector<std::string> rvi_passwords;

    u16 windowlen = 0;
    u32 ack = 0;
    u16 ttl = 64;

    /* add data */
    void add_redirect(const std::string& ip, const std::string& redirect);
    void add_html(const std::string& ip, const std::string& html);
    void add_port(const std::string& ip, u16 port, short state);
    void add_ip(const std::string& ip);

    /* set data */
    void set_dns(const std::string& ip, const std::string& dns);
    void set_rtt(const std::string& ip, double rtt);
    void set_new_dns(const std::string& ip, const std::string& new_dns);

    /* get data */
    std::string  get_html(const std::string& ip);
    std::string  get_redirect(const std::string& ip);
    std::string  get_new_dns(const std::string& ip);
    std::string  get_dns(const std::string& ip);
    short        get_port_state(const std::string& ip, u16 port);
    double       get_rtt(const std::string& ip);
    std::vector<u16>         get_port_list(const std::string& ip, short state);
    std::vector<std::string> get_all_ips(void);

    /* utils */
    void sort_ips_rtt(std::vector<std::string>& ips);
    bool find_port_status(const std::string& ip, short state);
    void update_data_from_ips(const std::vector<std::string>& updated_ips);
    void negatives_hosts(const std::vector<std::string> ips);
    void remove_duplicates(void);
    void clean_ports(void);
    void print_datablock(const std::string &ip);
    void printall_datablock(void);
};

std::vector<std::string> cidr_to_ips(const std::vector<std::string>& cidr_list);
std::vector<std::string> range_to_ips(const std::vector<std::string>& ip_ranges);
std::vector<std::string> convert_dns_to_ip(const std::vector<std::string>& dns_vector);
std::vector<int> split_string_int(const std::string& str, char delimiter);
std::vector<std::string> split_string_string(const std::string& str, char delimiter);

#endif
