/*
 * Copyright (c) 2024, oldteam. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef NESCADATAHDR
#define NESCADATAHDR

#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <map>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <regex>
#include <linux/rtnetlink.h>
#include <cctype>
#include <array>
#include <stdio.h>
#include <ifaddrs.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <getopt.h>
#include <fstream>

#include "../libncsnet/ncsnet/sys/types.h"
#include "../libncsnet/ncsnet/cidr.h"
#include "../libncsnet/ncsnet/hex.h"
#include "../libncsnet/ncsnet/intf.h"
#include "../libncsnet/ncsnet/dns.h"
#include "../libncsnet/ncsnet/ip.h"
#include "../libncsnet/ncsnet/arp.h"
#include "../libncsnet/ncsnet/linuxread.h"

#include "nescaprint.h"

#define IDOPT_HELP      0
#define IDOPT_IMPORT    1
#define IDOPT_GMAX      2
#define IDOPT_GMIN      3
#define IDOPT_GPLUS     4
#define IDOPT_PE        5
#define IDOPT_PI        6
#define IDOPT_PM        7
#define IDOPT_PS        8
#define IDOPT_PA        9
#define IDOPT_PY        10
#define IDOPT_PU        11
#define IDOPT_RADNOM_IP 12
#define IDOPT_DEV       13
#define IDOPT_IP4       14
#define IDOPT_IP6       15
#define IDOPT_SRC       16
#define IDOPT_DST       17
#define IDOPT_DLEN      18
#define IDOPT_DHEX      19
#define IDOPT_DSTR      20
#define IDOPT_TTL       21
#define IDOPT_OFF       22
#define IDOPT_IPOPT     23
#define IDOPT_BADSUM    24
#define IDOPT_CFG       25
#define IDOPT_N         26
#define IDOPT_N_PING    27
#define IDOPT_WAIT_PING 28
#define IDOPT_NUM_PING  29
#define IDOPT_PR        30
#define IDOPT_ALL_PING  31
#define IDOPT_SYN       32
#define IDOPT_P         33
#define IDOPT_SN        34
#define IDOPT_XMAS      35
#define IDOPT_FIN       36
#define IDOPT_PSH       37
#define IDOPT_NULL      38
#define IDOPT_ACK       39
#define IDOPT_WINDOW    40
#define IDOPT_MAIMON    41
#define IDOPT_INIT      42
#define IDOPT_COOKIE    43
#define IDOPT_UDP       44
#define IDOPT_WAIT_SCAN 45
#define IDOPT_MTPL_SCAN 46
#define IDOPT_PPS       47
#define IDOPT_STATS     48
#define IDOPT_MAXFDS    49
#define IDOPT_ALL_SCAN  50
#define IDOPT_NUM_SCAN  51
#define IDOPT_S         52
#define IDOPT_DETAL     53
#define IDOPT_V         54
#define IDOPT_HTML      55
#define IDOPT_WIN       56
#define IDOPT_ACKN      57
#define IDOPT_DBPATH    58
#define IDOPT_N_DB      59
#define IDOPT_N_BRUTE   60
#define IDOPT_LOGIN     61
#define IDOPT_PASS      62
#define IDOPT_WAIT_BRUTE 63
#define IDOPT_DELAY_BRUTE 64
#define IDOPT_THREADS_BRUTE 65
#define IDOPT_ADLER32   66
#define IDOPT_ONLYOPEN  67

#define SPLITOPT_DEL   ','

#define OPENCLOSEOPT   '\''
#define SPECOPT        '\\'
#define ENDOPT         ';'
#define ASSIGNMENTVAL  '='
#define INCLUDE_TOKEN  "INCLUDE"
#define _ERRBUFMAXLEN   1024

#define S_NUM           2
#define S_HTTP          0
#define S_FTP           1

#define DEFAULT_SERVICES_PATH "resources/nesca-services"
#define DEFAULT_DATABASE_PATH "resources/nesca-database"

class NESCADATA;
typedef __uint128_t u128;


/*
 * Structure to represent time for purposes, can be
 * used to represent rtt.
 */
