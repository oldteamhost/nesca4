/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "../include/nescalog.h"
#include "../ncbase/include/json.h"
#include "../ncsock/include/strbase.h"
#include "../ncsock/include/base.h"
#include "../ncsock/include/icmp.h"
#include "../ncsock/include/igmp.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <stdio.h>
#include <string>

html_output hou;

std::string
nesca_prints::html_to_ansi_color(const std::string& html_color)
{
  int r,g,b;

  if (html_color.size() != 7 || html_color[0] != '#')
    return NULL;

  std::istringstream stream(html_color.substr(1));

  r = std::stoi(html_color.substr(1, 2), nullptr, 16);
  g = std::stoi(html_color.substr(3, 2), nullptr, 16);
  b = std::stoi(html_color.substr(5, 2), nullptr, 16);

  return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

void nesca_prints::log_tcphdr(const struct tcp_header *tcphdr)
{
  gray_nesca_on();
  printf("[^][TCPHEADER]:");
  reset_colors;

  printf("%ssport:%s %s%u%s, %sdport:%s %s%u%s, %sseq:%s %s%u%s, %sack:%s %s%u%s, %s2x_off:%s %s%u bytes%s,",
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(tcphdr->th_sport), gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(tcphdr->th_dport), gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohl(tcphdr->th_seq), gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohl(tcphdr->th_ack), gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (unsigned int)(tcphdr->th_x2 * 4), gray_nesca.c_str());

  printf("%s window:%s %u%s,", green_html.c_str(), golder_rod.c_str(), ntohs(tcphdr->th_win), gray_nesca.c_str());
  printf("%s check:%s 0x%04X%s,", green_html.c_str(), golder_rod.c_str(), ntohs(tcphdr->th_sum), gray_nesca.c_str());
  printf("%s urg:%s %u%s,", green_html.c_str(), golder_rod.c_str(), ntohs(tcphdr->th_urp), gray_nesca.c_str());

  printf("%s flags: URG:%s%d %sACK:%s%d %sPSH:%s%d %sRST:%s%d %sSYN:%s%d %sFIN:%s%d %sCWR:%s%d %sECE:%s%d\n",
         green_html.c_str(),
         golder_rod.c_str(),
         (tcphdr->th_flags & TH_URG) ? 1 : 0,
         green_html.c_str(),
         golder_rod.c_str(),
         (tcphdr->th_flags & TH_ACK) ? 1 : 0,
         green_html.c_str(),
         golder_rod.c_str(),
         (tcphdr->th_flags & TH_PSH) ? 1 : 0,
         green_html.c_str(),
         golder_rod.c_str(),
         (tcphdr->th_flags & TH_RST) ? 1 : 0,
         green_html.c_str(),
         golder_rod.c_str(),
         (tcphdr->th_flags & TH_SYN) ? 1 : 0,
         green_html.c_str(),
         golder_rod.c_str(),
         (tcphdr->th_flags & TH_FIN) ? 1 : 0,
         green_html.c_str(),
         golder_rod.c_str(),
         (tcphdr->th_flags & TH_CWR) ? 1 : 0,
         green_html.c_str(),
         golder_rod.c_str(),
         (tcphdr->th_flags & TH_ECE) ? 1 : 0);
}

void nesca_prints::log_icmphdr(struct icmp4_header *icmphdr)
{
  gray_nesca_on();
  printf("[^][ICMPHEADER]:");
  reset_colors;
  printf("%stype:%s %s%u%s, %scode:%s %s%u%s, %scheck:%s %s0x%04X%s, %sid:%s %s%u%s, %sseq:%s %s%u%s\n",
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (unsigned int)icmphdr->type, gray_nesca.c_str(),
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (unsigned int)icmphdr->code, gray_nesca.c_str(),
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(icmphdr->checksum), gray_nesca.c_str(),
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(icmphdr->id), gray_nesca.c_str(),
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(icmphdr->seq), gray_nesca.c_str());
}

void nesca_prints::log_igmphdr(struct igmp_header *igmphdr)
{
  gray_nesca_on();
  printf("[^][IGMPHEADER]:");
  reset_colors;
  printf("%stype:%s %s%u%s, %scode:%s %s%u%s, %scheck:%s %s0x%04X%s, %svar:%s %s%u%s\n",
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (unsigned int)igmphdr->type, gray_nesca.c_str(),
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (unsigned int)igmphdr->code, gray_nesca.c_str(),
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(igmphdr->check), gray_nesca.c_str(),
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohl(igmphdr->var), gray_nesca.c_str());
}

void nesca_prints::log_iphdr(struct ip_header *iphdr)
{
  gray_nesca_on();
  printf("[^][IPHEADER]:");
  reset_colors;
  printf("%sversion:%s %s%u%s, %sihl:%s %s%u bytes%s, %stos:%s %s%u%s, %stot_len:%s %s%u%s, %sid:%s %s%u%s, %sflags:%s %s%c%c%c%s, %sfrag_off:%s %s%u%s, %sttl:%s %s%u%s, %sproto:%s %s%u%s, %scheck:%s %s0x%04X%s, %ssaddr:%s %s%s%s, %sdaddr:%s %s%s%s\n",
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (unsigned int)iphdr->version, gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (unsigned int)(iphdr->ihl * 4), gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (unsigned int)iphdr->tos, gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(iphdr->tot_len), gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(iphdr->ident), gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (iphdr->frag_off & IP_RF) ? 'R' : '-',
         (iphdr->frag_off & IP_DF) ? 'D' : '-', (iphdr->frag_off & IP_MF) ? 'M' : '-', gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (unsigned int)(iphdr->frag_off & IP_OFFMASK), gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (unsigned int)iphdr->ttl, gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), (unsigned int)iphdr->protocol, gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(iphdr->check), gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), inet_ntoa(*(struct in_addr*)&iphdr->saddr), gray_nesca.c_str(),
         green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), inet_ntoa(*(struct in_addr*)&iphdr->daddr), gray_nesca.c_str());
}

