/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "../include/nescatesting.h"
#include "../ncsock/include/readpkt.h"
#include "../ncsock/include/utils.h"
#include <arpa/inet.h>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <limits>
#include <limits.h>
#include <vector>

_importfile_::_importfile_(const std::string& path, _interdata_ *i)
{
  id = i;
  id->path = path;
  id->lines = 0;
  id->characters = 0;
}

void _importfile_::loadfile(void)
{
  std::string line;
  std::string templine;
  std::ifstream stream(id->path);
  size_t poscom;

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      REMOVE_WHITESPACE(templine);
      poscom = line.find('#');
      if (poscom != std::string::npos && poscom != 0)
        line = line.substr(0, poscom);
      if (!line.empty()) {
        id->data.push_back(line);
        id->lines++;
        id->characters += line.length();
      }
    }
    stream.close();
  }
}

static bool findkey(std::vector<std::string> data, const std::string& keyword, size_t start)
{
  for (size_t i = start; i < data.size(); ++i) {
    if (data[i].find(keyword) != std::string::npos)
      return true;
  }
  return false;
}

static bool Findword(const std::string& word, const std::string& sentence)
{
  std::string::size_type pos = sentence.find(word);
  while (pos != std::string::npos) {
    if (std::isalpha(sentence[pos - 1]) || std::isalpha(sentence[pos + word.length()]))
      pos = sentence.find(word, pos + 1);
    else
      return true;
  }
  return false;
}

void _importfile_::display_fileinfo(void)
{
  std::cout << "File Information:" << std::endl;
  std::cout << "  path: " << id->path << std::endl;
  std::cout << "  num lines: " << id->lines << std::endl;
  std::cout << "  num characters: " << id->characters << std::endl;
}

void _preprocessor_::getplaylines(void)
{
  playlines.clear();
  for (size_t i = 0; i < id->lines; i++) {
    if (findkey(id->data, TYPE_1, i))
      playlines.push_back(i);
  }
}

int _preprocessor_::check_directive(size_t line)
{
  std::string temp;
  temp = id->data[line];

  if (Findword(TYPE_1, temp))
    return INCLUDE;

  return -1;
}

static void intererror(size_t line, std::string element, std::string message)
{
  std::cout << "_ERROR: " << line << " line | " << element << "\n  " << message << std::endl;
  exit(0);
}

static void interwarning(size_t line, std::string element, std::string message)
{
  std::cout << "_WARNING: " << line << " line | " << element << " " << message << std::endl;
}

void _interpreter_::interverbose(std::string element, std::string message)
{
  if (verbose)
    std::cout << "VERBOSE: | " << element << " " << message << std::endl;
}

void _preprocessor_::execute_include(size_t line)
{
  std::string newline, respath, templine;
  std::vector<std::string> includefile;
  size_t pos1, pos2;

  newline = id->data[line];
  pos1 = newline.find('<');
  pos2 = newline.find('>', pos1 + 1);

  if (pos1 == std::string::npos && pos2 == std::string::npos)
    intererror(line, "INCLUDE", "no angle brackets found");
  if (pos1 == std::string::npos)
    intererror(line, "INCLUDE", "(<) not found");
  if (pos2 == std::string::npos)
    intererror(line, "INCLUDE", "<path (>) not found");

  if (pos2 > pos1 + 1)
    respath = newline.substr(pos1 + 1, pos2 - pos1 - 1);
  else
    intererror(line, "INCLUDE", "empty path between quotes");

  id->data.erase(id->data.begin() + line);
  id->lines--;

  std::ifstream stream(respath);
  if (stream.is_open()) {
    while (std::getline(stream, templine))
      if (templine.empty() || templine[0] != '#')
        includefile.push_back(templine);
    stream.close();
  }
  else
    intererror(line, "INCLUDE", "file \"" + respath + "\" not found!");

  id->data.insert(id->data.begin() + line, includefile.begin(), includefile.end());
  id->lines += includefile.size();
}

void _preprocessor_::execute_directives(void)
{
  size_t i;
  int type = -1;

  for (i = 0; i < playlines.size(); i++) {
    type = check_directive(i);
    if (type == INCLUDE) {
      execute_include(i);
      getplaylines();
    }
  }
}

void _preprocessor_::preprocessor(_interdata_ *i)
{
  id = i;
  getplaylines();
  execute_directives();
}

struct headerline parsehdrline(std::string newline, size_t line)
{
  struct headerline res;
  res.key = "";
  res.value = "";
  res.valuetype = -1;

  std::unordered_map<std::string, std::string> tempmap;
  std::string key, value;

  REMOVE_WHITESPACE(newline);
  REMOVE_BRACKETS(newline);

  if (newline.empty() || newline.length() <= 0)
    return res;

  std::istringstream iss(newline);
  if (std::getline(iss, key, ':') && std::getline(iss, value)) {
    key.erase(key.find_last_not_of(" \t") + 1);
    value.erase(0, value.find_first_not_of(" \t"));
    tempmap[key] = value;
  }
  else
    intererror(line, "HEADEROPT", "empty value \"" + newline + "\"");

  for (const auto& pair : tempmap) {
    res.key = pair.first;
    res.value = pair.second;

    if (res.value == VALUE_AUTO)
      res.valuetype = VALUE_TYPE_AUTO;
    else if (res.value == VALUE_RANDOM)
      res.valuetype = VALUE_TYPE_RANDOM;
    else if (res.value == VALUE_NONE)
      res.valuetype = VALUE_TYPE_NONE;
    else
      res.valuetype = VALUE_TYPE_CUSTOM;
  }

  return res;
}

std::string _scanner_::get_type_block(int type)
{
  switch (type)
  {
    case DELAY_TOKEN_2:
      return DELAY;
    case IPHEADER_TOKEN_4:
      return IPHEADER;
    case TCPHEADER_TOKEN_5:
      return TCPHEADER;
    case ICMPHEADER_TOKEN_6:
      return ICMPHEADER;
    case IGMPHEADER_TOKEN_7:
      return IGMPHEADER;
    case UDPHEADER_TOKEN_8:
      return UDPHEADER;
    case MAIN_TOKEN_9:
      return MAIN;
  }

  return "";
}

