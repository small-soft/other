/*
* AMTimer.h
*
*  Created on: 2009-11-23
*      Author: qinghua.liqh
*/
#ifndef _AM_TIMER_H_
#define _AM_TIMER_H_
#include "AMTime.h"

struct AMHandler;


//时间对象。
typedef AMPVoid AMTimer;

/*
typedef struct AMTimer
{
	AMUInt32 timer;
	struct AMHandler* handler;
}AMTimer;
*/

typedef AMPVoid (*AMTimerCallback)(AMPVoid pArg);

#ifdef __cplusplus 
extern "C" {
#endif
    //睡眠, 单位是毫秒 10^-3.
    ADAPTER_API AMVoid AMSleep(AMUInt32 millSeconds);

    //callback可能在另外一个线程中执行, 使用者一定要考虑同步问题
    ADAPTER_API AMInt32 AMSetTimer(AMTimer* timer, AMTimerCallback callback,
        AMPVoid parg, struct AMTimeval* delay, struct AMTimeval* intervel);//inervel 0、0表示只执行一次，不循环
    //记的一定要调用AMKillTimer释放空间哦
    ADAPTER_API AMInt32 AMKillTimer(AMTimer timer);
#ifdef __cplusplus 
}
#endif
/*
//设置计时器
//handler制定回调运行的Looper, callback是回调函数, time是延迟的时间.
ADAPTER_API AMInt32 AMSetTimer(AMTimer* timer, struct AMHandler* handler, 
		AMTimerCallback callback, AMPVoid parg, struct AMTimeval* time);
ADAPTER_API AMInt32 AMKillTimer(AMTimer* timer);
*/
#endif //_AM_TIMER_H_






