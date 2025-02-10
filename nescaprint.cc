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

#include "include/nescaprint.h"

#include "include/nescadata.h"
#include "include/nescaengine.h"
#include "libncsnet/ncsnet/ip4addr.h"
#include "libncsnet/ncsnet/ip6addr.h"
#include "libncsnet/ncsnet/mac.h"
#include "libncsnet/ncsnet/ncsnet.h"
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include <sys/types.h>

u8 strmethod(int m)
{
  switch (m) {
    case M_ICMP_PING_ECHO: return 'e';
    case M_ICMP_PING_INFO: return 'i';
    case M_ICMP_PING_TIME: return 't';
    case M_TCP_PING_SYN: return 's';
    case M_TCP_PING_ACK: return 'a';
    case M_TCP_SYN_SCAN: return 'S';
    case M_TCP_XMAS_SCAN: return 'x';
    case M_TCP_FIN_SCAN: return 'f';
    case M_TCP_NULL_SCAN: return 'n';
    case M_TCP_ACK_SCAN: return 'A';
    case M_TCP_WINDOW_SCAN: return 'w';
    case M_TCP_MAIMON_SCAN: return 'm';
    case M_TCP_PSH_SCAN: return 'p';
    case M_SCTP_INIT_SCAN: return 'I';
    case M_SCTP_COOKIE_SCAN: return 'C';
    case M_SCTP_INIT_PING: return 'N';
    case M_UDP_PING: return 'u';
    case M_UDP_SCAN: return 'U';
    case M_ARP_PING: return 'r';
  }
  return '?';
}


std::string is_service(NESCAPORT *port)
{
  std::string line, name, portproto, fproto;
  size_t sp, fport;

  std::ifstream f(DEFAULT_SERVICES_PATH);
  if (!f.is_open())
    return "???";

  while (std::getline(f, line)) {
    std::istringstream iss(line);
    if (iss>>name>>portproto) {
      sp=portproto.find('/');
      if (sp!=std::string::npos) {
        fport=std::stoi(portproto.substr(0, sp));
        fproto=portproto.substr(sp + 1);
        if ((int)fport==port->port&&fproto==
          ((port->proto==6)?"tcp":(port->proto==17)?"udp":"sctp"))
          break;
      }
    }

  }

  f.close();
  return name;

}

std::string portblock(NESCAPORT *port, bool onlyok)
{
  std::string res, p, s, m, srv, num;

  res="";
  if (onlyok) if (!isokport(port)) return "";

  res+='\'';
  switch (port->proto) {
    case PR_TCP: p="tcp"; break;
    case PR_UDP: p="udp"; break;
    case PR_SCTP: p="sctp"; break;
    default: p="???"; break;
  }
  switch (port->state) {
    case PORT_OPEN: s="open"; break;
    case PORT_CLOSED: s= "closed"; break;
    case PORT_FILTER: s="filtered"; break;
    case PORT_ERROR: s="error"; break;
    case PORT_OPEN_OR_FILTER: s="open|filtered"; break;
    case PORT_NO_FILTER: s="unfiltered"; break;
    default: s="???"; break;
  }
  switch (port->method) {
    case M_TCP_SYN_SCAN: m="syn"; break;
    case M_TCP_XMAS_SCAN: m="xmas"; break;
    case M_TCP_FIN_SCAN: m="fin"; break;
    case M_TCP_ACK_SCAN: m="ack"; break;
    case M_TCP_WINDOW_SCAN: m="window"; break;
    case M_TCP_NULL_SCAN: m="null"; break;
    case M_TCP_MAIMON_SCAN: m="maimon"; break;
    case M_TCP_PSH_SCAN: m="psh"; break;
    case M_SCTP_INIT_SCAN: m="init"; break;
    case M_SCTP_COOKIE_SCAN: m="cookie"; break;
    case M_UDP_SCAN: m="udp"; break;
    default: m="???"; break;
  }

  num=(port->num>1)?"/"+std::to_string(port->num):"";
  srv=is_service(port);

  res+=std::to_string(port->port)+"/";
  res+=p+"/";
  res+=s+"/";
  res+=srv+"(";
  res+=m+")";
  res+=num;
  res+='\'';

  return res;
}

