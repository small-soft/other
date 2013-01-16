
#include "AMGui.h"
__GUI_BEGIN_NAMESPACE

int Form::leftSK = KEY_LEFTSK;
int Form::rightSK = KEY_RIGHTSK;
int Form::rightSK2 = -7;
int Form::backSK = -11;
int Form::clearSK = KEY_CLEARSK;
int Form::backspaceSK = KEY_BACKSPACESK;
bool Form::comboLock = false;

AM_IMPLEMENT_DYNAMIC(Form, Container)

void Form::constructV(void)
{	
	Container::constructV(new BorderLayout());
	init();
}

void Form::constructV( shared_ptr<String> title )
{
    constructV();
	this->title->setText(title);
}

Form::Form( void )
{
	tint = false;
	cyclicFocus = true;
	comboLock = false;
	tintColor = 0;
	tactileTouchDuration = 0;
}

void Form::init()
{
	contentPane = Container::newV(new BorderLayout());
	shared_ptr<String> id = new String(L"Form");
	setUIID(id);
	// forms/dialogs are not visible by default
	setVisible(false);
	shared_ptr<Style> formStyle = getStyle();
	int w = Display::getInstance()->getDisplayWidth() - (formStyle->getMargin(isRTL(), Component::LEFT) + formStyle->getMargin(isRTL(), Component::RIGHT));
	int h = Display::getInstance()->getDisplayHeight() - (formStyle->getMargin(false, Component::TOP) + formStyle->getMargin(false, Component::BOTTOM));

	setWidth(w);
	setHeight(h);
	setPreferredSize(new Dimension(w, h));

	title =  Label::newV(new String(L""), new String(L"Title"));
	//cycle use
	menuBar = MenuBar::newV(this->shared_from_this());

	title->setEndsWith3Points(false);
	Container::addComponent(BorderLayout::NORTH, title);
	Container::addComponent(BorderLayout::CENTER, contentPane);
	Container::addComponent(BorderLayout::SOUTH, menuBar);
	contentPane->setUIID(new String(L"ContentPane"));
	contentPane->setScrollableY(true);
	shared_ptr<LookAndFeel> laf = UIManager::getInstance()->getLookAndFeel();
	initLaf(laf);
	tintColor = laf->getDefaultFormTintColor();

	selectMenuItem = createMenuSelectCommand();
	cancelMenuItem = createMenuCancelCommand();

	// hardcoded, anything else is just pointless...
	formStyle->setBgTransparency(0xFF);

	lock = new Locker();
}
Form::~Form(void)
{

}
shared_ptr<Form> Form::shared_from_this()
{
	shared_ptr<Container> cmp = Container::shared_from_this();
	return dynamic_pointer_cast<Form>(cmp);
}
void Form::setSoftButtonStyle( shared_ptr<Style> s )
{
	   menuBar->setUnSelectedStyle(s);
}

shared_ptr<Style> Form::getSoftButtonStyle()
{
	 return menuBar->getStyle();
}

void Form::hideNotify()
{

}

void Form::showNotify()
{

}

void Form::sizeChangedInternal( int w, int h )
{
	sizeChanged(w, h);
	setSize(new Dimension(w, h));
	setShouldCalcPreferredSize(true);
	doLayout();        
	Component::repaint();
}

void Form::setGlassPane( shared_ptr<Painter> glassPane )
{
	this->glassPane = glassPane;
	Component::repaint();
}

shared_ptr<Painter> Form::getGlassPane()
{
	return glassPane;
}

shared_ptr<Label> Form::getTitleComponent()
{
	 return title;
}

void Form::setTitleComponent( shared_ptr<Label> title )
{
	Container::replace(this->title, title);
	this->title = title;
}

void Form::setTitleComponent( shared_ptr<Label> title, shared_ptr<Transition> t )
{
	Container::replace(this->title, title, t);
	this->title = title;
}

void Form::addKeyListener( int keyCode, shared_ptr<ActionListener> listener )
{
	if (keyListeners.get() == NULL) {
		keyListeners = new ActionListenerMap();
	}
	addKeyListener(keyCode, listener, keyListeners);
}

void Form::addKeyListener( int keyCode, shared_ptr<ActionListener> listener, shared_ptr<ActionListenerMap> keyListeners )
{

	if (keyListeners.get() == NULL) {
		keyListeners = new ActionListenerMap();
	}
//	Integer code = new Integer(keyCode);
	shared_ptr<Vector<shared_ptr<ActionListener> > > vec =  keyListeners->get(keyCode);
	if (vec.get() == NULL) {
		vec = new Vector<shared_ptr<ActionListener> >();
		vec->addElement(listener);
		keyListeners->put(keyCode,vec);
		return;
	}
	if (!vec->contains(listener)) {
		vec->addElement(listener);
	}

}
void Form::removeKeyListener( int keyCode, shared_ptr<ActionListener> listener )
{
	if (keyListeners.get() == NULL) {
		return;
	}
	removeKeyListener(keyCode, listener, keyListeners);
}

void Form::removeKeyListener( int keyCode, shared_ptr<ActionListener> listener, shared_ptr<ActionListenerMap> keyListeners )
{

	if (keyListeners.get() == NULL) {
		return;
	}
//	Integer code = new Integer(keyCode);
	shared_ptr<Vector<shared_ptr<ActionListener> > > vec =  keyListeners->get(keyCode);
	if (vec.get() == NULL) {
		return;
	}
	vec->removeElement(listener);
	if (vec->size() == 0) {
		keyListeners->remove(keyCode);
	}

}
void Form::removeGameKeyListener( int keyCode, shared_ptr<ActionListener> listener )
{
	if (gameKeyListeners.get() == NULL) {
		return;
	}
	removeKeyListener(keyCode, listener, gameKeyListeners);
}

void Form::addGameKeyListener( int keyCode, shared_ptr<ActionListener> listener )
{
	if (gameKeyListeners.get() == NULL) {
		gameKeyListeners = new ActionListenerMap();
	}
	addKeyListener(keyCode, listener, gameKeyListeners);
}

int Form::getSoftButtonCount()
{
	 return menuBar->getSoftButtons()->size();
}

shared_ptr<Button> Form::getSoftButton( int offset )
{
	 return (*menuBar->getSoftButtons())[offset];
}

shared_ptr<Style> Form::getMenuStyle()
{
	 return menuBar->getMenuStyle();
}

shared_ptr<Style> Form::getTitleStyle()
{
	 return title->getStyle();
}

shared_ptr<Form> Form::getPreviousForm()
{
	 return previousForm;
}

void Form::initLaf( shared_ptr<LookAndFeel> laf )
{
	transitionOutAnimator = laf->getDefaultFormTransitionOut();
	transitionInAnimator = laf->getDefaultFormTransitionIn();
}

void Form::clearFocusVectors()
{
	focusDownSequence.reset();
	focusRightSequence.reset();
}

void Form::setDraggedComponent( shared_ptr<Component> dragged )
{
	  this->dragged = dragged;
}

void Form::initFocusRight()
{
	lock->lock();
	if (focusRightSequence.get() == NULL) {
		focusRightSequence = new Vector<shared_ptr<Component> >();
		findAllFocusable(contentPane, focusRightSequence, true);
	}
	lock->unlock();
}

