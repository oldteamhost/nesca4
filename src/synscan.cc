#include "../include/synscan.h"
#include <arpa/inet.h>

struct in_addr dest_ip;
nesca_prints nspr;

std::mutex fuck_sock;
std::mutex fuck_sock1;

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

void
syn_scan::create_ip_header(struct iphdr *iph, const char *source_ip, struct in_addr dest_ip){
    if (debug){
        nspr.nlog_custom("SYN", "Creation IP header.\n", 1);
    }

    /*Создание ip заголовка, для пакета.*/
    int ip_header_length = sizeof(struct iphdr);
    uint8_t iph_ihl = ip_header_length / 4;
    iph->ihl = iph_ihl;
    iph->version = 4;
    iph->tot_len = sizeof(struct ip) + sizeof(struct tcphdr);
    iph->tos = 0;
    iph->frag_off = htons(16384);
    iph->id = htons(54321);
    iph->ttl = 255;
    iph->protocol = IPPROTO_TCP;
    iph->check = 0;
    iph->saddr = inet_addr(source_ip);
    iph->daddr = dest_ip.s_addr; 
}

int 
syn_scan::syn_scan_port(const char* ip, int port, int timeout_ms){
    struct sockaddr_in dest;
    struct pseudo_header psh;
    char datagram[2048];
    struct iphdr *iph = (struct iphdr*) datagram;
    struct tcphdr *tcph = (struct tcphdr*) (datagram + sizeof (struct iphdr));
    memset (datagram, 0, 2048);

    if (debug){
        nspr.nlog_custom("SYN", "IP is: "+std::string(ip)+"\n", 1);
    }
    /*Таймаут, он реально помогает и очень сильно влияет.*/
    delay_ms(timeout_ms);

    /*Создание raw сокета, для более глубокой работы
    с сокетом.*/
    int sock = create_raw_sock("tcp");
    if (debug){
        nspr.nlog_custom("SYN", "Creation RAW sock on send.\n", 1);
    }
    if (sock == -1){
        if (debug){
            nspr.nlog_custom("^", "FAILED creation RAW sock on SEND.\n", 2);
        }
        return PORT_ERROR;
    }

    dest_ip.s_addr = inet_addr(ip);    
    create_ip_header(iph, source_ip, dest_ip);

    if (debug){
        nspr.nlog_custom("SYN", "Calculate sum for IP header.\n", 1);
    }
    iph->check = csum ((unsigned short *) datagram, iph->tot_len >> 1); // контрольная сумма пакета.

    /*Создание tcp заголовка для пакета.*/
    if (debug){
        nspr.nlog_custom("SYN", "Creation TCP header.\n", 1);
    }
    tcph->dest = htons(80);
    create_tcp_header(tcph, port);

    /*Указания ядру ос, то что будет отправлен
    кастомный ip заголовок.*/
    int one = 1;
    const int *val = &one;

    if (setsockopt (sock, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0){
        return PORT_ERROR;
    }

    /*Подготовка к заполнению фекового tcp заголовка.*/
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = dest_ip.s_addr;

    if (debug){
        nspr.nlog_custom("SYN", "Creation fake TCP header.\n", 1);
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
        nspr.nlog_custom("SYN", "Calculate sum for TCP header.\n", 1);
    }

    tcph->check = csum((unsigned short*)&psh, 
		  sizeof(struct pseudo_header));

    struct timeval timeout;
    timeout.tv_sec = s_timeout;
    timeout.tv_usec = 0;

    int _result = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    if (_result < 0){
        return PORT_ERROR;
    }

    /*Отправка syn пакета.*/
    if (debug){
        nspr.nlog_custom("SYN", "Send SYN packet.\n", 1);
    }
    if (sendto(sock, datagram, sizeof(struct iphdr) + sizeof(struct tcphdr) ,
                0 , (struct sockaddr *) &dest, sizeof (dest)) < 0){
        if (debug){
            nspr.nlog_custom("^", "FAILED send SYN packet.\n", 2);
        }
        return PORT_ERROR;
    }

    int saddr_size, data_size;

    struct sockaddr saddr;
    struct sockaddr_in source, _dest;
    unsigned char *buffer = (unsigned char *)malloc(1024);
    unsigned short iphdrlen;
    
    /*Создания нового сокета для обработки ответа.*/
    if (debug){
        nspr.nlog_custom("SYN", "Creation RAW sock on RECV.\n", 1);
    }

    close(sock);

    std::lock_guard<std::mutex> lock_sock(fuck_sock);
    int sock1 = create_raw_sock("tcp");
    if (sock1 == -1){
        if (debug){
            nspr.nlog_custom("^", "FAILED creation RAW sock on RECV.\n", 2);
        }
        return PORT_ERROR;
    }

    /*Установка таймаута для сокета.*/
    int result;
    struct timeval timeout2;
    timeout2.tv_sec = r_timeout;
    timeout2.tv_usec = 0;

    result = setsockopt(sock1, SOL_SOCKET, SO_RCVTIMEO, &timeout2, sizeof(timeout2));

    if (result < 0){
        return PORT_ERROR;
    }

    /*Получение пакета в буфер.*/
    if (debug){
        nspr.nlog_custom("SYN", "Getting packet on buffer.\n", 1);
    }

    data_size = recvfrom(sock1, buffer, 1024, 0, (struct sockaddr*)&saddr, (socklen_t*)&saddr_size);
    if (data_size < 0){
        if (debug){
            nspr.nlog_custom("^", "Getting packet on buffer.\n", 2);
        }
        return PORT_ERROR;
    }

    saddr_size = sizeof saddr;
    if (iph->protocol == 6){ // Если протокол равен tcp

        /*Извлечение ответа*/
        if (debug){
            nspr.nlog_custom("SYN", "Getting answer.\n", 1);
        }
        struct iphdr *iph = (struct iphdr *)buffer;
        iphdrlen = iph->ihl*4;

        struct tcphdr *tcph=(struct tcphdr*)(buffer + iphdrlen);
        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = iph->saddr;

        memset(&_dest, 0, sizeof(_dest));
        _dest.sin_addr.s_addr = iph->daddr;

        if (debug){
            if (tcph->syn != 0){
                nspr.nlog_custom("SYN", "Flag SYN is: " + std::to_string(tcph->syn) + "\n", 0);
            }
            else {
                nspr.nlog_custom("SYN", "Flag SYN is: " + std::to_string(tcph->syn) + "\n", 2);
            }
            if (tcph->ack != 0){
                nspr.nlog_custom("SYN", "Flag ACK is: " + std::to_string(tcph->ack) + "\n", 0);
            }
            else {
                nspr.nlog_custom("SYN", "Flag ACK is: " + std::to_string(tcph->ack) + "\n", 2);
            }
            if (tcph->rst != 0){
                nspr.nlog_custom("SYN", "Flag RST is: " + std::to_string(tcph->rst) + "\n", 0);
            }
            else {
                nspr.nlog_custom("SYN", "Flag RST is: " + std::to_string(tcph->rst) + "\n", 2);
            }
        }
	   int status = get_port_status(tcph->th_flags);
	   if (status != PORT_ERROR){
		  close(sock1);
		  return status;
	   }
    }

    /*В любом другом случае считаеться что выполнение
    функции кончилось ошибкой.*/
    close(sock1);
    return PORT_ERROR;
}

int
syn_scan::get_port_status(uint8_t flags){
    /*Обработка пакета, писалась используя
    эту статью: https://nmap.org/book/synscan.html*/
    if (fin || null | xmas){
	   switch (flags) {
		  case 0x04:{
			 return PORT_CLOSED;
		  }
		  default:{
			 return PORT_OPEN;
		  }
	   }
    } 
    else {
	   switch (flags) {
		  case 0x12:{
			 /*SYN + ACK
			 * Если хост ответил флагом ack и послал syn
			 значит порт считаеться открытым.*/
			 return PORT_OPEN;
		  }
		  case 0x1A:{
			 /*SYN + ACK + PSH
			 * Если хост ответил флагом ack и psh затем  послал syn
			 значит порт считаеться открытым, и готовым для
			 передачи данных*/
			 return PORT_OPEN;
		  }
		  case 0x04:{
			 /*RST
			 * Если хост послал только флаг rst
			 aka сброс соеденения, то считаеться что порт
			 закрыт.*/
			 return PORT_CLOSED;
		  }
		  default:{
			 /*Если ответа от хоста вообще не было то считаеться
			 что подлкючение не удалось, порт фильтруеться.*/
			 return PORT_FILTER;
		  }
	   }
    }
}

void
syn_scan::set_tcp_flags(struct tcphdr* tcph, int syn, int ack, int fin, int rst, int urg, int phs){
    tcph->fin=fin;
    tcph->syn=syn;
    tcph->rst=rst;
    tcph->psh=phs;
    tcph->ack=ack;
    tcph->urg=urg;
}

/*Убран в другую для более короткой основной*/
void 
syn_scan::create_tcp_header(struct tcphdr* tcph, int port){
    std::random_device rd;
    std::uniform_int_distribution<uint32_t> dist(0, std::numeric_limits<uint32_t>::max());
    uint32_t seq = dist(rd);
    tcph->seq = htonl(seq);
    tcph->source = htons(15845);
    tcph->dest = htons(port);
    tcph->ack_seq = 0;
    tcph->doff = sizeof(struct tcphdr) / 4;
    if (fin){
	   set_tcp_flags(tcph, 0, 0, 1, 0, 0, 0);
    }
    else if (null){
	   set_tcp_flags(tcph, 0, 0, 0, 0, 0, 0);
    }
    else if (xmas){
	   set_tcp_flags(tcph, 0, 0, 1, 0, 1, 1);
    }
    else {
	   set_tcp_flags(tcph, 1, 0, 0, 0, 0, 0);
    }
    tcph->check = 0;

    int window_size_bytes = 14600;
    uint16_t window_size_words = window_size_bytes / 2;
    tcph->window = htons(window_size_words);

    tcph->urg_ptr = 0;
}