int _scanner_::get_token_type_block(size_t line)
{
  std::string newline;
  newline = id->data[line];

  if (Findword(MAIN, newline))
    return MAIN_TOKEN_9;
  if (Findword(IPHEADER, newline))
    return IPHEADER_TOKEN_4;
  if (Findword(TCPHEADER, newline))
    return TCPHEADER_TOKEN_5;
  if (Findword(ICMPHEADER, newline))
    return ICMPHEADER_TOKEN_6;
  if (Findword(IGMPHEADER, newline))
    return IGMPHEADER_TOKEN_7;
  if (Findword(UDPHEADER, newline))
    return UDPHEADER_TOKEN_8;
  if (Findword(DELAY, newline))
    return DELAY_TOKEN_2;

  return -1;
}

#include <regex>
struct blockpreset _scanner_::parseblock(size_t line)
{
  std::string input;
  blockpreset res;
  std::string content;
  std::smatch matches;
  size_t i = line;

  while (i < id->data.size()) {
    input += id->data[i++];
    if (input.find('}') != std::string::npos) {
      res.end = i;
      break;
    }
  }

  res.blocktype = get_token_type_block(line);

  std::regex pat1(R"(\b(\w+)\s+(\w+)\s*\{\s*([^}]*)\s*\})");
  std::regex pat2(R"(\s*([^,}]+)\s*(?:,|$))");

  if (std::regex_match(input, matches, pat1)) {
    res.keyword = matches[2].str();
    content = matches[3].str();
    std::sregex_iterator start(content.begin(), content.end(), pat2);
    std::sregex_iterator end;

    for (auto it = start; it != end; ++it)
      res.lines.push_back(it->str(1));
  }

  res.start = line;
  return res;
}

static bool ishexstring(const std::string& node)
{
  size_t i;

  if (node.size() >= 2 && node.substr(0, 2) == "0x") {
    for (i = 2; i < node.size(); ++i)
      if (!std::isxdigit(node[i]))
        return false;
    return true;
  }

  return false;

}

u8 set_customhex(const std::string& value, const std::string& key, size_t maxval, size_t line)
{
  u8 res;
  if (ishexstring(value))
    sscanf(value.c_str(), "%hhx", &res);
  else
    intererror(line, "SET_HEX", "You cannot specify a \"" + value + "\" in ("+ key + ")");
  if (res > maxval)
    intererror(line, "SET_HEX", "Your value (" + key + ") exceeds (max " + std::to_string(maxval)+")");
  return res;
}

size_t set_customnum(const std::string& value, const std::string& key, size_t maxval, size_t line)
{
  size_t res;
  bool hasletters = false;

  for (char c : value) {
    if (std::isalpha(c)) {
      hasletters = true;
      break;
    }
  }
  if (!hasletters)
    res = std::stoi(value);
  else
    intererror(line, "SET_NUM", "You cannot specify a string in ("+ key + ")");
  if (res > maxval)
    intererror(line, "SET_NUM", "Your value (" + key + ") exceeds (max " + std::to_string(maxval)+")");
  return res;
}

static long long delay_convert(const std::string& delay)
{
  long long value;
  std::string unit;

  std::istringstream iss(delay);
  iss >> value >> unit;

  if (unit == "ms")
    return (value * 1000000LL);
  else if (unit == "s")
    return (value * 1000000000LL);
  else if (unit == "m")
    return (value * 60000000000LL);
  else if (unit == "h")
    return (value * 3600000000000LL);

  return -1;
}

struct delayline _scanner_::parsedelayline(std::string newline)
{
  struct delayline res;
  std::unordered_map<int, long long> tempmap;
  std::string key, value;

  memset(&res, 0, sizeof(struct delayline));

  REMOVE_WHITESPACE(newline);

  if (newline.empty() || newline.length() <= 0)
    return res;

  std::istringstream iss(newline);
  if (std::getline(iss, key, ':') && std::getline(iss, value)) {
    key.erase(key.find_last_not_of(" \t") + 1);
    value.erase(0, value.find_first_not_of(" \t"));
    tempmap[std::stoi(key)] = delay_convert(value);
  }
  else
    intererror(0, "DELAYOPT", "empty value \"" + newline + "\"");

  for (const auto& pair : tempmap) {
    res.numpackage = pair.first;
    res.delay = pair.second;
  }

  return res;
}

void _scanner_::get_ip_header(struct blockpreset *bp)
{
  struct temp_ip_header ip;
  struct headerline hl;
  bool finddaddr = false;
  size_t endline = 0;
  char* tempconvip;

  ip.ihl = -1;
  ip.version = 4;
  ip.tos = 5;
  ip.tot_len = -1;
  ip.ident = random_u16();
  ip.frag_off = -1;
  ip.ttl = 121;
  ip.protocol = -1;
  ip.check = -1;
  tempconvip  = ip4_util_strsrc();
  ip.saddr = inet_addr(tempconvip);
  free(tempconvip);
  ip.ipopt = NULL;
  ip.ipoptlen = 0;
  ip.mtu = -1;

  size_t i = 0;
  for (const auto& line : bp->lines) {
    hl = parsehdrline(line, i);
    if (hl.valuetype == -1 && hl.valuetype == VALUE_TYPE_AUTO)
      continue;

#define MAX_IP_IHL 15
    if (hl.key == "ihl") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          ip.ihl = set_customnum(hl.value, hl.key, IP4_IHL_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          ip.ihl = random_num_u32(0, MAX_IP_IHL);
          break;
        case VALUE_TYPE_NONE:
          ip.ihl = 0;
          break;
      }
    }
#define MAX_IP_VERSION 15
    else if (hl.key == "version") {
      if (hl.value != "4")
          interwarning(i, "[ip_header] (" + bp->keyword + ") <version>",
              "Normally the system will automatically change this field on sendto to the correct one.");
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          ip.version = set_customnum(hl.value, hl.key, MAX_IP_VERSION, i);
          break;
        case VALUE_TYPE_RANDOM:
          ip.version = random_num_u32(0, MAX_IP_VERSION);
          break;
        case VALUE_TYPE_NONE:
          ip.version = 0;
          break;
      }
    }
