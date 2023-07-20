#ifndef MATHUTILS_H 
#define MATHUTILS_H
#include <algorithm>

int /*Функция для расчёта количества поток на основе скорости.*/
calc_threads(int speed_type, int len);

int /*Функция для расчёта таймаута, на основе скорости.*/
calc_timeout(int speed_type);

int /*Функция для расчёта таймаута, на основе скорости для сканирования.*/
calc_port_timeout(int speed_type, int rtt_ping);

#endif
