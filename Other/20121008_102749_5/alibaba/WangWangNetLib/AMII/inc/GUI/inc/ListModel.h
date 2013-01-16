#ifndef __LIST_MODEL_H__
#define __LIST_MODEL_H__



#include "inc/Object.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class DataChangedListener;
class SelectionListener;
class ListModel
{
public:
	/**
	* Returns the item at the given offset
	* @param index an index into this list
	* @return the item at the specified index
	*/
	 virtual shared_ptr<Object> getItemAt(int index) = 0;

	/**
	* Returns the number of items in the list
	* @return the number of items in the list
	*/
	 virtual int getSize() = 0;

	/**
	* Returns the selected list offset
	* 
	* @return the selected list index
	*/
	 virtual int getSelectedIndex() = 0;

	/**
	* Sets the selected list offset can be set to -1 to clear selection
	* @param index an index into this list
	*/
	 virtual void setSelectedIndex(int index) = 0;

	/**
	* Invoked to indicate interest in future change events
	* @param l a data changed listener
	*/
	 virtual void addDataChangedListener(shared_ptr<DataChangedListener> l) = 0;

	/**
	* Invoked to indicate no further interest in future change events
	* @param l a data changed listener 
	*/
	 virtual void removeDataChangedListener(shared_ptr<DataChangedListener> l) = 0;

	/**
	* Invoked to indicate interest in future selection events
	* @param l a selection listener
	*/
	 virtual void addSelectionListener(shared_ptr<SelectionListener> l) = 0;

	/**
	* Invoked to indicate no further interest in future selection events
	* @param l a selection listener
	*/
	 virtual void removeSelectionListener(shared_ptr<SelectionListener> l) = 0;

	/**
	* Adds the specified item to the end of this list.
	* An optional operation for mutable lists, it can throw an unsupported operation
	* exception if a list model is not mutable.
	* @param item the item to be added
	*/
	 virtual void addItem(shared_ptr<Object> item) = 0;

	/**
	* Removes the item at the specified position in this list.
	* @param index the index of the item to removed
	*/
	 virtual void removeItem(int index) = 0;

	 virtual ~ListModel() {}

};
__GUI_END_NAMESPACE



#endif
