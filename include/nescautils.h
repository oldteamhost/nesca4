/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#ifndef NESCA_UTILS_H
#define NESCA_UTILS_H

#include <iostream>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <random>
#include <assert.h>
#include <cstdio>
#include <vector>
#include <filesystem>
#include "../include/nescadata.h"
#include "../config/compile.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

class services_nesca {
  private:
    std::map<int,std::string>
    parse_services(const std::string& filename);

  public:
    std::map<int,std::string> data;
    void init_services(void);
    std::string probe_service(int port);
};

int get_log(int total);
bool check_ansi_support(void);
std::vector<int> write_ports(std::string mode);
void logo(void);
std::string gettypeddos(class arguments_program& argp);
std::vector<int> parse_range(const std::string& range_string);
bool __check_root_perms();
std::string to_lower_case(std::string str);
bool hikvision_screenshot(const std::string& ip, const long user_id, const NET_DVR_DEVICEINFO_V40 device, const std::string& path);
size_t find_char(const std::string& str, char ch);
std::string parse_word(const std::vector<std::string>& options, const std::string& search_word);
int write_temp(const std::string& data, const std::string& file_name);
std::unordered_map<std::string, std::string>
get_negatives(const std::string& file_path);
std::vector<std::string>
write_file(const std::string& filename);
int write_line(std::string, std::string line);
bool check_file(const char* path);
int get_count_lines(const char* path);
int delete_line_from_file(const std::string& filename, const std::string& line_to_delete);

#endif

