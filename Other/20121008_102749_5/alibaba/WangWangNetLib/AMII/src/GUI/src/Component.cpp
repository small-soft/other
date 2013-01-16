
#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

AM_IMPLEMENT_DYNAMIC(Component, Animation)

Component::Component(void)
{
	shared_ptr<LookAndFeel> laf = UIManager::getInstance()->getLookAndFeel();
	animationSpeed = laf->getDefaultSmoothScrollingSpeed();
	rtl = laf->isRTL();
	tactileTouch = isFocusable();

	selectText = UIManager::getInstance()->localize(L"select", L"Select");
	dirtyRegionLock = new Locker();
	enabled = true;
	tactileTouch = false;
	visible = true;
	cellRenderer = false;
	bounds = new Rectangle(0, 0, new Dimension(0, 0));
	scrollX = 0;
	scrollY = 0;
	sizeRequestedByUser = false;
	scrollSizeRequestedByUser = false;
	focused = false;
	focusPainted = true;
	focusListeners = new EventDispatcher<FocusListener>();
	isHandlesInput = false;
	shouldCalcPreferredSize = true;
	shouldCalcScrollSize = true;
	focusable = true;
	scrollVisible = true;
	smoothScrolling = false;
	animationSpeed = 0;
	dragActivated = false;
	initialScrollY  = -1;
	destScrollY = -1;
	lastScrollX = 0;
	lastScrollY = 0;
	initialized = false;
	canLeftRight = true;
	canUpDown = true;
	scrollToVisible = true;
	rtl = false;
}

Component::~Component(void)
{
}

void Component::initStyle()
{	
	//cycle use
	shared_ptr<Component> cmp = this->shared_from_this();
	String str(*getUIID());

	unSelectedStyle = UIManager::getInstance()->getComponentStyle(str);
	if (unSelectedStyle.get() != NULL) {
		unSelectedStyle->addStyleListener(cmp);
		if (unSelectedStyle->getBgPainter().get() == NULL) {
			unSelectedStyle->setBgPainter(new BGPainter(cmp));
		}
	}
}

int Component::getX()
{
	 return bounds->getX();
}

int Component::getY()
{
	return bounds->getY();
}

bool Component::isVisible()
{
	return visible;
}

shared_ptr<Object> Component::getClientProperty( shared_ptr<String> key )
{
	shared_ptr<Object> ret;
	if (clientProperties.get() != NULL) {
		ret = clientProperties->get(*key);
	}
	return ret;
}

void Component::putClientProperty(shared_ptr<String> key,shared_ptr<Object> value )
{
	if (clientProperties.get() == NULL) {
		if (value.get() == NULL) {
			return;
		}
		clientProperties = new Map<String,shared_ptr<Object> >;
	}
	if (value.get() == NULL) {
		clientProperties->remove(*key);
		if (clientProperties->size() == 0) {
			clientProperties.reset();
		}
	} else {
		clientProperties->put(*key,value);
	}
}

 shared_ptr<Rectangle> Component::getDirtyRegion()const
{
	return dirtyRegion;
}

void Component::setDirtyRegion( shared_ptr<Rectangle> dirty )
{
	dirtyRegionLock->lock();
	{
		this->dirtyRegion = dirty;
	}
	dirtyRegionLock->unlock();
}

void Component::setVisible( bool visible )
{
	 this->visible = visible;
}

int Component::getWidth()
{
	return bounds->getSize()->getWidth();
}

int Component::getHeight()
{
	return bounds->getSize()->getHeight();
}

void Component::setX( int x )
{
	 bounds->setX(x);;
}

void Component::setY( int y )
{
	 bounds->setY(y);
}

int Component::getBaseline( int width, int height )
{
	return height - getStyle()->getPadding(false, BOTTOM);
}

int Component::getBaselineResizeBehavior()
{
	 return BRB_OTHER;
}

void Component::setPreferredSize( shared_ptr<Dimension> d )
{
	shared_ptr<Dimension> dim = preferredSize();
	dim->setWidth(d->getWidth());
	dim->setHeight(d->getHeight());
	sizeRequestedByUser = true;
}

shared_ptr<Dimension> Component::getPreferredSize()
{
	 return preferredSize();
}

shared_ptr<Dimension> Component::getPreferredSizeWithMargin()
{
	shared_ptr<Dimension> d = preferredSize();
	shared_ptr<Style> s = getStyle();
	return new Dimension(d->getWidth() +s->getMargin(LEFT) + s->getMargin(RIGHT), d->getHeight() + s->getMargin(TOP) + s->getMargin(BOTTOM));
}

shared_ptr<Dimension> Component::getScrollDimension()
{
	if (!scrollSizeRequestedByUser && (scrollSize.get() == NULL || shouldCalcScrollSize)) {
		scrollSize = calcScrollSize();
		shouldCalcScrollSize = false;
	}
	return scrollSize;
}

shared_ptr<Dimension> Component::calcScrollSize()
{
	return calcPreferredSize();
}

void Component::setScrollSize( shared_ptr<Dimension> d )
{
	scrollSize = d;
	scrollSizeRequestedByUser = true;
}

void Component::setPreferredW( int preferredW )
{
	shared_ptr<Dimension> d = new Dimension(preferredW, getPreferredH());
	setPreferredSize(d);
}

void Component::setPreferredH( int preferredH )
{
	shared_ptr<Dimension> d = new Dimension(getPreferredW(), preferredH);
	setPreferredSize(d);
}

int Component::getPreferredW()
{
	 return getPreferredSize()->getWidth();
}