static std::string cutinfo(const std::string &input, bool yes)
{
  std::string res;
  if (input.length()<40||yes)
    return input;
  res=input;
  res=res.substr(0,40);
  res+="...";
  return res;
}

/*
 * Print results, print class NESCATARGET
 */
void NESCAPRINT::nescatarget(NESCATARGET *target, bool onlyok, bool cut)
{
  std::string methodstr, block;
  size_t i, j;

  if (onlyok&&!target->isok())
    return;
  methodstr="'.";
  if (target->get_num_time()>0)
    for (i=0;i<target->get_num_time();i++)
      methodstr+=strmethod(target->get_type_time(i));
  if (target->get_num_port()>0)
    for (i=0;i<target->get_num_port();i++)
      methodstr+=strmethod(target->get_port(i).method);
  methodstr.erase(std::unique(methodstr.begin(),
    methodstr.end()), methodstr.end());
  methodstr+="'";
  std::cout << "Report nesca4 for ";
  if (!target->get_mainip().empty())
    std::cout << target->get_mainip();
  else
    std::cout << "???";
  std::cout << " (";
  if (target->get_num_dns()>0) {
    for (i=0;i<target->get_num_dns();i++) {
      std::cout << target->get_dns(i);
      if (i!=target->get_num_dns()-1)
        std::cout << " ";
    }
  }
  else std::cout << "???";
  std::cout << ") ";
  if (!target->get_mac().empty())
    std::cout << "[" << target->get_mac() << "] ";
  std::cout << methodstr << " ";
  if (target->get_num_time()>0) {
    for (i=0;i<target->get_num_time();i++) {
      std::cout << util_timediff(target->get_time(i).tstamp1,
        target->get_time(i).tstamp2);
      if (i!=target->get_num_time()-1)
        putchar(' ');
    }
  }
  putchar('\n');
  if (target->get_num_port()>0) {
    if (((onlyok&&target->openports())||!onlyok))
      putchar('\n');
  }
  else if (target->check_service()||target->get_num_dbres()>0)
    putchar('\n');
  if (target->get_num_port()>0) {
    target->removedublports();
    if (onlyok&&!target->openports())
      return;
    for (i=0;i<target->get_num_port();i++) {
      NESCAPORT p=target->get_port(i);
      if (onlyok&&!isokport(&p))
        continue;
      block+=portblock(&p, onlyok);
      block+=',';
    }
    block.pop_back();
    if (!block.empty()) {
      std::cout << "  ports  ";
      std::cout << block;
    }
    putchar('\n');
  }
  if (target->check_service()) {
    for (j=0;j<S_NUM;j++) {
      for (i=0;i<target->get_num_port();i++) {
        NESCASERVICE tmp=target->get_service(target->get_real_port(i), j);
        if (!tmp.init)
          continue;
        for (const auto&s:tmp.info) {
          std::cout<<"  "<<
            ((tmp.service==S_FTP)?"ftp":
             (tmp.service==S_HTTP)?"http":
             "???")
            << "(" << s.type << ")"
            << "  ";
            std::cout << cutinfo(s.info, cut);
            putchar('\n');
        }
      }
    }
  }
  if (target->get_num_dbres()>0) {
    for (j=0;j<target->get_num_dbres();j++) {
      NESCADBRES tmp=target->get_dbres(j);
      std::cout << "  db(" << tmp.find << ")  " <<
        tmp.info << std::endl;;
    }
  }
}

void NESCAPRINT::PRINTTARGETS(NESCADATA *ncsdata)
{
  if (ncsdata->opts.check_stats_flag())
    std::cout << "NESCAPRINT for "<<
      ncsdata->targets.size() << " targets\n";

  for (const auto&t:ncsdata->targets) {
    if (ncsdata->opts.check_onlyopen_flag()&&!t->openports())
      continue;
    this->nescatarget(t, 1, ncsdata->opts.check_detal_flag());
    if (t->openports())
      putchar('\n');
    ncsdata->tmplast=(t->openports())?0:1;
    if (t->isok()) ncsdata->ok++;
  }
}

#include <iomanip>
static void print_u128(u128 value)
{
  u64 high = value >> 64;
  u64 low = static_cast<u64>(value);

  if (high>0) {
    std::cout << std::hex << high << std::setfill('0') << std::setw(16);
    std::cout << low << std::dec;
  }
  else
    std::cout << low << std::dec;
}

