/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#ifndef JSON_H
#define JSON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct nesca_host_details
{
  const char* ip_address;
  const char* dns_name;
  double rtt;
};

struct nesca_port_details
{
  unsigned int port;
  const char* type_target;
  const char* protocol;
  const char* passwd;
  const char* content;
  const char* screenshot;
  const char* http_title;
};

int nesca_json_save_host(const char* filename, const struct nesca_host_details* host_data);
int nesca_json_save_port(const char* filename, const struct nesca_port_details* port_data);
int nesca_json_set_comma(const char *filename);
int nesca_json_skip_line(const char *filename);
int nesca_json_close_info(const char *filename);
int nesca_json_fix_file(const char* filename);
int nesca_json_start_array(const char *filename);
int nesca_json_close_array(const char *filename);

#ifdef __cplusplus
}
#endif

#endif
