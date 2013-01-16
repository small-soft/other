#include "AMGui.h"
#include "AMOS.h"


__GUI_BEGIN_NAMESPACE
shared_ptr<Display> Display::INSTANCE;// = new Display();
shared_ptr<Locker>	Display::lock;// = new Locker();
shared_ptr<Locker>	Display::lockThread;

int Display::transitionDelay = -1;

Display::Display(void)
{
	touchScreen = false;
	lightMode = false;
	editingText = false;
	longPointerCharged = false;
	keyRepeatCharged = false;
	longPressCharged = false;
	keyReleasedSinceEdit = false;
	processingSerialCalls = false;
	PATHLENGTH = 0;

	showDuringEdit = 0;
	pointerX = 0;
	pointerY = 0;
	longKeyPressTime = 0;
	lwuitRunning = false;
	framerateLock = 20;
	pendingSerialCalls = new Vector<shared_ptr<Runnable> >;
	thirdSoftButton = false;
	inputEvents = new Vector<shared_ptr<VectorArray<int> > >;
	longPressInterval = 800;
	nextKeyRepeatEvent = 0;
	keyRepeatValue = 0;
	keyRepeatInitialIntervalTime = 800;
	keyRepeatNextIntervalTime = 10;
	dragPathOffset = 0;
	dragPathLength = 0;
	lastInputEvent = -1;
	lastInputKeyCode = -1;
	hide = false;
	time = 0;
	lastKeyPressed = 0;
}

Display::~Display(void)
{	
	lwuitRunning = false;	
//	lock->notifyAll();
}

shared_ptr<Display> Display::getInstance()
{
	return INSTANCE;
}

void Display::deinitialize() {
	INSTANCE->lwuitRunning = false;
	
	lock->lock();
	{
		lock->notifyAll();
	}
	lock->unlock();

	 // 保证gui thread 退出, 调用线程在此等待
	 lockThread->lock();
	 lockThread->unlock();
	 
	 //INSTANCE->edt->join();
	 lock.reset();
	 INSTANCE->lwuitGraphics.reset();
	 INSTANCE->impl.reset();
	 INSTANCE->edt.reset();
	 INSTANCE.reset();
	 Border::deinitialize();
	
	 ImplementationFactory::deinitialize();
	 IndexedImage::deinitialize();
	 LWUITImplementation::deinitialize();
	 RunnableWrapper::deinitialize();
	 UIManager::deinitialize();
	 Font::deinitialize();
}
int Display::getDisplayWidth()
{
	return impl->getDisplayWidth();
}


int Display::getDisplayHeight()
{
	return impl->getDisplayHeight();
}

float Display::getDragSpeed( bool yAxis )
{
	float speed;
	if(yAxis)
	{
		speed = impl->getDragSpeed(dragPathY, dragPathTime, dragPathOffset, dragPathLength);
	}
	else
	{
		speed = impl->getDragSpeed(dragPathX, dragPathTime, dragPathOffset, dragPathLength);
	}
	dragPathLength = 0;
	return speed;

}
int Display::getLastInputEvent()
{
	return lastInputEvent;
}

int Display::getLastKeyCode()
{
	return lastInputKeyCode;
}

void Display::setHide( bool b )
{
	hide = b;
}

