/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef SMTPINFO_H 
#define SMTPINFO_H
#include <iostream>
#include <algorithm>
#include <regex>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../../ncsock/include/socket.h"

#define SMTP_ERROR "N/A"

std::string 
smtp_get_220_response(const std::string& ip, int port, int verbose);

#endif
