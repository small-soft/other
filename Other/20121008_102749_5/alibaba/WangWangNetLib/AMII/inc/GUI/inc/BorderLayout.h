#ifndef __BORDER_LAYOUT_H__
#define __BORDER_LAYOUT_H__

#include "inc/Config.h"
#include "inc/Layout.h"
#include "inc/String.h"

__GUI_BEGIN_NAMESPACE

class BorderLayout:public Layout
{
public:
	BorderLayout(void);
	virtual ~BorderLayout(void);
private:
	shared_ptr<Component> north;
	shared_ptr<Component> south;
	shared_ptr<Component> center;
	shared_ptr<Component> west;
	shared_ptr<Component> east;
public:
	/**
	* The north layout constraint (top of container).
	*/
	static const int NORTH = 1;
	/**
	* The south layout constraint (bottom of container).
	*/
	static const int SOUTH =2 ;
	/**
	* The center layout constraint (middle of container)
	*/
	static const int CENTER =3;
	/**
	* The west layout constraint (left of container).
	*/
	static const int WEST =4;
	/**
	* The east layout constraint (right of container).
	*/
	static const int EAST =5;

public:
	void addLayoutComponent(int name, shared_ptr<Component> comp, shared_ptr<Container> c);
	void removeLayoutComponent(shared_ptr<Component> comp);
	int getComponentConstraint(shared_ptr<Component> comp); 
	void layoutContainer(shared_ptr<Container> target);
	shared_ptr<Dimension> getPreferredSize(shared_ptr<Container> parent);
private:
	void positionLeftRight(shared_ptr<Component> c, int targetWidth, int bottom, int top);
	void positionTopBottom(shared_ptr<Component> target, shared_ptr<Component> c, int right, int left, int targetHeight);
protected:
	shared_ptr<Component> getSouth();
	shared_ptr<Component> getCenter();
	shared_ptr<Component> getNorth();
	shared_ptr<Component> getEast();
	shared_ptr<Component> getWest();
};
__GUI_END_NAMESPACE

#endif

