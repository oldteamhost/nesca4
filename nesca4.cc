/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <future>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <iomanip>
#include <mutex>
#include <algorithm> 
#include <random>
#include <string>
#include <future>
#include <sstream>
#include <vector>
#include <set>

#include "include/bruteforce.h"
#include "include/getopt.h"
#include "include/callbacks.h"
#include "include/files.h"
#include "include/generation.h"
#include "include/other.h"
#include "include/scanner.h"
#include "include/target.h"
#include "include/html.h"
#include "include/nescalog.h"
#include "include/portscan.h"
#include "include/netutils.h"
#include "include/services.h"

#include "modules/include/requests.h"
#include "modules/include/title.h"
#include "modules/include/redirect.h"
#include "modules/include/ftpinfo.h"
#include "modules/include/smtpinfo.h"

#include "config/nescaopts.h"
#include "ncping/include/icmpping.h"
#include "ncping/include/ackping.h"
#include "ncping/include/synping.h"
#include "ncsock/include/ncread.h"

/*Угадайте?*/
#define VERSION "20230705"

/*Классы, структуры.*/
std::mutex mtx;
std::mutex ls;
checking_finds cfs;
nesca_prints np;
brute_ftp_data bfd_;
html_output ho;
ip_utils _iu;
dns_utils dus;
services_nesca sn;
arguments_program argp;
struct nesca_scan_opts ncopts;

void 
help_menu(void);
void
init_bruteforce(void);
void 
processing_tcp_scan_ports(std::string ip, int port, int result);
std::string 
format_percentage(double procents);
void 
check_files(const char* path, const char* path1);
int
scan_port(const char* ip, std::vector<int>ports, const int timeout_ms);
void 
checking_default_files(void);
bool
process_ping(std::string ip);
void 
parse_args(int argc, char** argv);
void
pre_check(void);
void
print_results(std::string ip);
void
get_dns_thread(std::string ip);

/*Аргументы.*/
const struct 
option long_options[] = {
    {"threads", required_argument, 0, 'T'},
    {"delay", required_argument, 0, 'd'},
    {"import-ip", required_argument, 0, 23},
    {"import-cidr", required_argument, 0, 3},
    {"import-range", required_argument, 0, 32},
    {"random-ip", required_argument, 0, 5},
    {"brute-login", required_argument, 0, 12},
    {"brute-pass", required_argument, 0, 11},
    {"ping-log", required_argument, 0, 90},
    {"my-life-my-rulez", no_argument, 0, 53},
    {"brute-log", required_argument, 0, 30},
    {"brute-verbose", required_argument, 0, 31},
    {"thread-on-port", no_argument, 0, 48},
    {"no-brute", required_argument, 0, 44},
    {"brute-only", required_argument, 0, 46},
    {"brute-timeout", required_argument, 0, 47},
    {"sftp-brute-known-hosts", no_argument, 0, 45},
    {"dns-scan", required_argument, 0, 19},
    {"dns-length", required_argument, 0, 20},
    {"dns-dict", required_argument, 0, 21},
    {"txt", required_argument, 0, 22},
    {"TP", required_argument, 0, 57},
    {"debug", no_argument, 0, 27},
    {"er", no_argument, 0, 28},
    {"no-get-path", no_argument, 0, 50},
    {"import-color", required_argument, 0, 54},
    {"null", no_argument, 0, 91},
    {"fin", no_argument, 0, 92},
    {"xmas", no_argument, 0, 93},
    {"on-http-response", no_argument, 0, 51},
    {"scan-timeout", required_argument, 0, 101},
    {"no-ping", no_argument, 0, 29},
    {"no-proc", no_argument, 0, 95},
    {"no-color", no_argument, 0, 26},
    {"log-set", required_argument, 0, 24},
    {"packet-trace", no_argument, 0, 96},
    {"scan-db", no_argument, 0, 59},
    {"scan-debug", no_argument, 0, 60},
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'v'},
    {"ports", no_argument, 0, 'p'},
    {"db", no_argument, 0, 7},
    {"error", no_argument, 0, 25},
    {"html", required_argument, 0, 'l'},
    {"TD", required_argument, 0, 52},
    {"PS", required_argument, 0, 80},
    {"PA", required_argument, 0, 81},
    {"PE", no_argument, 0, 82},
    {"PI", no_argument, 0, 86},
    {"PM", no_argument, 0, 87},
    {"source-port", required_argument, 0, 36},
    {"ttl", required_argument, 0, 37},
    {"max-group", required_argument, 0, 38},
    {"max-ping", no_argument, 0, 88},
    {"source-ip", required_argument, 0, 34},
    {"ack", no_argument, 0, 89},
    {"window", no_argument, 0, 94},
    {"maimon", no_argument, 0, 97},
    {"resol-delay", required_argument, 0, 40},
    {"speed", required_argument, 0, 'S'},
    {"resol-port", required_argument, 0, 33},
    {"ping-timeout", required_argument, 0, 49},
    {0,0,0,0}
}; const char* short_options = "hl:vd:T:p:aS:";
const char* run; /*Для help_menu()*/

