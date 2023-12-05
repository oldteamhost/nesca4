/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#ifndef PRINTS_H
#define PRINTS_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <map>

#include "../include/nescautils.h"
#include "../ncsock/include/ip.h"
#include "../ncsock/include/tcp.h"
#include "../ncsock/include/readpkt.h"
#include "../ncsock/include/igmp.h"
#include "../ncsock/libdnet/include/eth.h"
#include "../ncsock/include/udp.h"

class nesca_prints {
  private:
  std::string gray_nesca = "\033[38;2;107;107;107m";
  std::string golder_rod = "\033[38;2;218;165;32m";
  std::string sea_green = "\033[38;2;60;179;96;4m";
  std::string green_html = "\033[38;2;127;255;0m";
  std::string red_html = "\033[38;2;240;50;55m";
  std::string yellow_html = "\033[38;2;255;255;0m";
  std::string reset_color = "\033[0m";

  std::string
  html_to_ansi_color(const std::string& html_color);
  void log_iphdr(struct ip_header *iphdr);
  void log_tcphdr(const struct tcp_header *tcphdr);
  void log_udphdr(struct udp_header *udphdr);
  void log_icmphdr(struct icmp4_header *icmphdr);
  void log_igmphdr(struct igmp_header *igmphdr);
  void log_ethhdr(struct eth_hdr *ethhdr);

  public:
    bool html_save;
    bool colors = true;
    std::map<std::string, std::string> config_values;
    std::string html_file_path;

    #define __RESET_COLOR "\033[0m"
    #define reset_colors printf(__RESET_COLOR)
    #define print_get_time(time) ("[" + std::string(time) + "]")

    void run_log();

    std::string main_nesca_out(const std::string& opt, const std::string& result, const int mode, const std::string& opt1, const std::string& opt2,
        const std::string& result1, const std::string& result2, const std::string& rtt,
        std::string type = "n/", std::string protocol = "a");

    void nlog_trivial(const std::string& message);
    void nlog_error(const std::string& message);
    void nlog_result(const std::string& message);
    void nlog_custom(const std::string& auth, std::string message, int color);

    void nlog_packet_trace(std::string action, std::string protocol, std::string& source_ip,
        std::string& dest_ip, int source_port, int dest_port,
        std::string message, int ttl, int id, int win, int seq, int iplen);

    void easy_packet_trace(u8 *buffer, bool hidden_eth);

    void disable_colors(void);
    void golder_rod_on(void);
    void sea_green_on(void);
    void green_html_on(void);
    void gray_nesca_on(void);
    void yellow_html_on(void);
    void red_html_on(void);

    void custom_color_on(const std::string& html_color);
    int import_color_scheme(const std::string& file_name, std::map<std::string, std::string>& config_values);
    int processing_color_scheme(const std::map<std::string, std::string>& config_values);
    void printcolorscheme(void);
};

class html_output {
private:
  std::string style_nesca3 = R"(
  <style>
    #recvSpan {
      display: inline-block;
      width: 150px;
    }
    #hostSpan {
      display: inline-block;
      width: 200px;
    }
    body {
      background-color: #141414;
      font-family: monospace;
      font-size: 95%;
    }
    #ipd {
      background: black;
      width: 100%;
      white-space: nowrap;
      overflow-x: none;
      display: inline-block;
    }
    #ipd:hover {
      color: #909090;
      background: #202020;
    }
    #tit {
      text-align: center;
      border: 1px solid #5d5d5d;
    }
    a {
      color: gray;
      text-decoration: underline;
    }
    a:focus {
      outline-style: dashed;
      outline-width: 1px;
      outline-color: red;
    }
  </style>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <title>output</title>

  <div id="tit">
  <a href="http://oldteamhost.ru">.oldteam</a>
  </div>
  )";

public:
  int html_main_init(const std::string& filepath);

  int html_pre_init(const std::string& filepath);

  int html_add_result(const std::string& filepath, const std::string& time, const std::string& href, const std::string& text,
    const std::string& opt, const std::string& res, const std::string& opt1, const std::string& res1,
    const std::string& opt2, const std::string& res2, const std::string& opt3, const std::string& res3);
};

#endif

