/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "../include/nesca4.h"
#include "../include/nescatesting.h"
#include "../include/nescautils.h"
#include "../include/nescahttp.h"
#include "../include/nescaengine.h"
#include "../ncsock/include/icmp.h"
#include "../ncsock/include/readpkt.h"
#include "../ncsock/include/utils.h"
#include "../ncsock/include/arp.h"
#include "../ncsock/include/eth.h"
#include "../ncsock/include/strbase.h"
#include "../ncsock/include/tcp.h"
#include "../ncsock/include/utils.h"
#include <arpa/inet.h>
#include <bits/getopt_core.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <netinet/in.h>
#include <set>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <vector>

nesca_prints np;
html_output ho;
services_nesca sn;
arguments_program argp;
readfiler rf;

#define HTTP_BUFLEN 65535

NESCADATA n;

const char* run;
std::mutex ls;
const char* short_options = "s:hl:vd:T:p:aS:n";


int main(int argc, char** argv)
{
  /*
    eth_addr_t src;
    const char* srcmac = "40:b0:76:47:8f:9a";
    char* temp = NULL;
    eth_t *s;
    ip_addreth_t daddr, saddr;

    maceth(srcmac, &src);
    inet_pton(AF_INET, "195.168.1.35", saddr.data);
    inet_pton(AF_INET, "142.250.150.113", daddr.data);

    temp = get_active_interface_name();
    s = eth_open(temp);

    send_arpreq_packet(s, src, saddr, daddr, ARP_OP_REQUEST);

    eth_close(s);
    if (temp)
      free(temp);
    return 0;
  return 0;
  */

  n.pd.data = "";
  n.pd.datalen = 0;

  char* templocalip = NULL;
  struct tcp_flags tf;

  run = argv[0];
  memset(&tf, 0, sizeof(struct tcp_flags));

  if (argc <= 1)
    usage(run);

  templocalip = get_local_ip();
  n.src = inet_addr(templocalip);
  free(templocalip);

  get_active_interface_name(n.dev, 512);
  get_gateway_ip(n.gateway_ip, sizeof(n.gateway_ip));
  get_local_mac(n.dev, n.srcmac);

  parse_args(argc, argv);

  if (!argp.scriptpath.empty()) {
    _interdata_ id;
    id.characters = 0;
    id.lines = 0;
    id.path = "";
    _preprocessor_ prepr;
    _scanner_ scane;
    _interpreter_ inter;
    _importfile_ filetemp(argp.scriptpath, &id);
    filetemp.loadfile();
    prepr.preprocessor(&id);
    scane.scanner(&id);
    inter.interpreter(&id, argp.no_verbose_script);
    exit(0);
  }

  pre_check();
  importfile();

  /* SET TCP FLAGS */

  if (argp.type != SCTP_INIT_SCAN && argp.type != SCTP_COOKIE_SCAN) {
    if (!argp.custom_tcpflags)
      tf = set_flags(argp.type);
    else
      tf = str_set_flags(argp.custom_res_tcpflags);
    n.tcpflags = set_tcp_flags(&tf);
  }

  /* GET HOSTS */

  if (optind < argc) {
    std::vector<std::string> temp_ips;
    temp_ips = split_string_string(argv[optind], ',');
    resolvhosts(true, temp_ips);
  }
  if (argp.random_ip)
    for (int i = 1; i <= argp.random_ip_count; i++)
      n.add_ip(generate_ipv4());
  std::vector<std::string> temp_vector = n.get_all_ips();

  /* WARNINGS */

  if (argp.no_scan && argp.ping_off) {
    np.nlog_error("-no-ping is not available with (-no-scan)\n");
    exit(1);
  }
  if (argp.custom_tcpflags){
    np.golder_rod_on();
    printf("-> syn: %d, ack: %d, rst: %d, fin: %d, psh: %d, urg: %d, cwr: %d, ece: %d\n",
            tf.syn, tf.ack, tf.rst, tf.fin, tf.psh, tf.urg, tf.cwr, tf.ece);
    reset_colors;
  }
  if (n.frag_mtu > 16) {
    np.golder_rod_on();
    printf("-> NOTE: Note that if (ihl * 4) < (mtu) then fragmentation will not be performed, it is better to use mtu not more than 16.\n");
    reset_colors;
  }
  if (n.pd.datalen > 1400) {
    np.golder_rod_on();
    puts("-> NOTE: Usually packages that have a payload greater than 1400 are rejected.");
    reset_colors;
  }
  if (temp_vector.size() > 50000 && argp.speed_type != 5) {
    np.golder_rod_on();
    std::cout << "-> NOTE: With your number of IPs - (" << temp_vector.size()
      << "), it is better to use speed (-S5), otherwise scanning may take longer.\n";
    reset_colors;
  }

  /* PING SPEED */

  if (!argp.custom_threads) {
    if (argp.my_life_my_rulez) {
      argp.threads_ping = temp_vector.size();
      n.ping_timeout = 250;
    }
    else {
      argp.threads_ping = calculate_threads(argp.speed_type, temp_vector.size());
      n.ping_timeout = calculate_ping_timeout(argp.speed_type);
    }
  }
  if (!argp.custom_ping) {
    if (argp.max_ping == true) {
      argp.syn_ping = true;
      argp.ack_ping = true;
      argp.echo_ping = true;
      argp.info_ping = true;
      argp.timestamp_ping = true;
      argp.sctp_ping_init = true;
      argp.udp_ping = true;
    }
    switch (argp.speed_type)
    {
      case 5:
        argp.ack_ping = true;
        break;
      case 4:
        argp.echo_ping = true;
        argp.ack_ping = true;
        break;
      case 3:
      case 2:
        argp.ack_ping = true;
        argp.syn_ping = true;
        argp.echo_ping = true;
        break;
      case 1:
        argp.syn_ping = true;
        argp.ack_ping = true;
        argp.echo_ping = true;
        argp.info_ping = true;
        argp.timestamp_ping = true;
        break;
    }
  }

  n.remove_duplicates();
  n.negatives_hosts(argp.exclude);

  /* NESCA SCAN */

  init_bruteforce();
  auto start_time_scan = std::chrono::high_resolution_clock::now();

  if (!argp.ping_off)
    PRENESCASCAN();
  else
    NESCASCAN(temp_vector);

  auto end_time_scan = std::chrono::high_resolution_clock::now();
  auto duration_scan = std::chrono::duration_cast<std::chrono::microseconds>(end_time_scan - start_time_scan);
  double duration = duration_scan.count() / 1000000.0;

  nescaend(argp.count_success_ips, duration);
  return 0;

}

