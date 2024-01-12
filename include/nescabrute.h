/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
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
#include "../include/nescalog.h"
#include "nescathread.h"
#include "../config/compile.h"

typedef std::vector<std::string> logins_t;
typedef std::vector<std::string> passwords_t;

#define HTTP_BRUTEFORCE      0
#define FTP_BRUTEFORCE       1
#define SMTP_BRUTEFORCE      2
#define RVI_BRUTEFORCE       3
#define RTSP_BRUTEFORCE      4
#define HIKVISION_BRUTEFORCE 5

class NESCABRUTE {
  private:
    std::vector<int> connections;
    int numconnections = 0;
    bool auth = false;
    const char *path;
    const char *ip;
    const char *reslogin, *respass;

    double rttmshost = 0.0;
    bool okprobe = false;
    bool customtimeout = false;
    int customtimeoutms = 0;

    void newconnect(const char* ip, u16 port, u8 proto,
        int timeoutms, int maxconnections);
    void authprobe(int fd, u8 proto, const char* login,
        const char* pass, int timeoutms);
    int gettimeoutms(void);
    int getrandomcon(void);
    bool checkres(const char *login, const char *pass);
    void runbrute(const std::string& ip, int port,
        std::string typebrute, nesca_prints *np);
    std::string getprotostr(u8 proto);

  public:
    NESCABRUTE(int threads, const char* ip, const char* path,
        u16 port, int maxconnections, int attempts, int timeoutms, int delayms,
        u8 proto, logins_t login, passwords_t pass, nesca_prints *np);

    std::string getlogin(void);
    std::string getpass(void);
    std::string getres_nescastyle(void);
};

bool hikvisionauth(const char* ip, u16 port, const char* login, const char* pass);
bool dvrauth(const char* ip, u16 port, const char* login, const char* pass);

#endif
