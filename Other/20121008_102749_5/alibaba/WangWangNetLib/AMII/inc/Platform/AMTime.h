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
    AMInt32    tv_sec;     //��        
    AMInt32    tv_usec;    //΢�� 10^-6           
};
#define _AM_HAVE_STRUCT_TIMEVAL
#endif


#ifndef _AM_HAVE_STRUCT_TIMESPEC
struct AMTimespec {
	AMInt32 tv_sec;         //��
	AMInt32 tv_nsec;        //����  10^-9
};
#define _AM_HAVE_STRUCT_TIMESPEC
#endif
#ifdef __cplusplus 
extern "C" {
#endif
    //�ֱ�õ�UTCʱ��, AMGetUTCTime ֻ�ܵõ��뼶��, *Ex���Եõ�΢���.
    //����ΪҪ����Buffer, ���󷵻�NULL, �ɹ����ز�����ָ��
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
//�õ���ǰʱ��, �ֱ�Ϊtime_t��tm���ݽṹ. UTCʱ��
ADAPTER_API AMTime_t        AMTime(AMTime_t *calptr);
ADAPTER_API AMInt32         AMGetTimeOfDay(struct AMTimeval* tp, AMPVoid tzp);
//����ʱ��
ADAPTER_API struct AMtm*    AMLocalTime(const AMTime_t* calptr);

//AMtm he AMTime_t��ʽ����ת��.
ADAPTER_API struct AMtm*    AMGmtime(const AMTime_t* calptr);
ADAPTER_API AMTime_t        AMMkTime(struct AMtm* tmptr);

//�õ�ʱ���ַ���.
ADAPTER_API AMChar*         AMCTime(const AMTime_t* calptr);
ADAPTER_API AMChar*         AMAscTime(const struct AMtm* tmptr);
ADAPTER_API AMClock_t       AMClock(AMVoid);
*/
#endif //_AM_TIME_H_