struct nescalog_opts initlog(int total, int set, const std::string &name)
{
  nescalog_opts nlo{};
  nlo.total = total;
  nlo.set = set;
  nlo.name = name;
  return nlo;
}

void nesca_log(struct nescalog_opts *nlo, int complete)
{
  double procents;
  int set = nlo->set, total = nlo->total;
  if (complete % set == 0) {
    procents = (static_cast<double>(complete) / total) * 100;
    std::cout << np.main_nesca_out("/", nlo->name + " " + std::to_string(complete)+" out of "+
    std::to_string(total) + " Targets", 6, "", "", format_percentage(procents), "", "") << std::endl;
  }
}

void nescaend(int success, double res)
{
  np.golder_rod_on();
  std::cout << "-> NESCA finished " << success << " up IPs (success) in " << std::fixed << std::setprecision(2) << res << " seconds\n";
  reset_colors;
}

template<typename Func, typename... Args> void
nesca_group_execute(struct nescalog_opts *nlo, int threads, std::vector<std::string> group, Func&& func, Args&&... args)
{
  thread_pool pool(threads);
  std::vector<std::future<void>> futures;
  int complete = 0;

  for (const auto& t : group) {
    futures.emplace_back(pool.enqueue(std::forward<Func>(func), t, std::forward<Args>(args)...));
    if (futures.size() >= static_cast<size_t>(threads)) {
      for (auto& future : futures)
        future.get();
      futures.clear();
    }
    if (nlo) {
      complete++;
      nesca_log(nlo, complete);
    }
  }
  for (auto& future : futures)
    future.get();
}

void PRENESCASCAN(void)
{
  struct nescalog_opts nlo;
  std::vector<std::string> temp_vector;
  std::vector<std::string> group_vector;
  bool groupscan = false;
  int ipsnoscan = 0, groupsize = 0, i = 0,
      count = 0, end = 0;
  temp_vector = n.get_all_ips();

  ipsnoscan = temp_vector.size();
  groupsize = ipsnoscan / argp.group_del;

  if (groupsize  >= argp.maxg_ping)
    groupsize = argp.maxg_ping;

  if (temp_vector.size() >= (unsigned long int)argp.maxg_ping) {
    count = ipsnoscan / groupsize;
    groupscan = true;
  }
  else
    count = 1;

  for (int j = 0; j < count; j++) {
    if (groupscan) {
      group_vector.clear();
      end = (j == count - 1) ? ipsnoscan : (j + 1) * groupsize;
      for (; i < end; i++)
        group_vector.push_back(temp_vector[i]);
    }
    else
      group_vector = temp_vector;

    nlo = initlog(group_vector.size(), get_log(group_vector.size()), "Ping");
    nesca_group_execute(&nlo, argp.threads_ping, group_vector, nesca_ping);
    n.update_data_from_ips(n.failed_ping_ip);
    n.sort_ips_rtt(n.success_ping_ip);

    NESCASCAN(n.success_ping_ip);

    if (argp.no_scan)
      for (const auto& ip : n.success_ping_ip)
        if (!argp.ping_off || n.get_new_dns(ip) != "n/a")
          std::cout << np.main_nesca_out("READY", ip, 5, "rDNS", "RTT", n.get_new_dns(ip),
              std::to_string(n.get_rtt(ip))+"ms","") << std::endl;

    argp.count_success_ips += n.success_ping_ip.size();
    n.failed_ping_ip.clear();
    n.success_ping_ip.clear();
  }
  if (argp.no_scan)
    putchar('\n');
}

void NESCASCAN(std::vector<std::string>& temp_vector)
{
  std::vector<std::string> group_vector;
  std::vector<std::string> http_ips;
  nesca_host_details nhd;
  bool groupscan = false;
  int ipsnoscan, groupsize, i = 0,
      count = 0, end = 0;
  struct nescalog_opts nlo;

  ipsnoscan = temp_vector.size();
  groupsize = ipsnoscan / argp.group_del;

  if (groupsize  >= argp.maxg_scan)
    groupsize = argp.maxg_scan;

  if (temp_vector.size() >= (unsigned long int)argp.maxg_scan) {
    count = ipsnoscan / groupsize;
    groupscan = true;
  }
  else
    count = 1;

  for (int j = 0; j < count; j++) {
    if (groupscan) {
      group_vector.clear();
      end = (j == count - 1) ? ipsnoscan : (j + 1) * groupsize;
      for (; i < end; i++)
        group_vector.push_back(temp_vector[i]);
    }
    else
      group_vector = temp_vector;

    if (!argp.custom_threads_resolv)
      argp.dns_threads = calculate_threads(argp.speed_type, group_vector.size());
    if (argp.my_life_my_rulez)
      argp.dns_threads = group_vector.size();

    if (!argp.no_get_dns) {
      nlo = initlog(group_vector.size(), get_log(group_vector.size()), "Resolv");
      nesca_group_execute(&nlo, argp.dns_threads, group_vector, get_dns_thread);
    }

    if (argp.no_scan)
      continue;

    argp._threads = group_vector.size();
    if (argp._threads >= 3000)
      argp._threads = 3000;

    nlo = initlog(group_vector.size(), get_log(group_vector.size()), "SCAN");
    nesca_group_execute(&nlo, argp._threads, group_vector, nesca_scan, argp.ports, argp.timeout_ms);

    if (!argp.no_proc) {
      if (!argp.custom_http_threads)
        argp.http_threads = calculate_threads(argp.speed_type, group_vector.size());
      for (const auto& ip : group_vector) {
        std::vector<u16> openports = n.get_port_list(ip, PORT_OPEN);
        for (const auto& port : openports) {
          if (sn.probe_service(port) == "HTTP")
            http_ips.push_back(ip);
        }
      }
      nlo = initlog(http_ips.size(), get_log(http_ips.size()), "HTTP");
      nesca_group_execute(&nlo, argp.http_threads, http_ips, nesca_http, 80, argp.http_timeout);
    }
    for (const auto& ip : group_vector) {
      if (n.find_port_status(ip, PORT_OPEN) || argp.debug ||
          n.find_port_status(ip, PORT_OPEN_OR_FILTER) ||
          n.find_port_status(ip, PORT_NO_FILTER)) {

        std::cout << np.main_nesca_out("READY", ip, 5, "rDNS", "RTT",
            n.get_new_dns(ip), std::to_string(n.get_rtt(ip))+"ms","") << std::endl;

        if (argp.json_save) {
          nhd.ip_address = ip.c_str();
          nhd.rtt = n.get_rtt(ip);
          nhd.dns_name = n.get_new_dns(ip).c_str();
          nesca_json_save_host(argp.json_save_path, &nhd);
        }

        process_port(ip, n.get_port_list(ip, PORT_OPEN), PORT_OPEN);
        process_port(ip, n.get_port_list(ip, PORT_FILTER), PORT_FILTER);
        process_port(ip, n.get_port_list(ip, PORT_OPEN_OR_FILTER), PORT_OPEN_OR_FILTER);
        process_port(ip, n.get_port_list(ip, PORT_NO_FILTER), PORT_NO_FILTER);
        process_port(ip, n.get_port_list(ip, PORT_CLOSED), PORT_CLOSED);
        process_port(ip, n.get_port_list(ip, PORT_ERROR), PORT_ERROR);
        putchar('\n');

        if (argp.json_save) {
          nesca_json_close_info(argp.json_save_path);
          nesca_json_set_comma(argp.json_save_path);
          nesca_json_skip_line(argp.json_save_path);
        }
      }
    }
    n.clean_ports();
  }
  if (argp.json_save) {
    nesca_json_fix_file(argp.json_save_path);
    nesca_json_skip_line(argp.json_save_path);
    nesca_json_close_array(argp.json_save_path);
  }

  return;
}

