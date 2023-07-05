#include <iostream>
#include <vector>
#include <map>

class arguments_program{
public:
	   /*Save*/
       bool txt;
       std::string txt_save;

	   /*Scan options*/
	   const char* source_ip;
	   int type = 1;
	   int speed_type = 3;
	   bool custom_source_ip;
	   bool custom_threads_scan;
	   bool custom_group_max;
	   int group_size = 20;

	   bool custom_source_port;
	   bool custom_ttl;

	   int _custom_ttl;
	   int _custom_source_port;

	   bool fin_scan;
	   bool null_scan;
	   bool xmas_scan;
	   bool ack_scan;
	   bool window_scan;
	   bool maimon_scan;
	   bool packet_trace;

       bool timeout;
       int timeout_ms = 0;
   	   bool custom_recv_timeout_ms;
       int recv_timeout_ms = 1000;
       int log_set = 20;
       int _threads = 50;

       std::vector<int> ports = {80,443};
	   bool no_proc;

       bool debug;
       bool print_errors;
	   bool my_life_my_rulez;
       bool get_path_log;
       bool syn_debug;

       bool ping_off;
       bool no_get_path;

       bool get_response;

	   /*DNS scan options*/
       bool dns_scan;
       std::string domain_1level;
       std::string dns_dictionary = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	   int dns_scan_domain_count = 5;
	   bool custom_threads_resolv;

	   /*Scan target*/
       bool random_ip;
       int random_ip_count;
	   int dns_threads = 50;
	   int resol_source_port = 4555;
	   int resol_delay = 0;

       bool ip_scan;
       bool ip_cidr_scan;
       bool ip_range_scan;

       bool ip_scan_import;
       bool ip_cidr_scan_import;
       bool ip_range_scan_import;

	   std::vector<std::string> _ip;
       std::vector<std::string> ip_cidr;
       std::vector<std::string> ip_range;
       std::vector<std::string> dns; // ip_scan on

       const char* path_range;
       const char* path_cidr;
       const char* path_ips;

	   /*Ping options*/
	   int ping_timeout = 1000;
	   int threads_ping = 100;
	   int ping_log = 20;
	   bool custom_threads;

	   bool ack_ping;
	   bool syn_ping;
	   bool echo_ping;
	   bool info_ping;
	   bool timestamp_ping;
	   bool max_ping;

	   int ack_dest_port = 80;
	   int syn_dest_port = 80;

	   std::map<std::string,double> rtts;

	   /*Don`t touch*/
       int fuck_yeah = 0;
	   int error_fuck = 0;
       bool warning_threads;
       bool print_help_menu;
       int threads_temp;
       std::string ports_temp;

	   std::map<std::string, std::vector<int>> success_target;
	   std::map<std::string, std::vector<int>> error_target;
	   std::map<std::string, std::vector<int>> filtered_target;
	   std::map<std::string, std::vector<int>> open_or_filtered_target;
	   std::map<std::string, std::vector<int>> no_filtered_target;
	   std::map<std::string, std::vector<int>> closed_target;

	   std::map<std::string, std::string> dns_completed;
       bool thread_on_port;
	   bool info_version;

	   /*Bruteforce auth data*/
       std::vector<std::string> ftp_logins;
       std::vector<std::string> ftp_passwords;
       std::vector<std::string> rtsp_logins;
       std::vector<std::string> rtsp_passwords;
       std::vector<std::string> sftp_logins;
       std::vector<std::string> sftp_passwords;
       std::vector<std::string> http_logins;
       std::vector<std::string> http_passwords;
       std::vector<std::string> hikvision_logins;
       std::vector<std::string> hikvision_passwords;
       std::vector<std::string> smtp_logins;
       std::vector<std::string> smtp_passwords;
       std::vector<std::string> rvi_logins;
       std::vector<std::string> rvi_passwords;

	   /*Bruteforce paths*/
       std::string path_ftp_login = "passwd/ftp_logins.txt";
       std::string path_ftp_pass = "passwd/ftp_passwords.txt";
       std::string path_sftp_login = "passwd/sftp_logins.txt";
       std::string path_sftp_pass = "passwd/sftp_passwords.txt";
       std::string path_rtsp_login = "passwd/rtsp_logins.txt";
       std::string path_rtsp_pass = "passwd/rtsp_passwords.txt";
       std::string path_http_login = "passwd/http_logins.txt";
       std::string path_http_pass = "passwd/http_passwords.txt";
       std::string path_hikvision_login = "passwd/hikvision_logins.txt";
       std::string path_hikvision_pass = "passwd/hikvision_passwords.txt";
       std::string path_smtp_login = "passwd/smtp_logins.txt";
       std::string path_smtp_pass = "passwd/smtp_passwords.txt";
       std::string path_rvi_login = "passwd/rvi_logins.txt";
       std::string path_rvi_pass = "passwd/rvi_passwords.txt";

	   /*Bruteforce options*/
       int brute_timeout_ms = 10;

       bool ftp_brute_verbose;
       bool sftp_brute_verbose;
       bool rtsp_brute_verbose;
       bool smtp_brute_verbose;
       bool http_brute_verbose;

       bool off_ftp_brute;
       bool off_sftp_brute;
       bool off_rtsp_brute;
	   bool off_rvi_brute;
       bool off_http_brute;
       bool off_smtp_brute;
       bool off_hikvision_brute;

       bool ftp_brute_log;
       bool sftp_brute_log;
       bool rtsp_brute_log;
	   bool rvi_brute_log;
       bool http_brute_log;
	   bool smtp_brute_log;
       bool hikvision_brute_log;

       bool ftp_only;
       bool sftp_only;
       bool rtsp_only;
	   bool rvi_only;
       bool http_only;
       bool smtp_only;
       bool hikvision_only;

       bool sftp_using_know_hosts;

	   /*Color options*/
       bool color_off;
	   bool import_color_scheme;
       const char* path_color_scheme;
};
