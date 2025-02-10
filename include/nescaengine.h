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

#pragma once
#include <bits/types/struct_timeval.h>
#include <vector>
#include <cstring>
#include <string>
#include <sys/time.h>
#include <unordered_map>
#include <condition_variable>
#include <functional>
#include <time.h>
#include <iostream>
#include <future>
#include "../libncsnet/ncsnet/raw.h"
#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include "nescadata.h"
#include "nescaprint.h"
#include "../libncsnet/ncsnet/arp.h"
#include "../libncsnet/ncsnet/eth.h"
#include "../libncsnet/ncsnet/hex.h"
#include "../libncsnet/ncsnet/icmp.h"
#include "../libncsnet/ncsnet/ip.h"
#include "../libncsnet/ncsnet/ip4addr.h"
#include "../libncsnet/ncsnet/ip6addr.h"
#include "../libncsnet/ncsnet/linuxread.h"
#include "../libncsnet/ncsnet/mac.h"
#include "../libncsnet/ncsnet/ncsnet.h"
#include "../libncsnet/ncsnet/random.h"
#include "../libncsnet/ncsnet/sctp.h"
#include "../libncsnet/ncsnet/tcp.h"
#include "../libncsnet/ncsnet/trace.h"
#include "../libncsnet/ncsnet/udp.h"
#include "../libncsnet/ncsnet/utils.h"
#include <algorithm>
#include <arpa/inet.h>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <sys/resource.h>
#include "../libncsnet/ncsnet/sys/types.h"
#include "../libncsnet/ncsnet/eth.h"
#include "../libncsnet/ncsnet/raw.h"
#include "../libncsnet/ncsnet/ncsnet.h"
#include "../libncsnet/ncsnet/ip.h"
#include "../libncsnet/ncsnet/linuxread.h"
#include "nescadata.h"

#define T_PING                      1
#define T_SCAN                      2

#define M_ICMP_PING_ECHO            1
#define M_ICMP_PING_INFO            2
#define M_ICMP_PING_TIME            3
#define M_TCP_PING_SYN              4
#define M_TCP_PING_ACK              5
#define M_TCP_SYN_SCAN              6
#define M_TCP_XMAS_SCAN             7
#define M_TCP_FIN_SCAN              8
#define M_TCP_NULL_SCAN             9
#define M_TCP_ACK_SCAN              10
#define M_TCP_WINDOW_SCAN           11
#define M_TCP_MAIMON_SCAN           12
#define M_TCP_PSH_SCAN              13
#define M_SCTP_INIT_SCAN            14
#define M_SCTP_COOKIE_SCAN          15
#define M_SCTP_INIT_PING            16
#define M_UDP_PING                  17
#define M_UDP_SCAN                  18
#define M_ARP_PING                  19

#define PORT_OPEN                 0
#define PORT_CLOSED               1
#define PORT_FILTER               2
#define PORT_ERROR               -1
#define PORT_OPEN_OR_FILTER       3
#define PORT_NO_FILTER            4

/*
 *  M_ICMP_PING_ECHO   .
 *  M_ICMP_PING_INFO   i
 *  M_ICMP_PING_TIME   t
 *  M_TCP_PING_SYN     s
 *  M_TCP_PING_ACK     a
 *  M_TCP_SYN_SCAN     S
 *  M_TCP_XMAS_SCAN    x
 *  M_TCP_FIN_SCAN     f
 *  M_TCP_NULL_SCAN    n
 *  M_TCP_ACK_SCAN     A
 *  M_TCP_WINDOW_SCAN  w
 *  M_TCP_MAIMON_SCAN  m
 *  M_TCP_PSH_SCAN     p
 *  M_SCTP_INIT_SCAN   I
 *  M_SCTP_COOKIE_SCAN C
 *  M_SCTP_INIT_PING   N
 *  M_UDP_PING         u
 *  M_UDP_SCAN         U
 *  M_ARP_PING         r
 */

#define MAXPKTLEN 2048

#define GETELAPSED(start, end)                                                 \
  (((end).tv_sec - (start).tv_sec) * 1000000000LL + (end).tv_nsec -            \
   (start).tv_nsec)

#define _MSGLEN 4096

bool NESCARESOLV_try(NESCATARGET *target, NESCADATA *ncsdata);
bool _NESCARESOLV_(std::vector<NESCATARGET*> targets, NESCADATA *ncsdata);

