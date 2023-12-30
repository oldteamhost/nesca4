/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"

u8 *hexbin(char *str, size_t *outlen)
{
  char auxbuff[1024];
  static u8 dst[16384];
  size_t dstlen=16384;
  char *start=NULL;
  char twobytes[3];
  u32 i = 0, j = 0;

  if (str == NULL || outlen == NULL)
    return NULL;
  if (strlen(str) == 0)
    return NULL;
  else
    memset(auxbuff,0,1024);
  if (!strncmp("0x", str, 2)) {
    if (strlen(str) == 2)
      return NULL;
    start=str+2;
  }
  else if(!strncmp("\\x", str, 2)) {
    if (strlen(str) == 2)
      return NULL;
    for (i = 0; i < strlen(str) && j<1023; i++) {
      if(str[i]!='\\' && str[i]!='x' && str[i]!='X')
        auxbuff[j++] = str[i];
    }
    auxbuff[j]='\0';
    start=auxbuff;
  }
  else
    start=str;
  for (i = 0; i < strlen(start); i++){
    if (!isxdigit(start[i]))
      return NULL;
  }
  if (strlen(start) % 2 != 0)
    return NULL;
  for (i = 0, j = 0; j < dstlen && i < strlen(start)- 1; i += 2) {
    twobytes[0] = start[i];
    twobytes[1] = start[i+1];
    twobytes[2] = '\0';
    dst[j++] = (u8)strtol(twobytes, NULL, 16);
  }

  *outlen=j;
  return dst;
}
