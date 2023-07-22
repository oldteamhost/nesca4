/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef PRINTS_H
#define PRINTS_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <map>

#include "../include/other.h"
#include "../include/files.h"

enum log_level{
	OK,
    INFO,
    WARNING,
    ERROR,
	MAIN,
	MAIN_OLD
};

struct log_enty{
    std::string option;
    std::string result;
    std::string option1;
    std::string result1;
    std::string option2;
    std::string result2;
};

class nesca_prints{
private:
	/*Дефолтные цвета для лога.*/ 
    std::string gray_nesca = "\033[38;2;107;107;107m";
    std::string golder_rod = "\033[38;2;218;165;32m";
    std::string sea_green = "\033[38;2;60;179;96;4m";
    std::string green_html = "\033[38;2;127;255;0m";
    std::string red_html = "\033[38;2;240;50;55m";
    std::string yellow_html = "\033[38;2;255;255;0m";
    std::string reset_color = "\033[0m";

	std::string /*Преобразование HTML цвета в ANSI 256colors*/
	html_to_ansi_color(const std::string& html_color);

    public:
		bool save_file;
		bool html_save;
		bool colors = true;
        std::map<std::string, std::string> config_values;
		std::string file_path_save;
		std::string html_file_path;

		/*Создание класса*/
		void
		run_log();


		std::string /*Главный лог.*/
		main_nesca_out(std::string opt, std::string result, int mode, std::string opt1, std::string opt2,
                        std::string result1, std::string result2, std::string rtt, std::string type = "n/a", std::string protocol = "n/a");

		/*Другие логи.*/
        void
        nlog_trivial(const std::string& message);
        void
        nlog_error(const std::string& message);
        void 
        nlog_result(const std::string& message);
        void
        nlog_custom(const std::string& auth, std::string message, int color);
        void
        nlog_packet_trace(std::string action, std::string protocol, std::string& source_ip,
				std::string& dest_ip, int source_port, int dest_port,
				std::string message, int ttl, int id, int win, int seq, int iplen);

		/*Включение выключение цветов.*/
        void 
        disable_colors(void);
        void
        golder_rod_on(void);
        void 
        sea_green_on(void);
        void 
        reset_colors(void);
        void 
        green_html_on(void);
	    void
	    gray_nesca_on(void);
	    void
	    yellow_html_on(void);
        void 
        red_html_on(void);

		void /*Включить кастомный цвет.*/
		custom_color_on(const std::string& html_color);

        int /*Импортирование кастомных цветов.*/
        import_color_scheme(const std::string& file_name, std::map<std::string, std::string>& config_values);

        int /*Парсинг кастомных цвето.*/
        processing_color_scheme(const std::map<std::string, std::string>& config_values);

        std::string /*Для времени.*/
        print_get_time(const char* time);
};

#endif

