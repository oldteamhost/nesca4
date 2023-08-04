#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

#define SPEED_TYPE_DEFAULT 4
#define SCAN_PORTS_TYPE_DEFAULT 1
#define DEFAULT_PORTS {80,443}
#define GROUP_MIN_SIZE_DEFAULT 5
#define SYN_PING_DEFAULT_DEST_PORT 80
#define ACK_PING_DEFAULT_DEST_PORT 80
#define PING_LOG_DEFAULT 20
#define DNS_RESOLV_SOURCE_PORT_DEFUALT 4555
#define DNS_SCAN_THREADS_DEFAULT 50
#define DNS_SCAN_SIZE_DNS_DEFAULT 5
#define NEGATIVES_PATH_DEFAULT "resources/negatives.txt"
#define DNS_SCAN_DICTIONARY_DEFAULT "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

#define PATH_FTP_LOGIN_DEFAULT "passwd/ftp_logins.txt"
#define PATH_FTP_PASS_DEFAULT "passwd/ftp_passwords.txt"
#define PATH_SFTP_LOGIN_DEFAULT "passwd/sftp_logins.txt"
#define PATH_SFTP_PASS_DEFAULT "passwd/sftp_passwords.txt"
#define PATH_RTSP_LOGIN_DEFAULT "passwd/rtsp_logins.txt"
#define PATH_RTSP_PASS_DEFAULT "passwd/rtsp_passwords.txt"
#define PATH_HTTP_LOGIN_DEFAULT "passwd/http_logins.txt"
#define PATH_HTTP_PASS_DEFAULT "passwd/http_passwords.txt"
#define PATH_HIKVISION_LOGIN_DEFAULT "passwd/hikvision_logins.txt"
#define PATH_HIKVISION_PASS_DEFAULT "passwd/hikvision_passwords.txt"
#define PATH_SMTP_LOGIN_DEFAULT "passwd/smtp_logins.txt"
#define PATH_SMTP_PASS_DEFAULT "passwd/smtp_passwords.txt"
#define PATH_RVI_LOGIN_DEFAULT "passwd/rvi_logins.txt"
#define PATH_RVI_PASS_DEFAULT "passwd/rvi_passwords.txt"

class arguments_program{
public:
	   std::string negatives_path = NEGATIVES_PATH_DEFAULT;
	   bool pro_mode;

       bool txt;
       std::string txt_save;

	   const char* source_ip;
	   int type = SCAN_PORTS_TYPE_DEFAULT;
	   int speed_type = SPEED_TYPE_DEFAULT;
	   int count_success_ips;

	   bool custom_g_rate;
	   std::vector<std::string> exclude;
	   bool custom_g_max;
	   bool custom_g_min;

	   bool custom_source_port;
	   bool custom_ttl;

	   int _custom_ttl;
	   int _custom_source_port;

	   bool fin_scan;
	   bool null_scan;
	   bool nesca3_scan;
       bool robots_txt;
       bool sitemap_xml;
	   bool xmas_scan;
	   bool ack_scan;
	   bool window_scan;
	   bool maimon_scan;

       bool timeout;
       int timeout_ms;
   	   bool custom_recv_timeout_ms;
       int recv_timeout_ms;
	   bool custom_log_set;
       int log_set;
       int _threads;
       int _threads_dns = DNS_SCAN_THREADS_DEFAULT;

       std::vector<int> ports = DEFAULT_PORTS;
	   bool no_proc;

       bool debug;
       bool print_errors;
	   bool my_life_my_rulez;
       bool get_path_log;
       bool syn_debug;

       bool ping_off;
       bool no_get_path;

       bool get_response;

       bool dns_scan;
       std::string domain_1level;
       std::string dns_dictionary = DNS_SCAN_DICTIONARY_DEFAULT;
	   int dns_scan_domain_count = DNS_SCAN_SIZE_DNS_DEFAULT;
	   bool custom_threads_resolv;

       bool random_ip;
	   bool no_get_dns;
       int random_ip_count;
	   int dns_threads;
	   int resol_source_port = DNS_RESOLV_SOURCE_PORT_DEFUALT;
	   int resol_delay;

       bool ip_scan_import;
       std::vector<std::string> result;
       const char* path_ips;

	   bool custom_ping;
	   int ping_timeout;
	   int threads_ping;
	   bool custom_threads;
	   int ping_log = PING_LOG_DEFAULT;

	   bool ack_ping;
	   bool syn_ping;
	   bool echo_ping;
	   bool info_ping;
	   bool timestamp_ping;
	   bool max_ping;

	   int ack_dest_port = ACK_PING_DEFAULT_DEST_PORT;
	   int syn_dest_port = SYN_PING_DEFAULT_DEST_PORT;

	   std::unordered_map<std::string,double> rtts;

	   /*Don`t touch*/
	   int error_fuck;
       bool print_help_menu;
       int threads_temp;
       std::string ports_temp;
	   double ping_duration;
	   double dns_duration;
	   double scan_duration;
	   double proc_duration;

	   std::unordered_map<std::string, std::vector<int>> success_target;
	   std::unordered_map<std::string, std::vector<int>> error_target;
	   std::unordered_map<std::string, std::vector<int>> filtered_target;
	   std::unordered_map<std::string, std::vector<int>> open_or_filtered_target;
	   std::unordered_map<std::string, std::vector<int>> no_filtered_target;
	   std::unordered_map<std::string, std::vector<int>> closed_target;

	   std::unordered_map<std::string, std::string> dns_completed;
	   std::unordered_map<std::string, std::string> http_requests;

       bool thread_on_port;
	   bool info_version;

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

	   std::string path_ftp_login = PATH_FTP_LOGIN_DEFAULT;
	   std::string path_ftp_pass = PATH_FTP_PASS_DEFAULT;
	   std::string path_sftp_login = PATH_SFTP_LOGIN_DEFAULT;
	   std::string path_sftp_pass = PATH_SFTP_PASS_DEFAULT;
	   std::string path_rtsp_login = PATH_RTSP_LOGIN_DEFAULT;
	   std::string path_rtsp_pass = PATH_RTSP_PASS_DEFAULT;
	   std::string path_http_login = PATH_HTTP_LOGIN_DEFAULT;
	   std::string path_http_pass = PATH_HTTP_PASS_DEFAULT;
	   std::string path_hikvision_login = PATH_HIKVISION_LOGIN_DEFAULT;
	   std::string path_hikvision_pass = PATH_HIKVISION_PASS_DEFAULT;
	   std::string path_smtp_login = PATH_SMTP_LOGIN_DEFAULT;
	   std::string path_smtp_pass = PATH_SMTP_PASS_DEFAULT;
	   std::string path_rvi_login = PATH_RVI_LOGIN_DEFAULT;
	   std::string path_rvi_pass = PATH_RVI_PASS_DEFAULT;

       int brute_timeout_ms;
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
