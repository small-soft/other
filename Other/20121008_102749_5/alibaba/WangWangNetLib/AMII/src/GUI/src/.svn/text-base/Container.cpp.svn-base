#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

AM_IMPLEMENT_DYNAMIC(Container, Component)

void Container::constructV( shared_ptr<Layout> layout )
{	
//	Component::constructV();
	setUIID(new String(L"Container"));
	this->layout = layout;
	setFocusable(false);
	components = new Vector<shared_ptr<Component> >;
	shared_ptr<LookAndFeel> laf = UIManager::getInstance()->getLookAndFeel();
	setSmoothScrolling(laf->isDefaultSmoothScrolling());
}

Container::~Container( void )
{

}
shared_ptr<Container> Container::shared_from_this()
{
	shared_ptr<Component> cmp = Component::shared_from_this();
	return dynamic_pointer_cast<Container>(cmp);
}
shared_ptr<Layout> Container::getLayout()
{
	return layout;
}

void Container::setLayout( shared_ptr<Layout> layout )
{
	this->layout = layout;
}

void Container::invalidate()
{
	setShouldCalcPreferredSize(true);
}

void Container::setShouldCalcPreferredSize( bool shouldCalcPreferredSize )
{
	Component::setShouldCalcPreferredSize(shouldCalcPreferredSize);
	shouldLayout = shouldCalcPreferredSize;
	if (shouldLayout) {
		int size = components->size();
		for(int iter = 0 ; iter < size ; iter++) {
			shared_ptr<Component> cmp =  components->elementAt(iter);
			Container* ctner = dynamic_cast<Container*>(cmp.get());
			if (ctner!= NULL) {
				ctner->setShouldCalcPreferredSize(shouldCalcPreferredSize);
			}
		}
	}
	shared_ptr<Form> f = getComponentForm();
	if (f.get() != NULL) {
		f->clearFocusVectors();
	}
}

int Container::getLayoutWidth()
{
	if (isScrollableX()) {
		return max(getWidth(), getPreferredW());
	} else {
		shared_ptr<Container> parent = getScrollableParent();
		if (parent.get() != NULL && parent->isScrollableX()) {
			return max(getWidth(), getPreferredW());
		}
		int width = getWidth();
		if (width <= 0) {
			return getPreferredW();
		}
		return width;
	}
}

void Container::applyRTL( bool rtl )
{
	setRTL(rtl);
	int c = getComponentCount();
	for(int iter = 0 ; iter < c ; iter++) {
		shared_ptr<Component> current = getComponentAt(iter);
		Container* ctner = dynamic_cast<Container*>(current.get());
		if(ctner != NULL) {
			ctner->applyRTL(rtl);
		} else {
			current->setRTL(rtl);
		}
	}
}

int Container::getLayoutHeight()
{
	if (isScrollableY()) {
		return max(getHeight(), getPreferredH());
	} else {
		shared_ptr<Container> parent = getScrollableParent();
		if (parent.get() != NULL && parent->isScrollableY()) {
			return max(getHeight(), getPreferredH());
		}
		int height = getHeight();
		if (height <= 1) {
			return getPreferredH();
		}
		return height;
	}
}

shared_ptr<Container> Container::getScrollableParent()
{
	shared_ptr<Container> parent = getParent();
	while (parent.get() != NULL) {
		if (parent->isScrollable()) {
			return parent;
		}
		parent = parent->getParent();
	}
	parent.reset();
	return parent;
}

void Container::addComponent( shared_ptr<Component> cmp )
{	
//	weak_ptr<Container> com = this;

	layout->addLayoutComponent(NULL, cmp, this->shared_from_this());
	insertComponentAt(components->size(), cmp);
}

void Container::addComponent(int constraints, shared_ptr<Component> cmp )
{
//	weak_ptr<Container> com = this;
	layout->addLayoutComponent(constraints, cmp, this->shared_from_this());
	insertComponentAt(components->size(), cmp);
}

void Container::addComponent( int index, int constraints, shared_ptr<Component> cmp )
{
//	weak_ptr<Container> com = this;
	layout->addLayoutComponent(constraints, cmp, this->shared_from_this());
	insertComponentAt(index, cmp);
}

