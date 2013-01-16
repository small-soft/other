/*
* AMTimer.h
*
*  Created on: 2009-11-23
*      Author: qinghua.liqh
*/

//#include "e32def.h"
#include "e32std.h"
#include "AMTimer.h"
#include "AMThread.h"
#include "stdlib.h"
#include "Timer.h"

#ifdef __SYMBIAN32__
#else
ADAPTER_API AMVoid AMSleep(AMUInt32 millSeconds)
{
#if _WIN32
	Sleep(millSeconds );
#else
	usleep(millSeconds * 1000);
#endif
}
#endif

#define REINTERPRET( Type, NewValue, OldValue ) Type NewValue = reinterpret_cast<Type>( OldValue )

/*
AMInt32 AMSetTimer(AMTimer* timer, struct AMHandler* handler, 
		AMTimerCallback callback, AMPVoid parg, struct AMTimeval* time)
{
	static AMUInt32 timerCount = 0;
	if(NULL == timer || NULL == handler || NULL == callback || NULL == time)
		return AME_ARG_AINVALID;
	else
	{
		struct AMMessage msg;
		AMMessageInit(&msg, NULL);
		msg.type = AM_MESSAGE_TIMER;
		msg.ref1.ptr = (AMPVoid)callback;
		msg.ref2.ptr = parg;
		msg.v1.ui = timer->timer;
		timer->timer = ++timerCount;
		msg.v1.ui = timer->timer;
		timer->handler = handler;
		return AMHandlerSendMsgAfterTime(handler, &msg, time);
	}

	return AME_SCUESS;
}

extern AMInt32 AMHandlerRemoveTimerMessage(struct AMHandler* handler, AMUInt32 timer);
AMInt32 AMKillTimer(AMTimer* timer)
{
	if(NULL == timer)
		return AME_ARG_AINVALID;
	else
	{
		return  AMHandlerRemoveTimerMessage(timer->handler, timer->timer);
	}
}
*/



ADAPTER_API AMVoid AMSleep(AMUInt32 millSeconds)
{
#if 0
	RTimer t;
	TRequestStatus s;
	
	t.CreateLocal();
	TTimeIntervalMicroSeconds32 ms(millSeconds*1000);
	t.After(s, ms);
	User::WaitForRequest(s);
	t.Close();
#endif
	User::After(millSeconds * 1000);
}


typedef struct AMTimer_
{
    AMTimerCallback callback;   //时间到时回调函数
    AMPVoid parg;                //回调函数对应的参数
    struct AMTimeval start;     //开始时间
    struct AMTimeval end;       //结束时间     
    AMThread thread;            //对应的线程
    AMBool isShouldEnd;         //是否已经被结束了
    AMBool isKillFreeMemory;    //是否是Kill函数销毁空间
}AMTimer_;

static AMPVoid _AMTimerThreadCallback (AMPVoid parg)
{
    AMTimer_* timer_ = (AMTimer_*)parg;
    if(timer_ == NULL)
        return NULL;

    while(timer_->isShouldEnd == AMFALSE)
    {
        struct AMTimeval v;
        AMGetUTCTimeEx(&v);
        if(v.tv_sec <= timer_->end.tv_sec && v.tv_usec <= timer_->end.tv_usec)
        {
             //时间到退出
             AMPVoid ret = timer_->callback(timer_->parg);

#ifdef __SYMBIAN32__
             timer_->isKillFreeMemory = AMTRUE;
#elif _WIN32
             InterlockedExchange((LPLONG)&timer_->isKillFreeMemory, AMTRUE);
#else
             timer_->isKillFreeMemory = AMTRUE;
#endif
             return ret;
        }

        AMSleep(100);
    }
    //调用AMTimerKill退出
    free(timer_);
    return NULL;
}

ADAPTER_API AMInt32 AMSetTimer(AMTimer* timer, AMTimerCallback callback,
        AMPVoid parg, struct AMTimeval* delay, struct AMTimeval* intervel)
{
	CTimerInternal* t = new ( ELeave ) CTimerInternal( callback, parg, delay, intervel );
	*timer = t;
	return 0;
}

ADAPTER_API AMInt32 AMKillTimer(AMTimer* timer)
{
	REINTERPRET( CTimerInternal*, t, *timer );
	delete t;
    return 0;
}


