/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "../include/ncread.h"
#include <cstdlib>
#include <unistd.h>

int
ncread(const char* dest_ip, int recv_timeout_ms, unsigned char **buffer, bool debug){
    /*Создания структуры и передача в неё айпи получателя.*/
    struct in_addr dest; dest.s_addr = inet_addr(dest_ip);

    /*Временный буфер.*/
    unsigned char *read_buffer = *buffer;

     /*Создание сокета.*/
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock == -1){return SOCKET_ERROR;}

    /*Устанока таймаута на recvfrom.*/
    struct pollfd poll_fds[1];
    poll_fds[0].fd = sock;
    poll_fds[0].events = POLLIN;
    int poll_result = poll(poll_fds, 1, recv_timeout_ms);
    if (poll_result == -1) {
	   /*Poll не смогла чё-то сделать.*/
	   close(sock);
	   return POLL_ERROR;
    }else if (poll_result == 0) {
	   /*Вышел таймаут на recvfrom.*/
	   close(sock);
	   return POLL_TIMEOUT_EXITED;
    }

    /*Для сравнения айпи.*/
    struct sockaddr saddr;
    int saddr_size = sizeof(saddr);
    auto start_time = std::chrono::steady_clock::now();

    /*Бесконечный цикл, по принятию вообще любых пакетов с системы.*/
    for (;;){
	   /*Принимаем пакет в буфер.*/
	   ssize_t data_size = recvfrom(sock, read_buffer, READ_BUFFER_SIZE, 0, &saddr, (socklen_t *)&saddr_size);
	   if (data_size == -1){
		  close(sock);
		  return READ_ERROR;
	   }

	   /*Получения IP заголовка полученного пакета.*/
	   struct iphdr *iph = (struct iphdr*)read_buffer;
	   unsigned short iphdrlen = (iph->ihl) * 4;
	   if (iphdrlen < 20){
		  close(sock);
		  return IP_HEADER_LEN_ERROR;
	   }

	   /*Поулучение из него IP отправителя.*/
	   struct sockaddr_in source;
	   memset(&source, 0, sizeof(source));
	   source.sin_addr.s_addr = iph->saddr;

	   /*Сравнение айпи сходиться ли он с тем на который мы отпаравляли.
	    * Это нужно для отброса других пакетов.*/
	   if (source.sin_addr.s_addr != dest.s_addr){
		  if (debug){std::cout << "Got the wrong package.\n";}

		  /*Тут может сработать таймаут на бесокнечный цикл.*/
		  auto current_time = std::chrono::steady_clock::now();
		  auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
		  if (elapsed_time >= recv_timeout_ms) {
			 close(sock);
			 return INFINITY_TIMEOUT_EXITED;
		  }

		  /*Если не тот то снова ловит, пока не выйдет таймаут,
		   * на бесокнечный цикл. Или пока не придёт тот пакет.*/
		  continue;
	   }
	   else {
		  /*Если пришёл правильный пакет.
		   * Заполняем буфер им.*/
		  *buffer = read_buffer;
		  close(sock);
		  return SUCCESS_READ;
	   }
    }
    /*Ну ок :)*/
    close(sock);
    return READ_ERROR;
}

