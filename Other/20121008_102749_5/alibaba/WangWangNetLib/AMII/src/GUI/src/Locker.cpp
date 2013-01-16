#include "AMGui.h"
#include "AMOS.h"

__GUI_BEGIN_NAMESPACE
Locker::Locker()
{	
	count = 0;
	AMThreadMutexCreate(&mutexLock);
	AMThreadCondCreate(&condLock);
	/*AMTimeval timeval;
	timeval.tv_sec = 0;
	timeval.tv_usec = 50 *1000;
	AMThreadMutexLock(&mutexLock);
	AMThreadCondTimewait (&condLock,&mutexLock,&timeval);
	AMThreadMutexUnlock(&mutexLock);*/
}

Locker::~Locker()
{
	AMThreadCondDestroy(&condLock);
	AMThreadMutexDestroy(&mutexLock);

}
void Locker::lock()
{	
	count ++;
	int p = int(mutexLock);
	if( p == 0x00273400){
		int i = 0;
		i ++;
	}
	AMThreadMutexLock(&mutexLock);
}
void Locker::unlock()
{	

	count --;
	int p = int(mutexLock);
	if( p == 0x00273400){
		int i = 0;
		i ++;
	}
	AMThreadMutexUnlock(&mutexLock);
}

void Locker::notify()
{
	AMThreadCondSignal(&condLock);
}
void Locker::notifyAll()
{
	AMThreadCondSignal(&condLock);
}

void Locker::wait(long timeout)
{
	if(timeout > 0 )
	{	
	//	long t = timeout + System::currentTimeMillis(); 
	/*	AMTimeval timeval;
		timeval.tv_sec = t/1000;
		timeval.tv_usec = (t% 1000) *1000;

		AMThreadCondTimewait (&condLock,&mutexLock,&timeval);*/

		struct AMTimeval tm;
		AMGetUTCTimeEx(&tm);
		tm.tv_sec += (timeout + tm.tv_usec / 1000) / 1000;
		tm.tv_usec = (((timeout + tm.tv_usec /1000)) % 1000) * 1000;
		AMThreadCondTimewait(&condLock,&mutexLock, &tm);
	//	AMThreadMutexUnlock(&looper->loop_cond_mutex);
	}
	else
		AMThreadCondWait(&condLock,&mutexLock);
}


__GUI_END_NAMESPACE
