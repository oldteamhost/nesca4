/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
*/

#ifndef NCSOCK_SOCKET_H
#define NCSOCK_SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

/* Compile opts */
#include "ncsockopt.h"

/* Starting a session aka connecting to an server
 * this function returns the socket descriptor, this
 * is to ensure that the server does not consider us a
 * new user after each submission. */
        #define CMD_BUFFER 4096
int session_run(const char* dest_ip, int port, int timeout_ms, int verbose);
void session_run_buf(const char* dest_ip, int port, int timeout_ms, char* buffer, size_t buffer_size);

/* Function for sending packet to server, in sockfd
 * specify what was returned by session_run function,
 * in message field you can specify command, also do not
 * forget to add: \r\n.*/
        #define SUCCESS_AUTH 0
        #define FAILED_AUTH -1
int
session_packet(int sockfd, char* response_buffer, const char* message,
    int verbose, int timeout_ms);

int /* Set flag timeout on socket, in ms. */
set_socket_timeout(int sock, int timeout_ms, int on_send, int on_recv);

int /* Set pool timeout. */
set_socket_timeout_pro(int sock, int timeout_ms);

int /* Set flag address reuse on socket. */
set_socket_reuseaddr(int sock);

int /* Set non_block flag on socket. */
set_socket_nonblocking(int sock);

int /* Set send buffer size, on socket. */
set_socket_send_buffer_size(int sock, int buffer_size);

int /* Set recv buffer size, on socket. */
set_socket_receive_buffer_size(int sock, int buffer_size);

int /* Send kernel custom ip header. */
set_socket_hdrincl(int sock);

#ifdef __cplusplus
}
#endif

#endif