struct NESCATIME {
  struct timeval tstamp1, tstamp2;
  int type;
};


/*
 * A structure to represent any information, can be used
 * to represent information about services, bruteforcing,
 * etc.
 */
struct NESCAINFO {
  std::string info, type;
};


/*
 * A structure for representing a service, stores information,
 * times, and the service itself. For example, http, ftp and
 * etc.
 */
struct NESCASERVICE {
  std::vector<NESCAINFO> info;
  NESCATIME rtt;
  int service;
  bool init;
};


/*
 * The structure for representing a port contains the services of that
 * port, its status (state), the method by which it was received, the
 * protocol (proto), and the port itself.
 */
struct NESCAPORT {
  std::vector<NESCASERVICE> services;
  int state, method, proto, port, num;
};


/*
 * A structure to represent the result of database detection.
 */
struct NESCADBRES {
  std::string info, find;
};


/*
 * A structure for storing information that is needed to bruteforce
 * the service.
 */
struct NESCABRUTEI
{
  int service, port;
  std::string other;
};




/*
 * The class to represent the target, this is the main class for it. It
 * stores all the results of any scans, for example after a ports scan
 * the ports vector may be filled, and after a dns resolution the dns
 * vector may be filled. And so on.
 */
class NESCATARGET
{
  std::string               mainip;
  std::vector<std::string>  ips, dns;
  std::vector<NESCAPORT>    ports;
  std::vector<NESCATIME>    rtts;
  std::vector<NESCADBRES>   dbresults;
  bool                      ip6, ok=0;
  std::string               mac; /* from arp ping */
  std::vector<NESCABRUTEI>  bruteforce;

public:
  void add_service(NESCAPORT *port, int service,
    struct timeval tstamp1, struct timeval tstamp2);
  void add_info_service(NESCAPORT *port, int service,
      const std::string &info, const std::string type);
  NESCASERVICE get_service(NESCAPORT *port, int service);
  bool check_service(void);
  bool is_ip6host(void);
  void add_ip(const std::string &ip);
  void add_dns(const std::string &dns);
  void add_mac(const std::string &mac);
  void add_port(int state, int method, int proto,
    int port);
  bool portcompare(NESCAPORT *first, NESCAPORT *second);
  NESCAPORT get_port(size_t id);
  NESCAPORT *get_real_port(size_t id);
  size_t get_num_port(void);
  std::string get_mac(void);
  size_t get_num_ip(void);
  size_t get_num_dns(void);
  bool openports(void);
  bool initservices(void);
  std::string get_ip(size_t id);
  std::string get_dns(size_t id);
  std::string get_mainip(void);
  void add_time(struct timeval tstamp1,
    struct timeval tstamp2, int type);
  long long get_time_ns(size_t id);
  NESCATIME get_time(size_t id);
  size_t get_num_time(void);
  size_t get_type_time(size_t id);
  void set_ok(void);
  void set_no_ok(void);
  void set_bruteforce(int service, int port, const std::string &other);
  NESCABRUTEI get_bruteforce(size_t id);
  size_t get_num_bruteforce(void);
  bool isok(void);
  void removedublports(void);
  void add_dbres(const std::string &info, const std::string &find);
  size_t get_num_dbres(void);
  NESCADBRES get_dbres(size_t id);
};

struct _cfgopt {
  int id;
  std::string name, val;
  bool nullval;
};




/*
 * A class for representing, storing and manipulating nesca4 options. Parses
 * them both from the start line and from the config. For each option a
 * variable is created to set its flag. A variable for its parameter, if
 * it exists, can be checked via is_required_options(). Functions are
 * created for these variables to work with them, it may be a bit complicated,
 * but it ensures accuracy. Functions and variables have the following syntax.
 *
 * <opt>_flag
 * <opt>_param
 *
 * set_<opt>_flag
 * set_<opt>_param
 * get_<opt>_param
 * check_<opt>_flag
 */
