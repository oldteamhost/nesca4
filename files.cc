#include "include/files.h"
#include <fstream>

#ifdef _WIN32
#include <string>
#endif

int get_count_lines(const char* path){
    std::ifstream file(path);
    int count = 0;
    std::string line;

    while (std::getline(file, line)) {
        ++count;
    }

    return count;
}

bool check_file(const char* path){
    std::ifstream file(path);
    return file.good();
}

std::vector<std::string>write_file(const std::string& filename){
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

int write_line(std::string path, std::string line){
    std::ofstream outfile;
    outfile.open(path, std::ios_base::app);
    if (!outfile.is_open()){
        return -1;
    }
    outfile << line << std::endl;

    if (outfile.fail()){
         return -2;
    }

    outfile.close();
    if (outfile.fail()){
        return -3;
    }
    return 0;
}