void Form::initFocusDown()
{
	lock->lock();
	if (focusDownSequence.get() == NULL) {
		focusDownSequence = new Vector<shared_ptr<Component> >();
		findAllFocusable(contentPane, focusDownSequence, false);
	}
	lock->unlock();
}

void Form::addSortedComponentRight( shared_ptr<Vector<shared_ptr<Component> > > components, shared_ptr<Component> c )
{

	int componentCount = components->size();
	int componentX = c->getAbsoluteX();

	int bestSpot = 0;
	bool rtl = isRTL();

	// add by qianjiajing
	if (c->getLeftRight() == false)
		return;
	//end
	shared_ptr<Component> scrollableParent = findScrollableAncestor(c);

	// find components in the same row and add the component either at the end
	// of the line or at its start
	for (int iter = 0; iter < componentCount; iter++) {
		shared_ptr<Component> current =  components->elementAt(iter);

		// this component is in the same row...
		shared_ptr<Component> currentScrollParent = findScrollableAncestor(current);
		if (currentScrollParent == scrollableParent) {
			if (isInSameRow(current, c)) {
				int currentX = current->getAbsoluteX();
				if (((!rtl) && (currentX > componentX)) ||
					((rtl) && (currentX < componentX))) {
						continue;
				}
				bestSpot = iter + 1;
				continue;
			}
		} else {
			shared_ptr<Component> tempScrollableParent = scrollableParent;
			if (scrollableParent.get() == NULL) {
				tempScrollableParent = c;
			}
			shared_ptr<Component> tempCurrentScrollParent = currentScrollParent;
			if (currentScrollParent.get() == NULL) {
				tempCurrentScrollParent = current;
			}
			if (((!rtl) && (tempCurrentScrollParent->getAbsoluteX() > tempScrollableParent->getAbsoluteX())) ||
				((rtl) && (tempCurrentScrollParent->getAbsoluteX() < tempScrollableParent->getAbsoluteX()))) {
					continue;
			}
			if (isInSameRow(tempCurrentScrollParent, tempScrollableParent)) {
				bestSpot = iter + 1;
				continue;
			}
		}
		if (current->getAbsoluteY() < c->getAbsoluteY()) {
			bestSpot = iter + 1;
		}
	}

	components->insertElementAt(c, bestSpot);

}

shared_ptr<Component> Form::findScrollableAncestor( shared_ptr<Component> c )
{
	c = c->getParent();
	if (c.get() == NULL || c->isScrollable()) {
		return c;
	}
	return findScrollableAncestor(c);
}

bool Form::isInSameColumn( shared_ptr<Component> source, shared_ptr<Component> dest )
{
	return Rectangle::intersects(source->getAbsoluteX(), source->getAbsoluteY(),
		source->getWidth(), INT_MAX, dest->getAbsoluteX(), dest->getAbsoluteY(),
		dest->getWidth(), dest->getHeight());
}

bool Form::isInSameRow( shared_ptr<Component> source, shared_ptr<Component> dest )
{
	return Rectangle::intersects(source->getAbsoluteX(), source->getAbsoluteY(),
		INT_MAX, source->getHeight(), dest->getAbsoluteX(), dest->getAbsoluteY(),
		dest->getWidth(), dest->getHeight());
}

void Form::addSortedComponent( shared_ptr<Vector<shared_ptr<Component> > > components, shared_ptr<Component> c, bool toTheRight )
{
	if (toTheRight) {
		addSortedComponentRight(components, c);
	} else {
		addSortedComponentDown(components, c);
	}
}

void Form::setDefaultCommand( shared_ptr<Command> defaultCommand )
{
	 this->defaultCommand = defaultCommand;
}

shared_ptr<Command> Form::getDefaultCommand()
{
	if (selectCommand.get() != NULL) {
		return selectCommand;
	}
	return defaultCommand;
}

void Form::setClearCommand( shared_ptr<Command> clearCommand )
{
	this->clearCommand = clearCommand;
}

shared_ptr<Command> Form::getClearCommand()
{
	 return clearCommand;
}

void Form::setBackCommand( shared_ptr<Command> backCommand )
{
	this->backCommand = backCommand;
}

shared_ptr<Command> Form::getBackCommand()
{
	  return backCommand;
}

void Form::findAllFocusable( shared_ptr<Container> c, shared_ptr<Vector<shared_ptr<Component> > > v, bool toTheRight )
{
	int size = c->getComponentCount();
	for (int iter = 0; iter < size; iter++) {
		shared_ptr<Component> current = c->getComponentAt(iter);
		shared_ptr<Container> ctner = dynamic_pointer_cast<Container>(current);
		if (ctner!=NULL) {
			findAllFocusable(ctner, v, toTheRight);
		}
		if (current->isFocusable()) {
			addSortedComponent(v, current, toTheRight);
		}
	}
}

shared_ptr<Container> Form::getContentPane()
{
	 return contentPane;
}

void Form::removeAll()
{
	 contentPane->removeAll();
}

void Form::setBgImage( shared_ptr<Image> bgImage )
{
	 getStyle()->setBgImage(bgImage);
}

void Form::setLayout( shared_ptr<Layout> layout )
{
	contentPane->setLayout(layout);
}

void Form::setTitle( shared_ptr<String> title )
{
	this->title->setText(title);
	if(isInitialized() && this->title->isTickerEnabled()) {
		if(this->title->shouldTickerStart()) {
			this->title->startTicker(UIManager::getInstance()->getLookAndFeel()->getTickerSpeed(), true);
		} else {
			if(this->title->isTickerRunning()) {
				this->title->stopTicker();
			}
		}
	}

}

shared_ptr<String> Form::getTitle()
{
	return title->getText();
}

void Form::addComponent( shared_ptr<Component> cmp )
{
	 contentPane->addComponent(cmp);
}

void Form::addComponent( int constraints, shared_ptr<Component> cmp )
{
	 contentPane->addComponent(constraints, cmp);
}

void Form::addComponent( int index, int constraints, shared_ptr<Component> cmp )
{
	  contentPane->addComponent(index, constraints, cmp);
}

void Form::addComponent( shared_ptr<Component> cmp, int index )
{
	contentPane->addComponent( cmp,index);
}

void Form::replace( shared_ptr<Component> current, shared_ptr<Component> next, shared_ptr<Transition> t )
{
	 contentPane->replace(current, next, t);
}

void Form::replaceAndWait( shared_ptr<Component> current, shared_ptr<Component> next, shared_ptr<Transition> t )
{
	  contentPane->replaceAndWait(current, next, t);
}

void Form::removeComponent( shared_ptr<Component> cmp )
{
	contentPane->removeComponent(cmp);
}

void Form::registerMediaComponent( shared_ptr<Component> mediaCmp )
{
	if (mediaComponents.get() == NULL) {
		mediaComponents = new Vector<shared_ptr<Component> >();
	}
	if (!mediaComponents->contains(mediaCmp)) {
		mediaComponents->addElement(mediaCmp);
	}
}

