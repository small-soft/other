#ifndef __EVENT_DISPATCHER_H__
#define __EVENT_DISPATCHER_H__

#include "inc/String.h"

#include "inc/Object.h"
#include "inc/Config.h"

#include "inc/DataChangedListener.h"
#include "inc/SelectionListener.h"
#include "inc/Component.h"
#include "inc/FocusListener.h"
__GUI_BEGIN_NAMESPACE
//class DataChangedListener;
//class SelectionListener;
class ActionEvent;
class ActionListener;
//class Component;
//class FocusListener;
class Style;
class StyleListener;
class Locker;

template<class N> class EventDispatcher:public Object
{
public:
	EventDispatcher(void);
	virtual ~EventDispatcher(void);
private:
	shared_ptr<Vector<weak_ptr<N> > >  listeners;
	/*shared_ptr<Vector<shared_ptr<Object pending;
	shared_ptr<Object> pendingEvent;*/
	shared_ptr<Locker> locker;// = new Locker();
public:
	void addListener(weak_ptr<N> listener);
	shared_ptr<Vector<weak_ptr<N> > > getListenerVector();
	void removeListener(weak_ptr<N> listener);
	void fireDataChangeEvent(int index, int type);
	void fireStyleChangeEvent(shared_ptr<String> property, shared_ptr<Style> source);
	void fireActionEvent(shared_ptr<ActionEvent> ev);
	void fireSelectionEvent(int oldSelection, int newSelection);
	void fireFocus(shared_ptr<Component> c);
private:
	void fireDataChangeSync(shared_ptr<Vector<shared_ptr<DataChangedListener> > >array, int type, int index);
	void fireStyleChangeSync(shared_ptr<Vector<shared_ptr<StyleListener> > >array, shared_ptr<String> property, shared_ptr<Style> source);
	void fireSelectionSync(shared_ptr<Vector<shared_ptr<SelectionListener> > > array, int oldSelection, int newSelection);
	void fireActionSync(shared_ptr<Vector<shared_ptr<ActionListener> > > array, shared_ptr<ActionEvent> ev);
	void fireFocusSync(shared_ptr<Vector<shared_ptr<FocusListener> > > array, shared_ptr<Component> c);
};

template<class N> EventDispatcher<N>::EventDispatcher(void)
{
	locker = new Locker();

	listeners = new Vector<weak_ptr<N> >;
}

template<class N> EventDispatcher<N>::~EventDispatcher(void)
{
	listeners->removeAllElements();	
}

template<class N> void EventDispatcher<N>::addListener( weak_ptr<N> listener )
{
	if(listeners.get() == NULL) {
		listeners = new Vector<weak_ptr<N> >;
	}
	listeners->addElement(listener);
}

template<class N> shared_ptr<Vector<weak_ptr<N> > > EventDispatcher<N>::getListenerVector()
{
	return listeners;
}

template<class N> void EventDispatcher<N>::removeListener( weak_ptr<N> listener )
{
	if(listeners.get() != NULL) {
		listeners->removeElement(listener);	
	}
}

template<class N> void EventDispatcher<N>::fireDataChangeEvent( int index, int type )
{	
	int size = listeners->size();
	if(listeners.get() == NULL || size == 0) {
		return;
	}
	shared_ptr<Vector<shared_ptr<DataChangedListener> > > array;
	locker->lock();
	{		
		array = new Vector<shared_ptr<DataChangedListener> >;
		for(int iter = 0 ; iter < size ; iter++) {
			array->addElement(static_pointer_cast<DataChangedListener>(listeners->elementAt(iter)));
		}
	}
	locker->unlock();
	fireDataChangeSync(array, type, index);
}

template<class N> void EventDispatcher<N>::fireStyleChangeEvent(shared_ptr<String> property, shared_ptr<Style> source )
{	
	int size = listeners->size();
	if(listeners.get() == NULL || size == 0) {
		return;
	}
	shared_ptr<Vector<shared_ptr<StyleListener> > > array;

	locker->lock();
	/*synchronized(this) */
	{
		int size = listeners->size();
		array = new Vector<shared_ptr<StyleListener> >;
		for(int iter = 0 ; iter < size ; iter++) {
			array->addElement(static_pointer_cast<StyleListener>(listeners->elementAt(iter)));
		}
	}
	locker->unlock();
	fireStyleChangeSync(array, property, source);
}

