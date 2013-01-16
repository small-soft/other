#include "AMGui.h"



__GUI_BEGIN_NAMESPACE
BorderLayout::BorderLayout(void)
{
}

BorderLayout::~BorderLayout(void)
{
}

void BorderLayout::addLayoutComponent( int name, shared_ptr<Component> comp, shared_ptr<Container> c)
{
	// helper check for a common mistake->->->
	if (name == NULL) {
		return;
	//	throw new IllegalArgumentException("Cannot add component to BorderLayout Container without constraint parameter");
	}

	shared_ptr<Component> previous ;

	/* Assign the component to one of the known regions of the layout->
	*/
	if (CENTER == name) {
		previous = center;
		center = comp;
	} else if (NORTH == name) {
		previous = north;
		north = comp;
	} else if (SOUTH == name) {
		previous = south;
		south = comp;
	} else if (EAST == name) {
		previous = east;
		east = comp;
	} else if (WEST == name) {
		previous = west;
		west = comp;
	} else {
		return;//throw new IllegalArgumentException("cannot add to layout: unknown constraint: " + name);
	}
	if (previous.get() != NULL && previous != comp) {
		c->removeComponent(previous);
	}
}

void BorderLayout::removeLayoutComponent( shared_ptr<Component> comp )
{
	if (comp == center) {
		center.reset();
	} else if (comp == north) {
		north.reset();
	} else if (comp == south) {
		south.reset();
	} else if (comp == east) {
		east.reset();
	} else if (comp == west) {
		west.reset();
	}

}

int BorderLayout::getComponentConstraint( shared_ptr<Component> comp )
{
	if (comp == center) {
		return CENTER;
	} else if (comp == north) {
		return NORTH;
	} else if (comp == south) {
		return SOUTH;
	} else if (comp == east) {
		return EAST;
	} else {
		return WEST;
	}

}

void BorderLayout::layoutContainer( shared_ptr<Container> target )
{

	shared_ptr<Style> s = target->getStyle();
	int top = s->getPadding(false, Component::TOP);
	int bottom = target->getLayoutHeight() - target->getBottomGap() - s->getPadding(false, Component::BOTTOM);
	int left = s->getPadding(target->isRTL(), Component::LEFT);
	int right = target->getLayoutWidth() - target->getSideGap() - s->getPadding(target->isRTL(), Component::RIGHT);
	int targetWidth = target->getWidth();
	int targetHeight = target->getHeight();

	bool rtl = target->isRTL();
	if (rtl) {
		left+=target->getSideGap();
	}

	if (north.get() != NULL) {
		shared_ptr<Component> c = north;
		positionTopBottom(target, c, right, left, targetHeight);
		c->setY(top + c->getStyle()->getMargin(false, Component::TOP));
		top += (c->getHeight() + c->getStyle()->getMargin(false, Component::TOP) + c->getStyle()->getMargin(false, Component::BOTTOM));
	}
	if (south.get() != NULL) {
		shared_ptr<Component> c = south;
		positionTopBottom(target, c, right, left, targetHeight);
		c->setY(bottom - c->getHeight() - c->getStyle()->getMargin(false, Component::TOP));
		bottom -= (c->getHeight() + c->getStyle()->getMargin(false, Component::TOP) + c->getStyle()->getMargin(false, Component::BOTTOM));
	}

	shared_ptr<Component> realEast = east;
	shared_ptr<Component> realWest = west;

	if (rtl) {
		realEast = west;
		realWest = east;
	}

	if (realEast.get() != NULL) {
		shared_ptr<Component> c = realEast;
		positionLeftRight(realEast, targetWidth, bottom, top);
		c->setX(right - c->getWidth() - c->getStyle()->getMargin(target->isRTL(), Component::RIGHT));
		right -= (c->getWidth() + c->getStyle()->getMargin(false, Component::LEFT) + c->getStyle()->getMargin(false, Component::RIGHT));
	}
	if (realWest.get() != NULL) {
		shared_ptr<Component> c = realWest;
		positionLeftRight(realWest, targetWidth, bottom, top);
		c->setX(left + c->getStyle()->getMargin(target->isRTL(), Component::LEFT));
		left += (c->getWidth() + c->getStyle()->getMargin(false, Component::LEFT) + c->getStyle()->getMargin(false, Component::RIGHT));
	}
	if (center.get() != NULL) {
		shared_ptr<Component> c = center;
		c->setWidth(right - left - c->getStyle()->getMargin(false, Component::LEFT) - c->getStyle()->getMargin(false, Component::RIGHT));
		c->setHeight(bottom - top - c->getStyle()->getMargin(false, Component::TOP) - c->getStyle()->getMargin(false, Component::BOTTOM)); //verify I want to use the remaining size
		c->setX(left + c->getStyle()->getMargin(target->isRTL(), Component::LEFT));
		c->setY(top + c->getStyle()->getMargin(false, Component::TOP));
	}

}

