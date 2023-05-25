#include "../include/scanner.h"
#include "../include/networktool.h"
#include <cerrno>
#include <vector>

checking_finds cf;

int 
dns_scan(std::string domain, std::string domain_1level){
    std::string result = domain + domain_1level;
     double response_time = 20;
     if (response_time != -1){
         if (response_time != 2){
             if (response_time != EOF){
                 return 1; // success
             }
         }
     }
     else {
         return 0; // failed
     }

    return -1; // error
}

std::string 
checking_finds::check_axis_camera(std::string ip){
    bool status = false;

    for (auto& path : cf.axis_path){
        size_t pos = ip.find(path);
        if (pos != std::string::npos){
            status = true;
            return path;
        }
    }
    return "no";
}

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