int Component::getPreferredH()
{
	 return getPreferredSize()->getHeight();
}

void Component::setWidth( int width )
{
	bounds->getSize()->setWidth(width);
}

void Component::setHeight( int height )
{
	 bounds->getSize()->setHeight(height);
}

void Component::setSize( shared_ptr<Dimension> d )
{
	shared_ptr<Dimension> d2 = bounds->getSize();
	d2->setWidth(d->getWidth());
	d2->setHeight(d->getHeight());
}

shared_ptr<String> Component::getUIID()
{
	 return id;
}

void Component::setUIID( shared_ptr<String> id )
{
	shared_ptr<String> tmpId = this->id;
	this->id = id;
	if (tmpId.get() != NULL && *tmpId!=*id) {
		initStyle();
	}
	selectedStyle.reset();
}

shared_ptr<Container> Component::getParent()
{
	return parent;
}

void Component::setParent( shared_ptr<Container> parent )
{
	 this->parent = parent;
}

void Component::addFocusListener( weak_ptr<FocusListener> l )
{
	 focusListeners->addListener(l);
}

void Component::removeFocusListener( weak_ptr<FocusListener> l )
{
	 focusListeners->removeListener(l);
}

void Component::fireClicked()
{

}

bool Component::isSelectableInteraction()
{
	return false;
}

void Component::fireFocusGained()
{
	fireFocusGained(this->shared_from_this());
}

void Component::fireFocusGained( shared_ptr<Component> cmp )
{
	if (cmp->isCellRenderer()) {
		return;
	}

	focusListeners->fireFocus(cmp);
	focusGainedInternal();
	focusGained();
	if (isSelectableInteraction()) {
		shared_ptr<Form> f = getComponentForm();
		if (f.get() != NULL) {
			f->addSelectCommand(getSelectCommandText());
		}
	}
}
void Component::fireFocusLost()
{	
	fireFocusLost(this->shared_from_this());
}

void Component::fireFocusLost( shared_ptr<Component> cmp )
{
	if (cmp->isCellRenderer()) {
		return;
	}
	if (isSelectableInteraction()) {
		shared_ptr<Form> f = getComponentForm();
		if (f.get() != NULL) {
			f->removeSelectCommand();
		}
	}

	focusListeners->fireFocus(cmp);
	focusLostInternal();
	focusLost();
}
void Component::setSelectCommandText( shared_ptr<String> selectText )
{
	 this->selectText = selectText;
}

shared_ptr<String> Component::getSelectCommandText()
{
	return selectText;
}

void Component::fireActionEvent()
{

}

void Component::setLabelForComponent( shared_ptr<Label> componentLabel )
{
	 this->componentLabel = componentLabel;
}

void Component::focusGainedInternal()
{
	if (componentLabel.get() != NULL && componentLabel->isTickerEnabled()) {
		if (componentLabel->shouldTickerStart()) {
			componentLabel->startTicker(UIManager::getInstance()->getLookAndFeel()->getTickerSpeed(), true);
		}
	}
}

void Component::focusGained()
{

}

void Component::focusLost()
{
	if (componentLabel.get() != NULL && componentLabel->isTickerEnabled() && componentLabel->isTickerRunning()) {
		componentLabel->stopTicker();
	}
}

void Component::focusLostInternal()
{

}

void Component::paintBackgrounds( shared_ptr<Graphics> g )
{
	drawPainters(g, this->getParent(), this->shared_from_this(), getAbsoluteX() + getScrollX(),
		getAbsoluteY() + getScrollY(),
		getWidth(), getHeight());
}

int Component::getAbsoluteX()
{
	int x = getX() - getScrollX();
	shared_ptr<Container> parent = getParent();
	if (parent.get() != NULL) {
		x += parent->getAbsoluteX();
	}
	return x;
}

int Component::getAbsoluteY()
{
	int y = getY() - getScrollY();
	shared_ptr<Container>parent = getParent();
	if (parent.get() != NULL) {
		y += parent->getAbsoluteY();
	}
	return y;
}

void Component::paintInternal( shared_ptr<Graphics> g )
{
	 paintInternal(g, true);
}

void Component::paintInternal( shared_ptr<Graphics> g, bool paintIntersects )
{
	if (!isVisible()) {
		return;
	}
	int oX = g->getClipX();
	int oY = g->getClipY();
	int oWidth = g->getClipWidth();
	int oHeight = g->getClipHeight();
	if (bounds->intersects(oX, oY, oWidth, oHeight)) {
		g->clipRect(getX(), getY(), getWidth(), getHeight());
		paintBackground(g);

		if (isScrollable()) {
			int scrollX = getScrollX();
			int scrollY = getScrollY();
			g->translate(-scrollX, -scrollY);
			paint(g);
			g->translate(scrollX, scrollY);
			if (isScrollVisible()) {
				paintScrollbars(g);
			}
		} else {
			//add by qianjiajing for fixing scroll bar bug
			scrollX = 0;
			scrollY = 0;
			//end
			paint(g);
		}
		if (isBorderPainted()) {
			paintBorder(g);
		}

		//paint all the intersecting Components above the Component
		if (paintIntersects && parent.get() != NULL) {
			paintIntersectingComponentsAbove(g);
		}

		g->setClip(oX, oY, oWidth, oHeight);
	}
}