shared_ptr<Vector<shared_ptr<Animation> > > Display::getAnimationQueue()
{
	return animationQueue;
}
void Display::init( void* m )
{	
	if(INSTANCE.get() == NULL){
		initStatic();
	}
	if(INSTANCE->impl.get() == NULL) {
		INSTANCE->lwuitRunning = true;
		INSTANCE->impl = ImplementationFactory::getInstance()->createImplementation();
		INSTANCE->impl->setDisplayLock(lock);
		INSTANCE->impl->init(m);
		INSTANCE->lwuitGraphics = new Graphics(INSTANCE->impl->getNativeGraphics());
		INSTANCE->impl->setLWUITGraphics(INSTANCE->lwuitGraphics);

		// only enable but never disable the third softbutton
		if(INSTANCE->impl->isThirdSoftButton()) {
			INSTANCE->thirdSoftButton = true;
		}
		if(INSTANCE->impl->getSoftkeyCount() > 0) {
			Form::leftSK = INSTANCE->impl->getSoftkeyCode(0)->elementAt(0);
			if(INSTANCE->impl->getSoftkeyCount() > 1) {
				Form::rightSK = INSTANCE->impl->getSoftkeyCode(1)->elementAt(0);
				if(INSTANCE->impl->getSoftkeyCode(1)->size() > 1){
					Form::rightSK2 = INSTANCE->impl->getSoftkeyCode(1)->elementAt(1);
				}
			}
			Form::backSK = INSTANCE->impl->getBackKeyCode();
			Form::backspaceSK = INSTANCE->impl->getBackspaceKeyCode();
			Form::clearSK = INSTANCE->impl->getClearKeyCode();
		}

		int width = INSTANCE->getDisplayWidth();
		int height = INSTANCE->getDisplayHeight();
		int colors = INSTANCE->numColors();


		INSTANCE->PATHLENGTH = INSTANCE->impl->getDragPathLength();
		INSTANCE->dragPathX = new VectorArray<float>(INSTANCE->PATHLENGTH);
		INSTANCE->dragPathY = new VectorArray<float>(INSTANCE->PATHLENGTH);
		INSTANCE->dragPathTime = new VectorArray<long>(INSTANCE->PATHLENGTH);

		// if the resolution is very high and the amount of memory is very low while the device 
		// itself has many colors (requiring 32 bits per pixel) then we should concerve memory
		// by activating light mode.
//		INSTANCE->lightMode = colors > 65536 && width * height * 30 > Runtime.getRuntime().totalMemory();

		// this can happen on some cases where an application was restarted etc...
		// generally its probably a bug but we can let it slide...
		if(INSTANCE->edt.get() == NULL) {
			INSTANCE->touchScreen = INSTANCE->impl->isTouchDevice();

			// initialize the LWUIT EDT which from now on will take all responsibility
			// for the event delivery->
			
		//	AMThreadCreate(&tid, NULL, thread_run, INSTANCE.get());
			INSTANCE->edt = new Thread(thread_run,NULL);
			//INSTANCE->edt->setPriority(Thread->NORM_PRIORITY + 1);
			INSTANCE->edt->start();
			
		/*	F f= &Display::mainEDTLoop;
			INSTANCE->edt = new Thread(f);
			INSTANCE->edt->start();*/
		}
	}

}
void * Display::thread_run(void *p)
{
	lockThread->lock();
	INSTANCE->mainEDTLoop();
	lockThread->unlock();
	return 0;
}
int Display::getDragStartPercentage()
{
	return getImplementation()->getDragStartPercentage();
}

void Display::setDragStartPercentage( int dragStartPercentage )
{
	 getImplementation()->setDragStartPercentage(dragStartPercentage);
}

shared_ptr<LWUITImplementation> Display::getImplementation()
{
	  return impl;
}

void Display::setFramerate( int rate )
{
	 framerateLock = 1000 / rate;
}

void Display::vibrate( int duration)
{
	impl->vibrate(duration);
}

void Display::flashBacklight( int duration )
{
	impl->flashBacklight(duration);
}

void Display::setShowDuringEditBehavior( int showDuringEdit )
{
	this->showDuringEdit = showDuringEdit;	
}

int Display::getShowDuringEditBehavior()
{
	return showDuringEdit;
}

int Display::getFrameRate()
{
	return 1000 / framerateLock;
}

bool Display::isEdt()
{
	return true;
}

void Display::playDialogSound( const int type )
{
	 impl->playDialogSound(type);
}

void Display::callSerially( shared_ptr<Runnable> r )
{

}

void Display::flushEdt()
{
	if(!isEdt()){
		return;
	}
}

void Display::callSeriallyAndWait( shared_ptr<Runnable> r )
{

}

void Display::restoreMenu( shared_ptr<Form> f )
{
	if(f.get() != NULL) {
		f->restoreMenu();
	}
}

