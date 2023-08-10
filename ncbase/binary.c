/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "include/binary.h"

long get_file_size(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

unsigned char* binary_file(const char* file_name, size_t* file_size)
{
    FILE* file = fopen(file_name, "rb");
    if (!file)
    {
        perror("Failed to open file");
        return NULL;
    }

    long size = get_file_size(file);
    unsigned char* buffer = (unsigned char*)malloc(size);
    if (!buffer)
    {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, size, file);
    if (bytes_read != size)
    {
        perror("Failed to read file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    fclose(file);
    *file_size= (size_t)size;
    return buffer;
}
