/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "include/socket.h"

#define ERROR  -1
#define SUCCESS 0

int 
set_socket_timeout(int sock, int timeout_ms, int on_send, int on_recv)
{
    struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

    if (on_send)
	{
	   if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) == -1)
	   {
		  fprintf(stderr, "Failed to set receive timeout: %s\n", strerror(errno));
		  return ERROR;
	   }
    }
    if (on_recv)
	{
	   if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout)) == -1)
	   {
		  fprintf(stderr, "Failed to set send timeout: %s\n", strerror(errno));
		  return ERROR;
	   }
    }

    return SUCCESS;
}

int 
set_socket_reuseaddr(int sock)
{
    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse)) < 0)
	{
        fprintf(stderr, "Failed to set socket reuse address: %s\n", strerror(errno));
        return ERROR;
    }
    return SUCCESS;
}

int 
set_socket_nonblocking(int sock)
{
    int flags = fcntl(sock, F_GETFL, 0);
    if (flags < 0)
	{
        fprintf(stderr, "Failed to get socket flags: %s\n", strerror(errno));
        return ERROR;
    }
    if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0)
	{
        fprintf(stderr, "Failed to set socket non-blocking: %s\n", strerror(errno));
        return ERROR;
    }
    return SUCCESS;
}

int 
set_socket_receive_buffer_size(int sock, int buffer_size)
{
    if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (const char *)&buffer_size, sizeof(buffer_size)) < 0)
	{
        fprintf(stderr, "Failed to set socket receive buffer size: %s\n", strerror(errno));
        return ERROR;
    }
    return SUCCESS;
}

int
set_socket_timeout_pro(int sock, int timeout_ms)
{
    struct pollfd poll_fds[1];
    poll_fds[0].fd = sock;
    poll_fds[0].events = POLLIN;
    int poll_result = poll(poll_fds, 1, timeout_ms);
    if (poll_result == -1)
	{
	   close(sock);
	   return -1;
    }else if (poll_result == 0)
	{
	   close(sock);
	   return -1;
    }
	return 0;
}
