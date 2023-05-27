#include "../include/callbacks.h"
#include <sstream>
#include <iomanip>

size_t 
write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    return size * nmemb;
}

size_t 
clear_callback(void *buffer, size_t size, size_t nmemb, void *userp){
    return size * nmemb;
}