bool Form::hasMedia()
{
	return mediaComponents.get() != NULL && mediaComponents->size() > 0;
}

void Form::deregisterMediaComponent( shared_ptr<Component> mediaCmp )
{
	  mediaComponents->removeElement(mediaCmp);
}

void Form::registerAnimated( shared_ptr<Animation> cmp )
{
	if (animatableComponents.get() == NULL) {
		animatableComponents = new Vector<shared_ptr<Animation> >();
	}
	if (!animatableComponents->contains(cmp)) {
		animatableComponents->addElement(cmp);
	}
	Display::getInstance()->notifyDisplay();
}

void Form::registerAnimatedInternal( shared_ptr<Animation> cmp )
{
	if (internalAnimatableComponents.get() == NULL) {
		internalAnimatableComponents = new Vector<shared_ptr<Animation> >();
	}
	if (!internalAnimatableComponents->contains(cmp)) {
		internalAnimatableComponents->addElement(cmp);
	}
	Display::getInstance()->notifyDisplay();
}

void Form::deregisterAnimatedInternal( shared_ptr<Animation> cmp )
{
	if (internalAnimatableComponents.get() != NULL) {
		internalAnimatableComponents->removeElement(cmp);
	}
}

void Form::deregisterAnimated( shared_ptr<Animation> cmp )
{
	if (animatableComponents.get() != NULL) {
		animatableComponents->removeElement(cmp);
	}
}

int Form::getFocusPosition( shared_ptr<Component> c )
{
	initFocusDown();
	return focusDownSequence->indexOf(c);
}

int Form::getFocusCount()
{
	initFocusDown();
	return focusDownSequence->size();
}

void Form::repaintAnimations()
{
	if (animatableComponents.get() != NULL) {
		shared_ptr<Vector<shared_ptr<Animation> > > notIn;
		loopAnimations(animatableComponents, notIn);
	}
	if (internalAnimatableComponents.get() != NULL) {
		loopAnimations(internalAnimatableComponents, animatableComponents);
	}

}

void Form::loopAnimations( shared_ptr<Vector<shared_ptr<Animation> > > v, shared_ptr<Vector<shared_ptr<Animation> > > notIn )
{
	// we don't save size() in a varible since the animate method may deregister
	// the animation thus invalidating the size
	for (int iter = 0; iter < v->size(); iter++) {
		shared_ptr<Animation> c =  v->elementAt(iter);
		if(c.get() == NULL || notIn.get() != NULL && notIn->contains(c)) {
			continue;
		}
		if (c->animate()) {
			Component *cmp = dynamic_cast<Component*>(c.get());
			if (cmp != NULL) {
				shared_ptr<Rectangle> rect = cmp->getDirtyRegion();
				if (rect.get() != NULL) {
					shared_ptr<Dimension> d = rect->getSize();

					// this probably can't happen but we got a really weird partial stack trace to this
					// method and this check doesn't hurt
					if(d.get() != NULL) {
						cmp->repaint(rect->getX(), rect->getY(), d->getWidth(), d->getHeight());
					}
				} else {
					cmp->repaint();
				}
			} else {
				Display::getInstance()->repaint(c);
			}
		}
	}

}

bool Form::hasAnimations()
{
	return (animatableComponents.get() != NULL && animatableComponents->size() > 0)
		|| (internalAnimatableComponents.get() != NULL && internalAnimatableComponents->size() > 0);

}

void Form::refreshTheme()
{
	// when changing the theme when a title/menu bar is not visible the refresh
	// won't apply to them. We need to protect against this occurance.
	if (menuBar.get() != NULL) {
		menuBar->refreshTheme();
	}
	if (title.get() != NULL) {
		title->refreshTheme();
	}
	Container::refreshTheme();

}

void Form::paintBackground( shared_ptr<Graphics> g )
{
	Container::paintBackground(g);
}

shared_ptr<Transition> Form::getTransitionInAnimator()
{
	return transitionInAnimator;
}

void Form::setTransitionInAnimator( shared_ptr<Transition> transitionInAnimator )
{
	this->transitionInAnimator = transitionInAnimator;
}

shared_ptr<Transition> Form::getTransitionOutAnimator()
{
	  return transitionOutAnimator;
}

void Form::setTransitionOutAnimator( shared_ptr<Transition> transitionOutAnimator )
{
	this->transitionOutAnimator = transitionOutAnimator;
}

void Form::addCommandListener( shared_ptr<ActionListener> l )
{
	if(commandListener.get() == NULL) {
		commandListener = new EventDispatcher<ActionListener>();
	}
	commandListener->addListener(l);
}

void Form::removeCommandListener( shared_ptr<ActionListener> l )
{
	 commandListener->removeListener(l);
}

void Form::actionCommand( shared_ptr<Command> cmd )
{

}

void Form::dispatchCommand( shared_ptr<Command> cmd, shared_ptr<ActionEvent> ev )
{
	cmd->actionPerformed(ev);
	if(!ev->isConsumed()) {
		actionCommandImpl(cmd, ev);
	}

}

void Form::actionCommandImpl( shared_ptr<Command> cmd )
{
	shared_ptr<ActionEvent> tmp = new ActionEvent(cmd);
	actionCommandImpl(cmd, tmp);
}

void Form::actionCommandImpl( shared_ptr<Command> cmd, shared_ptr<ActionEvent> ev )
{
	if (cmd.get() == NULL) {
		return;
	}

	if(comboLock) {
		if(cmd == cancelMenuItem) {
			actionCommand(cmd);
			return;
		}
		shared_ptr<Component> c = getFocused();
		if (c.get() != NULL) {
			c->fireClicked();
		}
		return;
	}
	if (cmd != selectCommand) {
		if (commandListener.get() != NULL) {
			commandListener->fireActionEvent(ev);
			if(ev->isConsumed()) {
				return;
			}
		}
		actionCommand(cmd);
	} else {
		shared_ptr<Component> c = getFocused();
		if (c.get() != NULL) {
			c->fireClicked();
		}
	}

}

void Form::initFocused()
{
	if (focused.get() == NULL) {
		setFocused(findFirstFocusable(contentPane));
		layoutContainer();
		initFocusDown();
		if(focusDownSequence.get() == NULL) {
			initFocusDown();
			if (focusDownSequence->size() > 0) {
				setFocused((shared_ptr<Component>) focusDownSequence->elementAt(0));
			}
		} else {
			if (focusDownSequence->size() > 0) {
				setFocused((shared_ptr<Component>) focusDownSequence->elementAt(0));
			}
		}
	}

}

void Form::show()
{
	 show(false);
}

void Form::show( bool reverse )
{

	if (transitionOutAnimator.get() == NULL && transitionInAnimator.get() == NULL) {
		initLaf(UIManager::getInstance()->getLookAndFeel());
	}
	initFocused();
	onShow();
	tint = false;
	//to check
//	weak_ptr<Form> f = this;
	Display::getInstance()->setCurrent(this->shared_from_this(), reverse);

}
void Form::showBack()
{
	 show(true);
}

