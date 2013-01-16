#ifndef __DEFAULT_LIST_MODEL_H__
#define __DEFAULT_LIST_MODEL_H__


#include "inc/EventDispatcher.h"
#include "inc/ListModel.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class DefaultListModel:public Object,public ListModel
{
public:
	DefaultListModel(shared_ptr<Vector<shared_ptr<Object> > > items = new Vector<shared_ptr<Object> >);
	DefaultListModel(shared_ptr<VectorArray<shared_ptr<Object> > > items);
	virtual ~DefaultListModel(void);
private:
	static shared_ptr<Vector<shared_ptr<Object> > > createVector(shared_ptr<VectorArray<shared_ptr<Object> > > items);

	shared_ptr<Vector<shared_ptr<Object> > > items;
	shared_ptr<EventDispatcher<DataChangedListener> > dataListener;// = new EventDispatcher();
	shared_ptr<EventDispatcher<SelectionListener> > selectionListener;// = new EventDispatcher();
	int selectedIndex;// = 0;
public:
	shared_ptr<Object> getItemAt(int index);
	int getSize();
	int getSelectedIndex();
	void addItem(shared_ptr<Object> item);
	void setItem(int index, shared_ptr<Object> item);
	void addItemAtIndex(shared_ptr<Object> item, int index);
	void removeItem(int index);
	void removeAll();
	void setSelectedIndex(int index) ;
	void addDataChangedListener(shared_ptr<DataChangedListener> l) ;
	void removeDataChangedListener(shared_ptr<DataChangedListener> l);
	void addSelectionListener(shared_ptr<SelectionListener> l);
	void removeSelectionListener(shared_ptr<SelectionListener> l);
private:
	void fireDataChangedEvent( int status, int index);
};
__GUI_END_NAMESPACE

#endif