class NESCAOPTS
{
  NESCAPRINT *ncsprint;

  std::string import_param;
  bool import_flag;

  size_t gmax_param, gmin_param, gplus_param;
  bool gmax_flag, gmin_flag, gplus_flag;

  std::vector<int> ps_param, pa_param, py_param, pu_param;
  bool pe_flag, pi_flag, pm_flag, ps_flag, pa_flag, py_flag, pu_flag, pr_flag;

  bool random_ip_flag;
  size_t random_ip_param;

  bool dev_flag, ip4_flag, ip6_flag, src_flag, dst_flag;
  std::string dev_param, ip4_param, ip6_param, src_param, dst_param;

  bool dlen_flag, dhex_flag, dstr_flag;
  std::string dlen_param, dhex_param, dstr_param;

  bool ttl_flag;
  std::string ttl_param;

  bool off_flag;
  std::string off_param;

  bool dbpath_flag;
  std::string dbpath_param;

  bool ipopt_flag;
  std::string ipopt_param;

  bool win_flag;
  std::string win_param;

  bool ackn_flag;
  std::string ackn_param;

  bool badsum_flag;

  bool cfg_flag;
  std::string cfg_param;

  bool login_flag;
  std::string login_param;

  bool pass_flag;
  std::string pass_param;

  bool wait_brute_flag;
  std::string wait_brute_param;

  bool delay_brute_flag;
  std::string delay_brute_param;

  bool n_flag;

  bool adler32_flag;

  bool n_ping_flag;

  bool wait_ping_flag;
  std::string wait_ping_param;

  bool num_ping_flag;
  std::string num_ping_param;

  bool all_ping_flag;

  bool syn_flag;

  bool p_flag;
  std::vector<NESCAPORT> p_param;

  bool sn_flag;

  bool xmas_flag;

  bool onlyopen_flag;

  bool fin_flag;

  bool null_flag;

  bool psh_flag;

  bool ack_flag;

  bool window_flag;

  bool maimon_flag;

  bool init_flag;

  bool cookie_flag;

  bool udp_flag;

  bool wait_scan_flag;
  std::string wait_scan_param;

  bool mtpl_scan_flag;
  std::string mtpl_scan_param;

  bool pps_flag;
  std::string pps_param;

  bool stats_flag;

  bool maxfds_flag;
  std::string maxfds_param;

  bool all_scan_flag;

  bool num_scan_flag;
  std::string num_scan_param;

  bool s_flag;
  std::vector<NESCAPORT> s_param;

  bool detal_flag;

  bool v_flag;

  bool html_flag;
  std::string html_param;

  bool n_db_flag;

  bool threads_brute_flag;
  std::string threads_brute_param;

  bool n_brute_flag;

  std::vector<_cfgopt> opts;
  std::string cfgpath;
  void opts_apply(int rez, std::string val);
  bool parse_cfgopt(std::string line, struct _cfgopt *res, char *errbuf);
  bool parse_cfg(std::vector<std::string> file, char *errbuf);
  bool parse_preproc(std::vector<std::string> file, char *errbuf);
  bool include_apply(struct _cfgopt *res, char *errbuf);

public:
  std::string runcmd;

  void opts_init(void);
  void args_apply(int argc, char **argv, NESCADATA *ncsdata, NESCAPRINT *ncsprint);
  void cfg_apply(const std::string &path, NESCADATA *ncsdata, NESCAPRINT *ncsprint);
  bool is_requiread_options(const std::string &opt);
  void opts_validate(void);

