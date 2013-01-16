#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
CoordinateLayout::CoordinateLayout(int width, int height)
{
	init(width, height);
}
CoordinateLayout::CoordinateLayout(shared_ptr<Dimension> d)
{
	init(d->getWidth(), d->getHeight());
}

void CoordinateLayout::init(int width, int height)
{
	this->width = width;
	this->height = height;
}
void CoordinateLayout::layoutContainer(shared_ptr<Container> parent) 
{
	int numOfcomponents = parent->getComponentCount();
	int parentW = parent->getWidth();
	int parentH = parent->getHeight();

	for(int i=0; i< numOfcomponents; i++)
	{
		shared_ptr<Component> cmp = parent->getComponentAt(i);
		int x = cmp->getX() * parentW /width;
		int y = cmp->getY() * parentH /height;
		cmp->setX(x);
		cmp->setY(y);

		cmp->setWidth(cmp->getPreferredW());
		cmp->setHeight(cmp->getPreferredH());
	}
	width = parentW;
	height = parentH;
}
shared_ptr<Dimension> CoordinateLayout::getPreferredSize(shared_ptr<Container> parent) 
{
	shared_ptr<Dimension> retVal = new Dimension();
	int numOfcomponents = parent->getComponentCount();
	for(int i=0; i< numOfcomponents; i++)
	{
		shared_ptr<Component> cmp = parent->getComponentAt(i);
		retVal->setWidth(max(retVal->getWidth(), cmp->getX() + cmp->getPreferredW()));
		retVal->setHeight(max(retVal->getHeight(), cmp->getY() + cmp->getPreferredH()));
	}

	return retVal;
}

bool CoordinateLayout::isOverlapSupported() 
{
	return true;
}
__GUI_END_NAMESPACE
