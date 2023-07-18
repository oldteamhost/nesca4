/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/generation.h"

const char*
generate_ipv6(int num_octets){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 65535);

    static char ip[40];
    std::stringstream ss;
    for (int i = 0; i < num_octets; i++) {
        ss << std::hex << distrib(gen);
        if (i < num_octets - 1) ss << ":";
    }
    std::string ip_str = ss.str();
    std::strcpy(ip, ip_str.c_str());
    return ip;
}

const char*
generate_ipv4(void){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);

    static char ip[16];
    std::stringstream ss;
    for (int i = 0; i < 4; i++) {
        ss << distrib(gen);
        if (i < 3) ss << ".";
    }
    std::string ip_str = ss.str();
    std::strcpy(ip, ip_str.c_str());
    return ip;
}

std::string
generate_random_str(int len, std::string dictionary){
    std::string result;
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(0, dictionary.length() - 1);
    for (int i = 0; i < len; i++){result += dictionary[dist(engine)];}
    return result;
}

unsigned int
generate_seq(void){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(0, 4294967295);
    unsigned int seq_res = dis(gen);
    return seq_res;
}

unsigned int
generate_ident(void){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(0, 65535);
    unsigned int seq_res = dis(gen);
    return seq_res;
}

int
generate_port(void){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(49151, 65535);
    int result = dist(gen);
    return result;
}

int
generate_ttl(void){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(31, 64);
    int result = dist(gen);
    return result;

}
