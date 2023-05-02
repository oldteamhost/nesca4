#include "include/prints.h"
#include "include/other.h"
#include <string>
#include <fstream>
#include <map>

void nesca_prints::disable_colors(void){
    gray_nesca = "";
    golder_rod = "";
    sea_green = "";
    green_html = "";
    red_html = "";
    yellow_html = "";
    reset_color = "";
}

std::string nesca_prints::print_get_time(const char* time){
    std::string temp = "[" + std::string(time) + "]";
    return temp;
}

std::string nesca_prints::main_nesca_out(std::string opt, std::string result, int mode, std::string opt1, std::string opt2,
                                        std::string result1, std::string result2){
    std::string temp;
    if (mode == 0){
        temp = green_html + print_get_time(get_time()) + "[" + opt + "]:" + result + reset_color;
        std::cout << reset_color;
    }
    if (mode == 1){
        temp = red_html + print_get_time(get_time()) + "[" + opt + "]:" + result + reset_color;
    }
    else if (mode == 2){
        temp = yellow_html + print_get_time(get_time()) + "[" + opt + "]:" + result + reset_color;
    }
    else if (mode == 3){
        temp = gray_nesca + print_get_time(get_time()) + "[" + opt + "]:" + reset_color + 
        sea_green + result + reset_color + gray_nesca + " " + opt1 + ": " + reset_color +
        golder_rod + result1 + reset_color + gray_nesca + " " + opt2 + ": " + reset_color +
        golder_rod + result2 + reset_color;
    }
    else if (mode == 31){
        temp = print_get_time(get_time()) + "[" + opt + "]:" +
        result + " " + opt1 + ": " + result1 + " " + opt2 + ": " + result2;
    }
    return temp;
}

void nesca_prints::golder_rod_on(void){
    std::cout << golder_rod;
}

void nesca_prints::sea_green_on(void){
    std::cout << sea_green;
}

void nesca_prints::reset_colors(void){
    std::cout << reset_color;
}

int nesca_prints::import_color_scheme(const std::string file_name, std::map<std::string, std::string>& config_values){
    std::ifstream configFile(file_name);
    if (configFile.is_open())
    {
        std::string line;
        while (std::getline(configFile, line))
        {
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos)
            {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                config_values[key] = value;
            }
        }
        return 0;
    }
    return -1;
}

int nesca_prints::processing_color_scheme(const std::map<std::string, std::string> config_values){
    for (const auto& kvp : config_values)
    {
        if (kvp.first == "color1"){
            gray_nesca = "\033" + kvp.second;
        }
        else if (kvp.first == "color2"){
            golder_rod = "\033" + kvp.second;
        }
        else if (kvp.first == "color3"){
            sea_green = "\033" + kvp.second;
        }
        else if (kvp.first == "color4"){
            green_html = "\033" + kvp.second;
        }
        else if (kvp.first == "color5"){
            red_html = "\033" + kvp.second;
        }
        else if (kvp.first == "color6"){
            yellow_html = "\033" + kvp.second;
        }
    }
    return 0;
}
