#include <iostream>
#include <vector>

// read and write all file
std::vector<std::string> write_file(const std::string& filename);
// write one line
int write_line(std::string, std::string line);
// check file 
bool check_file(const char* path);
// get count lines
int get_count_lines(const char* path);
