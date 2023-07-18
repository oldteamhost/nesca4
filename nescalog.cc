/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/nescalog.h"
#include "include/other.h"
#include "include/html.h"
#include <string>
#include <unistd.h>
#include <vector>

html_output hou;

std::string 
nesca_prints::main_nesca_out(std::string opt, std::string result, int mode, std::string opt1, std::string opt2,
                                        std::string result1, std::string result2, std::string rtt, std::string type, std::string protocol){
	std::string temp, temp_file;
	char dots[3] = {':', ':', ':'};
    if (opt.empty()){dots[0] = ' '; }
    if (opt1.empty()){dots[1] = ' ';}
    if (opt2.empty()){dots[2] = ' ';}

    if (mode == 0) {
        temp = green_html + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + result + reset_color;
        temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[1] + result;
    }
    else if (mode == 1) {
        temp = red_html + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + result + reset_color;
        temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[1] + result;
    }
    else if (mode == 2) {
        temp = yellow_html + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + result + reset_color;
        temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[1] + result;
    }
    else if (mode == 3) {
        temp = gray_nesca + "[>][" + opt + "]" + dots[0] + reset_color +
            sea_green + result + reset_color + gray_nesca + " " + opt1 + dots[1] + " " + reset_color +
            golder_rod + result1 + reset_color + gray_nesca + " " + opt2 + dots[2] + " " + reset_color +
            golder_rod + result2 + reset_color;

        temp_file = "[>][" + opt + "]" + dots[0] +
            result + " " + opt1 + dots[1] + " " + result1 + " " + opt2 + dots[2] + " " + result2;

		if (html_save){hou.html_add_result(html_file_path,get_time(), result, result, "RTT", rtt+"ms", opt2, result2, opt1, result1, "SERVICE", protocol);}
    }
    else if (mode == 4) {
        temp = gray_nesca + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + reset_color +
            golder_rod + result + reset_color + gray_nesca + " " + opt1 + dots[1] + " " + reset_color +
            golder_rod + result1 + reset_color + gray_nesca + " " + opt2 + dots[2] + " " + reset_color +
            golder_rod + result2 + reset_color;

        temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[0] +
            result + " " + opt1 + dots[1] + " " + result1 + " " + opt2 + dots[2] + " " + result2;
		
    }
    else if (mode == 5) {
        temp = gray_nesca + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + reset_color +
            green_html + result + reset_color + gray_nesca + " " + opt1 + dots[1] + " " + reset_color +
            green_html + result1 + reset_color + gray_nesca + " " + opt2 + dots[2] + " " + reset_color +
            green_html + result2 + reset_color;

        temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[0] +
            result + " " + opt1 + dots[1] + " " + result1 + " " + opt2 + dots[2] + " " + result2;

    }

    if (save_file){write_line(file_path_save, temp_file + "\n");}

	return temp;
}
void
nesca_prints::nlog_packet_trace(std::string action, std::string protocol, std::string& source_ip,
				std::string& dest_ip, int source_port, int dest_port,
				std::string message, int ttl, int id, int win,
				int seq, int iplen){

	std::string temp = gray_nesca + print_get_time(get_time()) + reset_color +
            green_html + "  " + action + reset_color + green_html + "  " + protocol + "  " + reset_color +
            green_html + source_ip + ":" + std::to_string(source_port) + " > " + dest_ip + ":" +
			std::to_string(dest_port) + reset_color + golder_rod + message + reset_color +
			gray_nesca + "  TTL  " + golder_rod + std::to_string(ttl) + gray_nesca + "  ID  " + golder_rod +
			std::to_string(id) + gray_nesca + "  WINDOW  " + golder_rod + std::to_string(win) + gray_nesca +
			"  IPLEN  " + golder_rod + std::to_string(iplen) + gray_nesca + "  SEQ  " + golder_rod + std::to_string(seq) +reset_color;

	std::cout << temp << std::endl;

}

void 
nesca_prints::disable_colors(void){
    gray_nesca = "";
    golder_rod = "";
    sea_green = "";
    green_html = "";
    red_html = "";
    yellow_html = "";
    reset_color = "";
}

std::string 
nesca_prints::print_get_time(const char* time){
    std::string temp = "[" + std::string(time) + "]";
    return temp;
}

int 
nesca_prints::import_color_scheme(const std::string& file_name, std::map<std::string, std::string>& config_values){
    std::ifstream configFile(file_name);
    if (configFile.is_open()){
        std::string line;
        while (std::getline(configFile, line)){
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos){
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                config_values[key] = value;
            }
        }
        return 0;
    }
    return -1;
}

void
nesca_prints::golder_rod_on(void){std::cout << golder_rod;}

void 
nesca_prints::sea_green_on(void){std::cout << sea_green;}

void 
nesca_prints::reset_colors(void){std::cout << reset_color;}

void
nesca_prints::gray_nesca_on(void){std::cout << gray_nesca;}

void
nesca_prints::yellow_html_on(void){std::cout << yellow_html;}

void 
nesca_prints::green_html_on(void){std::cout << green_html;}

void 
nesca_prints::red_html_on(void){std::cout << red_html;}

int 
nesca_prints::processing_color_scheme(const std::map<std::string, std::string>& config_values){
	for (const auto& kvp : config_values) {
        if (kvp.first == "color1") {
            gray_nesca = "\033" + kvp.second;
        } else if (kvp.first == "color2") {
            golder_rod = "\033" + kvp.second;
        } else if (kvp.first == "color3") {
            sea_green = "\033" + kvp.second;
        } else if (kvp.first == "color4") {
            green_html = "\033" + kvp.second;
        } else if (kvp.first == "color5") {
            red_html = "\033" + kvp.second;
        } else if (kvp.first == "color6") {
            yellow_html = "\033" + kvp.second;
        }
    }
    return 0;
}

void 
nesca_prints::nlog_trivial(const std::string& message){
    std::string log = print_get_time(get_time()) + "[OK]:" + message;
    std::cout << green_html << log << reset_color;

    if (save_file)write_line(file_path_save, log);
}

void 
nesca_prints::nlog_error(const std::string& message){
    std::string log = print_get_time(get_time()) + "[ERROR]:" + message;
    std::cout << red_html << log << reset_color;

    if (save_file)write_line(file_path_save, log);
}

void
nesca_prints::nlog_custom(const std::string& auth, std::string message, int color){
    std::string log = print_get_time(get_time()) + "[" + auth + "]:" + message;

    if (color == 0){std::cout << green_html;}
    else if (color == 1){std::cout << yellow_html;}
    else if (color == 2){std::cout << red_html;}
    std::cout << log << reset_color;

    if (save_file)write_line(file_path_save, log);
}