/* Главная функция для сканировния портов */
void nesca_scan(const std::string& ip, std::vector<int>ports, const int timeout_ms)
{
  int res, sock, recvtime = 600;
  u8* packet;
  double rtt_ping;
  double temptime;
  u8 portstat = PORT_ERROR;
  struct sockaddr_in ip4;

  ip4.sin_family = AF_INET;
  ip4.sin_addr.s_addr = inet_addr(ip.c_str());

  if (argp.custom_recv_timeout_ms)
    recvtime = argp.recv_timeout_ms;
  else {
    rtt_ping = n.get_rtt(ip);
    if (rtt_ping != -1)
      recvtime = calculate_timeout(rtt_ping, argp.speed_type);
  }

  for (const auto& port : ports) {
    sock = nescasocket();
    if (sock == -1)
      continue;

    res = sendprobe(sock, &n, ip4.sin_addr.s_addr, port, argp.type);

    ls.lock();
    close(sock);
    ls.unlock();

    if (res == -1) {
      ls.lock();
      if (argp.print_errors)
        n.add_port(ip, port, PORT_ERROR);
      ls.unlock();
      continue;
    }

    packet = recvpacket(&n, ip4.sin_addr.s_addr, argp.type, recvtime, &temptime);
    if (!packet) {
      ls.lock();
      free(packet);
      ls.unlock();

      if (argp.type != TCP_SYN_SCAN && argp.type != TCP_ACK_SCAN && argp.type != TCP_WINDOW_SCAN) {
        ls.lock();
        n.add_port(ip, port, PORT_OPEN_OR_FILTER);
        ls.unlock();
      }
      else {
        ls.lock();
        if (argp.debug)
          n.add_port(ip, port, PORT_FILTER);
        ls.unlock();
      }
      continue;
    }

    portstat = readscan(ip4.sin_addr.s_addr, packet, argp.type);

    ls.lock();
    free(packet);
    n.add_port(ip, port, portstat);
    if (portstat)
      argp.count_success_ports++;
    ls.unlock();
  }
}

void nesca_ping(const std::string& ip)
{
  double rtt = -1;
  u32 dst;

  dst = inet_addr(ip.c_str());
  goto start;

check:
  if (rtt != -1) {
    ls.lock();
    n.set_rtt(ip, rtt);
    n.success_ping_ip.push_back(ip);
    ls.unlock();
    return;
  }
  else {
    ls.lock();
    n.failed_ping_ip.push_back(ip);
    ls.unlock();
    return;
  }

start:
  if (argp.ack_ping && rtt == -1)
    rtt = nescaping(&n, dst, TCP_PING_ACK);
  if (argp.echo_ping && rtt == -1)
    rtt = nescaping(&n, dst, ICMP_PING_ECHO);
  if (argp.syn_ping && rtt == -1)
    rtt = nescaping(&n, dst, TCP_PING_SYN);
  if (argp.info_ping && rtt == -1)
    rtt = nescaping(&n, dst, ICMP_PING_INFO);
  if (argp.timestamp_ping && rtt == -1)
    rtt = nescaping(&n, dst, ICMP_PING_TIME);
  if (argp.sctp_ping_init && rtt == -1)
    rtt = nescaping(&n, dst, SCTP_INIT_PING);
  if (argp.udp_ping && rtt == -1)
    rtt = nescaping(&n, dst, UDP_PING);

  goto check;
}

void nesca_http(const std::string& ip, const u16 port, const int timeout_ms)
{
  struct http_header hh = initheader("/", ip, "oldteam", "GET");
  send_http(&hh, n, ip, port, timeout_ms);
}