void
pre_check(void){
    logo();

	if (np.html_save){
		std::vector<std::string> temp = write_file("resources/data");
		auto it = std::find(temp.begin(), temp.end(), np.html_file_path);
		if (it == temp.end() || temp[0] == "-1"){
			ho.html_main_init(np.html_file_path);
		}
		else {if (!check_file(np.html_file_path.c_str())){
			ho.html_main_init(np.html_file_path);
		}}

		ho.html_pre_init(np.html_file_path);
		write_temp(np.html_file_path);
	}

    if (np.save_file){
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm* tm = std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(tm, "%d.%m.%Y");
        std::string date_str = oss.str();
        write_line(np.file_path_save, "\n\n\t\tNESCA4:[" + date_str + "]:[" + get_time() + "]\n\n");}


    if (argp.import_color_scheme){
        np.import_color_scheme(argp.path_color_scheme, np.config_values);
        np.processing_color_scheme(np.config_values);
	    std::cout << np.main_nesca_out("NESCA4", "COLORSCHEME_DATA", 5, "STATE", "", "OK","","") << std::endl;
    }

    if (argp.info_version){
	   np.gray_nesca_on();
	   std::cout << np.print_get_time(get_time());
	   std::cout << "[VERSION]:";
	   np.golder_rod_on();
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

    if (!check_file("./resources/nesca-services")){std::cout << np.main_nesca_out("NESCA4", "SERVICES_DATA", 5, "status", "", "FAILED","","") << std::endl;}
    else {
	   sn.init_services();
	   std::cout << np.main_nesca_out("NESCA4", "SERVICES_DATA", 5, "status", "", "OK","","") << std::endl;
    }

    if (check_ansi_support() != true){
        std::cout << "You terminal don`t support ansi colors!\n";
        std::cout << "Colors disable!\n";
        np.disable_colors();
    }

    if (argp.print_help_menu){help_menu();exit(0);}
    if (!check_root_perms()){np.nlog_error("RAW socket only sudo run!\n");exit(1);}

}

int main(int argc, char** argv){
    run = argv[0];
    if (argc <= 1){help_menu();return 1;}
    parse_args(argc, argv);

    /*Предупреждение о потоках*/
    if (argp.warning_threads){
        char what;
        np.nlog_custom("WARNING","You set "+ std::to_string(argp.threads_temp) + 
                " threads this can severely overload a weak cpu, are you sure you want to continue (y,n): ", 2);
        std::cin >> what;
        std::cout << std::endl;

        if (what != 'y'){
            return 0;
        }
        else {
            argp._threads = argp.threads_temp;
        }
    }
    pre_check();

	/*Получение IP компютера.*/
	if (!argp.custom_source_ip){argp.source_ip = _iu.get_local_ip();}
 
    if (optind < argc){
        size_t cidr = std::string(argv[optind]).find("/");
        size_t range = std::string(argv[optind]).find("-");

        if (cidr != std::string::npos){
            argp.ip_cidr_scan = true;
            argp.ip_cidr = split_string_string(argv[optind], ',');
        }
        else if (range != std::string::npos){
            argp.ip_range_scan = true;
            argp.ip_range = split_string_string(argv[optind], ',');
        }
        else {
            argp.dns = split_string_string(argv[optind], ',');        
            if (dns_or_ip(argp.dns[0])){
                argp.ip_scan = true;
                argp._ip = convert_dns_to_ip(argp.dns);
            }
            else {
                argp.ip_scan = true;
                argp._ip = split_string_string(argv[optind], ',');
            }
        }
    }
    checking_default_files();
    std::cout << std::endl;

    /*Начало DNS сканирования.*/
    if (argp.dns_scan){
        argp.timeout_ms = 100;
        std::mutex mtx;
	   std::cout << np.main_nesca_out("NESCA4", "Starting "+std::to_string(argp._threads)+" threads...", 5, "on", "", "DNS","","") << std::endl << std::endl;
        for (int i = 0; i < argp._threads; i++) {

            std::thread([&](){
                for (;;) {
                    std::string random_ = generate_random_str(argp.dns_scan_domain_count, argp.dns_dictionary);
                    std::string result = random_ + argp.domain_1level;
                    std::string ip = dus.get_ip_by_dns(result.c_str());
					if (ip == "N/A"){
				    	if (argp.debug){np.nlog_custom("BA", result + " [FaILEd]\n",2);}
						continue;
					}
					if (ip == "-1"){
				    	if (argp.debug){np.nlog_custom("BA", result + " [FaILEd]\n",2);}
				    	continue;
					}
                	std::string result_print;
					int ping = process_ping(ip.c_str());
                	std::string html = send_http_request(ip, 80);
                	if (ping == -1) {
                    	if (argp.debug){std::lock_guard<std::mutex> lock(mtx);np.nlog_custom("BA", result + " [FaILEd]\n",2);}
                	}
                	else {
                    	std::lock_guard<std::mutex> lock(mtx);
                    	std::cout << np.main_nesca_out("BA", "http://" + result, 3, "T", "", get_http_title(html), "","") << std::endl;
                	}
            	}
        	}).detach();

            if (argp.timeout){
                delay_ms(argp.timeout_ms);
            }
        }
        std::getchar();
        std::cout << np.main_nesca_out("NN", "Stoping threads...", 0, "", "", "", "","") << std::endl;
    }

    /*Тут начинаеться само сканирование, брутфорс и всё остальное.
	* nesca 4*/
    init_bruteforce();
    std::vector<std::string> result;
  
    /*Установка цели из аргумента.*/
    if (argp.ip_scan_import || argp.ip_scan){
        result = argp._ip;
    } 
    else if (argp.ip_range_scan || argp.ip_range_scan_import){
        std::vector<std::string> range_convert = range_to_ips(argp.ip_range);
        result = range_convert;
    }
    else if (argp.ip_cidr_scan_import || argp.ip_cidr_scan){
        std::vector<std::string> cidr_convert = cidr_to_ips(argp.ip_cidr);
        result = cidr_convert;
    }
    else if (argp.random_ip){
        argp.ip_scan = true;
        for (int i = 0; i < argp.random_ip_count; i++){
            std::string random_temp = generate_ipv4();
            result.push_back(random_temp);
        }
    }

    std::vector<std::string> result_main; // ip для сканирования
    int ip_count = 0;
    int flag_desing = 0;

	if (!argp.custom_threads){
		if (argp.my_life_my_rulez){argp.threads_ping = result.size(); argp.ping_timeout = 250;}
		if (argp.speed_type == 5){
			argp.ping_timeout = 400;
			if (result.size() >= 2000){argp.threads_ping = 2000;}
			else{argp.threads_ping = result.size();}
		}
		else if (argp.speed_type == 4){
			argp.ping_timeout = 600;
			if (result.size() >= 1500){argp.threads_ping = 1500;}
			else{argp.threads_ping = result.size();}
		}
		else if (argp.speed_type == 3){
			argp.ping_timeout = 1000;
			if (result.size() >= 1000){argp.threads_ping = 1000;}
			else{argp.threads_ping = result.size();}
		}
		else if (argp.speed_type == 2){
			argp.ping_timeout = 2000;
			if (result.size() >= 500){argp.threads_ping = 500;}
			else{argp.threads_ping = result.size();}
		}
		else if (argp.speed_type == 1){
			argp.ping_timeout = 3000;
			if (result.size() >= 100){argp.threads_ping = 100;}
			else{argp.threads_ping = result.size();}
		}
	}
	if (argp.max_ping || argp.speed_type == 1){
		argp.syn_ping = true;
		argp.ack_ping = true;
		argp.echo_ping = true;
		argp.info_ping = true;
		argp.timestamp_ping = true;
	}
	if (argp.speed_type == 5){argp.ack_ping = true;}
	else if (argp.speed_type == 4){argp.echo_ping = true;argp.ack_ping = true;}
	else if (argp.speed_type == 2 || argp.speed_type == 3){
		argp.ack_ping = true;
		argp.syn_ping = true;
		argp.echo_ping = true;
		argp.info_ping = true;
	}

	if (!argp.syn_ping && !argp.ack_ping && !argp.echo_ping && !argp.info_ping && !argp.timestamp_ping){argp.ack_ping = true;argp.echo_ping = true;}

    /*Пинг сканирования*/
    if (!argp.ping_off) {
		char ch;
		std::cout << np.main_nesca_out("NESCA4", "PING_SCAN", 5, "recv-timeout", "threads", std::to_string(argp.ping_timeout), std::to_string(argp.threads_ping),"") << std::endl;
    	int threads_ping = argp.threads_ping;
    	int ips_per_thread = result.size() / threads_ping;
    	int ip_count_ping = 0;
    	std::vector<std::future<std::pair<bool, std::string>>> futures;
    	auto result_iter = result.begin();

    	while (result_iter != result.end()) {
        	int remaining_tasks = std::distance(result_iter, result.end());
        	int tasks_to_execute = std::min(threads_ping, remaining_tasks);

        	for (int i = 0; i < tasks_to_execute; ++i) {
            	std::string ip = *result_iter;
            	futures.push_back(std::async(std::launch::async, [ip]() -> std::pair<bool, std::string> {
                	bool ping = process_ping(ip);
                	return std::make_pair(ping, ip);
            	}));
            	++result_iter;
        	}
        	for (auto& future : futures) {
            	auto result = future.get();
            	bool ping = result.first;
            	std::string ip = result.second;
            	if (ping){result_main.push_back(ip);}
        	}
        	futures.clear();
        	ip_count_ping += tasks_to_execute;

			if (ip_count_ping % argp.ping_log == 0) {
            	double procents = (static_cast<double>(ip_count_ping) / result.size()) * 100;
            	std::string _result = format_percentage(procents);
            	std::cout << np.main_nesca_out("^NESCAPINGLOG", std::to_string(ip_count_ping) + " out of " + std::to_string(result.size()) 
						+ " IPs", 4, "P", "", _result + "%", "","") << std::endl;
			}
    	}
    	int error_count = result.size() - result_main.size();
    	// std::cout << np.main_nesca_out("NESCA4", "FINISH ping", 5, "success", "errors", std::to_string(result_main.size()), std::to_string(error_count)) << std::endl;
    }
    if (argp.ping_off){result_main = result;}
	if (!argp.custom_threads_resolv){
		if (argp.my_life_my_rulez){argp.dns_threads = result_main.size();}
		if (argp.speed_type == 5){
			if (result_main.size() >= 2000){argp.dns_threads = 2000;}
			else{argp.dns_threads = result_main.size();}
		}
		if (argp.speed_type == 4){
			if (result_main.size() >= 1500){argp.dns_threads = 1500;}
			else{argp.dns_threads = result_main.size();}
		}
		if (argp.speed_type == 3){
			if (result_main.size() >= 1000){argp.dns_threads = 1000;}
			else{argp.dns_threads = result_main.size();}
		}
		if (argp.speed_type == 2){
			if (result_main.size() >= 500){argp.dns_threads = 500;}
			else{argp.dns_threads = result_main.size();}
		}
		if (argp.speed_type == 1){
			if (result_main.size() >= 100){argp.dns_threads = 100;}
			else{argp.dns_threads = result_main.size();}
		}
	}

	/*Начало получения DNS.*/
	std::cout << np.main_nesca_out("NESCA4", "DNS_RESOLUTION", 5, "threads", "", std::to_string(argp.dns_threads), "","") << std::endl;
	std::vector<std::future<void>> futures_dns;
	for (const auto& ip : result_main) {
        futures_dns.emplace_back(std::async(std::launch::async, get_dns_thread, ip));
        if (futures_dns.size() >= argp.dns_threads) {
            for (auto& future : futures_dns){future.get();}
            futures_dns.clear();
        }
    }
	for (auto& future : futures_dns){future.wait();}
	/*Конец получения DNS.*/

	/*HARD режим.*/
	if (!argp.custom_threads_scan){
		if (argp.my_life_my_rulez){argp._threads = result_main.size();}
		if (argp.speed_type == 5){
			if (result_main.size() >= 2000){argp._threads= 2000;}
			else{argp._threads= result_main.size();}
		}
		if (argp.speed_type == 4){
			if (result_main.size() >= 1500){argp._threads= 1500;}
			else{argp._threads= result_main.size();}
		}
		if (argp.speed_type == 3){
			if (result_main.size() >= 1000){argp._threads= 1000;}
			else{argp._threads = result_main.size();}
		}
		if (argp.speed_type == 2){
			if (result_main.size() >= 500){argp._threads = 500;}
			else{argp._threads = result_main.size();}
		}
		if (argp.speed_type == 1){
			if (result_main.size() >= 100){argp._threads = 100;}
			else{argp._threads = result_main.size();}
		}
	}

	   /*Как тебе такое компилятор?!*/
	   /*Open source конечно open source, но придёться
		* постараться.*/
    if (argp.fin_scan){
	   std::cout << np.main_nesca_out("NESCA4", "START_FIN_SCAN", 5, "targets", "threads", std::to_string(result_main.size()),
	   std::to_string(argp._threads),"") <<
		   std::endl;
	}else if
		(argp.null_scan)
		{std::cout 			<< np.main_nesca_out("NESCA4", "START_NULL_SCAN",
				5, "targets", "threads",
			 
			std::to_string(result_main
				.size()), std::to_string(argp._threads),"") << std::endl;
	}else if 
		(argp.xmas_scan){
		std::cout << np.main_nesca_out("NESCA4", "START_XMAS_SCAN",
				5, "targets","threads", std::to_string(result_main.size()), std::to_string(argp._threads),"") << std::endl;
	}else if
		(argp.ack_scan){
		std::cout <<
			np.main_nesca_out("NESCA4", "START_ACK_SCAN", 5, "targets", "threads",
			   std::
			   to_string(result_main.size()),
			   std::to_string(argp._threads),"") << std::endl
			;}else{
		std::cout << np.main_nesca_out("NESCA4", "START_SYN_SCAN", 5,
				"targets", "threads",
			   std::to_string(result_main.size()), std::to_string(argp._threads),"")
			<< std::endl;
	}

    ncopts.source_ip = argp.source_ip;
	if (!argp.custom_ttl){ncopts.ttl = 121;}
	else{ncopts.ttl = argp._custom_ttl;}

    ncopts.debug = argp.syn_debug;
    ncopts.scan_type = argp.type;

    long long size = result_main.size();
    std::vector<std::future<int>> futures;
    std::set<std::string> processed_ip;
    int skipped_ip = 0;

	/*Сканирование по группам.*/
	for (int i = 0; i < size; i += argp.group_size) {
		/*Сканирование текущей группы.*/
        const int groupEnd = std::min(i + argp.group_size, static_cast<int>(size));
        std::vector<std::string> ipGroup(result_main.begin() + i, result_main.begin() + groupEnd);

        for (const auto& ip : ipGroup) {
            if (processed_ip.count(ip) > 0) {
                skipped_ip++;
                continue;
            }

            ip_count++;
            processed_ip.insert(ip);

	   		if (ip_count % argp.log_set == 0){
		  		double procents = (static_cast<double>(ip_count) / size) * 100;
		  		std::string result = format_percentage(procents);
		  		std::cout << std::endl << np.main_nesca_out("^NESCASYNLOG", std::to_string(ip_count) + " out of " + std::to_string(size) + " IPs", 4, "P", "", result + "%", "","") << std::endl;
	   		}

	   		std::future<int> fut = std::async(std::launch::async, scan_port, ip.c_str(), argp.ports, argp.timeout_ms);
            futures.push_back(std::move(fut));

			if (futures.size() >= argp._threads) {
                int main_scan = futures.front().get();
                futures.erase(futures.begin());
            }
        }

        for (auto& fut : futures){int main_scan = fut.get();}

        futures.clear();

        /*Обработка результатов для текущей группы*/
        for (const auto& ip : ipGroup) {
	   		if (argp.success_target.find(ip) != argp.success_target.end() 
			   		|| argp.debug 
			   		|| argp.open_or_filtered_target.find(ip) != argp.open_or_filtered_target.end()
	           		|| argp.no_filtered_target.find(ip) != argp.no_filtered_target.end()){
		  		double time_ms = argp.rtts[ip];
		  		if (np.save_file){write_line(np.file_path_save, "\n");}
		  		std::cout << std::endl << np.main_nesca_out("READY", ip, 5, "rDNS", "RTT", argp.dns_completed[ip], std::to_string(time_ms),"") << std::endl;
	   			print_results(ip);
			}
        }
    }

    std::cout << std::endl << np.main_nesca_out("NESCA4", "FINISH_SCAN", 5, "success", "errors", std::to_string(argp.fuck_yeah), std::to_string(argp.error_fuck),"") << std::endl;
    if (skipped_ip > 0){std::cout << std::endl << np.main_nesca_out("NESCA4", "Missed "+std::to_string(skipped_ip)+" identical IPs", 5, "status", "", "OK", "","") << std::endl;}

    return 0;
}

void
print_results(std::string ip){
	auto process_ports = [&](const std::map<std::string, std::vector<int>>& target_map, int port_type) {
        auto it = target_map.find(ip);
        if (it != target_map.end()) {
            const std::vector<int>& ports = it->second;
            for (int port : ports) {
                processing_tcp_scan_ports(ip, port, port_type);
            }
        }
    };

    process_ports(argp.success_target, PORT_OPEN);
    process_ports(argp.error_target, PORT_ERROR);
    process_ports(argp.filtered_target, PORT_FILTER);
    process_ports(argp.closed_target, PORT_CLOSED);
    process_ports(argp.open_or_filtered_target, PORT_OPEN_OR_FILTER);
    process_ports(argp.no_filtered_target, PORT_NO_FILTER);
}

bool
process_ping(std::string ip){
	/*TCP_SYN PING*/
	if (argp.syn_ping){
		int source_port;
		if (!argp.custom_source_port){source_port = generate_port();}
		else {source_port = argp._custom_source_port;}
		int ttl = 121;
		if (argp.custom_ttl){ttl = argp._custom_ttl;}
		double status_time1 = tcp_syn_ping(ip.c_str(), argp.source_ip, argp.syn_dest_port, source_port, argp.ping_timeout, ttl);
		if (status_time1 != -1){
			argp.rtts[ip] = status_time1;
			return true;
		}
	}
	/*TCP_ACK PING*/
	if (argp.ack_ping){
		int source_port;
		if (!argp.custom_source_port){source_port = generate_port();}
		else {source_port = argp._custom_source_port;}
		int ttl = 121;
		if (argp.custom_ttl){ttl = argp._custom_ttl;}
		double status_time = tcp_ack_ping(ip.c_str(), argp.source_ip, argp.ack_dest_port, source_port, argp.ping_timeout, ttl);
		if (status_time != -1){
			argp.rtts[ip] = status_time;
			return true;
		}
	}
	/*ICMP пинг 3 методами.*/
	if (argp.echo_ping){
    	double icmp_casual = icmp_ping(ip.c_str(), argp.ping_timeout, 8, 0, 0, 64);
    	if (icmp_casual != -1){
	   		argp.rtts[ip] = icmp_casual;
	   		return true;
    	}
	}
	if (argp.info_ping){
    	double icmp_rev = icmp_ping(ip.c_str(), argp.ping_timeout, 13, 0, 0, 64);
		if (icmp_rev != -1){
			argp.rtts[ip] = icmp_rev;
			return true;
		}
	}
	if (argp.timestamp_ping){
    	double icmp_rev1 = icmp_ping(ip.c_str(), argp.ping_timeout, 15, 0, 0, 64);
		if (icmp_rev1 != -1){
			argp.rtts[ip] = icmp_rev1;
			return true;
		}
	}

    return false;
}

int errors_files = 0;

void check_files(const char* path, const char* path1){
    if (!check_file(path)){
		std::cout << std::endl;
        np.nlog_error(std::string(path) + " (" + std::to_string(get_count_lines(path)) + ") entries");
		errors_files++;
    }else if (!check_file(path1)){
		std::cout << std::endl;
		np.nlog_error(std::string(path1) + " (" + std::to_string(get_count_lines(path1)) + ") entries");
		errors_files++;
    }
}

void 
checking_default_files(void){
	if (argp.ip_cidr_scan_import && check_file(argp.path_cidr)) {
        if (argp.ip_cidr_scan) {
            np.nlog_trivial(std::string(argp.path_cidr) + " (" + std::to_string(get_count_lines(argp.path_cidr)) + ") entries\n");
        }
        argp.ip_cidr = write_file(argp.path_cidr);
    }else if (argp.ip_cidr_scan_import) {
        np.nlog_error(std::string(argp.path_cidr) + " (" + std::to_string(get_count_lines(argp.path_cidr)) + ") entries\n");
        errors_files++;
    }

    if (argp.ip_range_scan_import && check_file(argp.path_range)) {
        if (argp.ip_range_scan) {
            np.nlog_trivial(std::string(argp.path_range) + " (" + std::to_string(get_count_lines(argp.path_range)) + ") entries\n");
        }
        argp.ip_range = write_file(argp.path_range);
    }else if (argp.ip_range_scan_import) {
        np.nlog_error(std::string(argp.path_range) + " (" + std::to_string(get_count_lines(argp.path_range)) + ") entries\n");
        errors_files++;
    }

    if (argp.ip_scan_import && check_file(argp.path_ips)) {
        np.nlog_trivial(std::string(argp.path_ips) + " (" + std::to_string(get_count_lines(argp.path_ips)) + ") entries\n");
        argp._ip = write_file(argp.path_ips);
    }else if (argp.ip_scan_import) {
        np.nlog_error(std::string(argp.path_ips) + " (" + std::to_string(get_count_lines(argp.path_ips)) + ") entries\n");
        errors_files++;
    }

    if (argp.ip_range_scan_import){
        if (check_file(argp.path_range)){
            if (argp.ip_range_scan){
                np.nlog_trivial(std::string(argp.path_range) + " (" + std::to_string(get_count_lines(argp.path_range)) + ") entries\n");
            }
            argp.ip_range = write_file(argp.path_range);
        }else {
            np.nlog_error(std::string(argp.path_range) + " (" + std::to_string(get_count_lines(argp.path_range)) + ") entries\n");
		  errors_files++;
        }
    }

	/*Чек паролей и логин.*/
	check_files(argp.path_ftp_login.c_str(),argp.path_ftp_pass.c_str());
    check_files(argp.path_sftp_login.c_str(),argp.path_sftp_pass.c_str());
    check_files(argp.path_http_login.c_str(),argp.path_http_pass.c_str());
    check_files(argp.path_rtsp_login.c_str(),argp.path_rtsp_pass.c_str());
    check_files(argp.path_smtp_login.c_str(),argp.path_smtp_pass.c_str());
    check_files(argp.path_hikvision_login.c_str(),argp.path_hikvision_pass.c_str());

    if (errors_files == 0){std::cout << np.main_nesca_out("NESCA4", "BRUTEFORCE_DATA", 5, "status", "", "OK","","");}
    else {std::cout << np.main_nesca_out("NESCA4", "BRUTEFORCE_DATA", 5, "status", "ERRORS", "FAILED", std::to_string(errors_files),"");}
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
    if (status == PORT_OPEN){
	   np.green_html_on();
	   result_txt += "open";
	   std::cout << "open"; 
    }
    else if (status == PORT_CLOSED){
	   np.reset_colors();
	   result_txt += "closed";
	   std::cout << "closed"; 
    }
    else if (status == PORT_FILTER){
	   np.yellow_html_on();
	   result_txt += "filtered";
	   std::cout << "filtered"; 
    }
    else if (status == PORT_ERROR){
	   np.red_html_on();
	   result_txt += "error";
	   std::cout << "error"; 
    }
    else if (status == PORT_OPEN_OR_FILTER){
	   np.yellow_html_on();
	   result_txt += "open|filtered";
	   std::cout << "open|filtered"; 
    }
    else if (status == PORT_NO_FILTER){
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

/*Функция где происходят все операции с открытими портами.
 * До разбивки по файлам, выглядела как ад. Но сейчас вполне
 * читабельна.*/
void 
processing_tcp_scan_ports(std::string ip, int port, int result){
		std::stringstream stream;
    	stream << std::fixed << std::setprecision(2) << argp.rtts[ip];
    	std::string rtt_log = stream.str();


        if (result == PORT_OPEN) {
		  	if (argp.no_proc){
			 	print_port_state(PORT_OPEN, port, sn.probe_service(port));return;}

            std::string result = ip + ":" + std::to_string(port);
            std::string brute_temp;
            std::string result_print;

			/*HTTP порты.*/
            if (port == 80 || port == 81 || port == 8080 ||
			port == 8081 || port == 8888 || port == 8008){
			    print_port_state(PORT_OPEN, port, "HTTP");
                result.insert(0, "http://");
                bool status_path = false;

                std::string redirect;
                std::string default_result = "http://" + ip + ":" + std::to_string(port) + "/";
                std::string html = send_http_request(ip, port);

				/*Получение перенаправления.*/
                if (argp.no_get_path != true){redirect = parse_redirect(html, html, ip, true, port);}

			 /*Получение заголовка.*/
             std::string http_title_result = get_http_title(html);
			 if (http_title_result == HTTPTITLE_ERROR){http_title_result = get_http_title_pro(ip);}

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
             if (argp.off_http_brute != true && temp_check_http != "no" && argp.no_get_path != true && brute != -1){
			 	np.yellow_html_on();
				std::cout << "[>][HTTP]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();

                brute_temp = threads_brute_http("http://" + ip + redirect, argp.http_logins, argp.http_passwords,
                        argp.http_brute_log, argp.http_brute_verbose, argp.brute_timeout_ms);
             }

             result_print = np.main_nesca_out("BA", "http://" + brute_temp + ip + ":" + std::to_string(port), 3, "T", "F", http_title_result, type_target,rtt_log);

             if (argp.http_only){if (brute_temp.length() > 1)
       		 {result_print = np.main_nesca_out("BA", "http://" + brute_temp + ip + ":" + std::to_string(port),
			  		3, "T", "F", http_title_result, type_target, rtt_log);}}


             std::cout << result_print << std::endl;

			 /*Вывод перенаправления.*/
             if (redirect.length() != default_result.length()){
                if (redirect.length() != 0){
				    np.gray_nesca_on();
				    std::cout << "[^][REDIRT]:";
				    np.yellow_html_on();
				    std::cout << redirect + "\n";
				    np.reset_colors();
					if (np.save_file){write_line(np.file_path_save, "[^][REDIRT]:" + redirect + "\n");}
                }
             }

			 /*Вывод ответа http.*/
             if (argp.get_response){
                 std::string result_code = np.main_nesca_out("TT", html, 2, "", "", "", "",rtt_log);
                 std::cout << result_code << std::endl;
			 }
            }

            else if (port == 20 || port == 21){
			 print_port_state(PORT_OPEN, port, "FTP");
                std::lock_guard<std::mutex> guard(mtx);

			 std::string ftp_version = get_ftp_description(ip, std::to_string(port), bfd_.get_success_login(), bfd_.get_success_pass());

                if (argp.off_ftp_brute != true){
				np.yellow_html_on();
				std::cout << "[>][FTP]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();

                    brute_temp = threads_brute_ftp(ip, port, argp.ftp_logins, argp.ftp_passwords, argp.ftp_brute_log,
                            argp.ftp_brute_verbose, argp.brute_timeout_ms);

                    if (argp.ftp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("BA", "ftp://" + brute_temp + result, 3, "D", "",
                                    ftp_version ,"",rtt_log);
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("BA", "ftp://" + brute_temp + result, 3, "D", "",
                                ftp_version, "",rtt_log);
                    }
                }
                else {
                    result_print = np.main_nesca_out("BA", "ftp://" + brute_temp + result, 3, "D", "",
                            ftp_version, "",rtt_log);
                }
                
                std::cout << result_print << std::endl;
            }
            else if (port == 22){
			 print_port_state(PORT_OPEN, port, "SSH");
                std::lock_guard<std::mutex> guard(mtx);

                if (argp.off_sftp_brute != true){
				np.yellow_html_on();
				std::cout << "[>][SSH]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();

                    brute_temp = threads_brute_ssh(ip, port, argp.sftp_logins, argp.sftp_passwords, argp.sftp_brute_log,
                        argp.sftp_brute_verbose, argp.sftp_using_know_hosts, argp.brute_timeout_ms);

                    if (argp.sftp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("BA", "sftp://" + brute_temp + result, 3, "", "", "", "",rtt_log);
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("BA", "sftp://" + brute_temp + result, 3, "", "", "", "",rtt_log);
                    }
                }
                else {
                    result_print = np.main_nesca_out("BA", "sftp://" + result, 3, "", "", "", "",rtt_log);
                }

                std::cout << result_print << std::endl;
            }
            else if (port == 554){
			 print_port_state(PORT_OPEN, port, "RTSP");
                std::lock_guard<std::mutex> guard(mtx);
                std::string path_yes = "";

                if (argp.off_rtsp_brute != true){

                    std::vector<std::string> rtsp_paths = {"/Streaming/Channels/101", "/h264/ch01/main/av_stream", 
                                                          "/cam/realmonitor?channel=1&subtype=0","/live/main",
                                                           "/av0_0", "/mpeg4/ch01/main/av_stream"};

				np.yellow_html_on();
				std::cout << "[>][RTSP]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();

                    for (auto& path : rtsp_paths){
                        brute_temp = threads_brute_rtsp(ip+path, argp.rtsp_logins, argp.rtsp_passwords, argp.rtsp_brute_log, argp.rtsp_brute_verbose,
                                                   argp.brute_timeout_ms);
                        if (brute_temp.length() > 1){
                            path_yes = path;
                        }
                    }

                    if (argp.rtsp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("BA", "rtsp://" + brute_temp + result + path_yes, 3, "", "", "", "",rtt_log);
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("BA", "rtsp://" + brute_temp + result + path_yes, 3, "", "", "", "",rtt_log);
                    }
                }
                else {
                    result_print = np.main_nesca_out("BA", "rtsp://" + result, 3, "", "", "", "",rtt_log);
                }

                std::cout << result_print << std::endl;
            }
            else if (port == 8000){
			 print_port_state(PORT_OPEN, port, "HIKVISION");
                std::lock_guard<std::mutex> guard(mtx);

                if (argp.off_hikvision_brute != true){
				np.yellow_html_on();
				std::cout << "[>][HIKVISION]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();
                    brute_temp = threads_brute_hikvision(ip, argp.hikvision_logins, argp.hikvision_passwords, argp.hikvision_brute_log,
                                                  argp.brute_timeout_ms);

                    if (argp.hikvision_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("BA", "" + brute_temp + result, 3, "", "", "", "",rtt_log);
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("BA", "" + brute_temp + result, 3, "", "", "", "",rtt_log);
                    }
                }
                else {
                    result_print = np.main_nesca_out("BA", "" + result, 3, "", "", "", "",rtt_log);
                }

                std::cout << result_print << std::endl;
            }
            else if (port == 443){
			 print_port_state(PORT_OPEN, port, "HTTPS");
                std::string result_print = np.main_nesca_out("BA", "https://" + result, 3, "", "", "", "",rtt_log);
                std::lock_guard<std::mutex> guard(mtx);
                std::cout << result_print << std::endl;

            } else if (port == 25){
			 print_port_state(PORT_OPEN, port, "SMTP");
                std::lock_guard<std::mutex> guard(mtx);
			 std::string responce_220 = smtp_get_220_response(ip, port, 0);

                if (argp.off_sftp_brute != true){
				np.yellow_html_on();
				std::cout << "[>][SMTP]:" + ip + " [BRUTEFORCE]\n";
				np.reset_colors();

                    brute_temp = threads_brute_smtp(ip, port, argp.smtp_logins, argp.smtp_passwords, argp.smtp_brute_log,
                        argp.smtp_brute_verbose, argp.brute_timeout_ms);


                    if (argp.sftp_only){
                        if (brute_temp.length() > 1){
                            result_print = np.main_nesca_out("BA", "smtp://" + brute_temp + result, 3, "D", "", responce_220, "",rtt_log);
                        }
                    }
                    else {
                        result_print = np.main_nesca_out("BA", "smtp://" + brute_temp + result, 3, "D", "", responce_220, "",rtt_log);
                    }
                }
                else {
                    result_print = np.main_nesca_out("BA", "smtp://" + result, 3, "", "", responce_220, "",rtt_log);
                }

                std::cout << result_print << std::endl;
		  }
            else{
                std::lock_guard<std::mutex> guard(mtx);
			 print_port_state(PORT_OPEN, port, sn.probe_service(port));
            }
        }
        else if (result == -1){
            if (argp.print_errors){
                std::lock_guard<std::mutex> guard(mtx);
			 print_port_state(PORT_ERROR, port, sn.probe_service(port));
            }
        }
        else if (result == 2){
            if (argp.debug){
                std::lock_guard<std::mutex> guard(mtx);
			 	print_port_state(PORT_FILTER, port, sn.probe_service(port));
            }
        }
        else if (result == 3){
            std::lock_guard<std::mutex> guard(mtx);
			print_port_state(PORT_OPEN_OR_FILTER, port, sn.probe_service(port));
        }
        else if (result == 4){
            std::lock_guard<std::mutex> guard(mtx);
			print_port_state(PORT_NO_FILTER, port, sn.probe_service(port));
        }
        else if (result == 1) {
            if (argp.debug){
                std::lock_guard<std::mutex> guard(mtx);
			 	print_port_state(PORT_CLOSED, port, sn.probe_service(port));
            }
        }
}
// You live?

void 
help_menu(void){
    logo();
    np.golder_rod_on();
    std::cout << "usage: " << run << " [target 1,2,3] [flags]\n";
    np.reset_colors();

    np.sea_green_on();
    std::cout << "\narguments target:" << std::endl;
    np.reset_colors();
    std::cout << "  -import-ip <path>        Set ip on target from file.\n";
    std::cout << "  -import-cidr <path>      Set cidr on target from file.\n";
    std::cout << "  -import-range <path>     Set range on target from file.\n";
    std::cout << "  -random-ip <count>       Set random ip target.\n";

    np.sea_green_on();
    std::cout << "\narguments speed:" << std::endl;
    np.reset_colors();
    std::cout << "  -speed, -S <1-5>         Edit max speed.\n";
    std::cout << "  -max-group <count>       Edit max group for scan ip.\n";
    std::cout << "  -my-life-my-rulez        Using very MAX speed settings.\n";

    np.sea_green_on();
    std::cout << "\narguments port scan methods:" << std::endl;
    np.reset_colors();
    std::cout << "  -fin, -xmas, -null       Use one of these scanning methods.\n";
    std::cout << "  -ack, -windows -maimon   Use ack or window or maimon scan method.\n";

    np.sea_green_on();
    std::cout << "\narguments saving to file:" << std::endl;
    np.reset_colors();
    std::cout << "  -html, -l <path>         Classic nesca save, write on html page.\n";
    std::cout << "  -txt <path>              Save result to text document.\n";

    np.sea_green_on();
    std::cout << "\narguments port scan:" << std::endl;
    np.reset_colors();
    std::cout << "  -delay, -d <ms>          Set delay for scan.\n";
    std::cout << "  -threads, -T <count>     Edit max threads for scan.\n";
    std::cout << "  -ports, -p <1,2,3>       Set ports on scan.\n";
    std::cout << "  -scan-timeout <ms>       Set timeout for getting packet on port.\n";
    std::cout << "  -scan-db, scan-debug     Display verbose info for send packets.\n";

    np.sea_green_on();
    std::cout << "\narguments dns resolution:" << std::endl;
    np.reset_colors();
    std::cout << "  -TD <count>              Set max threads for dns-resolution.\n";
    std::cout << "  -resol-port <port>       Edit source port for dns-resolution.\n";
    std::cout << "  -resol-delay <ms>        Set delay for dns-resolution.\n";

    np.sea_green_on();
    std::cout << "\narguments ping scan:" << std::endl;
    np.reset_colors();
    std::cout << "  -PS, -PA <port>          On TCP ping SYN|ACK and edit dest port.\n";
    std::cout << "  -PE, -PI, -PM            On ICMP ping ECHO|INFO|TIMESTAMP\n";
    std::cout << "  -max-ping                Using all ping methods ICMP and TCP.\n";
    std::cout << "  -no-ping                 Off ping scan.\n";

    np.sea_green_on();
    std::cout << "\narguments ping speed:" << std::endl;
    np.reset_colors();
    std::cout << "  -TP <count>              Set max threads for ping.\n";
    std::cout << "  -ping-timeout <ms>       Set recv timeout for ping.\n";

    np.sea_green_on();
    std::cout << "\narguments bruteforce:" << std::endl;
    np.reset_colors();
    std::cout << "  -brute-login <ss,path>   Set path for <ss> logins.\n";
    std::cout << "  -brute-pass <ss,path>    Set path for <ss> passwords.\n";
    std::cout << "  -brute-timeout <ms>      Edit brute timout.\n";
    std::cout << "  -brute-only <ss,2>       Display only success <ss> bruteforce.\n";
    std::cout << "  -no-brute <ss,2>         Disable <ss> bruteforce.\n";

    np.sea_green_on();
    std::cout << "\narguments other bruteforce:" << std::endl;
    np.reset_colors();
    std::cout << "  -brute-verbose <ss,2>    Display bruteforce <ss> all info.\n";
    std::cout << "  -brute-log <ss,2>        Display bruteforce <ss> info.\n";
    std::cout << "  -sftp-brute-known-hosts  Reading known_host for connection.\n";

    np.sea_green_on();
    std::cout << "\narguments dns scan:" << std::endl;
    np.reset_colors();
    std::cout << "  -dns-scan <.dns>         On dns-scan and set domain 1 level.\n";
    std::cout << "  -dns-length <count>      Edit length generating domain.\n";
    std::cout << "  -dns-dict <dict>         Edit dictionary for generation.\n";

    np.sea_green_on();
    std::cout << "\narguments output:" << std::endl;
    np.reset_colors();
    std::cout << "  -db, -debug              On debug mode, save and display not even working hosts.\n";
    std::cout << "  -er, -error              On display errors.\n";
    std::cout << "  -no-proc                 Only scan.\n";
    std::cout << "  -packet-trace            Display packet_trace.\n";
    std::cout << "  -no-get-path             Disable getting paths.\n";
    std::cout << "  -log-set <count>         Change change the value of ips after which, will be displayed information about how much is left.\n";
    std::cout << "  -on-http-response        On print response from port 80.\n";
    np.sea_green_on();
    std::cout << "\narguments colors:" << std::endl;
    np.reset_colors();
    std::cout << "  -no-color                Disable colors.\n";
    std::cout << "  -import-color <path>     Import color scheme from file.\n";

    np.sea_green_on();
    std::cout << "\narguments other:" << std::endl;
    np.reset_colors();
    std::cout << "  -source-ip               Set custom source_ip.\n";
    std::cout << "  -source-port             Set custom source_port.\n";
    std::cout << "  -ttl                     Set custom ip_header_ttl.\n";
}

void 
parse_args(int argc, char** argv){
    int rez;
    int option_index = 0;

    while ((rez = getopt_long_only(argc, argv, short_options, long_options, &option_index)) != EOF) {
        switch (rez) {
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
                if (argp.ports[0] == EOF){
                    size_t pos = argp.ports_temp.find(",");
                    size_t pos1 = argp.ports_temp.find("-");

                    if (pos1 != std::string::npos){
                        argp.ports = parse_range(optarg);
                    }
                    else {
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
               std::transform(what[0].begin(), what[0].end(), what[0].begin(), [](unsigned char c) {
                    return std::tolower(c);
               });
               const char* what_convert = what[1].c_str();
               if (what[0] == "ftp"){
                    argp.path_ftp_login = what_convert;
               }
               else if (what[0] == "sftp"){
                   argp.path_sftp_login = what_convert;
               }
               else if (what[0] == "rtsp"){
                   argp.path_rtsp_login = what_convert;
               }
               else if (what[0] == "http"){
                   argp.path_http_login = what_convert;
               }
               else if (what[0] == "smtp"){
			    argp.path_smtp_login = what_convert;
               }
               else if (what[0] == "hikvision"){
                   argp.path_hikvision_login = what_convert;
               }
               else {
                   break;
              }

               break;
           }
           case 11:
           {
               std::vector<std::string> what = split_string_string(optarg, ',');
               std::transform(what[0].begin(), what[0].end(), what[0].begin(), [](unsigned char c) {
                    return std::tolower(c);
               });
               const char* what_convert = what[1].c_str();
               if (what[0] == "ftp"){
                    argp.path_ftp_pass = what_convert;
               }
               else if (what[0] == "sftp"){
                   argp.path_sftp_pass = what_convert;
               }
               else if (what[0] == "rtsp"){
                   argp.path_rtsp_pass = what_convert;
               }
               else if (what[0] == "http"){
                   argp.path_http_pass = what_convert;
               }
               else if (what[0] == "smtp"){
			    argp.path_smtp_pass = what_convert;
               }
               else if (what[0] == "hikvision"){
                   argp.path_hikvision_pass = what_convert;
               }
               else {
                   break;
              }
               break;
           }
           case 30:
           {
               std::vector<std::string> what = split_string_string(optarg, ',');
                for (int i = 0; i < what.size(); i++){
                    std::transform(what[i].begin(), what[i].end(), what[i].begin(), [](unsigned char c) {
                        return std::tolower(c);
                    });
                    if (what[i] == "ftp"){
                        argp.ftp_brute_log = true;
                    }
                    else if (what[i] == "sftp"){
                        argp.sftp_brute_log = true;
                    }
                    else if (what[i] == "rtsp"){
                        argp.rtsp_brute_log = true;
                    }
                    else if (what[i] == "http"){
                        argp.http_brute_log = true;
                    }
                    else if (what[i] == "hikvision"){
                        argp.hikvision_brute_log = true;
                    }
                    else if (what[i] == "smtp"){
				    argp.smtp_brute_log = true;
                    }
                    else if (what[i] == "all"){
                        argp.ftp_brute_log = true;
				    argp.smtp_brute_log = true;
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

                for (int i = 0; i < what.size(); i++){
                    std::transform(what[i].begin(), what[i].end(), what[i].begin(), [](unsigned char c) {
                        return std::tolower(c);
                    });
                    if (what[i] == "ftp"){
                        argp.ftp_brute_verbose = true;
                    }
                    else if (what[i] == "sftp"){
                        argp.sftp_brute_verbose = true;
                    }
                    else if (what[i] == "rtsp"){
                        argp.rtsp_brute_verbose = true;
                    }
                    else if (what[i] == "http"){
                        argp.http_brute_verbose = true;
                    }
                    else if (what[i] == "smtp"){
				    argp.smtp_brute_verbose = true;
                    }
                    else if (what[i] == "all"){
                        argp.ftp_brute_verbose = true;
                        argp.sftp_brute_verbose = true;
				    argp.smtp_brute_verbose = true;
                        argp.rtsp_brute_verbose = true;
                        argp.http_brute_verbose = true;
                    }
                    else {
                        break;
                    }
                }

               break;
           }
           case 44:
           {
               std::vector<std::string> what = split_string_string(optarg, ',');

               for (int i = 0; i < what.size(); i++){
                    std::transform(what[i].begin(), what[i].end(), what[i].begin(), [](unsigned char c) {
                        return std::tolower(c);
                    });
                   if (what[i] == "ftp"){
                       argp.off_ftp_brute = true;
                   }
                   else if (what[i] == "sftp"){
                       argp.off_sftp_brute = true;
                   }
                   else if (what[i] == "rtsp"){
                       argp.off_rtsp_brute = true;
                   }
                   else if (what[i] == "http"){
                       argp.off_http_brute = true;
                   }
                   else if (what[i] == "hikvision"){
                       argp.off_hikvision_brute = true;
                   }
                   else if (what[i] == "smtp"){
				   argp.off_smtp_brute = true;
                   }
                   else if (what[i] == "all"){
                       argp.off_ftp_brute = true;
                       argp.off_sftp_brute = true;
				   argp.off_smtp_brute = true;
                       argp.off_rtsp_brute = true;
                       argp.off_http_brute = true;
                       argp.off_hikvision_brute = true;
                   }
                   else {
                       break;
                   }
               }

               break;
           }
           case 46:
           {
               std::vector<std::string> what = split_string_string(optarg, ',');

               for (int i = 0; i < what.size(); i++){
                    std::transform(what[i].begin(), what[i].end(), what[i].begin(), [](unsigned char c) {
                        return std::tolower(c);
                    });
                   if (what[i] == "ftp"){
                       argp.ftp_only = true;
                   }
                   else if (what[i] == "sftp"){
                       argp.sftp_only = true;
                   }
                   else if (what[i] == "rtsp"){
                       argp.rtsp_only = true;
                   }
                   else if (what[i] == "http"){
                       argp.http_only = true;
                   }
                   else if (what[i] == "hikvision"){
                       argp.hikvision_only = true;
                   }
                   else if (what[i] == "smtp"){
				   argp.smtp_only = true;
                   }
                   else if (what[i] == "all"){
                       argp.sftp_only = true;
                       argp.ftp_only = true;
				   argp.smtp_only = true;
                       argp.rtsp_only = true;
                       argp.http_only = true;
                       argp.hikvision_only = true;
                   }
                   else {
                       break;
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
				argp.custom_threads_scan = true;
                if (atoi(optarg) >= 600){
                    argp.warning_threads = true;
                    argp.threads_temp = atoi(optarg);
                }
                else {
                    argp._threads = atoi(optarg);
                }
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
			   argp.custom_source_ip = true;
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
			   argp.custom_group_max = true;
			   argp.group_size = atoi(optarg);
               break;
           case 39:
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
			   np.html_file_path = optarg;
               break;
           case 57:
			   argp.custom_threads = true;
			   argp.threads_ping = atoi(optarg);
               break;
           case 56:
               break;
           case 59:
               argp.syn_debug = true;
               break;
           case 60:
               argp.syn_debug = true;
               break;

		  /*Пинг аргументы влкючения.*/
	      case 80:
			 argp.syn_ping = true;
			 argp.syn_dest_port = atoi(optarg);
		     break;
	      case 81:
			 argp.ack_ping = true;
			 argp.ack_dest_port = atoi(optarg);
		     break;
	      case 82:
			 argp.echo_ping = true;
		     break;
	      case 86:
			 argp.info_ping = true;
		     break;
	      case 87:
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
init_bruteforce(void){
    argp.ftp_logins = write_file(argp.path_ftp_login);
    argp.ftp_passwords = write_file(argp.path_ftp_pass);
    argp.sftp_logins = write_file(argp.path_sftp_login);
    argp.sftp_passwords = write_file(argp.path_sftp_pass);
    argp.rtsp_logins = write_file(argp.path_rtsp_login);
    argp.rtsp_passwords = write_file(argp.path_rtsp_pass);
    argp.http_logins = write_file(argp.path_http_login);
    argp.http_passwords = write_file(argp.path_http_pass);
    argp.hikvision_logins = write_file(argp.path_hikvision_login);
    argp.hikvision_passwords = write_file(argp.path_hikvision_pass);
    argp.smtp_logins = write_file(argp.path_smtp_login);
    argp.smtp_passwords = write_file(argp.path_smtp_pass);
}

std::string 
format_percentage(double procents){
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << procents << "%";
    std::string result = oss.str();
    return result;
}


/*Функция через которую происходит само сканирование
 * портов. Вроде бы стабильно.*/
int
scan_port(const char* ip, std::vector<int>ports, const int timeout_ms){
	int source_port;
	if (!argp.custom_source_port){source_port = generate_port();}
	else {source_port = argp._custom_source_port;}

    ncopts.source_port = source_port;
    ncopts.seq = generate_seq();

    int recv_timeout_result = 600;
    if (argp.custom_recv_timeout_ms){
	   recv_timeout_result = argp.recv_timeout_ms;
    }else {
	   /*Расчёт таймаута для приёма данных*/
	   auto it = argp.rtts.find(ip);
	   if (it != argp.rtts.end()) {
		  double rtt_ping = argp.rtts.at(ip);
		  if (argp.my_life_my_rulez){recv_timeout_result = rtt_ping + 100;}
		  if (argp.speed_type == 5){recv_timeout_result = rtt_ping * 2;}
		  if (argp.speed_type == 4){recv_timeout_result = rtt_ping * 3;}
		  if (argp.speed_type == 3){recv_timeout_result = rtt_ping * 4;}
		  if (argp.speed_type == 2 || argp.speed_type == 1){recv_timeout_result = rtt_ping * 5;}
	   }
	   else{recv_timeout_result = 600;}/*В другом случае по стандарту 600.*/
    }

    for (const auto& port : ports){
	   /*Отправка пакета.*/
	   const int result = nesca_scan(&ncopts, ip, port, timeout_ms);
	   /*Лог.*/
	   if (argp.packet_trace){np.nlog_custom("SEND", "TCP >> "+ std::string(argp.source_ip)+
			 ":"+std::to_string(source_port)+" >> "+ std::string(ip)+":"+std::to_string(port)+"\n", 1);}

	   /*Если функция не вернула PORT_OPEN,
	    * Это означает что функция успешно выполнилась.*/
	   if (result != PORT_OPEN){
		  /*Значит была ошибка.*/
		  argp.error_target[ip].push_back(port);
		  argp.error_fuck++;
		  /*Переход к следующему порту.*/
		  continue;
	   }

	   /*Буфер для ответа.*/
	   ls.lock();
	   unsigned char *buffer = (unsigned char *)calloc(READ_BUFFER_SIZE, sizeof(unsigned char));
	   ls.unlock();

	   /*В другом случае, запускается
	    * "Принятие пакета" или скорее его ожидание.*/
	   int read = ncread(ip, recv_timeout_result, &buffer, argp.syn_debug);
	   /*Лог.*/
	   if (argp.packet_trace){np.nlog_custom("RECV", "TCP >> "+ std::string(ip)+
			 ":"+std::to_string(port)+" >> "+ std::string(argp.source_ip)+":"+std::to_string(source_port)+"\n", 1);}

	   /*Если функция не получила пакет.*/
	   if (read != SUCCESS_READ){
		  ls.lock();
		  free(buffer);
		  ls.unlock();
		  /*Значит порт open|filtered.*/
		  if (ncopts.scan_type != SYN_SCAN && ncopts.scan_type != ACK_SCAN && ncopts.scan_type != WINDOW_SCAN){argp.open_or_filtered_target[ip].push_back(port);}
		  /*Значит порт filtered.*/
		  else{argp.filtered_target[ip].push_back(port);}
		  continue;
	   }

	   /*В другом случае идёт обработка пакета.
	    * И только на этом этапе мы получаем статус порта.*/
	   int port_status = -1;
	   if (ncopts.scan_type == SYN_SCAN){port_status = get_port_status(buffer, false, false, false, false);}
	   else if (ncopts.scan_type == ACK_SCAN){port_status = get_port_status(buffer, false, true, false, false);}
	   else if (ncopts.scan_type == WINDOW_SCAN){port_status = get_port_status(buffer, false, false, true, false);}
	   else if (ncopts.scan_type == MAIMON_SCAN){port_status = get_port_status(buffer, false, false, false, true);}
	   else {port_status = get_port_status(buffer, true, false, false, false);}

	   if (port_status == PORT_CLOSED){argp.closed_target[ip].push_back(port);}
	   else if (port_status == PORT_OPEN){argp.success_target[ip].push_back(port); argp.fuck_yeah++;}
	   else if (port_status == PORT_FILTER){argp.filtered_target[ip].push_back(port);}
	   else if (port_status == PORT_NO_FILTER){argp.no_filtered_target[ip].push_back(port);}
	   else {argp.error_target[ip].push_back(port); argp.error_fuck++;}

	   ls.lock();
	   free(buffer);
	   ls.unlock();
    }
    return 0;
}

void
get_dns_thread(std::string ip){
	delay_ms(argp.resol_delay);
	std::string temp_dns = dus.get_dns_by_ip(ip.c_str(), argp.resol_source_port);
	argp.dns_completed.insert(std::make_pair(ip, temp_dns));}