void Container::addComponent(  shared_ptr<Component> cmp, int index)
{
	insertComponentAt(index, cmp);
}
void Container::insertComponentAt( int index, shared_ptr<Component> cmp )
{
	if (cmp->getParent().get() != NULL) {
		return;
	}
	Form *form = dynamic_cast<Form*>(cmp.get());
	if (form!=NULL) {
		return;
	}
//	weak_ptr<Container> com = this;
	cmp->setParent(this->shared_from_this());
	components->insertElementAt(cmp,index);
	setShouldCalcPreferredSize(true);
	if (isInitialized()) {
		cmp->initComponentImpl();
	}
	form = dynamic_cast<Form*>(this->shared_from_this().get());
	if( form == NULL){
		shared_ptr<Form> f = getComponentForm();
		if (f.get() != NULL) {
			f->clearFocusVectors();
		}
	}
}

void Container::replaceAndWait(  shared_ptr<Component> current,  shared_ptr<Component> next,  shared_ptr<Transition> t )
{
	replaceComponents(current, next, t, true);
}

void Container::replace( shared_ptr<Component> current,  shared_ptr<Component> next,  shared_ptr<Transition> t )
{
	 replaceComponents(current, next, t, false);
}

void Container::replace( shared_ptr<Component> current, shared_ptr<Component> next )
{
	shared_ptr<Container> ctner = this->shared_from_this();
	unsigned int index =components->indexOf(current);

	bool currentFocused = false;
	if (current->getComponentForm().get() != NULL) {
		shared_ptr<Component> currentF = current->getComponentForm()->getFocused();
		currentFocused = currentF == current;
		Container *container = dynamic_cast<Container *>(current.get());
		if (!currentFocused && container!= NULL && currentF.get() != NULL )
		{
			if(container->isParentOf(currentF)) 
				currentFocused = true;
		}
	}
	BorderLayout* bordLayout = dynamic_cast<BorderLayout*> (layout.get());
	if (bordLayout != NULL)
	{
		int constraint = layout->getComponentConstraint(current);
		removeComponentImpl(current);
		layout->addLayoutComponent(constraint, next, ctner);
	} else {
		removeComponentImpl(current);
	}
	shared_ptr<Container> container;
	next->setParent(container);
	if (index < 0) {
		index = 0;
	}
	insertComponentAt(index, next);
	if (currentFocused) {
		if (next->isFocusable()) {
			next->requestFocus();
		} else {
			Container *container = dynamic_cast<Container *>(next.get());
			if (container != NULL) {
				container->requestFocusChild();
			}
		}
	}

}
void Container::replaceComponents(  shared_ptr<Component> current,  shared_ptr<Component> next,  shared_ptr<Transition> t, bool wait )
{

	if (!contains(current)) {
		return;
	}
	if (t.get() == NULL || !isVisible() || getComponentForm().get() == NULL) {
		replace(current, next);
		return;
	}

	next->setX(current->getX());
	next->setY(current->getY());
	next->setWidth(current->getWidth());
	next->setHeight(current->getHeight());
//	weak_ptr<Container> com = this;
	next->setParent(this->shared_from_this());
	Container* ctner = dynamic_cast<Container*>(next.get());
	if (ctner !=  NULL) {
		ctner->layoutContainer();
	}

	//const Anim* anim = new Anim(this, current, next, t);

	//// register the transition animation
	//getComponentForm()->registerAnimatedInternal(anim);
	////wait until animation has finished
	//if (wait) {
	//	Display.getInstance().invokeAndBlock(anim);
	//}

}

bool Container::isParentOf( shared_ptr<Component> c )
{
	c = c->getParent();
	if (c.get() == NULL ) {
		Form *form = dynamic_cast<Form *>(c.get());
		if(form != NULL)
			return false;
	}
	return (c.get() == this) || isParentOf(c);
}

bool Container::requestFocusChild()
{
	for (int iter = 0; iter < getComponentCount(); iter++) 
	{
		shared_ptr<Component> c = getComponentAt(iter);
		if (c->isFocusable()) 
		{
			c->requestFocus();
			return true;
		}
		Container *ctner = dynamic_cast<Container *>(c.get());
		if(ctner != NULL)
		{
			ctner->requestFocusChild();
			return true;
		}
	}
	return false;
}

void Container::initComponentImpl()
{
	if (!isInitialized()) {
		Component::initComponentImpl();
	}
	int size = components->size();
	for(int iter = 0 ; iter < size ; iter++) {
		components->elementAt(iter)->initComponentImpl();
	}
}

void Container::removeComponent( shared_ptr<Component> cmp )
{
	 removeComponentImpl(cmp);
}

