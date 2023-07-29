/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef SERVICES_H
#define SERVICES_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class services_nesca{
private:
    std::map<int,std::string>
    parse_services(const std::string& filename);
public:
    std::map<int,std::string> data;

    void
    init_services();

    std::string
    probe_service(int port);
     
};
#endif