void Component::paintIntersectingComponentsAbove( shared_ptr<Graphics> g )
{
	shared_ptr<Container> parent = getParent();
	
	shared_ptr<Component> component = this->shared_from_this();
	int tx = g->getTranslateX();
	int ty = g->getTranslateY();

	g->translate(-tx, -ty);
	while (parent.get() != NULL) {
		g->translate(parent->getAbsoluteX() + parent->getScrollX(),
			parent->getAbsoluteY() + parent->getScrollY());
		parent->paintIntersecting(g, component, getAbsoluteX() + getScrollX(),
			getAbsoluteY() + getScrollY(),
			getWidth(), getHeight(), true);
		g->translate(-parent->getAbsoluteX() - parent->getScrollX(),
			-parent->getAbsoluteY() - parent->getScrollY());
		component = static_pointer_cast<Component>(parent);
		parent = parent->getParent();
	}
	g->translate(tx, ty);
}

void Component::paintScrollbars( shared_ptr<Graphics> g )
{
	if (isScrollableX()) {
		paintScrollbarX(g);
	}
	if (isScrollableY()) {
		paintScrollbarY(g);
	}
}

void Component::paintScrollbarX( shared_ptr<Graphics> g )
{	
//	weak_ptr<Component> cmp = this;
	float scrollW = (float)getScrollDimension()->getWidth();
	float block = ((float) getWidth()) / scrollW;
	float offset;
	if(getScrollX() + getWidth() == scrollW) {
		// normalize the offset to avoid rounding errors to the bottom of the screen
		offset = 1 - block;
	} else {
		offset = (((float) getScrollX() + getWidth()) / scrollW) - block;
	}
	UIManager::getInstance()->getLookAndFeel()->drawHorizontalScroll(g, this->shared_from_this(), offset, block);
}

void Component::paintScrollbarY( shared_ptr<Graphics> g )
{
//	weak_ptr<Component> cmp = this;
	float scrollH = (float)getScrollDimension()->getHeight();
	float block = ((float) getHeight()) / scrollH;
	float offset;
	if(getScrollY() + getHeight() == scrollH) {
		// normalize the offset to avoid rounding errors to the bottom of the screen
		offset = 1 - block;
	} else {
		offset = (((float) getScrollY() + getHeight()) / scrollH) - block;
	}
	UIManager::getInstance()->getLookAndFeel()->drawVerticalScroll(g, this->shared_from_this(), offset, block);
}

void Component::paintComponent( shared_ptr<Graphics> g )
{	
	 paintComponent(g, true);
//	 paintComponent(g, false);//for no clip
}

void Component::paintComponent( shared_ptr<Graphics> g, bool background )
{
	int clipX = g->getClipX();
	int clipY = g->getClipX();
	int clipW = g->getClipWidth();
	int clipH = g->getClipHeight();
	shared_ptr<Container> parent = getParent();
	int translateX = 0;
	int translateY = 0;
	while (parent.get() != NULL) {
		translateX += parent->getX();
		translateY += parent->getY();
	
		if (parent->isScrollableX()) {
			translateX -= parent->getScrollX();
		}
		if (parent->isScrollableY()) {
			translateY -= parent->getScrollY();
		}
		// since scrollability can translate everything... we should clip based on the
		// current scroll
		int parentX = parent->getAbsoluteX() + parent->getScrollX();
		if (isRTL()) {
			parentX += parent->getSideGap();
		}
		g->clipRect(parentX, parent->getAbsoluteY() + parent->getScrollY(),
			parent->getWidth() - parent->getSideGap(), parent->getHeight() - parent->getBottomGap());

		parent = parent->getParent();
	}

	g->clipRect(translateX + getX(), translateY + getY(), getWidth(), getHeight());
//	printf("paintBackgrounds 1:%d\n",System::currentTimeMillis());
	if (background) {
		paintBackgrounds(g);
	}
//	printf("paintBackgrounds 2:%d\n",System::currentTimeMillis());
	g->translate(translateX, translateY);
//	printf("paintInternal 1:%d\n",System::currentTimeMillis());
	paintInternal(g);
//	printf("paintInternal 2:%d\n",System::currentTimeMillis());
	g->translate(-translateX, -translateY);

	shared_ptr<Form> parentForm = getComponentForm();
	if (parentForm.get() != NULL) {
		shared_ptr<Painter> glass = parentForm->getGlassPane();
		if (glass.get() != NULL) {
			int tx = g->getTranslateX();
			int ty = g->getTranslateY();
			g->translate(-tx, -ty);
			glass->paint(g, parentForm->getBounds());
			g->translate(tx, ty);
		}
	}

	g->setClip(clipX, clipY, clipW, clipH);
}

void Component::drawPainters( shared_ptr<Graphics> g, shared_ptr<Component> par, shared_ptr<Component> c,int x, int y, int w, int h )
{
	if (par.get() == NULL) {
		return;
	} else {

		if (par->getStyle()->getBgTransparency() != ((unsigned char) 0xFF)) {
			drawPainters(g, par->getParent(), par, x, y, w, h);
		}
	}

	if (!par->isVisible()) {
		return;
	}

	int transX = par->getAbsoluteX() + par->getScrollX();
	int transY = par->getAbsoluteY() + par->getScrollY();

	g->translate(transX, transY);
	Container* container = dynamic_cast<Container*>(par.get());
	if(container != NULL)
		container->paintIntersecting(g, c, x, y, w, h, false);

	if (par->isBorderPainted()) {
		shared_ptr<Border> b = par->getBorder();
		if (b->isBackgroundPainter()) {
			g->translate(-par->getX(), -par->getY());
			b->paintBorderBackground(g, par);
			b->paint(g, par);
			g->translate(par->getX() - transX, par->getY() - transY);
			return;
		}
	}
	shared_ptr<Painter> p = par->getStyle()->getBgPainter();
	if (p.get() != NULL) {
		p->paint(g, new Rectangle(0, 0, par->getWidth(), par->getHeight()));
	}
	g->translate(-transX, -transY);
}

