/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef NCSOCK_SOCKET_H
#define NCSOCK_SOCKET_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

int fd(int domain, int type, int protocol);
int fuck_fd(int fd);

/*
int init_winsock(void);
int clean_winsock(void);
*/

int /*Set flag timeout on socket, in ms.*/
set_socket_timeout(int sock, int timeout_ms, int on_send, int on_recv);

int /*Set flag address reuse on socket.*/
set_socket_reuseaddr(int sock);

int /*Set non_block flag on socket.*/
set_socket_nonblocking(int sock);

int /*Set send buffer size, on socket.*/
set_socket_send_buffer_size(int sock, int buffer_size);

int /*Set recv buffer size, on socket.*/
set_socket_receive_buffer_size(int sock, int buffer_size);

int /*Send kernel custom ip header*/
set_socket_hdrincl(int sock);

#ifdef __cplusplus
}
#endif

#endif