void Display::paintTransitionAnimation()
{
	shared_ptr<Animation> ani =  animationQueue->elementAt(0);
	if (!ani->animate()) {
		animationQueue->removeElementAt(0);
		shared_ptr<Transition> tran = static_pointer_cast<Transition>(ani);
		if (tran != NULL) {
			shared_ptr<Form> f = dynamic_pointer_cast<Form>(tran->getSource());
			shared_ptr<Form> source = f;
			restoreMenu(source);

			if (animationQueue->size() > 0) {
				ani =  animationQueue->elementAt(0);
				shared_ptr<Transition> tran = static_pointer_cast<Transition>(ani);
				if (tran != NULL) {
					tran->initTransition();
				}
			}else{
				shared_ptr<Form> p= dynamic_pointer_cast<Form>(tran->getDestination());
				shared_ptr<Form> f = p;
				restoreMenu(f);
				if (source.get() == NULL || source == impl->getCurrentForm() || source == getCurrent()) {
					setCurrentForm(f);
				}
				tran->cleanup();
			}
			return;
		}
	}
	ani->paint(lwuitGraphics);
	impl->flushGraphics();

	if(transitionDelay > 0) {
		// yield for a fraction, some devices don't "properly" implement
		// flush and so require the painting thread to get CPU too.
		
			lock->lock();	
			{
				lock->wait(transitionDelay);
			}
			lock->unlock();	
	}

}




void Display::mainEDTLoop()
{
		lock->lock();	
		{
			// when there is no current form the EDT is useful only
			// for features such as call serially
			while(impl->getCurrentForm().get() == NULL) {
				if(shouldEDTSleep()) {
					lock->wait();
				}

				// paint transition or intro animations and don't do anything else if such
				// animations are in progress...
				if(animationQueue.get() != NULL && animationQueue->size() > 0) {
					paintTransitionAnimation();
					continue;
				}
				processSerialCalls();
			}
		}
		lock->unlock();

	while(lwuitRunning) {
			// wait indefinetly but no more than the framerate if
			// there are no animations... If animations exist then
			// only wait for the framerate
			// Lock surrounds the should method to prevent serial calls from
			// getting "lost"
			lock->lock();
			{
				if(shouldEDTSleep()) {
					impl->edtIdle(true);
					lock->wait();
					impl->edtIdle(false);
				}
			} 
			lock->unlock();
			edtLoopImpl();
	}
	/*lock.reset();
	INSTANCE->impl.reset();
	INSTANCE->lwuitGraphics.reset();
	INSTANCE->edt.reset();*/

}

void Display::edtLoopImpl()
{
		// transitions shouldn't be bound by framerate
		// modified by jiajing
		// if(animationQueue == null || animationQueue.size() == 0) {
		if(  animationQueue.get() == NULL || animationQueue->size() == 0) {
				//end
				// prevents us from waking up the EDT too much and 
				// thus exhausting the systems resources. The + 1
				// prevents us from ever waiting 0 milliseconds which
				// is the same as waiting with no time limit
				if(inputEvents->size() == 0 )
				{
					lock->lock();
					{	
						lock->wait(max(30, framerateLock - (int)time));
					}
					lock->unlock();
				}
			

		} else {
			// paint transition or intro animations and don't do anything else if such
			// animations are in progress...
			paintTransitionAnimation();
			return;
		}

		long currentTime = System::currentTimeMillis();

	while(inputEvents->size() > 0) {
		shared_ptr<VectorArray<int> > i = inputEvents->elementAt(0);
		inputEvents->removeElementAt(0);
		handleEvent(i);
	}

	lwuitGraphics->setGraphics(impl->getNativeGraphics());
	impl->paintDirty();

	// draw the animations
	shared_ptr<Form> current = impl->getCurrentForm();
	current->repaintAnimations();

	// check key repeat events
	long t = System::currentTimeMillis();
	/*if(keyRepeatCharged && nextKeyRepeatEvent <= t) {
		current->keyRepeated(keyRepeatValue);
		nextKeyRepeatEvent = t + keyRepeatNextIntervalTime;
	}*/
	if(longPressCharged && longPressInterval <= t - longKeyPressTime) {
		longPressCharged = false;
		current->longKeyPress(keyRepeatValue);
	}
	if(longPointerCharged && longPressInterval <= t - longKeyPressTime) {
		longPointerCharged = false;
		current->longPointerPress(pointerX, pointerY);
	}
	processSerialCalls();
	time = System::currentTimeMillis() - currentTime;

}

bool Display::hasNoSerialCallsPending()
{
	return pendingSerialCalls->size() == 0;
}

void Display::onEditingComplete( shared_ptr<Component> c, shared_ptr<String> text )
{
	 c->onEditComplete(text);
}

