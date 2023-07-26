/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/nesca4.h"
#include "include/other.h"
#include "include/portscan.h"
#include <string>

struct nesca_scan_opts ncopts;
const char* short_options = "hl:vd:T:p:aS:";
const char* run; /*Для help_menu()*/
std::mutex ls;
checking_finds cfs;
nesca_prints np;
brute_ftp_data bfd_;
html_output ho;
ip_utils _iu;
dns_utils dus;
services_nesca sn;
nesca_negatives nn;
arguments_program argp;

int main(int argc, char** argv)
{
    run = argv[0];
    if (argc <= 1) {help_menu();return 1;}

	argp.source_ip = _iu.get_local_ip();
    parse_args(argc, argv);
    pre_check();
    checking_default_files();

	/*Установка методов пинга.*/
	if (!argp.custom_ping)
	{
		if (argp.max_ping || argp.speed_type == 1)
		{
			argp.syn_ping = true;
			argp.ack_ping = true;
			argp.echo_ping = true;
			argp.info_ping = true;
			argp.timestamp_ping = true;
		}
		if (argp.speed_type == 5){argp.ack_ping = true;}
		else if (argp.speed_type == 4){argp.echo_ping = true;argp.ack_ping = true;}
		else if (argp.speed_type == 2 || argp.speed_type == 3)
		{
			argp.ack_ping = true;
			argp.syn_ping = true;
			argp.echo_ping = true;
		}
	}

	/*Начало DNS сканирования.*/
	if (argp.dns_scan) 
	{
    	std::mutex mtx;
    	argp.timeout_ms = 100;
    	std::cout << np.main_nesca_out("NESCA4", "Starting " + std::to_string(argp._threads_dns) + " threads...", 5, "on", "", "DNS", "", "") << std::endl << std::endl;
    	thread_pool dns_pool(argp._threads_dns);

    	for (int i = 0; i < argp._threads_dns; i++) 
		{
        	dns_pool.enqueue([&]() {
            	for (;;) 
				{
                	std::string random_ = generate_random_str(argp.dns_scan_domain_count, argp.dns_dictionary);
                	std::string result = random_ + argp.domain_1level;
                	std::string ip = dus.get_ip_by_dns(result.c_str());

                	if (ip == "N/A") 
					{
                    	if (argp.debug) {
                        	std::lock_guard<std::mutex> lock(mtx);
                        	np.nlog_custom("BA", result + " [FaILEd]\n", 2);
                    	}
                    	continue;
                	}

                	if (ip == "-1") {
                    	if (argp.debug) {
                        	std::lock_guard<std::mutex> lock(mtx);
                        	np.nlog_custom("BA", result + " [FaILEd]\n", 2);
                    	}
                    	continue;
                	}

                	std::string result_print;
                	bool ping_status = process_ping(ip.c_str());

                	if (!ping_status)
					{
                    	if (argp.debug)
						{
                        	std::lock_guard<std::mutex> lock(mtx);
                        	np.nlog_custom("BA", result + " [FaILEd]\n", 2);
                    	}
                	}
                	else {
                    	std::string html = send_http_request(ip, 80);
                    	std::lock_guard<std::mutex> lock(mtx);
                    	std::string rtt = std::to_string(argp.rtts[ip]) + "ms";
                    	std::cout << np.main_nesca_out("BA", "http://" + result, 3, "T", "RTT", get_http_title(html), rtt, rtt) << std::endl;

                    	if (argp.get_response)
						{
                        	std::string result_code = np.main_nesca_out("TT", html, 2, "", "", "", "", "");
                        	std::cout << result_code << std::endl;
                    	}
                	}
            	}
        	});
        
        	if (argp.timeout) {delay_ms(argp.timeout_ms);}
    	}

    	std::getchar();
    	std::cout << np.main_nesca_out("NN", "Stoping threads...", 0, "", "", "", "", "") << std::endl;
	}

	/*Иницилизация брутфорса.*/
    init_bruteforce();

	/*Определение цели.*/
    if (optind < argc)
	{
		std::vector<std::string> temp_ips;
		std::string target_arg(argv[optind]);
		size_t cidr_pos = find_char(target_arg, '/');
    	size_t range_pos = find_char(target_arg, '-');

        temp_ips = split_string_string(argv[optind], ',');
        if (cidr_pos != std::string::npos)
		{
			argp.ip_cidr_scan = true;
			argp.result = cidr_to_ips(temp_ips);
        }
        else if (range_pos != std::string::npos)
		{
			argp.ip_range_scan = true;
			argp.result = range_to_ips(temp_ips);
        }
        else 
		{
			argp.ip_scan = true;
            argp.dns = temp_ips;
            if (dns_or_ip(argp.dns[0])) {argp.result = convert_dns_to_ip(argp.dns);}
            else {argp.result = temp_ips;}
        }
    }

    if (argp.random_ip)
	{
        for (int i = 1; i <= argp.random_ip_count; i++)
		{
            std::string random_temp = generate_ipv4();
            argp.result.push_back(random_temp);
        }
    }

    int ip_count = 0;
    int flag_desing = 0;
    std::vector<std::string> result_main;

	/*Расчёт количества потоков и таймаута для пинга.*/
	if (!argp.custom_threads)
	{
    	if (argp.my_life_my_rulez)
		{
        	argp.threads_ping = argp.result.size();
        	argp.ping_timeout = 250;
    	}else
		{
        	argp.threads_ping = calc_threads(argp.speed_type, argp.result.size());
        	argp.ping_timeout = calc_timeout(argp.speed_type);
    	}
	}

	if (!argp.syn_ping && !argp.ack_ping && !argp.echo_ping && !argp.info_ping && !argp.timestamp_ping){argp.ack_ping = true;argp.echo_ping = true;}
	auto start_time_ping = std::chrono::high_resolution_clock::now();

    /*Пинг сканирования*/
	if (!argp.ping_off) 
	{
		if (argp.pro_mode)
		{
    		std::cout << np.main_nesca_out("NESCA4", "PING_SCAN", 5, "recv-timeout", "threads", std::to_string(argp.ping_timeout), std::to_string(argp.threads_ping), "") << std::endl;
		}
		thread_pool ping_pool(argp.threads_ping);
    	int threads_ping = argp.threads_ping;
    	int ips_per_thread = argp.result.size() / threads_ping;
    	int ip_count_ping = 0;
    	std::vector<std::future<std::pair<bool, std::string>>> futures;
    	auto result_iter = argp.result.begin();

    	while (result_iter != argp.result.end())
		{
        	int remaining_tasks = std::distance(result_iter, argp.result.end());
			int tasks_to_execute = (threads_ping < remaining_tasks) ? threads_ping : remaining_tasks;

        	for (int i = 0; i < tasks_to_execute; ++i)
			{
            	std::string ip = *result_iter;
            	futures.push_back(ping_pool.enqueue([ip]() -> std::pair<bool, std::string> {
                	bool ping = process_ping(ip);
                	return std::make_pair(ping, ip);
            	}));
            	++result_iter;
        	}
        	for (auto& future : futures)
			{
            	auto result = future.get();
            	bool ping = result.first;
            	std::string ip = result.second;
            	if (ping) {result_main.push_back(ip);}
        	}
        	futures.clear();

        	for (auto& future : futures) {future.wait();}
        	ip_count_ping += tasks_to_execute;

        	if (ip_count_ping % argp.ping_log == 0)
			{
            	double procents = (static_cast<double>(ip_count_ping) / argp.result.size()) * 100;
            	std::string _result = format_percentage(procents);
				std::cout << np.main_nesca_out("#", "Ping "+std::to_string(ip_count_ping)+" out of "+
						std::to_string(argp.result.size()) + " IPs", 6, "", "", _result+"%", "", "") << std::endl;
        	}
    	}
    	int error_count = argp.result.size() - result_main.size();
    	// std::cout << np.main_nesca_out("NESCA4", "FINISH ping", 5, "success", "errors", std::to_string(result_main.size()), std::to_string(error_count)) << std::endl;
	}
	if (argp.ping_off){result_main = argp.result;}
	auto end_time_ping = std::chrono::high_resolution_clock::now();
	auto duration_ping = std::chrono::duration_cast<std::chrono::microseconds>(end_time_ping - start_time_ping);
	argp.ping_duration = duration_ping.count() / 1000000.0;

	/*Расчёт количеста потоков для DNS resolv.*/
	if (!argp.custom_threads_resolv){argp.dns_threads = calc_threads(argp.speed_type, result_main.size());}
	if (argp.my_life_my_rulez){argp.dns_threads = result_main.size();}

	auto start_time_dns = std::chrono::high_resolution_clock::now();
	if (!argp.no_get_dns)
	{
		if (argp.pro_mode)
		{
			std::cout << np.main_nesca_out("NESCA4", "DNS_RESOLUTION", 5, "threads", "",
			std::to_string(argp.dns_threads), "","") << std::endl;
		}
		std::vector<std::future<void>> futures_dns;
		thread_pool dns_pool(argp.dns_threads);

		for (const auto& ip : result_main)
		{
			futures_dns.emplace_back(dns_pool.enqueue(get_dns_thread, ip));
        	if (futures_dns.size() >= argp.dns_threads)
			{
            	for (auto& future : futures_dns){future.get();}
            	futures_dns.clear();
        	}
    	}
		for (auto& future : futures_dns){future.wait();}
		futures_dns.clear();
	}
	auto end_time_dns = std::chrono::high_resolution_clock::now();
	auto duration_dns = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dns - start_time_dns);
	argp.dns_duration = duration_dns.count() / 1000000.0;


	/*Установка настроек группы и потоков.*/
	if (argp.speed_type == 5)
	{
		if (!argp.custom_g_max){argp.group_size_max = 2000;}
		if (!argp.custom_g_rate){argp.group_rate = 100;}
	}
	else if (argp.speed_type == 4)
	{
		if (!argp.custom_g_max){argp.group_size_max = 1500;}
		if (!argp.custom_g_rate){argp.group_rate = 50;}
	}
	else if (argp.speed_type == 3)
	{
		if (!argp.custom_g_max){argp.group_size_max = 1000;}
		if (!argp.custom_g_rate){argp.group_rate = 20;}
	}
	else if (argp.speed_type == 2)
	{
		if (!argp.custom_g_max){argp.group_size_max = 500;}
		if (!argp.custom_g_rate){argp.group_rate = 10;}
	}
	else if (argp.speed_type == 1)
	{
		if (!argp.custom_g_max){argp.group_size_max = 300;}
		if (!argp.custom_g_rate){argp.group_rate = 5;}
	}

	/*Потоки для сканирования портов.*/
	argp._threads = argp.group_size_max;
	
	if (argp.pro_mode)
	{
		std::cout << np.main_nesca_out("NESCA4", get_type(argp.type), 5, "targets", "threads",
				std::to_string(result_main.size()),std::to_string(argp._threads),"") << std::endl;
	}

    ncopts.source_ip = argp.source_ip;
	ncopts.packet_trace = argp.packet_trace;
	ncopts.tcpf = set_flags(argp.type);

    long long size = result_main.size();
    std::vector<std::future<int>> futures;
    std::set<std::string> processed_ip;
    int skipped_ip = 0;
	int count_success_ips = 0;

	/*Создание пула потоков.*/
	thread_pool pool(argp._threads);

    /*Сканирование по группам*/
	int group_start = 0;
	bool fix_group_log = true;
	while (group_start < size)
	{
		auto start_time_scan = std::chrono::high_resolution_clock::now();
		int group_end = (group_start + static_cast<int>(argp.group_size) < static_cast<int>(size)) ?
               group_start + static_cast<int>(argp.group_size) :
               static_cast<int>(size);

    	std::vector<std::string> 
		ip_group(result_main.begin() + group_start, result_main.begin() + group_end);

        /*Сканирование текущей группы*/
        for (const auto& ip : ip_group)
		{
			/*Подсчёт повторившихся IP.*/
            if (processed_ip.count(ip) > 0){skipped_ip++;continue;}

        	ip_count++;
        	processed_ip.insert(ip);

			int log_set;
			if (argp.custom_log_set){log_set = argp.log_set;}
			else{log_set = argp.group_size;}

        	if (ip_count % log_set == 0)
			{
            	double procents = (static_cast<double>(ip_count) / size) * 100;
            	std::string result = format_percentage(procents);

				std::cout << np.main_nesca_out("#", "Scan "+std::to_string(ip_count)+" out of "+
						std::to_string(size) + " IPs", 6, "", "", result+"%", "", "") << std::endl;

				std::cout << np.main_nesca_out("# rate", "Group "+std::to_string(argp.group_size)+" out of "+
						std::to_string(argp.group_size_max), 6, "", "", std::to_string(argp.group_rate), "", "") << std::endl;
        	}

        	/*Добавление задачи сканирования портов в пул потоков*/
        	auto fut = pool.enqueue(scan_ports, ip.c_str(), argp.ports, argp.timeout_ms);
        	futures.push_back(std::move(fut));

        	if (futures.size() >= argp._threads)
			{
            	/*Получение результата задачи из пула потоков*/
            	int main_scan = futures.front().get();
            	futures.erase(futures.begin());
        	}
    	}

		if (argp.group_size < argp.group_size_max && argp.group_size > 0){argp.group_size += argp.group_rate;}
		group_start = group_end;

    	for (auto& fut : futures){fut.wait();} /*Ожидание оставшихся потоков.*/
    	for (auto& fut : futures) {int main_scan = fut.get();} /*Получение результата функции.*/
		if (argp.packet_trace){std::cout << std::endl;}
    	futures.clear(); /*Очистка после потоков.*/

		auto end_time_scan = std::chrono::high_resolution_clock::now();
		auto duration_scan = std::chrono::duration_cast<std::chrono::microseconds>(end_time_scan - start_time_scan);
		argp.scan_duration += duration_scan.count() / 1000000.0;

		auto start_time_proc = std::chrono::high_resolution_clock::now();

		/*Для первого переноса \n.*/
		bool standart_mode_fix = true;

        /*Обработка результатов для текущей группы*/
        for (const auto& ip : ip_group)
		{
	   		if (argp.success_target.find(ip) != argp.success_target.end() 
			   	|| argp.debug 
			   	|| argp.open_or_filtered_target.find(ip) != argp.open_or_filtered_target.end()
	           	|| argp.no_filtered_target.find(ip) != argp.no_filtered_target.end())
			{

		  		double time_ms = argp.rtts[ip];
		  		if (np.save_file){write_line(np.file_path_save, "\n");}

				std::string result;
		  		std::cout << np.main_nesca_out("READY", ip, 5, "rDNS", "RTT", argp.dns_completed[ip], std::to_string(argp.rtts[ip])+"ms","") << std::endl;
	   			print_results(ip);
				std::cout << std::endl;
			}
        }

		/*Успешные цели.*/
		count_success_ips += argp.success_target.size();
		count_success_ips += argp.no_filtered_target.size();
		count_success_ips += argp.open_or_filtered_target.size();

		argp.open_or_filtered_target.clear();
		argp.filtered_target.clear();
		argp.closed_target.clear();
		argp.success_target.clear();
		argp.no_filtered_target.clear();
		argp.error_target.clear();

		auto end_time_proc = std::chrono::high_resolution_clock::now();
		auto duration_proc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_proc - start_time_proc);
		argp.proc_duration += duration_proc.count() / 1000000.0;
	}

	if (np.save_file){write_line(np.file_path_save, "\n");}

	np.golder_rod_on();
	std::cout << "-> NESCA finished " << count_success_ips << " up IPs (success) in "
		<< std::fixed << std::setprecision(2) << argp.ping_duration+argp.dns_duration+argp.scan_duration+argp.proc_duration << " seconds";
	np.reset_colors();

	if (!argp.pro_mode){
		np.golder_rod_on();
		std::cout << "\n-^ If you want to see the detailed execution use: -pro\n";
		np.reset_colors();
	}

    if (skipped_ip > 0){std::cout << np.main_nesca_out("NESCA4", std::to_string(skipped_ip)+" identical IPs", 5, "status", "", "OK", "","") << std::endl;}

	if (argp.pro_mode)
	{
		np.golder_rod_on();
		std::cout << "\n-> PING:"; fix_time(argp.ping_duration);
		std::cout << "  DNS:";     fix_time(argp.dns_duration);
		std::cout << "  SCAN:";    fix_time(argp.scan_duration);
		std::cout << "  PROC:";    fix_time(argp.proc_duration);
		std::cout << std::endl;
	}

    return 0;
}

