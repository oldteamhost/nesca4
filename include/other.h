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

bool 
dns_or_ip(std::string &node);

int
generate_port();

#endif
