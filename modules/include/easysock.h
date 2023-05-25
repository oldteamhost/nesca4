#ifndef EASYSOCK_H
#define EASYSOCK_H
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

#define ERROR -1

int create_sock(std::string protocol);
int create_raw_sock(std::string protocol);
void close_sock(int sock);
#endif
