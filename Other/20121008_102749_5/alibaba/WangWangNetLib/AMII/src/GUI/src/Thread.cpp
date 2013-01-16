#include "AMGui.h"
#include "AMThread.h"

#ifdef WIN32
#include "windows.h"
#endif

__GUI_BEGIN_NAMESPACE
Thread::Thread(shared_ptr<Runnable> target)
{
	this->target = target;
	isLive = false;
}

Thread::Thread(shared_ptr<Runnable> target, shared_ptr<String> name)
{
	this->target = target;
	isLive = false;
}

Thread::Thread( F f,void* p )
{
	this->point = f;
	this->param = p;
}
bool Thread::start()
{	
	int res;
	if(point != NULL){
//#ifdef WIN32
//		DWORD dwThreadId, dwThrdParam = 1; 
//
//		HANDLE pThread = CreateThread( 
//			NULL,                        // no security attributes 
//			0,                           // use default stack size  
//			(unsigned long (WINAPI*)(void*))point, // thread function 
//			0,					 // argument to thread function 
//			0,                           // use default creation flags 
//			&dwThreadId);                // returns the thread identifier
//#else
		res = AMThreadCreate(&tid, NULL,point,param);
//#endif
	}
	else 
		res= AMThreadCreate(&tid, NULL, target->get(), NULL);
	if (res == 0)
	{
		isLive = true;
		return true;
	}
	else
	{
		return false;
	}
}

void Thread::run()
{

}

bool Thread::isAlive()
{
	return isLive;
}

void Thread::setPriority(int newPriority)
{
	priority = newPriority;
}

int Thread::getPriority()
{
	return priority;
}

void Thread::join()
{
	AMThreadWait(&tid, NULL);
	isLive = false;
}

Thread::~Thread()
{	
	if(tid != NULL)
		AMThreadWait(tid, NULL);
}
__GUI_END_NAMESPACE
