#if (defined (_WIN32_WCE) || defined(_WIN32)) && (!defined(__SYMBIAN32__)) 
#define NO_ERRNO
#define DLLTEST_EXPORTS
#define NO_FTIME
#define _PTHREAD_CREATETHREAD
#include "../wince/pthread.h"
#define sleep(t)  (Sleep(t * 1000))
#else
#include <pthread.h>
#endif