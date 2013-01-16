#ifndef __GUI_THREAD_H__
#define __GUI_THREAD_H__

#include "inc/Runnable.h"
#include "inc/String.h"

#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Thread : public Runnable
{
public:
	typedef void *(* F)(void *);
	Thread(shared_ptr<Runnable> target);
	Thread(F f,void* p);
	Thread(shared_ptr<Runnable> target, shared_ptr<String> name);
	virtual ~Thread() ;
public:
	static shared_ptr<Thread> currentThread();

	bool start();
	virtual void run();

	bool isAlive();
	void setPriority(int newPriority);
	int getPriority();
	void join();

private:
	int priority;
	bool isLive;

	AMThread tid;
	void* param;
	shared_ptr<Runnable> target;
};

__GUI_END_NAMESPACE

#endif