#define MAX_IP_TOS 255
    else if (hl.key == "tos") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          ip.tos = set_customnum(hl.value, hl.key, MAX_IP_TOS, i);
          break;
        case VALUE_TYPE_RANDOM:
          ip.tos = random_num_u32(0, MAX_IP_TOS);
          break;
        case VALUE_TYPE_NONE:
          ip.tos = 0;
          break;
      }
    }
    else if (hl.key == "totlen") {
      if (hl.valuetype != VALUE_TYPE_AUTO)
          interwarning(i, "[ip_header] (" + bp->keyword + ") <totlen>",
              "Normally the system will automatically change this field on sendto to the correct one.");
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          ip.tot_len = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          ip.tot_len = random_u16();
          break;
        case VALUE_TYPE_NONE:
          ip.tot_len = 0;
          break;
      }
    }
    else if (hl.key == "ident") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          ip.ident = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          break;
        case VALUE_TYPE_NONE:
          ip.ident = 0;
          break;
      }
    }
    else if (hl.key == "fragoff") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          if (hl.value == "DF" || hl.value == "df")
            ip.frag_off = -2;
          else
            ip.frag_off = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          ip.frag_off = random_u16();
          break;
        case VALUE_TYPE_NONE:
          ip.frag_off = -2;
          break;
      }
    }
#define MAX_IP_TTL 255
    else if (hl.key == "ttl") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          ip.ttl = set_customnum(hl.value, hl.key, MAX_IP_TTL, i);
          break;
        case VALUE_TYPE_RANDOM:
          ip.ttl = random_num_u32(0, MAX_IP_TTL);
          break;
        case VALUE_TYPE_NONE:
          ip.ttl = 0;
          break;
      }
    }
#define MAX_IP_PROTOCOL 255
    else if (hl.key == "proto") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          ip.protocol = set_customnum(hl.value, hl.key, MAX_IP_PROTOCOL, i);
          break;
        case VALUE_TYPE_RANDOM:
          ip.protocol = random_num_u32(0, MAX_IP_PROTOCOL);
          break;
        case VALUE_TYPE_NONE:
          ip.protocol = 0;
          break;
      }
    }
    else if (hl.key == "check") {
      if (hl.valuetype != VALUE_TYPE_AUTO)
          interwarning(i, "[ip_header] (" + bp->keyword + ") <check>",
              "Normally the system will automatically change this field on sendto to the correct one.");
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          ip.check = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          ip.check = random_check();
          break;
        case VALUE_TYPE_NONE:
          ip.check = 0;
          break;
      }
    }
    else if (hl.key == "saddr") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          ip.saddr = inet_addr(hl.value.c_str());
          break;
        case VALUE_TYPE_RANDOM:
          const char* temprandomip;
          temprandomip = random_ip4();
          ip.saddr = inet_addr(temprandomip);
          break;
        case VALUE_TYPE_NONE:
          ip.saddr = 0;
          break;
      }
    }
    else if (hl.key == "daddr") {
      finddaddr = true;
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          ip.daddr = inet_addr(hl.value.c_str());
          break;
        case VALUE_TYPE_RANDOM:
          const char* temprandomip;
          temprandomip = random_ip4();
          ip.daddr = inet_addr(temprandomip);
          break;
        case VALUE_TYPE_NONE:
          interwarning(i, "[ip_header] (" + bp->keyword + ") <daddr>", "The empty daddr package is unlikely to make it");
          ip.daddr = 0;
          break;
      }
    }
    else if (hl.key == "ipopt") {
      int len;
      int ipopts_first_hop_offset = 0;
      int ipopts_last_hop_offset = 0;
      u8 ip_options[256];
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          len = parse_ipopts(hl.value.c_str(), ip_options, 256, &ipopts_first_hop_offset, &ipopts_last_hop_offset, NULL, 0);
          ip.ipopt = ip_options;
          ip.ipoptlen = len;
          break;
        case VALUE_TYPE_RANDOM:
          // XXX
          break;
        case VALUE_TYPE_NONE:
          break;
      }
    }
#define MAX_IP_MTU 64
    else if (hl.key == "fragmtu") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM: {
          int value = set_customnum(hl.value, hl.key, MAX_IP_MTU, i);
          if (value >! 0 && value % 8 != 0)
            intererror(i, "[ip_header] (" + bp->keyword + ") <fragmtu>", "Data payload MTU must be > 0 and multiple of 8: (8,16,32,64)");
          else
            ip.mtu = value;
          break;
        }
        case VALUE_TYPE_RANDOM:
          // XXX
          break;
        case VALUE_TYPE_NONE:
          ip.mtu = 0;
          ip.frag_off = -2;
          break;
      }
    }
    else
      intererror(i, "[ip_header]", "Not found field \"" + hl.key + "\"\n");
    endline = i;
    i++;
  }
  if (!finddaddr)
    intererror(endline, "[ip_header] (" + bp->keyword + ") <daddr>", "The IP address of the recipient cannot be determined automatically");
  id->iphdr_presets[bp->keyword] = ip;

  /*
  struct in_addr saddr_struct, daddr_struct;
  saddr_struct.s_addr = ip.saddr;
  daddr_struct.s_addr = ip.daddr;

  std::cout << "ihl: " << ip.ihl << std::endl;
  std::cout << "version: " << ip.version << std::endl;
  std::cout << "tos: " << ip.tos << std::endl;
  std::cout << "tot_len: " << ip.tot_len << std::endl;
  std::cout << "ident: " << ip.ident << std::endl;
  std::cout << "frag_off: " << ip.frag_off << std::endl;
  std::cout << "ttl: " << ip.ttl << std::endl;
  std::cout << "protocol: " << ip.protocol << std::endl;
  std::cout << "check: " << ip.check << std::endl;
  std::cout << "saddr: " << inet_ntoa(saddr_struct) << std::endl;
  std::cout << "daddr: " << inet_ntoa(daddr_struct) << std::endl;
  std::cout << "mtu: " << ip.mtu << std::endl;
  */
}