void Form::initComponentImpl()
{
	Container::initComponentImpl();
	tactileTouchDuration = UIManager::getInstance()->getLookAndFeel()->getTactileTouchDuration();
	if(title->getText().get() != NULL && title->shouldTickerStart()) {
		title->startTicker(UIManager::getInstance()->getLookAndFeel()->getTickerSpeed(), true);
	}

}

void Form::setSmoothScrolling( bool smoothScrolling )
{
	// invoked by the constructor for component
	if (contentPane.get() != NULL) {
		contentPane->setSmoothScrolling(smoothScrolling);
	}

}

bool Form::isSmoothScrolling()
{
	return contentPane->isSmoothScrolling();
}

int Form::getScrollAnimationSpeed()
{
	  return contentPane->getScrollAnimationSpeed();
}

void Form::setScrollAnimationSpeed( int animationSpeed )
{
	 contentPane->setScrollAnimationSpeed(animationSpeed);
}

void Form::onShow()
{

}

void Form::onShowCompleted()
{

}

void Form::showModal( int top, int bottom, int left, int right, bool includeTitle, bool modal, bool reverse )
{
	Display::getInstance()->flushEdt();
	if (previousForm.get() == NULL)
	{
		previousForm = Display::getInstance()->getCurrent();
		// special case for application opening with a dialog before any form is shown
		if (previousForm.get() == NULL)
		{
			previousForm = Form::newV();
			previousForm->show();
		} else
		{
			shared_ptr<Dialog> previousDialog = dynamic_pointer_cast<Dialog>(previousForm);
			if( previousDialog.get() != NULL )
			{
				if(previousDialog->isDisposed())
				{
					previousForm = Display::getInstance()->getCurrentUpcoming();
				}
			}
		}
		// not support alfa fillrect
		//previousForm->tint = true;
		previousForm->tint = false;
	}
	shared_ptr<Painter> p = getStyle()->getBgPainter();
	if (top > 0 || bottom > 0 || left > 0 || right > 0)
	{
		shared_ptr<Style> titleStyle = title->getStyle();
		shared_ptr<Style> contentStyle = contentPane->getUnselectedStyle();
		if (includeTitle)
		{
			titleStyle->setMargin(Component::TOP, top, true);
			titleStyle->setMargin(Component::BOTTOM, 0, true);
			titleStyle->setMargin(Component::LEFT, left, true);
			titleStyle->setMargin(Component::RIGHT, right, true);

			contentStyle->setMargin(Component::TOP, 0, true);
			contentStyle->setMargin(Component::BOTTOM, bottom, true);
			contentStyle->setMargin(Component::LEFT, left, true);
			contentStyle->setMargin(Component::RIGHT, right, true);
		} else
		{
			titleStyle->setMargin(Component::TOP, 0, true);
			titleStyle->setMargin(Component::BOTTOM, 0, true);
			titleStyle->setMargin(Component::LEFT, 0, true);
			titleStyle->setMargin(Component::RIGHT, 0, true);

			contentStyle->setMargin(Component::TOP, top, true);
			contentStyle->setMargin(Component::BOTTOM, bottom, true);
			contentStyle->setMargin(Component::LEFT, left, true);
			contentStyle->setMargin(Component::RIGHT, right, true);
		}

		shared_ptr<BGPainter> bgP = dynamic_pointer_cast<BGPainter>(p);
		if (bgP.get() != NULL && bgP->getPreviousForm().get() != NULL)
		{
			//  ((BGPainter) p).setPreviousForm(previousForm);
			// modified by qianjiajing
			shared_ptr<Dialog> currentDialog = dynamic_pointer_cast<Dialog>(this->shared_from_this());
			if (currentDialog.get() != NULL && currentDialog->isPaintBG())
			{
				previousForm->tint = currentDialog->getPreFormTint();
				bgP->setPreviousForm(previousForm);
				bgP->setBgRect(currentDialog->getBGRect());
				currentDialog->setPaintBG(false);
			}
			//end
			bgP->setParent(this->shared_from_this());
		} else
		{
			shared_ptr<BGPainter> b = new BGPainter(this->shared_from_this(), p);
			b->setIgnorCoordinates(true);
			getStyle()->setBgPainter(b);

			// modified by qianjiajing
			shared_ptr<Dialog> currentDialog = dynamic_pointer_cast<Dialog>(this->shared_from_this());
			if (currentDialog.get() != NULL && currentDialog->isPaintBG())
			{
				previousForm->tint = currentDialog->getPreFormTint();
				b->setPreviousForm(previousForm);
				b->setBgRect(currentDialog->getBGRect());
				currentDialog->setPaintBG(false);
			}
			//end
			//  b.setPreviousForm(previousForm);
		}
		revalidate();
	}

	initFocused();
	if (getTransitionOutAnimator().get() == NULL && getTransitionInAnimator().get() == NULL)
	{
		initLaf(UIManager::getInstance()->getLookAndFeel());
	}

	initComponentImpl();
	Display::getInstance()->setCurrent(this->shared_from_this(), reverse);
	onShow();

	if (modal)
	{
		// called to display a dialog and wait for modality  
		Display::getInstance()->invokeAndBlock(new RunnableWrapper(this->shared_from_this(), p, reverse));

		// if the virtual keyboard was opend by the dialog close it
		if(Display::getInstance()->isVirtualKeyboardShowingSupported())
		{
			Display::getInstance()->setShowVirtualKeyboard(false);
		}
	}
}

void Form::showModal( bool reverse )
{
	 showDialog(true, reverse);
}

void Form::showDialog( bool modal, bool reverse )
{
	int h = Display::getInstance()->getDisplayHeight() - menuBar->getPreferredH() - title->getPreferredH();
	int w = Display::getInstance()->getDisplayWidth();
	int topSpace = h / 100 * 20;
	int bottomSpace = h / 100 * 10;
	int sideSpace = w / 100 * 20;
	showModal(topSpace, bottomSpace, sideSpace, sideSpace, true, modal, reverse);

}

void Form::dispose()
{
	 disposeImpl();
}

bool Form::isDisposed()
{
	return false;;
}

void Form::disposeImpl()
{
	if (previousForm.get() != NULL) {
		previousForm->tint = false;
		
		Dialog * dlg = dynamic_cast<Dialog *>(previousForm.get());
		if ( dlg!=NULL ) {
			if (!dlg->isDisposed()) {
				Display::getInstance()->setCurrent(previousForm, false);
			}
		} else {
			Display::getInstance()->setCurrent(previousForm, false);
		}

		// enable GC to cleanup the previous form if no longer referenced
		previousForm.reset();
	}

}

bool Form::isMenu()
{
	 return false;
}

void Form::repaint( shared_ptr<Component> cmp )
{
	if (isVisible()) {
		Display::getInstance()->repaint(cmp);
	}

}

shared_ptr<Form> Form::getComponentForm()
{
	return this->shared_from_this();
}

void Form::restoreMenu()
{
	if (menuBar->getParent().get() == NULL) {
		Container::addComponent(BorderLayout::SOUTH, menuBar);
	}
}

