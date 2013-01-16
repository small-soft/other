#ifndef __FOCUS_LISTENER_H__
#define __FOCUS_LISTENER_H__

#include "inc/Object.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE

class Component;
class FocusListener
{
public:
	/**
	* Invoked when component gains focus
	* @param cmp the component that gains focus
	*/
	virtual  void focusGained(shared_ptr<Component> cmp) = 0;

	/**
	* Invoked when component loses focus
	* @param cmp the component that lost focus
	*/
	virtual void focusLost(shared_ptr<Component> cmp) = 0;

	virtual ~FocusListener() {}
};
__GUI_END_NAMESPACE

#endif