void _scanner_::get_tcp_header(struct blockpreset *bp)
{
  struct temp_tcp_header tcp;
  struct headerline hl;

  tcp.th_sport = random_srcport();
  tcp.th_dport = 80;
  tcp.th_seq = random_u32();
  tcp.th_ack = 0;
  tcp.th_flags = TCP_FLAG_SYN;
  tcp.th_win = random_u16();
  tcp.th_urp = 0;
  tcp.th_x2 = -1;
  tcp.th_off = -1;
  tcp.th_sum = -1;
  tcp.tp.data = "";
  tcp.tp.datalen = 0;

  size_t i = 0;
  for (const auto& line : bp->lines) {
    hl = parsehdrline(line, i);
    if (hl.valuetype == -1 && hl.valuetype == VALUE_TYPE_AUTO)
      continue;

    if (hl.key == "sport") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          tcp.th_sport = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          break;
        case VALUE_TYPE_NONE:
          tcp.th_sport = 0;
          break;
      }
    }
    else if (hl.key == "dport") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          tcp.th_dport = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          tcp.th_dport = random_srcport();
          break;
        case VALUE_TYPE_NONE:
          tcp.th_dport = 0;
          break;
      }
    }
    else if (hl.key == "seq") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          tcp.th_seq = set_customnum(hl.value, hl.key, UINT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          break;
        case VALUE_TYPE_NONE:
          tcp.th_seq = 0;
          break;
      }
    }
    else if (hl.key == "ack") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          tcp.th_ack = set_customnum(hl.value, hl.key, UINT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          tcp.th_ack = random_u32();
          break;
        case VALUE_TYPE_NONE:
          break;
      }
    }

    else if (hl.key == "flags") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          struct tcp_flags tf;
          tf = tcp_util_str_setflags(hl.value.c_str());
          tcp.th_flags = tcp_util_setflags(&tf);
          break;
        case VALUE_TYPE_RANDOM:
          // XXX
          break;
        case VALUE_TYPE_NONE:
          tcp.th_flags = 0;
          break;
      }
    }
    else if (hl.key == "window") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          tcp.th_win = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          break;
        case VALUE_TYPE_NONE:
          tcp.th_win = 0;
          break;
      }
    }
    else if (hl.key == "urp") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          tcp.th_urp = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          tcp.th_urp = random_u16();
          break;
        case VALUE_TYPE_NONE:
          break;
      }
    }
#define MAX_TCP_REVERSED 15
    else if (hl.key == "reversed") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          tcp.th_x2 = set_customnum(hl.value, hl.key, MAX_TCP_REVERSED, i);
          break;
        case VALUE_TYPE_RANDOM:
          tcp.th_x2 = random_num_u32(0, MAX_TCP_REVERSED);
          break;
        case VALUE_TYPE_NONE:
          tcp.th_x2 = 0;
          break;
      }
    }
#define MAX_TCP_OFF 15
    else if (hl.key == "off") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          tcp.th_off = set_customnum(hl.value, hl.key, MAX_TCP_OFF, i);
          break;
        case VALUE_TYPE_RANDOM:
          tcp.th_off = random_num_u32(0, MAX_TCP_OFF);
          break;
        case VALUE_TYPE_NONE:
          tcp.th_off = 0;
          break;
      }
    }
    else if (hl.key == "check") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          tcp.th_sum = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          tcp.th_sum = random_check();
          break;
        case VALUE_TYPE_NONE:
          tcp.th_sum = 0;
          break;
      }
    }
#define MAX_TCP_DATA_SIZE 1400
    else if (hl.key == "data") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          if (hl.value.length() < MAX_TCP_DATA_SIZE) {
            tcp.tp.data = hl.value.c_str();
            tcp.tp.datalen = hl.value.length();
          }
          else
            intererror(i, "[tcp_header] (" + bp->keyword + ") <data>", "The maximum payload size on linux is 1400.");
          break;
        case VALUE_TYPE_RANDOM: {
          tcp.tp.data = random_str(random_num_u32(0, MAX_TCP_DATA_SIZE), DEFAULT_DICTIONARY);
          tcp.tp.datalen = strlen(tcp.tp.data);
          break;
        }
        case VALUE_TYPE_NONE:
          break;
      }
    }
    else
      intererror(i, "[tcp_header]", "Not found field \"" + hl.key + "\"\n");
    i++;
  }
  id->tcphdr_presets[bp->keyword] = tcp;

  /*
  std::cout << "th_sport: " << tcp.th_sport << std::endl;
  std::cout << "th_dport: " << tcp.th_dport << std::endl;
  std::cout << "th_seq: " << tcp.th_seq << std::endl;
  std::cout << "th_ack: " << tcp.th_ack << std::endl;
  std::cout << "th_off: " << static_cast<int>(tcp.th_off) << std::endl;
  std::cout << "th_x2: " << tcp.th_x2 << std::endl;
  std::cout << "th_win: " << tcp.th_win << std::endl;
  std::cout << "th_sum: " << tcp.th_sum << std::endl;
  std::cout << "th_urp: " << tcp.th_urp << std::endl;
  std::cout << "th_flags: " << static_cast<int>(tcp.th_flags) << std::endl;
  std::cout << "data: " << tcp.data << std::endl;
  std::cout << "datalen: " << tcp.datalen << std::endl;
  */
}

void _scanner_::get_icmp_header(struct blockpreset *bp)
{
  struct temp_icmp4_header icmp;
  struct headerline hl;

  icmp.checksum = -1;
  icmp.code = 0;
  icmp.id = random_u16();
  icmp.seq = -1;
  icmp.type = ICMP4_ECHO;
  icmp.tp.data = "";
  icmp.tp.datalen = 0;

  size_t i = 0;
  for (const auto& line : bp->lines) {
    hl = parsehdrline(line, i);
    if (hl.valuetype == -1 && hl.valuetype == VALUE_TYPE_AUTO)
      continue;

    if (hl.key == "type") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          icmp.type = set_customnum(hl.value, hl.key, UCHAR_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          icmp.type = random_u8();
          break;
        case VALUE_TYPE_NONE:
          icmp.type = 0;
          break;
      }
    }
    else if (hl.key == "code") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          icmp.code = set_customnum(hl.value, hl.key, UCHAR_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          icmp.code = random_u8();
          break;
        case VALUE_TYPE_NONE:
          icmp.type = 0;
          break;
      }
    }
    else if (hl.key == "seq") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          icmp.seq = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          icmp.seq = random_u16();
          break;
        case VALUE_TYPE_NONE:
          icmp.seq = 0;
          break;
      }
    }
    else if (hl.key == "ident") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          icmp.id = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          break;
        case VALUE_TYPE_NONE:
          icmp.id = 0;
          break;
      }
    }
    else if (hl.key == "check") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          icmp.checksum = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          icmp.checksum = random_check();
          break;
        case VALUE_TYPE_NONE:
          icmp.checksum = 0;
          break;
      }
    }
    else if (hl.key == "data") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          if (hl.value.length() < MAX_TCP_DATA_SIZE) {
            const char *data;
            data = hl.value.c_str();
            icmp.tp.data = data;
            icmp.tp.datalen = strlen(data);
          }
          else
            intererror(i, "[icmp_header] (" + bp->keyword + ") <data>", "The maximum payload size on linux is 1400.");
          break;
        case VALUE_TYPE_RANDOM: {
          icmp.tp.data = random_str(random_num_u32(0, MAX_TCP_DATA_SIZE), DEFAULT_DICTIONARY);
          icmp.tp.datalen = strlen(icmp.tp.data);
          break;
        }
        case VALUE_TYPE_NONE:
          break;
      }
    }
    else
      intererror(i, "[icmp_header]", "Not found field \"" + hl.key + "\"\n");
    i++;
  }
  id->icmphdr_presets[bp->keyword] = icmp;
}

