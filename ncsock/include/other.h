#ifndef NCSOCK_OTHER_H
#define NCSOCK_OTHER_H

#ifdef __cplusplus
#include <sys/time.h>
extern "C" {
#endif

/*Easy calc timeout on ms.*/
struct timeval 
calculate_timeout_in_ms(int timeout_ms);

#ifdef __cplusplus
}
#endif

#endif