class NESCAPOOL {
public:
  explicit NESCAPOOL(size_t numthreads);
  template <class F,class...Args>
  auto enqueue(F&&f,Args&&...args)->std::future<typename std::result_of
  <F(Args...)>::type>
  {
    using return_type=typename std::result_of<F(Args...)>::type;
    auto task=std::make_shared<std::packaged_task<return_type()>>
      (std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> result=task->get_future(); {
      std::unique_lock<std::mutex> lock(queuemutex);
      if (stop){throw std::runtime_error("enqueue on stopped threadpool");}
      tasks.emplace([task](){(*task)();});
    }
    condition.notify_one();
    return result;
  }
  ~NESCAPOOL();

private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;
  std::mutex queuemutex;
  std::condition_variable condition;
  bool stop;
};

typedef struct __arg_ {
  int addrtype, method,
    port, proto, state,
    srcport;
  size_t chk;
  union {
    ip4_t ip4;
    ip6_t ip6;
  }addr;
} ___arg;

struct NESCAPROBE {
  ___arg  filter;
  size_t  probelen;
  u8     *probe;
  int     method;
};

struct NESCARESULT {
  std::string c;
  u8 *frame;
  size_t frmlen;
  struct timeval t_start, t_end;
  int method, port, state;
  bool ok;
};

class NESCAINIT {
  protected:
  std::vector<lr_t*>        recvfds;
  eth_t                    *sendfd=NULL;
  std::vector<NESCAPROBE*>  probes;
  std::vector<NESCARESULT*> results;
  class                     NESCAMETHOD {
    public:
    size_t numprobes, lastport;
    int    method, proto;
    std::vector<int> ports;
  };
  std::vector<NESCAMETHOD>  ni_methods;
  size_t                    num, total, last_target,
                            last_method, last_num;

  void ni_initsendfd(NESCADEVICE *ncsdev);
  void ni_initrecvfd(NESCATARGET *target, NESCADEVICE *ncsdev,
      NESCAOPTS *ncsopts, bool ping);
  void ni_initmethod(size_t numprobes, int method,
      std::vector<int> ports);
  void ni_initmethods(NESCAOPTS *ncsopts, bool ping);
  void ni_initres(NESCATARGET *target, NESCAMETHOD *ncsmethod);
  void ni_ethprobe(NESCAPROBE *probe, NESCATARGET *target,
      NESCADATA *ncsdata, NESCAMETHOD *ncsmethod);
  void ni_iprobe(NESCAPROBE *probe, NESCATARGET *target,
      NESCADATA *ncsdata, NESCAMETHOD *ncsmethod);
  void ni_icmprobe(NESCAPROBE *probe, NESCATARGET *target,
      NESCADATA *ncsdata, NESCAMETHOD *ncsmethod);
  void ni_arprobe(NESCAPROBE *probe, NESCATARGET *target,
      NESCADATA *ncsdata, NESCAMETHOD *ncsmethod);
  void ni_tcprobe(NESCAPROBE *probe, NESCATARGET *target,
      NESCADATA *ncsdata, NESCAMETHOD *ncsmethod, int port);
  void ni_udprobe(NESCAPROBE *probe, NESCATARGET *target,
      NESCADATA *ncsdata, NESCAMETHOD *ncsmethod, int port);
  void ni_sctprobe(NESCAPROBE *probe, NESCATARGET *target,
      NESCADATA *ncsdata, NESCAMETHOD *ncsmethod, int port);
  void ni_initprobe(NESCATARGET *target, NESCADATA *ncsdata,
      NESCAMETHOD *ncsmethod);

  public:
  NESCAINIT(NESCADATA *ncsdata, bool ping);
  bool NI_INIT(std::vector<NESCATARGET*> targets,
      NESCADATA *ncsdata, bool ping, size_t max);
  size_t NI_NUM(std::vector<NESCATARGET*> targets);
  void NI_CLEAR(void);

  std::vector<NESCAPROBE*>   ni_probes(void);
  std::string                ni_method(void);
  std::vector<lr_t*>         ni_recvfds(void);
  eth_t                     *ni_sendfd(void);
  std::vector<NESCARESULT*>  ni_results(void);
  ~NESCAINIT(void);
};

class NESCARECV {
  protected:
  struct timeval tstamp_e, tstamp_s;
  size_t recvbytes, ok, err, tot;
  bool stats;

  void nr_stats(void);
  void _nr_recv(lr_t *fd, NESCAPROBE *probe,
    NESCARESULT *result);

  public:
  NESCARECV(void);
  void nr_recv(std::vector<lr_t*> fds,
    std::vector<NESCAPROBE*> probes,
    std::vector<NESCARESULT*> results);

  std::vector<NESCARESULT> nr_results(void);
  void nr_setstats(void);

};

class NESCASEND {
  protected:
  struct timeval tstamp_e, tstamp_s;
  size_t sendbytes, ok, err, tot, pps;
  bool stats;

  void ns_stats(void);

  public:
  NESCASEND(void);
  void ns_send(eth_t *fd,
    std::vector<NESCAPROBE*> probes,
    size_t num);

  void ns_setpps(size_t pps);
  void ns_setstats(void);
  long long ns_ns(void);
};

class NESCAREAD {
  public:
  NESCAREAD(void);
  void nr_read(std::vector<NESCARESULT*> results,
    std::vector<NESCATARGET*> targets);
};

class _NESCAENGINE_ : public NESCASEND, public NESCAINIT,
                      public NESCARECV, public NESCAREAD
{
  std::vector<NESCATARGET*> forscan;
  bool ret;

  void NE_CONFIGURE(NESCADATA *ncsdata, bool ping);
  void NE_GROUPS(NESCADATA *ncsdata);

  public:
  _NESCAENGINE_(NESCADATA *ncsdata, bool ping);
};