  void        set_import_flag(void);
  void        set_import_param(const std::string &import_param);
  std::string get_import_param(void);
  bool        check_import_flag(void);
  void        set_gmax_flag(void);
  void        set_gmin_flag(void);
  void        set_gplus_flag(void);
  void        set_gmax_param(size_t gmax_param);
  void        set_gmin_param(size_t gmin_param);
  void        set_gplus_param(size_t gplus_param);
  size_t      get_gmax_param(void);
  size_t      get_gmin_param(void);
  size_t      get_gplus_param(void);
  bool        check_gmax_flag(void);
  bool        check_gmin_flag(void);
  bool        check_gplus_flag(void);
  void        set_pe_flag(void);
  void        set_pi_flag(void);
  void        set_pm_flag(void);
  void        set_ps_flag(void);
  void        set_pa_flag(void);
  void        set_pr_flag(void);
  void        set_py_flag(void);
  void        set_pu_flag(void);
  void        set_ps_param(const std::string &ps_param);
  void        set_pa_param(const std::string &pa_param);
  void        set_py_param(const std::string &py_param);
  void        set_pu_param(const std::string &pu_param);
  std::vector<int> get_ps_param(void);
  std::vector<int> get_pa_param(void);
  std::vector<int> get_py_param(void);
  std::vector<int> get_pu_param(void);
  bool        check_pr_flag(void);
  bool        check_pe_flag(void);
  bool        check_pi_flag(void);
  bool        check_pm_flag(void);
  bool        check_ps_flag(void);
  bool        check_pa_flag(void);
  bool        check_py_flag(void);
  bool        check_pu_flag(void);
  void        set_random_ip_flag(void);
  void        set_random_ip_param(size_t random_ip_param);
  size_t      get_random_ip_param(void);
  bool        check_random_ip_flag(void);
  void        set_dev_flag(void);
  void        set_ip4_flag(void);
  void        set_ip6_flag(void);
  void        set_src_flag(void);
  void        set_dst_flag(void);
  void        set_dev_param(const std::string &dev_param);
  void        set_ip4_param(const std::string &ip4_param);
  void        set_ip6_param(const std::string &ip6_param);
  void        set_src_param(const std::string &src_param);
  void        set_dst_param(const std::string &dst_param);
  std::string get_dev_param(void);
  std::string get_ip4_param(void);
  std::string get_ip6_param(void);
  std::string get_src_param(void);
  std::string get_dst_param(void);
  bool        check_dev_flag(void);
  bool        check_ip4_flag(void);
  bool        check_ip6_flag(void);
  bool        check_src_flag(void);
  bool        check_dst_flag(void);
  void        set_dlen_flag(void);
  void        set_dhex_flag(void);
  void        set_dstr_flag(void);
  void        set_dlen_param(const std::string &dlen_param);
  void        set_dhex_param(const std::string &dhex_param);
  void        set_dstr_param(const std::string &dstr_param);
  std::string get_dlen_param(void);
  std::string get_dhex_param(void);
  std::string get_dstr_param(void);
  bool        check_dlen_flag(void);
  bool        check_dhex_flag(void);
  bool        check_dstr_flag(void);
  void        set_ttl_flag(void);
  void        set_off_flag(void);
  void        set_ipopt_flag(void);
  void        set_ttl_param(const std::string &ttl_param);
  void        set_off_param(const std::string &off_param);
  void        set_ipopt_param(const std::string &ipopt_param);
  std::string get_ttl_param(void);
  std::string get_off_param(void);
  std::string get_ipopt_param(void);
  bool        check_ttl_flag(void);
  bool        check_off_flag(void);
  bool        check_ipopt_flag(void);
  void        set_badsum_flag(void);
  bool        check_badsum_flag(void);
  void        set_cfg_flag(void);
  void        set_cfg_param(const std::string &cfg_param);
  std::string get_cfg_param(void);
  bool        check_cfg_flag(void);
  void        set_n_flag(void);
  bool        check_n_flag(void);
  void        set_n_ping_flag(void);
  bool        check_n_ping_flag(void);
  void        set_wait_ping_flag(void);
  void        set_wait_ping_param(const std::string &wait_ping_param);
  std::string get_wait_ping_param(void);
  bool        check_wait_ping_flag(void);
  void        set_num_ping_flag(void);
  void        set_num_ping_param(const std::string &num_ping_param);
  std::string get_num_ping_param(void);
  bool        check_num_ping_flag(void);
  void        set_all_ping_flag(void);
  bool        check_all_ping_flag(void);
  void        set_syn_flag(void);
  bool        check_syn_flag(void);
  void        set_p_param(const std::string &p_param);
  std::vector<NESCAPORT> get_p_param(void);
  void        set_p_flag(void);
  bool        check_p_flag(void);
  void        set_sn_flag(void);
  bool        check_sn_flag(void);
  void        set_xmas_flag(void);
  bool        check_xmas_flag(void);
  void        set_fin_flag(void);
  bool        check_fin_flag(void);
  void        set_null_flag(void);
  bool        check_null_flag(void);
  void        set_psh_flag(void);
  bool        check_psh_flag(void);
  void        set_ack_flag(void);
  bool        check_ack_flag(void);
  void        set_window_flag(void);
  bool        check_window_flag(void);
  void        set_maimon_flag(void);
  bool        check_maimon_flag(void);
  void        set_init_flag(void);
  bool        check_init_flag(void);
  void        set_cookie_flag(void);
  bool        check_cookie_flag(void);
  void        set_udp_flag(void);
  bool        check_udp_flag(void);
  void        set_wait_scan_flag(void);
  void        set_wait_scan_param(const std::string &wait_scan_param);
  std::string get_wait_scan_param(void);
  bool        check_wait_scan_flag(void);
  void        set_mtpl_scan_flag(void);
  void        set_mtpl_scan_param(const std::string &mtpl_scan_param);
  std::string get_mtpl_scan_param(void);
  bool        check_mtpl_scan_flag(void);
  void        set_pps_flag(void);
  void        set_pps_param(const std::string &pps_param);
  std::string get_pps_param(void);
  bool        check_pps_flag(void);
  void        set_stats_flag(void);
  bool        check_stats_flag(void);
  void        set_maxfds_flag(void);
  void        set_maxfds_param(const std::string &maxfds_param);
  std::string get_maxfds_param(void);
  bool        check_maxfds_flag(void);
  void        set_all_scan_flag(void);
  bool        check_all_scan_flag(void);
  void        set_num_scan_flag(void);
  void        set_num_scan_param(const std::string &num_scan_param);
  std::string get_num_scan_param(void);
  bool        check_num_scan_flag(void);
  void        set_s_flag(void);
  void        set_s_param(const std::string &s_param);
  std::vector<NESCAPORT> get_s_param(void);
  bool        check_s_flag(void);
  void        set_detal_flag(void);
  bool        check_detal_flag(void);
  void        set_v_flag(void);
  bool        check_v_flag(void);
  void        set_html_param(const std::string &html_param);
  std::string get_html_param(void);
  void        set_html_flag(void);
  bool        check_html_flag(void);
  void        set_win_param(const std::string &win_param);
  std::string get_win_param(void);
  void        set_win_flag(void);
  bool        check_win_flag(void);
  void        set_ackn_param(const std::string &ackn_param);
  std::string get_ackn_param(void);
  void        set_ackn_flag(void);
  bool        check_ackn_flag(void);
  void        set_n_db_flag(void);
  bool        check_n_db_flag(void);
  void        set_dbpath_param(const std::string &dbpath_param);
  std::string get_dbpath_param(void);
  void        set_dbpath_flag(void);
  bool        check_dbpath_flag(void);
  void        set_login_param(const std::string &login_param);
  std::string get_login_param(void);
  void        set_login_flag(void);
  bool        check_login_flag(void);
  void        set_pass_param(const std::string &pass_param);
  std::string get_pass_param(void);
  void        set_pass_flag(void);
  bool        check_pass_flag(void);
  void        set_wait_brute_param(const std::string &wait_brute_param);
  std::string get_wait_brute_param(void);
  void        set_wait_brute_flag(void);
  bool        check_wait_brute_flag(void);
  void        set_n_brute_flag(void);
  bool        check_n_brute_flag(void);
  void        set_delay_brute_param(const std::string &delay_brute_param);
  std::string get_delay_brute_param(void);
  void        set_delay_brute_flag(void);
  bool        check_delay_brute_flag(void);
  void        set_adler32_flag(void);
  bool        check_adler32_flag(void);

