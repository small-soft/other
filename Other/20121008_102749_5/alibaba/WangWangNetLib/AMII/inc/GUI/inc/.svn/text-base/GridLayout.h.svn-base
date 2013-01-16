#ifndef __GRID_LAYOUT_H__
#define __GRID_LAYOUT_H__

#include "inc/Layout.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class GridLayout:public Layout
{
public:
	GridLayout(int rows, int columns);
	virtual ~GridLayout(void);
private:
	int rows;
	int columns;
public:
	void layoutContainer(shared_ptr<Container> parent);
	shared_ptr<Dimension> getPreferredSize(shared_ptr<Container> parent);
};
__GUI_END_NAMESPACE

#endif
