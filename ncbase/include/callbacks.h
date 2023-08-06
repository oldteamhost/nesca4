/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef CALLBBACKS_H
#define CALLBBACKS_H
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t 
write_callback(char* ptr, size_t size, size_t nmemb, void* userdata);
size_t 
clear_callback(void *buffer, size_t size, size_t nmemb, void *userp);

#ifdef __cplusplus
}
#endif

#endif