void Display::processSerialCalls()
{
	processingSerialCalls = true;
	int size = pendingSerialCalls->size();
	if(size > 0) {
		shared_ptr<VectorArray<shared_ptr<Runnable> > >  array = new VectorArray<shared_ptr<Runnable> >(size);

		// copy all elements to an array and remove them otherwise invokeAndBlock from
		// within a callSerially() can cause an infinite loop...
		for(int iter = 0 ; iter < size ; iter++) {
			(*array)[iter] = pendingSerialCalls->elementAt(iter);
		}

		lock->lock();		
		{
			if(size == pendingSerialCalls->size()) {
				// this is faster
				pendingSerialCalls->removeAllElements();
			} else {
				// this can occur if an element was added during the loop
				for(int iter = 0 ; iter < size ; iter++) {
					pendingSerialCalls->removeElementAt(0);
				}
			}
		}
		lock->unlock();

		for(int iter = 0 ; iter < size ; iter++) {
			(*array)[iter]->run();
		}

		// after finishing an event cycle there might be serial calls waiting
		// to return.
		lock->lock();
		{
			lock->notify();
		}
		lock->unlock();
	}
	processingSerialCalls = false;

}

bool Display::isProcessingSerialCalls()
{
	 return processingSerialCalls;
}

void Display::notifyDisplay()
{
	lock->lock();
	{
		lock->notify();
	}
	lock->unlock();
}

void Display::invokeAndBlock( shared_ptr<Runnable> r )
{
	if(isEdt()) {
		// this class allows a runtime exception to propogate correctly out of the
		// internal thread
		shared_ptr<RunnableWrapper> w = new RunnableWrapper(r, 1);
		RunnableWrapper::pushToThreadPull(w);

		// loop over the EDT until the thread completes then return
		while(!w->isDone()) {		
				edtLoopImpl();
				lock->lock();				
				{
					lock->wait(framerateLock);
				}
				lock->unlock();
		}
		// if the thread thew an exception we need to throw it onwards
		//if(w->getErr() != NULL) {
		//	return;//throw wgetErr();
		//}
	} else {
		r->run();
	}

}

bool Display::isTouchScreenDevice()
{
	 return touchScreen;
}

void Display::setTouchScreenDevice( bool touchScreen )
{
	 this->touchScreen = touchScreen;
}

void Display::setCurrent( shared_ptr<Form> newForm, bool reverse )
{
	if(edt.get() == NULL) {
	    return ;//	throw new IllegalStateException("Initialize must be invoked before setCurrent!");
	}

	if(isVirtualKeyboardShowingSupported()) {
		setShowVirtualKeyboard(false);
	}

	if(editingText) {
		switch(showDuringEdit) {
				case SHOW_DURING_EDIT_ALLOW_DISCARD:
					break;
				case SHOW_DURING_EDIT_ALLOW_SAVE:
					impl->saveTextEditingState();
					break;
				case SHOW_DURING_EDIT_EXCEPTION:
					return;//throw new IllegalStateException("Show during edit");
				case SHOW_DURING_EDIT_IGNORE:
					return;
				case SHOW_DURING_EDIT_SET_AS_NEXT:
					impl->setCurrentForm(newForm);
					return;
		}
	}

	if(!isEdt()) {
		shared_ptr<Painter> painter;
		callSerially(new RunnableWrapper(newForm, painter, reverse));
		return;
	}

	shared_ptr<Form> current = impl->getCurrentForm();
	if(current.get() != NULL){
		if(current->isInitialized()) {
			current->deinitializeImpl();
		}
	}
	if(!newForm->isInitialized()) {
		newForm->initComponentImpl();
	}

	if(newForm->getWidth() != getDisplayWidth() || newForm->getHeight() != getDisplayHeight()) {
		newForm->setShouldCalcPreferredSize(true);
		newForm->layoutContainer();
	}

//	synchronized(lock) 
	lock->lock();
	{
		bool transitionExists = false;
		if(animationQueue.get() != NULL && animationQueue->size() > 0) {
			shared_ptr<Animation> o = animationQueue->lastElement();
			Transition* tran = dynamic_cast<Transition*>(o.get());
			if(tran != NULL) {
				//check if use weak pointer
				Form* f = dynamic_cast<Form*>(tran->getDestination().get());
				current = f->shared_from_this();
				impl->setCurrentForm(current);
			}
		}

		if(current.get() != NULL) {
			// make sure the fold menu occurs as expected then set the current
			// to the correct parent!
			Dialog *dlg = dynamic_cast<Dialog *>(current.get());
			if(dlg!=NULL&& dlg->isMenu()) {
				shared_ptr<Transition> t = current->getTransitionOutAnimator();
				if(t.get() != NULL) {
					// go back to the parent form first
					if(dlg->getPreviousForm().get() != NULL) {
						initTransition(t->copy(false), current, dlg->getPreviousForm());
					}
				}
				current = dlg->getPreviousForm();
				impl->setCurrentForm(current);
			}

			// prevent the transition from occurring from a form into itself
			if(newForm != current) {
				if((current.get() != NULL && current->getTransitionOutAnimator().get() != NULL) || newForm->getTransitionInAnimator().get() != NULL) {
					if(animationQueue.get() == NULL) {
						animationQueue = new Vector<shared_ptr<Animation> >();
					}
					// prevent form transitions from breaking our dialog based
					// transitions which are a bit sensitive
					Dialog *dlg = dynamic_cast<Dialog *>(newForm.get());
					if(current.get() != NULL && (dlg == NULL)) {
						shared_ptr<Transition> t = current->getTransitionOutAnimator();
						if(current.get() != NULL && t.get() != NULL) {
							initTransition(t->copy(reverse), current, newForm);
							transitionExists = true;
						}
					}
					dlg = dynamic_cast<Dialog *>(current.get());
					if(current.get() != NULL && dlg == NULL) {
						shared_ptr<Transition> t = newForm->getTransitionInAnimator();
						if(t.get() != NULL) {
							initTransition(t->copy(reverse), current, newForm);
							transitionExists = true;
						}
					}
				}
			}
		}
		lock->notify();

		if(!transitionExists) {
			if(animationQueue.get() == NULL || animationQueue->size() == 0) {
				setCurrentForm(newForm);
			} else {
				// we need to add an empty transition to "serialize" this
				// screen change...
				shared_ptr<Transition> t = CommonTransitions::createEmpty();
				initTransition(t, current, newForm);
			}
		}
	}
	lock->unlock();
}

