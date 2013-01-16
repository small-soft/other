#if (defined (_WIN32_WCE) || defined(_WIN32)) && (!defined(__SYMBIAN32__)) 
#ifndef _WINCE_TIME_
#define _WINCE_TIME_
#include <stdlib.h>
#include <time.h>

#ifdef DLL_UTIL_EXPORTS
#ifndef UTIL_API
#define UTIL_API __declspec(dllexport)
#endif
#else
#ifndef UTIL_API
#define UTIL_API //__declspec(dllimport)
#endif
#endif

#ifndef _TM_DEFINED
struct tm {
	int tm_sec;	/* seconds after the minute - [0,59] */
	int tm_min;	/* minutes after the hour - [0,59] */
	int tm_hour;	/* hours since midnight - [0,23] */
	int tm_mday;	/* day of the month - [1,31] */
	int tm_mon;	/* months since January - [0,11] */
	int tm_year;	/* years since 1900 */
	int tm_wday;	/* days since Sunday - [0,6] */
	int tm_yday;	/* days since January 1 - [0,365] */
	int tm_isdst;	/* daylight savings time flag */
	};
#define _TM_DEFINED
#endif

#ifndef _TIME_T_DEFINED
typedef long time_t;		/* time value */
#define _TIME_T_DEFINED 	/* avoid multiple def's of time_t */
#endif

#ifndef _CLOCK_T_DEFINED
typedef long clock_t;
#define _CLOCK_T_DEFINED
#endif

#ifdef _WIN32_WCE
#ifndef HAVE_STRUCT_TIMEVAL
struct timeval {
        long    tv_sec;             //秒    
        long    tv_usec;            //毫秒 10^-6
};
#define HAVE_STRUCT_TIMEVAL
#endif
#endif


#ifndef HAVE_STRUCT_TIMESPEC
struct timespec {
	long tv_sec;                    //秒
	long tv_nsec;                   //纳秒  10^-9
};
#define HAVE_STRUCT_TIMESPEC
#endif

//得到当前时间, 分别为time_t和tm数据结构. UTC时间
time_t time(time_t *calptr);
UTIL_API int gettimeofday(struct timeval* tp, void* tzp);
//当地时间
struct tm* localtime(const time_t* calptr);

//tm he time_t格式互相转换.
struct tm *gmtime(const time_t* calptr);
time_t mktime(struct tm* tmptr);

//得到时间字符串.
char* ctime(const time_t* calptr);
char* asctime(const struct tm* tmptr);

clock_t  clock(void);
#endif
#endif
