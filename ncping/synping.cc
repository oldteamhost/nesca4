/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/synping.h"

std::mutex fuck_syn;

double
tcp_syn_ping(const char* ip, const char* source_ip, int dest_port, int source_port, int timeout_ms, int ttl){
	/*Отпкавка пакета с флагом SYN.*/
	double response_time = -1;
	nesca_scan_opts ncops;
	ncops.source_ip = source_ip;
	ncops.seq = generate_seq();
	ncops.ttl = ttl;
	ncops.source_port = source_port;
	ncops.tcpf = set_flags(SYN_SCAN);

	/*Отправка.*/
	int send = nesca_scan(&ncops, ip, dest_port, 0);
	if (send == EOF){return -1;}

	/*Буфер для приёма ответа.*/
	fuck_syn.lock();
	unsigned char *buffer = (unsigned char *)calloc(READ_BUFFER_SIZE, sizeof(unsigned char));
	fuck_syn.unlock();

	/*Ожидание пакета, и запуск таймера на время ответа.*/
	std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

	int read = ncread(ip, timeout_ms, &buffer, 0, dest_port, source_port);
	/*Не дождалась пакета.*/
	if (read != SUCCESS_READ){
		fuck_syn.lock();
		free(buffer);
		fuck_syn.unlock();
		return -1;
	}
	std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

	/*Ответ получен, теперь проверяем его.*/
    struct ip_header *iph = (struct ip_header*)buffer;
    unsigned short iphdrlen = (iph->ihl) * 4;
    if (iph->protocol != 6) {return PORT_ERROR;}
    struct tcp_header *tcph = (struct tcp_header*)((char*)buffer + iphdrlen);

	/*Если ответило флагом RST значит спалился.*/
	if (tcph->th_flags != 0){
		std::chrono::duration<double, std::milli> elapsed_ms = end_time - start_time;
		response_time = elapsed_ms.count();
	}

	fuck_syn.lock();
	free(buffer);
	fuck_syn.unlock();
	return response_time;
}
