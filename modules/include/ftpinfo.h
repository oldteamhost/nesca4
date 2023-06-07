// Баг иногда выводиться то что не должно.
#ifndef FTPINFO_H 
#define FTPINFO_H 
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

#define FTP_ERROR "N/A"

std::string 
get_ftp_description(std::string server, std::string port, std::string username, std::string password);

#endif
