#ifndef __COORDINATE_LAYOUT_H__
#define __COORDINATE_LAYOUT_H__

#include "inc/Layout.h"
#include "inc/Dimension.h"
#include "inc/Container.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Layout;
class Dimension;
class Container;

class CoordinateLayout : public Layout
{
public:
	CoordinateLayout(int width, int height);
	CoordinateLayout(shared_ptr<Dimension> d);

	virtual ~CoordinateLayout() {}

	void layoutContainer(shared_ptr<Container> parent);
	shared_ptr<Dimension> getPreferredSize(shared_ptr<Container> parent);
	bool isOverlapSupported();
private:
	void init(int width, int height);
private:
	int width;
	int height;
};
__GUI_END_NAMESPACE

#endif
