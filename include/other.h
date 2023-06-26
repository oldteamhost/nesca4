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

// get now tim
const char* 
get_time();

// custom delay
void 
delay_ms(int milliseconds);

// check ansii colors
bool 
check_ansi_support(void);

// write ports
std::vector<int> 
write_ports(std::string mode);

// print help menu
void 
logo(void);

// range ports
std::vector<int> 
parse_range(const std::string& range_string);

// check root
bool 
check_root_perms();

// check dns or ip
bool 
dns_or_ip(std::string &node);

// random port
int
generate_port();

#endif