/*Функция через которую происходит само сканирование
 * портов. Стабильно.*/
int
scan_ports(const char* ip, std::vector<int>ports, const int timeout_ms)
{
	/*Установка порты с которого будут идти пакеты на этот IP.*/
	int source_port;
	if (!argp.custom_source_port){source_port = generate_port();}
	else {source_port = argp._custom_source_port;}

	/*Если не было получено RTT, по стандарту время ответа 600.*/
    int recv_timeout_result = 600;

	/*Если кастомное.*/
    if (argp.custom_recv_timeout_ms){recv_timeout_result = argp.recv_timeout_ms;}else
	{
	   /*Расчёт таймаута для приёма данных*/
	   auto it = argp.rtts.find(ip);
	   if (it != argp.rtts.end())
	   {
		  double rtt_ping = argp.rtts.at(ip);
		  recv_timeout_result = calc_port_timeout(argp.speed_type, rtt_ping);
	   }
    }

	/*Один рандомный порт отправки на каждый IP.
	 * Можно и на каждый порт, но лучше менять не часто.*/
    ncopts.source_port = source_port;

	/*Рандомный SEQ на каждый IP. Не порт!*/
    ncopts.seq = generate_seq();

    for (const auto& port : ports)
	{
		/*Настройка TTL.*/
		if (!argp.custom_ttl){ncopts.ttl = generate_ttl();}
		else{ncopts.ttl = argp._custom_ttl;}

	   /*Отправка пакета.*/
	   const int result = nesca_scan(&ncopts, ip, port, timeout_ms);

	   /*Если функция не вернула PORT_OPEN,
	    * Это означает что функция успешно выполнилась.*/
	   if (result != PORT_OPEN)
	   {
		  ls.lock();
		  /*Значит была ошибка.*/
		  if (argp.print_errors){argp.error_target[ip].push_back(port); argp.error_fuck++;}
		  ls.unlock();
		  /*Переход к следующему порту.*/
		  continue;
	   }

	   ls.lock(); /*Буфер для ответа.*/
	   unsigned char *buffer = (unsigned char *)calloc(READ_BUFFER_SIZE, sizeof(unsigned char));
	   ls.unlock();

	   /*В другом случае, запускается
	    * "Принятие пакета" или скорее его ожидание.*/
	   int read = ncread(ip, recv_timeout_result, &buffer, argp.syn_debug, port, source_port, argp.packet_trace);
	   /*Если функция не получила пакет.*/
	   if (read != SUCCESS_READ)
	   {
		  ls.lock();
		  free(buffer);
		  ls.unlock();

		  if (argp.type != SYN_SCAN && argp.type != ACK_SCAN && argp.type != WINDOW_SCAN)
		  {
		  	  ls.lock();
		      /*Значит порт open|filtered.*/
			  argp.open_or_filtered_target[ip].push_back(port);
		  	  ls.unlock();
		  }
		  else
		  {
		  	  ls.lock();
		  	  /*Значит порт filtered.*/
			  if (argp.debug){argp.filtered_target[ip].push_back(port);}
		  	  ls.unlock();
		  }
		  continue;
	   }

	   /*В другом случае идёт обработка пакета.
	    * И только на этом этапе мы получаем статус порта.*/
	   int port_status = -1;
	   port_status = get_port_status(buffer, argp.type);

	   if (port_status == PORT_CLOSED && argp.debug){argp.closed_target[ip].push_back(port);}
	   else if (port_status == PORT_OPEN){argp.success_target[ip].push_back(port);}
	   if (port_status == PORT_FILTER && argp.debug){argp.filtered_target[ip].push_back(port);}
	   else if (port_status == PORT_NO_FILTER){argp.no_filtered_target[ip].push_back(port);}

	   ls.lock();
	   free(buffer);
	   ls.unlock();
    }

    return 0;
}


