/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/callbacks.h"

size_t 
write_callback(char* ptr, size_t size, size_t nmemb, void* userdata){return size * nmemb;}

size_t 
clear_callback(void *buffer, size_t size, size_t nmemb, void *userp){return size * nmemb;}

size_t
http_request(char* contents, size_t size, size_t nmemb, std::string* buffer){
	size_t totalSize = size * nmemb;
    buffer->append(contents, totalSize);
    return totalSize;
}
