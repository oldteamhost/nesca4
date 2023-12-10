/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#ifndef NESCAPING_HEADER
#define NESCAPING_HEADER

#include "../config/nescaopts.h"
#include "nescadata.h"

void send_ping(struct datastring *pd, NESCADATA &nd, arguments_program &argp, const std::string& ip);

#endif