void _scanner_::get_udp_header(struct blockpreset *bp)
{
  struct temp_udp_header udp;
  struct headerline hl;

  udp.uh_sport = random_srcport();
  udp.uh_dport = 80;
  udp.ulen = -1;
  udp.check = -1;
  udp.tp.data = "";
  udp.tp.datalen = 0;

  size_t i = 0;
  for (const auto& line : bp->lines) {
    hl = parsehdrline(line, i);
    if (hl.valuetype == -1 && hl.valuetype == VALUE_TYPE_AUTO)
      continue;

    if (hl.key == "sport") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          udp.uh_sport = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          break;
        case VALUE_TYPE_NONE:
          udp.uh_sport = 0;
          break;
      }
    }
    else if (hl.key == "dport") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          udp.uh_dport = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          udp.uh_dport = random_u16();
          break;
        case VALUE_TYPE_NONE:
          udp.uh_dport = 0;
          break;
      }
    }
    else if (hl.key == "len") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          udp.ulen = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          udp.ulen = random_u16();
          break;
        case VALUE_TYPE_NONE:
          udp.ulen = 0;
          break;
      }
    }
    else if (hl.key == "check") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          udp.check = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          udp.check = random_check();
          break;
        case VALUE_TYPE_NONE:
          udp.check = 0;
          break;
      }
    }
    else if (hl.key == "data") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          if (hl.value.length() < MAX_TCP_DATA_SIZE) {
            udp.tp.data = hl.value.c_str();
            udp.tp.datalen = hl.value.length();
          }
          else
            intererror(i, "[udp_header] (" + bp->keyword + ") <data>", "The maximum payload size on linux is 1400.");
          break;
        case VALUE_TYPE_RANDOM: {
          udp.tp.data = random_str(random_num_u32(0, MAX_TCP_DATA_SIZE), DEFAULT_DICTIONARY);
          udp.tp.datalen = strlen(udp.tp.data);
          break;
        }
        case VALUE_TYPE_NONE:
          break;
      }
    }
    else
      intererror(i, "[udp_header]", "Not found field \"" + hl.key + "\"\n");
    i++;
  }
  id->udphdr_presets[bp->keyword] = udp;
}

void _scanner_::get_igmp_header(struct blockpreset *bp)
{
  struct temp_igmp_header igmp;
  struct headerline hl;

  igmp.type = 0x11;
  igmp.code = 0;
  igmp.check = -1;
  igmp.var = 0;
  igmp.tp.data = "";
  igmp.tp.datalen = 0;

  size_t i = 0;
  for (const auto& line : bp->lines) {
    hl = parsehdrline(line, i);
    if (hl.valuetype == -1 && hl.valuetype == VALUE_TYPE_AUTO)
      continue;

    if (hl.key == "type") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          igmp.type = set_customhex(hl.value, hl.key, UCHAR_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          igmp.type = random_u8();
          break;
        case VALUE_TYPE_NONE:
          igmp.type = 0;
          break;
      }
    }
    else if (hl.key == "code") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          igmp.code = set_customnum(hl.value, hl.key, UCHAR_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          igmp.code = random_u8();
          break;
        case VALUE_TYPE_NONE:
          break;
      }
    }
    else if (hl.key == "check") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          igmp.check = set_customnum(hl.value, hl.key, USHRT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          igmp.check = random_check();
          break;
        case VALUE_TYPE_NONE:
          igmp.check = 0;
          break;
      }
    }
    else if (hl.key == "var") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          igmp.var = set_customnum(hl.value, hl.key, UINT_MAX, i);
          break;
        case VALUE_TYPE_RANDOM:
          igmp.var = random_u32();
          break;
        case VALUE_TYPE_NONE:
          break;
      }
    }
    else if (hl.key == "data") {
      switch (hl.valuetype) {
        case VALUE_TYPE_CUSTOM:
          if (hl.value.length() < MAX_TCP_DATA_SIZE) {
            const char *data;
            data = hl.value.c_str();
            igmp.tp.data = data;
            igmp.tp.datalen = strlen(data);
          }
          else
            intererror(i, "[igmp_header] (" + bp->keyword + ") <data>", "The maximum payload size on linux is 1400.");
          break;
        case VALUE_TYPE_RANDOM: {
          igmp.tp.data = random_str(random_num_u32(0, MAX_TCP_DATA_SIZE), DEFAULT_DICTIONARY);
          igmp.tp.datalen = strlen(igmp.tp.data);
          break;
        }
        case VALUE_TYPE_NONE:
          break;
      }
    }
    else
      intererror(i, "[igmp_header]", "Not found field \"" + hl.key + "\"\n");
    i++;
  }
  id->igmphdr_presets[bp->keyword] = igmp;
}

void _scanner_::get_delay_preset(struct blockpreset *bp)
{
  struct delaypreset dp;
  struct delayline dl;

  for (const auto& line : bp->lines) {
    dl = parsedelayline(line);
    if (dl.delay != 0 || dl.numpackage != 0)
      dp.delays.push_back(dl);
  }

  id->delay_presets[bp->keyword] = dp;
}

