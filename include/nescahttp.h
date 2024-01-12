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
#include "../ncsock/include/socket.h"
#include "../ncsock/include/ftp.h"
#include "../ncsock/include/http.h"
#include <mutex>

void prepare_redirect(const char* redirect, char* reshost, char* respath, ssize_t buflen);
void send_http(struct http_request *r, NESCADATA &nd, const std::string& ip,
    const u16 port, const int timeout_ms);

#endif

