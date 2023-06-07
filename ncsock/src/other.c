#include <stdio.h>
#include <sys/time.h>
#include "../include/other.h"

struct timeval 
calculate_timeout_in_ms(int timeout_ms){
    struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;
    return timeout;
}
