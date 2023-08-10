/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#ifndef SYN_SCAN_H
#define SYN_SCAN_H
#include <iostream>
#include <cstdint>
#include <cstring>
#include <arpa/inet.h>
#include <string>
#include <random>
#include <netdb.h>
#include <cerrno>
#include <unistd.h>
#include <thread>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <mutex>
#include <vector>

#include "../include/nescalog.h"
#include "../ncsock/include/ip4.h"
#include "../ncsock/include/tcp.h"
#include "../ncsock/include/socket.h"
#include "../include/other.h"
#include "services.h"
#include "services.h"
#include <cstdint>
#include <ctime>
#include <string>

#define PORT_OPEN             0
#define PORT_CLOSED           1
#define PORT_FILTER           2
#define PORT_ERROR           -1
#define PORT_OPEN_OR_FILTER   3
#define PORT_NO_FILTER        4

#define SYN_SCAN              1
#define XMAS_SCAN             2
#define FIN_SCAN              3
#define NULL_SCAN             4
#define ACK_SCAN              5
#define WINDOW_SCAN           6
#define MAIMON_SCAN           7

std::string
get_type(uint8_t type);

int /*Определение статуса порта.*/
get_port_status(unsigned char* buffer, uint8_t scan_type);

#include "../config/compile.h"

#ifdef HAVE_CURL
#include <curl/curl.h>
class nesca3_scan
{
public:
	int timeout_ms = 600;
	int http_probe(const std::string& node, int port);
	int ftp_probe(const std::string& node, int port);
	int smtp_probe(const std::string& node, int port);
	int ssh_probe(const std::string& node, int port);
	int rtsp_probe(const std::string& node, int port);
	int https_probe(const std::string& node, int port);
};
#endif

#endif