void nesca_prints::log_udphdr(struct udp_header *udphdr)
{
  gray_nesca_on();
  printf("[^][UDPHEADER]:");
  reset_colors;
  printf("%sSource Port:%s %s%u%s, %sDestination Port:%s %s%u%s, %sLength:%s %s%u bytes%s, %sChecksum:%s %s0x%04X%s\n",
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(udphdr->uh_sport), gray_nesca.c_str(),
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(udphdr->uh_dport), gray_nesca.c_str(),
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(udphdr->ulen), gray_nesca.c_str(),
    green_html.c_str(), gray_nesca.c_str(), golder_rod.c_str(), ntohs(udphdr->check), gray_nesca.c_str());
}

void nesca_prints::log_ethhdr(struct eth_hdr *ethhdr)
{
  gray_nesca_on();
  printf("[^][ETHHEADER]:");
  reset_colors;
  printf("%sdaddr:%s %02X:%02X:%02X:%02X:%02X:%02X, %ssaddr:%s %02X:%02X:%02X:%02X:%02X:%02X, %stype:%s 0x%04X\n",
    green_html.c_str(), golder_rod.c_str(),
    ethhdr->eth_dst.data[0], ethhdr->eth_dst.data[1], ethhdr->eth_dst.data[2],
    ethhdr->eth_dst.data[3], ethhdr->eth_dst.data[4], ethhdr->eth_dst.data[5],
    green_html.c_str(), golder_rod.c_str(),
    ethhdr->eth_src.data[0], ethhdr->eth_src.data[1], ethhdr->eth_src.data[2],
    ethhdr->eth_src.data[3], ethhdr->eth_src.data[4], ethhdr->eth_src.data[5],
    green_html.c_str(), golder_rod.c_str(),
    ntohs(ethhdr->eth_type));
}

void nesca_prints::easy_packet_trace(u8 *buffer)
{
  u8* rbuffer;
  int len = -1;
  struct tcp_header  *tcph;
  struct udp_header  *udph;
  struct icmp4_header *icmph;
  struct igmp_header *igmph;
  struct eth_hdr *ethh;

  struct ip_header *iph = ext_iphdr(buffer);

  printf("\n%s%s[TRACEROUTE]:%slen=%s%u %ssaddr=%s%s\n", gray_nesca.c_str(), print_get_time(get_time()).c_str(), green_html.c_str(), golder_rod.c_str(),
      ntohs(iph->tot_len), green_html.c_str(), golder_rod.c_str(), inet_ntoa(*(struct in_addr*)&iph->saddr));

  ethh = (struct eth_hdr *)buffer;
  log_ethhdr(ethh);

  log_iphdr(iph);

  switch (iph->protocol) {
    case IPPROTO_TCP: {
      tcph = ext_tcphdr(buffer);
      log_tcphdr(tcph);
      break;
    }
    case IPPROTO_UDP:
      udph = ext_udphdr(buffer);
      log_udphdr(udph);
      break;
    case IPPROTO_ICMP:
      icmph = ext_icmphdr(buffer);
      log_icmphdr(icmph);
      break;
    case IPPROTO_IGMP:
      igmph = ext_igmphdr(buffer);
      log_igmphdr(igmph);
      break;
  }
  rbuffer = (u8*)calloc(2048, sizeof(u8));
  if (!rbuffer)
    return;

  /*
  len = ext_payload(buffer, rbuffer);
  */

  if (len > 0) {
    gray_nesca_on();
    std::cout << "[^][PAYLOAD]:";
    golder_rod_on();
    print_payload(rbuffer, len);
    gray_nesca_on();
    std::cout << "[^][PAYLOAD(ASCII)]:";
    golder_rod_on();
    print_payload_ascii(rbuffer, len);
    reset_colors;
  }

  free(rbuffer);
}