void NESCAPRINT::nescastats(size_t grouplen, __uint128_t total, __uint128_t i)
{
  u128 complete;
  int dots;

  if (total==0)
    return;

  complete=(i*100)/total;
  dots=(static_cast<uint64_t>(complete)*10)/100;
  std::cout << "\n -> completed ";
  print_u128(complete);
  std::cout << "% targets";
  std::cout << "\n -> remaining ";
  print_u128(100-complete);
  std::cout << "% [";
  for (;dots+1;dots--)
    putchar('.');
  std::cout << "]\n\n";
}

void NESCAPRINT::finish(NESCADATA *ncsdata)
{
  if (!ncsdata->ok)
    std::cout << "All scanned targets were unavailable, try another ping method.\n\n";
  if (ncsdata->tmplast)
    putchar('\n');
  std::cout << "NESCA4 finished ";
  print_u128(ncsdata->ok);
  std::cout << " up IPs (success) in ";
  std::cout << util_timediff(ncsdata->tstamp_s, ncsdata->tstamp_e) << "\n";
}




/* NESCA4 STATUS BAR */
std::string NESCASTATUS="";
void nescastatus(const std::string &status) {
  NESCASTATUS=status;
}
static std::string uint128_to_string(__uint128_t value)
{
  std::string res;
  if (value==0)
    return "0";
  while (value > 0) {
    res.insert(res.begin(),'0'+(value%10));
    value/=10;
  }
  return res;
}
static std::string firstline(const std::string& path)
{
  std::ifstream file(path);
  std::string line;

  if (!file.is_open())
    return "";

  if (std::getline(file, line))
    return line;

  return "";
}
static size_t ccalc(size_t *a, size_t *b, short issize_t)
{
  if (*b>=*a)
   return *b-*a;
  else {
    if (*a>sizeof(u32)||*b>sizeof(u32)
      ||issize_t==1)
      return SIZE_MAX-*a+*b;
    else
      return sizeof(u32)-*a+*b;
  }
}
static std::string getstatsdevice(NESCADEVICE *ncsdev)
{
  static size_t startrx=SIZE_MAX, starttx=SIZE_MAX;
  size_t tmprx, tmptx, rx, tx;
  std::string prepath, res;

  prepath="/sys/class/net/"+ncsdev->get_device()+"/statistics/";
  tmprx=atoll(firstline((prepath+"rx_bytes")).c_str());
  tmptx=atoll(firstline((prepath+"tx_bytes")).c_str());

  if (startrx==SIZE_MAX&&starttx==SIZE_MAX) {
    startrx=tmprx;
    starttx=tmptx;
  }

  rx=ccalc(&startrx, &tmprx, 1);
  tx=ccalc(&starttx, &tmptx, 1);

  startrx=tmprx;
  starttx=tmptx;

  res=(util_bytesconv(rx)+"  "+util_bytesconv(tx));
  return res;
}
void nescawatting(std::atomic<bool> &running, __uint128_t i,
    NESCADEVICE *ncsdev)
{
  std::string symbols[]={"-", "|", "/"}, line;
  size_t ident;

  ident=0;
  for (;running;) {
    std::ostringstream oss;

    oss << symbols[ident] << " PASSED " <<
      uint128_to_string(i) << "    " <<
      NESCASTATUS << "    " <<
      getstatsdevice(ncsdev);

    line=oss.str();
    std::cout << "\r" << line << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "\r" << std::string(line.size(), ' ') << "\r" << std::flush;
    ident=(ident+1)%3;
  }
  std::cout << "\r" << std::string((line.size()), ' ') << "\r" << std::flush;
}
/* NESCA4 STATUS BAR */




/*
 * Print class NESCADEVICE
 */