void Form::setFocused( shared_ptr<Component> focused )
{
	if (this->focused == focused && focused.get() != NULL) {
		this->focused->repaint();
		return;
	}
	shared_ptr<Component> oldFocus = this->focused;
	this->focused = focused;
	bool triggerRevalidate = false;
	if (oldFocus.get() != NULL) {
		triggerRevalidate = changeFocusState(oldFocus, false);
		//if we need to revalidate no need to repaint the Component, it will
		//be painted from the Form
		if (!triggerRevalidate && oldFocus->getParent().get() != NULL) {
			oldFocus->repaint();
		}
	}
	// a listener might trigger a focus change event essentially
	// invalidating focus so we shouldn't break that 
	if (focused.get() != NULL && this->focused == focused) {
		triggerRevalidate = changeFocusState(focused, true) || triggerRevalidate;
		//if we need to revalidate no need to repaint the Component, it will
		//be painted from the Form
		if(!triggerRevalidate){
			focused->repaint();
		}
	}
	if(triggerRevalidate){
		revalidate();
	}

}

bool Form::changeFocusState( shared_ptr<Component> cmp, bool gained )
{

	bool trigger = false;
	shared_ptr<Style> selected = cmp->getSelectedStyle();
	shared_ptr<Style> unselected = cmp->getUnselectedStyle();
	//if selected style is different then unselected style there is a good 
	//chance we need to trigger a revalidate
	if( selected->getFont()!=unselected->getFont() || 
		selected->getPadding(false, Component::TOP) != unselected->getPadding(false, Component::TOP) ||
		selected->getPadding(false, Component::BOTTOM) != unselected->getPadding(false, Component::BOTTOM) ||
		selected->getPadding(isRTL(), Component::RIGHT) != unselected->getPadding(isRTL(), Component::RIGHT) ||
		selected->getPadding(isRTL(), Component::LEFT) != unselected->getPadding(isRTL(), Component::LEFT) ||
		selected->getMargin(false, Component::TOP) != unselected->getMargin(false, Component::TOP) ||
		selected->getMargin(false, Component::BOTTOM) != unselected->getMargin(false, Component::BOTTOM) ||
		selected->getMargin(isRTL(), Component::RIGHT) != unselected->getMargin(isRTL(), Component::RIGHT) ||
		selected->getMargin(isRTL(), Component::LEFT) != unselected->getMargin(isRTL(), Component::LEFT)){
			trigger = true;
	}
	int prefW = 0;
	int prefH = 0;
	if(trigger){
		shared_ptr<Dimension> d = cmp->getPreferredSize();
		prefW = d->getWidth();
		prefH = d->getHeight();
	}            

	if (gained) {
		cmp->setFocus(true);
		cmp->fireFocusGained();
		fireFocusGained(cmp);
	} else {
		cmp->setFocus(false);
		cmp->fireFocusLost();
		fireFocusLost(cmp);
	}
	//if the styles are different there is a chance the preffered size is 
	//still the same therefore make sure there is a real need to preform 
	//a revalidate
	if(trigger){
		cmp->setShouldCalcPreferredSize(true);
		shared_ptr<Dimension> d = cmp->getPreferredSize();
		if(prefW != d->getWidth() || prefH != d->getHeight()){
			cmp->setShouldCalcPreferredSize(false);
			trigger = false;
		}
	}            

	return trigger;

}

shared_ptr<Component> Form::findFirstFocusable( shared_ptr<Container> c )
{
	int size = c->getComponentCount();
	shared_ptr<Component> cmp;
	for (int iter = 0; iter < size; iter++) {
		shared_ptr<Component> current = c->getComponentAt(iter);
		if(current->isFocusable()){
			return current;
		}
		shared_ptr<Container> ctner = dynamic_pointer_cast<Container>(current);
		if (ctner.get() != NULL) {
			shared_ptr<Container> container = ctner;
			cmp = findFirstFocusable(container);
			if(cmp.get() != NULL){
				return cmp;
			}
		}
	}        
	return cmp;
}

shared_ptr<Component> Form::getFocused()
{
	  return focused;
}

void Form::longKeyPress( int keyCode )
{
	if (focused.get() != NULL) {
		if (focused->getComponentForm().get() == this) {
			focused->longKeyPress(keyCode);
		}
	}
}

void Form::longPointerPress( int x, int y )
{
	if (focused.get() != NULL && focused->contains(x, y)) {
		if (focused->getComponentForm().get() == this) {
			focused->longPointerPress(x, y);
		}
	}
}

void Form::keyPressed( int keyCode )
{
	int game = Display::getInstance()->getGameAction(keyCode);
	if (keyCode == leftSK || (keyCode == rightSK || keyCode == rightSK2) || keyCode == backSK || 
		(keyCode == clearSK && clearCommand.get() != NULL) ||
		(keyCode == backspaceSK && clearCommand.get() != NULL) ||
		(Display::getInstance()->isThirdSoftButton() && game == Display::GAME_FIRE)) {
			menuBar->keyPressed(keyCode);
			return;
	}

	//Component focused = focusManager.getFocused();
	if (focused.get() != NULL) {
		focused->keyPressed(keyCode);
		if(focused.get() == NULL) {
			initFocused();
			return;
		}
		if (focused->handlesInput()) {
			return;
		}
		if (focused->getComponentForm().get() == this) {
			if (focused.get() != NULL && focused->handlesInput()) {
				return;
			}
			//if the arrow keys have been pressed update the focus.
			updateFocus(Display::getInstance()->getGameAction(keyCode));
		} else {
			initFocused();
		}
	} else {
		initFocused();
		if(focused.get() == NULL) {
			shared_ptr<Component> cmp;
			contentPane->moveScrollTowards(Display::getInstance()->getGameAction(keyCode), cmp);
			return;
		}
	}


}

shared_ptr<Layout> Form::getLayout()
{
	 return contentPane->getLayout();
}

void Form::keyReleased( int keyCode )
{
	int game = Display::getInstance()->getGameAction(keyCode);
	if (keyCode == leftSK || (keyCode == rightSK || keyCode == rightSK2) || keyCode == backSK ||
		(keyCode == clearSK && clearCommand.get() != NULL) ||
		(keyCode == backspaceSK && clearCommand.get() != NULL) ||
		(Display::getInstance()->isThirdSoftButton() && game == Display::GAME_FIRE)) {
			menuBar->keyReleased(keyCode);
			return;
	}

	//Component focused = focusManager.getFocused();
	if (focused.get() != NULL) {
		if (focused->getComponentForm().get() == this) {
			focused->keyReleased(keyCode);
		}
	}

	// prevent the default action from stealing the behavior from the popup/combo box...
	if (game == Display::GAME_FIRE) {
		shared_ptr<Command> defaultCmd = getDefaultCommand();
		if (defaultCmd.get() != NULL) {
			defaultCmd->actionPerformed(new ActionEvent(defaultCmd, keyCode));
			actionCommandImpl(defaultCmd);
		}
	}
	fireKeyEvent(keyListeners, keyCode);
	fireKeyEvent(gameKeyListeners, game);

}

