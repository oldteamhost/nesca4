/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
 * -----------------------------------------------------------
 * ftp.h - It contains, constants and functions
 * for working with ftp protocol.
 * -----------------------------------------------------------
*/

#ifndef FTP_H
#define FTP_H

/* Support c++. */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* Compile opts */
#include "ncsockopt.h"

/* Response codes */
#define FTP_REPLY_OKAY            200
#define FTP_REPLY_FILESTATUS      213
#define FTP_REPLY_READY           220
#define FTP_REPLY_CLOSED          221
#define FTP_REPLY_LOGGEDIN        230
#define FTP_REPLY_SERVICEUNAVAIL  421
#define FTP_REPLY_NEEDPASS        331
#define FTP_REPLY_NEEDACCT        332
#define FTP_REPLY_PASSOKAY        230
#define FTP_REPLY_SYST            215
#define FTP_REPLY_FILEOKAY        250
#define FTP_REPLY_CREATED         257
#define FTP_REPLY_PASVMODE        227
#define FTP_REPLY_USEROKAY        331
#define FTP_REPLY_NOTFOUND        550
#define FTP_REPLY_NOPERM          550

#define FTP_CMD_BUFFER_SIZE 4096

/* Starting a session aka connecting to an ftp server
 * this function returns the socket descriptor, this
 * is to ensure that the server does not consider us a
 * new user after each submission. */
int
ftp_session_run(const char* ip, int port, int timeout_ms, int verbose);

/* Function for sending packet to ftp server, in sockfd
 * specify what was returned by ftp_session_run function,
 * in message field you can specify command, also do not
 * forget to add: \r\n.*/
int
ftp_send_package(int sockfd, const char* message, int verbose, int timeout_ms);

/* Function for authorization on ftp server, uses 2 previous
 * functions, can work in threads.*/
        #define SUCCESS_AUTH 0
        #define FAILED_AUTH -1
int
ftp_auth(const char* ip, int port, const char* login, const char* pass,
        int verbose, int timeout_ms);

#ifdef __cplusplus
}
#endif

#endif

