#ifndef __BOX_LAYOUT_H__
#define __BOX_LAYOUT_H__

#include "inc/Config.h"
#include "inc/Layout.h"
__GUI_BEGIN_NAMESPACE


class BoxLayout : public Layout
{
public:
	BoxLayout(int axis);
	virtual ~BoxLayout() {}
public:
	static const int X_AXIS = 1;
	static const int Y_AXIS = 2;

	void layoutContainer(shared_ptr<Container> parent);
	shared_ptr<Dimension> getPreferredSize(shared_ptr<Container> parent);
private:
	int axis;
};

__GUI_END_NAMESPACE
#endif