void
print_results(std::string ip)
{
	/*Лямбда функция.*/
	auto process_ports = [&](const std::unordered_map<std::string, std::vector<int>>& target_map, int port_type) 
	{
        auto it = target_map.find(ip);
        if (it != target_map.end()) 
		{
            const std::vector<int>& ports = it->second;
            for (int port : ports){processing_tcp_scan_ports(ip, port, port_type);}
        }
    };

	/*Её использование.*/
    process_ports(argp.success_target, PORT_OPEN);
    process_ports(argp.error_target, PORT_ERROR);
    process_ports(argp.filtered_target, PORT_FILTER);
    process_ports(argp.closed_target, PORT_CLOSED);
    process_ports(argp.open_or_filtered_target, PORT_OPEN_OR_FILTER);
    process_ports(argp.no_filtered_target, PORT_NO_FILTER);
}

void
fix_time(double time) {std::cout << std::fixed << std::setprecision(2) << time << "s";}

bool /*Лесенка ping-ов.*/
process_ping(std::string ip)
{
	int ttl = 121;
	int source_port;
	if (!argp.custom_source_port){source_port = generate_port();}
	else {source_port = argp._custom_source_port;}
	if (argp.custom_ttl){ttl = argp._custom_ttl;}

	/*ICMP ECHO классика.*/
	if (argp.echo_ping)
	{
    	double icmp_casual = icmp_ping(ip.c_str(), argp.ping_timeout, 8, 0, 0, 64);
    	if (icmp_casual != EOF)
		{
	   		argp.rtts[ip] = icmp_casual;
	   		return true;
    	}
	}
	/*TCP_SYN PING*/
	if (argp.syn_ping)
	{
		double status_time1 = tcp_syn_ping(ip.c_str(), argp.source_ip, argp.syn_dest_port, source_port, argp.ping_timeout, ttl);
		if (status_time1 != EOF)
		{
			argp.rtts[ip] = status_time1;
			return true;
		}
	}
	/*TCP_ACK PING*/
	if (argp.ack_ping)
	{
		double status_time = tcp_ack_ping(ip.c_str(), argp.source_ip, argp.ack_dest_port, source_port, argp.ping_timeout, ttl);
		if (status_time != EOF)
		{
			argp.rtts[ip] = status_time;
			return true;
		}
	}
	/*ICMP пинг 2 методами.*/
	if (argp.info_ping)
	{
    	double icmp_rev = icmp_ping(ip.c_str(), argp.ping_timeout, 13, 0, 0, 64);
		if (icmp_rev != EOF)
		{
			argp.rtts[ip] = icmp_rev;
			return true;
		}
	}
	if (argp.timestamp_ping)
	{
    	double icmp_rev1 = icmp_ping(ip.c_str(), argp.ping_timeout, 15, 0, 0, 64);
		if (icmp_rev1 != EOF)
		{
			argp.rtts[ip] = icmp_rev1;
			return true;
		}
	}
    return false;
}

int errors_files = 0;

void check_files(const char* path, const char* path1)
{
    if (!check_file(path)){
        np.nlog_error(std::string(path) + " (" + std::to_string(get_count_lines(path)) + ") entries\n");
		errors_files++;
    }else if (!check_file(path1)){
		np.nlog_error(std::string(path1) + " (" + std::to_string(get_count_lines(path1)) + ") entries\n");
		errors_files++;
    }
}

void 
checking_default_files(void)
{
	/*Чек целей из файлов.*/
	std::vector<std::string> temp_ips;
	if (argp.ip_cidr_scan_import && check_file(argp.path_cidr)) {
        np.nlog_trivial(std::string(argp.path_cidr) + " (" + std::to_string(get_count_lines(argp.path_cidr)) + ") entries\n");
        if (argp.ip_cidr_scan){np.nlog_trivial(std::string(argp.path_cidr) + " (" + std::to_string(get_count_lines(argp.path_cidr)) + ") entries\n");}
        temp_ips = write_file(argp.path_cidr);
		argp.result = cidr_to_ips(temp_ips);
    }else if (argp.ip_cidr_scan_import) {
        np.nlog_error(std::string(argp.path_cidr) + " (" + std::to_string(get_count_lines(argp.path_cidr)) + ") entries\n");
        errors_files++;
    }
    if (argp.ip_range_scan_import && check_file(argp.path_range)) {
        np.nlog_trivial(std::string(argp.path_range) + " (" + std::to_string(get_count_lines(argp.path_range)) + ") entries\n");
        if (argp.ip_range_scan){np.nlog_trivial(std::string(argp.path_range) + " (" + std::to_string(get_count_lines(argp.path_range)) + ") entries\n");}
        temp_ips = write_file(argp.path_range);
		argp.result = range_to_ips(temp_ips);
    }else if (argp.ip_range_scan_import) {
        np.nlog_error(std::string(argp.path_range) + " (" + std::to_string(get_count_lines(argp.path_range)) + ") entries\n");
        errors_files++;
    }
    if (argp.ip_scan_import && check_file(argp.path_ips)) {
        np.nlog_trivial(std::string(argp.path_ips) + " (" + std::to_string(get_count_lines(argp.path_ips)) + ") entries\n");
        argp.result = write_file(argp.path_ips);
    }else if (argp.ip_scan_import) {
        np.nlog_error(std::string(argp.path_ips) + " (" + std::to_string(get_count_lines(argp.path_ips)) + ") entries\n");
        errors_files++;
    }

	/*Чек паролей и логин.*/
	check_files(argp.path_ftp_login.c_str(),argp.path_ftp_pass.c_str());
    check_files(argp.path_sftp_login.c_str(),argp.path_sftp_pass.c_str());
    check_files(argp.path_http_login.c_str(),argp.path_http_pass.c_str());
    check_files(argp.path_rtsp_login.c_str(),argp.path_rtsp_pass.c_str());
    check_files(argp.path_smtp_login.c_str(),argp.path_smtp_pass.c_str());
    check_files(argp.path_hikvision_login.c_str(),argp.path_hikvision_pass.c_str());
    check_files(argp.path_rvi_login.c_str(),argp.path_rvi_pass.c_str());

	/*Ну чё там.*/
    if (errors_files == 0)
	{
	   if (argp.pro_mode)
	   {
		   std::cout << np.main_nesca_out("NESCA4", "BRUTEFORCE_DATA", 5, "status", "", "OK","","") << std::endl;
	   }
	}
    else {std::cout << std::endl << np.main_nesca_out("NESCA4", "BRUTEFORCE_DATA", 5, "status", "ERRORS", "FAILED", std::to_string(errors_files),"") << std::endl;}
}

