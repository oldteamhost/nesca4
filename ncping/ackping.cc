#include "include/ackping.h"
std::mutex fuck_ack;

double
tcp_ack_ping(const char* ip, const char* source_ip, int timeout_ms){
	/*Отпкавка пакета с флагом ACK.*/
	double response_time = -1;
	int source_port = generate_port();
	nesca_scan_opts ncops;
	ncops.debug = false;
	ncops.source_ip = source_ip;
	ncops.scan_type = 5;
	ncops.seq = generate_seq();
	ncops.source_port = source_port;
	nesca_scan(&ncops, ip, DEFAULT_SEND_PORT, 0);

	/*Буфер для приёма ответа.*/
	fuck_ack.lock();
	unsigned char *buffer = (unsigned char *)calloc(READ_BUFFER_SIZE, sizeof(unsigned char));
	fuck_ack.unlock();

	/*Ожидание пакета, и запуск таймера на время ответа.*/
	struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
	int read = ncread(ip, timeout_ms, &buffer, 0);
	/*Не дождалась пакета.*/
	if (read != SUCCESS_READ){
		fuck_ack.lock();
		free(buffer);
		fuck_ack.unlock();
		return -1;
	}
	struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);

	/*Ответ получен, теперь проверяем его.*/
    struct iphdr *iph = (struct iphdr*)buffer;
    unsigned short iphdrlen = (iph->ihl) * 4;
    if (iph->protocol != 6){return PORT_ERROR;}
    struct tcphdr *tcph = (struct tcphdr*)((char*)buffer + iphdrlen);

	/*Если ответило флагом RST значит спалился.*/
	if (tcph->th_flags == 0x04){
		response_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0; 
    	response_time += (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
	}

	fuck_ack.lock();
	free(buffer);
	fuck_ack.unlock();
	return response_time;
}
