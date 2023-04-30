#include <iostream>
#include <vector>

// brutforce ftp
std::string brute_ftp(const std::string ip, const std::string login, const std::string pass, int brute_log, int verbose);
// on threads
std::string threads_brute_ftp(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms);

// brutforce ssh
std::string brute_ssh(const std::string& ip, const std::string login, const std::string pass, int brute_log, int verbose, int known_hosts);
// on threads
std::string threads_brute_ssh(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int known_hosts, int brute_timeout_ms);

// brutforce rtsp
std::string brute_rtsp(std::string ip, std::string login, std::string pass, int brute_log, int verbose);
// on threads
std::string threads_brute_rtsp(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms);
