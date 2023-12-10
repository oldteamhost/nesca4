/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "../include/nescadata.h"
#include "../include/nescaddos.h"
#include "../ncsock/include/readpkt.h"
#include <mutex>
#include <netinet/in.h>

extern std::mutex ls;

void read_ddos(nesca_prints &np, struct readfiler *rf, int recvtime, bool hidden_eth)
{
  int res;
  u8* buffer = NULL;

  ls.lock();
  buffer = (u8*)calloc(RECV_BUFFER_SIZE, sizeof(u8));
  ls.unlock();

  res = read_packet(rf, recvtime, &buffer);
  if (res == -1) {
    ls.lock();
    np.nlog_error("The package was not accepted.\n");
    free(buffer);
    ls.unlock();
    return;
  }

  ls.lock();
  np.easy_packet_trace(buffer, hidden_eth);
  free(buffer);
  ls.unlock();
}

#include "../ncsock/include/strbase.h"
#include "../ncsock/include/strbase.h"
#include "../ncsock/include/base.h"

void send_ddos(struct datastring *ds, nesca_prints &np, NESCADATA &nd, arguments_program &argp, u8 proto, u8 type,
    const u32 daddr, const u32 saddr, const int port, bool ip_ddos)
{
  u32 seq;
  int source_port, sock, res, recvtime;
  struct in_addr addr_struct;
  u16 ttl;
  bool df = true;
  double rtt_ping;
  readfiler rf;

  if (argp.frag_mtu)
    df = false;

  if (argp.custom_recv_timeout_ms)
    recvtime = argp.recv_timeout_ms;
  else {
    addr_struct.s_addr = daddr;
    rtt_ping = nd.get_rtt(inet_ntoa(addr_struct));
    if (rtt_ping != -1)
      recvtime = calculate_timeout(rtt_ping, argp.speed_type);
  }

  if (proto == IPPROTO_ICMP || proto == IPPROTO_TCP)
    seq = generate_seq();
  if (proto == IPPROTO_TCP || proto == IPPROTO_UDP) {
    if (argp.custom_source_port)
      source_port = argp._custom_source_port;
    else
      source_port = generate_rare_port();
  }

  if (argp.custom_ttl)
    ttl = argp._custom_ttl;
  else
    ttl = random_num(29, 255);

  sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  if (sock == -1)
    return;

  if (proto == IPPROTO_TCP)
    res = send_tcp_packet(sock, saddr, daddr, ttl, df, 0, 0, source_port, port, seq, 0, 0, argp.tcpflags,
        1024, 0, 0, 0, ds->data, ds->datalen, argp.frag_mtu);
  else if (proto == IPPROTO_ICMP)
    res = send_icmp_packet(sock, saddr, daddr, ttl, df, 0, 0, seq, 0, type, ds->data, ds->datalen, argp.frag_mtu);
  else if (proto == IPPROTO_UDP)
    res = send_udp_packet(sock, saddr, daddr, ttl, generate_ident(), NULL, 0, source_port, port, df, ds->data, ds->datalen, argp.frag_mtu);
  else if (ip_ddos)
    res = send_ip_empty(sock, saddr, daddr, ttl, proto, df, 0, 0, NULL, 0, argp.frag_mtu);

  if (res != -1)
    argp.success_packet_ddos++;

  ls.lock();
  close(sock);
  ls.unlock();

  if (!argp.reply_ddos)
    return;

  rf.dest_ip = daddr;
  rf.protocol = argp.reply_ddos_proto;

  read_ddos(np, &rf, recvtime, argp.hidden_eth);
}
