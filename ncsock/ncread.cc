/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/ncread.h"

#ifdef NESCA
	#include <mutex>
	#include "../include/nescalog.h"

	std::mutex packet_trace1;
	nesca_prints np3;
	int
	ncread(const char* dest_ip, int recv_timeout_ms, unsigned char **buffer, bool debug,
		  int dest_port, int source_port, bool packet_trace){
#else
	int
	ncread(const char* dest_ip, int recv_timeout_ms, unsigned char **buffer, bool debug){
#endif

    /*Создания структуры и передача в неё айпи получателя.*/
    struct in_addr dest; dest.s_addr = inet_addr(dest_ip);

    /*Временный буфер.*/
    unsigned char *read_buffer = *buffer;

     /*Создание сокета.*/
    int sock = fd(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock == -1) {return SOCKET_ERROR;}

    /*Устанока таймаута на recvfrom.*/
    struct pollfd poll_fds[1];
    poll_fds[0].fd = sock;
    poll_fds[0].events = POLLIN;
    int poll_result = poll(poll_fds, 1, recv_timeout_ms);
    if (poll_result == -1) {
	   /*Poll не смогла чё-то сделать.*/
	   fuck_fd(sock);
	   return POLL_ERROR;
    }else if (poll_result == 0) {
	   /*Вышел таймаут на recvfrom.*/
	   fuck_fd(sock);
	   return POLL_TIMEOUT_EXITED;
    }

#ifdef NESCA
	/*Ещё один таймаут, иногда poll не работает просто.*/
	int result = set_socket_timeout(sock, recv_timeout_ms, 1, 1);

#else
	struct timeval timeout;
	timeout.tv_sec = recv_timeout_ms / 1000;
	timeout.tv_usec = (recv_timeout_ms % 1000) * 1000;
	int result = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
#endif

	if (result < 0) {
	   /*Вышел таймаут.*/
	    fuck_fd(sock);
    	return -1;
	}

    /*Для сравнения айпи.*/
    struct sockaddr saddr;
    int saddr_size = sizeof(saddr);
    auto start_time = std::chrono::steady_clock::now();

    /*Бесконечный цикл, по принятию вообще любых пакетов с системы.*/
    for (;;){
	   /*Принимаем пакет в буфер.*/
	   int data_size = recvfrom(sock, read_buffer, READ_BUFFER_SIZE, 0, &saddr, (socklen_t *)&saddr_size);
	   if (data_size == -1){
	      fuck_fd(sock);
		  return READ_ERROR;
	   }

	   /*Получения IP заголовка полученного пакета.*/
	   struct ip_header *iph = (struct ip_header*)read_buffer;
	   unsigned short iphdrlen = (iph->ihl) * 4;
	   if (iphdrlen < 20){
	      fuck_fd(sock);
		  return IP_HEADER_LEN_ERROR;
	   }

	   /*Поулучение из него IP отправителя.*/
	   struct sockaddr_in source;
	   memset(&source, 0, sizeof(source));
	   source.sin_addr.s_addr = iph->saddr;

	   /*Сравнение айпи сходиться ли он с тем на который мы отпаравляли.
	    * Это нужно для отброса других пакетов.*/
	   if (source.sin_addr.s_addr != dest.s_addr){
		  if (debug) {std::cout << "Got the wrong package.\n";}

		  /*Тут может сработать таймаут на бесокнечный цикл.*/
		  auto current_time = std::chrono::steady_clock::now();
		  auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
		  if (elapsed_time >= recv_timeout_ms) {
	      	 fuck_fd(sock);
			 return INFINITY_TIMEOUT_EXITED;
		  }

		  /*Если не тот то снова ловит, пока не выйдет таймаут,
		   * на бесокнечный цикл. Или пока не придёт тот пакет.*/
		  continue;
	   }
	   else {

#ifdef NESCA
		  if (packet_trace){
		  	struct in_addr addr;
		  	addr.s_addr = iph->saddr;
		  	std::string source_ip = inet_ntoa(addr);
		  	addr.s_addr = iph->daddr;
		  	std::string dest_ip = inet_ntoa(addr);

		  	struct tcp_header *tcph = (struct tcp_header*)(buffer+ iphdrlen);
		  	unsigned short id = ntohs(iph->id);
		  	unsigned int seq = ntohl(tcph->seq);
		  	unsigned int iplen = ntohs(iph->tot_len);
			packet_trace1.lock();
		  	np3.nlog_packet_trace("RCVD", "TCP", source_ip, dest_ip, dest_port, source_port, "", iph->ttl, id, tcph->window, seq, iplen);
			packet_trace1.unlock();
		  }
#endif
		  /*Если пришёл правильный пакет.
		   * Заполняем буфер им.*/
		  *buffer = read_buffer;
		  fuck_fd(sock);
		  return SUCCESS_READ;
	   }
    }
    /*Ну ок :)*/
    fuck_fd(sock);
    return READ_ERROR;
}

int
ncread_recv(int sockfd, void* buf, size_t len, int timeout_ms){
	struct pollfd fds[1];
    fds[0].fd = sockfd;
    fds[0].events = POLLIN;

    int ready = poll(fds, 1, timeout_ms);
    if (ready == -1) {
        return POLL_ERROR;
    } else if (ready == 0) {
        return POLL_TIMEOUT_EXITED;
    } else {
        int bytes_received = recv(sockfd, buf, len, 0);
        if (bytes_received == -1) {
            return READ_ERROR;
        } else {
            return bytes_received;
        }
    }
}
