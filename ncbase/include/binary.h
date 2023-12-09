/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#ifndef BINARY_H 
#define BINARY_H 
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

long get_file_size(FILE* file);
unsigned char* binary_file(const char* file_name, size_t* file_size);

#ifdef __cplusplus
}
#endif

#endif