std::string
nesca_prints::main_nesca_out(const std::string& opt, const std::string& result, const int mode, const std::string& opt1, const std::string& opt2,
                            const std::string& result1, const std::string& result2, const std::string& rtt,
                            std::string type, std::string protocol)
{
  std::string temp, temp_file;
  char dots[3] = {':', ':', ':'};

  if (opt.empty())  {dots[0] = ' '; }
  if (opt1.empty()) {dots[1] = ' ';}
  if (opt2.empty()) {dots[2] = ' ';}

  if (mode == 0) {
    temp = green_html + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + result + reset_color;
      temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[1] + result;
  }
  else if (mode == 1) {
    temp = red_html + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + result + reset_color;
      temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[1] + result;
  }
  else if (mode == 2) {
    temp = yellow_html + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + result + reset_color;
      temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[1] + result;
  }
  else if (mode == 3) {
    temp = gray_nesca + "[>][" + opt + "]" + dots[0] + reset_color +
      sea_green + result + reset_color + gray_nesca + " " + opt1 + dots[1] + " " + reset_color +
      golder_rod + result1 + reset_color + gray_nesca + " " + opt2 + dots[2] + " " + reset_color +
      golder_rod + result2 + reset_color;

    temp_file = "[>][" + opt + "]" + dots[0] +
      result + " " + opt1 + dots[1] + " " + result1 + " " + opt2 + dots[2] + " " + result2;

    if (html_save) {hou.html_add_result(html_file_path,get_time(), result, result, "RTT", rtt+"ms", opt2, result2, opt1, result1, "SERVICE", protocol);}
  }
  else if (mode == 4) {
    temp = gray_nesca + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + reset_color +
      golder_rod + result + reset_color + gray_nesca + " " + opt1 + dots[1] + " " + reset_color +
      golder_rod + result1 + reset_color + gray_nesca + " " + opt2 + dots[2] + " " + reset_color +
      golder_rod + result2 + reset_color;

    temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[0] +
      result + " " + opt1 + dots[1] + " " + result1 + " " + opt2 + dots[2] + " " + result2;
  }
  else if (mode == 5) {
    temp = gray_nesca + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + reset_color +
      green_html + result + reset_color + gray_nesca + " " + opt1 + dots[1] + " " + reset_color +
      green_html + result1 + reset_color + gray_nesca + " " + opt2 + dots[2] + " " + reset_color +
      green_html + result2 + reset_color;

    temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[0] +
      result + " " + opt1 + dots[1] + " " + result1 + " " + opt2 + dots[2] + " " + result2;

  }
  else if (mode == 6) {
    temp = golder_rod + "-> " + result + " " + opt + " " + result1;
      temp_file = "-> " + result + " " + opt + " " + result1;

  }

  return temp;
}
void
nesca_prints::nlog_packet_trace(std::string action, std::string protocol, std::string& source_ip,
      std::string& dest_ip, int source_port, int dest_port,
      std::string message, int ttl, int id, int win,
      int seq, int iplen)
{
  const std::string temp = green_html + "-> " + reset_color +
      green_html + "  " + action + reset_color + green_html + "  " + protocol + "  " + reset_color +
      green_html + source_ip + ":" + std::to_string(source_port) + " > " + dest_ip + ":" +
      std::to_string(dest_port) + reset_color + golder_rod + message + reset_color +
      gray_nesca + "  TTL  " + golder_rod + std::to_string(ttl) + gray_nesca + "  ID  " + golder_rod +
      std::to_string(id) + gray_nesca + "  WINDOW  " + golder_rod + std::to_string(win) + gray_nesca +
      "  IPLEN  " + golder_rod + std::to_string(iplen) + gray_nesca + "  SEQ  " + golder_rod + std::to_string(seq) +reset_color;

  fwrite(temp.c_str(), sizeof(char), strlen(temp.c_str()), stdout);
}

void
nesca_prints::disable_colors(void)
{
  colors = false;
  gray_nesca = "";
  golder_rod = "";
  sea_green = "";
  green_html = "";
  red_html = "";
  yellow_html = "";
  reset_color = "";
}


int
nesca_prints::import_color_scheme(const std::string& file_name, std::map<std::string, std::string>& config_values)
{
  std::ifstream configFile(file_name);
  if (configFile.is_open()){
    std::string line;
    while (std::getline(configFile, line)){
      size_t delimiterPos = line.find('=');
      if (delimiterPos != std::string::npos){
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        config_values[key] = value;
      }
    }
    return 0;
  }
  return -1;
}

void
nesca_prints::golder_rod_on(void)
{
  printf("%s", golder_rod.c_str());
}

