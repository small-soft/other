#ifndef __LOCKER_H__
#define __LOCKER_H__

#include "inc/Object.h"
#include "inc/Config.h"
#include "AMThreadMutex.h"
__GUI_BEGIN_NAMESPACE
class Locker:public Object
{
public:
	Locker();
	virtual ~Locker();
private:
	AMThreadMutex mutexLock;
	AMThreadCond  condLock;
	int count;
public:
	void lock();
	void unlock();
	void notify();
	void notifyAll();
	void wait(long timeout = 0);
};
__GUI_END_NAMESPACE

#endif