void
print_port_state(int status, int port, std::string service){
	std::string result_txt = "[&][REPORT]:" + std::to_string(port) + "/tcp STATE: ";
    np.gray_nesca_on();
    std::cout << "[&][REPORT]:";
    np.green_html_on();
    std::cout << std::to_string(port) << "/tcp"; 
    np.gray_nesca_on();
    std::cout << " STATE: ";
    if (status == PORT_OPEN)
	{
	   np.green_html_on();
	   result_txt += "open";
	   std::cout << "open"; 
    }
    else if (status == PORT_CLOSED)
	{
	   np.reset_colors();
	   result_txt += "closed";
	   std::cout << "closed"; 
    }
    else if (status == PORT_FILTER)
	{
	   np.yellow_html_on();
	   result_txt += "filtered";
	   std::cout << "filtered"; 
    }
    else if (status == PORT_ERROR)
	{
	   np.red_html_on();
	   result_txt += "error";
	   std::cout << "error"; 
    }
    else if (status == PORT_OPEN_OR_FILTER)
	{
	   np.yellow_html_on();
	   result_txt += "open|filtered";
	   std::cout << "open|filtered"; 
    }
    else if (status == PORT_NO_FILTER)
	{
	   np.green_html_on();
	   result_txt += "unfiltered";
	   std::cout << "unfiltered"; 
    }
    np.gray_nesca_on();
    std::cout << " SERVICE: ";
    np.green_html_on();
    std::cout << service << std::endl;
    np.reset_colors();
	result_txt += " SERVICE: " + service;

	if (np.save_file){write_line(np.file_path_save, result_txt + "\n");}
}

void ssh_strategy::handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
		const std::string& protocol, int port, arguments_program& argp, nesca_prints& np)
{
    if (argp.off_sftp_brute != true)
	{
		np.yellow_html_on();
		std::cout << "[>][SSH]:" + ip + " [BRUTEFORCE]\n";
		np.reset_colors();

		brute_temp = threads_brute_ssh(ip, port, argp.sftp_logins, argp.sftp_passwords, argp.sftp_brute_log,
            argp.sftp_brute_verbose, argp.sftp_using_know_hosts, argp.brute_timeout_ms);

        if (argp.sftp_only)
		{
            if (brute_temp.length() > 1){result_print = np.main_nesca_out("BA", "sftp://" + brute_temp + result, 3, "", "", "", "",rtt_log, "", protocol);}
        }
        else {result_print = np.main_nesca_out("BA", "sftp://" + brute_temp + result, 3, "", "", "", "",rtt_log, "", protocol);}
    }
    else {result_print = np.main_nesca_out("BA", "sftp://" + result, 3, "", "", "", "",rtt_log,"", protocol);}
    std::cout << result_print << std::endl;
}

void ftp_strategy::handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
		const std::string& protocol, int port, arguments_program& argp, nesca_prints& np)
{

	std::string port_s = std::to_string(port);
	std::string ftp_version = get_ftp_description(ip, port_s, bfd_.get_success_login(), bfd_.get_success_pass());

    if (argp.off_ftp_brute != true)
	{
		np.yellow_html_on();
		std::cout << "[>][FTP]:" + ip + " [BRUTEFORCE]\n";
		np.reset_colors();

        brute_temp = threads_brute_ftp(ip, port, argp.ftp_logins, argp.ftp_passwords, argp.ftp_brute_log,
                argp.ftp_brute_verbose, argp.brute_timeout_ms);

        if (argp.ftp_only)
		{
            if (brute_temp.length() > 1)
			{
                result_print = np.main_nesca_out("BA", "ftp://" + brute_temp + result, 3, "D", "",
                        ftp_version ,rtt_log, "", protocol);
            }
        }
        else 
		{
            result_print = np.main_nesca_out("BA", "ftp://" + brute_temp + result, 3, "D", "",
                ftp_version ,rtt_log, "", protocol);
        }
    }
    else 
	{
        result_print = np.main_nesca_out("BA", "ftp://" + brute_temp + result, 3, "D", "",
                ftp_version ,rtt_log, "", protocol);
    }
                
    std::cout << result_print << std::endl;
}
void smtp_strategy::handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
		const std::string& protocol, int port, arguments_program& argp, nesca_prints& np)
{
	std::string responce_220 = smtp_get_220_response(ip, port, 0);
    if (argp.off_sftp_brute != true)
	{
		np.yellow_html_on();
		std::cout << "[>][SMTP]:" + ip + " [BRUTEFORCE]\n";
		np.reset_colors();

        brute_temp = threads_brute_smtp(ip, port, argp.smtp_logins, argp.smtp_passwords, argp.smtp_brute_log,
            argp.smtp_brute_verbose, argp.brute_timeout_ms);


        if (argp.sftp_only)
		{
            if (brute_temp.length() > 1)
			{
                result_print = np.main_nesca_out("BA", "smtp://" + brute_temp + result, 3, "D", "", responce_220, "",rtt_log, "", protocol);
            }
        }
        else 
		{
            result_print = np.main_nesca_out("BA", "smtp://" + brute_temp + result, 3, "D", "", responce_220, "",rtt_log, "", protocol);
        }
    }
    else 
	{
        result_print = np.main_nesca_out("BA", "smtp://" + result, 3, "", "", responce_220, "",rtt_log, "", protocol);
    }
    std::cout << result_print << std::endl;
}
void hikvision_strategy::handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
		const std::string& protocol, int port, arguments_program& argp, nesca_prints& np)
{
    if (argp.off_hikvision_brute != true)
	{
		np.yellow_html_on();
		std::cout << "[>][HIKVISION]:" + ip + " [BRUTEFORCE]\n";
		np.reset_colors();
        brute_temp = threads_brute_hikvision(ip, argp.hikvision_logins, argp.hikvision_passwords, argp.hikvision_brute_log,
                    argp.brute_timeout_ms);

        if (argp.hikvision_only)
		{
            if (brute_temp.length() > 1)
			{
                result_print = np.main_nesca_out("BA", "" + brute_temp + result, 3, "", "", "", "",rtt_log, "", protocol);
            }
        }
        else 
		{
            result_print = np.main_nesca_out("BA", "" + brute_temp + result, 3, "", "", "", "",rtt_log, "", protocol);
        }
    }
    else 
	{
        result_print = np.main_nesca_out("BA", "" + result, 3, "", "", "", "",rtt_log, "", protocol);
    }
    std::cout << result_print << std::endl;
}

void https_strategy::handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
		const std::string& protocol, int port, arguments_program& argp, nesca_prints& np)
{
    std::string result_print = np.main_nesca_out("BA", "https://" + result, 3, "", "", "", "",rtt_log, "" ,protocol);
    std::cout << result_print << std::endl;
}

void rvi_strategy::handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
		const std::string& protocol, int port, arguments_program& argp, nesca_prints& np)
{
    if (argp.off_rvi_brute != true){
		np.yellow_html_on();
		std::cout << "[>][RVI]:" + ip + " [BRUTEFORCE]\n";
		np.reset_colors();
        brute_temp = threads_brute_rvi(ip, port, argp.rvi_logins, argp.rvi_passwords, argp.rvi_brute_log,
                    argp.brute_timeout_ms);

        if (argp.rvi_only)
		{
            if (brute_temp.length() > 1)
			{
                result_print = np.main_nesca_out("BA", "" + brute_temp + result, 3, "", "", "", "",rtt_log, "", protocol);
            }
        }
        else
		{
        	result_print = np.main_nesca_out("BA", "" + brute_temp + result, 3, "", "", "", "",rtt_log,"", protocol);
        }
    }
    else
	{
        result_print = np.main_nesca_out("BA", "" + result, 3, "", "", "", "",rtt_log,"", protocol);
    }

    std::cout << result_print << std::endl;
}