void
nesca_prints::sea_green_on(void)
{
  printf("%s", sea_green.c_str());
}

void
nesca_prints::gray_nesca_on(void)
{
  printf("%s", gray_nesca.c_str());
}

void
nesca_prints::yellow_html_on(void)
{
  printf("%s", yellow_html.c_str());
}

void
nesca_prints::green_html_on(void)
{
  printf("%s", green_html.c_str());
}

void
nesca_prints::red_html_on(void)
{
  printf("%s", red_html.c_str());
}

void
nesca_prints::custom_color_on(const std::string& html_color)
{
  if (colors == true)
    std::cout << html_to_ansi_color(html_color);
}

int
nesca_prints::processing_color_scheme(const std::map<std::string, std::string>& config_values)
{
  for (const auto& kvp : config_values) {
    if (kvp.first == "auth")
      gray_nesca = html_to_ansi_color(kvp.second);
    else if (kvp.first == "title")
      golder_rod = html_to_ansi_color(kvp.second);
    else if (kvp.first == "link")
      sea_green = html_to_ansi_color(kvp.second);
    else if (kvp.first == "ok")
      green_html = html_to_ansi_color(kvp.second);
    else if (kvp.first == "error")
      red_html = html_to_ansi_color(kvp.second);
    else if (kvp.first == "debug")
      yellow_html = html_to_ansi_color(kvp.second);
  }
  return 0;
}

void
nesca_prints::nlog_trivial(const std::string& message)
{
  green_html_on();
  std::cout << print_get_time(get_time()) + "[OK]:" + message;
  reset_colors;
}

void nesca_prints::nlog_error(const std::string& message)
{
  red_html_on();
  std::cout << print_get_time(get_time()) + "[ERROR]:" + message;
  reset_colors;
}

void nesca_prints::nlog_custom(const std::string& auth, std::string message, int color)
{
  switch (color)
  {
    case 0:
      green_html_on();
    case 1:
      yellow_html_on();
    case 2:
      red_html_on();
  }

  std::cout << print_get_time(get_time()) + "[" + auth + "]:" + message;
  reset_colors;
}
void nesca_prints::printcolorscheme(void)
{
   printf("-> " "%sauth" __RESET_COLOR "  %stitle" __RESET_COLOR "  %slink" __RESET_COLOR "  %sok" __RESET_COLOR "  %serror" __RESET_COLOR "  %sdebug\n",
      gray_nesca.c_str(), golder_rod.c_str(), sea_green.c_str(), green_html.c_str(), red_html.c_str(), yellow_html.c_str());
}

int html_output::html_main_init(const std::string& filepath)
{
  int write = -1;

  write = write_line(filepath, style_nesca3);
  if (write != 0)
    return -1;

  return 0;
}

int html_output::html_pre_init(const std::string& filepath)
{
  int write = -1;
  char formatted_date[11];
  std::string data_html;

  get_current_date(formatted_date, sizeof(formatted_date));
  data_html = R"(
  <br><br>
  <hr>
      <center>
      <h5>
      <font color="#a1a1a1">[)" + std::string(get_time()) + " & " + formatted_date + R"(]</font>
      </h5>
      </center>
  <hr>
  <br><br>
  )";

  write = write_line(filepath, data_html);
  if (write != 0)
    return -1;

  return 0;
}

int html_output::html_add_result(const std::string& filepath, const std::string& time, const std::string& href, const std::string& text,
    const std::string& opt, const std::string& res, const std::string& opt1, const std::string& res1,
    const std::string& opt2, const std::string& res2, const std::string& opt3, const std::string& res3)
{
  int write = -1;
  std::string data_html;
  char dots[4] = {':', ':', ':', ':'};

  if (res.empty())  {dots[0] = ' ';}
  if (res1.empty()) {dots[1] = ' ';}
  if (res2.empty()) {dots[2] = ' ';}
  if (res2.empty()) {dots[3] = ' ';}

  data_html = R"(
  <div id="ipd" style="color:#707070;text-decoration: none;">
  [)" + time + R"(]
  <span id="hostSpan"><a href=")" + href + R"(" target="_blank">
  <font color=MediumSeaGreen>)" + text + R"(</font></a>;</span>
  <span id="recvSpan">)" + opt3 + dots[0] + R"( <font color=SteelBlue>)" + res3 + R"(</font> </span>
  <span id="recvSpan">)" + opt + dots[1] + R"( <font color=SteelBlue>)" + res + R"(</font> </span>
  <span id="recvSpan">)" + opt1 + dots[2] + R"( <font color=GoldenRod>)" + res1 + R"(</font></span>)" 
  + opt2 + dots[3] + R"( <font color=GoldenRod>)" + res2 + R"(</font>
  </div>)";

  write = write_line(filepath, data_html);
  if (write != 0)
    return -1;

  return 0;
}