void Container::removeComponentImpl( shared_ptr<Component> cmp )
{
	shared_ptr<Form> parentForm = cmp->getComponentForm();
	layout->removeLayoutComponent(cmp);
	cmp->deinitializeImpl();
	components->removeElement(cmp);

	shared_ptr<Container> container;
	cmp->setParent(container);

	cmp->setShouldCalcPreferredSize(true);
	if (parentForm.get()!= NULL) {
		if (parentForm->getFocused() == cmp)
		{
			Container* ctner = dynamic_cast<Container*>(cmp.get());
			if(ctner!= NULL && ctner->contains(parentForm->getFocused()))
			{	
				shared_ptr<Component> Component;
				parentForm->setFocused(Component);
			}
		}
		parentForm->clearFocusVectors();
		if (cmp->isSmoothScrolling()) {
			parentForm->deregisterAnimatedInternal(cmp);
		}
	}
	setShouldCalcPreferredSize(true);
}

void Container::deinitializeImpl()
{
	Component::deinitializeImpl();
	int size = components->size();
	for (int iter = 0; iter < size; iter++) {
		 components->elementAt(iter)->deinitializeImpl();
	}
	flushReplace();
}

void Container::flushReplace()
{
	if (cmpTransitions.get() != NULL) {
		int size = cmpTransitions->size();
		for (int iter = 0; iter < size; iter++) {
		//	((Anim) cmpTransitions.elementAt(iter)).destroy();
		}
		cmpTransitions->removeAllElements();
		cmpTransitions.reset();
	}
}

void Container::removeAll()
{
	shared_ptr<Form> parentForm = getComponentForm();
	if (parentForm.get() != NULL) {
		shared_ptr<Component> focus = parentForm->getFocused();
		if (focus.get() != NULL && contains(focus)) {
			shared_ptr<Component> Component;
			parentForm->setFocused(Component);
		}
	}
	int size = components->size();
	shared_ptr<Component> * arr = new shared_ptr<Component>[size];
	components->copyInto(arr);
	for ( int i = 0; i < size; i++) 
	{
		removeComponent(arr[i]);
	}
	delete[] arr;
}

void Container::revalidate()
{
	setShouldCalcPreferredSize(true);
	shared_ptr<Form> root = getComponentForm();

	if (root.get() != NULL) {
		root->layoutContainer();
		root->Component::repaint();
	} else {
		layoutContainer();
		Component::repaint();
	}
}

void Container::paint( shared_ptr<Graphics> g )
{
	layoutContainer();
	g->translate(getX(), getY());
	int size = components->size();
	for (int i = 0; i < size; i++) {
		shared_ptr<Component> cmp = components->elementAt(i);
		cmp->paintInternal(g, false);
	}
	g->translate(-getX(), -getY());
}

void Container::paintIntersecting( shared_ptr<Graphics> g, shared_ptr<Component> cmp, int x, int y, int w, int h, bool above )
{
	if (layout->isOverlapSupported() ) 
	{
		int indexOfComponent =components->indexOf(cmp);
		if(indexOfComponent >=0)
		{
			int startIndex;
			int endIndex;
			if (above)
			{
				startIndex = indexOfComponent + 1;
				endIndex = components->size();
			} else 
			{
				startIndex = 0;
				endIndex = indexOfComponent;
			}

			for (int i = startIndex; i < endIndex; i++) 
			{
				shared_ptr<Component> cmp2 =  components->elementAt(i);
				if(Rectangle::intersects(x, y, w, h,
					cmp2->getAbsoluteX() + cmp2->getScrollX(),
					cmp2->getAbsoluteY() + cmp2->getScrollY(),
					cmp2->getBounds()->getSize()->getWidth(),
					cmp2->getBounds()->getSize()->getHeight()))
				{
						cmp2->paintInternal(g, false);
				}
			}
		}		
	}
}

void Container::layoutContainer()
{
	if (shouldLayout) {
		shouldLayout = false;
		doLayout();
	}
}

void Container::doLayout()
{
	layout->layoutContainer(this->shared_from_this());
	int count = getComponentCount();

	shared_ptr<Component> c;
	shared_ptr<Container> ctner;

	for (int i = 0; i < count; i++) {
		c = getComponentAt(i);
		ctner = dynamic_pointer_cast<Container> (c);
		if (ctner.get() != NULL)
		{
			ctner->doLayout();
		}else{
			c->laidOut();
		}
	}
	laidOut();
}

int Container::getComponentCount()
{
	return components->size();
}

shared_ptr<Component> Container::getComponentAt( int index )
{
	 return  components->elementAt(index);
}

