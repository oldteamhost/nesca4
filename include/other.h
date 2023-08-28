/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
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
#include <cstdio>
#include <vector>
#include <filesystem>
#include "../include/files.h"
#include "../include/target.h"

const char* get_time(void);
std::string get_current_date(void);
void delay_ms(int milliseconds);
bool check_ansi_support(void);
std::vector<int> write_ports(std::string mode);
void logo(void);
std::vector<int> parse_range(const std::string& range_string);
bool check_root_perms();
int generate_port();
bool dns_or_ip(std::string &node);
std::string to_lower_case(std::string str);
size_t find_char(const std::string& str, char ch);
std::string parse_word(const std::vector<std::string>& options, const std::string& search_word);
int write_temp(const std::string& data, const std::string& file_name);

#endif