shared_ptr<Border> Component::getBorder()
{
	return getStyle()->getBorder();
}

void Component::paintBackground( shared_ptr<Graphics> g )
{
//	weak_ptr<Component> cmp = this;
	if (isBorderPainted()) {
		shared_ptr<Border> b = getBorder();
		if (b.get() != NULL && b->isBackgroundPainter()) {
			b->paintBorderBackground(g, this->shared_from_this());
			return;
		}
	}
	if (getStyle()->getBgPainter().get() != NULL) {
		getStyle()->getBgPainter()->paint(g, bounds);
	}
}

void Component::paint( shared_ptr<Graphics> g )
{

}

bool Component::isScrollable()
{
	return isScrollableX() || isScrollableY();
}

bool Component::isScrollableX()
{
	return false;
}

bool Component::isScrollableY()
{
	return false;
}

int Component::getScrollX()
{
	 return scrollX;
}

int Component::getScrollY()
{
	return scrollY;
}

void Component::setScrollX( int scrollX )
{
	this->scrollX = scrollX;
	this->scrollX = min(this->scrollX, getScrollDimension()->getWidth() - getWidth());        
	this->scrollX = max(this->scrollX, 0);
	if (isScrollableX()) {
		repaint();
	}
}

void Component::setScrollY( int scrollY )
{
	this->scrollY = scrollY;
	this->scrollY = min(this->scrollY, getScrollDimension()->getHeight() - getHeight());
	this->scrollY = max(this->scrollY, 0);
	if (isScrollableY()) {
		repaint();
	}
}

int Component::getBottomGap()
{
	if (isScrollableX() && isScrollVisible()) {
		return UIManager::getInstance()->getLookAndFeel()->getHorizontalScrollHeight();
	}
	return 0;
}

int Component::getSideGap()
{
	if (isScrollableY() && isScrollVisible()) {
		return UIManager::getInstance()->getLookAndFeel()->getVerticalScrollWidth();
	}
	return 0;
}

bool Component::contains( int x, int y )
{
	int absX = getAbsoluteX() + getScrollX();
	int absY = getAbsoluteY() + getScrollY();
	return (x >= absX && x < absX + getWidth() && y >= absY && y < absY + getHeight());
}

shared_ptr<Dimension> Component::calcPreferredSize()
{
	shared_ptr<Dimension> d = new Dimension(0, 0);
	return d;
}

shared_ptr<Dimension> Component::preferredSize()
{
	if (!sizeRequestedByUser && (shouldCalcPreferredSize || preferredSizeD.get() == NULL)) {
		shouldCalcPreferredSize = false;
		preferredSizeD = calcPreferredSize();
	}
	return preferredSizeD;
}

shared_ptr<Rectangle> Component::getBounds()
{
	return bounds;
}

shared_ptr<Rectangle> Component::getVisibleBounds()
{
	return bounds;
}

bool Component::isFocusable()
{
	return focusable && enabled && isVisible();
}

void Component::setFocusable( bool focusable )
{
	this->focusable = focusable;
	shared_ptr<Form> p = getComponentForm();
	if (p.get() != NULL) {
		p->clearFocusVectors();
	}
}

void Component::setShouldCalcPreferredSize( bool shouldCalcPreferredSize )
{
	if (!shouldCalcScrollSize) {
		this->shouldCalcScrollSize = shouldCalcPreferredSize;
	}
	if (shouldCalcPreferredSize != this->shouldCalcPreferredSize) {
		this->shouldCalcPreferredSize = shouldCalcPreferredSize;
		this->shouldCalcScrollSize = shouldCalcPreferredSize;
		if (shouldCalcPreferredSize && getParent().get() != NULL) {
			this->shouldCalcPreferredSize = shouldCalcPreferredSize;
			getParent()->setShouldCalcPreferredSize(shouldCalcPreferredSize);
		}
	}
}

bool Component::isFocusPainted()
{
	return focusPainted;
}

void Component::setFocusPainted( bool focusPainted )
{
	this->focusPainted = focusPainted;
}

bool Component::handlesInput()
{
	 return isHandlesInput;
}

void Component::setHandlesInput( bool handlesInput )
{
	this->isHandlesInput = handlesInput;
}

bool Component::hasFocus()
{
	return focused;
}

void Component::setFocus( bool focused )
{
	this->focused = focused;
}

shared_ptr<Form> Component::getComponentForm()
{
	shared_ptr<Form> retVal;
	shared_ptr<Component> parent = getParent();
	if (parent.get() != NULL) {
		retVal = parent->getComponentForm();
	}
	return retVal;
}

void Component::repaint( shared_ptr<Component> cmp )
{
	if (isCellRenderer() || cmp->getWidth() <= 0 || cmp->getHeight() <= 0) {
		return;
	}
	// null parent repaint can happen when a component is removed and modified which
	// is common for a popup
	shared_ptr<Component> parent = getParent();
	if (parent.get() != NULL) {
		parent->repaint(cmp);
	}
}

void Component::repaint()
{
	if (dirtyRegion.get() != NULL) {
		shared_ptr<Rectangle>  d;
		setDirtyRegion(d);
	}
	repaint(this->shared_from_this());
}

