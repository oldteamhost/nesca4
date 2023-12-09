/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "include/binary.h"

long get_file_size(FILE* file)
{
  long size;

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  return size;
}

unsigned char* binary_file(const char* file_name, size_t* file_size)
{
  FILE* file = fopen(file_name, "rb");
  if (!file)
    return NULL;

  long size = get_file_size(file);
  unsigned char* buffer = (unsigned char*)malloc(size);
  if (!buffer)
    goto fail;

  size_t bytes_read = fread(buffer, 1, size, file);
  if (bytes_read != size) {
    free(buffer);
    goto fail;
  }

  fclose(file);
  *file_size= (size_t)size;
  return buffer;

fail:
  fclose(file);
  return NULL;
}
