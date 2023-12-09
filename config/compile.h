/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#ifndef COMPILE_H
#define COMPILE_H

#define HAVE_HIKVISION /*Disable HIKVISION lib*/
#define HAVE_NODE_JS   /*Disable save screenshots*/

#ifdef HAVE_HIKVISION
#include "../library/HCNetSDK.h"
#endif

#endif
