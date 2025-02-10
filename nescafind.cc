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

#include "include/nescafind.h"
#include "include/nescadata.h"
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

NESCAFINDLINE NESCAFIND::lineget(const std::string &txt)
{
  std::vector<std::string>  strings;
  std::string               strres, numres;
  NESCAFINDLINE             res;
  size_t                    o, arg;
  bool                      str, num, num2;

  if (txt.empty())
    return {};

  if (txt[0]=='r'||txt[0]=='R')
    res.regex=1;
  for (o=str=num=num2=0,arg=1;
      o<txt.length();o++) {
    if (txt[o]=='\''&&txt[(o-1)]!='\\') {
      if (str) {
        str=0;
        strings.push_back(strres);
      }
      else {
        str=1;
        strres.clear();
      }
      continue;
    }
    if (str)
      strres.push_back(txt[o]);
    if (txt[o]==','&&!str&&
        txt[(o-1)]!='\\') {
      arg++;
      continue;
    }
    if (arg==3)
      num=1;
    if (arg==4&&!num2) {
      strings.push_back(numres);
      numres.clear();
      num=0;
      num2=1;
    }
    if (num)
      numres.push_back(txt[o]);
    if (num2)
      numres.push_back(txt[o]);
  }
  strings.push_back(numres);

  if (strings.size()<4)
    return {};
  for (const auto&s:strings)
    if (s.empty())
      return {};

  res.node=strings[0];
  res.info=strings[1];
  for (numres.clear(),o=0;o<strings[2].length();o++)
    if (strings[2][o]!=' '&&std::isdigit(strings[2][o]))
      numres.push_back(strings[2][o]);
  res.bruteforce=std::stoi(numres);
  for (numres.clear(),o=0;o<strings[3].length();o++)
    if (strings[3][o]!=' '&&std::isdigit(strings[3][o]))
      numres.push_back(strings[3][o]);
  res.find=std::stoi(numres);

  return res;
}

NESCAFIND::NESCAFIND(NESCADATA *ncsdata)
{
  size_t j, i;
  init(&ncsdata->opts);

  for (const auto &t:ncsdata->targets) {

    fileprobe(t, t->get_mainip(), FIND_IP);

    if (t->get_num_dns()>0)
      for (i=0;i<t->get_num_dns();i++)
        fileprobe(t, t->get_dns(i), FIND_DNS);

    if (!t->get_mac().empty())
      fileprobe(t, t->get_mac(), FIND_MAC);

    if (t->check_service()) {
      for (j=0;j<S_NUM;j++) {
        for (i=0;i<t->get_num_port();i++) {
          NESCASERVICE tmp=t->get_service(t->get_real_port(i), j);
          if (!tmp.init)
            continue;

          /* HTTP */
          if (tmp.service==S_HTTP) {
            for (const auto&s:tmp.info) {
              if (s.type=="html")
                fileprobe(t, s.info, FIND_HTTP_HTML);
              if (s.type=="redirect")
                fileprobe(t, s.info, FIND_HTTP_REDIRECT);
              if (s.type=="title")
                fileprobe(t, s.info, FIND_HTTP_TITLE);
            }
          }
          /* FTP */
          if (tmp.service==S_FTP) {
            for (const auto&s:tmp.info) {
              if (s.type=="header")
                fileprobe(t, s.info, FIND_FTP_HELLO);
            }
          }
        }
      }
    }

  }
}

void NESCAFIND::init(NESCAOPTS *opts)
{
  if (!opts->check_dbpath_flag())
    this->path=DEFAULT_DATABASE_PATH;
  else
    this->path=opts->get_dbpath_param();
}

std::vector<NESCAFINDLINE> NESCAFIND::fileget(void)
{
  std::vector<NESCAFINDLINE> res;
  std::string resbuf, tmp;
  std::ostringstream buf;
  std::ifstream f(path);
  NESCAFINDLINE tmpres;
  size_t o;

  if (!f)
    return {};
  buf<<f.rdbuf();
  resbuf=buf.str();

  for (o=0;o<resbuf.length();o++) {
    if (resbuf[o]==';'&&resbuf[(o-1)]!='\\') {
      tmpres=lineget(tmp);
      tmp.clear();
      res.push_back(tmpres);
      continue;
    }
    tmp.push_back(resbuf[o]);
  }

  return res;
}

/* from old NESCA4 */
bool contains_word(const std::string& word, const std::string& sentence)
{
  std::string lowerWord = word;
  std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), [](u8 c){ return std::tolower(c); });

  std::string lowerSentence = sentence;
  std::transform(lowerSentence.begin(), lowerSentence.end(), lowerSentence.begin(), [](u8 c){ return std::tolower(c); });

  std::string::size_type pos = lowerSentence.find(lowerWord);
  while (pos != std::string::npos) {
    if ((pos > 0 && std::isalpha(lowerSentence[pos - 1])) ||
   (pos + lowerWord.length() < lowerSentence.length() && std::isalpha(lowerSentence[pos + lowerWord.length()])))
      pos = lowerSentence.find(lowerWord, pos + 1);
    else
      return 1;
  }

  return 0;
}


bool applyregex(const std::string &pat, const std::string &txt)
{
  std::regex re(pat);
  return std::regex_search(txt, re);
}

std::string strtypefind(int find)
{
  switch (find) {
    case FIND_HTTP_HTML: return "html";
    case FIND_HTTP_REDIRECT: return "redirect";
    case FIND_HTTP_TITLE: return "title";
    case FIND_MAC: return "mac";
    case FIND_DNS: return "dns";
    case FIND_IP: return "ip";
    case FIND_FTP_HELLO: return "ftphello";
    default: return "???";
  }
}
NESCAFINDRESULT NESCAFIND::fileprobe(NESCATARGET *target, const std::string &node, int find)
{
  std::string resbuf, tmp;
  std::ostringstream buf;
  std::ifstream f(path);
  NESCAFINDLINE tmpres;
  NESCAFINDRESULT res;
  size_t o;
  bool ok;

  if (!f)
    return {};
  buf<<f.rdbuf();
  resbuf=buf.str();

  res.bruteforce=res.ok=0;
  res.info="";

  for (o=0;o<resbuf.length();o++) {
    if (resbuf[o]==';'&&resbuf[(o-1)]!='\\') {
      ok=0;
      tmpres=lineget(tmp);
      tmp.clear();

      if (find==-1||tmpres.find==find) {
        if (tmpres.regex) {
          if (applyregex(tmpres.node, node))
            ok=1;
        }
        else if (contains_word(tmpres.node, node))
          ok=1;
      }

      if (ok) {
        res.info=tmpres.info;
        res.bruteforce=tmpres.bruteforce;
        res.ok=1;
        target->add_dbres(res.info,
          strtypefind(find));
        /*
        if (res.bruteforce) {
          target->set_bruteforce(, int port, const std::string &other)
        }
        */

        return res;
      }
      continue;
    }
    tmp.push_back(resbuf[o]);
  }

  return {};
}
