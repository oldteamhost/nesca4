/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "../ncsock/include/utils.h"

u16 generate_rare_port(void)
{
  return(random_num(49151, 65535));
}

u32 generate_seq(void)
{
  return(random_num(1, 4294967294));
}

const char* generate_ipv4(void)
{
  static char ip[16];
  mt19937_seed(generate_seed());

  snprintf(ip, sizeof(ip), "%u.%u.%u.%u",
      mt19937_random() % 256, mt19937_random() % 256,
      mt19937_random() % 256, mt19937_random() % 256);

  return ip;
}

u32 random_num(u32 min, u32 max)
{
  u32 range = max - min + 1;
  if (min > max)
    return -1;

  mt19937_seed(generate_seed());
  u32 random_value = min + (u32)(mt19937_random() % range);

  return random_value;
}

u32 generate_ident(void)
{
  mt19937_seed(generate_seed());
  return (u16)(mt19937_random() % 229444421);
}

u16 generate_checksum(void)
{
  mt19937_seed(generate_seed());
  return (u16)(1+ (mt19937_random() % 0xFFFF-1));
}

#include <limits.h>
u32 random_u32(void)
{
  return generate_random_u32(1, UINT_MAX);
}
u16 random_u16(void)
{
  return (u16)generate_random_u32(1, USHRT_MAX);
}
u8 random_u8(void)
{
  return (u8)generate_random_u32(1, UCHAR_MAX);
}