  void        set_threads_brute_param(const std::string &threads_brute_param);
  std::string get_threads_brute_param(void);
  void        set_threads_brute_flag(void);
  bool        check_threads_brute_flag(void);

  void        set_onlyopen_flag(void);
  bool        check_onlyopen_flag(void);

};




/*
 * Class for presentation ipv4 range,
 *   0.0.0.0-255.255.255.255
 * and cidr,
 *   0.0.0.0/24
 */
class NESCARAWRANGEV4
{
  std::array<int,4>  start, end;
  size_t             last=1, len=0;
  bool               cidr=0;

  std::array<int,4>  ip4parse(const std::string& ip);
  std::string        ip4unparse(const std::array<int,4> &octets);
  void               init(const std::string &range);
  void               init_cidr(const std::string &cidr);
  void               setlen(void);

public:
  NESCARAWRANGEV4(const std::string &txt, bool cidr);
  std::vector<std::string> exportips(size_t start, size_t num);
  size_t getlen(void);
  size_t getlast(void);
};




/*
 * Class for presentation ipv6 range,
 *   0000:0000:0000:0000:0000:0000:0000:0000-
 *   ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff
 * and cidr,
 *   0000:0000:0000:0000:0000:0000:0000:0000/24
 */
class NESCARAWRANGEV6
{
  std::array<int, 8> start, end;
  u128               last=1, len=0;
  bool               cidr=0;

