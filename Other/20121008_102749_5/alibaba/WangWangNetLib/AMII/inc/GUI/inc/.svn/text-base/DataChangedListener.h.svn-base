#ifndef __DATA_CHANGED_LISTENER_H__
#define __DATA_CHANGED_LISTENER_H__

#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class DataChangedListener
{
public:
	/**
	* Type value for removed data in ListModel
	*/
	const static int REMOVED = 0;

	/**
	* Type value for added data in ListModel
	*/
	const static int ADDED = 1;

	/**
	* Type value for changed data in ListModel
	*/
	const static int CHANGED = 2;

	/**
	* Invoked when there was a change in the underlying model
	* 
	* @param type the type data change; REMOVED, ADDED or CHANGED
	* @param index item index in a list model
	*/
	virtual  void dataChanged(int type, int index) = 0;

	virtual ~DataChangedListener() {}
};
__GUI_END_NAMESPACE

#endif