void rtsp_strategy::handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
		const std::string& protocol, int port, arguments_program& argp, nesca_prints& np)
{
    std::string path_yes = "";
    if (argp.off_rtsp_brute != true)
	{
        std::vector<std::string> rtsp_paths = {"/Streaming/Channels/101", "/h264/ch01/main/av_stream", 
                                            "/cam/realmonitor?channel=1&subtype=0","/live/main",
                                            "/av0_0", "/mpeg4/ch01/main/av_stream"};
		np.yellow_html_on();
		std::cout << "[>][RTSP]:" + ip + " [BRUTEFORCE]\n";
		np.reset_colors();

        for (auto& path : rtsp_paths)
		{
            brute_temp = threads_brute_rtsp(ip+path, argp.rtsp_logins, argp.rtsp_passwords, argp.rtsp_brute_log, argp.rtsp_brute_verbose,
                        argp.brute_timeout_ms);
            if (brute_temp.length() > 1)
			{
                path_yes = path;
            }
        }

        if (argp.rtsp_only)
		{
            if (brute_temp.length() > 1)
			{
                result_print = np.main_nesca_out("BA", "rtsp://" + brute_temp + result + path_yes, 3, "", "", "", "",rtt_log, "", protocol);
            }
        }
        else 
		{
            result_print = np.main_nesca_out("BA", "rtsp://" + brute_temp + result + path_yes, 3, "", "", "", "",rtt_log, "", protocol);
        }
    }
    else 
	{
        result_print = np.main_nesca_out("BA", "rtsp://" + result, 3, "", "", "", "",rtt_log,"", protocol);
    }

    std::cout << result_print << std::endl;
}

void http_strategy::handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
		const std::string& protocol, int port, arguments_program& argp, nesca_prints& np)
{
	/*Получение заголовков и кода страницы.*/
    std::string redirect;
    std::string html = to_lower_case(send_http_request(ip, port));
    std::string default_result = "http://" + ip + ":" + std::to_string(port) + "/";

	/*Получение перенаправления.*/
    if (argp.no_get_path != true){redirect = parse_redirect(html, html, ip, true, port);}

	/*Получение заголовка.*/
    std::string http_title_result = get_http_title(html);
   	if (cfs.contains_word("301", http_title_result)){http_title_result = get_http_title_pro(ip);}

	/*Сравнение списка negatives*/
	for (const auto& n : nn.nesca_negatives)
	{
		const std::string& first = n.first;
        const std::string& second = n.second;

		if (second == "1" || second == "title")
		{
			if(cfs.contains_word(first, http_title_result))
			{
				if (argp.debug){np.nlog_custom("WARNING", "Skip negative: "+first+"\n", 2);}
				return;
			}
		}
		else if (second == "2" || second == "code" || second == "header")
		{
			if(cfs.contains_word(first, html))
			{
				if (argp.debug){np.nlog_custom("WARNING", "Skip negative: "+first+"\n", 2);}
				return;
			}
		}
		else if (second == "3" || second == "path" || second == "redirect")
		{
			if(cfs.contains_word(first, redirect))
			{
				if (argp.debug){np.nlog_custom("WARNING", "Skip negative: "+first+"\n", 2);}
				return;
			}
		}
	}

	/*Удаление переносов из заголовка.*/
    http_title_result.erase(std::remove(http_title_result.begin(), http_title_result.end(), '\r'), http_title_result.end());
    http_title_result.erase(std::remove(http_title_result.begin(), http_title_result.end(), '\n'), http_title_result.end());
	if (http_title_result.empty()){http_title_result = "n/a";}

	/*Получение характеристики.*/
	std::string type_target = "n/a";
    std::string temp_check_http = cfs.set_target_at_path(redirect);
	std::string temp_check_http1 = cfs.set_target_at_http_header(html);
	std::string temp_check_http2 = cfs.set_target_at_title(http_title_result);
	if (temp_check_http != "fuck"){type_target = temp_check_http;}
	if (temp_check_http1 != "fuck"){type_target = temp_check_http1;}
	if (temp_check_http2 != "fuck"){type_target = temp_check_http2;}
	int brute = cfs.than_bruteforce(type_target);

	/*Брутфорс HTTP basic auth.*/
    if (argp.off_http_brute != true && temp_check_http != "no" && argp.no_get_path != true && brute != EOF)
	{
		np.yellow_html_on();
		std::cout << "[>][HTTP]:" + ip + " [BRUTEFORCE]\n";
		np.reset_colors();

        brute_temp = threads_brute_http("http://" + ip + redirect, argp.http_logins, argp.http_passwords,
                argp.http_brute_log, argp.http_brute_verbose, argp.brute_timeout_ms);
    }

    result_print = np.main_nesca_out("BA", "http://" + brute_temp + ip + ":" + std::to_string(port), 3, "T", "F", http_title_result, 
			type_target, rtt_log, "", protocol );

    if (argp.http_only)
	{
		if (brute_temp.length() > 1)
		{
			result_print = np.main_nesca_out("BA", "http://" + brute_temp + ip + ":" + std::to_string(port),
				3, "T", "F", http_title_result, type_target, rtt_log, "", protocol);
		}
	}

	/*Вывод основного.*/
    std::cout << result_print << std::endl;

	/*Вывод перенаправления.*/
    if (redirect.length() != default_result.length())
	{
        if (redirect.length() != 0)
		{
			np.gray_nesca_on();
			std::cout << "[^][REDIRT]:";
			np.yellow_html_on();
			std::cout << redirect + "\n";
			np.reset_colors();
			if (np.save_file){write_line(np.file_path_save, "[^][REDIRT]:" + redirect);}
        }
    }

	/*Вывод ответа http.*/
    if (argp.get_response)
	{
		np.yellow_html_on();
		std::cout << html << std::endl;
		np.reset_colors();
	}
}

void else_strategy::handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
		const std::string& protocol, int port, arguments_program& argp, nesca_prints& np)
{
	std::string result_print = np.main_nesca_out("BA", result, 3, "", "", "", "",rtt_log, "", protocol);
	print_port_state(PORT_OPEN, port, sn.probe_service(port));
}

void 
processing_tcp_scan_ports(std::string ip, int port, int result)
{
		std::stringstream stream; stream << std::fixed << std::setprecision(2) << argp.rtts[ip];
    	std::string rtt_log = stream.str();
		std::string protocol = sn.probe_service(port);

		/*Класс с обработками.*/
		std::unique_ptr<ports_strategy> ports_strategy_;

		/*Открытый порт.*/
        if (result == PORT_OPEN)
		{
		  	if (argp.no_proc){print_port_state(PORT_OPEN, port, sn.probe_service(port));return;}
            std::string result1 = ip + ":" + std::to_string(port);

            if (sn.probe_service(port) == "HTTP")
			{
				print_port_state(PORT_OPEN, port, "HTTP");
				ports_strategy_ = std::make_unique<http_strategy>();
            }
            else if (port == 20 || port == 21)
			{
			 	print_port_state(PORT_OPEN, port, "FTP");
			 	ports_strategy_ = std::make_unique<ftp_strategy>();
            }
            else if (port == 22)
			{
			 	print_port_state(PORT_OPEN, port, "SSH");
				ports_strategy_ = std::make_unique<ssh_strategy>();
            }
            else if (port == 554)
			{
			 	print_port_state(PORT_OPEN, port, "RTSP");
			 	ports_strategy_ = std::make_unique<rtsp_strategy>();
            }else if (port == 37777)
			{
			    print_port_state(PORT_OPEN, port, "RVI");
			 	ports_strategy_ = std::make_unique<rvi_strategy>();
			}
            else if (port == 8000)
			{
			 	print_port_state(PORT_OPEN, port, "HIKVISION");
			 	ports_strategy_ = std::make_unique<hikvision_strategy>();
            }
            else if (port == 443)
			{
			 	print_port_state(PORT_OPEN, port, "HTTPS");
				ports_strategy_ = std::make_unique<https_strategy>();
            }else if (port == 25)
			{
			 	print_port_state(PORT_OPEN, port, "SMTP");
				ports_strategy_ = std::make_unique<smtp_strategy>();
		  	}
            else
			{
			 	print_port_state(PORT_OPEN, port, sn.probe_service(port));
				ports_strategy_ = std::make_unique<else_strategy>();
            }

			/*Запуск стратегий.*/
			if (ports_strategy_){ports_strategy_->handle(ip, result1, rtt_log, protocol, port, argp, np);}
        }

		/*Ошибочный порт.*/
        else if (result == EOF)
		{
            if (argp.print_errors){print_port_state(PORT_ERROR, port, sn.probe_service(port));}
        }
		/*Закрытый порт.*/
        else if (result == 1)
		{
            if (argp.debug){print_port_state(PORT_CLOSED, port, sn.probe_service(port));}
        }
		/*Фильтруемый порт.*/
        else if (result == 2)
		{
            if (argp.debug){print_port_state(PORT_FILTER, port, sn.probe_service(port));}
        }
		/*Открыт или фильтруеться.*/
        else if (result == 3)
		{
			print_port_state(PORT_OPEN_OR_FILTER, port, sn.probe_service(port));
        }
		/*Не фильтруеться.*/
        else if (result == 4)
		{
			print_port_state(PORT_NO_FILTER, port, sn.probe_service(port));
        }
}
// You live?