void Display::initTransition( shared_ptr<Transition> transition, shared_ptr<Form> source, shared_ptr<Form> dest )
{
	dest->setVisible(true);
	transition->init(source, dest);
	animationQueue->addElement(transition);

	if(animationQueue->size() == 1) {
		transition->initTransition();
	}

}

void Display::setCurrentForm( shared_ptr<Form> newForm )
{
	shared_ptr<Form> current = impl->getCurrentForm();
	if(current.get() != NULL){
		current->setVisible(false);
	}
	current = newForm;
	impl->setCurrentForm(current);
	current->setVisible(true);
	impl->confirmControlView();
	int w = current->getWidth();
	int h = current->getHeight();
	if(isEdt() && ( w != impl->getDisplayWidth() || h != impl->getDisplayHeight())){
		current->setSize(new Dimension(impl->getDisplayWidth(), impl->getDisplayHeight()));

		current->setShouldCalcPreferredSize(true);
		current->layoutContainer();
	}
	lastKeyPressed = 0;
	shared_ptr<Animation> ani = dynamic_pointer_cast<Animation>(newForm);
//	Form* f = dynamic_cast<Form*>(ani.get());
	repaint(ani);
	newForm->onShowCompleted();

}

void Display::setTransitionYield( int transitionD )
{
	  transitionDelay = transitionD;
}

void Display::editString( shared_ptr<Component> cmp, int maxSize, int constraint, shared_ptr<String> text )
{
	editingText = true;
	keyRepeatCharged = false;
	longPressCharged = false;
	keyReleasedSinceEdit = false;
	lastKeyPressed = 0;
	impl->editString(cmp, maxSize, constraint, text);
	editingText = false;

}

bool Display::minimizeApplication()
{
	return getImplementation()->minimizeApplication();
}

bool Display::isMinimized()
{
	return getImplementation()->isMinimized();
}

void Display::restoreMinimizedApplication()
{
	 getImplementation()->restoreMinimizedApplication();
}

void Display::addInputEvent( shared_ptr<VectorArray<int> > ev )
{
	lock->lock();
	{
		inputEvents->addElement(ev);
		lock->notify();
	}
	lock->unlock();
}

shared_ptr<VectorArray<int> > Display::createPointerEvent( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y, int eventType )
{

	if(x->size() == 1) 
	{
		shared_ptr<VectorArray<int> > arr = new VectorArray<int>[3];
		(*arr)[0] = eventType;
		(*arr)[1] = (*x)[0];
		(*arr)[2] = (*y)[0];
		return arr;
	}

	shared_ptr<VectorArray<int> > arr = new VectorArray<int>[1 + x->size() * 2];
	(*arr)[0] = eventType;
	int arrayOffset = 1;
	for(int iter = 0 ; iter < x->size() ; iter++) 
	{
		(*arr)[arrayOffset] = (*x)[iter];
		arrayOffset++;
		(*arr)[arrayOffset] = (*y)[iter];
		arrayOffset++;
	}
	return arr;
}

