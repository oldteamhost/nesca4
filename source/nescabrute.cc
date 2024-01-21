/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "../include/nescabrute.h"
#include "../include/nescautils.h"
#include "../ncsock/include/socket.h"
#include "../ncsock/include/ftp.h"
#include "../ncsock/include/http.h"
#include "../ncsock/include/utils.h"
#include "../include/nescautils.h"

#define MAXLEN 6554543
#define START_TIMEOUT 1200

extern std::mutex ls;

#ifdef HAVE_HIKVISION
#include "../library/HCNetSDK.h"
LONG V0_brute_hikvision(char* ip, char* login, char* pass, int port) {
  NET_DVR_DEVICEINFO device = {0};
  return (NET_DVR_Login(ip, port, login, pass, &device));
}
LONG V30_brute_hikvision(char* ip, char* login, char* pass, int port) {
  NET_DVR_DEVICEINFO_V30 device = {0};
  return (NET_DVR_Login_V30(ip, port, login, pass, &device));
}
LONG V40_brute_hikvision(char *ip, char* login, char* pass, int port)
{
  NET_DVR_USER_LOGIN_INFO logininfo = {0};
  NET_DVR_DEVICEINFO_V40 device = {0};

  logininfo.bUseAsynLogin = false;
  logininfo.wPort = port;

  strcpy(logininfo.sDeviceAddress, ip);
  strcpy(logininfo.sUserName, login);
  strcpy(logininfo.sPassword, pass);

  return (NET_DVR_Login_V40(&logininfo, &device));
}
bool hikvisionauth(const char* ip, u16 port, const char* login, const char* pass)
{
  char *_ip, *_login, *_pass;
  LONG res;

  freopen("/dev/null", "w", stderr);
  NET_DVR_Init();

  _ip = const_cast<char*>(ip);
  _login = const_cast<char*>(login);
  _pass = const_cast<char*>(pass);

  res = V0_brute_hikvision(_ip, _login, _pass, port);

  ls.lock();
  NET_DVR_Logout(res);
  NET_DVR_Cleanup();
  ls.unlock();

  if (res < 0)
    return false;
  return true;
}
#endif

#ifdef HAVE_DVR
#include "../library/dhnetsdk.h"
void CALLBACK MyDisconnectCallback(LLONG lLoginID, char *pchDVRIP,
    LONG nDVRPort, LDWORD dwUser) {
  return;
}

bool dvrauth(const char* ip, u16 port, const char* login, const char* pass)
{
  NET_DEVICEINFO devinfo = {0};
  char *_ip, *_login, *_pass;
  u64 res = 0;

  _ip = const_cast<char*>(ip);
  _login = const_cast<char*>(login);
  _pass = const_cast<char*>(pass);

  CLIENT_Init(MyDisconnectCallback, 0);
  res = CLIENT_Login(_ip, port, _login, _pass, &devinfo);

  ls.lock();
  CLIENT_Logout(res);
  CLIENT_Cleanup();
  ls.unlock();

  if (res == 0)
    return false;
  return true;
}
#endif

void NESCABRUTE::newconnect(const char* ip, u16 port, u8 proto,
    int timeoutms, int maxconnections)
{
  if (proto == HIKVISION_BRUTEFORCE || proto == RVI_BRUTEFORCE)
    return;
  
  std::chrono::high_resolution_clock::time_point start, end;
  std::chrono::microseconds duration;
  int res = 0, code = 0;
  u8 temp[MAXLEN];

  if (numconnections > maxconnections)
    return;

  if (!okprobe)
    start = std::chrono::high_resolution_clock::now();
  if (proto == FTP_BRUTEFORCE)
    res = session(ip, port, timeoutms, temp, MAXLEN);
  else
    res = session(ip, port, timeoutms, NULL, 0);
  if (!okprobe)
    end = std::chrono::high_resolution_clock::now();
  if (res == -1)
    return;

  if (!okprobe) {
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    rttmshost = (duration.count() / 1000.0) * 3;
    okprobe = true;
  }

  if (proto == FTP_BRUTEFORCE) {
    code = atoi((char*)temp);
    if (code != R_220)
      return;
  }

  ls.lock();
  connections.push_back(res);
  numconnections++;
  ls.unlock();
}