void processing_tcp_scan_ports(std::string ip, int port, int result)
{
  argp.result_success_ports++;
  argp.result_success_ip++;
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << n.get_rtt(ip);
  std::string rtt_log = stream.str(); std::string protocol = sn.probe_service(port);
  std::string result1 = ip + ":" + std::to_string(port);

  std::unique_ptr<ports_strategy> ports_strategy_;

  if (result == PORT_OPEN) {
    print_port_state(PORT_OPEN, port, argp.type, sn.probe_service(port), np);
    if (argp.no_proc)
      return;
    if (sn.probe_service(port) == "HTTP")
      ports_strategy_ = std::make_unique<http_strategy>();
    else if (port == 20 || port == 21)
      ports_strategy_ = std::make_unique<ftp_strategy>();
    else if (port == 554)
      ports_strategy_ = std::make_unique<rtsp_strategy>();
    else if (port == 37777)
      ports_strategy_ = std::make_unique<rvi_strategy>();
    else if (port == 8000)
      ports_strategy_ = std::make_unique<hikvision_strategy>();
    else if (port == 443)
      ports_strategy_ = std::make_unique<https_strategy>();
    else if (port == 25)
      ports_strategy_ = std::make_unique<smtp_strategy>();
    else
      ports_strategy_ = std::make_unique<else_strategy>();
    if (ports_strategy_)
      ports_strategy_->handle(ip, result1, rtt_log, protocol, port, argp, np, n, sn);
    if (argp.json_save) {
      nesca_port_details npd;
      npd.port = port;
      npd.protocol = protocol.c_str();
      npd.http_title = ports_strategy_->http_title.c_str();
      npd.screenshot = ports_strategy_->screenshot_base64.c_str();
      npd.content = "";
      npd.passwd = ports_strategy_->brute_temp.c_str();
      npd.type_target = ports_strategy_->type_target.c_str();
      nesca_json_save_port(argp.json_save_path, &npd);
    }
  }
  else if (result == PORT_ERROR) {
    if (argp.print_errors)
      print_port_state(PORT_ERROR, port, argp.type, sn.probe_service(port), np);
  }
  else if (result == PORT_CLOSED) {
    if (argp.debug)
      print_port_state(PORT_CLOSED, port, argp.type, sn.probe_service(port), np);
  }
  else if (result == PORT_FILTER) {
    if (argp.debug)
      print_port_state(PORT_FILTER, port, argp.type, sn.probe_service(port), np);
  }
  else if (result == PORT_OPEN_OR_FILTER) {
    print_port_state(PORT_OPEN_OR_FILTER, port, argp.type, sn.probe_service(port), np);
  }
  else if (result == PORT_NO_FILTER) {
    print_port_state(PORT_NO_FILTER, port, argp.type, sn.probe_service(port), np);
  }
}

void process_port(const std::string& ip, std::vector<uint16_t> ports, int port_type)
{
  int total_ports_to_process = ports.size();
  int port_count_on_this_ip = 0;

  for (const auto& port : ports) {
    processing_tcp_scan_ports(ip, port, port_type);
    if (port_count_on_this_ip != total_ports_to_process - 1 && argp.json_save) {
      nesca_json_set_comma(argp.json_save_path);
      nesca_json_skip_line(argp.json_save_path);
    }
    port_count_on_this_ip++;
  }
}

void fix_time(double time)
{
  std::cout << std::fixed <<
    std::setprecision(2) << time << "s";
}

std::vector<std::string> resolvhosts(bool datablocks, std::vector<std::string> hosts)
{
  char ipbuf[16];
  std::unordered_map<std::string,
    std::string> result;
  std::vector<std::string> ret;
  int temp, res;
  char* clean;

  for (const auto& t : hosts) {
    if (t.empty())
      continue;
    if (t == "localhost") {
      ret.push_back("127.0.0.1");
      n.add_ip("127.0.0.1");
    }
    else if (t == "route" || t == "gateway") {
      ret.push_back(n.gateway_ip);
      n.add_ip(n.gateway_ip);
    }
    else {

    temp = this_is(t.c_str());
    if (temp == CIDR) {
      std::vector<std::string> temp = cidr_to_ips({t});
      for (auto& tt : temp)
        result[tt] = "";
    }
    if (temp == RANGE) {
      std::vector<std::string> temp = range_to_ips({t});
      for (auto& tt : temp)
        result[tt] = "";
    }
    if (temp == _URL_) {
      clean = clean_url(t.c_str());
      if (!clean)
        continue;
      res = get_ip(clean, ipbuf, sizeof(ipbuf));
      if (res == -1)
        np.nlog_error("Failed to resolve \"" + std::string(clean)+ "\"\n");
      else
        result[ipbuf] = clean;
      free(clean);
      memset(ipbuf, 0, 16);
    }
    if (temp == DNS) {
      res = get_ip(t.c_str(), ipbuf, sizeof(ipbuf));
      if (res == -1)
        np.nlog_error("Failed to resolve \"" + std::string(t.c_str())+ "\"\n");
      else
        result[ipbuf] = t;
    }
    else
      result[t] = "";
    }
  }
  if (datablocks) {
    for (const auto& node : result) {
      n.add_ip(node.first);
      if (!node.second.empty())
        n.set_dns(node.first, node.second);
    }
  }
  for (const auto& node : result)
    ret.push_back(node.first);

  return ret;
}

void importfile(void)
{
  std::vector<std::string> temp_ips;
  if (!argp.ip_scan_import)
    return;

  if (check_file(argp.path_ips)) {
    np.golder_rod_on();
    std::cout << "-> Import file (" + std::string(argp.path_ips) + ") loaded " +
      std::to_string(get_count_lines(argp.path_ips)) + " entries\n";
    reset_colors;
  }
  else {
    np.nlog_error("Failed to import file, check path (" +
        std::string(argp.path_ips) + ")\n");
    exit(1);
  }
  temp_ips = write_file(argp.path_ips);
  resolvhosts(true, temp_ips);
}


