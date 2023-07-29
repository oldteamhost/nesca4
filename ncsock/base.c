#include "include/base.h"

const char*
get_local_ip(void)
{
    struct sockaddr_in serv;
    static char buffer[100];
    socklen_t namelen;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {return "-1";}

    const char *kGoogleDnsIp = "8.8.8.8";
    const int dns_port             = 53;

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(kGoogleDnsIp);
    serv.sin_port = htons(dns_port);

    const int err = connect(sock,(const struct sockaddr*)&serv, sizeof(serv));
    if (err < 0) {close(sock);return "-1";}

    struct sockaddr_in name;
    namelen = sizeof(name);
    memset(&name, 0, sizeof(name));
    if (getsockname(sock,(struct sockaddr*)&name, &namelen)){close(sock);return "-1";}

    const char *p = inet_ntop(AF_INET, &name.sin_addr, buffer, sizeof(buffer));
    close(sock);
    return p;
}
