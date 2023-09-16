/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "include/mathutils.h"

int
calc_threads(int speed_type, int len)
{
  const int sizes[] = {100, 500, 1000, 1500, 2000};
  const int speed_type_index = speed_type - 1;
  const int max_threads = (speed_type_index >= 0 && speed_type_index < 5) ? sizes[speed_type_index] : 0;
  return std::min(max_threads, len);
}

int
calc_timeout(int speed_type)
{
  const int timeouts[] = {3000, 2000, 1000, 600, 400};
  const int speed_type_index = speed_type - 1;
  return (speed_type_index >= 0 && speed_type_index < 5) ? timeouts[speed_type_index] : 0;
}

int
calc_port_timeout(int speed_type, int rtt_ping)
{
  const int coefficients[] = {0, 5, 4, 3, 2, 1};
  if (speed_type < 1 || speed_type > 5) {return rtt_ping;}
  return rtt_ping * coefficients[speed_type];
}
