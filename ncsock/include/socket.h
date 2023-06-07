#ifndef NCSOCK_SOCKET_H
#define NCSOCK_SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#define ERROR -1
#define SUCCESS 0

/*Set flag timeout on socket, in ms.*/
int 
set_socket_timeout(int sock, int timeout_ms, int on_send, int on_recv);

/*Set flag address reuse on socket.*/
int 
set_socket_reuseaddr(int sock);

/*Set non_block flag on socket.*/
int 
set_socket_nonblocking(int sock);

/*Set send buffer size, on socket.*/
int 
set_socket_send_buffer_size(int sock, int buffer_size);

/*Set recv buffer size, on socket.*/
int 
set_socket_receive_buffer_size(int sock, int buffer_size);

/*Send kernel custom ip header*/
int 
set_socket_hdrincl(int sock);

#ifdef __cplusplus
}
#endif

#endif