void 
help_menu(void)
{
    logo();
    np.golder_rod_on();
    std::cout << "usage: " << run << " [target 1,2,3] [flags]\n";
    np.reset_colors();

    np.sea_green_on();
    std::cout << "\nTARGET:" << std::endl;
    np.reset_colors();
    std::cout << "  -import-ip <path>: Set ip on target from file.\n";
    std::cout << "  -import-cidr <path>: Set cidr on target from file.\n";
    std::cout << "  -import-range <path>: Set range on target from file.\n";
    std::cout << "  -random-ip <count>: Set random ip target.\n";

    np.sea_green_on();
    std::cout << "SPEED:" << std::endl;
    np.reset_colors();
    std::cout << "  -speed, -S <1-5>: Edit preset speed.\n";
    std::cout << "  -my-life-my-rulez: Using very MAX speed settings.\n";

    np.sea_green_on();
    std::cout << "PORT SCAN METHODS:" << std::endl;
    np.reset_colors();
    std::cout << "  -fin, -xmas, -null: Use one of these scanning methods.\n";
    std::cout << "  -ack, -windows -maimon: Use ack or window or maimon scan method.\n";

    np.sea_green_on();
    std::cout << "SAVING TO FILE:" << std::endl;
    np.reset_colors();
    std::cout << "  -html, -l <path>: Classic nesca save, write on html page.\n";
    std::cout << "  -txt <path>: Save result to text document.\n";

    np.sea_green_on();
    std::cout << "PORT SCAN:" << std::endl;
    np.reset_colors();
    std::cout << "  -delay, -d <ms>: Set delay for scan.\n";
    std::cout << "  -ports, -p <1,2,3>: Set ports on scan.\n";
    std::cout << "  -packet-trace: Display packet_trace on port scan.\n";

    np.sea_green_on();
    std::cout << "PORT SCAN SPEED:" << std::endl;
    np.reset_colors();
    std::cout << "  -max-group <count>: Edit max size group & threads for port scan.\n";
    std::cout << "  -min-group <count>: Edit min size group & threads for port scan.\n";
    std::cout << "  -rate-group <count: Edit the value by which the group is incremented.\n";
    std::cout << "  -scan-timeout <ms>: Edit timeout for getting packet on port.\n";

    np.sea_green_on();
    std::cout << "DNS RESOLUTION:" << std::endl;
    np.reset_colors();
    std::cout << "  -TD <count>: Set max threads for dns-resolution.\n";
    std::cout << "  -resol-port <port>: Edit source port for dns-resolution.\n";
    std::cout << "  -resol-delay <ms>: Set delay for dns-resolution.\n";
    std::cout << "  -no-resolv: Skip dns-resolution.\n";

    np.sea_green_on();
    std::cout << "PING SCAN:" << std::endl;
    np.reset_colors();
    std::cout << "  -PS, -PA <port>: On TCP ping SYN|ACK and edit dest port.\n";
    std::cout << "  -PE, -PI, -PM: On ICMP ping ECHO|INFO|TIMESTAMP\n";
    std::cout << "  -max-ping: Using all ping methods ICMP and TCP.\n";
    std::cout << "  -no-ping: Off ping scan.\n";

    np.sea_green_on();
    std::cout << "PING SPEED:" << std::endl;
    np.reset_colors();
    std::cout << "  -TP <count>: Set max threads for ping.\n";
    std::cout << "  -ping-timeout <ms>: Set recv timeout for ping.\n";

    np.sea_green_on();
    std::cout << "BRUTEFORCE:" << std::endl;
    np.reset_colors();
    std::cout << "  -brute-login <ss,path>: Set path for <ss> logins.\n";
    std::cout << "  -brute-pass <ss,path>: Set path for <ss> passwords.\n";
    std::cout << "  -brute-timeout <ms>: Edit brute timout.\n";
    std::cout << "  -brute-only <ss,2>: Display only success <ss> bruteforce.\n";
    std::cout << "  -no-brute <ss,2>: Disable <ss> bruteforce.\n";

    np.sea_green_on();
    std::cout << "OTHER BRUTEFORCE:" << std::endl;
    np.reset_colors();
    std::cout << "  -brute-verbose <ss,2>: Display bruteforce <ss> all info.\n";
    std::cout << "  -brute-log <ss,2>: Display bruteforce <ss> info.\n";
    std::cout << "  -sftp-brute-known-hosts: Reading known_host for connection.\n";

    np.sea_green_on();
    std::cout << "ARGUMENTS DNS SCAN:" << std::endl;
    np.reset_colors();
    std::cout << "  -dns-scan <.dns>: On dns-scan and set domain 1 level.\n";
    std::cout << "  -T, -threads <count>: Edit threads count.\n";
    std::cout << "  -dns-length <count>: Edit length generating domain.\n";
    std::cout << "  -dns-dict <dict>: Edit dictionary for generation.\n";

    np.sea_green_on();
    std::cout << "ARGUMENTS OUTPUT:" << std::endl;
    np.reset_colors();
    std::cout << "  -pro: On pro mode, display more info.\n";
    std::cout << "  -db, -debug: On debug mode, save and display not even working hosts.\n";
    std::cout << "  -er, -error: On display errors.\n";
    std::cout << "  -no-proc: Only scan.\n";
    std::cout << "  -no-get-path: Disable getting paths.\n";
    std::cout << "  -log-set <count>: Change change the value of ips after which, will be displayed information about how much is left.\n";
    std::cout << "  -http-response: Display HTTP response.\n";

    np.sea_green_on();
    std::cout << "ARGUMENTS COLORS:" << std::endl;
    np.reset_colors();
    std::cout << "  -no-color: Disable colors.\n";
    std::cout << "  -import-color <path>: Import color scheme from file.\n";

    np.sea_green_on();
    std::cout << "ARGUMENTS OTHER:" << std::endl;
    np.reset_colors();
    std::cout << "  -negatives <path>: Set custom path for negatives.\n";
    std::cout << "  -source-ip <ip>: Set custom source_ip.\n";
    std::cout << "  -source-port <port>: Set custom source_port.\n";
    std::cout << "  -ttl <count>: Set custom ip_header_ttl.\n";
}