shared_ptr<VectorArray<int> > Display::createKeyEvent( int keyCode, bool pressed )
{
	shared_ptr<VectorArray<int> > arr = new VectorArray<int>(2);
	if(pressed) 
	{
		(*arr)[0] = KEY_PRESSED;
		(*arr)[1] = keyCode;
		return arr;
	}
	else
	{
		(*arr)[0] = KEY_RELEASED;
		(*arr)[1] = keyCode;
		return arr;
	}

}

void Display::keyPressed( const int keyCode )
{
	if(impl->getCurrentForm().get() == NULL)
	{
		return;
	}
	addInputEvent(createKeyEvent(keyCode, true));

	// this solves a Sony Ericsson bug where on slider open/close someone "brilliant" chose
	// to send a keyPress with a -43/-44 keycode... Without ever sending a key release!
	keyRepeatCharged = (keyCode >= 0 || getGameAction(keyCode) > 0);
	longPressCharged = keyRepeatCharged;
	longKeyPressTime = System::currentTimeMillis();
	keyRepeatValue = keyCode;
	nextKeyRepeatEvent = System::currentTimeMillis() + keyRepeatInitialIntervalTime;
	lastKeyPressed = keyCode;

}

void Display::keyReleased( const int keyCode )
{
	keyRepeatCharged = false;
	longPressCharged = false;
	if(impl->getCurrentForm().get() == NULL){
		return;
	}
	// this can happen when traversing from the native form to the current form
	// caused by a keypress
	if((!keyReleasedSinceEdit) && keyCode != lastKeyPressed) {
		return;
	}
	keyReleasedSinceEdit = true;
	addInputEvent(createKeyEvent(keyCode, false));

}

void Display::keyRepeatedInternal( const int keyCode )
{

}

void Display::pointerHover( shared_ptr<VectorArray<int> >x, shared_ptr<VectorArray<int> > y )
{
	if(impl->getCurrentForm().get() == NULL)
	{
		return;
	}
	addInputEvent(createPointerEvent(x, y, POINTER_HOVER));

}

void Display::pointerHoverReleased( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> >y )
{
	if(impl->getCurrentForm().get() == NULL)
	{
		return;
	}
	addInputEvent(createPointerEvent(x, y, POINTER_HOVER_RELEASED));

}

void Display::pointerPressed( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y )
{
	if(impl->getCurrentForm().get() == NULL)
	{
		return;
	}
	longPointerCharged = true;
	longKeyPressTime = System::currentTimeMillis();
	pointerX = (*x)[0];
	pointerY = (*y)[0];
	addInputEvent(createPointerEvent(x, y, POINTER_PRESSED));
}

void Display::pointerReleased( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y )
{
	longPointerCharged = false;
	if(impl->getCurrentForm().get() == NULL)
	{
		return;
	}
	addInputEvent(createPointerEvent(x, y, POINTER_RELEASED));

}

void Display::sizeChanged( int w, int h )
{
	shared_ptr<Form> current = impl->getCurrentForm();
	if(current.get() == NULL) {
		return;
	}
	if(w == current->getWidth() && h == current->getHeight()) {
		return;
	}

	addInputEvent(createSizeChangedEvent(w, h));

}

shared_ptr<VectorArray<int> > Display::createSizeChangedEvent( int w, int h )
{
	shared_ptr<VectorArray<int> > vect = new VectorArray<int>(3);
	(*vect)[0] = (SIZE_CHANGED);
	(*vect)[1] = (w);
	(*vect)[2] = (h);
	return vect;
}

void Display::hideNotify()
{
	keyRepeatCharged = false;
	longPressCharged = false;
	longPointerCharged = false;

	shared_ptr<VectorArray<int> > vect = new VectorArray<int>(1);
	(*vect)[0] = (HIDE_NOTIFY);
	addInputEvent(vect);
}

void Display::showNotify()
{	
	shared_ptr<VectorArray<int> > vect = new VectorArray<int>(1);
	(*vect)[0] = (SHOW_NOTIFY);

	addInputEvent(vect);        
}

