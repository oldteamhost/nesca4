#ifndef GENERATION_H
#define GENERATION_H

#include <iostream>
#include <random>
#include <cstring>
#include <sstream>

// random str
std::string 
generate_random_str(int len, std::string dictionary);
// random ipv6
const char* 
generate_ipv6(int num_octets);
// random ipv4
const char* 
generate_ipv4(void);

#endif