void Form::fireKeyEvent(shared_ptr<ActionListenerMap> keyListeners, int keyCode )
{
	if (keyListeners.get() != NULL) {
		shared_ptr<Vector<shared_ptr<ActionListener> > > listeners =  keyListeners->get(keyCode);
		if (listeners.get() != NULL) {
			shared_ptr<Object> object = dynamic_pointer_cast<Object>(this->shared_from_this());
			shared_ptr<ActionEvent> evt = new ActionEvent(object, keyCode);
			for (int iter = 0; iter < listeners->size(); iter++) {
				listeners->elementAt(iter)->actionPerformed(evt);
				if (evt->isConsumed()) {
					return;
				}
			}
		}
	}

}
void Form::keyRepeated( int keyCode )
{
	if (focused.get() != NULL) {
		focused->keyRepeated(keyCode);

		int game = Display::getInstance()->getGameAction(keyCode);
		// this has issues in the WTK
		if (!focused->handlesInput() && 
			(game == Display::GAME_DOWN || game == Display::GAME_UP || game == Display::GAME_LEFT || game == Display::GAME_RIGHT)) {
				keyPressed(keyCode);
				keyReleased(keyCode);
		}
	} else {
		keyPressed(keyCode);
		keyReleased(keyCode);
	}

}

void Form::tactileTouchVibe( shared_ptr<Component> cmp )
{
	if(tactileTouchDuration > 0 && cmp->isTactileTouch()) {
		Display::getInstance()->vibrate(tactileTouchDuration);
	}

}

void Form::pointerPressed( int x, int y )
{
//	weak_ptr<Form> fThis = this;
	if(pointerPressedListeners.get() != NULL) {
		shared_ptr<ActionEvent> event = new ActionEvent(this->shared_from_this(), x, y);
		pointerPressedListeners->fireActionEvent(event);
	}
	//if there is no popup on the screen an click is relevant to the menu bar.
	if (menuBar->Component::contains(x, y)) {
		shared_ptr<Component> cmp = menuBar->getComponentAt(x, y);
		if (cmp.get() != NULL) {
			cmp->pointerPressed(x, y);
			tactileTouchVibe(cmp);
		}
		return;
	}

	shared_ptr<Component> cmp = contentPane->getComponentAt(x, y);
	if (cmp.get() != NULL && cmp->isFocusable()) {
		setFocused(cmp);
		//add by jiajing
		if(cmp->pointerPressedVerticalScroll(x, y) == false){
			//end
			cmp->pointerPressed(x, y);
			tactileTouchVibe(cmp);
		}
	}
}

void Form::addPointerPressedListener( shared_ptr<ActionListener> l )
{
	if(pointerPressedListeners.get() == NULL) {
		pointerPressedListeners = new EventDispatcher<ActionListener>();
	}
	pointerPressedListeners->addListener(l);

}

void Form::removePointerPressedListener( shared_ptr<ActionListener> l )
{
	if(pointerPressedListeners.get() != NULL) {
		pointerPressedListeners->removeListener(l);
	}

}

void Form::addPointerReleasedListener( shared_ptr<ActionListener> l )
{
	if(pointerReleasedListeners.get() == NULL) {
		pointerReleasedListeners = new EventDispatcher<ActionListener>();
	}
	pointerReleasedListeners->addListener(l);

}

void Form::removePointerReleasedListener( shared_ptr<ActionListener> l )
{
	if(pointerReleasedListeners.get() != NULL) {
		pointerReleasedListeners->removeListener(l);
	}

}

void Form::addPointerDraggedListener( shared_ptr<ActionListener> l )
{
	if(pointerDraggedListeners.get() == NULL) {
		pointerDraggedListeners = new EventDispatcher<ActionListener>();
	}
	pointerDraggedListeners->addListener(l);

}

void Form::removePointerDraggedListener( shared_ptr<ActionListener> l )
{
	if(pointerDraggedListeners.get() != NULL) {
		pointerDraggedListeners->removeListener(l);
	}

}

void Form::pointerDragged( int x, int y )
{
//	weak_ptr<Form> fThis = this;
	if(pointerDraggedListeners.get() != NULL) 
	{
		pointerDraggedListeners->fireActionEvent(new ActionEvent(this->shared_from_this(), x, y));
	}

	if (dragged.get() != NULL) 
	{
		dragged->pointerDragged(x, y);
		return;
	}

	shared_ptr<Component> cmp = contentPane->getComponentAt(x, y);
	if (cmp.get() != NULL) 
	{
		if (cmp->isFocusable()) 
		{
			setFocused(cmp);
		}
		cmp->pointerDragged(x, y);
		cmp->repaint();
	}
}

void Form::pointerHoverReleased( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y )
{
	shared_ptr<Component> cmp = contentPane->getComponentAt((*x)[0], (*y)[0]);
	if (cmp.get() != NULL) 
	{
		if (cmp->isFocusable()) 
		{
			setFocused(cmp);
		}
		cmp->pointerHoverReleased(x, y);
		cmp->repaint();
	}
}

void Form::pointerHover( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y )
{
	shared_ptr<Component> cmp = contentPane->getComponentAt((*x)[0], (*y)[0]);
	if (cmp.get() != NULL) 
	{
		if (cmp->isFocusable()) 
		{
			setFocused(cmp);
		}
		cmp->pointerHover(x, y);
		cmp->repaint();
	}
}

bool Form::isSingleFocusMode()
{
	initFocusDown();
	return focusDownSequence->size() == 1;
}

void Form::pointerReleased( int x, int y )
{
	//weak_ptr<Form> fThis = this;
	if(pointerReleasedListeners.get() != NULL) {
		pointerReleasedListeners->fireActionEvent(new ActionEvent(this->shared_from_this(), x, y));
	}
	if (dragged.get() == NULL) {
		//if the pointer was released on the menu invoke the appropriate
		//soft button.
		if (menuBar->Component::contains(x, y)) {
			shared_ptr<Component> cmp = menuBar->getComponentAt(x, y);
			if (cmp.get() != NULL) {
				cmp->pointerReleased(x, y);
			}
			return;
		}

		shared_ptr<Component> cmp = contentPane->getComponentAt(x, y);
		if (cmp.get() != NULL) {
			cmp->pointerReleased(x, y);
			if (cmp->isFocusable()) {
				setFocused(cmp);
			}
		}
	} else {
		dragged->pointerReleased(x, y);
		dragged.reset();
	}

}

void Form::setScrollableY( bool scrollableY )
{
	getContentPane()->setScrollableY(scrollableY);
}

void Form::setScrollableX( bool scrollableX )
{
	getContentPane()->setScrollableX(scrollableX);
}

int Form::getComponentIndex( shared_ptr<Component> cmp )
{
	return getContentPane()->getComponentIndex(cmp);
}

void Form::addCommand( shared_ptr<Command> cmd, int offset )
{
	 menuBar->addCommand(cmd, offset);
}

void Form::addCommand( shared_ptr<Command> cmd )
{
	menuBar->addCommand(cmd);
}
int Form::getCommandCount()
{
	 return menuBar->getCommandCount();
}

shared_ptr<Command> Form::getCommand( int index )
{
	return menuBar->getCommand(index);
}

void Form::removeCommand( shared_ptr<Command> cmd )
{
	menuBar->removeCommand(cmd);
}

void Form::setCyclicFocus( bool cyclicFocus )
{
	this->cyclicFocus = cyclicFocus;
}

