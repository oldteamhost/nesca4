// Баг иногда выводиться то что не должно.
#ifndef GETFTPVERSION_H
#define GETFTPVERSION_H
#include <iostream>
#include <algorithm>
#include <regex>
#include <cstring>
#include <string>
#include "easysock.h"

#define FTP_VERSION 0.1
#define FTP_ERROR "N/A"

std::string 
get_ftp_description(std::string server, std::string port, std::string username, std::string password);

#endif
