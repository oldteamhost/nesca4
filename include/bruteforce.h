#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <iostream>
#include <string>
#include <vector>

class brute_ftp_data{
    private:
        std::string success_login;
        std::string success_pass;
    public:
        std::string get_success_login(void);
        std::string get_success_pass(void);
        void set_success_login(std::string success_login);
        void set_success_pass(std::string success_pass);
};

// brutforce ftp
std::string brute_ftp(const std::string ip, const std::string login, const std::string pass, int brute_log, int verbose);
// on threads
std::string threads_brute_ftp(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms);

// brutforce ssh
std::string brute_ssh(const std::string& ip, const std::string login, const std::string pass, int brute_log, int verbose, int known_hosts);
// on threads
std::string threads_brute_ssh(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int known_hosts, int brute_timeout_ms);

// brutforce rtsp
std::string brute_rtsp(const std::string ip, const std::string login, const std::string pass, int brute_log, int verbose);
// on threads
std::string threads_brute_rtsp(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms);

// bruteforce http
std::string brute_http(const std::string ip, const std::string login, const std::string pass, const int verbose);
std::string threads_brute_http(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms);

// bruteforce hikvision
std::string brute_hikvision(const std::string ip, const std::string login, const std::string pass, int brute_log);
std::string threads_brute_hikvision(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int brute_timeout_ms);

#endif