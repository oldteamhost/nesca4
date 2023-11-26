/*
 * NCSOCK & NESCA 4
 * by oldteam & lomaster
 * license GPL-2.0
 *   Сделано от души 2023.
*/

#include "include/strbase.h"
#include <stdint.h>

int find_word(const char* buffer, const char* word)
{
  int buffer_length = strlen(buffer);
  int word_length = strlen(word);

  if (word_length > buffer_length) {
    return -1;
  }

  char buffer_lower[4096];
  strcpy(buffer_lower, buffer);
  to_lower(buffer_lower);

  char word_lower[256];
  strcpy(word_lower, word);
  to_lower(word_lower);

  for (int i = 0; i <= buffer_length - word_length; i++) {
    if (strncmp(buffer_lower + i, word_lower, word_length) == 0) {
      return i;
    }
  }

  return -1;
}
#include <time.h>
#include <stdlib.h>

char* clean_url(const char* url)
{
  const char* https_prefix = "https://";
  const char* http_prefix = "http:///";
  const char* http_prefix_alt = "http://";

  if (strncmp(url, https_prefix, strlen(https_prefix)) == 0) {
    url += strlen(https_prefix);
  }
  else if (strncmp(url, http_prefix, strlen(http_prefix)) == 0) {
    url += strlen(http_prefix);
  }
  else if (strncmp(url, http_prefix_alt, strlen(http_prefix_alt)) == 0) {
    url += strlen(http_prefix_alt);
  }

  size_t url_length = strlen(url);

  if (url_length > 0 && url[url_length - 1] == '/') {
    char* modified_url = (char*)malloc(url_length);
    strncpy(modified_url, url, url_length - 1);
    modified_url[url_length - 1] = '\0';
    return modified_url;
  }
  else {
    return strdup(url);
  }
}

void remove_specials(char* buffer)
{
  int len = strlen(buffer);
  int i, j = 0;

  for (i = 0; i < len; i++) {
      if (buffer[i] != '\r' && buffer[i] != '\n' && buffer[i] != '\t') {
      buffer[j++] = buffer[i];
    }
  }

  buffer[j] = '\0';
}


unsigned int generate_seed(void)
{
  struct timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
    perror("clock_gettime");
    exit(1);
  }
  unsigned int seed = (unsigned int)(ts.tv_sec * 1000000000ULL + ts.tv_nsec);
  return seed;
}

char* generate_random_str(int len, const char* dictionary)
{
  mt19937_seed(generate_seed());
  char* result = (char*)malloc(len + 1);
  if (result == NULL) {
    return NULL;
  }

  int dict_len = strlen(dictionary);
  for (int i = 0; i < len; i++) {
    result[i] = dictionary[mt19937_random() % dict_len];
  }

  result[len] = '\0';
  return result;
}

uint16_t generate_rare_port(void)
{
  return(random_num(49151, 65535));
}

uint32_t generate_seq(void)
{
  return(random_num(1, 4294967294));
}

const char* generate_ipv4(void)
{
  mt19937_seed(generate_seed());
  static char ip[256];

  snprintf(ip, sizeof(ip), "%u.%u.%u.%u",
      mt19937_random() % 256, mt19937_random() % 256,
      mt19937_random() % 256, mt19937_random() % 256);

  return ip;
}

void to_lower(char* str)
{
  for (int i = 0; str[i]; i++) {
    str[i] = tolower((unsigned char)str[i]);
  }
}

unsigned int random_num(unsigned int min, unsigned int max)
{
  if (min > max) {
    return -1;
  }

  mt19937_seed(generate_seed());
  unsigned int range = max - min + 1;
  unsigned int random_value = min + (unsigned int)(mt19937_random() % range);

  return random_value;
}

uint32_t generate_ident(void)
{
  mt19937_seed(generate_seed());
  return (uint16_t)(mt19937_random() % 229444421);
}
