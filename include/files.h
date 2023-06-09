/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

// read and write all file
std::vector<std::string>
write_file(const std::string& filename);
// write one line
int 
write_line(std::string, std::string line);
// check file 
bool 
check_file(const char* path);
// get count lines
int 
get_count_lines(const char* path);

int
delete_line_from_file(const std::string& filename,
		const std::string& line_to_delete);

#endif
