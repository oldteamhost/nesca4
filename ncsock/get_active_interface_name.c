/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/utils.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define MAX_INTERFACE_NAME_LEN 512
char* get_active_interface_name(char* buffer, size_t len)
{
  DIR *dir;
  struct dirent *entry;
  char interface_path[MAX_INTERFACE_NAME_LEN];
  FILE *operstate_file;
  char operstate[16];

  dir = opendir("/sys/class/net");
  if (!dir)
    return NULL;

  while ((entry = readdir(dir))) {
    if (entry->d_type == DT_LNK && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      snprintf(interface_path, sizeof(interface_path), "/sys/class/net/%s/operstate", entry->d_name);
      operstate_file = fopen(interface_path, "r");
      if (operstate_file) {
        if (fgets(operstate, sizeof(operstate), operstate_file) != NULL) {
          if (strcmp(operstate, "up\n") == 0) {
            closedir(dir);
            fclose(operstate_file);

            if (strlen(entry->d_name) < len) {
              strcpy(buffer, entry->d_name);
              return buffer;
            }
            return NULL;
          }
        }
        fclose(operstate_file);
      }
    }
  }

  closedir(dir);
  return NULL;
}
