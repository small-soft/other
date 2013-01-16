#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "inc/Object.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Container;
class Component;
class Dimension;
class Layout:public Object
{
public:
	virtual ~Layout(void);
public:
	virtual void layoutContainer(shared_ptr<Container> parent) = 0;
	virtual shared_ptr<Dimension> getPreferredSize(shared_ptr<Container> parent) = 0;
	virtual void addLayoutComponent(int value, shared_ptr<Component> comp, shared_ptr<Container> c);
	virtual void removeLayoutComponent(shared_ptr<Component> comp);
	virtual int getComponentConstraint(shared_ptr<Component> comp);
	virtual bool isOverlapSupported();
};
__GUI_END_NAMESPACE

#endif
