/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef ICMP_PROTO_H
#define ICMP_PROTO_H

#include <stdio.h>
#include <stdint.h>

/*Для отправки IMCP пакета без своего IP загловка.*/
int 
send_icmp_packet(struct sockaddr_in* addr, int type,
				int code, int ident, int seq, int ttl);

/*ncread но для IMCP протокола.*/
int 
recv_icmp_packet(const char* dest_ip, int timeout_ms, int type,
				int code, int identm);
#endif
