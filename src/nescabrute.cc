/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "../include/nescabrute.h"
#include "../include/nescautils.h"
#include "../ncsock/include/bruteforce.h"
#include "../ncsock/include/socket.h"
#include "../ncsock/include/ftp.h"
#include "../ncsock/include/base.h"
#include "../ncsock/include/strbase.h"
#include <mutex>
#include <string>

nesca_prints np1;

std::string
threads_bruteforce(const std::vector<std::string>& login, std::vector<std::string>& pass,
    std::string http_path, std::string ip, int port, int delay, uint8_t proto, int brute_log)
{
  std::vector<std::future<void>> futures;
  thread_pool pool(100);
  std::string result = "";
  std::mutex wait;

  int total = login.size() * pass.size();
  int combinations = 0;

  for (const auto& l : login){
    for (const auto& p : pass){
      futures.push_back(pool.enqueue([&combinations, &total, &wait, brute_log, l, p, ip, port, proto, http_path, delay, &result]() {
        wait.lock();
        if (brute_log)
          np1.nlog_custom("LOG", "                 try: " + l + "@" + p + " [BRUTEFORCE]\n", 1);

        bruteforce_opts bo;
        bo.dest_ip = ip.c_str();
        bo.dest_port = port;
        bo.proto = proto;
        bo.http_path = http_path.c_str();
        bo.delay_ms = delay;
        bo.login = l.c_str();
        bo.pass = p.c_str();
        wait.unlock();

        int auth = ncsock_bruteforce(&bo);
        if(auth == 0) {
          result = l + ":" + p + "@";
        }

        combinations++;
        if (combinations % 20 == 0) {
          int procents = (combinations * 100) / total;
          std::cout << np1.main_nesca_out("#", "BRUTE "+std::to_string(combinations)+" out of "+std::to_string(total) +" passwd", 6, "", "", std::to_string(procents)+"%", "", "") << std::endl;
        }
      }));
    }
  }

  for (auto& future : futures){future.wait();}
  if (!result.empty()){return result;}
  return "";
}

LONG
V0_brute_hikvision(char* ip, char* login, char* pass, int port)
{
  NET_DVR_DEVICEINFO device = {0};
  return (NET_DVR_Login(ip, 8000, login, pass, &device));
}

LONG
V30_brute_hikvision(char* ip, char* login, char* pass, int port)
{
  NET_DVR_DEVICEINFO_V30 device = {0};
  return (NET_DVR_Login_V30(ip, port, login, pass, &device));
}

LONG
V40_brute_hikvision(char *ip, char* login, char* pass, int port)
{
  NET_DVR_USER_LOGIN_INFO logininfo = {0};
  NET_DVR_DEVICEINFO_V40 device = {0};

  logininfo.bUseAsynLogin = false;
  logininfo.wPort = 8000;

  strcpy(logininfo.sDeviceAddress, ip);
  strcpy(logininfo.sUserName, login);
  strcpy(logininfo.sPassword, pass);

  return (NET_DVR_Login_V40(&logininfo, &device));
}

std::string
brute_hikvision(std::string ip, std::string login, std::string pass, int brute_log, const std::string& path)
{
#ifdef HAVE_HIKVISION
  if (brute_log)
    np1.nlog_custom("HIKVISION", "                 try: " + login + "@" + pass + " [BRUTEFORCE]\n", 1);

  LONG res;
  std::string result = "";

  freopen("/dev/null", "w", stderr);
  NET_DVR_Init();

  char *_ip = ip.data();
  char *_login = login.data();
  char *_pass = pass.data();
  u16 port = 8000;

  res = V0_brute_hikvision(_ip, _login, _pass, port);

  /*
  if (res < 0) {
    res = V30_brute_hikvision(_ip, _login, _pass, port);
    if (res < 0) {
      res = V40_brute_hikvision(_ip, _login, _pass, port);
      if (res < 0)
        goto sum;
    }
  }
  */

  if (res < 0)
    goto sum;

  result = login + ":" + pass + "@";
  goto sum;

#else
  return "no-hikvision";
#endif
sum:
  NET_DVR_Logout(res);
  NET_DVR_Cleanup();
  return result;
}

std::mutex fuck;

std::string
threads_brute_hikvision(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords,
    int brute_log, int brute_timeout_ms, const std::string&path)
{
  std::vector<std::string> results;
  std::vector<std::future<void>> futures;
  thread_pool pool(100);

  for (const auto& login : logins) {
    for (const auto& password : passwords) {
      delayy(brute_timeout_ms);
      futures.push_back(pool.enqueue([ip, login, password, brute_log, path, &results]() {
        std::string temp = brute_hikvision(ip, login, password, brute_log, path);

        fuck.lock();
        if (!temp.empty())
          results.push_back(temp);
        fuck.unlock();
      }));
    }
  }
  for (auto& future : futures) {future.wait();}
  if (!results.empty()) {return results[0];} else{return "";}

  return "";
}
