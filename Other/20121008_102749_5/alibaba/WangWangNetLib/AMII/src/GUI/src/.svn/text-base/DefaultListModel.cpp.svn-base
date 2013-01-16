#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
DefaultListModel::DefaultListModel( shared_ptr<Vector<shared_ptr<Object> > > items /*= new Vector<shared_ptr<Object>>*/ )
:items(items),selectedIndex(0)
{
	dataListener =  new EventDispatcher<DataChangedListener>();
	selectionListener = new EventDispatcher<SelectionListener>();
}

DefaultListModel::DefaultListModel( shared_ptr<VectorArray<shared_ptr<Object> > > items ): selectedIndex(0)
{
	shared_ptr<Vector<shared_ptr<Object> > > tempVector = createVector(items);
	this->items = tempVector;
	dataListener =  new EventDispatcher<DataChangedListener>();
	selectionListener = new EventDispatcher<SelectionListener>();
}
shared_ptr<Object> DefaultListModel::getItemAt( int index )
{
	shared_ptr<Object> object;
	if(index < getSize() && index >= 0){
		object = (*items)[index];
	}
	return object;

}

int DefaultListModel::getSize()
{
	return items->size();
}

int DefaultListModel::getSelectedIndex()
{
	 return selectedIndex;
}

void DefaultListModel::addItem( shared_ptr<Object> item )
{
	items->addElement(item);
	fireDataChangedEvent(DataChangedListener::ADDED, items->size());
}

void DefaultListModel::setItem( int index, shared_ptr<Object> item )
{
	items->setElementAt(item, index);
	fireDataChangedEvent(DataChangedListener::CHANGED, index);
}

void DefaultListModel::addItemAtIndex( shared_ptr<Object> item, int index )
{
	if (index <= items->size()) {
		items->insertElementAt(item, index);
		fireDataChangedEvent(DataChangedListener::ADDED, index);
	}
}

void DefaultListModel::removeItem( int index )
{
	if(index < getSize() && index >= 0){
		items->removeElementAt(index);
		if(index != 0){
			setSelectedIndex(index - 1);
		}
		fireDataChangedEvent(DataChangedListener::REMOVED, index);
	}

}

void DefaultListModel::removeAll()
{
	while(getSize() > 0) {
		removeItem(0);
	}
}

void DefaultListModel::setSelectedIndex( int index )
{
	int oldIndex = selectedIndex;
	this->selectedIndex = index;
	selectionListener->fireSelectionEvent(oldIndex, selectedIndex);

}

void DefaultListModel::addDataChangedListener( shared_ptr<DataChangedListener> l )
{
	 dataListener->addListener(l);
}

void DefaultListModel::removeDataChangedListener( shared_ptr<DataChangedListener> l )
{
	dataListener->removeListener(l);
}

void DefaultListModel::fireDataChangedEvent( int status, int index )
{
	 dataListener->fireDataChangeEvent(index, status);
}

void DefaultListModel::removeSelectionListener( shared_ptr<SelectionListener> l )
{
	 selectionListener->removeListener(l);
}

void DefaultListModel::addSelectionListener( shared_ptr<SelectionListener> l )
{
	 selectionListener->addListener(l);
}

DefaultListModel::~DefaultListModel( void )
{

}

shared_ptr<Vector<shared_ptr<Object> > > DefaultListModel::createVector( shared_ptr<VectorArray<shared_ptr<Object> > > items )
{
	shared_ptr<Vector<shared_ptr<Object> > > vec = new Vector<shared_ptr<Object> >;
	if (items.get() == NULL) 
	{
		return vec;
	}
	for(int iter = 0 ; iter < items->size() ; iter++) 
	{
		vec->addElement((*items)[iter]);
	}
	return vec;	
}
__GUI_END_NAMESPACE
