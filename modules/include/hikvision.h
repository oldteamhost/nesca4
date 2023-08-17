/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#ifndef HIKVISION_H 
#define HIKVISION_H 
#include "../../config/compile.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

bool hikvision_screenshot(const std::string& ip, const long user_id, const NET_DVR_DEVICEINFO_V40 device, const std::string& path);

#endif

