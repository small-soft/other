/*
* AMTimer.h
*
*  Created on: 2009-11-23
*      Author: qinghua.liqh
*/
//#include "AMLooperHandler.h"
//#include "AMLooperMessage.h"
#ifdef __SYMBIAN32__
#elif _WIN32
#include <windows.h>
#else
#endif
#include "AMTimer.h"
#include "AMThread.h"
#include "stdlib.h"

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

typedef struct AMTimer_
{
    AMTimerCallback callback;   //时间到时回调函数
    AMPVoid parg;                //回调函数对应的参数
    struct AMTimeval start;     //开始时间
    struct AMTimeval end;       //结束时间\目前没有使用，因为接口上不支持？
	struct AMTimeval intervel;	//循环间隔
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
		if(timer_->start.tv_sec - v.tv_sec > timer_->intervel.tv_sec + 2)
		{
			timer_->start.tv_sec = v.tv_sec;
			timer_->start.tv_usec = v.tv_usec;
		}
        else if(v.tv_sec > timer_->start.tv_sec || (v.tv_sec == timer_->start.tv_sec && v.tv_usec >= timer_->start.tv_usec) )
        {
             //时间到退出
             timer_->callback(timer_->parg);

			 if(timer_->intervel.tv_sec || timer_->intervel.tv_usec)
			 {
				 if(v.tv_sec - timer_->start.tv_sec > timer_->intervel.tv_sec + 2) 
				 {
					 timer_->start.tv_sec = v.tv_sec;
					 timer_->start.tv_usec = v.tv_usec;
				 }

				 timer_->start.tv_sec = (timer_->start.tv_sec + timer_->intervel.tv_sec) +
					 (timer_->start.tv_usec + timer_->intervel.tv_usec)/ 1000000;
				 timer_->start.tv_usec = (timer_->start.tv_usec + timer_->intervel.tv_usec) % 1000000;
			 }
			 else
			 {
#ifdef __SYMBIAN32__
				 timer_->isKillFreeMemory = AMTRUE;
#elif _WIN32
				 InterlockedExchange((LPLONG)&timer_->isKillFreeMemory, AMTRUE);
#else
				 timer_->isKillFreeMemory = AMTRUE;
#endif
				 return NULL;
			 }
        }

        AMSleep(100);
    }

	return NULL;
}

ADAPTER_API AMInt32 AMSetTimer(AMTimer* timer, AMTimerCallback callback,
        AMPVoid parg, struct AMTimeval* time, struct AMTimeval* intervel)
{
    AMTimer_* timer_;
    if(timer == NULL || time == NULL && callback == NULL)
        return AME_ARG_AINVALID;

    timer_ = (AMTimer_*)malloc(sizeof(AMTimer_));
    if(timer_ == NULL)
        return AME_MALLOC_ERROR;

    AMGetUTCTimeEx(&timer_->start);
    timer_->start.tv_sec = (timer_->start.tv_sec + time->tv_sec) +
        (timer_->start.tv_usec + time->tv_usec)/ 1000000;
    timer_->start.tv_usec = (timer_->start.tv_usec + time->tv_usec) % 1000000;
	timer_->intervel.tv_sec = intervel->tv_sec;
	timer_->intervel.tv_usec = intervel->tv_usec;
    timer_->callback = callback;
    timer_->parg = parg;
    timer_->isShouldEnd = AMFALSE;
    timer_->isKillFreeMemory = AMFALSE;

    if(AMThreadCreate(&timer_->thread, NULL, _AMTimerThreadCallback, timer_) == 0)
	{
		*timer = timer_;
		return 0;
	}
	else
        return AME_TIMER_CREATE_ERR;
}

ADAPTER_API AMInt32 AMKillTimer(AMTimer timer)
{
    AMTimer_* timer_ = (AMTimer_*)timer;
    if(timer == NULL)
        return AME_ARG_AINVALID;

    if(timer_->isKillFreeMemory == AMTRUE)
    {
        AMThreadWait(timer_->thread, NULL);
        free(timer_);
        return AME_TIMER_HAS_FINISHED;
    }

#ifdef __SYMBIAN32__
    timer_->isShouldEnd = AMTRUE;
#elif _WIN32
    InterlockedExchange((LPLONG)&timer_->isShouldEnd, AMTRUE);
#else
    timer_->isShouldEnd = AMTRUE;
#endif

	AMThreadWait(timer_->thread, NULL);
	free(timer_);
    return 0;
}


