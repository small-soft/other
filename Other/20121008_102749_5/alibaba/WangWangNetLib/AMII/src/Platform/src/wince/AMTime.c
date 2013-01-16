/*
 * AMTime.c
 *
 *  Created on: 2009-11-20
 *      Author: qinghua.liqh
 */

#include "AMTime.h"
#include <time.h>
#include <windows.h>

#ifdef _WIN32_WCE
#ifndef HAVE_STRUCT_TIMEVAL
struct timeval {
        long    tv_sec;             //√Î    
        long    tv_usec;            //∫¡√Î 10^-6
};
#define HAVE_STRUCT_TIMEVAL
#endif
#endif

#define TIMESPEC_TO_FILETIME_OFFSET (((LONGLONG)27111902 << 32) + (LONGLONG)3577643008)
static AMVoid timeval_to_filetime(const struct timeval *ts, FILETIME *ft)
{
	*(LONGLONG *)ft = ts->tv_sec * 10000000 + (ts->tv_usec + 50) * 10 + TIMESPEC_TO_FILETIME_OFFSET;
}
static void filetime_to_timeval(const FILETIME *ft, struct timeval *ts)
{
	ts->tv_sec = (long)((*(LONGLONG *)ft - TIMESPEC_TO_FILETIME_OFFSET) / 10000000);
	ts->tv_usec = (long)((*(LONGLONG *)ft - TIMESPEC_TO_FILETIME_OFFSET - ((LONGLONG)ts->tv_sec * (LONGLONG)10000000)) / 10);
}

AMTime_t AMTime(AMTime_t *calptr)
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
struct AMtm* AMGmtime(const AMTime_t* calptr)
{
	return NULL;
}

AMClock_t AMClock(AMVoid)
{
	return 0;
}

AMInt32 AMGetTimeOfDay(struct AMTimeval* tp, AMPVoid tzp)
{
	FILETIME ft;
	SYSTEMTIME st;
	struct timeval currSysTime;

	GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);

	filetime_to_timeval(&ft, &currSysTime);
	memcpy(tp, &currSysTime, sizeof(struct timeval));
	
//	tp->tv_usec = GetTickCount()* 1000;
	return 0;
}

ADAPTER_API AMTime_t AMGetUTCTime(AMTime_t *calptr)
{
    return AMTime(calptr);
}
ADAPTER_API struct AMTimeval*  AMGetUTCTimeEx(struct AMTimeval* tp)
{
    AMGetTimeOfDay(tp, NULL);
    tp->tv_sec =  tp->tv_sec ;
    tp->tv_usec =  tp->tv_usec;
    return tp;
}

ADAPTER_API AMTime_t AMGetUpTime(AMTime_t *calptr)
{
	AMTime_t t = GetTickCount()/1000;
	
	if(calptr)
		*calptr = t;

	return t;
}

AMTime_t AMMkTime(struct AMtm* tmptr)
{
    time_t time = mktime(tmptr);
    return (AMTime_t)time;
}