void Component::repaint( int x, int y, int w, int h )
{
	shared_ptr<Rectangle> rect;
	dirtyRegionLock->lock();
	{
		if (dirtyRegion.get() == NULL) {
			rect = new Rectangle(x, y, w, h);
			setDirtyRegion(rect);
		} else if (dirtyRegion->getX() != x || dirtyRegion->getY() != y ||
			dirtyRegion->getSize()->getWidth() != w || dirtyRegion->getSize()->getHeight() != h) {
				rect = new Rectangle(*dirtyRegion);
				shared_ptr<Dimension> size = rect->getSize();

				int x1 = min(rect->getX(), x);
				int y1 = min(rect->getY(), y);

				int x2 = max(x + w, rect->getX() + size->getWidth());
				int y2 = max(y + h, rect->getY() + size->getHeight());

				rect->setX(x1);
				rect->setY(y1);
				size->setWidth(x2 - x1);
				size->setHeight(y2 - y1);
				setDirtyRegion(rect);
		}
	}
	dirtyRegionLock->unlock();
	
	repaint(this->shared_from_this());
}

void Component::longKeyPress( int keyCode )
{

}

void Component::keyPressed( int keyCode )
{

}

void Component::keyReleased( int keyCode )
{

}

void Component::keyRepeated( int keyCode )
{
	keyPressed(keyCode);
	keyReleased(keyCode);
}

void Component::setAnimationMotion( shared_ptr<Motion> motion )
{
	 animationMotion = motion;
}

shared_ptr<Motion> Component::getAnimationMotion()
{
	return animationMotion;
}

int Component::getScrollAnimationSpeed()
{
	return animationSpeed;
}

void Component::setScrollAnimationSpeed( int animationSpeed )
{
	  this->animationSpeed = animationSpeed;
}

bool Component::isSmoothScrolling()
{
	 return smoothScrolling;
}

void Component::setSmoothScrolling( bool smoothScrolling )
{
	  this->smoothScrolling = smoothScrolling;
}

void Component::pointerHover( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y )
{
	draggedMotion.reset();
	pointerDragged(x, y);
}

void Component::clearDrag()
{
	draggedMotion.reset();
}

void Component::pointerHoverReleased( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y )
{
	pointerReleaseImpl((*x)[0], (*y)[0]);
}

void Component::pointerDragged( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y )
{
	 pointerDragged((*x)[0], (*y)[0]);
}

void Component::pointerDragged( int x, int y )
{
	if (isScrollable() && isSmoothScrolling()) {
		int axisValue;
		if (isScrollableY()) {
			axisValue = y;
		} else {
			axisValue = x;
		}

		if (!dragActivated) {
			dragActivated = true;
			lastScrollY = y;
			lastScrollX = x;
			shared_ptr<Form> p = getComponentForm();
			shared_ptr<Component> cmp = this->shared_from_this();
			p->setDraggedComponent(cmp);
			shared_ptr<Animation> ani = static_pointer_cast<Animation>(cmp);
			p->registerAnimatedInternal(dynamic_pointer_cast<Animation>(ani));
		}

		// we drag inversly to get a feel of grabbing a physical screen
		// and pulling it in the reverse direction of the drag
		if (isScrollableY()) {
			int scroll = getScrollY() + (lastScrollY - y);
			if (scroll >= 0 && scroll < getScrollDimension()->getHeight() - getHeight()) {
				setScrollY(scroll);
			}
		}
		if (isScrollableX()) {
			int scroll = getScrollX() + (lastScrollX - x);
			if (scroll >= 0 && scroll < getScrollDimension()->getWidth() - getWidth()) {
				setScrollX(scroll);
			}
		}
		lastScrollY = y;
		lastScrollX = x;
	} else {
		//try to find a scrollable element until you reach the Form
		shared_ptr<Component>  parent = getParent();
		Form *form = dynamic_cast<Form*>(parent.get());
		if (form != NULL) {
			parent->pointerDragged(x, y);
		}
	}

}

void Component::initScrollMotion()
{
	shared_ptr<Form> f = getComponentForm();
	if (f.get()!= NULL) {
		f->registerAnimatedInternal(this->shared_from_this());
	}

	shared_ptr<Motion> m = Motion::createLinearMotion(initialScrollY, destScrollY, getScrollAnimationSpeed());
	setAnimationMotion(m);
	m->start();
}

void Component::pointerPressed( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y )
{
	draggedMotion.reset();
	dragActivated = false;
	pointerPressed((*x)[0], (*y)[0]);
}

void Component::pointerPressed( int x, int y )
{
	draggedMotion.reset();
}

void Component::pointerReleased(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y )
{
	 pointerReleased((*x)[0], (*y)[0]);
}

void Component::pointerReleased( int x, int y )
{
  pointerReleaseImpl(x, y);
}
void Component::longPointerPress( int x, int y )
{

}

void Component::pointerReleaseImpl( int x, int y )
{
	if (dragActivated) {
		int scroll = scrollY;
		if(isScrollableX()){
			scroll = scrollX;
		}
		draggedMotion = Motion::createFrictionMotion(scroll,
			Display::getInstance()->getDragSpeed(isScrollableY()),0.0004f);

		draggedMotion->start();
		dragActivated = false;
	}
}

shared_ptr<Style> Component::getStyle()
{
	if (unSelectedStyle.get() == NULL) {
		initStyle();
	}

	if (hasFocus() && isFocusPainted()) {
		return getSelectedStyle();
	}
	return unSelectedStyle;
}