  std::string        ip6uncompact(const std::string &ipv6);
  std::array<int, 8> ip6parse(const std::string &ip);
  std::string        ip6unparse(const std::array<int,8> &octets);
  void               init(const std::string &range);
  void               init_cidr(const std::string &cidr);
  void               setlen(void);

public:
  NESCARAWRANGEV6(const std::string &txt, bool cidr);
  std::vector<std::string> exportips(u128 start, u128 num);
  u128 getlen(void);
  u128 getlast(void);
};




/*
 * A class for storing “raw” targets. It has a rather complex operation. The
 * load function loads targets from arguments, load_from_file from a file,
 * load_random_ips generates random targets. Then, the main unload function
 * returns a vector of ip's from these targets loaded by load functions.
 * This is quite complicated, because these targets may well be cidr, or
 * range, and loading it completely into a vector may not be the best idea,
 * because they may well have enough addresses to fill all the RAM. So they
 * need gradual loading, which is what this class does. It does not load
 * the targets completely, but gradually loads them as they are fetched,
 * either from a file, or from random, or from cidr, or from range.
 *
 *
 * For example the targets are as follows, 0.0.0.0.0-255.255.255.255.255. The
 * first run of unload on 2 targets, will return,
 *
 *  0.0.0.0
 *  0.0.0.1
 *
 * the rest of the ip in 0.0.0.0.0.0-255.255.255.255.255, have not yet
 * been fetched and even loaded into RAM.
 *
 * A second run of unload on the 3 targets, will return,
 *
 *  0.0.0.2
 *  0.0.0.3
 *  0.0.0.4
 *
 * And likewise with the following targets, [dns, ipv4, ipv6, cidripv4,
 * rangeipv4, cidripv6, rangeipv6] (Which may still be loaded from a file
 * during this process).
 */