void _scanner_::getall(void)
{
  struct blockpreset bp;
  struct blockpreset dotstart;
  size_t i;
  bool find = false;
  size_t endblockline = 0;

  for (i = 0; i < id->lines; i++) {
    if (Findword(DELAY, id->data[i]))
      endblockline = i;
    if (Findword(IPHEADER, id->data[i]))
      endblockline = i;
    if (Findword(ICMPHEADER, id->data[i]))
      endblockline = i;
    if (Findword(TCPHEADER, id->data[i]))
      endblockline = i;
    if (Findword(IGMPHEADER, id->data[i]))
      endblockline = i;
    if (Findword(UDPHEADER, id->data[i]))
      endblockline = i;
    if (Findword(MAIN, id->data[i]))
      endblockline = i;
  }

  for (i = 0; i < id->lines;) {
    find = false;
    if (Findword(DELAY, id->data[i])) {
      find = true;
      bp = parseblock(i);
      get_delay_preset(&bp);
      i = bp.end;
    }
    if (Findword(IPHEADER, id->data[i])) {
      find = true;
      bp = parseblock(i);
      get_ip_header(&bp);
      i = bp.end;
    }
    if (Findword(ICMPHEADER, id->data[i])) {
      find = true;
      bp = parseblock(i);
      get_icmp_header(&bp);
      i = bp.end;
    }
    if (Findword(TCPHEADER, id->data[i])) {
      find = true;
      bp = parseblock(i);
      get_tcp_header(&bp);
      i = bp.end;
    }
    if (Findword(IGMPHEADER, id->data[i])) {
      find = true;
      bp = parseblock(i);
      get_igmp_header(&bp);
      i = bp.end;
    }
    if (Findword(UDPHEADER, id->data[i])) {
      find = true;
      bp = parseblock(i);
      get_udp_header(&bp);
      i = bp.end;
    }
    if (Findword(MAIN, id->data[i])) {
      find = true;
      dotstart = parseblock(i);
      id->dotstart = dotstart;
      i = bp.end;
    }
    if (!id->data[i].empty() && !find)
      intererror(i, "No keyword match detected", id->data[i]);
    if (id->data[i] == id->data[endblockline])
      break;
    else
      continue;
    i++;
  }
}

void _scanner_::scanner(_interdata_ *i)
{
  id = i;
  getall();
}

int _interpreter_::get_type_active(const std::string& newline)
{
  if (Findword(DELAY_LINE, newline))
    return DELAY_TOKEN;
  if (Findword(SEND_PACKET_LINE, newline))
    return SEND_PACKET_TOKEN;
  if (Findword(RECV_PACKET_LINE, newline))
    return RECV_PACKET_TOKEN;
  if (Findword(WHILE_LINE, newline))
    return WHILE_TOKEN;

  return -1;

}

void _delay_(long long nanoseconds)
{
  struct timespec req, rem;

  req.tv_sec = nanoseconds / 1000000000;
  req.tv_nsec = nanoseconds % 1000000000;

  while (nanosleep(&req, &rem) == -1)
    req = rem;
}

#include <regex>
struct sendpktline _interpreter_::get_send_options(const std::string& line)
{
  struct sendpktline res;
  std::regex pattern(R"((\w+)=([\w,]+)(;|$))");

  auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
  auto end = std::sregex_iterator();

  res.count = 0;
  res.protocol = "";
  res.delay = "";

  for (std::sregex_iterator i = begin; i != end; ++i) {
    std::smatch match = *i;
    std::string key = match[1];
    std::string value = match[2];

    if (key == KEY_COUNT || key == KEY_COUNT_1 || key == KEY_COUNT_2 || key == KEY_COUNT_3)
      res.count = std::stoi(value);
    else if (key == KEY_PROTOCOL || key == KEY_PROTOCOL_1 || key == KEY_PROTOCOL_2)
      res.protocol = value;
    else if (key == KEY_IPHEADER)
      res.hp.iphdr = value;
    else if (key == KEY_TCPHEADER)
      res.hp.tcphdr = value;
    else if (key == KEY_ICMPHEADER)
      res.hp.icmphdr = value;
    else if (key == KEY_IGMPHEADER)
      res.hp.igmphdr = value;
    else if (key == KEY_UDPHEADER)
      res.hp.udphdr = value;
    else if (key == KEY_DELAY || key == KEY_DELAY_1 || key == KEY_DELAY_2 || key == KEY_DELAY_3)
      res.delay = value;
  }

  return res;
}

#include <sys/socket.h>
int getprotonum(const std::string& proto)
{
  if (proto == "icmp")
    return IPPROTO_ICMP;
  else if (proto == "tcp")
    return IPPROTO_TCP;
  else if (proto == "udp")
    return IPPROTO_UDP;
  else if (proto == "igmp")
    return IPPROTO_IGMP;
  else if (proto == "ip")
    return IPPROTO_IP;

  return -1;
}

void _interpreter_::checkoptions(u8 protocol, struct sendpktline *spl)
{
  if (spl->protocol.empty())
    intererror(0, "PROTOCOL", "the protocol field is blank, that's weird...");

  if (spl->count == 0) {
    interwarning(0, "COUNT", "the count field is blank, will automatically be set to (30)");
    spl->count = 30;
  }
  if (spl->delay.empty())
    interwarning(0, "DELAY", "the delay field is blank, will automatically be set to (0)");

  if (spl->hp.iphdr.empty())
    intererror(0, "HEADER", "ip_header required but not found");

  if (!spl->hp.iphdr.empty()) {
    auto it1 = id->iphdr_presets.find(spl->hp.iphdr);
    if (it1 == id->iphdr_presets.end())
      intererror(0, "HEADER", "ip_header " + spl->hp.iphdr + " not found");
  }
  if (!spl->hp.tcphdr.empty() || protocol == IPPROTO_TCP) {
    auto it2 = id->tcphdr_presets.find(spl->hp.tcphdr);
    if (it2 == id->tcphdr_presets.end())
      intererror(0, "HEADER", "tcp_header " + spl->hp.tcphdr + " not found");
  }
  if (!spl->hp.icmphdr.empty() || protocol == IPPROTO_ICMP) {
    auto it3 = id->icmphdr_presets.find(spl->hp.icmphdr);
    if (it3 == id->icmphdr_presets.end())
      intererror(0, "HEADER", "icmp_header " + spl->hp.icmphdr + " not found");
  }
  if (!spl->hp.igmphdr.empty() || protocol == IPPROTO_IGMP) {
    auto it4 = id->igmphdr_presets.find(spl->hp.igmphdr);
    if (it4 == id->igmphdr_presets.end())
      intererror(0, "HEADER", "igmp_header " + spl->hp.igmphdr + " not found");
  }
  if (!spl->hp.udphdr.empty() || protocol == IPPROTO_UDP) {
    auto it5 = id->udphdr_presets.find(spl->hp.udphdr);
    if (it5 == id->udphdr_presets.end())
      intererror(0, "HEADER", "udp_header " + spl->hp.udphdr + " not found");
  }
}