void NESCABRUTE::authprobe(int fd, u8 proto, const char* login, const char* pass, int timeoutms)
{
  switch (proto) {
    case FTP_BRUTEFORCE:
      auth = ftpauth(fd, login, pass);
      break;
    case HTTP_BRUTEFORCE:
      auth = auth_http_basic(fd, ip, path, login, pass);
      break;
      
    case RVI_BRUTEFORCE:
#ifdef HAVE_DVR
      auth = dvrauth(ip, 37777, login, pass);
#endif
      break;

    case HIKVISION_BRUTEFORCE:
#ifdef HAVE_HIKVISION
      auth = hikvisionauth(ip, 8000, login, pass);
#endif
      break;
  }
}

int NESCABRUTE::getrandomcon(void)
{
  u32 index;
  if (connections.empty())
    return -1;

  mt19937_seed(generate_seed());
  index = mt19937_random() % connections.size();

  return connections[index];
}

bool NESCABRUTE::checkres(const char *login, const char *pass)
{
  if (!auth)
    return false;
  reslogin = login;
  respass = pass;

  for (const auto& c : connections)
    if (c != -1)
      close(c);

  return true;
}

int NESCABRUTE::gettimeoutms(void)
{
  if (customtimeout)
    return customtimeoutms;
  else {
    if (!okprobe)
      return START_TIMEOUT;
    else {
      if ((int)rttmshost > START_TIMEOUT)
        return START_TIMEOUT;
      return (int)rttmshost;
    }
  }
}

std::string NESCABRUTE::getlogin(void)
{
  if (reslogin)
    return reslogin;
  else
    return "";
}

std::string NESCABRUTE::getpass(void)
{
  if (reslogin)
    return respass;
  else
    return "";
}

std::string NESCABRUTE::getres_nescastyle(void)
{
  if (!getlogin().empty() && !getpass().empty())
    return (getlogin() + ":" + getpass() + "@");
  return "";
}

void NESCABRUTE::runbrute(const std::string& ip, int port, std::string typebrute, nesca_prints* np)
{
  np->yellow_html_on();
  std::cout << "  * " << typebrute << " " + ip + ":" + std::to_string(port) + " BRUTEFORCE\n";
  reset_colors;
}

std::string NESCABRUTE::getprotostr(u8 proto)
{
  switch (proto) {
    case HTTP_BRUTEFORCE:
      return "HTTP";
    case FTP_BRUTEFORCE:
      return "FTP";
    case RVI_BRUTEFORCE:
      return "RVI(DVR)";
    case HIKVISION_BRUTEFORCE:
      return "HIKVISION";
  }
  return "n/a";
}

NESCABRUTE::NESCABRUTE(int threads, const char* ip, const char* path,
    u16 port, int maxconnections, int attempts, int timeoutms, int delayms,
    u8 proto, logins_t login, passwords_t pass, nesca_prints *np)
{
  /*
    std::cout << "threads: " << threads << std::endl;
    std::cout << "maxcon: " << maxconnections << std::endl;
    std::cout << "timeout: " << timeoutms << std::endl;
    std::cout << "attempts: " << attempts << std::endl;
    std::cout << "delayms: " << delayms << std::endl;
  */

  runbrute(ip, port, getprotostr(proto), np);
  thread_pool pool(threads);
  int i, combinations = 0, procents, total;
  reslogin = NULL;
  respass = NULL;

  this->path = "";
  this->ip = ip;
  if (path)
    this->path = path;
  total = login.size() * pass.size();
  if (timeoutms != -1) {
    customtimeout = true;
    customtimeoutms = timeoutms;
  }

  if (proto != HIKVISION_BRUTEFORCE && proto != RVI_BRUTEFORCE) {
    for (i = 0; i < 5; i++) {
      newconnect(ip, port, proto, gettimeoutms(), maxconnections);
      if (!connections.empty())
        break;
    }
    if (connections.empty())
      return;
  }

  for (const auto& l : login) {
    for (const auto& p : pass) {
      if (combinations % (get_log(total)) == 0) {
        procents = (combinations * 100) / total;
        std::cout << "    " << np->main_nesca_out("#", "BRUTE " + std::to_string(combinations) +
            " out of " + std::to_string(total) + " passwd", 6, "", "",
            std::to_string(procents)+"%", "", "") << std::endl;
      }
      pool.enqueue([this, ip, port, proto, attempts, maxconnections, l, p]() {
        newconnect(ip, port, proto, gettimeoutms(), maxconnections);
        for (int i = 1; i <= attempts; i++) {
          authprobe(getrandomcon(), proto, l.c_str(), p.c_str(), gettimeoutms());
          ls.lock();
          bool check = checkres(l.c_str(), p.c_str());
          ls.unlock();
          if (check)
            return;
        }
      });
      combinations++;
      delayy(delayms);
    }
  }
}
