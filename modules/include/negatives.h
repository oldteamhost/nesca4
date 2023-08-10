/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#ifndef NEGATIVES_H 
#define NEGATIVES_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

class nesca_negatives{
public:
	std::unordered_map<std::string, std::string> nesca_negatives;

	std::unordered_map<std::string, std::string>
	parse_config_file(const std::string& file_path);
};


#endif
