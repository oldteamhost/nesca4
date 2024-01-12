/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "include/json.h"

/*
[
    {
        "ip_address": "192.168.1.1",
        "details": {
            "dns_name": "example.com",
            "rtt": 10.5,
            "ports": [
                {
                    "protocol": "HTTP",
                    "passwd": "secret",
                    "http_title": "Welcome Page",
                    "port": 80
                },
                {
                    "protocol": "HZ",
                    "passwd": "anothersecret",
                    "http_title": "Alternate Page",
                    "port": 123
                }
            ]
        }
    }
]
*/

int
nesca_json_save_host(const char* filename, const struct nesca_host_details* host_data)
{
  FILE* file = fopen(filename, "a");
  if (file) {
      fprintf(file, "    {\n");
      fprintf(file, "        \"ip_address\": \"%s\",\n", host_data->ip_address);
      fprintf(file, "        \"details\": {\n");
      fprintf(file, "            \"dns_name\": \"%s\",\n", host_data->dns_name);
      fprintf(file, "            \"rtt\": %lf,\n", host_data->rtt);
      fprintf(file, "            \"ports\": [\n");
      fclose(file);
      return 0;
  }
  return -1;
}

int
nesca_json_set_comma(const char *filename)
{
  FILE* file = fopen(filename, "a");
  if (file) {
    fprintf(file, ",");
    fclose(file);
    return 0;
  }
  return -1;
}

int
nesca_json_skip_line(const char *filename)
{
  FILE* file = fopen(filename, "a");
  if (file) {
    fprintf(file, "\n");
    fclose(file);
    return 0;
  }
  return -1;
}

int
nesca_json_save_port(const char* filename, const struct nesca_port_details* port_data)
{
  FILE* file = fopen(filename, "a");
  if (file) {
    fprintf(file, "                {\n");
    fprintf(file, "                    \"port\": %u,\n", port_data->port);
    fprintf(file, "                    \"protocol\": \"%s\",\n", port_data->protocol);
    if (*port_data->http_title != '\0')
      fprintf(file, "                    \"http_title\": \"%s\",\n", port_data->http_title);
    if (*port_data->screenshot != '\0')
      fprintf(file, "                    \"screenshot\": \"%s\",\n", port_data->screenshot);
    if (*port_data->type_target != '\0')
      fprintf(file, "                    \"type_target\": \"%s\",\n", port_data->type_target);
    if (*port_data->content!= '\0')
      fprintf(file, "                    \"content\": \"%s\",\n", port_data->content);
    fprintf(file, "                    \"passwd\": \"%s\"\n", port_data->passwd);
    fprintf(file, "                }");
    fclose(file);
    return 0;
  }
  return -1;
}

int
nesca_json_close_info(const char *filename)
{
  FILE* file = fopen(filename, "a");
  if (file) {
    fprintf(file, "\n            ]\n");
    fprintf(file, "        }\n");
    fprintf(file, "    }");
    fclose(file);
    return 0;
  }

  return -1;
}

int
nesca_json_start_array(const char *filename)
{
  FILE* file = fopen(filename, "a");
  if (file) {
    fprintf(file, "[\n");
    fclose(file);
    return 0;
  }

  return -1;
}

int
nesca_json_close_array(const char *filename)
{
  FILE* file = fopen(filename, "a");
  if (file) {
    fprintf(file, "]");
    fclose(file);
    return 0;
  }

  return -1;
}

int
nesca_json_fix_file(const char* filename)
{
  FILE *inputFile = fopen(filename, "r");
  if (inputFile == NULL) {
    perror("Failed to open input file");
    return 1;
  }

  fseek(inputFile, 0, SEEK_END);
  long fileSize = ftell(inputFile);
  rewind(inputFile);

  char *jsonContent = (char *)malloc(fileSize + 1);
  if (jsonContent == NULL) {
    perror("Memory allocation failed");
    fclose(inputFile);
    return 1;
  }

  fread(jsonContent, 1, fileSize, inputFile);
  jsonContent[fileSize] = '\0';

  fclose(inputFile);

  char *lastCommaPos = strrchr(jsonContent, ',');
  if (lastCommaPos != NULL) {
    *lastCommaPos = '\0';
  }

  FILE *outputFile = fopen(filename, "w");
  if (outputFile == NULL) {
    perror("Failed to open output file");
    free(jsonContent);
    return 1;
  }

  fprintf(outputFile, "%s", jsonContent);
  fclose(outputFile);
  free(jsonContent);

  return 0;
}