bool Display::shouldEDTSleepNoFormAnimation()
{
	lock->lock();
	{
		return inputEvents->size() == 0 &&
			hasNoSerialCallsPending() && 
			(!keyRepeatCharged || !longPressCharged);
	}
	lock->unlock();
}

void Display::updateDragSpeedStatus(shared_ptr<VectorArray<int> > ev )
{
	//save dragging input to calculate the dragging speed later
	(*dragPathX)[dragPathOffset] = (float)(*pointerEvent(1, ev))[0];
	(*dragPathY)[dragPathOffset] = (float)(*pointerEvent(2, ev))[0];
	
	(*dragPathTime)[dragPathOffset] = System::currentTimeMillis();
	if (dragPathLength < PATHLENGTH) 
	{
		dragPathLength++;
	}
	dragPathOffset++;
	if (dragPathOffset >= PATHLENGTH) 
	{
		dragPathOffset = 0;
	}

}

void Display::handleEvent( shared_ptr<VectorArray<int> > ev )
{
	shared_ptr<Form> f = getCurrentUpcomingForm(true);
	// modified by jiajing
	lastInputEvent = (*ev)[0]; 
	if(ev->size() > 1)
	{
		lastInputKeyCode = (*ev)[1];
	}
	//end
	switch((*ev)[0]) 
	{
		case KEY_PRESSED:
			f->keyPressed((*ev)[1]);
			break;
		case KEY_RELEASED:
			f->keyReleased((*ev)[1]);
			break;
		case POINTER_PRESSED:
			f->Component::pointerPressed(pointerEvent(1, ev), pointerEvent(2, ev));
			break;
		case POINTER_RELEASED:
			f->Component::pointerReleased(pointerEvent(1, ev), pointerEvent(2, ev));
			break;
		case POINTER_DRAGGED:
			updateDragSpeedStatus(ev);
			f->Component::pointerDragged(pointerEvent(1, ev), pointerEvent(2, ev));
			break;
		case POINTER_HOVER:
			updateDragSpeedStatus(ev);
			f->pointerHover(pointerEvent(1, ev), pointerEvent(2, ev));
			break;
		case POINTER_HOVER_RELEASED:
			f->pointerHoverReleased(pointerEvent(1, ev), pointerEvent(2, ev));
			break;
		case SIZE_CHANGED:
			f->sizeChangedInternal((*ev)[1], (*ev)[2]);
			break;
		case HIDE_NOTIFY:
			f->hideNotify();
			break;
		case SHOW_NOTIFY:
			f->showNotify();
			break;    
	}

}

shared_ptr<VectorArray<int> > Display::pointerEvent( int off, shared_ptr<VectorArray<int> > event )
{
	shared_ptr<VectorArray<int> > peX = new VectorArray<int>(event->size() / 2);
	int offset = 0;
	for( int iter = off ; iter < event->size() ; iter+=2 ) 
	{
		(*peX)[offset] = (*event)[iter];
		offset++;
	}
	return peX;

}

bool Display::shouldEDTSleep()
{
	shared_ptr<Form> current = impl->getCurrentForm();
	return (current.get() == NULL || (!current->hasAnimations())) &&
		(animationQueue.get() == NULL || animationQueue->size() == 0) &&
		inputEvents->size() == 0 &&
		(!impl->hasPendingPaints()) &&
		hasNoSerialCallsPending() && !keyRepeatCharged 
		&& !longPointerCharged;

}

shared_ptr<Object> Display::getVideoControl( shared_ptr<Object> player )
{
	return impl->getVideoControl(player);
}

shared_ptr<Form> Display::getCurrentInternal()
{
	return impl->getCurrentForm();
}

shared_ptr<Form> Display::getCurrentUpcoming()
{
	return getCurrentUpcomingForm(false);
}

shared_ptr<Form> Display::getCurrentUpcomingForm( bool includeMenus )
{
	shared_ptr<Form> upcoming ;

	// we are in the middle of a transition so we should extract the next form
	if(animationQueue.get() != NULL) {
		int size = animationQueue->size();
		for(int iter = 0 ; iter < size ; iter++) {
			shared_ptr<Animation> ani = animationQueue->elementAt(iter);
			Transition* tran = dynamic_cast<Transition*>(ani.get());
			if(tran!=NULL) {
				Form* f = dynamic_cast<Form*>(tran->getDestination().get());
				upcoming = f->shared_from_this();
			}
		}
	}
	if(upcoming.get() == NULL) {
		if(includeMenus){
			shared_ptr<Form> f = impl->getCurrentForm();
			Dialog *dlg = dynamic_cast<Dialog *>(f.get());
			if(dlg != NULL) {
				if(dlg->isDisposed()) {
					return getCurrent();
				}
			}
			return f;
		}else{
			return getCurrent();
		}
	}
	return upcoming;

}

