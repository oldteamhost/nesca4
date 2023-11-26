/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#ifndef COMPILE_H
#define COMPILE_H

#define HAVE_HIKVISION /*Disable HIKVISION lib*/
#define HAVE_NODE_JS   /*Disable save screenshots*/

#ifdef HAVE_HIKVISION
#include "../lib/HCNetSDK.h"
#endif

#endif
