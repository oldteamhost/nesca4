/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/other.h"

const char*
get_time()
{
    time_t rawtime;
    struct tm * timeinfo;
    static char time_str[9];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(time_str, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return time_str;
}

std::string get_current_date()
{
    std::time_t current_time = std::time(nullptr);
    std::tm* local_time = std::localtime(&current_time);
    
    const int year = local_time->tm_year + 1900;
    const int month = local_time->tm_mon + 1;
    const int day = local_time->tm_mday;
    
    const std::string formatted_date = std::to_string(year) + "-" +
                                (month < 10 ? "0" : "") + std::to_string(month) + "-" +
                                (day < 10 ? "0" : "") + std::to_string(day);
    
    return formatted_date;
}

bool
check_ansi_support(void)
{
    const char* envValue = std::getenv("TERM");
    if (envValue == nullptr) {return false;}

    return std::string(envValue).find("xterm") != std::string::npos;
}

#ifdef _WIN32
void delay_ms(int milliseconds){Sleep(milliseconds);}
#else
void delay_ms(int milliseconds)
{
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
}
#endif


std::vector<int>
write_ports(std::string mode)
{
    std::vector<int> temp;
    std::transform(mode.begin(), mode.end(), mode.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    if (mode == "all"){
        for (int i = 0; i < 65536; i++) {temp.push_back(i);}
        return temp;
    }
    else if (mode == "nesca" || mode == "nesca3"){
		/*On https://github.com/cora32/Nesca/blob/master/resource.h*/
        temp = {80,81,88,8080,8081,60001,60002,8008,8888,554,9000,441,4111,6667,3536,22,21};
        return temp;
    }
    else if (mode == "top100"){
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
    else if (mode == "top50"){
        temp  = {80, 443, 22, 21, 25, 3389, 110, 143, 53, 445, 139, 3306, 8080, 1723,
                     111, 995, 993, 5900, 1025, 587, 8888, 199, 1720, 465, 548, 113, 81, 6001, 10000,
                     514, 5060, 179, 1026, 23, 8443, 8000, 444, 1433, 1900, 2001, 1027, 49152,
                     2049, 1028, 1029, 5901, 32768, 1434, 3283}; 
        return temp;
    }
    else if (mode == "http"){
        temp = {80,81,8080,8081,8888, 8008};
        return temp;
    }
    else if (mode == "nesca4"){
        temp = {80,81,8080,8081,8888,8008,21,22,8000,37777};
        return temp;
    }

    return {-1};
}

void logo(void)
{
    puts("d8b   db d88888b .d8888.  .o88b.  .d8b.         j88D  ");
    puts("888o  88 88'     88'  YP d8P  Y8 d8' `8b       j8~88  "); 
    puts("88V8o 88 88ooooo `8bo.   8P      88ooo88      j8' 88  ");
    puts("88 V8o88 88~~~~~   `Y8b. 8b      88~~~88      V88888D ");
    puts("88  V888 88.     db   8D Y8b  d8 88   88          88  ");
    puts("VP   V8P Y88888P `8888Y'  `Y88P' YP   YP          VP  \n");
}

std::vector<int>
parse_range(const std::string& range_string)
{
    std::vector<int> result;
    int start = 0, end = 0;
    bool found_dash = false;
    for (char c : range_string) {
        if (c == '-') {
            found_dash = true;
            start = std::stoi(range_string.substr(0, end));
            end = std::stoi(range_string.substr(end + 1));
        }
        ++end;
    }
    if (!found_dash) {return result;}
    for (int i = start; i <= end; ++i) {result.push_back(i);}

    return result;
}

#ifdef _WIN32
bool check_root_perms() 
{
	BOOL is_admin = FALSE;
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdminGroup;
	if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdminGroup)){
    	if (!CheckTokenMembership(NULL, AdminGroup, &is_admin))
        	is_admin = FALSE;
    	FreeSid(AdminGroup);
	}
	return (is_admin != 0);
}
#else
bool check_root_perms() {return (geteuid() == 0);}
#endif


bool 
dns_or_ip(std::string &node)
{
	struct sockaddr_in sa;
    return (inet_pton(AF_INET, node.c_str(), &(sa.sin_addr)) == 0);
}

int
write_temp(const std::string& data)
{
	const std::vector<std::string> temp = write_file("resources/data");
	for (auto& str : temp) {
        if (str == data) {return -1;}
    }
	if (temp.size() > 2000){
		std::filesystem::path file_path("resources/data");
        std::filesystem::remove(file_path);
	}
	const int write = write_line("resources/data", data + "\n");
	if (write != 0) {return -1;}

	return 0;
}

std::string
parse_word(const std::vector<std::string>& options,
		   const std::string& search_word)
{
	for (const std::string& option : options) 
	{
		if (option == search_word) {return option;}
    }
    return "failed";
}

std::string
to_lower_case(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {return std::tolower(c);});
    return str;
}

size_t 
find_char(const std::string& str, char ch)
{
	return str.find(ch);
}

