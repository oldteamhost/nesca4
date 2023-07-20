#include "include/mathutils.h"

int
calc_threads(int speed_type, int len){
	int sizes[] = {100, 500, 1000, 1500, 2000};
    int speeds[] = {1, 2, 3, 4, 5};
    int speed_type_index = speed_type - 1;
    int max_threads = (speed_type_index >= 0 && speed_type_index < 5) ? sizes[speed_type_index] : 0;
    return std::min(max_threads, len);
}

int
calc_timeout(int speed_type){
	int timeouts[] = {3000, 2000, 1000, 600, 400};
    int speed_type_index = speed_type - 1;
    return (speed_type_index >= 0 && speed_type_index < 5) ? timeouts[speed_type_index] : 0;
}

int
calc_port_timeout(int speed_type, int rtt_ping){
	int coefficients[] = {0, 5, 4, 3, 2, 1};
    if (speed_type < 1 || speed_type > 5){return rtt_ping;}
    return rtt_ping * coefficients[speed_type];
}
