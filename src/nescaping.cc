/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "../include/nescaping.h"
#include <cstring>
#include "../ncsock/include/strbase.h"
#include "../ncsock/include/ip.h"
#include "../ncsock/include/tcp.h"
#include "../ncsock/include/icmp.h"
#include <mutex>

extern std::mutex ls;

void send_ping(struct datastring *pd, NESCADATA &nd, arguments_program &argp, const std::string& ip)
{
  const char* ipc;
  double rtt;
  u8 ttl;
  u16 source;
  u16 seq;

  source = generate_rare_port();
  seq = generate_seq();

  if (argp.custom_source_port)
    source = argp._custom_source_port;
  if (nd.ttl == 0)
    ttl = random_num(29, 255);
  else
    ttl = nd.ttl;

  ipc = ip.c_str();

  if (argp.echo_ping) {
    rtt = icmp_ping(ipc, argp.source_ip, argp.ping_timeout, ICMP_ECHO, 0, seq, ttl,
        nd.ip_options, nd.ipoptslen, pd->data, pd->datalen, argp.frag_mtu);
    goto check;
  }
  if (argp.syn_ping) {
    rtt = tcp_ping(SYN_PACKET, ipc, argp.source_ip, argp.syn_dest_port, source,
        nd.windowlen, nd.ack, argp.ping_timeout, ttl, nd.ip_options, nd.ipoptslen, pd->data, pd->datalen, argp.frag_mtu);
    goto check;
  }
  if (argp.ack_ping) {
    rtt = tcp_ping(ACK_PACKET, ipc, argp.source_ip, argp.syn_dest_port, source,
        nd.windowlen, nd.ack, argp.ping_timeout, ttl, nd.ip_options, nd.ipoptslen, pd->data, pd->datalen, argp.frag_mtu);
    goto check;
  }
  if (argp.info_ping) {
    rtt = icmp_ping(ipc, argp.source_ip, argp.ping_timeout, ICMP_INFO_REQUEST, 0, seq, ttl,
        nd.ip_options, nd.ipoptslen, pd->data, pd->datalen, argp.frag_mtu);
    goto check;
  }
  if (argp.timestamp_ping) {
    rtt = icmp_ping(ipc, argp.source_ip, argp.ping_timeout, ICMP_TIMESTAMP, 0, seq, ttl,
        nd.ip_options, nd.ipoptslen, pd->data, pd->datalen, argp.frag_mtu);
    goto check;
  }

check:
  if (rtt != -1) {
    ls.lock();
    nd.set_rtt(ip, rtt);
    nd.success_ping_ip.push_back(ip);
    ls.unlock();
  }
  else {
    ls.lock();
    nd.failed_ping_ip.push_back(ip);
    ls.unlock();
  }
}