void usage(const char* exec)
{
  puts("d8b   db d88888b .d8888.  .o88b.  .d8b.         j88D ");
  puts("888o  88 88'     88'  YP d8P  Y8 d8' `8b       j8~88 "); 
  puts("88V8o 88 88ooooo `8bo.   8P      88ooo88      j8' 88 ");
  puts("88 V8o88 88~~~~~   `Y8b. 8b      88~~~88      V88888D");
  puts("88  V888 88.     db   8D Y8b  d8 88   88          88 ");
  puts("VP   V8P Y88888P `8888Y'  `Y88P' YP   YP          VP \n");

  np.gray_nesca_on();
  std::cout << "[VERSION]:";
  np.green_html_on();
  std::cout << _VERSION << std::endl;
  np.gray_nesca_on();

  np.gray_nesca_on();
  std::cout << "[USAGE]:";
  np.green_html_on();
  std::cout << exec << " <hosts> <flags>" << std::endl;
  np.gray_nesca_on();

  np.golder_rod_on();
  std::cout << "\nTARGET SPECIFICATION:" << std::endl;
  reset_colors;
  std::cout << "  -import <inputfilename>: Set target(s) from file.\n";
  std::cout << "  -random-ip <num hosts>: Choose random target(s)\n";
  std::cout << "  -exclude <host1[,host2][,host3],...>: Exclude host(s).\n";
  std::cout << "  -excludefile <exclude_file>: Exclude list from file\n";

  np.golder_rod_on();
  std::cout << "PORT SCAN OPTIONS:" << std::endl;
  reset_colors;
  std::cout << "  -fin, -xmas, -null, -psh: Use one of these scanning methods.\n";
  std::cout << "  -ack, -windows -maimon: Use ack or window or maimon scan method.\n";
  std::cout << "  -scanflags <flags>: Customize TCP scan flag. Ex: (ACKSYN) > AS;\n";
  std::cout << "  -sctp-init, -sctp-cookie: Use SCTP INIT/COOKIE-ECHO scan method.\n";
  std::cout << "  -udp: On UDP scan method and udp ports.\n";
  std::cout << "  -p <port ranges>: Only scan specified port(s). \n    Ex: -p 80; -p 22,80; -p 1-65535;\n";
  std::cout << "  -delay, -d <ms>: Set delay for scan.\n";
  std::cout << "  -scan-timeout <ms>: Edit timeout for getting packet on port.\n";
  std::cout << "  -no-scan: Disable port scan(skip).\n";

  np.golder_rod_on();
  std::cout << "PING SCAN OPTIONS:" << std::endl;
  reset_colors;
  std::cout << "  -PS, -PA, -PY, -PU <port>: Use SYN|ACK|UDP|SCTP ping.\n";
  std::cout << "  -PE, -PI, -PM: Use ICMP ping ECHO|INFO|TIMESTAMP\n";
  std::cout << "  -TP <num>: Set max thread(s) for ping.\n";
  std::cout << "  -max-ping: Using all ping methods.\n";
  std::cout << "  -ping-timeout <ms>: Set recv timeout for ping.\n";
  std::cout << "  -no-ping: Skip ping scan.\n";

  np.golder_rod_on();
  std::cout << "HOST RESOLUTION:" << std::endl;
  reset_colors;
  std::cout << "  -TD <num>: Set max thread(s) for dns-resolution.\n";
  std::cout << "  -resol-port <port>: Edit source port for dns-resolution.\n";
  std::cout << "  -resol-delay <ms>: Set delay for dns-resolution.\n";
  std::cout << "  -no-resolv, -n: Skip dns-resolution.\n";

  np.golder_rod_on();
  std::cout << "BRUTEFORCE OPTIONS:" << std::endl;
  reset_colors;
  std::cout << "  -brute-login <ss,path>: Set path for <ss> logins.\n";
  std::cout << "  -brute-pass <ss,path>: Set path for <ss> passwords.\n";
  std::cout << "  -brute-delay <ms>: Edit brute timout.\n";
  std::cout << "  -no-brute <ss,2>: Disable <ss> bruteforce.\n";
  std::cout << "  -brute-verbose <ss,2>: Display bruteforce <ss> all info.\n";
  std::cout << "  -brute-log <ss,2>: Display bruteforce <ss> info.\n";

  np.golder_rod_on();
  std::cout << "FIREWALL/IDS EVASION AND SPOOFING:" << std::endl;
  reset_colors;
  std::cout << "  -data <hex>: Append a custom data to payload\n";
  std::cout << "  -data-string <string>: Append a custom ASCII string to payload.\n";
  std::cout << "  -data-len <num>: Append random data to payload.\n";
  std::cout << "  -saddr <ip>: Set custom source_ip.\n";
  std::cout << "  -sport <port>: Set custom source_port.\n";
  std::cout << "  -ipopt <R|S [route]|L [route]|T|U |[HEX]>: Adding ip option in packets.\n";
  std::cout << "  -frag <mtu>: Fragment all packets.\n";
  std::cout << "  -window <num>: Set custom window size.\n";
  std::cout << "  -badsum: Send packets with a bogus checksum.\n";
  std::cout << "  -ack <num>: Set custom ACK number.\n";
  std::cout << "  -ttl <num>: Set custom ip_header_ttl.\n";

  np.golder_rod_on();
  std::cout << "PROCCESSING SCAN:" << std::endl;
  reset_colors;
  std::cout << "  -TH <num>: Set max thread(s) for HTTP requests.\n";
  std::cout << "  -http-timeout <num>: Edit timeout for recv HTTP requests.\n";
  std::cout << "  -find <target1[,target2][,target3],...>: Search for keywords on the host.\n";
  std::cout << "  -http-response: Display HTTP response.\n";
  std::cout << "  -negatives <path>: Set custom path for negatives.\n";
  std::cout << "  -sitemap: Get /sitemap.xml.\n";
  std::cout << "  -robots: Get /robots.txt.\n";
  std::cout << "  -no-proc: Skip main processing.\n";

  np.golder_rod_on();
  std::cout << "SPEED OPTIONS:" << std::endl;
  reset_colors;
  std::cout << "  -speed, -S <1-5>: Set timing template (higher is faster).\n";
  std::cout << "  -gdel <num>: Edit groupsize delimetr (default 5).\n";
  std::cout << "  -maxg-ping <num>: Edit max len group for ping scan (default 3000).\n";
  std::cout << "  -maxg-scan <num>: Edit max len group for scan (default 2000).\n";
  std::cout << "  -my-life-my-rulez: Using very MAX speed settings.\n";

  np.golder_rod_on();
  std::cout << "OUTPUT:" << std::endl;
  reset_colors;
  std::cout << "  -html, -l <path file>: Classic nesca save, write on html page.\n";
  std::cout << "  -json <path file>: Save on json file.\n";
  std::cout << "  -debug, -db: On debug mode, display not even working hosts.\n";
  std::cout << "  -error, -er: On display all port errors.\n";
  std::cout << "  -no-color: Disable all colors in nesca4.\n";
  std::cout << "  -import-color <path>: Import color scheme from file.\n";
  std::cout << "  -print-color <path>: Check color scheme.\n";

  np.golder_rod_on();
  std::cout << "NETWORK TEST/SCRIPT:" << std::endl;
  reset_colors;
  std::cout << "  -script <path>: Running nesca interpreter.\n";
  std::cout << "  -no-verbose: Disable interpreter verbose.\n";

#ifdef HAVE_NODE_JS
  np.golder_rod_on();
  std::cout << "SAVE SCREENSHOTS:" << std::endl;
  reset_colors;
  std::cout << "  -screenshot, -s <folder>: Save screenshot on pages.\n";
  std::cout << "  -ss-timeout <ms>: Set timeout on save screenshots.\n";
#endif

  np.golder_rod_on();
  std::cout << "EXAMPLES:" << std::endl;
  reset_colors;
  std::cout << "  ./nesca4 google.com -p 80,443\n";
  std::cout << "  ./nesca4 72.230.205.0/24 -p 80,8080,81 -S5\n";
  std::cout << "  ./nesca4 https://www.youtube.com\n";
  exit(0);
}

