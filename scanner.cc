#include "include/scanner.h"

checking_finds cf;

std::string 
checking_finds::check_basic_auth(std::string ip){
    bool status = false;

    for (auto& path : cf.basic_auth_paths){
        size_t pos = ip.find(path);
        if (pos != std::string::npos){
            status = true;
            return path;
        }
    }
    return "no";
}
