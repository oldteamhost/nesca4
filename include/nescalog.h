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
	/*Цвета для лога.*/
    std::string gray_nesca = "\033[38;2;112;112;112m";
    std::string golder_rod = "\033[38;2;218;165;32m";
    std::string sea_green = "\033[38;2;60;179;113;4m";
    std::string green_html = "\033[38;2;45;235;65m";
    std::string red_html = "\033[38;2;240;50;55m";
    std::string yellow_html = "\033[38;2;240;215;75m";
    std::string reset_color = "\033[0m";

    public:
		bool save_file;
		bool html_save;
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

        int /*Импортирование кастомных цветов.*/
        import_color_scheme(const std::string& file_name, std::map<std::string, std::string>& config_values);

        int /*Парсинг кастомных цвето.*/
        processing_color_scheme(const std::map<std::string, std::string>& config_values);

        std::string /*Для времени.*/
        print_get_time(const char* time);
};

#endif