void init_bruteforce(void)
{
  n.ftp_logins          = write_file(argp.path_ftp_login);
  n.ftp_passwords       = write_file(argp.path_ftp_pass);
  n.rtsp_logins         = write_file(argp.path_rtsp_login);
  n.rtsp_passwords      = write_file(argp.path_rtsp_pass);
  n.http_logins         = write_file(argp.path_http_login);
  n.http_passwords      = write_file(argp.path_http_pass);
  n.hikvision_logins    = write_file(argp.path_hikvision_login);
  n.hikvision_passwords = write_file(argp.path_hikvision_pass);
  n.smtp_logins         = write_file(argp.path_smtp_login);
  n.smtp_passwords      = write_file(argp.path_smtp_pass);
  n.rvi_logins          = write_file(argp.path_rvi_login);
  n.rvi_passwords       = write_file(argp.path_rvi_pass);
}

std::string format_percentage(double procents)
{
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(1) << procents << "%";
  std::string result = oss.str();
  return result;
}

void get_dns_thread(std::string ip)
{
  char dnsbuf[1024];
  std::string temp_dns;

  delayy(argp.resol_delay);
  get_dns(ip.c_str(), argp.resol_source_port, dnsbuf, sizeof(dnsbuf));
  temp_dns = dnsbuf;

  ls.lock();
  n.set_new_dns(ip, temp_dns);
  ls.unlock();
}

void
pre_check(void)
{
  if (check_ansi_support() != true) {
    std::cout << "You terminal don`t support ansi colors!\n";
    std::cout << "Colors disable!\n\n";
    np.disable_colors();
  }

  if (argp.import_color_scheme) {
    np.import_color_scheme(argp.path_color_scheme, np.config_values);
    np.processing_color_scheme(np.config_values);
  }

  char formatted_date[11];
  np.golder_rod_on();
  get_current_date(formatted_date, sizeof(formatted_date));
  std::cout << "-> Running NESCA [v" + std::string(_VERSION) + "] # " +
  std::string(get_time()) + " at " + formatted_date << std::endl; 
  reset_colors;

  if (argp.info_version)
    version_menu();

  if (argp.print_help_menu)
    usage(run);

  if (!check_root_perms()) {
    np.nlog_error("UNIX requires root permissions, to use raw sockets (sudo).\n");
    exit(1);
  }

  if (argp.ns_track) {
    std::filesystem::path directory_path= "ns_track";
    if (!std::filesystem::exists(directory_path))
      std::filesystem::create_directory(directory_path);

    argp.json_save = true;
    argp.save_screenshots = true;
    argp.json_save_path = "ns_track/data.json";
    argp.screenshots_save_path = "ns_track/";
  }

  if (np.html_save) {
    std::vector<std::string> temp = write_file("resources/data_html");
    auto it = std::find(temp.begin(), temp.end(), np.html_file_path);
    if (it == temp.end() || temp[0] == "-1")
      ho.html_main_init(np.html_file_path);
    else {
      if (!check_file(np.html_file_path.c_str()))
        ho.html_main_init(np.html_file_path);
    }
    ho.html_pre_init(np.html_file_path);
    write_temp(np.html_file_path, "resources/data_html");
  }

  if (argp.json_save) {
    std::vector<std::string> temp = write_file("resources/data_json");
    auto it = std::find(temp.begin(), temp.end(), argp.json_save_path);
    if (it != temp.end() && temp[0] != "-1") {
      if (check_file(argp.json_save_path)) {
        nesca_json_set_comma(argp.json_save_path);
        nesca_json_skip_line(argp.json_save_path);
      }
    }
    write_temp(argp.json_save_path, "resources/data_json");
  }

  if (!check_file("./resources/nesca-services"))
    std::cout << np.main_nesca_out("NESCA4", "SERVICES_DATA", 5, "status", "", "FAILED","","") << std::endl;
  else
    sn.init_services();

  if (!check_file(argp.negatives_path.c_str()))
    std::cout << np.main_nesca_out("NESCA4", "NEGATIVES_LOAD", 5, "status", "", "FAILED","","") << std::endl;
  else
    argp.nesca_negatives = get_negatives(argp.negatives_path);
}

void version_menu(void)
{
  logo();
  np.gray_nesca_on();
  std::cout << print_get_time(get_time());
  std::cout << "[VERSION]:";
  np.green_html_on();
  std::cout << _VERSION << std::endl;
  np.gray_nesca_on();
  std::cout << print_get_time(get_time());
  std::cout << "[INFO]:";
  np.sea_green_on();
  std::cout << "https://github.com/oldteamhost/nesca4" << std::endl;
  reset_colors;
  np.gray_nesca_on();
  std::cout << print_get_time(get_time());
  std::cout << "[NB]:";
  np.golder_rod_on();
  std::cout << "Not read \"do_not_read\"" << std::endl;
  reset_colors;
  std::cout << std::endl;
  exit(0);
}

int count_map_vector(const std::unordered_map<std::string, std::vector<int>>& map, const std::string& key)
{
  auto it = map.find(key);
  if (it != map.end())
    return it->second.size();

  return 0;
}

std::string randomstr(int len)
{
  int i;
  std::string res;
  const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  const int chlen = characters.length(); /* член */

  std::srand(static_cast<u32>(std::time(0)));
  for (i = 0; i < len; ++i) {
    char _char = characters[std::rand() % chlen];
    res += _char;
  }
  return res;
}

