/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef GENERATION_H
#define GENERATION_H

#include <iostream>
#include <random>
#include <cstring>
#include <sstream>

std::string 
generate_random_str(int len, std::string dictionary);

const char* 
generate_ipv6(int num_octets);

const char* 
generate_ipv4(void);

unsigned int
generate_seq(void);

int
generate_port(void);

int
generate_ttl(void);
#endif
