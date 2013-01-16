#include "SymbianMainScheduler.h"
#include "AlibabaMobileSDKInit.h"
#include "AMThread.h"
#include "AMThreadCond.h"
#include "AMMemory.h"
#include "e32err.h"

struct AMThread_
{
	RThread thread;					//RThread
	AMPVoid (*start) (AMPVoid);		//线程函数
	AMPVoid parg;					//参数
	AMThreadMutex	mutex;			//线程同步用到的Mutex
	bool   isStarted;				//标志线程函数是否开始运行.
};

AMThread gThread = NULL;

void* MainSchedulerThreadCallback(void* parg)
{
	AMThread_* pThread = (AMThread_*)gThread;

	SymbianMainScheduler* p = SymbianMainScheduler::NewL(CActiveScheduler::Current(), pThread->thread.Id());
	CActiveScheduler::Start();
	AMDelete(p);
	
	return NULL;
}

AMSDKHandle AlibabaMobileSDKInit()
{
	AMThreadCreate(&gThread, NULL, MainSchedulerThreadCallback, NULL);
	
	return (AMSDKHandle)gThread;
}

void AlibabaMobileSDKUnInit(AMSDKHandle handle)
{
	if(handle != NULL)
	{		
		//close scheduler.
		SymbianMainScheduler::GetInstance()->Close();
		
		//close thread.
		AMThreadWait((AMThread)handle, NULL);
	}
	
#ifdef AMOS_DEBUG
	PrintfLeakMemory();
#endif
}