template<class N> void EventDispatcher<N>::fireDataChangeSync( shared_ptr<Vector<shared_ptr<DataChangedListener> > >array, int type, int index )
{
	for(int iter = 0 ; iter < array->size() ; iter++) {
		(*array)[iter]->dataChanged(type, index);
	}
}

template<class N> void EventDispatcher<N>::fireStyleChangeSync( shared_ptr<Vector<shared_ptr<StyleListener> > > array, shared_ptr<String> property, shared_ptr<Style> source )
{
	for(int iter = 0 ; iter < array->size() ; iter++) {
		(*array)[iter]->styleChanged(property, source);
	}
}

template<class N> void EventDispatcher<N>::fireActionEvent( shared_ptr<ActionEvent> ev )
{
	int size = listeners->size();
	if(listeners.get() == NULL || size == 0) {
		return;
	}

	shared_ptr<Vector<shared_ptr<ActionListener> > > array;
	locker->lock();
	/*synchronized(this)*/ 
	{
		array = new Vector<shared_ptr<ActionListener> >;
		for(int iter = 0 ; iter < size ; iter++) {
			array->addElement(static_pointer_cast<ActionListener>(listeners->elementAt(iter)));
		}
	}
	locker->unlock();
	// if we already are on the EDT just fire the event

	fireActionSync(array, ev);
}

template<class N> void EventDispatcher<N>::fireActionSync( shared_ptr<Vector<shared_ptr<ActionListener> > > array, shared_ptr<ActionEvent> ev )
{
	for(int iter = 0 ; iter < array->size() ; iter++) {
		if(!ev->isConsumed()) {
			shared_ptr<ActionListener> l = (*array)[iter];
			l->actionPerformed(ev);
		}
	}
}

template<class N> void EventDispatcher<N>::fireSelectionEvent( int oldSelection, int newSelection )
{
	int size = listeners->size();
	if(listeners.get() == NULL || size == 0) {
		return;
	}
	shared_ptr<Vector<shared_ptr<SelectionListener> > > array;
	locker->lock();
	/*synchronized(this)*/ 
	{
		array = new Vector<shared_ptr<SelectionListener> >;
		for(int iter = 0 ; iter < size ; iter++) {
			array->addElement(static_pointer_cast<SelectionListener>(listeners->elementAt(iter)));
		}
	}
	locker->unlock();
	// if we already are on the EDT just fire the event

	fireSelectionSync(array, oldSelection, newSelection);
}

template<class N> void EventDispatcher<N>::fireSelectionSync( shared_ptr<Vector<shared_ptr<SelectionListener> > > array, int oldSelection, int newSelection )
{
	for(int iter = 0 ; iter < array->size() ; iter++) {
		shared_ptr<SelectionListener> listener = array->elementAt(iter);
		listener->selectionChanged(oldSelection, newSelection);
	}
}

template<class N> void EventDispatcher<N>::fireFocus( shared_ptr<Component> c )
{
	int size = listeners->size();
	if(listeners.get() == NULL || size == 0) {
		return;
	}
	shared_ptr<Vector<shared_ptr<FocusListener> > > array;

	locker->lock();
	/*synchronized(this)*/ 
	{
		array = new Vector<shared_ptr<FocusListener> >;
		for(int iter = 0 ; iter < size ; iter++) {
			array->addElement(static_pointer_cast<FocusListener>(listeners->elementAt(iter)));
		}
	}
	locker->unlock();
	// if we already are on the EDT just fire the event

	fireFocusSync(array, c);
}

template<class N> void EventDispatcher<N>::fireFocusSync( shared_ptr<Vector<shared_ptr<FocusListener> > > array, shared_ptr<Component> c )
{
	if(c->hasFocus()) {
		for(int iter = 0 ; iter < array->size() ; iter++) {
			(*array)[iter]->focusGained(c);
		}
	} else {
		for(int iter = 0 ; iter < array->size() ; iter++) {
			(*array)[iter]->focusLost(c);
		}
	}

}
__GUI_END_NAMESPACE

#endif
