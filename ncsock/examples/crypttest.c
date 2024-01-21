/*
 * LIBNCSOCK & NESCA4 & CRYPTTEST
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "../include/sha256.h"
#include "../include/sha512.h"
#include "../include/md5.h"

#define SHA512M 1
#define SHA256M 2
#define MD5M    3

noreturn void usage(char** argv)
{
  printf("Usage: %s [string] [method(1,2,3)]\n", argv[0]);
  printf("Methods: [1](SHA512), [2](SHA256), [3](MD5)\n");
  exit(0);
}

int main(int argc, char **argv)
{
  char *temp = NULL;
  
    if (argc < 2 + 1)
    usage(argv);

  if (atoi(argv[2]) > 3)
    usage(argv);

  if (atoi(argv[2]) == MD5M)
    temp = md5str(argv[1], strlen(argv[1]));
  if (atoi(argv[2]) == SHA256M)
    temp = sha256str(argv[1], strlen(argv[1]));
  if (atoi(argv[2]) == SHA512M)
    temp = sha512str(argv[1], strlen(argv[1]));

  printf("encoded: %s\n", temp);
  
  if (temp)
    free(temp);

  return 0;
}
