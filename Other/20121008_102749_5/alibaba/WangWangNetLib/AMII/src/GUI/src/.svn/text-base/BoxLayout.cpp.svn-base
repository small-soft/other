#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
BoxLayout::BoxLayout(int axis)
{
	this->axis = axis;
}

void BoxLayout::layoutContainer(shared_ptr<Container> parent) 
{        
	int width = parent->getLayoutWidth() - parent->getSideGap() - parent->getStyle()->getPadding(Component::RIGHT) - parent->getStyle()->getPadding(Component::LEFT);
	int height = parent->getLayoutHeight() - parent->getBottomGap() - parent->getStyle()->getPadding(Component::BOTTOM) - parent->getStyle()->getPadding(Component::TOP);
	int x = parent->getStyle()->getPadding(Component::LEFT);
	int y = parent->getStyle()->getPadding(Component::TOP);
	int numOfcomponents = parent->getComponentCount();

	for(int i=0; i< numOfcomponents; i++)
	{
		shared_ptr<Component> cmp = parent->getComponentAt(i);

		if(axis == Y_AXIS)
		{
			int cmpBottom = height;
			int cmpH = cmp->getPreferredH();

			y += cmp->getStyle()->getMargin(Component::TOP);

			if(y >= cmpBottom)
			{
				cmpH = 0;
			}
			else 
			{
				if(y + cmpH - parent->getStyle()->getPadding(Component::TOP) > cmpBottom)
				{
					cmpH = cmpBottom - y - cmp->getStyle()->getMargin(Component::BOTTOM);
				}
			}

			cmp->setWidth(width - cmp->getStyle()->getMargin(Component::LEFT) - cmp->getStyle()->getMargin(Component::RIGHT));
			cmp->setHeight(cmpH);
			cmp->setX(x + cmp->getStyle()->getMargin(Component::LEFT));
			cmp->setY(y);
			y += cmp->getHeight() + cmp->getStyle()->getMargin(Component::BOTTOM);
		}
		else
		{
			int cmpRight = width;
			int cmpW = cmp->getPreferredW();

			x += cmp->getStyle()->getMargin(Component::LEFT);
			if(x >= cmpRight)
			{
				cmpW = 0;
			}
			else
			{
				if(x + cmpW - parent->getStyle()->getPadding(Component::LEFT) > cmpRight)
				{
					cmpW = cmpRight - x - cmp->getStyle()->getMargin(Component::RIGHT);
				}
			}

			cmp->setWidth(cmpW);
			cmp->setHeight(height- cmp->getStyle()->getMargin(Component::TOP) - cmp->getStyle()->getMargin(Component::BOTTOM));
			cmp->setX(x);
			cmp->setY(y + cmp->getStyle()->getMargin(Component::TOP));
			x += cmp->getWidth() + cmp->getStyle()->getMargin(Component::RIGHT);
		}
	}
}
shared_ptr<Dimension> BoxLayout::getPreferredSize(shared_ptr<Container> parent) 
{
	int width = 0;
	int height = 0;

	int numOfcomponents = parent->getComponentCount();
	for(int i=0; i< numOfcomponents; i++)
	{
		shared_ptr<Component> cmp = parent->getComponentAt(i);

		if(axis == Y_AXIS)
		{
			int cmpH = cmp->getPreferredH() + cmp->getStyle()->getMargin(Component::TOP) + cmp->getStyle()->getMargin(Component::BOTTOM);
			height += cmpH;
			width = max(width , cmp->getPreferredW()+ cmp->getStyle()->getMargin(Component::LEFT) + cmp->getStyle()->getMargin(Component::RIGHT));
		}
		else
		{
			int cmpW = cmp->getPreferredW() + cmp->getStyle()->getMargin(Component::LEFT) + cmp->getStyle()->getMargin(Component::RIGHT);
			width += cmpW;
			height = max(height, cmp->getPreferredH() + cmp->getStyle()->getMargin(Component::TOP) + cmp->getStyle()->getMargin(Component::BOTTOM));
		}
	}
	shared_ptr<Dimension> d = new Dimension(width + parent->getStyle()->getPadding(Component::LEFT)+ parent->getStyle()->getPadding(Component::RIGHT), height + parent->getStyle()->getPadding(Component::TOP)+ parent->getStyle()->getPadding(Component::BOTTOM));
	return d;
}

__GUI_END_NAMESPACE