void 
parse_args(int argc, char** argv)
{
    int rez;
    int option_index = 0;

    while ((rez = getopt_long_only(argc, argv, short_options, long_options, &option_index)) != EOF)
	{
        switch (rez) 
		{
            case 'h':
                argp.print_help_menu = true;
                break;
            case 'v':
			 argp.info_version = true;
                break;
            case 'S':
				argp.speed_type = atoi(optarg);
                break;
            case 'p':
            {
                argp.ports_temp = optarg;
                argp.ports = write_ports(argp.ports_temp);
                if (argp.ports[0] == EOF)
				{
                    size_t pos = argp.ports_temp.find(",");
                    size_t pos1 = argp.ports_temp.find("-");

                    if (pos1 != std::string::npos)
					{
                        argp.ports = parse_range(optarg);
                    }
                    else 
					{
                        argp.ports = split_string_int(optarg, ',');
                    }
                }
                break;
            }
            case 3:
            {
               argp.ip_cidr_scan_import = true;
               argp.path_cidr = optarg;
               break;
            }
           case 12:
           {
               std::vector<std::string> what = split_string_string(optarg, ',');
			   what[0] = to_lower_case(what[0]);
			   what[1] = to_lower_case(what[1]);

               const char* what_convert = what[0].c_str();
               if (what[1] == "ftp")
			   {
                    argp.path_ftp_login = what_convert;
               }
               else if (what[1] == "sftp")
			   {
                   argp.path_sftp_login = what_convert;
               }
               else if (what[1] == "rtsp")
			   {
                   argp.path_rtsp_login = what_convert;
               }
               else if (what[1] == "http")
			   {
                   argp.path_http_login = what_convert;
               }
               else if (what[1] == "smtp")
			   {
			       argp.path_smtp_login = what_convert;
               }
               else if (what[1] == "hikvision")
			   {
                   argp.path_hikvision_login = what_convert;
               }
               else if (what[1] == "rvi")
			   {
                   argp.path_rvi_login = what_convert;
               }
               else if (what[1] == "all")
			   {
                   argp.path_rvi_login = what_convert;
                   argp.path_sftp_login = what_convert;
                   argp.path_ftp_login = what_convert;
                   argp.path_http_login = what_convert;
                   argp.path_rtsp_login = what_convert;
			       argp.path_smtp_login = what_convert;
                   argp.path_hikvision_login = what_convert;
               }

               break;
           }
           case 11:
           {
               std::vector<std::string> what = split_string_string(optarg, ',');
			   what[0] = to_lower_case(what[0]);
			   what[1] = to_lower_case(what[1]);

               const char* what_convert = what[0].c_str();
               if (what[1] == "ftp")
			   {
                    argp.path_ftp_pass = what_convert;
               }
               else if (what[1] == "sftp")
			   {
                   argp.path_sftp_pass = what_convert;
               }
               else if (what[1] == "rtsp")
			   {
                   argp.path_rtsp_pass = what_convert;
               }
               else if (what[1] == "http")
			   {
                   argp.path_http_pass = what_convert;
               }
               else if (what[1] == "smtp")
			   {
			       argp.path_smtp_pass = what_convert;
               }
               else if (what[1] == "hikvision")
			   {
                   argp.path_hikvision_pass = what_convert;
               }
               else if (what[1] == "rvi")
			   {
                   argp.path_rvi_pass = what_convert;
               }
               else if (what[1] == "all")
			   {
                   argp.path_sftp_pass = what_convert;
                   argp.path_rvi_pass = what_convert;
                   argp.path_ftp_pass = what_convert;
			       argp.path_smtp_pass = what_convert;
                   argp.path_rtsp_pass = what_convert;
                   argp.path_http_pass = what_convert;
                   argp.path_hikvision_pass = what_convert;
               }
               break;
           }
           case 30:
           {
               std::vector<std::string> what = split_string_string(optarg, ',');
                for (int i = 0; i < what.size(); i++)
				{
			   		what[i] = to_lower_case(what[i]);
                    if (what[i] == "ftp")
					{
                        argp.ftp_brute_log = true;
                    }
                    else if (what[i] == "sftp")
					{
                        argp.sftp_brute_log = true;
                    }
                    else if (what[i] == "rtsp")
					{
                        argp.rtsp_brute_log = true;
                    }
                    else if (what[i] == "http")
					{
                        argp.http_brute_log = true;
                    }
                    else if (what[i] == "hikvision")
					{
                        argp.hikvision_brute_log = true;
                    }
                    else if (what[i] == "smtp")
					{
				    	argp.smtp_brute_log = true;
                    }else if (what[i] == "rvi")
					{
                   		argp.rvi_brute_log = true;
               		}
                    else if (what[i] == "all")
					{
                        argp.ftp_brute_log = true;
				    	argp.smtp_brute_log = true;
                   		argp.rvi_brute_log = true;
                        argp.sftp_brute_log = true;
                        argp.rtsp_brute_log = true;
                        argp.http_brute_log = true;
                        argp.hikvision_brute_log = true;
                    }
                    else {
                        break;
                    }
                }

                break;
           }
           case 31:
           {
                std::vector<std::string> what = split_string_string(optarg, ',');
                for (int i = 0; i < what.size(); i++)
				{
			   		what[i] = to_lower_case(what[i]);
                    if (what[i] == "ftp")
					{
                        argp.ftp_brute_verbose = true;
                    }
                    else if (what[i] == "sftp")
					{
                        argp.sftp_brute_verbose = true;
                    }
                    else if (what[i] == "rtsp")
					{
                        argp.rtsp_brute_verbose = true;
                    }
                    else if (what[i] == "http")
					{
                        argp.http_brute_verbose = true;
                    }
                    else if (what[i] == "smtp")
					{
				    	argp.smtp_brute_verbose = true;
                    }
                    else if (what[i] == "all")
					{
                        argp.ftp_brute_verbose = true;
                        argp.sftp_brute_verbose = true;
				    	argp.smtp_brute_verbose = true;
                        argp.rtsp_brute_verbose = true;
                        argp.http_brute_verbose = true;
                    }
                }

               break;
           }
           case 44:
           {
               std::vector<std::string> what = split_string_string(optarg, ',');

               for (int i = 0; i < what.size(); i++)
			   {
			   	   what[i] = to_lower_case(what[i]);
                   if (what[i] == "ftp")
				   {
                       argp.off_ftp_brute = true;
                   }
                   else if (what[i] == "sftp")
				   {
                       argp.off_sftp_brute = true;
                   }
                   else if (what[i] == "rtsp")
				   {
                       argp.off_rtsp_brute = true;
                   }
                   else if (what[i] == "http")
				   {
                       argp.off_http_brute = true;
                   }
                   else if (what[i] == "hikvision")
				   {
                       argp.off_hikvision_brute = true;
                   }
                   else if (what[i] == "smtp")
				   {
				   	   argp.off_smtp_brute = true;
                   }
               	   else if (what[i] == "rvi")
				   {
					   argp.off_rvi_brute = true;
               	   }
                   else if (what[i] == "all")
				   {
                       argp.off_ftp_brute = true;
                       argp.off_sftp_brute = true;
					   argp.off_rvi_brute = true;
				   	   argp.off_smtp_brute = true;
                       argp.off_rtsp_brute = true;
                       argp.off_http_brute = true;
                       argp.off_hikvision_brute = true;
                   }
               }

               break;
           }
           case 46:
           {
               std::vector<std::string> what = split_string_string(optarg, ',');
               for (int i = 0; i < what.size(); i++)
			   {
			   	   what[i] = to_lower_case(what[i]);
                   if (what[i] == "ftp")
				   {
                       argp.ftp_only = true;
                   }
                   else if (what[i] == "sftp")
				   {
                       argp.sftp_only = true;
                   }
                   else if (what[i] == "rtsp")
				   {
                       argp.rtsp_only = true;
                   }
                   else if (what[i] == "http")
				   {
                       argp.http_only = true;
                   }
                   else if (what[i] == "hikvision")
				   {
                       argp.hikvision_only = true;
                   }
                   else if (what[i] == "smtp")
				   {
				       argp.smtp_only = true;
                   }
                   else if (what[i] == "rvi")
				   {
				       argp.rvi_only = true;
                   }
                   else if (what[i] == "all")
				   {
                       argp.sftp_only = true;
				       argp.rvi_only = true;
                       argp.ftp_only = true;
				   	   argp.smtp_only = true;
                       argp.rtsp_only = true;
                       argp.http_only = true;
                       argp.hikvision_only = true;
                   }
               }

               break;
           }
           case 47:
               argp.brute_timeout_ms = atoi(optarg);
               break;
           case 48:
               argp.thread_on_port = true;
               break;
           case 32:
               argp.ip_range_scan_import = true;
               argp.path_range = optarg;
               break;
           case 5:
                argp.random_ip = true;
                argp.random_ip_count = atoi(optarg); 
                break;
           case 7:
                argp.debug = true;
                break;
           case 45:
                argp.sftp_using_know_hosts = true;
                break;
          case 'd':
                argp.timeout = true;
                argp.timeout_ms = atoi(optarg);
                break;
          case 'T':
				argp._threads_dns = atoi(optarg);
                break;
           case 19:
                argp.dns_scan = true;
                argp.domain_1level = optarg;
                break;
           case 20:
                argp.dns_scan = true;
                argp.dns_scan_domain_count = atoi(optarg);
                break;
           case 21:
                argp.dns_dictionary = optarg;
                break;
           case 22:
                np.save_file = true;
                np.file_path_save = optarg;
                break;
           case 23:
           {
               argp.ip_scan_import = true;
               argp.path_ips = optarg;
               break;
           }
           case 24:
		   	  argp.custom_log_set = true;
              argp.log_set = atoi(optarg);
              break;
           case 25:
              argp.print_errors = true;
              break;
           case 26:
           {
               np.disable_colors();
               break;
           }
           case 27:
               argp.debug = true;
               break;
           case 28:
               argp.print_errors = true;
               break;
           case 29:
               argp.ping_off = true;
               break;
           case 34:
			   argp.source_ip = optarg;
               break;
           case 36:
			   argp.custom_source_port = true;
			   argp._custom_source_port = atoi(optarg);
               break;
           case 37:
			   argp.custom_ttl = true;
			   argp._custom_ttl = atoi(optarg);
               break;


           case 38:
			   argp.custom_g_max = true;
			   argp.group_size_max = atoi(optarg);
               break;
           case 60:
			   argp.custom_g_min = true;
			   argp.group_size = atoi(optarg);
               break;
           case 61:
			   argp.custom_g_rate = true;
			   argp.group_rate = atoi(optarg);
               break;


           case 49:
			   argp.ping_timeout = atoi(optarg);
               break;
           case 33:
			   argp.resol_source_port = atoi(optarg);
               break;
           case 40:
			   argp.resol_delay = atoi(optarg);
               break;
           case 50:
               argp.no_get_path = true;
               break;
           case 51:
               argp.get_response = true;
               break;
           case 52:
			   argp.custom_threads_resolv = true;
			   argp.dns_threads = atoi(optarg);
               break;
           case 53:
			   argp.my_life_my_rulez = true;
			   argp.speed_type = 0;
               break;
           case 54:
               argp.import_color_scheme = true;
               argp.path_color_scheme = optarg;
               break;
           case 'l':
			   np.html_save = true;
			   np.html_file_path = std::string(optarg) + ".html";
               break;
           case 57:
			   argp.custom_threads = true;
			   argp.threads_ping = atoi(optarg);
               break;
           case 56:
               break;
           case 59:
			   argp.no_get_dns = true;
               break;
           case 76:
			   argp.negatives_path = std::string(optarg);
               break;
		  /*Пинг аргументы влкючения.*/
	      case 80:
			 argp.custom_ping = true;
			 argp.syn_ping = true;
			 argp.syn_dest_port = atoi(optarg);
		     break;
	      case 81:
			 argp.custom_ping = true;
			 argp.ack_ping = true;
			 argp.ack_dest_port = atoi(optarg);
		     break;
	      case 78:
			 argp.pro_mode = true;
		     break;
	      case 82:
			 argp.custom_ping = true;
			 argp.echo_ping = true;
		     break;
	      case 86:
			 argp.custom_ping = true;
			 argp.info_ping = true;
		     break;
	      case 87:
			 argp.custom_ping = true;
			 argp.timestamp_ping= true;
		     break;
	      case 88:
			 argp.max_ping = true;
		     break;

	      case 89:
			 argp.ack_scan = true;
			 argp.type = ACK_SCAN;
		     break;
	      case 90:
			argp.ping_log = atoi(optarg);
		     break;
	      case 91:
			argp.null_scan = true;
			argp.type = NULL_SCAN;
			break;
	      case 92:
			argp.fin_scan = true;
			argp.type = FIN_SCAN;
			break;
	      case 93:
			argp.xmas_scan = true;
			argp.type = XMAS_SCAN;
			break;
	      case 94:
			argp.window_scan = true;
			argp.type = WINDOW_SCAN;
			break;
	      case 95:
			argp.no_proc = true;
			break;
	      case 96:
			argp.packet_trace = true;
			break;
	      case 97:
			argp.maimon_scan = true;
			argp.type = MAIMON_SCAN;
			break;
	      case 101:
			argp.custom_recv_timeout_ms = true;
			argp.recv_timeout_ms = atoi(optarg);
			break;
        }
    }
}
void
init_bruteforce(void)
{
    argp.ftp_logins          = write_file(argp.path_ftp_login);
    argp.ftp_passwords       = write_file(argp.path_ftp_pass);
    argp.sftp_logins         = write_file(argp.path_sftp_login);
    argp.sftp_passwords      = write_file(argp.path_sftp_pass);
    argp.rtsp_logins         = write_file(argp.path_rtsp_login);
    argp.rtsp_passwords      = write_file(argp.path_rtsp_pass);
    argp.http_logins         = write_file(argp.path_http_login);
    argp.http_passwords      = write_file(argp.path_http_pass);
    argp.hikvision_logins    = write_file(argp.path_hikvision_login);
    argp.hikvision_passwords = write_file(argp.path_hikvision_pass);
    argp.smtp_logins         = write_file(argp.path_smtp_login);
    argp.smtp_passwords      = write_file(argp.path_smtp_pass);
    argp.rvi_logins          = write_file(argp.path_rvi_login);
    argp.rvi_passwords       = write_file(argp.path_rvi_pass);
}

