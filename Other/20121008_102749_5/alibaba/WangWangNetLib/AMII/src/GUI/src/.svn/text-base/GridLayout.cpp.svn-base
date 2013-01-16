#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
GridLayout::GridLayout( int rows, int columns )
{
	this->rows = rows;
	this->columns = columns;
}

GridLayout::~GridLayout(void)
{
}

void GridLayout::layoutContainer(shared_ptr<Container> parent )
{
	int width = parent->getLayoutWidth() - parent->getSideGap() - parent->getStyle()->getPadding(false, Component::RIGHT) - parent->getStyle()->getPadding(false, Component::LEFT);
	int height = parent->getLayoutHeight() - parent->getBottomGap() - parent->getStyle()->getPadding(false, Component::BOTTOM) - parent->getStyle()->getPadding(false, Component::TOP);
	int x = parent->getStyle()->getPadding(parent->isRTL(), Component::LEFT);
	int y = parent->getStyle()->getPadding(false, Component::TOP);
	int numOfcomponents = parent->getComponentCount();

	bool rtl = parent->isRTL();
	if (rtl) {
		x += parent->getSideGap();
	}

	int cmpWidth = (width)/columns;
	int cmpHeight;
	if (numOfcomponents > rows * columns) {
		cmpHeight  = (height)/(numOfcomponents/columns + (numOfcomponents%columns == 0 ? 0 : 1));//actual rows number
	} else {
		cmpHeight  = (height)/rows;  
	}
	int row = 0;        

	for(int i=0; i< numOfcomponents; i++){
		shared_ptr<Component> cmp = parent->getComponentAt(i);
		shared_ptr<Style> cmpStyle = cmp->getStyle();
		int marginLeft = cmpStyle->getMargin(parent->isRTL(), Component::LEFT);
		int marginTop = cmpStyle->getMargin(false, Component::TOP);
		cmp->setWidth(cmpWidth - marginLeft - cmpStyle->getMargin(parent->isRTL(), Component::RIGHT));
		cmp->setHeight(cmpHeight - marginTop - cmpStyle->getMargin(false, Component::BOTTOM));
		if (rtl) {
			cmp->setX(x + (columns-1-(i%columns))*cmpWidth + marginLeft);
		} else {
			cmp->setX(x + (i%columns)*cmpWidth + marginLeft);
		}
		cmp->setY(y + row*cmpHeight + marginTop);
		if((i + 1)%columns == 0){
			row++;
		}
	}

}

shared_ptr<Dimension> GridLayout::getPreferredSize( shared_ptr<Container> parent )
{
	int width = 0;
	int height = 0;

	int numOfcomponents = parent->getComponentCount();
	for(int i=0; i< numOfcomponents; i++){
		shared_ptr<Component> cmp = parent->getComponentAt(i);
		width = max(width, cmp->getPreferredW() + cmp->getStyle()->getMargin(false, Component::LEFT)+ cmp->getStyle()->getMargin(false, Component::RIGHT));
		height = max(height, cmp->getPreferredH()+ cmp->getStyle()->getMargin(false, Component::TOP)+ cmp->getStyle()->getMargin(false, Component::BOTTOM));
	}

	if(columns > 1){
		width = width*columns;
	}

	if(rows > 1){
		if(numOfcomponents>rows*columns){ //if there are more components than planned
			height =  height * (numOfcomponents/columns + (numOfcomponents%columns == 0 ? 0 : 1));
		}else{
			height = height*rows;
		}
	}

	return new Dimension(width + parent->getStyle()->getPadding(false, Component::LEFT)+ parent->getStyle()->getPadding(false, Component::RIGHT),
		height + parent->getStyle()->getPadding(false, Component::TOP)+ parent->getStyle()->getPadding(false, Component::BOTTOM));

}

__GUI_END_NAMESPACE