void BorderLayout::positionLeftRight( shared_ptr<Component> c, int targetWidth, int bottom, int top )
{
	c->setWidth(min(targetWidth, c->getPreferredW()));
	c->setHeight(bottom - top - c->getStyle()->getMargin(false, Component::TOP) - c->getStyle()->getMargin(false, Component::BOTTOM)); //verify I want to use tge prefered size
	c->setY(top + c->getStyle()->getMargin(false, Component::TOP));

}

void BorderLayout::positionTopBottom( shared_ptr<Component> target, shared_ptr<Component> c, int right, int left, int targetHeight )
{
	c->setWidth(right - left - c->getStyle()->getMargin(false, Component::LEFT) - c->getStyle()->getMargin(false, Component::RIGHT));
	c->setHeight(min(targetHeight, c->getPreferredH())); //verify I want to use tge prefered size
	c->setX(left + c->getStyle()->getMargin(target->isRTL(), Component::LEFT));

}

shared_ptr<Dimension> BorderLayout::getPreferredSize( shared_ptr<Container> parent )
{
	shared_ptr<Dimension> dim = new Dimension(0, 0);

	if (east.get() != NULL) {
		dim->setWidth(east->getPreferredW() + east->getStyle()->getMargin(false, Component::LEFT) + east->getStyle()->getMargin(false, Component::RIGHT));
		dim->setHeight(max(east->getPreferredH() + east->getStyle()->getMargin(false, Component::TOP) + east->getStyle()->getMargin(false, Component::BOTTOM), dim->getHeight()));
	}
	if (west.get() != NULL) {
		dim->setWidth(dim->getWidth() + west->getPreferredW() + west->getStyle()->getMargin(false, Component::LEFT) + west->getStyle()->getMargin(false, Component::RIGHT));
		dim->setHeight(max(west->getPreferredH() + west->getStyle()->getMargin(false, Component::TOP) + west->getStyle()->getMargin(false, Component::BOTTOM), dim->getHeight()));
	}
	if (center.get() != NULL) {
		dim->setWidth(dim->getWidth() + center->getPreferredW() + center->getStyle()->getMargin(false, Component::LEFT) + center->getStyle()->getMargin(false, Component::RIGHT));
		dim->setHeight(max(center->getPreferredH() + center->getStyle()->getMargin(false, Component::TOP) + center->getStyle()->getMargin(false, Component::BOTTOM), dim->getHeight()));
	}
	if (north.get() != NULL) {
		dim->setWidth(max(north->getPreferredW() + north->getStyle()->getMargin(false, Component::LEFT) + north->getStyle()->getMargin(false, Component::RIGHT), dim->getWidth()));
		dim->setHeight(dim->getHeight() + north->getPreferredH() + north->getStyle()->getMargin(false, Component::TOP) + north->getStyle()->getMargin(false, Component::BOTTOM));
	}

	if (south.get() != NULL) {
		dim->setWidth(max(south->getPreferredW() + south->getStyle()->getMargin(false, Component::LEFT) + south->getStyle()->getMargin(false, Component::RIGHT), dim->getWidth()));
		dim->setHeight(dim->getHeight() + south->getPreferredH() + south->getStyle()->getMargin(false, Component::TOP) + south->getStyle()->getMargin(false, Component::BOTTOM));
	}

	dim->setWidth(dim->getWidth() + parent->getStyle()->getPadding(false, Component::LEFT) + parent->getStyle()->getPadding(false, Component::RIGHT));
	dim->setHeight(dim->getHeight() + parent->getStyle()->getPadding(false, Component::TOP) + parent->getStyle()->getPadding(false, Component::BOTTOM));
	return dim;

}

shared_ptr<Component> BorderLayout::getSouth()
{
	 return south;
}

shared_ptr<Component> BorderLayout::getCenter()
{
	 return center;
}

shared_ptr<Component> BorderLayout::getNorth()
{
	 return north;
}

shared_ptr<Component> BorderLayout::getEast()
{
	return east;
}

shared_ptr<Component> BorderLayout::getWest()
{
	 return west;
}
__GUI_END_NAMESPACE
