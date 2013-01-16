/*
 * AMTime.h
 *
 *  Created on: 2009-11-20
 *      Author: qinghua.liqh
 */
#ifndef _AM_TIME_H_
#define _AM_TIME_H_
#include "AMErrno.h"
#include "AMTypes.h"

#ifndef _AM_TM_DEFINED
struct AMtm {
	AMInt32 tm_sec;	    /* seconds after the minute - [0,59] */
	AMInt32 tm_min;	    /* minutes after the hour - [0,59] */
	AMInt32 tm_hour;	/* hours since midnight - [0,23] */
	AMInt32 tm_mday;	/* day of the month - [1,31] */
	AMInt32 tm_mon;	    /* months since January - [0,11] */
	AMInt32 tm_year;	/* years since 1900 */
	AMInt32 tm_wday;	/* days since Sunday - [0,6] */
	AMInt32 tm_yday;	/* days since January 1 - [0,365] */
	AMInt32 tm_isdst;	/* daylight savings time flag */
	};
#define _AM_TM_DEFINED
#endif

#ifndef _AM_TIME_T_DEFINED
typedef AMInt32 AMTime_t;
#define _AM_TIME_T_DEFINED 
#endif

#ifndef _AM_CLOCK_T_DEFINED
typedef AMInt32 AMClock_t;
#define _AM_CLOCK_T_DEFINED
#endif

#ifndef _AM_HAVE_STRUCT_TIMEVAL
struct AMTimeval {
    AMInt32    tv_sec;     //秒        
    AMInt32    tv_usec;    //微秒 10^-6           
};
#define _AM_HAVE_STRUCT_TIMEVAL
#endif


#ifndef _AM_HAVE_STRUCT_TIMESPEC
struct AMTimespec {
	AMInt32 tv_sec;         //秒
	AMInt32 tv_nsec;        //纳秒  10^-9
};
#define _AM_HAVE_STRUCT_TIMESPEC
#endif
#ifdef __cplusplus 
extern "C" {
#endif
    //分别得到UTC时间, AMGetUTCTime 只能得到秒级别, *Ex可以得到微妙级别.
    //参数为要填充的Buffer, 错误返回NULL, 成功返回参数的指针
    ADAPTER_API AMTime_t AMGetUTCTime(AMTime_t *calptr);
    ADAPTER_API struct AMTimeval*  AMGetUTCTimeEx(struct AMTimeval* tp);

	//************************************
	// Method:    AMGetUpTime
	// Author:    yanlong.shiyl 
	// Returns:   ADAPTER_API AMTime_t
	// Parameter: AMTime_t * calptr		pointing to a place to store the uptime.
	//************************************
	ADAPTER_API AMTime_t AMGetUpTime(AMTime_t *calptr);

    ADAPTER_API AMTime_t        AMMkTime(struct AMtm* tmptr);

#ifdef __cplusplus 
}
#endif
/*
//得到当前时间, 分别为time_t和tm数据结构. UTC时间
ADAPTER_API AMTime_t        AMTime(AMTime_t *calptr);
ADAPTER_API AMInt32         AMGetTimeOfDay(struct AMTimeval* tp, AMPVoid tzp);
//当地时间
ADAPTER_API struct AMtm*    AMLocalTime(const AMTime_t* calptr);

//AMtm he AMTime_t格式互相转换.
ADAPTER_API struct AMtm*    AMGmtime(const AMTime_t* calptr);
ADAPTER_API AMTime_t        AMMkTime(struct AMtm* tmptr);

//得到时间字符串.
ADAPTER_API AMChar*         AMCTime(const AMTime_t* calptr);
ADAPTER_API AMChar*         AMAscTime(const struct AMtm* tmptr);
ADAPTER_API AMClock_t       AMClock(AMVoid);
*/
#endif //_AM_TIME_H_