#define BUILD_IP(data, len, _proto, reslen) \
  do { \
    bool df = false; \
    if (iph.mtu == -1 || iph.frag_off == -2) df = true; \
    res = ip4_build(iph.saddr, iph.daddr, iph.protocol, iph.ttl, iph.ident, \
        iph.tos, df, iph.ipopt, iph.ipoptlen, (char*)data, len, &(reslen)); \
    ip = (struct ip4_hdr*)res; \
    if (iph.protocol == -1) \
      ip->proto = (_proto); \
    if (iph.frag_off != -1 && iph.frag_off != -2) \
      ip->off = htons(iph.frag_off); \
    if (iph.ihl != -1) \
      ip->ihl = iph.ihl; \
    if (iph.tot_len != -1) \
      ip->totlen = htons(iph.tot_len); \
    if (iph.tot_len != -1 || iph.ihl != -1 || iph.protocol == -1) \
      ip->check = ip_check_add((u16*)ip, sizeof(struct ip4_hdr) + iph.ipoptlen, 0); \
    if (iph.check != -1) { \
      ip->check = 0; \
      ip->check = htons(iph.check); \
    } \
  } while (0)

u8* _interpreter_::sendtcp(int fd, struct sendpktline *spl, u32 *plen, struct sockaddr_in *dst)
{
  struct temp_ip_header iph;
  struct temp_tcp_header tcph;
  struct sockaddr_in resdst;
  struct tcp_hdr *tcp;
  struct ip4_hdr *ip;
  u8 *tcpopt = NULL;
  int tcpoptlen = 0;
  u8* res;
  u32 reslen;
  u32 tcplen;

  iph = id->iphdr_presets[spl->hp.iphdr];
  tcph = id->tcphdr_presets[spl->hp.tcphdr];

  /* BUILD TCP */
  tcp = (struct tcp_hdr*)tcp_build(tcph.th_sport, tcph.th_dport,
      tcph.th_seq, tcph.th_ack, tcph.th_x2, tcph.th_flags, tcph.th_win,
      tcph.th_urp, tcpopt, tcpoptlen, tcph.tp.data, tcph.tp.datalen, &tcplen);
  if (tcph.th_off != -1) {
    tcp->th_off = tcph.th_off;
    std::cout << tcph.th_off << std::endl;
  }
  if (tcph.th_sum == -1)
    tcp->th_sum = ip4_pseudocheck(iph.saddr, iph.daddr, IPPROTO_TCP, tcplen, (struct tcp_hdr*)tcp);
  else
    tcp->th_sum = tcph.th_sum;

  /* BUILD IP */
  BUILD_IP(tcp, tcplen, IPPROTO_TCP, reslen);

  resdst.sin_addr.s_addr = ip->dst;
  resdst.sin_family = AF_INET;

  if (tcp)
    free(tcp);
  *dst = resdst;
  *plen = reslen;
  return res;
}

u8* _interpreter_::sendicmp(int fd, struct sendpktline *spl, u32 *plen, u16 seq, struct sockaddr_in *dst)
{
  struct temp_ip_header iph;
  struct temp_icmp4_header icmph;
  struct ip4_hdr *ip;
  struct sockaddr_in resdst;
  struct icmp4_hdr icmp;
  u8* res;
  u32 reslen;

  iph = id->iphdr_presets[spl->hp.iphdr];
  icmph = id->icmphdr_presets[spl->hp.icmphdr];

  /* BUILD ICMP */
  u8 *datastart = icmp.data;
  int dlen = sizeof(icmp.data);
  int icmplen = 0;
  char *ping = (char *)&icmp;
  icmp.type = icmph.type;
  icmp.code = icmph.code;
  if (icmp.type == 8)
    icmplen = 8;
  else if (icmp.type == 13 && icmp.code == 0) {
    icmplen = 20;
    memset(datastart, 0, 12);
    datastart += 12;
    dlen -= 12;
  }
  else if (icmp.type == 17 && icmp.code == 0) {
    icmplen = 12;
    memset(datastart, 0, 4);
    datastart += 4;
    dlen -= 4;
  }
#ifndef MIN
  #define MIN(a,b) ((a) <= (b) ? (a) : (b))
#endif
  if (icmph.tp.datalen > 0) {
    icmplen += MIN(dlen, icmph.tp.datalen);
    if (!icmph.tp.data)
      memset(datastart, 0, MIN(dlen, icmph.tp.datalen));
    else
      memcpy(datastart, icmph.tp.data, MIN(dlen, icmph.tp.datalen));
  }
  icmp.id = htons(icmph.id);
  if (icmph.seq != -1)
    icmp.seq = htons(icmph.seq);
  else
    icmp.seq = seq;
  icmp.check = 0;
  if (iph.check == -1)
    icmp.check = in_check((u16*)ping, icmplen);
  else
    icmp.check = htons(icmph.checksum);

  /* BUILD IP */
  BUILD_IP(ping, icmplen, IPPROTO_ICMP, reslen);

  resdst.sin_addr.s_addr = ip->dst;
  resdst.sin_family = AF_INET;

  *dst = resdst;
  *plen = reslen;
  return res;
}

u8* _interpreter_::sendip(int fd, struct sendpktline *spl, u32 *plen, struct sockaddr_in *dst)
{
  struct temp_ip_header iph;
  struct sockaddr_in resdst;
  struct ip4_hdr *ip;
  u8* res;
  u32 reslen;

  iph = id->iphdr_presets[spl->hp.iphdr];

  /* BUILD IP */
  BUILD_IP(NULL, 0, IPPROTO_IP, reslen);

  resdst.sin_addr.s_addr = ip->dst;
  resdst.sin_family = AF_INET;

  *dst = resdst;
  *plen = reslen;
  return res;
}

u8* _interpreter_::sendudp(int fd, struct sendpktline *spl, u32 *plen, struct sockaddr_in *dst)
{
  struct temp_ip_header iph;
  struct temp_udp_header udph;
  struct sockaddr_in resdst;
  struct ip4_hdr *ip;
  struct udp_hdr *udp;
  u8* res;
  u32 reslen;
  u32 udplen;

  iph = id->iphdr_presets[spl->hp.iphdr];
  udph = id->udphdr_presets[spl->hp.udphdr];

  /* BUILD UDP */
  udp = (struct udp_hdr*)udp_build(udph.uh_sport, udph.uh_dport,
      udph.tp.data, udph.tp.datalen, &udplen);
  if (udph.ulen != -1)
    udp->len = htons(udph.ulen);
  if (udph.check == -1)
    udp->check = ip4_pseudocheck(iph.saddr, iph.daddr, IPPROTO_UDP, udplen, udp);
  else
    udp->check = htons(udph.check);

  /* BUILD IP */
  BUILD_IP(udp, udplen, IPPROTO_UDP, reslen);

  resdst.sin_addr.s_addr = ip->dst;
  resdst.sin_family = AF_INET;

  if (udp)
    free(udp);

  *dst = resdst;
  *plen = reslen;
  return res;
}