shared_ptr<Form> Display::getCurrent()
{
	shared_ptr<Form> current = impl->getCurrentForm();
	Dialog *dlg = dynamic_cast<Dialog *>(current.get());
	if(current.get() != NULL && dlg!= NULL) 
	{
		if(dlg->isMenu() || dlg->isDisposed()) 
		{
			shared_ptr<Form> p = current->getPreviousForm();
			if(p.get() != NULL) 
			{
				return p;
			}

			// we are in the middle of a transition so we should extract the next form
			int size = animationQueue->size();
			for(int iter = 0 ; iter < size ; iter++) 
			{
				shared_ptr<Animation> ani = animationQueue->elementAt(iter);
				Transition* tran = dynamic_cast<Transition*>(ani.get());
				if(tran != NULL) 
				{
					Form *f = dynamic_cast<Form*>(tran->getDestination().get());
					shared_ptr<Form> ret = f;
					return f;
				}
			}
		}
	}
	return current;

}

int Display::numAlphaLevels()
{
	 return impl->numAlphaLevels();
}

int Display::numColors()
{
	 return impl->numColors();
}

bool Display::isLightMode()
{
	return lightMode;
}

void Display::setLightMode( bool lightMode )
{
	 this->lightMode = lightMode;
}

void Display::repaint(shared_ptr<Animation> cmp )
{
	 impl->repaint(cmp);
}

int Display::getGameAction( int keyCode )
{
	 return impl->getGameAction(keyCode);
}

int Display::getKeyCode( int gameAction )
{
	 return impl->getKeyCode(gameAction);
}

bool Display::isThirdSoftButton()
{
	 return thirdSoftButton;
}

void Display::setThirdSoftButton( bool thirdSoftButton )
{
	 this->thirdSoftButton = thirdSoftButton;
}

void Display::setShowVirtualKeyboard( bool show )
{
	  impl->setShowVirtualKeyboard(show);
}

bool Display::isVirtualKeyboardShowing()
{
	  return impl->isVirtualKeyboardShowing();
}

bool Display::isVirtualKeyboardShowingSupported()
{
	return impl->isVirtualKeyboardShowingSupported();
}

int Display::getKeyboardType()
{
	return impl->getKeyboardType();
}

bool Display::isNativeInputSupported()
{
	return false;
}

bool Display::isMultiTouch()
{
	return impl->isMultiTouch();
}

bool Display::isClickTouchScreen()
{
	 return impl->isClickTouchScreen();
}

bool Display::isBidiAlgorithm()
{
	 return impl->isBidiAlgorithm();
}

void Display::setBidiAlgorithm( bool activate )
{
	 impl->setBidiAlgorithm(activate);
}

shared_ptr<String>  Display::convertBidiLogicalToVisual( shared_ptr<String> s )
{
	return impl->convertBidiLogicalToVisual(s);
}

int Display::getCharLocation( shared_ptr<String>  source, int index )
{
	return impl->getCharLocation(source, index);
}

bool Display::isRTL( char c )
{
	return impl->isRTL(c);
}

void Display::pointerDragged( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y )
{
	if(impl->getCurrentForm().get() == NULL)
	{
		return;
	}
	longPointerCharged = false;
	addInputEvent(createPointerEvent(x, y, POINTER_DRAGGED));
}

shared_ptr<InputStream> Display::getResourceAsStream(shared_ptr<String> resource )
{
	int len = AMUnicodeToAnsi(resource->toCharArray(), -1, NULL, 0);
	shared_ptr<char> str = new char[len];
	AMUnicodeToAnsi(resource->toCharArray(), -1, str.get(), len);
	shared_ptr<InputStream> is = DataInputStream::getInputStreamFromFile(str.get());
	return is;
}

void Display::initStatic()
{	
	INSTANCE = new Display();
	lock = new Locker();

	lockThread = new Locker();
}
__GUI_END_NAMESPACE
