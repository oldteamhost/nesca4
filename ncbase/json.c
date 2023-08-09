/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/json.h"

/*
{
    "ip_address": "192.168.1.1",
    "details": {
        "dns_name": "example.com",
        "rtt": 10.5,
        "ports": [
            {
                "protocol": "TCP",
                "passwd": "secret",
                "http_title": "Welcome Page",
                "port": 80
            },
            {
                "protocol": "UDP",
                "passwd": "anothersecret",
                "http_title": "Alternate Page",
                "port": 123
            }
        ]
    }
}
*/

int
nesca_json_save_host(const char* filename, const struct nesca_host_details* host_data)
{
    FILE* file = fopen(filename, "a");
    if (file) {
        fprintf(file, "{\n");
        fprintf(file, "    \"ip_address\": \"%s\",\n", host_data->ip_address);
        fprintf(file, "    \"details\": {\n");
        fprintf(file, "        \"dns_name\": \"%s\",\n", host_data->dns_name);
        fprintf(file, "        \"content\": \"%s\",\n", host_data->content);
        fprintf(file, "        \"rtt\": %lf,\n", host_data->rtt);
        fprintf(file, "        \"ports\": [\n");
        fclose(file);
        return 0;
    }

    return -1;
}

int
nesca_json_set_comma(const char *filename)
{
    FILE* file = fopen(filename, "a");
    if (file)
    {
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
    if (file)
    {
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
    if (file)
    {
        fprintf(file, "            {\n");
        fprintf(file, "                \"port\": %u,\n", port_data->port);
        fprintf(file, "                \"protocol\": \"%s\",\n", port_data->protocol);
        if (*port_data->http_title != '\0')
        {
            fprintf(file, "                \"http_title\": \"%s\",\n", port_data->http_title);
        }
        fprintf(file, "                \"passwd\": \"%s\"\n", port_data->passwd);
        fprintf(file, "            }");
        fclose(file);
        return 0;
    }
    return -1;
}

int
nesca_json_close_info(const char *filename)
{
    FILE* file = fopen(filename, "a");
    if (file)
    {
        fprintf(file, "\n        ]\n");
        fprintf(file, "    }\n");
        fprintf(file, "}");
        fclose(file);
        return 0;
    }

    return -1;
}
