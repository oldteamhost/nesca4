#ifndef COMPILE_H
#define COMPILE_H

/*Disable lib(s).*/
#define HAVE_CURL
#define HAVE_SSL
#define HAVE_HIKVISION

#ifdef HAVE_CURL
#include <curl/curl.h>
#endif

#ifdef HAVE_SSL
#include <libssh/libssh.h>
#endif

#ifdef HAVE_HIKVISION
#include "../lib/HCNetSDK.h"
#endif

#endif
