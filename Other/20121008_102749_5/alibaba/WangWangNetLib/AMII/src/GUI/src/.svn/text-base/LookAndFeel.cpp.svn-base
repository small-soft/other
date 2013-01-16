#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
LookAndFeel::LookAndFeel()
{	
	rtl = false;
	tickerSpeed = 50;
	defaultFormTintColor = 0x77000000;
	disableColor = 0xcccccc;
	defaultSmoothScrolling = true;
	defaultSmoothScrollingSpeed = 150;
	reverseSoftButtons = false;
	touchMenus = false;
	tactileTouchDuration = 0;
	menuIcons = new VectorArray<shared_ptr<Image> >(3);
}

void LookAndFeel::drawVerticalScroll( shared_ptr<Graphics> g, shared_ptr<Component> c, float offsetRatio, float blockSizeRatio )
{
	if(verticalScroll.get() == NULL) {
		initScroll();
	}
	int x = c->getX();
	if(!c->isRTL()) {
		x += c->getWidth() - getVerticalScrollWidth();
	}
	int y = c->getY();
	int height = c->getHeight();
	int width = getVerticalScrollWidth();
	drawScroll(g, c, offsetRatio, blockSizeRatio, true, x, y, width, height, verticalScroll, verticalScrollThumb);

}

void LookAndFeel::drawHorizontalScroll( shared_ptr<Graphics> g, shared_ptr<Component> c, float offsetRatio, float blockSizeRatio )
{
	if(horizontalScroll.get() == NULL) {
		initScroll();
	}
	int x = c->getX();
	int y = c->getY() + c->getHeight() - getHorizontalScrollHeight();
	int width = c->getWidth();
	int height = getHorizontalScrollHeight();
	drawScroll(g, c, offsetRatio, blockSizeRatio, false, x, y, width, height, horizontalScroll, horizontalScrollThumb);

}

void LookAndFeel::drawScroll( shared_ptr<Graphics> g, shared_ptr<Component> c, float offsetRatio, float blockSizeRatio, bool isVertical, int x, int y, int width, int height, shared_ptr<Component> scroll, shared_ptr<Component> scrollThumb )
{
	shared_ptr<Style> scrollStyle = scroll->getUnselectedStyle();
	shared_ptr<Style> scrollThumbStyle = scrollThumb->getUnselectedStyle();

	// take margin into consideration when positioning the scroll
	int marginLeft = scrollStyle->getMargin(c->isRTL(), Component::LEFT);
	int marginTop = scrollStyle->getMargin(false, Component::TOP);
	x += marginLeft;
	width -= (marginLeft + scrollStyle->getMargin(c->isRTL(), Component::RIGHT));
	y += marginTop;
	height -= (marginTop + scrollStyle->getMargin(false, Component::BOTTOM));

	scroll->setX(x);
	scroll->setY(y);
	scroll->setWidth(width);
	scroll->setHeight(height);

	int cx = g->getClipX();
	int cy = g->getClipY();
	int cw = g->getClipWidth();
	int ch = g->getClipHeight();

	scroll->paintComponent(g);

	marginLeft = scrollThumbStyle->getMargin(c->isRTL(), Component::LEFT);
	marginTop = scrollThumbStyle->getMargin(false, Component::TOP);
	x += marginLeft;
	width -= (marginLeft + scrollThumbStyle->getMargin(c->isRTL(), Component::RIGHT));
	y += marginTop;
	height -= (marginTop + scrollThumbStyle->getMargin(false, Component::BOTTOM));

	int offset, blockSize;

	if (isVertical) {
		blockSize = (int) (c->getHeight() * blockSizeRatio) + 2;
		offset = (int) ((c->getHeight()) * offsetRatio);
	} else {
		blockSize = (int) (c->getWidth() * blockSizeRatio) + 2;
		offset = (int) ((c->getWidth()) * offsetRatio);
	}

	if (isVertical) {
		scrollThumb->setX(x);
		scrollThumb->setY(y + offset);
		scrollThumb->setWidth(width);
		scrollThumb->setHeight(blockSize);
	} else {
		scrollThumb->setX(x + offset);
		scrollThumb->setY(y);
		scrollThumb->setWidth(blockSize);
		scrollThumb->setHeight(height);
	}

	g->setClip(cx, cy, cw, ch);
	scrollThumb->paintComponent(g);
	g->setClip(cx, cy, cw, ch);

}

void LookAndFeel::setFG( shared_ptr<Graphics> g, shared_ptr<Component> c )
{
	shared_ptr<Style> s = c->getStyle();
	g->setFont(s->getFont());
	if (c->isEnabled()) {
		g->setColor(s->getFgColor());
	//	g->setFgColor(s->getFgColor());
	} else {
		g->setColor(disableColor);
	//	g->setFgColor(disableColor);
	}

}

int LookAndFeel::getVerticalScrollWidth()
{
	if(verticalScroll.get() == NULL) {
		initScroll();
	}
	shared_ptr<Style> scrollStyle = verticalScroll->getStyle();

	// bidi doesn't matter for width calculations
	return scrollStyle->getMargin(false, Component::LEFT) + scrollStyle->getMargin(false, Component::RIGHT) +
		scrollStyle->getPadding(false, Component::LEFT) + scrollStyle->getPadding(false, Component::RIGHT);

}

