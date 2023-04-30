#include "include/other.h"
#include "include/target.h"
#include <iostream>

const char* get_time(){
    time_t rawtime;
    struct tm * timeinfo;
    static char time_str[9];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(time_str, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return time_str;
}


bool check_ansi_support(void){
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return false;
    }

    if (dwMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)
    {
        return true;
    }

    return false;
    #else
    const char* envValue = std::getenv("TERM");
    if (envValue == nullptr)
    {
        return false;
    }

    return std::string(envValue).find("xterm") != std::string::npos;
    #endif
}

void delay_ms(int milliseconds){
#ifdef _WIN32
    Sleep(milliseconds);
#else
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#endif
}

std::vector<int> write_ports(std::string mode){
    std::vector<int> temp;
    if (mode == "all" || mode == "ALL" || mode == "0"){
        for (int i = 0; i < 65536; i++) {
            temp.push_back(i);
        }
        return temp;
    }
    else if (mode == "nesca" || mode == "NESCA" || mode == "1" || mode == "nesca3"){
        temp = {80,81,88,8080,8081,60001,60002,8008,8888,554,9000,3536,21};
        return temp;
    }
    else if (mode == "top100" || mode == "TOP100" || mode == "2"){
        temp = {80, 443, 22, 21, 25, 3389, 110, 143, 53, 445, 139, 3306, 8080, 
               1723, 111, 995, 993, 5900, 1025, 587, 8888, 199, 1720, 465, 548, 113, 81,
               6001, 10000, 514, 5060, 179, 1026, 23, 8443, 8000, 444, 1433, 1900, 2001,
               1027, 49152, 2049, 1028, 1029, 5901, 32768, 1434, 3283, 5800, 389, 53, 17988,
               106, 5666, 1725, 465, 995, 548, 7, 123, 389, 113, 37, 427, 8001, 427, 1726,
               49153, 2002, 515, 1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039,
               1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049, 1050, 1051, 1052,
               1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061, 1062, 1063, 1064, 1065,
               1066, 1067, 1068, 1069, 1070, 1071, 1072, 1073, 1074, 1075, 1076, 1077};
        return temp;
    }
    else if (mode == "top50" || mode == "TOP50" || mode == "3"){
        temp  = {80, 443, 22, 21, 25, 3389, 110, 143, 53, 445, 139, 3306, 8080, 1723,
                     111, 995, 993, 5900, 1025, 587, 8888, 199, 1720, 465, 548, 113, 81, 6001, 10000,
                     514, 5060, 179, 1026, 23, 8443, 8000, 444, 1433, 1900, 2001, 1027, 49152,
                     2049, 1028, 1029, 5901, 32768, 1434, 3283}; 
        return temp;
    }
    return {-1};
}

void logo(void){
    std::cout << "d8b   db d88888b .d8888.  .o88b.  .d8b.         j88D  \n";
    std::cout << "888o  88 88'     88'  YP d8P  Y8 d8' `8b       j8~88  \n"; 
    std::cout << "88V8o 88 88ooooo `8bo.   8P      88ooo88      j8' 88  \n";
    std::cout << "88 V8o88 88~~~~~   `Y8b. 8b      88~~~88      V88888D \n";
    std::cout << "88  V888 88.     db   8D Y8b  d8 88   88          88  \n";
    std::cout << "VP   V8P Y88888P `8888Y'  `Y88P' YP   YP          VP  \n";
    std::cout << std::endl;
}
