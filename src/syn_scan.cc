#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <random>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <cerrno>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <cstdint>
#include <cstring>

#include "../include/syn_scan.h"
#include "../include/net_utils.h"
#include "../include/prints.h"
#include "../include/other.h"

struct in_addr dest_ip;
ip_utils iu;
nesca_prints nspr;

unsigned short 
csum(unsigned short *ptr,int nbytes){
    long sum;
    unsigned short oddbyte;
    short answer;

    sum=0;
    while(nbytes>1) {
        sum+=*ptr++;
        nbytes-=2;
    }

    if(nbytes==1) {
        oddbyte=0;
        *((u_char*)&oddbyte)=*(u_char*)ptr;
        sum+=oddbyte;
    }
    sum = (sum>>16)+(sum & 0xffff);
    sum += (sum>>16);
    answer=(short)~sum;

    return(answer);
}

int 
syn_scan::syn_scan_port(const char* ip, int port, int timeout_ms){
    /*Таймаут, он реально помогает и очень сильно влияет.*/
    delay_ms(timeout_ms);

    /*Создание raw сокета, для более глубокой работы
    с сокетом.*/
    int sock = main_utils::create_raw_socket("tcp");
    if (debug){
        std::cout << nspr.main_nesca_out("SYN", "Creation RAW sock.", 2, "", "", "", "") << std::endl;
    }
    if (sock == -1){
        if (debug){
            std::cout << nspr.main_nesca_out("^", "FAILED Creation RAW sock.", 1, "", "", "", "") << std::endl;
        }
        return PORT_ERROR;
    }

    char datagram[4096];

    struct iphdr *iph = (struct iphdr *) datagram;
    struct tcphdr *tcph = (struct tcphdr *) (datagram + sizeof (struct ip));

    struct sockaddr_in dest;
    struct pseudo_header psh;

    dest_ip.s_addr = inet_addr(ip);    
    memset (datagram, 0, 4096);

    if (debug){
        std::cout << nspr.main_nesca_out("SYN", "Creation IP header.", 2, "", "", "", "") << std::endl;
    }
    /*Создание ip заголовка, для пакета.*/
    int ip_header_length = sizeof(struct iphdr);
    uint8_t iph_ihl = ip_header_length / 4;
    iph->ihl = iph_ihl;
    iph->version = 4;
    iph->tot_len = sizeof (struct ip) + sizeof (struct tcphdr);
    iph->tos = 0;
    iph->frag_off = htons(16384);
    iph->id = htons (54321);
    iph->ttl = 255;
    iph->protocol = IPPROTO_TCP;
    iph->check = 0; // На всякий
    iph->saddr = inet_addr(source_ip); // ip отправителя.
    iph->daddr = dest_ip.s_addr; // ip получателя.

    if (debug){
        std::cout << nspr.main_nesca_out("SYN", "Calculate sum for IP header.", 2, "", "", "", "") << std::endl;
    }
    iph->check = csum ((unsigned short *) datagram, iph->tot_len >> 1); // контрольная сумма пакета.

    /*Создание tcp заголовка для пакета.*/
    if (debug){
        std::cout << nspr.main_nesca_out("SYN", "Creation TCP header.", 2, "", "", "", "") << std::endl;
    }
    tcph->dest = htons(80);
    create_tcp_header(tcph, port);

    /*Указания ядру ос, то что будет отправлен
    кастомный ip заголовок.*/
    int one = 1;
    const int *val = &one;

#ifdef _WIN32
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (const char*)val, sizeof(one)) < 0){
        return PORT_ERROR;
    }