u8* _interpreter_::sendigmp(int fd, struct sendpktline *spl, u32 *plen, struct sockaddr_in *dst)
{
  struct temp_ip_header iph;
  struct temp_igmp_header igmph;
  struct ip4_hdr *ip;
  struct sockaddr_in resdst;
  struct igmp_hdr igmp;
  u8* res;
  u32 reslen;
  u32 igmplen;

  iph = id->iphdr_presets[spl->hp.iphdr];
  igmph = id->igmphdr_presets[spl->hp.igmphdr];

  /* BUILD IGMP */
  u32 *datastart = (u32 *)igmp.data;
  int dlen = sizeof(igmp.data);
  char *pkt = (char *)&igmp;
  igmp.type = igmph.type;
  igmp.var = igmph.var;
  igmp.code = igmph.code;
  switch (igmp.type) {
    case 0x11:
    case 0x12:
    case 0x16:
    case 0x17:
    case 0x22:
      igmplen = 8;
      break;
  }
  if (igmph.tp.datalen > 0) {
    igmplen += MIN(dlen, igmph.tp.datalen);
    if (!igmph.tp.data)
      memset(datastart, 0, MIN(dlen, igmph.tp.datalen));
    else
      memcpy(datastart, igmph.tp.data, MIN(dlen, igmph.tp.datalen));
  }
  igmp.check = 0;
  if (igmph.check == -1)
    igmp.check = in_check((u16*) pkt, igmplen);
  else
    igmp.check = htons(igmph.check);

  /* BUILD IP */
  BUILD_IP(pkt, igmplen, IPPROTO_IGMP, reslen);

  resdst.sin_addr.s_addr = ip->dst;
  resdst.sin_family = AF_INET;

  *dst = resdst;
  *plen = reslen;
  return res;
}

void _interpreter_::sendpacket(u8 proto, int fd, struct sendpktline *spl)
{
  long long delay;
  bool presetdelay = false;
  bool nodelay = false;
  struct delaypreset dp;
  struct temp_ip_header iph;
  struct sockaddr_in dst;
  u16 icmpseq = 1;
  u8* packet = NULL;
  u32 plen = 0;
  dst.sin_family = AF_INET;

  delay = delay_convert(spl->delay);
  if (delay == -1 && spl->delay != "none" && spl->delay != "0" && !spl->delay.empty()) {
    presetdelay = true;

    auto it = id->delay_presets.find(spl->delay);
    if (it != id->delay_presets.end())
      dp = id->delay_presets[spl->delay];
    else
      intererror(0, "DELAY", "preset " + spl->delay + " not found");
  }
  if (spl->delay == "none" || spl->delay == "0" || spl->delay.empty())
    nodelay = true;

  for (size_t i = 1; i <= spl->count; i++) {
    if (!presetdelay && !nodelay)
      _delay_(delay);
    else {
      if (!nodelay) {
        for (const auto& delay : dp.delays) {
          if ((size_t)delay.numpackage == i) {
            _delay_(delay.delay);
            interverbose("delay on", std::to_string(i) + " pkt in " + std::to_string(delay.delay) + " nanoseconds");
          }
        }
      }
    }
    plen = 0;
    iph = id->iphdr_presets[spl->hp.iphdr];
    if (proto == IPPROTO_TCP) {
      packet = sendtcp(fd, spl, &plen, &dst);
      ip4_send(NULL, fd, &dst, iph.mtu, packet, plen);
    }
    else if (proto == IPPROTO_ICMP) {
      packet = sendicmp(fd, spl, &plen, icmpseq, &dst);
      ip4_send(NULL, fd, &dst, iph.mtu, packet, plen);
      icmpseq++;
    }
    else if (proto == IPPROTO_UDP) {
      packet = sendudp(fd, spl, &plen, &dst);
      ip4_send(NULL, fd, &dst, iph.mtu, packet, plen);
    }
    else if (proto == IPPROTO_IP) {
      packet = sendip(fd, spl, &plen, &dst);
      ip4_send(NULL, fd, &dst, iph.mtu, packet, plen);
    }
    else if (proto == IPPROTO_IGMP) {
      packet = sendigmp(fd, spl, &plen, &dst);
      ip4_send(NULL, fd, &dst, iph.mtu, packet, plen);
    }
    if (packet)
      free(packet);
  }
}

void _interpreter_::sendprobe(int fd, struct headerline hl)
{
  int proto;
  struct sendpktline spl;
  spl = get_send_options(hl.value);

  proto = getprotonum(spl.protocol);
  if (proto == -1)
    intererror(0, "PROTOCOL", "protocol \"" + spl.protocol + "\" not found, or unsupported.");
  checkoptions(proto, &spl);
  interverbose("[" + spl.protocol + "] send package(s)", "(" + std::to_string(spl.count) + ") num / (" + spl.delay +") delay / ("
    + spl.hp.iphdr + ") iphdr | (" + spl.hp.tcphdr + ") tcphdr | ("
    + spl.hp.icmphdr + ") icmphdr | (" + spl.hp.udphdr + ") udphdr | (" + spl.hp.igmphdr + ") igmphdr");

  sendpacket(proto, fd, &spl);
}

void _interpreter_::interpreter(_interdata_ *i, bool verbose)
{
  int typeline, fd;
  struct headerline hl;
  struct sendpktline spl;
  std::string newline;
  this->verbose = verbose;

  id = i;
  fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  assert(fd != -1);

  for (const auto& line : id->dotstart.lines) {
    typeline = get_type_active(line);
    REMOVE_WHITESPACE(newline);

    if (typeline == -1)
      intererror(0, "[main]", "Active not found \"" + newline + "\"");

    hl = parsehdrline(line, 0);

    if (typeline == DELAY_TOKEN) {
      interverbose("main delay", hl.value + " wating...");
      _delay_(delay_convert(hl.value));
    }
    if (typeline == SEND_PACKET_TOKEN) {
      sendprobe(fd, hl);
    }
  }
  close(fd);
}
