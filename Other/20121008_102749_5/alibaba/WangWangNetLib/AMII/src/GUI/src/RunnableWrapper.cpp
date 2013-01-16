#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
shared_ptr<Locker> RunnableWrapper::THREADPOOL_LOCK = new Locker();
shared_ptr<Vector<shared_ptr<Runnable> > > RunnableWrapper::threadPool = new Vector<shared_ptr<Runnable> >;
int RunnableWrapper::threadCount = 0;
int RunnableWrapper::maxThreadCount = 3;
int RunnableWrapper::availableThreads  = 0 ;

RunnableWrapper::RunnableWrapper(void)
{
	done = false;
	reverse = false;
	type = 0;
}

RunnableWrapper::RunnableWrapper( shared_ptr<Form> parentForm, shared_ptr<Painter> paint, bool reverse )
{
	done = false;
	reverse = false;
	type = 0;
	this->parentForm = parentForm;
	this->paint = paint;
	this->reverse = reverse;
}

RunnableWrapper::RunnableWrapper( shared_ptr<Runnable> internal, int type )
{
	done = false;
	reverse = false;
	this->internal = internal;
	this->type = type;
}
RunnableWrapper::~RunnableWrapper(void)
{
}

void RunnableWrapper::setDone( bool done )
{
	  this->done = done;
}

bool RunnableWrapper::isDone()
{
	return done;
}

void RunnableWrapper::run()
{
	if(parentForm.get() != NULL) {
		// set current form uses this portion to make sure all set current operations
		// occur on the EDT
		if(paint.get() == NULL) {
			Display::getInstance()->setCurrent(parentForm, reverse);
			return;
		}

		Dialog *dlg = dynamic_cast<Dialog*>(parentForm.get());
		while ( dlg!= NULL &&!dlg->isDisposed()) {
			
				Display::lock->lock();
				{
					Display::lock->wait(40);
				}
				Display::lock->unlock();
			
		}
		parentForm->getStyle()->setBgPainter(paint);
	} else {
		switch(type) {
				case 0: 
					internal->run();
					done = true;
					Display::lock->lock();
					{
						Display::lock->notify();
					}
					Display::lock->unlock();
					break;
				case 1:
					internal->run();			
					break;
				case 2:
					while(!done) {
						Display::lock->lock();
						{				
							Display::lock->wait(10);			
						}
						Display::lock->unlock();
					}
					break;
				case 3:
					Display::getInstance()->mainEDTLoop();
					break;
				case 4:
					while(true) {
						shared_ptr<Runnable> r ;
						THREADPOOL_LOCK->lock();
						{
							if(threadPool->size() > 0) {
								r = threadPool->elementAt(0);
								threadPool->removeElementAt(0);
							} else {							
									availableThreads++;
									THREADPOOL_LOCK->wait();		
							}
						}
						THREADPOOL_LOCK->unlock();
						if(r.get() != NULL) {
							availableThreads--;
							r->run();
						}
					}
		}
	}
	done = true;

}

void RunnableWrapper::pushToThreadPull(shared_ptr<Runnable> r )
{
	if(availableThreads == 0 && threadCount < maxThreadCount) {
		threadCount++;
		shared_ptr<Runnable> r;
		shared_ptr<RunnableWrapper> wrapper = new  RunnableWrapper(r, 4);
		String tempString(L"invokeAndBlock");
		shared_ptr<String>id = new String((tempString + System::getString(threadCount)));
		shared_ptr<Thread> poolThread = new Thread(wrapper, id);
		poolThread->start();
	}
	THREADPOOL_LOCK->lock();
	{
		threadPool->addElement(r);
		THREADPOOL_LOCK->notify();
	}
	THREADPOOL_LOCK->unlock();
}

void RunnableWrapper::deinitialize()
{
	THREADPOOL_LOCK.reset();
	threadPool.reset();
}
__GUI_END_NAMESPACE
