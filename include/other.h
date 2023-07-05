/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef OTHER_H
#define OTHER_H
#include <vector>
#include <iostream>
#include <regex>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <random>

#include "../include/target.h"

const char* 
get_time();

int
write_temp(const std::string& data);

std::string
get_current_date();

void 
delay_ms(int milliseconds);

bool 
check_ansi_support(void);

std::vector<int> 
write_ports(std::string mode);

void 
logo(void);

std::vector<int> 
parse_range(const std::string& range_string);

bool 
check_root_perms();

std::string
parse_word(const std::vector<std::string>& options,
		   const std::string& search_word);

int
generate_port();

bool 
dns_or_ip(std::string &node);

#endif
