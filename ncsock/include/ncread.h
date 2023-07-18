/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

/*Конечно не nsock_read в nmap, но тоже неплохо.
 * Функция по принятию и сортировки пакетов.
 * Вообще любые которые приходят на систему.
*/

#ifndef NCREAD_H
#define NCREAD_H
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <chrono>
#include <netinet/ip.h>
#include <poll.h>
#include <netinet/tcp.h>
#include <unistd.h>

/*Если убрать этот макрос, то функция не будет привязана к другим классам.*/
#define NESCA

#define SUCCESS_READ			 0
#define READ_BUFFER_SIZE		 2048

#define SOCKET_ERROR			 -1
#define BUFFER_CALLOC_ERROR		 -2
#define POLL_ERROR				 -3
#define POLL_TIMEOUT_EXITED		 -4
#define READ_ERROR				 -5
#define INFINITY_TIMEOUT_EXITED	 -6
#define IP_HEADER_LEN_ERROR		 -7

#ifdef NESCA
	int
	ncread(const char* dest_ip, int recv_timeout_ms, unsigned char **buffer, bool debug,
		  int dest_port = 0, int source_port = 0, bool packet_trace = false);
#else
	int
	ncread(const char* dest_ip, int recv_timeout_ms, unsigned char **buffer, bool debug);
#endif

ssize_t 
ncread_recv(int sockfd, void* buf, size_t len, int timeout_ms);

#endif