shared_ptr<Style> Component::getUnselectedStyle()
{
	if (unSelectedStyle.get() == NULL) {
		initStyle();
	}
	return unSelectedStyle;
}

shared_ptr<Style> Component::getSelectedStyle()
{
	shared_ptr<Component> cmp = this->shared_from_this();
	if (selectedStyle.get() == NULL) {
		selectedStyle = UIManager::getInstance()->getComponentSelectedStyle(*getUIID());

		selectedStyle->addStyleListener(static_pointer_cast<StyleListener>(cmp));
		if (selectedStyle->getBgPainter().get() == NULL) {
			shared_ptr<BGPainter> painter = new BGPainter(cmp);
			selectedStyle->setBgPainter(painter);
		}
	}
	return selectedStyle;
}

void Component::setUnSelectedStyle( shared_ptr<Style> style )
{
	shared_ptr<Component> cmp = this->shared_from_this();
	if (this->unSelectedStyle.get() != NULL) 
	{
		this->unSelectedStyle->removeStyleListener(static_pointer_cast<StyleListener>(cmp));
	}
	this->unSelectedStyle = style;

	this->unSelectedStyle->addStyleListener(static_pointer_cast<StyleListener>(cmp));
	if (this->unSelectedStyle->getBgPainter().get() == NULL) 
	{
		shared_ptr<BGPainter> painter = new BGPainter(cmp);
		unSelectedStyle->setBgPainter(painter);
	}
	setShouldCalcPreferredSize(true);
	checkAnimation();
}

void Component::setSelectedStyle(shared_ptr<Style> style )
{
	shared_ptr<Component> cmp = this->shared_from_this();
	if (this->selectedStyle.get() != NULL) {
		this->selectedStyle->removeStyleListener(dynamic_pointer_cast<StyleListener>(cmp));
	}
	this->selectedStyle = style;

	this->selectedStyle->addStyleListener(dynamic_pointer_cast<StyleListener>(cmp));
	if (this->selectedStyle->getBgPainter().get() == NULL) {	
		shared_ptr<BGPainter> painter = new BGPainter(cmp);
		selectedStyle->setBgPainter(painter);
	}
	setShouldCalcPreferredSize(true);
	checkAnimation();
}

void Component::requestFocus()
{	
//	weak_ptr<Component> cmp = this;
	shared_ptr<Form> rootForm = getComponentForm();
	if (rootForm.get() != NULL) {
		rootForm->requestFocus(this->shared_from_this());
	}
}

void Component::refreshTheme()
{
	 refreshTheme(getUIID());
}

void Component::refreshTheme( shared_ptr<String> id )
{	
//	weak_ptr<Component> cmp = this;
	shared_ptr<Style> unSelected = getUnselectedStyle();
	setUnSelectedStyle(mergeStyle(unSelected, UIManager::getInstance()->getComponentStyle(*id)));

	if (selectedStyle.get() != NULL) {
		setSelectedStyle(mergeStyle(selectedStyle, UIManager::getInstance()->getComponentSelectedStyle(*id)));
	}
	checkAnimation();
	UIManager::getInstance()->getLookAndFeel()->bind(this->shared_from_this());
}

shared_ptr<Style> Component::mergeStyle( shared_ptr<Style> toMerge, shared_ptr<Style> newStyle )
{
	if (toMerge->isModified()) {
		toMerge->merge(newStyle);
		return toMerge;
	} else {
		return newStyle;
	}
}

bool Component::isDragActivated()
{
	 return dragActivated;
}

void Component::setDragActivated( bool dragActivated )
{
	this->dragActivated = dragActivated;
}

void Component::checkAnimation()
{
//	weak_ptr<Component> cmp = this;
	shared_ptr<Image> bgImage = getStyle()->getBgImage();
	if (bgImage.get() != NULL && bgImage->isAnimation()) {
		shared_ptr<Form> parent = getComponentForm();
		if (parent.get() != NULL) {
			// animations are always running so the internal animation isn't
			// good enough. We never want to stop this sort of animation
			parent->registerAnimated(this->shared_from_this());
		}
	}
}

void Component::deregisterAnimatedInternal()
{	
//	weak_ptr<Component> cmp = this;
	shared_ptr<Form> f = getComponentForm();
	if (f.get() != NULL) {
		f->deregisterAnimatedInternal(this->shared_from_this());
	}
}

bool Component::animate()
{
	shared_ptr<Image> bgImage = getStyle()->getBgImage();
	bool animateBackground = bgImage.get() != NULL && bgImage->isAnimation() && bgImage->animate();
	shared_ptr<Motion> m = getAnimationMotion();
	//preform regular scrolling
	if (m.get() != NULL && destScrollY != -1 && destScrollY != getScrollY()) {
		// change the variable directly for efficiency both in removing redundant
		// repaints and scroll checks
		setScrollY(m->getValue());
		if (destScrollY == scrollY) {
			destScrollY = -1;
			deregisterAnimatedInternal();
		}
		return true;
	}

	//preform the dragging motion if exists
	if (draggedMotion.get() != NULL && !draggedMotion->isFinished()) {
		// change the variable directly for efficiency both in removing redundant
		// repaints and scroll checks
		int dragVal = draggedMotion->getValue();
		if (isScrollableY()) {
			if (dragVal >= 0 && dragVal <= (getScrollDimension()->getHeight() - getHeight())) {
				scrollY = dragVal;
				return true;
			}
		} else {
			if (dragVal >= 0 && dragVal <= (getScrollDimension()->getWidth() - getWidth())) {
				scrollX = dragVal;
				return true;
			}
		}
	}
	//to do
	//if (animateBackground && typeid(bgImage) == typeid(StaticAnimation))
	//{
	//	Rectangle *dirty = ((StaticAnimation*) bgImage)->getDirtyRegion();
	//	if (dirty != NULL) {
	//		dirty->setX(getAbsoluteX());
	//		dirty->setY(getAbsoluteY() + dirty->getY());
	//	}
	//	setDirtyRegion(dirty);
	//}
	return animateBackground;

}