bool Form::isCyclicFocus()
{
	 return cyclicFocus;
}

void Form::updateFocus( int gameAction )
{
	shared_ptr<Component> focused = getFocused();
	switch (gameAction) {
			case Display::GAME_DOWN: {
				shared_ptr<Component> down = focused->getNextFocusDown();
				if ( down.get() != NULL && down->getComponentForm().get() == this) {
					focused = down;
				} else {
					initFocusDown();
					int i = focusDownSequence->indexOf(focused) + 1;
					if (focusDownSequence->size() > 0) {
						if (i == focusDownSequence->size()) {
							if (cyclicFocus) {
								i = 0;
							} else {
								i = focusDownSequence->size() - 1;
							}
						}
						focused =  focusDownSequence->elementAt(i);
					}
				}
				break;
									}
			case Display::GAME_UP: {
				shared_ptr<Component> up = focused->getNextFocusUp();
				if (up.get() != NULL && up->getComponentForm().get() == this) {
					focused = up;
				} else {
					initFocusDown();
					if (focusDownSequence->size() > 0) {
						int i = focusDownSequence->indexOf(focused) - 1;
						if (i < 0) {
							if (cyclicFocus) {
								i = focusDownSequence->size() - 1;
							} else {
								i = 0;
							}
						}
						focused = focusDownSequence->elementAt(i);
					}
				}
				break;
								  }
			case Display::GAME_RIGHT: {
				shared_ptr<Component> right = focused->getNextFocusRight();
				if (right.get() != NULL && right->getComponentForm().get() == this) {
					focused = right;
				} else {
					initFocusRight();
					if (focusRightSequence->size() > 0) {
						int i = focusRightSequence->indexOf(focused) + 1;
						if (i == focusRightSequence->size()) {
							if (cyclicFocus) {
								i = 0;
							} else {
								i = focusRightSequence->size() - 1;
							}
						}
						focused =  focusRightSequence->elementAt(i);
					}
				}
				break;
									 }
			case Display::GAME_LEFT: {
				shared_ptr<Component> left = focused->getNextFocusLeft();
				if (left.get() != NULL && left->getComponentForm().get() == this) {
					focused = left;
				} else {
					initFocusRight();
					if (focusRightSequence->size() > 0) {
						int i = focusRightSequence->indexOf(focused) - 1;
						if (i < 0) {
							if (cyclicFocus) {
								i = focusRightSequence->size() - 1;
							} else {
								i = 0;
							}
						}
						focused =  focusRightSequence->elementAt(i);
					}
				}
				break;
			}
			default:
				return;
	}

	//if focused is now visible we need to give it the focus.
	{
		if (moveScrollTowards(gameAction, focused)) {
			setFocused(focused);
		}
	}

}

bool Form::moveScrollTowards( int direction, shared_ptr<Component> c )
{
	shared_ptr<Container> parent = c->getParent();
	while (parent.get() != NULL) {
		if (parent->isScrollable()) {
			return parent->moveScrollTowards(direction, c);
		}
		parent = parent->getParent();
	}
	return true;

}

void Form::scrollComponentToVisible( shared_ptr<Component> c )
{
	initFocused();
	shared_ptr<Container> parent = c->getParent();
	while (parent.get() != NULL) {
		if (parent->isScrollable()) {
			parent->scrollComponentToVisible(c);
			return;
		}
		parent = parent->getParent();
	}

}

void Form::setMenuCellRenderer( shared_ptr<ListCellRenderer> menuCellRenderer )
{
	  menuBar->setMenuCellRenderer(menuCellRenderer);
}

void Form::removeAllCommands()
{
	 menuBar->removeAllCommands();
}

void Form::requestFocus( shared_ptr<Component> cmp )
{
	if (cmp->isFocusable() && contains(cmp)) {
		scrollComponentToVisible(cmp);
		setFocused(cmp);
	}

}

shared_ptr<Command> Form::createSelectCommand()
{
	return new Command(UIManager::getInstance()->localize(L"select", L"Select"));
}

shared_ptr<Command> Form::createMenuSelectCommand()
{
	shared_ptr<LookAndFeel> lf = UIManager::getInstance()->getLookAndFeel();
	shared_ptr<Image> icon;
	if(lf->getMenuIcons()->size() > 0){
		icon = (*lf->getMenuIcons())[0];
	}
	shared_ptr<Command> ret = new Command(UIManager::getInstance()->localize(L"select", L"Select"), icon);
	return ret;
}

void Form::setRTL( bool r )
{
	Container::setRTL(r);
	contentPane->setRTL(r);
}

shared_ptr<Command> Form::createMenuCancelCommand()
{
	shared_ptr<LookAndFeel> lf = UIManager::getInstance()->getLookAndFeel();
	shared_ptr<Image> icon;
	if(lf->getMenuIcons()->size() > 1){
		icon = (*lf->getMenuIcons())[1];
	}
	shared_ptr<Command> ret = new Command(UIManager::getInstance()->localize(L"cancel", L"Cancel"), icon);
	return ret;
}

void Form::paint( shared_ptr<Graphics> g )
{
	paintBackground(g);
	Container::paint(g);
	if (tint) {
		g->setColor(tintColor);
		g->fillRect(0, 0, getWidth(), getHeight(), (unsigned char) ((tintColor >> 24) & 0xff));
	}

}

void Form::setScrollable( bool scrollable )
{
	contentPane->setScrollable(scrollable);
}

void Form::setVisible( bool visible )
{
	Container::setVisible(visible);
	if (mediaComponents.get() != NULL) {
		int size = mediaComponents->size();
		for (int i = 0; i < size; i++) {
			shared_ptr<Component> mediaCmp = mediaComponents->elementAt(i);
			mediaCmp->setVisible(visible);
		}
	}

}

int Form::getTintColor()
{
	return tintColor;
}

void Form::setTintColor( int tintColor )
{
	this->tintColor = tintColor;
}

void Form::addSelectCommand( shared_ptr<String> selectText )
{
	if (Display::getInstance()->isThirdSoftButton()) {
		if (selectCommand.get() == NULL) {
			selectCommand = createSelectCommand();
		}
		selectCommand->setCommandName(selectText);
		addCommand(selectCommand);
	}

}

void Form::removeSelectCommand()
{
	if (Display::getInstance()->isThirdSoftButton()) {
		removeCommand(selectCommand);
	}
}

void Form::setMenuTransitions( shared_ptr<Transition> transitionIn, shared_ptr<Transition> transitionOut )
{
	 menuBar->setTransitions(transitionIn, transitionOut);
}

shared_ptr<Command> Form::showMenuDialog( shared_ptr<Dialog> menu )
{
	int marginLeft = (int) (getWidth() * 0.25f);
	int marginRight = 0;
	bool rtl = isRTL();

	if (isReverseSoftButtons()) {
		marginRight = marginLeft;
		marginLeft = 0;
	}
	int height = getHeight() / 2;
	if(UIManager::getInstance()->getLookAndFeel()->isTouchMenus()) {
		marginLeft = 0;
		marginRight = 0;
	}
	this->menuDialog = menu;
	return menu->show(height, 0, marginLeft, marginRight, true);

}

