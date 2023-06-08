#include <iostream>
#include <vector>

class arguments_program{
public:
	   /*Save*/
        bool txt;
        std::string txt_save;

	   /*Scan options*/
	   const char* source_ip;
	   int type = 1;
	   bool nmap_mode;
	   bool fin_scan;
	   bool null_scan;
	   bool xmas_scan;

        bool timeout;
        int timeout_ms = 140;
        int recv_timeout_ms = 2000;
        int scanning_count = 2;
        int log_set = 20;
        int _threads = 15;

        std::vector<int> ports = {80};
	   std::vector<int> source_ports = {46566, 42849, 38872, 58098,
								 34343, 54075, 54176, 54784};

        bool debug;
        bool print_errors;
        bool get_path_log;
        bool syn_debug;

        bool ping_off;
        bool no_get_path;
        bool fix_get_path;

        bool get_response;
        bool get_dns;

	   /*DNS scan options*/
        bool dns_scan;
        std::string domain_1level;
        std::string dns_dictionary = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	   int dns_scan_domain_count = 5;

	   /*Scan target*/
        bool random_ip;
        int random_ip_count;

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
	   int icmp_ping_timeout = 500;
	   int tcp_ping_timeout = 300;
	   int threads_ping = 10;
	   int ping_log = 20;
        bool display_response_time;

	   /*Don`t touch*/
        int fuck_yeah = 0;
        bool warning_threads;
        bool print_help_menu;
        int threads_temp;
        std::string ports_temp;
        bool thread_on_port;
	   bool info_version;
        bool html;

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
        bool off_http_brute;
        bool off_smtp_brute;
        bool off_hikvision_brute;

        bool ftp_brute_log;
        bool sftp_brute_log;
        bool rtsp_brute_log;
        bool http_brute_log;
	   bool smtp_brute_log;
        bool hikvision_brute_log;

        bool ftp_only;
        bool sftp_only;
        bool rtsp_only;
        bool http_only;
        bool smtp_only;
        bool hikvision_only;

        bool sftp_using_know_hosts;

	   /*Testing*/
        bool host_testing;
        std::vector<std::string> hosts_test;
        bool get_redirect;
        bool response_code_test;
        bool http_request;
        bool tcp_ping_test; // icmp :)
        std::string tcp_ping_mode;

	   /*Generation*/
        bool generation_test;
        int generate_count;
        bool generate_ipv4_test;
        bool generate_ipv6_test;
        int octets;

	   /*Color options*/
        bool color_off;
	   bool import_color_scheme;
        const char* path_color_scheme;
};
