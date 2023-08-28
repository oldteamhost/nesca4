/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
#include <cstring>
#include "../include/other.h"
#include "../include/nescalog.h"
#include "nescathread.h"
#include "../modules/include/hikvision.h"
#include "../config/compile.h"

#ifdef HAVE_CURL
#include "../ncbase/include/callbacks.h"
#endif

class brute_ftp_data
{
  private:
    std::string success_login;
    std::string success_pass;
  public:
    std::string get_success_login(void);
    std::string get_success_pass(void);
    void set_success_login(std::string success_login);
    void set_success_pass(std::string success_pass);
};

// brutforce smtp
std::string 
base64_encode(const std::string& input);
std::string 
brute_smtp(const std::string& ip, int port, const std::string& login, const std::string& pass,
        int brute_log, int verbose);
std::string 
threads_brute_smtp(const std::string ip, int port, const std::vector<std::string> logins,
        const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms);

// brutforce ftp
std::string 
brute_ftp(const std::string ip, int port, const std::string login, const std::string pass,
        int brute_log, int verbose);
// on threads
std::string 
threads_brute_ftp(const std::string ip, int port, const std::vector<std::string> logins,
        const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms);

// brutforce ssh
std::string 
brute_ssh(const std::string& ip, int port, const std::string login, const std::string pass,
        int brute_log, int verbose);
// on threads
std::string 
threads_brute_ssh(const std::string ip, int port, const std::vector<std::string> logins,
        const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms);

// brutforce rtsp
std::string 
brute_rtsp(const std::string ip, const std::string login, const std::string pass,
        int brute_log, int verbose);
// on threads
std::string 
threads_brute_rtsp(const std::string ip, const std::vector<std::string> logins,
        const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms);

// bruteforce http
std::string 
brute_http(const std::string ip, const std::string login, const std::string pass,
        const int verbose);
// on threads
std::string 
threads_brute_http(const std::string ip, const std::vector<std::string> logins,
        const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms);

// bruteforce hikvision
std::string 
brute_hikvision(const std::string ip, const std::string login, const std::string pass,
        int brute_log, const std::string& path);
// on threads
std::string 
threads_brute_hikvision(const std::string ip, const std::vector<std::string> logins,
        const std::vector<std::string> passwords, int brute_log, int brute_timeout_ms, const std::string&path);

// bruteforce rvi
std::string 
brute_rvi(const std::string ip, int port, const std::string login, const std::string pass,
        int brute_log);
// on threads
std::string 
threads_brute_rvi(const std::string ip, const int port, const std::vector<std::string> logins,
        const std::vector<std::string> passwords, int brute_log, int brute_timeout_ms);
#endif
