/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "../include/services.h"

std::map<int,std::string>
services_nesca::parse_services(const std::string& filename){
    std::map<int, std::string> result;
    std::ifstream file(filename);

    if (!file){return result;}

    std::string line;

    while (std::getline(file, line)){
        std::istringstream lineIss(line);
        int key;
        std::string value;

        if (lineIss >> value >> key){result[key] = value;}
    }
    file.close();

    return result;
}

std::string
services_nesca::probe_service(int port){
    std::string service = data[port];
    if (service.empty()){return "N/A";}
    return data[port];
}

void
services_nesca::init_services(){
    data = parse_services("./resources/nesca-services");
}
