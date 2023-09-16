/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#ifndef _BRUTEFORCE_H
#define _BRUTEFORCE_H

#include <cstdint>
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
#include "../ncsock/include/bruteforce.h"

std::string 
threads_bruteforce(const std::vector<std::string>& login, std::vector<std::string>& pass,
        std::string http_path, std::string ip, int port, int delay, uint8_t proto, int brute_log);



std::string 
brute_ssh(const std::string& ip, int port, const std::string login, const std::string pass,
        int brute_log, int verbose);
std::string 
threads_brute_ssh(const std::string ip, int port, const std::vector<std::string> logins,
        const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms);

std::string 
brute_hikvision(const std::string ip, const std::string login, const std::string pass,
        int brute_log, const std::string& path);
std::string 
threads_brute_hikvision(const std::string ip, const std::vector<std::string> logins,
        const std::vector<std::string> passwords, int brute_log, int brute_timeout_ms, const std::string&path);
#endif