void Component::scrollRectToVisible( int x, int y, int width, int height, shared_ptr<Component> coordinateSpace )
{
	if (isScrollable()) {
		int scrollPosition = getScrollY();
		shared_ptr<Style> s = getStyle();
		int w = getWidth() - s->getPadding(isRTL(), LEFT) - s->getPadding(isRTL(), RIGHT);
		int h = getHeight() - s->getPadding(false, TOP) - s->getPadding(false, BOTTOM);

		shared_ptr<Rectangle>view;
		if (isSmoothScrolling() && destScrollY > -1) {
			view = new Rectangle(destScrollY, getScrollX(), w, h);
		} else {
			view = new Rectangle(getScrollX(), getScrollY(), w, h);
		}

		int relativeX = x;
		int relativeY = y;

		// component needs to be in absolute coordinates...
		shared_ptr<Container> parent ;
		if (coordinateSpace.get() != NULL) {
			parent = coordinateSpace->getParent();
		}
		if (parent.get() == this) {
			if (view->contains(x, y, width, height)) {
				return;
			}
		} else {
			while (parent.get() != this) {
				// mostly a special case for list
				if (parent.get() == NULL) {
					relativeX = x;
					relativeY = y;
					break;
				}
				relativeX += parent->getX();
				relativeY += parent->getY();
				parent = parent->getParent();
			}
			if (view->contains(relativeX, relativeY, width, height)) {
				return;
			}
		}
		if (isScrollableX()) {
			if (getScrollX() > relativeX) {
				setScrollX(relativeX);
			}
			int rightX = relativeX + width;
			if (getScrollX() + w < rightX) {
				setScrollX(getScrollX() + (rightX - (getScrollX() + w)));
			} else {
				if (getScrollX() > relativeX) {
					setScrollX(relativeX);
				}
			}
		}

		if (isScrollableY()) {
			if (getScrollY() > relativeY) {
				scrollPosition = relativeY;
			}
			int bottomY = relativeY + height - 
				s->getPadding(TOP) - s->getPadding(BOTTOM);
			if (getScrollY() + h < bottomY) {
				scrollPosition = getScrollY() + (bottomY - (getScrollY() + h));
			} else {
				if (getScrollY() > relativeY) {
					scrollPosition = relativeY;
				}
			}
			if (isSmoothScrolling()) {
				initialScrollY = getScrollY();
				destScrollY = scrollPosition;
				initScrollMotion();
			} else {
				setScrollY(scrollPosition);
			}
		}
		repaint();
	} else {
		//try to move parent scroll if you are not scrollable
		shared_ptr<Container> parent = getParent();
		if (parent.get() != NULL) {
			parent->scrollRectToVisible(getAbsoluteX() - parent->getAbsoluteX() + x,
				getAbsoluteY() - parent->getAbsoluteY() + y, 
				width, height, parent);
		}
	}

}
void Component::scrollRectToVisible( shared_ptr<Rectangle> rect, shared_ptr<Component> coordinateSpace )
{
	scrollRectToVisible(rect->getX(), rect->getY(), 
		rect->getSize()->getWidth(), rect->getSize()->getHeight(), coordinateSpace);
}

bool Component::isBorderPainted()
{
	return getStyle()->getBorder().get() != NULL;
}

void Component::paintBorder( shared_ptr<Graphics> g )
{
	shared_ptr<Border> b = getBorder();
	if (b.get() != NULL) {
		g->setColor(getStyle()->getFgColor());
		b->paint(g, this->shared_from_this());
	}
}

void Component::setCellRenderer( bool cellRenderer )
{
	this->cellRenderer = cellRenderer;
}

bool Component::isCellRenderer()
{
	return cellRenderer;
}

bool Component::isScrollVisible()
{
	 return scrollVisible;
}

void Component::setIsScrollVisible( bool isScrollVisible )
{
	scrollVisible = isScrollVisible;
}

void Component::initComponentImpl()
{
	if (!initialized) {
		initialized = true;
		getStyle();
		UIManager::getInstance()->getLookAndFeel()->bind(this->shared_from_this());
		checkAnimation();
		if(isRTL() && isScrollableX()){
			setScrollX(getScrollDimension()->getWidth());
		}
		initComponent();
	}
}

void Component::deinitializeImpl()
{
	if (isInitialized()) {
		setInitialized(false);
		shared_ptr<Rectangle> d;
		setDirtyRegion(d);
		deinitialize();
	}
}

void Component::laidOut()
{
	if (isScrollableY() && getScrollY() > 0 && getScrollY() + getHeight() > 
		getScrollDimension()->getHeight()) {
			setScrollY(getScrollDimension()->getHeight() - getHeight());
	}
	if (isScrollableX() && getScrollX() > 0 && getScrollX() + getWidth() > 
		getScrollDimension()->getWidth()) {
			setScrollX(getScrollDimension()->getWidth() - getWidth());
	}
	if(!isScrollableY()){
		setScrollY(0);
	}
	if(!isScrollableX()){
		setScrollX(0);
	}
}

