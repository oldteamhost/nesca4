/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#ifndef NESCADDOS_HEADER
#define NESCADDOS_HEADER

#include "../ncsock/include/icmp.h"
#include "../ncsock/include/tcp.h"
#include "../ncsock/include/udp.h"
#include "../ncsock/include/ip.h"
#include "../include/nescalog.h"
#include "../config/nescaopts.h"
#include "nescadata.h"

void read_ddos(nesca_prints &np, struct readfiler *rf, int recvtime, bool hidden_eth);
void send_ddos(struct datastring *ds, nesca_prints &np, NESCADATA &nd, arguments_program &argp, u8 proto, u8 type,
    const u32 daddr, const u32 saddr, const int port, bool ip_ddos);

#endif

