#ifndef CALLBBACKS_H
#define CALLBBACKS_H
#include <iostream>

size_t 
write_callback(char* ptr, size_t size, size_t nmemb, void* userdata);
size_t 
clear_callback(void *buffer, size_t size, size_t nmemb, void *userp);

#endif