void Component::deinitialize()
{

}

void Component::initComponent()
{

}

bool Component::isInitialized()
{
	return initialized;
}

void Component::setInitialized( bool initialized )
{
	 this->initialized = initialized;
}

void Component::styleChanged( shared_ptr<String> propertyName, shared_ptr<Style> source )
{
	if ((!shouldCalcPreferredSize &&
		source == getStyle()) &&
		(*propertyName == Style::FONT ||
		*propertyName == Style::MARGIN ||
		*propertyName == Style::PADDING)) {
			setShouldCalcPreferredSize(true);
			shared_ptr<Container> parent = getParent();
			if (parent.get() != NULL && parent->getComponentForm().get() != NULL) {
				parent->revalidate();
			}
	}
}

shared_ptr<Component> Component::getNextFocusDown()
{
	 return nextFocusDown;
}

void Component::setNextFocusDown( shared_ptr<Component> nextFocusDown )
{
	this->nextFocusDown = nextFocusDown;
}

shared_ptr<Component> Component::getNextFocusUp()
{
	return nextFocusUp;
}

void Component::setNextFocusUp( shared_ptr<Component> nextFocusUp )
{
	this->nextFocusUp = nextFocusUp;
}

shared_ptr<Component> Component::getNextFocusLeft()
{
	 return nextFocusLeft;
}

void Component::setNextFocusLeft( shared_ptr<Component> nextFocusLeft )
{
	this->nextFocusLeft = nextFocusLeft;
}

shared_ptr<Component> Component::getNextFocusRight()
{
	return nextFocusRight;
}

void Component::setNextFocusRight( shared_ptr<Component> nextFocusRight )
{
	 this->nextFocusRight = nextFocusRight;
}

bool Component::isEnabled()
{
	return enabled;
}

void Component::onEditComplete( shared_ptr<String> text )
{

}

void Component::setEnabled( bool enabled )
{
	this->enabled = enabled;
	shared_ptr<Form> f = getComponentForm();
	if (f.get() != NULL) {
		f->clearFocusVectors();
		repaint();
	}
}

void Component::initCustomStyle( shared_ptr<Style> s )
{
	shared_ptr<Component> cmp = this->shared_from_this();
	s->addStyleListener(static_pointer_cast<StyleListener>(cmp));
	if (s->getBgPainter().get() == NULL) {
		shared_ptr<BGPainter> painter = new BGPainter(cmp);
		s->setBgPainter(painter);
	}
}

void Component::deinitializeCustomStyle( shared_ptr<Style> s )
{
	s->removeStyleListener(static_pointer_cast<StyleListener>(this->shared_from_this()));
}

bool Component::isRTL()
{
	return rtl;
}

void Component::setRTL( bool rtl )
{
	this->rtl = rtl;
}

bool Component::isTactileTouch()
{
	 return tactileTouch;
}

void Component::setTactileTouch( bool tactileTouch )
{
	this->tactileTouch = tactileTouch;
}

void Component::setScrollToVisible( bool b )
{
	scrollToVisible = b;
}

void Component::setLeftRight( bool b )
{
	canLeftRight = b;
}

void Component::setUpDown( bool b )
{
	canUpDown = b;
}

bool Component::getLeftRight()
{
	return canLeftRight;
}

bool Component::getUpDown()
{
	return canUpDown;
}

int Component::getAbsoluteYModified()
{
	int y = getY();
	shared_ptr<Container> parent = getParent();
	if (parent.get() != NULL) {
		y += parent->getAbsoluteYModified();
	}
	return y;

}

bool Component::pointerPressedVerticalScroll( int x,int y )
{
	if (!(isScrollableY() && isScrollVisible()))
		return false;
	int scrollX = this->getX() + this->getWidth() - UIManager::getInstance()->getLookAndFeel()->getVerticalScrollWidth();
	int height = this->getHeight();
	if( x <= scrollX)
		return false;
	if( x > scrollX  ){
		float scrollH = (float)getScrollDimension()->getHeight();
		float offset = (float)(y - this->getAbsoluteYModified());
		int oldScrollY = this->getScrollY();
		int ScrollBarH =  (int) (height *height / scrollH);
		int oldScrollTopY = (int) ((oldScrollY/scrollH)* height);
		if (offset < oldScrollTopY) {	
			float offsetRatio = offset / (float) height;
			float scrollF = offsetRatio * scrollH;
			if (scrollF > scrollH - height || offsetRatio > 0.95)
				scrollF = scrollH - height;
			else if (offsetRatio < 0.05)
				scrollF = 0;
			int scroll = (int) scrollF;
			this->setScrollY(scroll);
			repaint();
		} else if (offset > oldScrollTopY + ScrollBarH) {
			float offsetRatio = (offset - ScrollBarH) / (float) height;
			float scrollF = offsetRatio * scrollH;
			if (scrollF > scrollH - height || offsetRatio > 0.95)
				scrollF = scrollH - height;
			else if (offsetRatio < 0.05)
				scrollF = 0;
			int scroll = (int) scrollF;
			this->setScrollY(scroll);
			repaint();
		}
	}
	return true;

}

void Component::scrollBottom()
{
	if(!this->isScrollableY())
		return;
	int scrollH = getScrollDimension()->getHeight();
	int scroll = scrollH - this->getHeight();
	this->setScrollY(scroll);
}

void Component::scrollTop()
{
	if(!this->isScrollableY())
		return;
	int scroll = 0;
	this->setScrollY(scroll);
}
__GUI_END_NAMESPACE
