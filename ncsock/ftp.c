/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
 * -----------------------------------------------------------
 * ftp.c - functions for working with ftp protocol.
 * -----------------------------------------------------------
*/

#include "include/ftp.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int 
ftp_session_run(const char* ip, int port, int timeout_ms, int verbose)
{
#ifdef PACKET_TRACE
    printf("FTP & CONNECT: ip=%s port=%d\n", ip, port);
#endif

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
#ifdef PRINT_ERRORS
        perror("Error creating socket");
#endif
        return -1;
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0)
    {
#ifdef PRINT_ERRORS
        perror("Invalid address");
#endif
        close(sockfd);
        return -1;
    }

    struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
    {
#ifdef PRINT_ERRORS
        perror("Error setting receive timeout");
#endif
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
#ifdef PRINT_ERRORS
        perror("Connection failed");
#endif
        close(sockfd);
        return -1;
    }

    /*mandatory package acceptance*/
    char response_buffer[FTP_CMD_BUFFER_SIZE];
    ssize_t bytes_received = recv(sockfd, response_buffer, sizeof(response_buffer) - 1, 0);

    if (bytes_received == -1)
    {
#ifdef PRINT_ERRORS
        perror("Error receiving response");
#endif
        close(sockfd);
        return -1;
    }
    if (verbose)
    {
        response_buffer[bytes_received] = '\0';
        printf("VERBOSE  %s", response_buffer);
    }

    return sockfd;
}

int
ftp_auth(const char* ip, int port, const char* login, const char* pass,
        int verbose, int timeout_ms)
{
    /*run session aka connect to ftp server*/
    int sockfd = ftp_session_run(ip, port, timeout_ms, verbose);
    if (sockfd == -1)
    {
        return -1;
    }

    /*create login command for send ftp*/
    char login_send_buf[FTP_CMD_BUFFER_SIZE];
    snprintf(login_send_buf, FTP_CMD_BUFFER_SIZE, "USER %s\r\n", login);

    /*send login*/
    int send_login = ftp_send_package(sockfd, login_send_buf, verbose, timeout_ms);

    if (send_login == FTP_REPLY_READY || send_login == FTP_REPLY_LOGGEDIN) /*ftp server no password*/
    {
        close(sockfd);
        return 0;
    }
    else if (send_login != FTP_REPLY_NEEDPASS) /*ftp server not ask password*/
    {
        close(sockfd);
        return -1;
    }
    else if (send_login == FTP_REPLY_SERVICEUNAVAIL)
    {
        close(sockfd);
        return -1;
    }

    /*create password command for send ftp*/
    char pass_send_buf[FTP_CMD_BUFFER_SIZE];
    snprintf(pass_send_buf, FTP_CMD_BUFFER_SIZE, "PASS %s\r\n", pass);

    /*send password*/
    int send_pass = ftp_send_package(sockfd, pass_send_buf, verbose, timeout_ms);
    if (send_pass != FTP_REPLY_LOGGEDIN && send_pass != FTP_REPLY_OKAY) /*failed password*/
    {
        close(sockfd);
        return -1;
    }
    else if (send_pass == FTP_REPLY_SERVICEUNAVAIL)
    {
        close(sockfd);
        return -1;
    }

    close(sockfd);
    return 0; /*successful auth*/
}

int
ftp_send_package(int sockfd, const char* message, int verbose, int timeout_ms)
{
#ifdef PACKET_TRACE
    printf("FTP & SENT: message=%s", message);
#endif

    struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

    int bytes_sent = send(sockfd, message, strlen(message), 0);
    if (bytes_sent == -1) {
#ifdef PRINT_ERRORS
        perror("Error sending message");
#endif
        return -1;
    }

    char response_buffer[FTP_CMD_BUFFER_SIZE];
    int bytes_received = recv(sockfd, response_buffer, FTP_CMD_BUFFER_SIZE - 1, 0);
    if (bytes_received == -1) {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
        {
#ifdef PRINT_ERRORS
            perror("Timeout waiting for response");
#endif
        }
        else
        {
#ifdef PRINT_ERRORS
            perror("Error receiving response");
#endif
        }
        return -1;
    }

    response_buffer[bytes_received] = '\0';
    if (verbose)
    {
        printf("VERBOSE  %s", response_buffer);
    }

    int response_code = atoi(response_buffer); 
    return response_code;
}
