/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "include/negatives.h"

std::unordered_map<std::string, std::string>
nesca_negatives::parse_config_file(const std::string& file_path){
	std::unordered_map<std::string, std::string> config_dict;
    
    std::ifstream file(file_path);
    std::string line;
    
    while (std::getline(file, line))
	{
        /*Игнорируем пустые строки и строки-комментарии*/
        if (line.empty() || line.substr(0, 2) == "//"){continue;}
        
        std::stringstream ss(line);
        std::string value, type;
        
        /*Используем разделитель '|' для разделения значения и типа*/
        if (std::getline(ss, value, '|') && std::getline(ss, type))
		{
            value = value.substr(value.find_first_not_of(' '));
            value = value.substr(0, value.find_last_not_of(' ') + 1);
            
            type = type.substr(type.find_first_not_of(' '));
            type = type.substr(0, type.find_last_not_of(' ') + 1);
            config_dict[value] = type;
        }
    }
    
    file.close();
    return config_dict;
}