#else
    if (setsockopt (sock, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0){
        return PORT_ERROR;
    }
#endif

    /*Подготовка к заполнению фекового tcp заголовка.*/
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = dest_ip.s_addr;

    if (debug){
    std::cout << nspr.main_nesca_out("SYN", "Creation TCP fake header.", 2, "", "", "", "") << std::endl;
    }
    /*Заполнение псевдо tcp заголовка, для обмана
    хоста, и установки псевдо подключения.*/
    psh.source_address = inet_addr(source_ip);
    psh.dest_address = dest.sin_addr.s_addr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_TCP;
    psh.tcp_length = htons( sizeof(struct tcphdr) );
    memcpy(&psh.tcp , tcph , sizeof (struct tcphdr));

    /*Заполнение контрольной суммы пакета для
    tcp заголовка*/
    if (debug){
        std::cout << nspr.main_nesca_out("SYN", "Calculate sum for TCP header.", 2, "", "", "", "") << std::endl;
    }

    tcph->check = csum( (unsigned short*) &psh , sizeof (struct pseudo_header));
    struct timeval timeout;
    timeout.tv_sec = s_timeout;
    timeout.tv_usec = 0;
#ifdef _WIN32
    int _result = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
#else
    int _result = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
#endif
    if (_result < 0){
        return PORT_ERROR;
    }

    /*Отправка syn пакета.*/
    if (debug){
        std::cout << nspr.main_nesca_out("SYN", "Send SYN packet.", 2, "", "", "", "") << std::endl;
    }
    if (sendto (sock, datagram , sizeof(struct iphdr) + sizeof(struct tcphdr) ,
                0 , (struct sockaddr *) &dest, sizeof (dest)) < 0){
        if (debug){
            std::cout << nspr.main_nesca_out("^", "FAILED Send SYN packet.", 1, "", "", "", "") << std::endl;
        }
        return PORT_ERROR;
    }

    int saddr_size, data_size;

    struct sockaddr saddr;
    struct sockaddr_in source, _dest;
    unsigned char *buffer = (unsigned char *)malloc(65536);
    unsigned short iphdrlen;
    
    /*Создания нового сокета для обработки ответа.*/
    if (debug){
        std::cout << nspr.main_nesca_out("SYN", "Create RAW sock for processing answer.", 2, "", "", "", "") << std::endl;
    }

    int sock1 = main_utils::create_raw_socket("tcp");
    if (sock1 == -1){
        return PORT_ERROR;
    }

    /*Установка таймаута для сокета.*/
    int result;
    struct timeval timeout2;
    timeout2.tv_sec = r_timeout;
    timeout2.tv_usec = 0;
#ifdef _WIN32
    result = setsockopt(sock1, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
#else
    result = setsockopt(sock1, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
#endif
    if (result < 0){
        return PORT_ERROR;
    }

    /*Получение пакета в буфер.*/
    if (debug){
        std::cout << nspr.main_nesca_out("SYN", "Getting packet on buffer.", 2, "", "", "", "") << std::endl;
    }
#ifdef _WIN32
    data_size = recvfrom(sock1, buffer, 65536, 0, (struct sockaddr*)&saddr, &saddr_size);
#else
    data_size = recvfrom(sock1, buffer, 65536, 0, (struct sockaddr*)&saddr, (socklen_t*)&saddr_size);
#endif
    if (data_size < 0){
        if (debug){
            std::cout << nspr.main_nesca_out("^", "FAILED Getting packet on buffer.", 1, "", "", "", "") << std::endl;
        }
        return PORT_ERROR;
    }

    saddr_size = sizeof saddr;
    if (iph->protocol == 6){ // Если протокол равен tcp

        /*Извлечение ответа*/
        if (debug){
            std::cout << nspr.main_nesca_out("SYN", "Getting answer.", 2, "", "", "", "") << std::endl;
        }
        struct iphdr *iph = (struct iphdr *)buffer;
        iphdrlen = iph->ihl*4;

        struct tcphdr *tcph=(struct tcphdr*)(buffer + iphdrlen);
        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = iph->saddr;

        memset(&dest, 0, sizeof(dest));
        dest.sin_addr.s_addr = iph->daddr;

        if (debug){
            if (tcph->syn != 0){
                std::cout << nspr.main_nesca_out("SYN", "Flag SYN is: "+std::to_string(tcph->syn), 0, "", "", "", "") << std::endl;
            }
            else {
                std::cout << nspr.main_nesca_out("SYN", "Flag SYN is: "+std::to_string(tcph->syn), 1, "", "", "", "") << std::endl;
            }
            if (tcph->ack != 0){
                std::cout << nspr.main_nesca_out("SYN", "Flag ACK is: "+std::to_string(tcph->ack), 0, "", "", "", "") << std::endl;
            }
            else {
                std::cout << nspr.main_nesca_out("SYN", "Flag ACK is: "+std::to_string(tcph->ack), 1, "", "", "", "") << std::endl;

            }
            if (tcph->rst != 0){
                std::cout << nspr.main_nesca_out("SYN", "Flag RST is: "+std::to_string(tcph->rst), 0, "", "", "", "") << std::endl;
            }
            else {
                std::cout << nspr.main_nesca_out("SYN", "Flag RST is: "+std::to_string(tcph->rst), 1, "", "", "", "") << std::endl;
            }
        }

        /*Обработка пакета, писалась используя
        эту статью: https://nmap.org/book/synscan.html*/
        if (tcph->th_flags == 0x12){ // syn + ack
            main_utils::close_socket(sock);
            main_utils::close_socket(sock1);
            /*Если хост ответил флагом ack и послал syn
            значит порт считаеться открытым.*/
            return PORT_OPEN;
        }
        else if (tcph->th_flags == 0x12 && tcph->th_flags == 0x08){ // syn + ack + psh
            main_utils::close_socket(sock);
            main_utils::close_socket(sock1);
            /*Если хост ответил флагом ack и psh затем  послал syn
            значит порт считаеться открытым, и готовым для
            передачи данных*/
            return PORT_OPEN;
        }
        else if (tcph->th_flags == 0x04){ // rst
            main_utils::close_socket(sock);
            main_utils::close_socket(sock1);
            /*Если хост послал только флаг rst
            aka сброс соеденения, то считаеться что порт
            закрыт.*/
            return PORT_CLOSED;
        }
        else{
            main_utils::close_socket(sock);
            main_utils::close_socket(sock1);
            /*Если ответа от хоста вообще не было то считаеться
            что подлкючение не удалось, порт фильтруеться.*/
            return PORT_FILTER;
       }
       //
    }

    main_utils::close_socket(sock);
    main_utils::close_socket(sock1);
    /*В любом другом случае считаеться что выполнение
    функции кончилось ошибкой.*/
    return PORT_ERROR;
}

void 
syn_scan::create_tcp_header(struct tcphdr* tcph, int port){
    std::random_device rd;
    std::uniform_int_distribution<uint32_t> dist(0, std::numeric_limits<uint32_t>::max());
    uint32_t seq = dist(rd);
    tcph->seq = htonl(seq);
    tcph->source = htons(15845);
    tcph->dest = htons (port);
    tcph->ack_seq = 0;
    tcph->doff = sizeof(struct tcphdr) / 4;
    tcph->fin=0;
    tcph->syn=1;
    tcph->rst=0;
    tcph->psh=0;
    tcph->ack=0;
    tcph->urg=0;
    tcph->check = 0;

    int window_size_bytes = 14600;
    uint16_t window_size_words = window_size_bytes / 2;
    tcph->window = htons(window_size_words);

    tcph->urg_ptr = 0;
}