void NESCAPRINT::nescadevice(NESCADEVICE *device)
{
  mac_t mac, dstmac;
  ip4_t ip4, ip4_g;
  ip6_t ip6, ip6_g;

  mac=device->get_srcmac();
  dstmac=device->get_dstmac();
  ip4=device->get_srcip4();
  ip6=device->get_srcip6();
  ip4_g=device->get_gateway4();
  ip6_g=device->get_gateway6();

  std::cout << "note: device " << device->get_device() <<
    ((device->check_ipv6())?" [support ip6]":" [not support ip6]") <<
    ((device->check_ipv4())?" [support ip4]":" [not support ip4]") <<
    ": mac(" << mact_ntop_c(&mac) <<
    ") ip4(" << ip4t_ntop_c(&ip4) <<
    ") ip6(" << ip6t_ntop_c(&ip6) << ") gateway4(";

  std::cout << ip4t_ntop_c(&ip4_g) <<") gateway6(" <<
    ip6t_ntop_c(&ip6_g) << ") dstmac(" << mact_ntop_c(&dstmac)
    << ")\n";

}


/*
 * print usage (help menu)
 */
void NESCAPRINT::usage(int argc, char **argv)
{
  printf("Usage %s [flags] <targets>\n", argv[0]);
  std::cout << R"(
 -import <filepath> - import target(s) from file
 -random-ip <numips> - choose random ip4 target(s)
 -dev <ifr.if_name> - specify your interface
 -dst, -src <mac> - set your source/dest mac address
 -ip4, -ip6 <ip4/6> - set your source ip4 or ip6
 -maxfds <numfds> - set your max open fds
 -pps <pps> - set max packet per second for send
 -gplus <num> - set plus target group size
 -gmax <num> - set max target group size
 -gmin <num> - set min target group size
 -stats - display engine statistics after exec
 -dlen <length> - append random data to packets
 -dhex <hexseq> - append a custom data to packet
 -dstr <str> - append a custom ASCII data to packets
 -ttl <num> - set Time To Live, (TTL)
 -win <num> - set your TCP window siz, default 1024
 -ackn <num> - set TCP acknowledgment number
 -off <flag1[/flag2]...,> - set fragmentation OFFset: df,mf,rf
 -ipopt <hex> - set ip options to packet
 -badsum - send packets with bodus checksum
 -adler32 - use adler32 checksum for all SCTP packets
 -ps, -pa, -py, -pu <ports> - use SYN/ACK/UDP/SCTP ping
 -pr, -pe, -pi, -pm - use ARP/ICMP ping ECHO/INFO/TIMESTAMP
 -all-ping - use all ping methods
 -wait-ping <time> - set your wait time for ping (timeout)
 -num-ping <num> - set count ping probes
 -n-ping - skip ping scan, disable ping
 -xmas, -fin, -psh, -null - use one of these scanning methods
 -syn, -ack, -window, -maimon - use other TCP methods port scan
 -init, -cookie, -udp - use init, cookie SCTP, or UDP port scan method
 -all-scan - using all scan port methods
 -wait-scan <time> - set your max wait time for scan (timeout)
 -num-scan <num> - set count scan probes
 -mtpl-scan <multiplier> - set your multiplier for calc scan timeout
   Nb: <rtt> * <mult> = timeout
 -p <ports> - set ports for scan
   Ex: -p 80; -p 80,443; -p S:40-50,U:3,T:33,10-15
 -sn, -n-scan - skip port scan, disable port scan
 -s <ports> - set ports for service, ex: -s http:80-81,ftp:21,21
 -detal - do not abbreviate service information
 -dbpath <path> - set your nesca database path
 -n-db - skip or off nesca database scanning
 -login <path> - set your logins passwd list
 -pass <path> - set your pass passwd list
 -wait-brute <time> - set your max wait time (timeout)
 -threads-brute <num> - set your number threads
 -delay-brute <time> - set your special delay
 -n-brute - skip or off nesca bruteforcing
 -onlyopen - output information only if there are open ports
 -v - display all verbose information
 -html <filepath> - save output in html format
 -n - no resolv, skip resolution dns names
 -cfg <path> - set your config file for opts
 -help - display this menu and exit

 ./nesca4 google.com -p 80,443 -syn -pe -v
 ./nesca4 -random-ip 1000 google.com -p 80,443 -all-ping -syn -v
 ./nesca4 _gateway -pr -p 0-500 -syn -v -maxfds 5
)";
  putchar(0xa);
  exit(0);
}


/*
 * print run string
 */
