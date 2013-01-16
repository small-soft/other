#ifndef __FLOWLAYOUT_H__
#define __FLOWLAYOUT_H__

#include "inc/Layout.h"
#include "inc/Config.h"
#include "inc/Component.h"

__GUI_BEGIN_NAMESPACE
class FlowLayout:public Layout
{
public:
	FlowLayout(int orientation =  Component::LEFT);
	virtual ~FlowLayout(void);
private:
	int orientation;// = Component::LEFT;
public:
	void layoutContainer(shared_ptr<Container> parent);
	shared_ptr<Dimension> getPreferredSize(shared_ptr<Container> parent);
private:
	void moveComponents(shared_ptr<Container> target, int x, int y, int width, int height, int rowStart, int rowEnd );
};
__GUI_END_NAMESPACE

#endif
