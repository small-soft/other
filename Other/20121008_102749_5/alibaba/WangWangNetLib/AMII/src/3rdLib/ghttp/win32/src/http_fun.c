#include "http_fun.h"

int
strcasecmp (const char *s1, const char *s2)
{
	while (*s1 != 0 && tolower(*s1) == tolower(*s2))
		s1++, s2++;

	if (*s1 == 0 || *s2 == 0)
		return (unsigned char) *s1 - (unsigned char) *s2;
	return *s1 - *s2;
}