void NESCAPRINT::run(void)
{
  char formatted_date[11];
  get_current_date(formatted_date, sizeof(formatted_date));
  printf("Running NESCA4 (v%s) time %s at %s\n",
      PACKAGE_VERSION, get_time(), formatted_date);
}


/*
 * print error string
 */
void NESCAPRINT::error(const std::string &err)
{
  std::cout << "err: " << err << std::endl;
  exit(0);
}

void NESCAPRINT::warning(const std::string &warn)
{
  std::cout << "warn: " << warn << std::endl;
}

void NESCAPRINT::note(const std::string &note)
{
  std::cout << "note: " << note << std::endl;
}

void NESCAHTML::nh_addtobuf(const std::string &txt)
{
  std::ofstream file(this->path, std::ios::app);
  if (file.is_open())
     file<<txt<<std::endl;
  total++;
}

std::string NESCAHTML::nh_fmtdate(const std::string &fmt)
{
  char date[100];
  std::time_t t;
  std::tm* now;

  t=std::time(NULL);
  now=std::localtime(&t);

  std::strftime(date, sizeof(date),
    fmt.c_str(), now);

  return std::string(date);
}

void NESCAHTML::nh_style(const std::string &filepath)
{
  std::string respath, line;
  respath=(filepath.empty())?
    DEFAULT_STYLE_PATH:filepath;
  std::ifstream f(respath);
  while (std::getline(f, line))
    nh_addtobuf(line);
  f.close();
}

void NESCAHTML::nh_headeropen(void)
{
  nh_addtobuf("<!DOCTYPE html>");
  nh_addtobuf("<html lang=\"en\">");
  nh_addtobuf("  <head>");
  nh_addtobuf("    <meta charset=\"UTF-8\">");
  nh_addtobuf("    <title>"+nh_fmtdate("Results of %b %d %Y")+"</title>");
  nh_style("");
  nh_addtobuf("  </head>");
}

void NESCAHTML::nh_bodyopen(NESCADATA *ncsdata)
{
  nh_addtobuf("  <body>");
  nh_addtobuf("    <center><span>"+ncsdata->opts.runcmd+"</span></center>");
  nh_addtobuf("    <div class=\"title\">");
  nh_addtobuf("      <center><h5>"+nh_fmtdate("%a %b %d %H:%M:%S %Y")+"</h5></center>");
  nh_addtobuf("      <hr>");
  nh_addtobuf("      <center><a href=\"  \">.Automatically generated by NESCA4.</a></center>");
  nh_addtobuf("    </div>");
  nh_addtobuf("    <br>");
}

static void remline(const std::string &filename, size_t num)
{
  std::string line="";
  size_t cur=0;

  std::ifstream infile(filename);
  if (!infile.is_open())
    return;
  std::ofstream temp_file("resources/tmp.txt");
  if (!temp_file.is_open()) {
    infile.close();
    return;
  }
  while (std::getline(infile, line)) {
    if (cur!=num)
      temp_file<<line<<'\n';
    ++cur;
  }
  infile.close();
  temp_file.close();
  std::remove(filename.c_str());
  std::rename("resources/tmp.txt", filename.c_str());
}

void NESCAHTML::nh_bodyclose(void)
{
  if (this->bodyclose_pos>0&&this->bodyclose_pos<=total)
    remline(this->path, bodyclose_pos);
  nh_addtobuf("  </body>");
  this->bodyclose_pos=total-1;
}

void NESCAHTML::nh_headerclose(void)
{
  if (this->headerclose_pos>0&&this->headerclose_pos<=total)
    remline(this->path, headerclose_pos-1);
  nh_addtobuf("</html>");
  this->headerclose_pos=total-1;
}

#include <filesystem>

void NESCAHTML::NH_OPEN(NESCADATA *ncsdata)
{
  this->open=1;
  nh_headeropen();
  nh_bodyopen(ncsdata);
}

