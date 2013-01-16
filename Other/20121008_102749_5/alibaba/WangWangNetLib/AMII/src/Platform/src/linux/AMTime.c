/*
 * AMTime.c
 *
 *  Created on: 2009-11-23
 *      Author: qinghua.liqh
 */
#include "AMTime.h"
#include <time.h>

#include <unistd.h>

//#define MY_HAVE_ANDROID_OS 1
//#if MY_HAVE_ANDROID_OS

#ifdef ANDROID_BUILD
#include <linux/ioctl.h>
#include <linux/rtc.h>
#include <sys/atomics.h>
#include <linux/android_alarm.h>
#include <fcntl.h>
#endif

AMInt32 AMGetTimeOfDay(struct AMTimeval* tp, AMPVoid tzp)
{
    if(gettimeofday((struct timeval*)tp, NULL) == 0)
        return AME_SCUESS;
    else
        return AME_GETTIMEOFDAY;
}

AMTime_t AMGetUTCTime(AMTime_t *calptr)
{
    time_t t = time(NULL);
    if(calptr)
	*(AMInt32*)calptr = *(AMInt32*)t;

    return t;
}
struct AMTimeval*  AMGetUTCTimeEx(struct AMTimeval* tp)
{
    AMGetTimeOfDay(tp, NULL);
    tp->tv_sec =  tp->tv_sec ;
    tp->tv_usec =  tp->tv_usec;
    return tp;
}

static AMTime_t AMGetUpTime_noSleep(AMTime_t *calptr) {
    AMTime_t t = times((struct tms*)NULL)/sysconf(_SC_CLK_TCK);
    if(calptr)
	 *(AMInt32*)calptr = *(AMInt32*)t;
    return t;
}

AMTime_t AMGetUpTime(AMTime_t *calptr)
{
#ifdef ANDROID_BUILD
    static int s_fd = -1;
    struct timespec ts;
    int result = 0;

    if (s_fd == -1) {
        int fd = open("/dev/alarm", O_RDONLY);
        if (__atomic_cmpxchg(-1, fd, &s_fd)) {
            close(fd);
        }
    }

    result = ioctl(s_fd,
            ANDROID_ALARM_GET_TIME(ANDROID_ALARM_ELAPSED_REALTIME), &ts);

    if (result == 0) {
        return ts.tv_sec;
    }
#endif
    return AMGetUpTime_noSleep(calptr);
}



/*******************************************mktime临时解决方案（android下运行库的mktime）出错***********************/
#define MINUTE 60
#define HOUR (60*MINUTE)
#define DAY (24*HOUR)
#define YEAR (365*DAY)
/* interestingly, we assume leap-years */
static int month[12] = {                //－－每月初所经过的秒数
	0,
	DAY*(31),
	DAY*(31+29),
	DAY*(31+29+31),
	DAY*(31+29+31+30),
	DAY*(31+29+31+30+31),
	DAY*(31+29+31+30+31+30),
	DAY*(31+29+31+30+31+30+31),
	DAY*(31+29+31+30+31+30+31+31),
	DAY*(31+29+31+30+31+30+31+31+30),
	DAY*(31+29+31+30+31+30+31+31+30+31),
	DAY*(31+29+31+30+31+30+31+31+30+31+30)
};

long my_mktime(struct tm * tm)
{
	long res;
	int year;
	year = tm->tm_year - 70;                            //－－年数
	/* magic offsets (y+1) needed to get leapyears right.*/
	res = YEAR*year + DAY*((year+1)/4);                    //－－年数＋闰年数
	res += month[tm->tm_mon];                            //－－月
	/* and (y+2) here. If it wasn't a leap-year, we have to adjust */
	if (tm->tm_mon>1 && ((year+2)%4))                    //－－若(y+2)不是闰年，则减一天
		res -= DAY;
	res += DAY*(tm->tm_mday-1);                            //－－当月已经过的天数
	res += HOUR*tm->tm_hour;                            //－－当天已经过的小时数
	res += MINUTE*tm->tm_min;                            //－－此时已经过的分钟
	res += tm->tm_sec;                                    //－－此分已经过的秒
	return res;
}
/*******************************************mktime临时解决方案 end************************************/

AMTime_t AMMkTime(struct AMtm* tmptr)
{
    time_t time = my_mktime(tmptr);
    return (AMTime_t)time;
}