shared_ptr<Component> Container::getComponentAt( int x, int y )
{
	int count = getComponentCount();
	bool overlaps = getLayout()->isOverlapSupported();
	shared_ptr<Component> component;
	for (int i = count - 1; i >= 0; i--) {
		shared_ptr<Component> cmp = getComponentAt(i);
		if (cmp->contains(x, y)) {
			component = cmp;
			if (!overlaps && component->isFocusable()) {
				return component;
			}
			Container *ctner = dynamic_cast<Container *>(cmp.get());
			if (ctner != NULL) {
				component = ctner->getComponentAt(x, y);
			}
			if (!overlaps || component->isFocusable()) {
				return component;
			}
		}
	}
	if (component.get() != NULL){
		return component;
	}
	if (Component::contains(x, y)) {
		return this->shared_from_this();
	}
	return component;

}

int Container::getComponentIndex( shared_ptr<Component> cmp )
{
	return components->indexOf(cmp);
}

bool Container::contains( shared_ptr<Component> cmp )
{
	bool found = false;
	int count = getComponentCount();
	for (int i = 0; i < count; i++) {
		shared_ptr<Component> c = getComponentAt(i);
		if (c == cmp) {
			return true;
		}
		Container *ctner= dynamic_cast<Container *>(c.get());
		if (ctner != NULL) {
			found = ctner->contains(cmp);
			if (found) {
				return true;
			}

		}
	}
	return false;
}

void Container::scrollComponentToVisible( shared_ptr<Component> c )
{	
//	weak_ptr<Container> cnter = this;
	if (isScrollable()) {
		if (c.get() != NULL) {
			shared_ptr<Rectangle> r = c->getVisibleBounds();
			if (c->getParent().get() != NULL) {
				// special case for the first component to allow the user to scroll all the 
				// way to the top
				shared_ptr<Form> f = getComponentForm();
				if (f.get() != NULL && f->getFocusPosition(c) == 0) {
					// support this use case only if the component doesn't explicitly declare visible bounds
					if(r == c->getBounds()) {
						scrollRectToVisible(new Rectangle(0, 0, 
							c->getX() + min(c->getWidth(), getWidth()), 
							c->getY() + min(c->getHeight(), getHeight())), this->shared_from_this());
						return;
					}
				}
			}
			scrollRectToVisible(r->getX(), r->getY(), 
				min(r->getSize()->getWidth(), getWidth()), 
				min(r->getSize()->getHeight(), getHeight()), c);
		}
	}

}

bool Container::moveScrollTowards( int direction, shared_ptr<Component> next )
{

	if (isScrollable()) {
		shared_ptr<Component> current;
		shared_ptr<Form>f = getComponentForm();
		if (f.get() != NULL) {
			current = f->getFocused();
		}

		int position = f->getFocusPosition(current);
		bool edge = false;
		bool currentLarge = false;
		bool scrollOutOfBounds = false;
		//add by jiajing
		bool nextLarge =  (next.get() != NULL && next->getVisibleBounds()->getSize()->getHeight() > getHeight());
		//end
		int x = getScrollX();
		int y = getScrollY();
		int w = getWidth();
		int h = getHeight();

		switch (direction) {
				case Display::GAME_UP:
					y = getScrollY() - scrollIncrement;
					edge = (position == 0);
					currentLarge = (current.get() != NULL && current->getVisibleBounds()->getSize()->getHeight() > getHeight());
					scrollOutOfBounds = y < 0;
					//add by jiajing
					if(scrollOutOfBounds &&  getScrollY()!= 0){
						y =0;
						scrollOutOfBounds = false;
					}
					//end
					break;
				case Display::GAME_DOWN:
					y = getScrollY() + scrollIncrement;
					edge = (position == f->getFocusCount() - 1);
					currentLarge = (current.get() != NULL && current->getVisibleBounds()->getSize()->getHeight() > getHeight());
					scrollOutOfBounds = y > getScrollDimension()->getHeight() - getHeight();
					//add by jiajing
					if(scrollOutOfBounds &&  getScrollY()!= getScrollDimension()->getHeight() - getHeight()){
						y = getScrollDimension()->getHeight() - getHeight();
						scrollOutOfBounds = false;
					}
					//end
					break;
				case Display::GAME_RIGHT:
					x = getScrollX() + scrollIncrement;
					edge = (position == f->getFocusCount() - 1);
					currentLarge = (current.get() != NULL && current->getVisibleBounds()->getSize()->getWidth() > getWidth());
					scrollOutOfBounds = x > getScrollDimension()->getWidth() - getWidth();
					break;
				case Display::GAME_LEFT:
					x = getScrollX() - scrollIncrement;
					edge = (position == 0);
					currentLarge = (current.get() != NULL && current->getVisibleBounds()->getSize()->getWidth() > getWidth());
					scrollOutOfBounds = x < 0;
					break;
		}
		//if the Form doesn't contain a focusable Component simply move the 
		//viewport by pixels
		if(next .get()== NULL){
		//	weak_ptr<Container> cnter = this;
			scrollRectToVisible(x, y, w, h, this->shared_from_this());
			return false;
		}

		bool nextIntersects = Rectangle::intersects(next->getAbsoluteX(),
			next->getAbsoluteY(),
			next->getWidth(),
			next->getHeight(),
			getAbsoluteX() + x,
			getAbsoluteY() + y,
			w,
			h);

		if (nextIntersects && !currentLarge && !edge && !nextLarge) {
			scrollComponentToVisible(next);
			return true;
		} else {
			if (!scrollOutOfBounds) {
			//	weak_ptr<Container> cnter = this;
				scrollRectToVisible(x, y, w, h, this->shared_from_this());
				//if after moving the scroll the current focus is out of the
				//view port and the next focus is in the view port move 
				//the focus
				if (nextIntersects && !Rectangle::intersects(current->getAbsoluteX(),
					current->getAbsoluteY(),
					current->getWidth(),
					current->getHeight(),
					getAbsoluteX() + x,
					getAbsoluteY() + y,
					w,
					h)) {
						return true;
				}
				return false;
			} else {
				//modified by jiajing
				if (this->getComponentForm()->getFocused() != next){
					//end
					scrollComponentToVisible(next);
					return true;
				}
				return false;
			}
		}

	}


	return true;

}

