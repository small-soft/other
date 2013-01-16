#ifndef HTTP_FUN_H
#define HTTP_FUN_H

#include <assert.h>
#include<ctype.h>

#ifdef _cplusplus
extern "C" {
#endif // _cplusplus

#define STRDUP(dst,src)			do\
								{\
									dst = malloc(strlen(src) + 1);\
									assert(dst);\
									strcpy(dst,src);\
								}while(0)

int strcasecmp (const char *s1, const char *s2);

#ifdef _cplusplus
}
#endif // _cplusplus


#endif