class NESCARAWTARGETS
{
  size_t lastfileline=0, filelines=0, lastgroup6=0;
  std::vector<NESCARAWRANGEV6> grouptargets6;
  bool check_from_file=0, check_randomips=0;
  std::vector<NESCARAWRANGEV4> grouptargets;
  size_t lastip4=0, lastip6=0, lastgroup=0;
  std::map<std::string,std::string> dns;
  std::vector<std::string> ipv4, ipv6;
  std::string from_file="";
  ssize_t randomips=0;
  NESCADEVICE *ncsdev;
  NESCAPRINT *ncsprint;

  void processing(const std::vector<std::string> &targets);

  public:
  std::vector<std::string> unload(u128 num);
  u128 totlen(void);
  void load(int argc, char **argv, NESCAOPTS *ncsopts,
      NESCAPRINT *ncsprint, NESCADEVICE *dev);
  void load_from_file(size_t num);
  void load_random_ips(size_t num);
  std::string getdns(std::string ip);
};




/*
 * A class for representing a network interface, and getting it filled, etc. Gets
 * srcmac, dstmac, srcip4, srcip6, gateway4, gateway6 addresses from a specified
 * or found interface. You could even say that it stores data about the sender,
 * or device.
 */
class NESCADEVICE
{
  NESCAPRINT  *ncsprint;
  std::string  device;
  int          deviceindex;
  mac_t        srcmac, dstmac;
  ip4_t        srcip4, gateway4;
  ip6_t        srcip6, gateway6;
  bool         ip6=0, ip4=0;
  long long    send_at=0; /* time need for one sent */

  std::string getfileln(const std::string &path);
  std::vector<std::string> find_devices(void);
  bool is_okdevice(const std::string &device, bool err);
  void init_device(const std::string &device, NESCAOPTS *ncsopts);
  bool gateway4_at_all_costs(void);
  bool gateway6_at_all_costs(void);
  bool srcip6_at_all_costs(void);
  bool srcip4_at_all_costs(void);
  bool srcmac_at_all_costs(void);
  bool dstmac4_at_all_costs(void);
  void set_send_at(void);

  /* XXX */
  bool dstmac6_at_all_costs(void);

public:
  void init(NESCAPRINT *ncsprint=NULL,
      NESCAOPTS *ncsopts=NULL);

  std::string get_device(void);
  mac_t       get_srcmac(void);
  ip4_t       get_srcip4(void);
  ip6_t       get_srcip6(void);
  mac_t       get_dstmac(void);
  ip4_t       get_gateway4(void);
  ip6_t       get_gateway6(void);
  void        set_srcip4(const std::string &ip4);
  void        set_srcip6(const std::string &ip6);
  void        set_srcmac(const std::string &mac);
  void        set_dstmac(const std::string &mac);
  void        set_gateway4(const std::string &ip4);
  void        set_gateway6(const std::string &ip6);
  bool        check_ipv6(void);
  bool        check_ipv4(void);
  long long   get_send_at(void);
};



/*
 * The class for representing all data nesca4, combines all the previous
 * ones in itself, contains some useful functions for working with it.
 */
class NESCADATA
{
public:
  NESCARAWTARGETS           rawtargets;
  std::vector<NESCATARGET*> targets;
  NESCAOPTS                 opts;
  NESCADEVICE               dev;
  u128                      ok;
  bool                      tmplast;
  struct timeval            tstamp_s, tstamp_e;


  void add_target(const std::string &ip);
  std::vector<NESCATARGET*> get_oktargets(void);
  void set_all_targets_ok(void);
  void clear_targets(void);
};




/* other utils */
std::string util_bytesconv(size_t bytes);
std::string util_timediff(const struct timeval& start,
    const struct timeval& end);
std::string util_pps(const struct timeval& start,
    const struct timeval& end, size_t total);
bool isokport(NESCAPORT *p);
int enservicekey(int service, int port, int id);

#endif
