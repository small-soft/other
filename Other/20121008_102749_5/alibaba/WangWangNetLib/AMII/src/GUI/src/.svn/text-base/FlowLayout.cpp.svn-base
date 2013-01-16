#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
FlowLayout::FlowLayout( int orientation /*= Component::LEFT*/ )
:orientation(orientation)
{

}
FlowLayout::~FlowLayout(void)
{
}

void FlowLayout::layoutContainer(shared_ptr<Container> parent )
{
	int x = parent->getStyle()->getPadding(parent->isRTL(), Component::LEFT);
	int width = parent->getLayoutWidth() - parent->getSideGap() - parent->getStyle()->getPadding(parent->isRTL(), Component::RIGHT) - x;

	bool rtl = parent->isRTL();
	if(rtl) {
		x += parent->getSideGap();
	}
	int initX = x;

	int y = parent->getStyle()->getPadding(false, Component::TOP);
	int rowH=0;
	int start=0;

	int maxComponentWidth = width - parent->getStyle()->getPadding(parent->isRTL(), Component::LEFT);
	int maxComponentHeight = parent->getLayoutHeight() - y - parent->getStyle()->getPadding(false, Component::BOTTOM);
	if(maxComponentHeight > parent->getHeight()) {
		maxComponentHeight = parent->getHeight();
	}

	int numOfcomponents = parent->getComponentCount();
	for(int i=0; i< numOfcomponents; i++){
		shared_ptr<Component> cmp = parent->getComponentAt(i);
		shared_ptr<Style> style = cmp->getStyle();

		int marginY = style->getMargin(false, Component::TOP) + style->getMargin(false, Component::BOTTOM);
		int marginX = style->getMargin(false, Component::LEFT) + style->getMargin(false, Component::RIGHT);

		cmp->setWidth(min(maxComponentWidth - marginX, cmp->getPreferredW()));
		cmp->setHeight(min(cmp->getPreferredH(), maxComponentHeight - marginY));

		if((x == parent->getStyle()->getPadding(parent->isRTL(), Component::LEFT)) || ( x+ cmp->getPreferredW() < width) ) {
			// We take the actual LEFT since drawing is done in reverse
			x += cmp->getStyle()->getMargin(false, Component::LEFT);
			if(rtl) {
				cmp->setX(max(width + initX - (x - initX) - cmp->getPreferredW(), style->getMargin(false, Component::LEFT)));
			} else {
				cmp->setX(x);
			}

			cmp->setY(y + cmp->getStyle()->getMargin(cmp->isRTL(), Component::TOP));

			x += cmp->getPreferredW() + cmp->getStyle()->getMargin(false, Component::RIGHT);
			rowH = max(rowH, cmp->getPreferredH() + cmp->getStyle()->getMargin(false, Component::TOP)+ cmp->getStyle()->getMargin(false, Component::BOTTOM));
		} else {
			moveComponents(parent, parent->getStyle()->getPadding(parent->isRTL(), Component::LEFT), y, width - x, rowH, start, i);
			x = initX+cmp->getStyle()->getMargin(false, Component::LEFT);
			y += rowH;

			if(rtl) {
				cmp->setX(max(width + initX - (x - initX) - cmp->getPreferredW(), style->getMargin(false, Component::LEFT)));
			} else {
				cmp->setX(x);
			}

			cmp->setY(y + cmp->getStyle()->getMargin(false, Component::TOP));
			rowH = cmp->getPreferredH()+ cmp->getStyle()->getMargin(false, Component::TOP)+ cmp->getStyle()->getMargin(false, Component::BOTTOM);
			x += cmp->getPreferredW()+ cmp->getStyle()->getMargin(false, Component::RIGHT);
			start = i;

		}
	}
	moveComponents(parent, parent->getStyle()->getPadding(parent->isRTL(), Component::LEFT), y, width - x, rowH, start, numOfcomponents);

}


shared_ptr<Dimension> FlowLayout::getPreferredSize(shared_ptr<Container> parent )
{
	int width = 0;
	int height = 0;

	int numOfcomponents = parent->getComponentCount();
	for(int i=0; i< numOfcomponents; i++){
		shared_ptr<Component> cmp = parent->getComponentAt(i);
		height =max(height, cmp->getPreferredH() + cmp->getStyle()->getMargin(false, Component::TOP)+ cmp->getStyle()->getMargin(false, Component::BOTTOM));
		width += cmp->getPreferredW()+ cmp->getStyle()->getMargin(false, Component::RIGHT)+ cmp->getStyle()->getMargin(false, Component::LEFT);
	}
	shared_ptr<Dimension> d  = new Dimension(width + parent->getStyle()->getPadding(false, Component::LEFT)+ parent->getStyle()->getPadding(false, Component::RIGHT),
		height + parent->getStyle()->getPadding(false, Component::TOP)+ parent->getStyle()->getPadding(false, Component::BOTTOM));

	return d;
}

void FlowLayout::moveComponents( shared_ptr<Container> target, int x, int y, int width, int height, int rowStart, int rowEnd )
{
	switch (orientation) {
			case Component::CENTER:
				// this will remove half of last gap
				if (target->isRTL()) {
					x -= (width) / 2;  
				} else {
					x += (width) / 2;
				}
				break;
			case Component::RIGHT:
				x+=width;  // this will remove the last gap 
				break;
	}
	for (int i = rowStart ; i < rowEnd ; i++) {
		shared_ptr<Component> m = target->getComponentAt(i);

		m->setX(m->getX()+ x);
		m->setY(y + m->getStyle()->getMargin(false, Component::TOP) + (height - m->getPreferredH()) / 2);
	}

}
__GUI_END_NAMESPACE