void Container::pointerHover( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y )
{
	if(!isDragActivated()) 
	{
		shared_ptr<Component>c = getComponentAt((*x)[0], (*y)[0]);
		if(c.get() != NULL && c->isFocusable()) 
		{
			c->requestFocus();
		}
	}
	Component::pointerDragged((*x)[0], (*y)[0]);
}

void Container::pointerPressed( int x, int y )
{
	clearDrag();
	setDragActivated(false);
	shared_ptr<Component> cmp = getComponentAt(x, y);
	if (cmp.get() == this) 
	{
		Component::pointerPressed(x, y);
	} 
	else
	{
		if (cmp.get() != NULL) 
		{
			cmp->pointerPressed(x, y);
		}
	}
}

shared_ptr<Dimension> Container::calcPreferredSize()
{
//	weak_ptr<Container> com = this;
	shared_ptr<Dimension> d = layout->getPreferredSize(this->shared_from_this());
	return d;
}

void Container::refreshTheme()
{
	Component::refreshTheme();
	int size = components->size();
	for(int iter = 0 ; iter < size ; iter++) {
		shared_ptr<Component> cmp =  components->elementAt(iter);
		cmp->refreshTheme();
	}
}

bool Container::isScrollableX()
{
	return scrollableX && getScrollDimension()->getWidth() > getWidth();
}

bool Container::isScrollableY()
{
	 return scrollableY && getScrollDimension()->getHeight() > getHeight();
}

void Container::setScrollableX( bool scrollableX )
{
	 this->scrollableX = scrollableX;
}

void Container::setScrollableY( bool scrollableY )
{
	 this->scrollableY = scrollableY;
}

void Container::setScrollable( bool scrollable )
{
	setScrollableX(scrollable);
	setScrollableY(scrollable);
}

void Container::setCellRenderer( bool cellRenderer )
{
	if (isCellRenderer() != cellRenderer) {
		Component::setCellRenderer(cellRenderer);
		int size = getComponentCount();
		for (int iter = 0; iter <size; iter++) {
			getComponentAt(iter)->setCellRenderer(cellRenderer);
		}
	}
}

void Container::setScrollIncrement( int scrollIncrement )
{
	 this->scrollIncrement = scrollIncrement;
}

int Container::getScrollIncrement()
{
	 return scrollIncrement;
}

void Container::repaint( shared_ptr<Component>cmp )
{
	Component::repaint(cmp);
}

shared_ptr<Container> Container::newV(shared_ptr<Layout> layout)
{
	shared_ptr<Container> container = new Container();
	container->constructV(layout);
	return container;
}

Container::Container()
{
	shouldLayout = true;
	scrollableX = false;
	scrollableY = false;
	scrollIncrement = 20;
}

//shared_ptr<Form> Container::getComponentForm()
//{
//	return Component::getComponentForm();
//}
__GUI_END_NAMESPACE
