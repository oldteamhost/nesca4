/*Конечно не nsock_read в nmap, но тоже неплохо.
 * Главное стабильно.*/

#ifndef NCREAD_H
#define NCREAD_H
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <chrono>
#include <netinet/ip.h>
#include <poll.h>
#include <unistd.h>

#define SUCCESS_READ			 0
#define READ_BUFFER_SIZE			 4096

#define SOCKET_ERROR			 -1
#define BUFFER_CALLOC_ERROR		 -2
#define POLL_ERROR				 -3
#define POLL_TIMEOUT_EXITED		 -4
#define READ_ERROR				 -5
#define INFINITY_TIMEOUT_EXITED	 -6
#define IP_HEADER_LEN_ERROR		 -7

/*Функция по принятию и сортировки пакетов.
 * Вообще любые которые приходят на систему.*/
int
ncread(const char* dest_ip, int recv_timeout_ms, unsigned char **buffer, bool debug);

#endif