int LookAndFeel::getHorizontalScrollHeight()
{
	if(horizontalScroll.get() == NULL) {
		initScroll();
	}
	shared_ptr<Style> scrollStyle = horizontalScroll->getStyle();

	// bidi doesn't matter for height calculations
	return scrollStyle->getMargin(false, Component::TOP) + scrollStyle->getMargin(false, Component::BOTTOM) +
		scrollStyle->getPadding(false, Component::TOP) + scrollStyle->getPadding(false, Component::BOTTOM);

}

shared_ptr<Transition> LookAndFeel::getDefaultFormTransitionIn()
{
	 return defaultFormTransitionIn;
}

void LookAndFeel::setDefaultFormTransitionIn( shared_ptr<Transition> defaultFormTransitionIn )
{
	this->defaultFormTransitionIn = defaultFormTransitionIn;
}

shared_ptr<Transition> LookAndFeel::getDefaultDialogTransitionOut()
{
	return defaultDialogTransitionOut;
}


int LookAndFeel::getDefaultFormTintColor()
{
	 return defaultFormTintColor;
}

void LookAndFeel::setDefaultFormTintColor( int defaultFormTintColor )
{
	 this->defaultFormTintColor = defaultFormTintColor;
}

int LookAndFeel::getDisableColor()
{
	 return disableColor;
}

void LookAndFeel::setDisableColor( int disableColor )
{
	this->disableColor = disableColor;
}

bool LookAndFeel::isDefaultSmoothScrolling()
{
	 return defaultSmoothScrolling;
}

void LookAndFeel::setDefaultSmoothScrolling( bool defaultSmoothScrolling )
{
	 this->defaultSmoothScrolling = defaultSmoothScrolling;
}

int LookAndFeel::getDefaultSmoothScrollingSpeed()
{
	 return defaultSmoothScrollingSpeed;
}

void LookAndFeel::setDefaultSmoothScrollingSpeed( int defaultSmoothScrollingSpeed )
{
	  this->defaultSmoothScrollingSpeed = defaultSmoothScrollingSpeed;
}

bool LookAndFeel::isReverseSoftButtons()
{
	return reverseSoftButtons;
}

void LookAndFeel::setReverseSoftButtons( bool reverseSoftButtons )
{
	this->reverseSoftButtons = reverseSoftButtons;
}

shared_ptr<ListCellRenderer> LookAndFeel::getMenuRenderer()
{
	 return menuRenderer;
}

void LookAndFeel::setMenuRenderer( shared_ptr<ListCellRenderer> menuRenderer )
{
	 this->menuRenderer = menuRenderer;
}

void LookAndFeel::setMenuIcons( shared_ptr<Image> select, shared_ptr<Image> cancel, shared_ptr<Image> menu )
{
	(*menuIcons)[0] = select;
	(*menuIcons)[1] = cancel;
	(*menuIcons)[2] = menu;
}

shared_ptr<VectorArray<shared_ptr<Image> > > LookAndFeel::getMenuIcons()
{
	return menuIcons;
}

long LookAndFeel::getTickerSpeed()
{
	 return tickerSpeed;
}

void LookAndFeel::setTickerSpeed( long tickerSpeed )
{
	this->tickerSpeed = tickerSpeed;
}

void LookAndFeel::initScroll()
{
	verticalScroll = Label::newV();
	shared_ptr<String> id = new String(L"Scroll");
	verticalScroll->setUIID(id);
	horizontalScroll = Label::newV();
	 id = new String(L"HorizontalScroll");
	horizontalScroll->setUIID(id);
	verticalScrollThumb = Label::newV();
	 id = new String(L"ScrollThumb");
	verticalScrollThumb->setUIID(id);
	horizontalScrollThumb = Label::newV();
	 id = new String(L"HorizontalScrollThumb");
	horizontalScrollThumb->setUIID(id);

}

void LookAndFeel::refreshTheme()
{
	initScroll();
	if(menuRenderer.get()!= NULL) {
		Component* cmp = dynamic_cast<Component*>(menuRenderer.get());
		if(cmp != NULL) {
			cmp->refreshTheme();
		}
	}
}

bool LookAndFeel::isTouchMenus()
{
	   return touchMenus;
}

void LookAndFeel::setTouchMenus( bool touchMenus )
{
	 this->touchMenus = touchMenus;
}

void LookAndFeel::setRTL( bool rtl )
{
	this->rtl = rtl;
	if(rtl) {
		Display::getInstance()->setBidiAlgorithm(true);
	}

}

bool LookAndFeel::isRTL()
{
	return rtl;
}

int LookAndFeel::getTactileTouchDuration()
{
	 return tactileTouchDuration;
}

void LookAndFeel::setTactileTouchDuration( int tactileTouchDuration )
{
	 this->tactileTouchDuration = tactileTouchDuration;
}

shared_ptr<Transition> LookAndFeel::getDefaultFormTransitionOut()
{
	return defaultFormTransitionOut;
}

void LookAndFeel::setDefaultFormTransitionOut( shared_ptr<Transition> defaultFormTransitionOut )
{
	this->defaultFormTransitionOut = defaultFormTransitionOut;
}

shared_ptr<Transition> LookAndFeel::getDefaultDialogTransitionIn()
{
	return defaultDialogTransitionIn;
}

void LookAndFeel::setDefaultDialogTransitionIn( shared_ptr<Transition> defaultDialogTransitionIn )
{
	this->defaultDialogTransitionIn = defaultDialogTransitionIn;
}

void LookAndFeel::bind( shared_ptr<Component> cmp )
{

}

void LookAndFeel::uninstall()
{

}

LookAndFeel::~LookAndFeel()
{

}
__GUI_END_NAMESPACE
