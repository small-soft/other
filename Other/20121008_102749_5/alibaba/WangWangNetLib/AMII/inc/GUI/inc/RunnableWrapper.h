#ifndef __RUNNABLE_WRAPPER_H__
#define __RUNNABLE_WRAPPER_H__

#include "inc/Runnable.h"
#include "inc/Locker.h"
#include "inc/Object.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Locker;
class Form;
class Painter;

class RunnableWrapper:public Object,public Runnable
{
public:
	RunnableWrapper(void);
	RunnableWrapper(shared_ptr<Form> parentForm, shared_ptr<Painter> paint, bool reverse);
	RunnableWrapper(shared_ptr<Runnable> internal, int type);
	virtual ~RunnableWrapper(void);
	static void deinitialize();
private:
	static shared_ptr<Locker> THREADPOOL_LOCK;// = new Object();
	static shared_ptr<Vector<shared_ptr<Runnable> > > threadPool;// = new Vector();
	static int threadCount;// = 0;
	static int maxThreadCount;// = 3;
	static int availableThreads;// = 0;

	bool done;// = false;
	shared_ptr<Runnable> internal;
	int type;
	shared_ptr<Form> parentForm;
	shared_ptr<Painter> paint;
	bool reverse;
public:
	void setDone(bool done);
	bool isDone();
	virtual void run();
	static void pushToThreadPull(shared_ptr<Runnable> r);
};

__GUI_END_NAMESPACE

#endif