bool Form::isReverseSoftButtons()
{
	shared_ptr<LookAndFeel> lf = UIManager::getInstance()->getLookAndFeel();
	if(isRTL()) {
		return !lf->isReverseSoftButtons();
	}
	return lf->isReverseSoftButtons();

}

int Form::calculateTouchCommandGridColumns( shared_ptr<Container> grid )
{
	int count = grid->getComponentCount();
	int maxWidth = 0;
	for(int iter = 0 ; iter < count ; iter++) {
		shared_ptr<Component> c = grid->getComponentAt(iter);
		shared_ptr<Style> s = c->getUnselectedStyle();

		// bidi doesn't matter since this is just a summary of width
		maxWidth = max(maxWidth, c->getPreferredW() + s->getPadding(false, Component::LEFT) + s->getPadding(false, Component::RIGHT) +
			s->getMargin(false, Component::LEFT) + s->getMargin(false, Component::RIGHT));
	}
	return max(2, getWidth() / maxWidth);

}

shared_ptr<Button> Form::createTouchCommandButton( shared_ptr<Command> c )
{
	shared_ptr<Button> b = Button::newV(c);
	b->setTactileTouch(true);
	b->setTextPosition(Label::BOTTOM);
	b->setAlignment(CENTER);
	shared_ptr<String> id = new String(L"TouchCommand");
	b->setUIID(id);
	return b;
}

shared_ptr<Component> Form::createCommandComponent( shared_ptr<Vector<shared_ptr<Command> > > commands )
{
	// Create a touch based menu interface
	if(UIManager::getInstance()->getLookAndFeel()->isTouchMenus()) {
		shared_ptr<Container> menu = Container::newV();
		for(int iter = 0 ; iter < commands->size() ; iter++) {
			shared_ptr<Command> c = commands->elementAt(iter);
			menu->addComponent(createTouchCommandButton(c));
		}
		int cols = calculateTouchCommandGridColumns(menu);
		menu->setLayout(new GridLayout(max(1, commands->size() / cols + 
			commands->size() % cols != 0 ? 1:0 ), cols));
		return menu;
	}
	return createCommandList(commands);

}

shared_ptr<List> Form::createCommandList( shared_ptr<Vector<shared_ptr<Command> > > commands )
{
	//point cast
	shared_ptr<VectorArray<shared_ptr<Object> > > vect = new VectorArray<shared_ptr<Object> >(commands->size());

	for(int i = 0 ; i < commands->size(); i ++)
	{
		(*vect)[i] = static_pointer_cast<Object>((*commands)[i]);
	}
	shared_ptr<List> l = List::newV(vect);

	shared_ptr<String> id = new String(L"CommandList");
	l->setUIID(id);
	Component* c = dynamic_cast<Component*>(l->getRenderer().get());
	id = new String(L"Command");
	c->setUIID(id);
	c = l->getRenderer()->getListFocusComponent(l).get();
	id = new String(L"CommandFocus");
	c->setUIID(id);
	l->setFixedSelection(List::FIXED_NONE_CYCLIC);
	shared_ptr<ActionListener> actListener = dynamic_pointer_cast<ActionListener>(this->shared_from_this());
	l->addActionListener(actListener);
	shared_ptr<SelectionListener> selListener = dynamic_pointer_cast<SelectionListener>(this->shared_from_this());
	l->addSelectionListener(selListener);
	commandList = l;
	return l;
}

shared_ptr<Command> Form::getComponentSelectedCommand( shared_ptr<Component> cmp )
{
	shared_ptr<Command> cmd;
	List* list = dynamic_cast<List*>(cmp.get());
	if(list != NULL) {
		//point cast
		cmd =  dynamic_pointer_cast<Command>(list->getSelectedItem());
	} else {
		cmp = cmp->getComponentForm()->getFocused();
		Button* btn  = dynamic_cast<Button*>(cmp.get());
		if(btn != NULL) {
			cmd =  btn->getCommand();
		}
	}
	// nothing to do for this case...
	return cmd;
}

shared_ptr<MenuBar> Form::getMenuBar()
{
	return menuBar;
}

void Form::sizeChanged( int w, int h )
{

}

void Form::addSortedComponentDown( shared_ptr<Vector<shared_ptr<Component> > > components, shared_ptr<Component> c )
{

	int componentCount = components->size();
	int componentY = c->getAbsoluteY();

	int bestSpot = 0;
	bool rtl = isRTL();

	// add by jiajing
	if (c->getUpDown() == false)
		return;
	//end

	shared_ptr<Component> scrollableParent = findScrollableAncestor(c);

	// find components in the same column and add the component either at the end
	// of the line or at its start
	for (int iter = 0; iter < componentCount; iter++) {
		shared_ptr<Component> current =  components->elementAt(iter);

		// this component is in the same column...
		shared_ptr<Component> currentScrollParent = findScrollableAncestor(current);
		if (currentScrollParent == scrollableParent) {
			if (isInSameColumn(current, c)) {
				int currentY = current->getAbsoluteY();
				if (currentY > componentY) {
					continue;
				}
				bestSpot = iter + 1;
				continue;
			}
		} else {
			shared_ptr<Component> tempScrollableParent = scrollableParent;
			if (scrollableParent.get() == NULL) {
				tempScrollableParent = c;
			}
			shared_ptr<Component> tempCurrentScrollParent = currentScrollParent;
			if (currentScrollParent.get() == NULL) {
				tempCurrentScrollParent = current;
			}
			if (tempCurrentScrollParent->getAbsoluteY() > tempScrollableParent->getAbsoluteY()) {
				continue;
			}
			if (isInSameColumn(tempCurrentScrollParent, tempScrollableParent)) {
				bestSpot = iter + 1;
				continue;
			}
		}
		if (((!rtl) && (current->getAbsoluteX() < c->getAbsoluteX())) ||
			((rtl) && (current->getAbsoluteX() > c->getAbsoluteX()))) {
				bestSpot = iter + 1;
		}
	}

	components->insertElementAt(c, bestSpot);

}

shared_ptr<Form> Form::newV( void )
{
	shared_ptr<Form>  form = new Form();
	form->constructV();
	return form;
}

shared_ptr<Form> Form::newV( shared_ptr<String> title )
{
	shared_ptr<Form> form = new Form();
	form->constructV(title);
	return form;
}

shared_ptr<Command> Form::getSelectMenuItem()
{
	return selectMenuItem;
}

shared_ptr<Command> Form::getCancelMenuItem()
{
	return cancelMenuItem;
}

void Form::actionPerformed( shared_ptr<ActionEvent> evt )
{
	menuDialog->dispose();
	menuDialog.reset();
	if (lastCmd.get() != NULL) {
		shared_ptr<ActionEvent> e = new ActionEvent(lastCmd);
		lastCmd->actionPerformed(e);
		if(!e->isConsumed())
			actionCommandImpl(lastCmd);
	}
}

void Form::selectionChanged( int oldSelected, int newSelected )
{
	shared_ptr<Object> o = this->commandList->getSelectedItem();
	lastCmd = dynamic_pointer_cast<Command>(o);
}
__GUI_END_NAMESPACE
