#include "include/callbacks.h"

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    return size * nmemb;
}

size_t write_callback_plus(char* buf, size_t size, size_t nmemb, void* up){
    size_t realsize = size * nmemb;
    std::string* str = (std::string*) up;
    str->append(buf, realsize);
    return realsize;
}

size_t write_callback_http(char* ptr, size_t size, size_t nmemb, void* userdata){
    ((std::string*)userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp){
    return size * nmemb;
}

size_t clear_callback(void *buffer, size_t size, size_t nmemb, void *userp){
    return size * nmemb;
}

size_t write_callback_ssh(void* ptr, size_t size, size_t nmemb, std::string* data){
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}