std::string 
format_percentage(double procents)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << procents << "%";
    std::string result = oss.str();
    return result;
}

void /*Для DNS_RESOLV*/
get_dns_thread(std::string ip)
{
	delay_ms(argp.resol_delay);
	std::string temp_dns = dus.get_dns_by_ip(ip.c_str(), argp.resol_source_port);
	ls.lock(); /*Добавление DNS.*/
	argp.dns_completed.insert(std::make_pair(ip, temp_dns));
	ls.unlock();
}

void
pre_check(void)
{
    if (check_ansi_support() != true)
	{
        std::cout << "You terminal don`t support ansi colors!\n";
        std::cout << "Colors disable!\n\n";
        np.disable_colors();
    }

	np.golder_rod_on();
	std::cout << "-> Running NESCA [v" + std::string(VERSION) + "] # " +
		std::string(get_time()) + " at " + get_current_date() << std::endl; 
	np.reset_colors();

    if (argp.info_version) {version_menu();}

	if (np.html_save)
	{
		std::vector<std::string> temp = write_file("resources/data");
		auto it = std::find(temp.begin(), temp.end(), np.html_file_path);
		if (it == temp.end() || temp[0] == "-1")
		{
			ho.html_main_init(np.html_file_path);
		}
		else {
			if (!check_file(np.html_file_path.c_str()))
			{
				ho.html_main_init(np.html_file_path);
			}
		}

		ho.html_pre_init(np.html_file_path);
		write_temp(np.html_file_path);
	}

    if (np.save_file)
	{
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm* tm = std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(tm, "%d.%m.%Y");
        std::string date_str = oss.str();
        write_line(np.file_path_save, "\n\n\t\tNESCA4:[" + date_str + "]:[" + get_time() + "]\n\n");}


    if (argp.import_color_scheme)
	{
        np.import_color_scheme(argp.path_color_scheme, np.config_values);
        np.processing_color_scheme(np.config_values);
		if (argp.pro_mode)
		{
	    	std::cout << np.main_nesca_out("NESCA4", "COLORSCHEME_DATA", 5, "STATE", "", "OK","","") << std::endl;
		}
    }


    if (!check_file("./resources/nesca-services")){std::cout << np.main_nesca_out("NESCA4", "SERVICES_DATA", 5, "status", "", "FAILED","","") << std::endl;}
    else 
	{
	   sn.init_services();
	   if (argp.pro_mode)
	   {
	       std::cout << np.main_nesca_out("NESCA4", "SERVICES_DATA", 5, "status", "", "OK","","") << std::endl;
	   }
    }

	if (!check_file(argp.negatives_path.c_str())){std::cout << np.main_nesca_out("NESCA4", "NEGATIVES_LOAD", 5, "status", "", "FAILED","","") << std::endl;}
	else
	{
	   nn.nesca_negatives = nn.parse_config_file(argp.negatives_path);
	   std::size_t num_first_values = nn.nesca_negatives.size();
		if (argp.pro_mode)
		{
	   		std::cout << np.main_nesca_out("NESCA4", "NEGATIVES_LOAD", 5, "status", "count", "OK", std::to_string(num_first_values),"") << std::endl;
		}
	}

    if (argp.print_help_menu){help_menu();exit(0);}
    if (!check_root_perms()){np.nlog_error("RAW socket only sudo run!\n");exit(1);}
}

void
version_menu(void)
{
	logo();
	np.gray_nesca_on();
	std::cout << np.print_get_time(get_time());
	std::cout << "[VERSION]:";
	np.green_html_on();
	std::cout << VERSION << std::endl;
	np.gray_nesca_on();
	std::cout << np.print_get_time(get_time());
	std::cout << "[INFO]:";
	np.sea_green_on();
	std::cout << "https://github.com/oldteamhost/nesca4" << std::endl;
	np.reset_colors();
	np.gray_nesca_on();
	std::cout << np.print_get_time(get_time());
	std::cout << "[NB]:";
	np.golder_rod_on();
	std::cout << "Don`t read \"do_not_read.txt\"" << std::endl;
	np.reset_colors();
	std::cout << std::endl;
	exit(0);
}
