#if (defined (_WIN32_WCE) || defined(_WIN32)) && (!defined(__SYMBIAN32__)) 
#include "wince\wince_time.h"
#include <windows.h>

#define TIMESPEC_TO_FILETIME_OFFSET (((LONGLONG)27111902 << 32) + (LONGLONG)3577643008)
static void timeval_to_filetime(const struct timeval *ts, FILETIME *ft)
{
	*(LONGLONG *)ft = ts->tv_sec * 10000000 + (ts->tv_usec + 50) / 100 + TIMESPEC_TO_FILETIME_OFFSET;
}
static void filetime_to_timeval(const FILETIME *ft, struct timeval *ts)
{
	ts->tv_sec = (long)((*(LONGLONG *)ft - TIMESPEC_TO_FILETIME_OFFSET) / 10000000);
	ts->tv_usec = (long)((*(LONGLONG *)ft - TIMESPEC_TO_FILETIME_OFFSET - ((LONGLONG)ts->tv_sec * (LONGLONG)10000000)) * 100);
}

#ifdef _WIN32_WCE
time_t time(time_t *calptr)
{
	FILETIME ft;
	SYSTEMTIME st;
	struct timeval currSysTime;

	GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);

	filetime_to_timeval(&ft, &currSysTime);
	if(NULL != calptr)
		*calptr = currSysTime.tv_sec;

	return currSysTime.tv_sec;
}
struct tm *gmtime(const time_t* calptr)
{
	return NULL;
}

clock_t  clock(void)
{
	return 0;
}
#endif

int gettimeofday(struct timeval* tp, void* tzp)
{
	FILETIME ft;
	SYSTEMTIME st;
	struct timeval currSysTime;

	GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);

	filetime_to_timeval(&ft, &currSysTime);
	memcpy(tp, &currSysTime, sizeof(struct timeval));
	return 0;
}



#endif