void parse_args(int argc, char** argv)
{
  int rez;
  int option_index = 0;

  while ((rez = getopt_long_only(argc, argv, short_options, long_options, &option_index)) != EOF) {
    switch (rez)
    {
      case 'h':
        argp.print_help_menu = true;
        break;
      case 'v':
        argp.info_version = true;
        break;
      case 'S':
        argp.speed_type = atoi(optarg);
        break;
      case 'p': {
        argp.ports_temp = optarg;
        argp.ports = write_ports(argp.ports_temp);
        if (argp.ports[0] == EOF) {
          size_t pos1 = argp.ports_temp.find("-");
          if (pos1 != std::string::npos)
            argp.ports = parse_range(optarg);
          else
            argp.ports = split_string_int(optarg, ',');
        }
        break;
      }
      case 12: {
        std::vector<std::string> what = split_string_string(optarg, ',');
        what[0] = to_lower_case(what[0]);
        what[1] = to_lower_case(what[1]);

        const char* what_convert = what[0].c_str();
        if (what[1] == "ftp")
          argp.path_ftp_login = what_convert;
        else if (what[1] == "rtsp")
          argp.path_rtsp_login = what_convert;
        else if (what[1] == "http")
          argp.path_http_login = what_convert;
        else if (what[1] == "smtp")
          argp.path_smtp_login = what_convert;
        else if (what[1] == "hikvision")
          argp.path_hikvision_login = what_convert;
        else if (what[1] == "rvi")
          argp.path_rvi_login = what_convert;
        else if (what[1] == "all") {
          argp.path_rvi_login = what_convert;
          argp.path_ftp_login = what_convert;
          argp.path_http_login = what_convert;
          argp.path_rtsp_login = what_convert;
          argp.path_smtp_login = what_convert;
          argp.path_hikvision_login = what_convert;
        }
        break;
      }
      case 11: {
        std::vector<std::string> what = split_string_string(optarg, ',');
        what[0] = to_lower_case(what[0]);
        what[1] = to_lower_case(what[1]);

        const char* what_convert = what[0].c_str();
        if (what[1] == "ftp")
          argp.path_ftp_pass = what_convert;
        else if (what[1] == "rtsp")
          argp.path_rtsp_pass = what_convert;
        else if (what[1] == "http")
          argp.path_http_pass = what_convert;
        else if (what[1] == "smtp")
          argp.path_smtp_pass = what_convert;
        else if (what[1] == "hikvision")
          argp.path_hikvision_pass = what_convert;
        else if (what[1] == "rvi")
          argp.path_rvi_pass = what_convert;
        else if (what[1] == "all") {
          argp.path_rvi_pass = what_convert;
          argp.path_ftp_pass = what_convert;
          argp.path_smtp_pass = what_convert;
          argp.path_rtsp_pass = what_convert;
          argp.path_http_pass = what_convert;
          argp.path_hikvision_pass = what_convert;
        }
        break;
      }
      case 30: {
        std::vector<std::string> what = split_string_string(optarg, ',');
        for (int i = 0; i < static_cast<int>(what.size()); i++) {
          what[i] = to_lower_case(what[i]);
          if (what[i] == "ftp")
            argp.ftp_brute_log = true;
          else if (what[i] == "rtsp")
            argp.rtsp_brute_log = true;
          else if (what[i] == "http")
            argp.http_brute_log = true;
          else if (what[i] == "hikvision")
            argp.hikvision_brute_log = true;
          else if (what[i] == "smtp")
            argp.smtp_brute_log = true;
          else if (what[i] == "rvi")
            argp.rvi_brute_log = true;
          else if (what[i] == "all") {
            argp.ftp_brute_log = true;
            argp.smtp_brute_log = true;
            argp.rvi_brute_log = true;
            argp.rtsp_brute_log = true;
            argp.http_brute_log = true;
            argp.hikvision_brute_log = true;
          }
        }
        break;
      }
      case 31: {
        std::vector<std::string> what = split_string_string(optarg, ',');
        for (int i = 0; i < static_cast<int>(what.size()); i++) {
          what[i] = to_lower_case(what[i]);
          if (what[i] == "ftp")
            argp.ftp_brute_verbose = true;
          else if (what[i] == "rtsp")
            argp.rtsp_brute_verbose = true;
          else if (what[i] == "http")
            argp.http_brute_verbose = true;
          else if (what[i] == "smtp")
            argp.smtp_brute_verbose = true;
          else if (what[i] == "all") {
            argp.ftp_brute_verbose = true;
            argp.smtp_brute_verbose = true;
            argp.rtsp_brute_verbose = true;
            argp.http_brute_verbose = true;
          }
        }
        break;
      }
      case 44: {
        std::vector<std::string> what = split_string_string(optarg, ',');
        for (int i = 0; i < static_cast<int>(what.size()); i++) {
          what[i] = to_lower_case(what[i]);
          if (what[i] == "ftp")
            argp.off_ftp_brute = true;
          else if (what[i] == "rtsp")
            argp.off_rtsp_brute = true;
          else if (what[i] == "http")
            argp.off_http_brute = true;
          else if (what[i] == "hikvision")
            argp.off_hikvision_brute = true;
          else if (what[i] == "smtp")
            argp.off_smtp_brute = true;
          else if (what[i] == "rvi")
            argp.off_rvi_brute = true;
          else if (what[i] == "all") {
            argp.off_ftp_brute = true;
            argp.off_rvi_brute = true;
            argp.off_smtp_brute = true;
            argp.off_rtsp_brute = true;
            argp.off_http_brute = true;
            argp.off_hikvision_brute = true;
          }
        }
        break;
      }
      case 47:
        argp.brute_timeout_ms = atoi(optarg);
        break;
      case 48:
        argp.thread_on_port = true;
        break;
      case 5:
        argp.random_ip = true;
        argp.random_ip_count = atoi(optarg);
        break;
      case 7:
        argp.debug = true;
        break;
      case 'd':
        argp.timeout = true;
        argp.timeout_ms = atoi(optarg);
        break;
      case 19:
        argp.find = true;
        argp.find_target = split_string_string(optarg, ',');
        break;
      case 20:
        n.frag_mtu = atoi(optarg);
        if (n.frag_mtu >! 0 && n.frag_mtu % 8 != 0) {
          np.nlog_error("Data payload MTU must be > 0 and multiple of 8: (8,16,32,64)\n");
          exit(1);
        }
        break;
      case 21:
        argp.custom_tcpflags = true;
        argp.custom_res_tcpflags = optarg;
        break;
      case 79: {
        u32 datalen = atoi(optarg);
        std::string temp = randomstr(datalen);
        n.pd.data = temp.c_str();
        n.pd.datalen = strlen(n.pd.data);
        break;
      }
      case 23:
        argp.ip_scan_import = true;
        argp.path_ips = optarg;
        break;
      case 15:
        break;
      case 16:
        break;
      case 25:
        argp.print_errors = true;
        break;
      case 26:
        np.disable_colors();
        break;
      case 27:
        argp.debug = true;
        break;
      case 28:
        argp.print_errors = true;
        break;
      case 29:
        argp.ping_off = true;
        break;
      case 34:
        n.src = inet_addr(optarg);
        break;
      case 13:
        argp.custom_ping = true;
        argp.sctp_ping_init = true;
        n.sctpport = atoi(optarg);
        break;
      case 35:
        argp.save_camera_screens = true;
        argp.screenshots_save_path_cam = optarg;
        break;
      case 36:
        argp.custom_source_port = true;
        n.sport = atoi(optarg);
        n.customsport = true;
        break;
      case 37:
        if (atoi(optarg) > 255) {
          np.nlog_error("The ttl is too big (1-255)\n");
          exit(1);
        }
        n.ttl = atoi(optarg);
        n.customttl = true;
        break;
      case 38: {
        u8 *buf = NULL;
        size_t len = 0;

        buf = hexbin(optarg, &len);
        if (buf == NULL)
          np.nlog_error("Invalid hex string specification\n");
        else {
          n.pd.data = reinterpret_cast<const char*>(buf);;
          n.pd.datalen = len;
        }
        break;
      }
#ifdef HAVE_NODE_JS
      case 's':
        argp.save_screenshots = true;
        argp.screenshots_save_path = optarg;
        break;
      case 41:
        argp.timeout_save_screenshots = atoi(optarg);
        break;
      case 39:
        argp.ns_track = true;
        break;
#endif
      case 56: {
        n.pd.data = optarg;
        n.pd.datalen = strlen(optarg);
        break;
      }
      case 58:
        argp.group_del = atoi(optarg);
        break;
      case 60:
        argp.maxg_ping = atoi(optarg);
        break;
      case 61:
        argp.maxg_scan = atoi(optarg);
        break;
      case 49:
        n.ping_timeout = atoi(optarg);
        break;
      case 33:
        argp.resol_source_port = atoi(optarg);
        break;
      case 32:
        argp.random_dns = true;
        argp.random_dns_count = atoi(optarg);
        break;
      case 40:
        argp.resol_delay = atoi(optarg);
        break;
      case 50:
        argp.custom_http_threads = true;
        argp.http_threads = atoi(optarg);
        break;
      case 51:
        argp.get_response = true;
        break;
      case 46:
        argp.no_scan = true;
        break;
      case 67:
        argp.robots_txt = true;
        break;
      case 68:
        argp.sitemap_xml = true;
        break;
      case 52:
        argp.custom_threads_resolv = true;
        argp.dns_threads = atoi(optarg);
        break;
      case 62: {
        std::vector<std::string> temp_ips = split_string_string(optarg, ',');
        argp.exclude = resolvhosts(false, temp_ips);
        break;
      }
      case 63: {
        std::vector<std::string> temp_ips = write_file(optarg);
        argp.exclude = resolvhosts(false, temp_ips);
        break;
      }
      case 53:
        argp.my_life_my_rulez = true;
        argp.speed_type = 5;
        break;
      case 10:
        break;
      case 78:
        np.import_color_scheme(optarg, np.config_values);
        np.processing_color_scheme(np.config_values);
        np.printcolorscheme();
        exit(1);
        break;
      case 54:
        argp.import_color_scheme = true;
        argp.path_color_scheme = optarg;
        break;
      case 'l':
        np.html_save = true;
        np.html_file_path = std::string(optarg);
        break;
      case 57:
        argp.custom_threads = true;
        argp.threads_ping = atoi(optarg);
        break;
      case 'n':
        argp.no_get_dns = true;
        break;
      case 4: {
        argp.scriptpath = std::string(optarg);
        break;
      }
      case 76:
        argp.negatives_path = std::string(optarg);
        break;
      case 80:
        argp.custom_ping = true;
        argp.syn_ping = true;
        n.syn_dest_port = atoi(optarg);
        break;
      case 81:
        argp.custom_ping = true;
        argp.ack_ping = true;
        n.ack_dest_port = atoi(optarg);
        break;
      case 43:
        argp.json_save = true;
        argp.json_save_path = optarg;
        break;
      case 82:
        argp.custom_ping = true;
        argp.echo_ping = true;
        break;
      case 86:
        argp.custom_ping = true;
        argp.info_ping = true;
        break;
      case 87:
        argp.custom_ping = true;
        argp.timestamp_ping= true;
        break;
      case 88:
        argp.max_ping = true;
        break;
      case 89:
        argp.type = TCP_ACK_SCAN;
        break;
      case 9:
        break;
      case 90:
        argp.ping_log = atoi(optarg);
        break;
      case 91:
        argp.type = TCP_NULL_SCAN;
        break;
      case 8:
        //argp.custom_ping = true;
        //argp.arp_ping = true;
        break;
      case 22:
        argp.http_timeout = atoi(optarg);
        break;
      case 3:
        argp.type = TCP_PSH_SCAN;
        break;
      case 24:
        if (atoi(optarg) > 65535) {
          np.nlog_error("The window size is too big (0-65535)\n");
          exit(1);
        }
        n.windowlen = atoi(optarg);
        break;
      case 92:
        argp.type = TCP_FIN_SCAN;
        break;
      case 93:
        argp.type = TCP_XMAS_SCAN;
        break;
      case 14:
        argp.type = SCTP_INIT_SCAN;
        break;
      case 17:
        argp.type = SCTP_COOKIE_SCAN;
        break;
      case 94:
        argp.type = TCP_WINDOW_SCAN;
        break;
      case 95:
        argp.no_proc = true;
        break;
      case 64:
        break;
      case 42:
        n.ack = atoi(optarg);
        break;
      case 18:
        argp.custom_ping = true;
        argp.udp_ping = true;
        n.udpport = atoi(optarg);
        break;
      case 65:
        n.badsum = true;
        break;
      case 55:
        argp.type = UDP_SCAN;
        break;
      case 59: {
        n.ipoptslen = parse_ipopts(optarg, n.ip_options, sizeof(n.ip_options), &n.ipopts_first_hop_offset,
            &n.ipopts_last_hop_offset, NULL, 0);
        break;
      }
      case 6:
        argp.no_verbose_script = false;
        break;
      case 97:
        argp.type = TCP_MAIMON_SCAN;
        break;
      case 101:
        argp.custom_recv_timeout_ms = true;
        argp.recv_timeout_ms = atoi(optarg);
        break;
      default:
        usage(run);
      }
    }
}
