#ifndef SMTPINFO_H 
#define SMTPINFO_H
#include <iostream>
#include <algorithm>
#include <regex>
#include <cstring>
#include <string>
#include "easysock.h"

#define SMTP_VERSION 0.1
#define SMTP_ERROR "N/A"

std::string 
smtp_get_220_response(const std::string& ip, int port, int verbose);

#endif