void NESCAHTML::NH_ADD(NESCATARGET *target, NESCADATA *ncsdata, bool onlyok, bool cut)
{
  std::string block, methodstr;
  size_t i, j;
  bool details;

  details=0;
  if (onlyok&&!target->isok())
    return;

  methodstr="'.";
  if (target->get_num_time()>0)
    for (i=0;i<target->get_num_time();i++)
      methodstr+=strmethod(target->get_type_time(i));
  if (target->get_num_port()>0)
    for (i=0;i<target->get_num_port();i++)
      methodstr+=strmethod(target->get_port(i).method);
  methodstr.erase(std::unique(methodstr.begin(),
    methodstr.end()), methodstr.end());
  methodstr+="'";

  nh_addtobuf("");
  nh_addtobuf("    <div class=\"log-entry\">");
  nh_addtobuf("      "+nh_fmtdate("[%a %b %d %H:%M:%S %Y]"));
  nh_addtobuf("      <a href=\"http://"+target->get_mainip()+"\">"+target->get_mainip()+"</a>");
  nh_addtobuf("      mtdh=<span class=\"info_1\">"+methodstr+"</span>;");

  if (target->get_num_dns()>0) {
    block="";
    for (i=0;i<target->get_num_dns();i++) {
      block+=target->get_dns(i);
      if (i!=target->get_num_dns()-1)
        block+=", ";
    }
    if (!block.empty())
      nh_addtobuf("      rdns=<span class=\"info\">"+block+"</span>;");
  }

  if (target->get_num_time()>0) {
    block="";
    for (i=0;i<target->get_num_time();i++) {
      block+=util_timediff(target->get_time(i).tstamp1,
        target->get_time(i).tstamp2);
      if (i!=target->get_num_time()-1)
        block+=", ";
    }
    if (!block.empty())
      nh_addtobuf("      rtt=<span class=\"info_2\">"+block+"</span>;");
  }

  if (onlyok&&(target->openports()||target->check_service()))
    details=1;

  if (details) {
    nh_addtobuf("    <details><summary>detail</summary>");
    nh_addtobuf("    <pre>");
    nh_addtobuf("");
  }
  if (target->get_num_port()>0) {
    block="";
    if (onlyok&&!target->openports())
      goto skip;
    for (i=0;i<target->get_num_port();i++) {
      NESCAPORT p=target->get_port(i);
      if (onlyok&&!isokport(&p))
        continue;
      block+=portblock(&p, onlyok);
      block+=", ";
    }
    block.pop_back();
    block.pop_back();
    if (!block.empty())
      nh_addtobuf("  Ports: <span class=\"info\">"+
        block+"</span>;");
  }
skip:
  if (target->check_service()) {
    for (j=0;j<S_NUM;j++) {
      for (i=0;i<target->get_num_port();i++) {
        NESCASERVICE tmp=target->get_service(target->get_real_port(i), j);
        if (!tmp.init)
          continue;
        for (const auto&s:tmp.info) {
          block="";
          block+=
          std::string(((tmp.service==S_FTP)?"ftp":(tmp.service==S_HTTP)?
            "http": "???")) + "(" + s.type + ")" + "  ";
          nh_addtobuf("  "+block+"<span class=\"info\">"+
            cutinfo(s.info, cut)+"</span>;");
        }
      }
    }
  }
  if (target->get_num_dbres()>0) {
    for (j=0;j<target->get_num_dbres();j++) {
      NESCADBRES tmp=target->get_dbres(j);
      block="";
      block+="db("+tmp.find+")  ";
      nh_addtobuf("  "+block+"<span class=\"info\">"+
        cutinfo(tmp.info, cut)+"</span>;");
    }
  }
  if (details) {
    nh_addtobuf("    </pre>");
    nh_addtobuf("    </details>");
  }
  nh_addtobuf("    </div>");
  NH_CLOSE();
}

void NESCAHTML::NH_CLOSE(void)
{
  nh_bodyclose();
  nh_headerclose();
  total-=2;
}

void NESCAHTML::NHTARGETS(NESCADATA *ncsdata)
{
  bool onlyoktmp=1;
  if (!ncsdata->opts.check_html_flag())
    return;
  if (!this->open) {
    nh_setpath(ncsdata->opts.get_html_param());
    NH_OPEN(ncsdata);
  }
  for (const auto&t:ncsdata->targets) {
    if (ncsdata->opts.check_onlyopen_flag()
      &&!t->openports())
      continue;
    NH_ADD(t, ncsdata, onlyoktmp,
      ncsdata->opts.check_detal_flag());
  }
}

void NESCAHTML::nh_setpath(const std::string &path) {
  this->path=path;
}
