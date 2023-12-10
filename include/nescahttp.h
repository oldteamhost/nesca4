/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#ifndef NESCAHTTP_HEADER
#define NESCAHTTP_HEADER

#include "../include/nescabrute.h"
#include "../include/nescautils.h"
#include "../include/nescadata.h"
#include "../ncsock/include/bruteforce.h"
#include "../ncsock/include/socket.h"
#include "../ncsock/include/ftp.h"
#include "../ncsock/include/base.h"
#include "../ncsock/include/http.h"
#include "../ncsock/include/strbase.h"
#include <mutex>

struct http_header initheader(const std::string& path, const std::string &host,
    const std::string &useragent, const std::string &method);

char* updsend_http(struct http_header *hh, const std::string& ip,
    const u16 port, const int timeout_ms);

void send_http(struct http_header *hh, NESCADATA &nd, const std::string& ip,
    const u16 port, const int timeout_ms);

#endif

