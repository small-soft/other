/*
 * AMThread.c
 *
 *  Created on: 2009-11-17
 *      Author: qinghua.liqh
 */

#include <stdlib.h>
#include "AMThread.h"
#include "AMThreadMutex.h"
#include "AMMemory.h"

#define SYS_RTHREAD

#ifdef SYS_RTHREAD
#include <estlib.h>
#include <e32cons.h>
#include <sys/reent.h>
#endif

struct AMThreadAttr_
{
	AMInt32     prority;			//优先级
	AMInt32     status;				//当前状态.
	AMUInt32  	stackSize;		    //堆栈大小
	AMPVoid		stackAddr;		    //堆栈位置.
};

struct AMThread_
{
	RThread thread;					//RThread
	AMPVoid (*start) (AMPVoid);		//线程函数
	AMPVoid parg;					//参数
	AMThreadMutex	mutex;			//线程同步用到的Mutex
	bool   isStarted;				//标志线程函数是否开始运行.
};
_LIT(KThreadName, "AdapterThread %d");

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrCreate(AMThreadAttr * attr)
{
    if(NULL == attr)
        return AME_ARG_AINVALID;

    //*attr = new AMThreadAttr_();
    AMNewE(AMThreadAttr, *attr, AMThreadAttr_());
    
    if(*attr == NULL)
    	return AME_MALLOC_ERROR;
    
    memset(*attr,  0, sizeof(struct AMThreadAttr_));
    return AME_THREAD_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrDestroy (AMThreadAttr * attr)
{
    if(NULL == attr && *attr == NULL)
        return AME_ARG_AINVALID;

    //delete *attr;
    AMDelete(*attr);
    *attr = NULL;
    
    return AME_THREAD_SCUESS;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetStackAddr (const AMThreadAttr * attr, void **stackaddr)
{
	if(NULL != attr && stackaddr != NULL && *stackaddr != NULL)
	{
		struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
		*stackaddr = attr_->stackAddr;
		return AME_THREAD_SCUESS;
	}
	return AME_ARG_AINVALID;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetStackSize (const AMThreadAttr* attr, AMUInt32* stacksize)
{
	if(NULL != attr && stacksize != NULL)
	{
		struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
		
		*stacksize = attr_->stackSize;
		return AME_THREAD_SCUESS;
	}
	return AME_ARG_AINVALID;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrGetPrority (const AMThreadAttr* attr, AMInt32* prority)
{
	if(NULL != attr && prority != NULL)
	{
		struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
		
		*prority = attr_->prority;
		return AME_THREAD_SCUESS;
	}
	return AME_ARG_AINVALID;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetStackAddr (AMThreadAttr * attr, void *stackaddr)
{
	if(NULL != attr && stackaddr != NULL)
	{
		struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
		
		attr_->stackAddr = stackaddr;
		return AME_THREAD_SCUESS;
	}
	return AME_ARG_AINVALID;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetStackSize (AMThreadAttr * attr, AMUInt32 stacksize)
{
	if(NULL != attr)
	{
		struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
		
		attr_->stackSize = stacksize;
		return AME_THREAD_SCUESS;
	}
	return AME_ARG_AINVALID;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadAttrSetPrority (AMThreadAttr* attr, AMInt32 prority)
{
	if(NULL != attr && prority >= AM_THREAD_NORMAL && AM_THREAD_NORMAL <= AM_THREAD_REALTIME)
	{
		struct AMThreadAttr_* attr_ = (struct AMThreadAttr_*)attr;
		
		attr_->prority = prority;
		return AME_THREAD_SCUESS;
	}
	return AME_ARG_AINVALID;
}

TInt _TThreadCallback(TAny* parg)
{
	if(parg == NULL)
		return AME_THREAD_ERROR;
	AMThread_* pThread = (AMThread_*)parg;
	AMThreadMutexLock(&pThread->mutex);
	pThread->isStarted = true;
	
//#if 0
	//denx add for cleanup stack and active scheduler.
	//__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	if(cleanup == NULL)
	{
		return KErrNoMemory;
	}
	
	TRAPD(error,
	//CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
	AMNewLD(CActiveScheduler, scheduler, ELeave, CActiveScheduler());
	
	CleanupStack::PushL(scheduler);
	CActiveScheduler::Install(scheduler);
	//end of denx add.
//#endif
	pThread->start(pThread->parg);
//#if 0
	//denx add for cleanup stack and active scheduler.
	// Delete active scheduler
	CleanupStack::Pop(scheduler);
	AMDelete(scheduler);
	);
	
	//delete cleanup;
	AMDelete(cleanup);
	//__UHEAP_MARKEND;
	//end of denx
//#endif
	AMThreadMutexUnlock(&pThread->mutex);
	return AME_THREAD_SCUESS;
}

TThreadPriority _ParseThreadPriority(TInt priority)
{
	switch (priority)
	{
		case AM_THREAD_NORMAL:
			return EPriorityNormal;
		case AM_THREAD_ABOVE_NORMAL:
			return EPriorityMore;
		case AM_THREAD_BELOEW_NORMAL:
			return EPriorityLess;
		case AM_THREAD_HIGHEST:
			return EPriorityAbsoluteHigh;
		case AM_THREAD_LOWEST:
			return EPriorityAbsoluteLow;
		case AM_THREAD_REALTIME:
			return EPriorityRealTime;
		default:
			return EPriorityNormal;
	}
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadCreate(AMThread * tid, const AMThreadAttr * attr, AMPVoid (*start) (AMPVoid), AMPVoid arg)
{
	if(tid == NULL || start == NULL)
		return AME_ARG_AINVALID;
	
	//AMThread_* pThread = new AMThread_();
	AMNewD(AMThread_, pThread, AMThread_());
	
	if(pThread == NULL)
	    return AME_MALLOC_ERROR;
	*tid = pThread;
	pThread->start = start;
	pThread->parg = arg;
	pThread->isStarted = false;
	
	TBuf<100> buffer;
	buffer.Format(KThreadName, (TUint)pThread);
	
	TInt ret_code = 0;
	TInt err_code = 0;
	
	if((ret_code = AMThreadMutexCreate(&pThread->mutex)) != AME_MUTEX_SCUESS)
	{
		//delete pThread;
		AMDelete(pThread);
		return AME_THREAD_ERROR;
	}
	if(attr != NULL)
	{
		AMThreadAttr_*  pattr = (AMThreadAttr_*)attr;
		pThread->thread.SetPriority(_ParseThreadPriority(pattr->prority));
		
		//TRAP(err_code, ret_code = pThread->thread.Create(buffer, _TThreadCallback, 
		//		pattr->stackSize, KMinHeapSize, 0x100000, pThread));
		TRAP(err_code, ret_code = pThread->thread.Create(buffer, _TThreadCallback,
				pattr->stackSize, NULL, pThread));
	}
	else
	{
		pThread->thread.SetPriority(_ParseThreadPriority(AM_THREAD_NORMAL));
		//TRAP(err_code, ret_code = pThread->thread.Create(buffer, _TThreadCallback,
		//		KDefaultStackSize, KMinHeapSize, 0x100000, pThread));
		TRAP(err_code, ret_code = pThread->thread.Create(buffer, _TThreadCallback,
				KDefaultStackSize, NULL, pThread));
	}
	
	if(err_code == KErrNone && ret_code == KErrNone)
	{
		pThread->thread.Resume();
		return AME_THREAD_SCUESS;
	}
	
	if(err_code != KErrNone)
	{
		//delete pThread;
		AMDelete(pThread);
		pThread = NULL;
		return AME_THREAD_ERROR;
	}
	
	return AME_THREAD_ERROR;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadDetach (AMThread tid)
{
	return AME_UNIMPL_METHOD;
}

AMTHREAD_DLL_EXPORT void AMThreadExit (void *value_ptr)
{
	return;
}

AMTHREAD_DLL_EXPORT AMInt32 AMThreadWait (AMThread thread, void **value_ptr)
{
	if(thread == NULL)
		return AME_ARG_AINVALID;
	
	AMThread_* pThread = (AMThread_*)thread;
	while(!pThread->isStarted)
		User::After(10000);
	
	AMThreadMutexLock(&pThread->mutex);
	while(pThread->thread.ExitType() == EExitPending)
		User::After(10000);
	AMThreadMutexUnlock(&pThread->mutex);
	
	AMThreadMutexDestroy(&pThread->mutex);
	pThread->thread.Close();
	//delete pThread;
	AMDelete(pThread);
	return AME_THREAD_SCUESS;
}
