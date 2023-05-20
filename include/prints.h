#ifndef PRINTS_H
#define PRINTS_H

#include <iostream>
#include <map>
#include <vector>

class nesca_prints{
    private:
        std::string gray_nesca = "\033[38;2;112;112;112m";
        std::string golder_rod = "\033[38;2;218;165;32m";
        std::string sea_green = "\033[38;2;60;179;113;4m";
        std::string green_html = "\033[38;2;45;235;65m";
        std::string red_html = "\033[38;2;240;50;55m";
        std::string yellow_html = "\033[38;2;240;215;75m";
        std::string reset_color = "\033[0m";
    public:
        std::map<std::string, std::string> config_values;
        int 
        no_color_txt;
        void 
        disable_colors(void);
        void
        golder_rod_on(void);
        void 
        sea_green_on(void);
        void 
        reset_colors(void);
        int 
        import_color_scheme(const std::string file_name, std::map<std::string, std::string>& config_values);
        int 
        processing_color_scheme(const std::map<std::string, std::string> config_values);
        std::string 
        print_get_time(const char* time);
        std::string 
        main_nesca_out(std::string opt, std::string result, int mode, std::string opt1, std::string opt2,
                std::string result1, std::string result2);

        bool save_file;
        const char* file_path_save;

        void 
        nlog_trivial(std::string message);
        void 
        nlog_error(std::string message);
        void 
        nlog_result(std::string message);
        void
        nlog_custom(std::string auth, std::string message, int color);
};

#endif

