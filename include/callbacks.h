#ifndef CALLBBACKS_H
#define CALLBBACKS_H

#include <iostream>

size_t write_callback_headers(char *ptr, size_t size, size_t nmemb, void *userdata);
size_t write_callback_request(char* buf, size_t size, size_t nmemb, void* up);
size_t write_callback_auth(char* buf, size_t size, size_t nmemb, void* userdata);
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata);
size_t write_callback_ssh(void* ptr, size_t size, size_t nmemb, std::string* data);
size_t write_callback_plus(char* buf, size_t size, size_t nmemb, void* up);
size_t write_callback_http(char* ptr, size_t size, size_t nmemb, void* userdata);
size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp);
size_t clear_callback(void *buffer, size_t size, size_t nmemb, void *userp);

#endif
