/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#ifndef ROBOTS_H
#define ROBOTS_H
#include <iostream>

std::string
get_robots_txt(const std::string& ip, int port);

std::string
get_sitemap_xml(const std::string& ip, int port);
#endif
