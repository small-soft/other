#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

AM_IMPLEMENT_DYNAMIC(List, Component)

List::List()
{
	fixedSelection = 0;
	fireOnRelease = false;
	commandList = false;
	ignoreFocusComponentWhenUnfocused = false;
	disposeDialogOnSelection = false;
	mutableRendererBackgrounds = false;

	orientation = VERTICAL;
	inputOnFocus = true;
	numericKeyActions = true;
	paintFocusBehindList = true;
	minElementHeight = 0;
	itemGap = 2;
	borderGap = 2;
	animationPosition = 0;
	destination = 0;
	fireOnClick = true;
	scrollToSelected = true;
	initialFixedDrag = 0;
	initialFixedSelection = 0;
}

void List::constructV( shared_ptr<VectorArray<shared_ptr<Object> > > items)
{	
	defaultListModel = new DefaultListModel(items);
	shared_ptr<ListModel> listModel = static_pointer_cast<ListModel>(defaultListModel);
	this->constructV(listModel);
}

void List::constructV(shared_ptr<ListModel> model)
{	
	shared_ptr<String> id = new String(L"List");
	setUIID(id);
	setModel(model);
	shared_ptr<LookAndFeel> laf = UIManager::getInstance()->getLookAndFeel();
	setSmoothScrolling(laf->isDefaultSmoothScrolling());

	dispatcher = new EventDispatcher<ActionListener>();
	eventSource = this->shared_from_this();
	this->defaultRenderer = new DefaultListCellRenderer();
	this->renderer = this->defaultRenderer;
}

void List::constructV( shared_ptr<Vector<shared_ptr<Object> > > items)
{
	defaultListModel = new DefaultListModel(items);
	shared_ptr<ListModel> listModel = static_pointer_cast<ListModel>(defaultListModel);
	this->constructV(listModel);
}

List::~List(void)
{
}

shared_ptr<List> List::shared_from_this()
{
	shared_ptr<Component> cmp = Component::shared_from_this();
	return dynamic_pointer_cast<List>(cmp);
}
void List::initComponentImpl()
{
	dataChanged(0, 0);
	// lazily bind listeners to prevent a memory leak in cases where models
	// are stored separately from view
	bindListeners();
	Component::initComponentImpl();
	int index = model->getSelectedIndex();
	if(index >= 0){
		model->setSelectedIndex(index);
	}

}

void List::laidOut()
{
	Component::laidOut();
	if (isScrollable() && isInitialized() && scrollToSelected) {
		int index = model->getSelectedIndex();
		if (index >= 0) {
			selectElement(index);
		}
	}

}

void List::deinitializeImpl()
{
	Component::deinitializeImpl();

	// cleanup to allow garbage collection even if the user keeps the model in
	// memory which is a valid use case
	if (listener.get() != NULL) {
		// modified by leex
		shared_ptr<DataChangedListener> dataChangeListener= dynamic_pointer_cast<DataChangedListener>(listener);
		model->removeDataChangedListener(dataChangeListener);
		shared_ptr<SelectionListener> selectionListener= dynamic_pointer_cast<SelectionListener>(listener);
		model->removeSelectionListener(listener);
		listener.reset();
	}
}

bool List::isScrollableY()
{
	return getScrollDimension()->getHeight() > getHeight() && (fixedSelection < FIXED_NONE_BOUNDRY) &&
		orientation != HORIZONTAL;

}

bool List::isScrollableX()
{
	return getScrollDimension()->getWidth() > getWidth() && (fixedSelection < FIXED_NONE_BOUNDRY) &&
		orientation == HORIZONTAL;
}

int List::getMinElementHeight()
{
	 return minElementHeight;
}

void List::setMinElementHeight( int minElementHeight )
{
	this->minElementHeight = minElementHeight;
}

int List::size()
{
	return model->getSize();
}

int List::getSelectedIndex()
{
	 return model->getSelectedIndex();
}

void List::setSelectedIndex( int index )
{
	setSelectedIndex(index, true);
}

void List::setSelectedIndex( int index, bool scrollToSelection )
{
	if (index < 0) {
		return;//throw new IllegalArgumentException("Selection index is negative:" + index);
	}
	model->setSelectedIndex(index);
	if (scrollToSelection && isInitialized()) {
		selectElement(index);
	}

}
shared_ptr<Rectangle> List::getVisibleBounds()
{
	shared_ptr<Rectangle> pos = new Rectangle();
	shared_ptr<Dimension> rendererSize = getElementSize(false, true);
	shared_ptr<Style> style = getStyle();
	int width = getWidth() - style->getPadding(isRTL(), RIGHT) - style->getPadding(isRTL(), LEFT) - getSideGap();
	calculateComponentPosition(getSelectedIndex(), width, pos, rendererSize, getElementSize(true, true), true);
	pos->setX(pos->getX() + getX());
	pos->setY(pos->getY() + getY());
	return pos;

}

shared_ptr<Object> List::getSelectedItem()
{
	shared_ptr<Object> o;
	int idx = model->getSelectedIndex();
	if (idx < model->getSize() && idx > -1) {
		o =  model->getItemAt(idx);
	}
	return o;

}

void List::setSelectedItem( shared_ptr<Object> item )
{
	int size = model->getSize();
	for (int iter = 0; iter < size; iter++) {
		shared_ptr<Object> current = model->getItemAt(iter);
		if (current == item /*|| (current.get() != NULL && (*current) ==(*item))*/) {
			model->setSelectedIndex(iter);
			break;
		}
	}

}

shared_ptr<ListModel> List::getModel()
{
	 return model;
}

void List::setShouldCalcPreferredSize( bool shouldCalcPreferredSize )
{
	Component::setShouldCalcPreferredSize(shouldCalcPreferredSize);
	elemSize.reset();
	selectedElemSize.reset();

	// we should try passing the should calcPreferredSize to the renderer so it can revalidate too
	if(shouldCalcPreferredSize) {
		shared_ptr<ListCellRenderer> r = getRenderer();
		shared_ptr<Object> val;
		if (renderingPrototype.get() != NULL) {
			val = renderingPrototype;
		} else {
			if (getModel()->getSize() > 0) {
				val = getModel()->getItemAt(0);
			} else {
				return;
			}
		}
		shared_ptr<Component> c = r->getListCellRendererComponent(this->shared_from_this(), val, 0, false);
		c->setShouldCalcPreferredSize(shouldCalcPreferredSize);
		shared_ptr<Component> c2 = r->getListCellRendererComponent(this->shared_from_this(), val, 0, true);
		c2->setShouldCalcPreferredSize(shouldCalcPreferredSize);
	}

}

void List::dataChanged( int status, int index )
{
	setShouldCalcPreferredSize(true);
	if (getSelectedIndex() >= model->getSize()) {
		setSelectedIndex(max(model->getSize() - 1, 0));
	}

	modelChanged(status, index);
	repaint();

}

void List::bindListeners()
{
	if (listener.get() == NULL) {
		listener = new Listeners(this->shared_from_this().get());
		model->addDataChangedListener(listener);
		model->addSelectionListener(listener);
	}

}

void List::setModel( shared_ptr<ListModel> model )
{
	if (this->model.get() != NULL) {
		setShouldCalcPreferredSize(true);
		this->model->removeDataChangedListener(listener);
		this->model->removeSelectionListener(listener);
		this->model = model;
		listener.reset();

		// when replacing a model on a scrolled list reset the scrolling if necessary
		if (getScrollDimension()->getHeight() < getScrollY() + getHeight()) {
			setScrollY(0);
		}
		if (getScrollDimension()->getWidth() < getScrollX() + getWidth()) {
			setScrollX(0);
		}
	}
	this->model = model;
	if (isInitialized()) {
		bindListeners();
	}
	repaint();

}

bool List::isNumericKeyActions()
{
	 return numericKeyActions;
}

void List::setNumericKeyActions( bool numericKeyActions )
{
	 this->numericKeyActions = numericKeyActions;
}

bool List::isCommandList()
{
	 return commandList;
}

void List::setCommandList( bool commandList )
{
	 this->commandList = commandList;
}

bool List::isIgnoreFocusComponentWhenUnfocused()
{
	 return ignoreFocusComponentWhenUnfocused;
}

void List::setIgnoreFocusComponentWhenUnfocused( bool ignoreFocusComponentWhenUnfocused )
{
	  this->ignoreFocusComponentWhenUnfocused = ignoreFocusComponentWhenUnfocused;
}

bool List::isMutableRendererBackgrounds()
{
	return mutableRendererBackgrounds;
}

void List::setMutableRendererBackgrounds( bool mutableRendererBackgrounds )
{
	 this->mutableRendererBackgrounds = mutableRendererBackgrounds;
}

void List::setListCellRenderer( shared_ptr<ListCellRenderer> renderer )
{
	if (this->renderer.get() != NULL) {
		//calculate the item list size and the list size.
		elemSize.reset();
		selectedElemSize.reset();
		setShouldCalcPreferredSize(true);
	}
	this->renderer = renderer;

}

shared_ptr<ListCellRenderer> List::getRenderer()
{
	 return renderer;
}

int List::getOrientation()
{
	 return orientation;
}

void List::refreshTheme()
{
	shared_ptr<ListCellRenderer> r = getRenderer();
	if (renderingPrototype.get() != NULL) {
		r->getListCellRendererComponent(this->shared_from_this(), renderingPrototype, 0, false)->refreshTheme();
	} else {
		if (getModel()->getSize() > 0) {
			r->getListCellRendererComponent(this->shared_from_this(), getModel()->getItemAt(0), 0, false)->refreshTheme();
		} else {
			shared_ptr<Object> o;
			r->getListCellRendererComponent(this->shared_from_this(), o, 0, false)->refreshTheme();
		}
	}
	shared_ptr<List> list =this->shared_from_this();
	shared_ptr<Component> focus = r->getListFocusComponent(list);
	if (focus.get() != NULL) {
		focus->refreshTheme();
	}
	Component::refreshTheme();

}

void List::setOrientation( int orientation )
{
	 this->orientation = orientation;
}

void List::scrollRectToVisible( shared_ptr<Rectangle> rect )
{
	if (fixedSelection < FIXED_NONE_BOUNDRY) {
		//Dimension elemSize = getElementSize();
		shared_ptr<Rectangle> toScroll;
		if (orientation != HORIZONTAL) {
			toScroll = new Rectangle(getScrollX(), rect->getY(), rect->getSize()->getWidth(), rect->getSize()->getHeight() + itemGap);
		} else {
			toScroll = new Rectangle(rect->getX(), getScrollY(), rect->getSize()->getWidth() + itemGap, rect->getSize()->getHeight());
		}
		shared_ptr<Component> o = static_pointer_cast<Component>(this->shared_from_this());
		Component::scrollRectToVisible(toScroll, o);

	}

}

void List::setHandlesInput( bool b )
{
	shared_ptr<Form> f = getComponentForm();
	if (f.get() != NULL) {
		// prevent the list from losing focus if its the only element
		// or when the user presses fire and there is no other component
		Component::setHandlesInput(b || f->isSingleFocusMode());
	} else {
		Component::setHandlesInput(b);
	}

}

void List::setHandlesInputParent( bool b )
{
	Component::setHandlesInput(b);
}

void List::fireClicked()
{
	bool h = handlesInput();
	setHandlesInput(!h);
	if (h) {
		fireActionEvent();
	}
	repaint();
}

bool List::isSelectableInteraction()
{
	 return true;
}

void List::keyReleased( int keyCode )
{
	// other events are in keyReleased to prevent the next event from reaching the next form
	int gameAction = Display::getInstance()->getGameAction(keyCode);
	if (gameAction == Display::GAME_FIRE) {
		bool h = handlesInput();
		setHandlesInput(!h);
		if (h) {
			fireActionEvent();
		}
		repaint();
		return;
	}

	if (numericKeyActions && gameAction != Display::GAME_LEFT &&
		gameAction != Display::GAME_RIGHT && gameAction != Display::GAME_UP &&
		gameAction != Display::GAME_DOWN) {
			if (keyCode >= '1' && keyCode <= '9') {
				int offset = keyCode - '1';
				if (offset < getModel()->getSize()) {
					setSelectedIndex(offset);
					fireActionEvent();
				}
			}
	}

}

void List::keyPressed( int keyCode )
{
	// scrolling events are in keyPressed to provide immediate feedback
	if (!handlesInput()) {
		return;
	}

	int gameAction = Display::getInstance()->getGameAction(keyCode);
	int keyFwd;
	int keyBck;
	if (getOrientation() != HORIZONTAL) {
		keyFwd = Display::GAME_DOWN;
		keyBck = Display::GAME_UP;
		if (gameAction == Display::GAME_LEFT || gameAction == Display::GAME_RIGHT) {
			setHandlesInput(false);
		}
	} else {
		if (isRTL()) {
			keyFwd = Display::GAME_LEFT;
			keyBck = Display::GAME_RIGHT;
		} else {
			keyFwd = Display::GAME_RIGHT;
			keyBck = Display::GAME_LEFT;
		}
		if (gameAction == Display::GAME_DOWN || gameAction == Display::GAME_UP) {
			setHandlesInput(false);
		}
	}

	int selectedIndex = model->getSelectedIndex();
	if (gameAction == keyBck) {
		selectedIndex--;
		if (selectedIndex < 0) {
			if (fixedSelection != FIXED_NONE && fixedSelection != FIXED_NONE_ONE_ELEMENT_MARGIN_FROM_EDGE) {
				selectedIndex = size() - 1;
			} else {
				selectedIndex = 0;
				setHandlesInput(false);
			}
		}
	} else if (gameAction == keyFwd) {
		selectedIndex++;
		if (selectedIndex >= size()) {
			if (fixedSelection != FIXED_NONE && fixedSelection != FIXED_NONE_ONE_ELEMENT_MARGIN_FROM_EDGE) {
				selectedIndex = 0;
			} else {
				selectedIndex = size() - 1;
				setHandlesInput(false);
			}
		}
	}

	if (selectedIndex != model->getSelectedIndex()) {
		model->setSelectedIndex(selectedIndex);
		int direction = (gameAction == keyFwd ? 1 : -1);
		if ((isRTL()) && (getOrientation() == HORIZONTAL)) {
			direction = -direction;
		}
		updateAnimationPosition(direction);
		if (fixedSelection == FIXED_NONE || fixedSelection == FIXED_NONE_CYCLIC) {
			selectElement(selectedIndex);
		}
		if (fixedSelection == FIXED_NONE_ONE_ELEMENT_MARGIN_FROM_EDGE) {
			// are we going down?
			if (keyFwd == gameAction) {
				selectElement(min(selectedIndex + 1, getModel()->getSize() - 1));
			} else {
				selectElement(max(selectedIndex - 1, 0));
			}
		}
	}
	repaint();

}

void List::selectElement( int selectedIndex )
{
	shared_ptr<Dimension> size = getElementSize(false, true);
	shared_ptr<Rectangle> rect;
	if (getOrientation() != HORIZONTAL) {
		rect = new Rectangle(getX(), (size->getHeight() + itemGap) * selectedIndex, getElementSize(true, true));
	} else {
		rect = new Rectangle((size->getWidth() + itemGap) * selectedIndex, getY(), getElementSize(true, true));
	}
	scrollRectToVisible(rect);

}

void List::updateAnimationPosition( int direction )
{
	if (animationPosition != 0) {
		return;
	}
	if (isSmoothScrolling()) {
		if (orientation != HORIZONTAL) {
			animationPosition += (direction * getElementSize(false, true)->getHeight());
		} else {
			animationPosition += (direction * getElementSize(false, true)->getWidth());
		}
		destination = abs(animationPosition);
		initListMotion();
	}

}

void List::initListMotion()
{
	shared_ptr<Form> p = getComponentForm();
	if(p.get() != NULL) {
		shared_ptr<Animation> ani = this->shared_from_this();
		p->registerAnimatedInternal(ani);
	}
	listMotion = Motion::createSplineMotion(0, destination, getScrollAnimationSpeed());
	listMotion->start();

}

void List::calculateComponentPosition( int index, int defaultWidth, shared_ptr<Rectangle> rect, shared_ptr<Dimension> rendererSize, shared_ptr<Dimension> selectedSize, bool beforeSelected )
{
	shared_ptr<Style> style = getStyle();
	int initialY = style->getPadding(false, Component::TOP);
	int initialX = style->getPadding(false, Component::LEFT);

	bool rtl = isRTL();
	if (rtl) {
		initialX += getSideGap();
	}

	int selection = getSelectedIndex();
	shared_ptr<Dimension> d = rect->getSize();
	int selectedDiff;

	// the algorithm illustrated here is very simple despite the "mess" of code...
	// The idea is that if we have a "fixed" element we just add up the amount of pixels
	// to get it into its place in the screen (nothing for top obviously).
	// In order to cause the list to be cyclic we just subtract the list size
	// which will cause the bottom elements to "return" from the top.
	if (orientation != HORIZONTAL) {
		int height = rendererSize->getHeight();
		selectedDiff = selectedSize->getHeight() - height;
		rect->setX(initialX);
		d->setHeight(height);
		d->setWidth(defaultWidth);
		int y = 0;
		int listHeight = getHeight() - style->getPadding(false, Component::TOP) - style->getPadding(false, Component::BOTTOM);
		int totalHeight = (height + itemGap) * getModel()->getSize() + selectedDiff;
		switch (fixedSelection) {
				case FIXED_CENTER:
					y = listHeight / 2 - (height + itemGap + selectedDiff) / 2 +
						(index - selection) * (height + itemGap);
					if (!beforeSelected) {
						y += selectedDiff;
					}
					y = recalcOffset(y, totalHeight, listHeight, height + itemGap);
					break;
				case FIXED_TRAIL:
					y = listHeight - (height + itemGap + selectedDiff);
				case FIXED_LEAD:
					y += (index - selection) * (height + itemGap);
					if (index - selection > 0) {
						y += selectedDiff;
					}
					y = recalcOffset(y, totalHeight, listHeight, height + itemGap);
					break;
				default:
					y = index * (height + itemGap);
					if (!beforeSelected) {
						y += selectedDiff;
					}
					break;
		}
		rect->setY(y + initialY);
		if (index == selection) {
			d->setHeight(d->getHeight() + selectedDiff);
		}

	} else {
		int width = rendererSize->getWidth();
		selectedDiff = selectedSize->getWidth() - width;
		rect->setY(initialY);
		d->setHeight(getHeight() - style->getPadding(false, Component::TOP) - style->getPadding(false, Component::BOTTOM));
		d->setWidth(width);
		int x = 0;
		int listWidth = getWidth() - style->getPadding(isRTL(), Component::RIGHT) - style->getPadding(isRTL(), Component::LEFT);
		int totalWidth = (width + itemGap) * getModel()->getSize() + selectedDiff;
		switch (fixedSelection) {
				case FIXED_CENTER:
					x = listWidth / 2 - (width + itemGap + selectedDiff) / 2 +
						(index - selection) * (width + itemGap);
					if (!beforeSelected) {
						x += selectedDiff;
					}
					if(rtl) {
						x = listWidth - x - width;
					}

					x = recalcOffset(x, totalWidth, listWidth, width + itemGap);
					break;
				case FIXED_TRAIL:
					x = listWidth - (width + itemGap + selectedDiff);
				case FIXED_LEAD:
					x += (index - selection) * (width + itemGap);
					if (index - selection > 0) {
						x += selectedDiff;
					}
					if (rtl) {
						x = listWidth - x - width;
					}
					x = recalcOffset(x, totalWidth, listWidth, width + itemGap);
					break;
				default:
					x = index * (width + itemGap);
					if (!beforeSelected) {
						x += selectedDiff;
					}
					break;
		}
		int rectX=initialX + x;
		if ((rtl) && (fixedSelection<FIXED_NONE_BOUNDRY)) {

			rectX = initialX + totalWidth - (x - initialX) - (width + itemGap);
			if(index == getSelectedIndex()) {
				rectX -= selectedDiff;
			}
			if(totalWidth < listWidth) {
				rectX += (listWidth - totalWidth);
			}
		}
		rect->setX(rectX);
		if (index == selection) {
			d->setWidth(d->getWidth() + selectedDiff);
		}
	}

}

int List::recalcOffset( int offset, int totalSize, int viewSize, int componentSize )
{
	if (offset + animationPosition % componentSize >= viewSize) {
		offset -= totalSize;
	} else {
		if (offset + animationPosition % componentSize < 1 - componentSize) {
			offset += totalSize;
		}
	}
	return offset;

}

void List::paint( shared_ptr<Graphics> g )
{
	UIManager::getInstance()->getLookAndFeel()->drawList(g, this->shared_from_this());
	shared_ptr<Style> style = getStyle();
	int width = getWidth() - style->getPadding(isRTL(), RIGHT) - style->getPadding(isRTL(), LEFT) - getSideGap();
	if (isScrollableX()) {
		width = max(width, getScrollDimension()->getWidth() - style->getPadding(isRTL(), RIGHT) - style->getPadding(isRTL(), LEFT) - getSideGap());
	}
	int numOfcomponents = model->getSize();
	if (numOfcomponents == 0) {
		return;
	}
	int xTranslate = getX();
	int yTranslate = getY();
	g->translate(xTranslate, yTranslate);
	shared_ptr<Rectangle> pos = new Rectangle();
	shared_ptr<Dimension> rendererSize = getElementSize(false, true);

	int selection = model->getSelectedIndex();

	if (animationPosition != 0 && fixedSelection > FIXED_NONE_BOUNDRY) {
		// selection should never move during animation of fixed elements
		selection = -1;

		if (orientation != HORIZONTAL) {
			yTranslate += animationPosition;
			g->translate(0, animationPosition);
		} else {
			xTranslate += animationPosition;
			g->translate(animationPosition, 0);
		}
	}

	int clipX = g->getClipX();
	int clipY = g->getClipY();
	int clipWidth = g->getClipWidth();
	int clipHeight = g->getClipHeight();

	// this flag is for preformance improvements
	// if we figured out that the list items are not visible anymore
	// we should break from the List loop
	bool shouldBreak = false;

	// improve performance for browsing the end of a very large list
	int startingPoint = 0;
	if (fixedSelection < FIXED_NONE_BOUNDRY) {
		int startX = clipX + getAbsoluteX();
		if (isRTL()) {
			//In RTL the start of the list is not in the left side of the viewport, but rather the right side
			startX += getWidth();
		}
		startingPoint = max(0, pointerSelect(startX, clipY + getAbsoluteY()) - 1);
	}

	int startOffset = 0;
	int endOffset = numOfcomponents;

	if(mutableRendererBackgrounds) {
		for (int i = startingPoint; i < numOfcomponents; i++) {
			// skip on the selected
			if (i == getSelectedIndex() && animationPosition == 0) {
				shouldBreak = true;
				if(!shouldBreak) {
					startOffset = i;
				}
				endOffset = i;
				continue;
			}
			calculateComponentPosition(i, width, pos, rendererSize, getElementSize(true, true), i <= getSelectedIndex());

			// if the renderer is in the clipping region
			if (pos->intersects(clipX, clipY, clipWidth, clipHeight)) {
				if(!shouldBreak) {
					startOffset = i;
				}
				endOffset = i;
				shared_ptr<Dimension> size = pos->getSize();
				
				shared_ptr<Component> selectionCmp = renderer->getListCellRendererComponent(this->shared_from_this(), getModel()->getItemAt(i), i, i == getSelectedIndex());
				renderComponentBackground(g, selectionCmp, pos->getX(), pos->getY(), size->getWidth(), size->getHeight());
				shouldBreak = true;
			} else {
				//this is relevant only if the List is not fixed.
				if (shouldBreak && (fixedSelection < FIXED_NONE_BOUNDRY)) {
					break;
				}
			}
		}
	} else {
		shared_ptr<Object> valueAt0 = getModel()->getItemAt(0);
		shared_ptr<Component> selectionCmp = renderer->getListCellRendererComponent(this->shared_from_this(), valueAt0, 0, true);
		shared_ptr<Component> unselectedCmp = renderer->getListCellRendererComponent(this->shared_from_this(), valueAt0, 0, false);
		for (int i = startingPoint; i < numOfcomponents; i++) {
			// skip on the selected
			if (i == getSelectedIndex() && animationPosition == 0) {
				shouldBreak = true;
				if(!shouldBreak) {
					startOffset = i;
				}
				endOffset = i;
				continue;
			}
			calculateComponentPosition(i, width, pos, rendererSize, getElementSize(true, true), i <= getSelectedIndex());

			// if the renderer is in the clipping region
			if (pos->intersects(clipX, clipY, clipWidth, clipHeight)) {
				if(!shouldBreak) {
					startOffset = i;
				}
				endOffset = i;
				if(i == getSelectedIndex()) {
					shared_ptr<Dimension> size = pos->getSize();
					renderComponentBackground(g, selectionCmp, pos->getX(), pos->getY(), size->getWidth(), size->getHeight());
				} else {
					shared_ptr<Dimension> size = pos->getSize();
					renderComponentBackground(g, unselectedCmp, pos->getX(), pos->getY(), size->getWidth(), size->getHeight());
				}
				shouldBreak = true;
			} else {
				//this is relevant only if the List is not fixed.
				if (shouldBreak && (fixedSelection < FIXED_NONE_BOUNDRY)) {
					break;
				}
			}
		}
	}

	if (paintFocusBehindList) {
		paintFocus(g, width, pos, rendererSize);
	}

	for (int i = startOffset; i <= endOffset; i++) {
		// skip on the selected
		if (i == getSelectedIndex() && animationPosition == 0) {
			continue;
		}
		calculateComponentPosition(i, width, pos, rendererSize, getElementSize(true, true), i <= getSelectedIndex());

		shared_ptr<Object> value = model->getItemAt(i);
		shared_ptr<Component> cmp = renderer->getListCellRendererComponent(this->shared_from_this(), value, i, false);
		cmp->setCellRenderer(true);
		shared_ptr<Dimension> size = pos->getSize();
		renderComponent(g, cmp, pos->getX(), pos->getY(), size->getWidth(), size->getHeight());
	}
	calculateComponentPosition(getSelectedIndex(), width, pos, rendererSize, getElementSize(true, true), true);

	shared_ptr<Dimension> size = pos->getSize();
	//if the animation has finished draw the selected element
	if ((renderer->getListFocusComponent(this->shared_from_this()).get() == NULL && (fixedSelection < FIXED_NONE_BOUNDRY)) || animationPosition == 0 && model->getSize() > 0) {
		shared_ptr<Component> selected = renderer->getListCellRendererComponent(this->shared_from_this(), model->getItemAt(selection), selection, true);
		renderComponentBackground(g, selected, pos->getX(), pos->getY(), size->getWidth(), size->getHeight());
		renderComponent(g, selected, pos->getX(), pos->getY(), size->getWidth(), size->getHeight());
	}

	if (!paintFocusBehindList) {
		paintFocus(g, width, pos, rendererSize);
	}
	g->translate(-xTranslate, -yTranslate);
	
}

void List::paintFocus( shared_ptr<Graphics> g, int width, shared_ptr<Rectangle> pos, shared_ptr<Dimension> rendererSize )
{

	if(ignoreFocusComponentWhenUnfocused && !hasFocus()) {
		return;
	}
	calculateComponentPosition(getSelectedIndex(), width, pos, rendererSize, getElementSize(true, true), true);
	shared_ptr<Dimension> size = pos->getSize();

	shared_ptr<Component> cmp = renderer->getListFocusComponent(this->shared_from_this());
	if (cmp.get() != NULL) {
		cmp->setCellRenderer(true);
		int x = pos->getX();
		int y = pos->getY();

		// prevent focus animation from working during a drag operation
		if (orientation != HORIZONTAL) {
			y -= animationPosition;
		} else {
			x -= animationPosition;
		}
		renderComponentBackground(g, cmp, x, y, size->getWidth(), size->getHeight());
		renderComponent(g, cmp, x, y, size->getWidth(), size->getHeight());
	}


}

void List::renderComponent( shared_ptr<Graphics> g, shared_ptr<Component> cmp, int x, int y, int width, int height )
{
	shared_ptr<Style> s = cmp->getStyle();
	int left = s->getMargin(isRTL(), LEFT);
	int top =  s->getMargin(false, TOP);
	cmp->setWidth(width - left - s->getMargin(isRTL(), RIGHT));
	cmp->setHeight(height - top - s->getMargin(false, BOTTOM));
	cmp->setX(x + left);
	cmp->setY(y + top);

	int oX = g->getClipX();
	int oY = g->getClipY();
	int oWidth = g->getClipWidth();
	int oHeight = g->getClipHeight();

	g->clipRect(cmp->getX(), cmp->getY(), cmp->getWidth(), cmp->getHeight());

	cmp->paint(g);
	if (cmp->isBorderPainted()) {
		cmp->paintBorder(g);
	}
	g->setClip(oX, oY, oWidth, oHeight);

}

void List::renderComponentBackground( shared_ptr<Graphics> g, shared_ptr<Component> cmp, int x, int y, int width, int height )
{
	shared_ptr<Style> s = cmp->getStyle();
	int left = s->getMargin(isRTL(), LEFT);
	int top =  s->getMargin(false, TOP);
	cmp->setWidth(width - left - s->getMargin(isRTL(), RIGHT));
	cmp->setHeight(height - top - s->getMargin(false, BOTTOM));
	cmp->setX(x + left);
	cmp->setY(y + top);
	int cX = g->getClipX();
	int cY = g->getClipY();
	int cW = g->getClipWidth();
	int cH = g->getClipHeight();
	g->clipRect(cmp->getX(), cmp->getY(), cmp->getWidth(), cmp->getHeight());
	cmp->paintBackground(g);
	g->setClip(cX, cY, cW, cH);

}

void List::addSelectionListener( shared_ptr<SelectionListener> l )
{
	 model->addSelectionListener(l);
}

void List::removeSelectionListener( shared_ptr<SelectionListener> l )
{
	 model->removeSelectionListener(l);
}

void List::addActionListener( shared_ptr<ActionListener> l )
{
	 dispatcher->addListener(l);
}

void List::removeActionListener( shared_ptr<ActionListener> l )
{
	 dispatcher->removeListener(l);
}

void List::fireActionEvent()
{
	if(isEnabled()){
		if(disposeDialogOnSelection) {
			Dialog* dlg = dynamic_cast<Dialog*>(getComponentForm().get());
			dlg->dispose();
		}
		Component::fireActionEvent();
		shared_ptr<ActionEvent> a = new ActionEvent(eventSource);
		dispatcher->fireActionEvent(a);
		if(isCommandList() && !a->isConsumed()) {
			shared_ptr<Object> i = getSelectedItem();
			if(i.get() != NULL){
			Command* command = dynamic_cast<Command*>(i.get());
			if(command != NULL) {
				command->actionPerformed(a);
				if(!a->isConsumed()) {
					shared_ptr<Form> f = getComponentForm();
					if(f.get() != NULL) {
						f->actionCommandImpl(command);
					}
				}
			}
			}
		}
	}
}

void List::setInputOnFocus( bool inputOnFocus )
{
	this->inputOnFocus = inputOnFocus;
}

void List::setPaintFocusBehindList( bool paintFocusBehindList )
{
	 this->paintFocusBehindList = paintFocusBehindList;
}

void List::focusGainedInternal()
{
	if (inputOnFocus) {
		setHandlesInput(true);
	}
}

void List::focusLostInternal()
{

}

int List::getItemGap()
{
	 return itemGap;
}

void List::setItemGap( int itemGap )
{
	this->itemGap = itemGap;
}

void List::setRenderingPrototype( shared_ptr<Object> renderingPrototype )
{
	this->renderingPrototype = renderingPrototype;
}

shared_ptr<Object> List::getRenderingPrototype()
{
	 return renderingPrototype;
}

shared_ptr<Dimension> List::getElementSize( bool selected, bool addMargin )
{
	if (selected) {
		if (selectedElemSize.get() == NULL) {
			// don't keep element size if there are no elements and no prototype...
			if (renderingPrototype.get() == NULL) {
				if (model->getSize() == 0) {
					// put a sensible value as default when there are no elements or rendering prototype
					shared_ptr<String> title = new String(L"XXXXXX");
					shared_ptr<Label> label = Label::newV(title);
					if(addMargin) {
						
						return label->getPreferredSizeWithMargin();
					}
					return label->getPreferredSize();
				}
			}
			selectedElemSize = calculateElementSize(true, addMargin);
		}
		return selectedElemSize;
	} else {
		if (elemSize.get() == NULL) {
			// don't keep element size if there are no elements and no prototype...
			if (renderingPrototype.get() == NULL) {
				if (model->getSize() == 0) {
					// put a sensible value as default when there are no elements or rendering prototype
					shared_ptr<String> title = new String(L"XXXXXX");
					shared_ptr<Label> l = Label::newV(title);
					if(addMargin) {
						return l->getPreferredSizeWithMargin();
					} else {
						return l->getPreferredSize();
					}
				}
			}
			elemSize = calculateElementSize(false, addMargin);
		}
		return elemSize;
	}

}

shared_ptr<Dimension> List::calculateElementSize( bool selected, bool addMargin )
{
	if (renderingPrototype.get() != NULL) {
		shared_ptr<Component> unselected = renderer->getListCellRendererComponent(this->shared_from_this(), renderingPrototype, 0, selected);
		if(addMargin) {
			return unselected->getPreferredSizeWithMargin();
		} else {
			return unselected->getPreferredSize();
		}
	}
	int width = 0;
	int height = 0;
	int elements = min(5, model->getSize());
	int marginY = 0;
	int marginX = 0;
	for (int iter = 0; iter < elements; iter++) {
		shared_ptr<Component> cmp = renderer->getListCellRendererComponent(this->shared_from_this(), model->getItemAt(iter), iter, selected);
		shared_ptr<Dimension> d = cmp->getPreferredSize();
		width = max(width, d->getWidth());
		height = max(height, d->getHeight());
		if(iter == 0) {
			shared_ptr<Style> s = cmp->getStyle();
			marginY = s->getMargin(TOP) + s->getMargin(BOTTOM);
			marginX = s->getMargin(LEFT) + s->getMargin(RIGHT);
		}
	}
	return new Dimension(width + marginX, height + marginY);

}

void List::longPointerPress( int x, int y )
{
	int s = pointerSelect(x, y);
	if(s > -1) {
		model->setSelectedIndex(s);
	}
}

void List::pointerPressed( int x, int y )
{
	if(fixedSelection > FIXED_NONE_BOUNDRY) {
		// for a fixed list we need to store the initial drag position
		if(isSmoothScrolling()) {
			if(orientation != HORIZONTAL) {
				initialFixedDrag = y;
			} else {
				initialFixedDrag = x;
			}
			initialFixedSelection = getModel()->getSelectedIndex();
		}
	}
	// prevent a hover event from activating the drag in case of a click screen,
	// this is essential for the Storm device
	setDragActivated(false);

	int current = model->getSelectedIndex();
	int selection = pointerSelect(x, y);
	if (selection > -1) {
		model->setSelectedIndex(selection);
		fireOnRelease = current == selection;
	}

	Component::pointerPressed(x, y);

}

void List::pointerHover( shared_ptr<Vector<int> > x,shared_ptr<Vector<int> > y )
{
	clearDrag();
	if(!isDragActivated()) {
		int selection = pointerSelect((*x)[0], (*y)[0]);
		if (selection > -1) {
			model->setSelectedIndex(selection);
		}
	}
	pointerDraggedImpl((*x)[0], (*y)[0]);

}

void List::pointerDragged( int x, int y )
{
 pointerDraggedImpl(x, y);
}

void List::pointerDraggedImpl( int x, int y )
{
	if (isSmoothScrolling()) {
		if(fixedSelection < FIXED_NONE_BOUNDRY) {
			Component::pointerDragged(x, y);
		} else {
			if(getModel()->getSize() > 2) {
				// a fixed list is not scrollable we need to implement dragging ourselves...
				int offset;
				int componentSize;

				if(orientation != HORIZONTAL) {
					offset = y - initialFixedDrag;
					componentSize = getElementSize(false, true)->getHeight();
				} else {
					offset = x - initialFixedDrag;
					componentSize = getElementSize(false, true)->getWidth();
				}

				if(!isDragActivated()) {
					if(offset > 4) {
						setDragActivated(true);
					}
				}
				if(isDragActivated()) {

					int elementSelection = initialFixedSelection + (offset / componentSize) % getModel()->getSize();
					if(elementSelection < 0) {
						elementSelection += getModel()->getSize();
					}
					getModel()->setSelectedIndex(elementSelection);
				}
			}


			int numOfcomponents = getModel()->getSize();
			shared_ptr<Style> style = getStyle();
			int width = getWidth() - style->getPadding(false, RIGHT) - style->getPadding(false, LEFT) - getSideGap();
			if (isScrollableX()) {
				width = max(width, getScrollDimension()->getWidth() - style->getPadding(false, RIGHT) - style->getPadding(false, LEFT) - getSideGap());
			}
			shared_ptr<Dimension> rendererSize = getElementSize(false, true);
			shared_ptr<Dimension> selectedSize = getElementSize(true, true);
			shared_ptr<Rectangle> pos = new Rectangle();
			for (int i = 0; i < numOfcomponents; i++) {
				calculateComponentPosition(i, width, pos, rendererSize, selectedSize, true);
				if (pos->contains(x, y)) {
					model->setSelectedIndex(i);
					break;
				}
			}
		}
	} else {
		model->setSelectedIndex(pointerSelect(x, y));
	}

}

int List::pointerSelect( int x, int y )
{
	int selectedIndex = -1;
	int numOfcomponents = getModel()->getSize();
	shared_ptr<Style> style = getStyle();

	shared_ptr<Dimension> rendererSize = getElementSize(false, true);
	shared_ptr<Dimension> selectedSize = getElementSize(true, true);

	shared_ptr<Rectangle> pos = new Rectangle();
	int width = getWidth() - style->getPadding(false, RIGHT) - style->getPadding(false, LEFT) - getSideGap();
	if (isScrollableX()) {
		width = max(width, getScrollDimension()->getWidth() - style->getPadding(false, RIGHT) - style->getPadding(false, LEFT) - getSideGap());
	}
	y = y - getAbsoluteY();
	x = x - getAbsoluteX();

	if (fixedSelection < FIXED_NONE_BOUNDRY) {
		calculateComponentPosition(getSelectedIndex(), width, pos, rendererSize, getElementSize(true, true), true);

		if (orientation != HORIZONTAL) {
			if(y < pos->getY()){
				selectedIndex = y / (rendererSize->getHeight() + itemGap);
			}else{
				int current = getSelectedIndex();
				if(y < pos->getY() + selectedSize->getHeight()){
					selectedIndex = current;
				}else{
					selectedIndex = (current+1) + (y - (pos->getY() + selectedSize->getHeight()))/(rendererSize->getHeight() + itemGap);
				}
			}
		} else {
			if (isRTL()) {
				if (x > pos->getX()+selectedSize->getWidth()) {
					int delta=x-(pos->getX()+selectedSize->getWidth());
					delta /= (rendererSize->getWidth() + itemGap);

					// should have been -1-delta, but works better like this.
					selectedIndex = getSelectedIndex()-delta;
				} else {
					if(x >= pos->getX()){
						selectedIndex = getSelectedIndex();
					} else {
						int delta=pos->getX()-x;
						delta/=(rendererSize->getWidth() + itemGap);
						selectedIndex=getSelectedIndex()+1+delta;
					}
				}
			} else {
				if(x < pos->getX()){
					selectedIndex = x / (rendererSize->getWidth() + itemGap);
				}else{
					int current = getSelectedIndex();
					if(x < pos->getX() + selectedSize->getWidth()){
						selectedIndex = current;
					}else{
						selectedIndex = (current+1) + (x - (pos->getX() + selectedSize->getWidth()))/(rendererSize->getWidth() + itemGap);
					}
				}
			}
		}
	} else {
		for (int i = 0; i < numOfcomponents; i++) {
			calculateComponentPosition(i, width, pos, rendererSize, selectedSize, true);
			if (pos->contains(x, y)) {
				selectedIndex = i;
				break;
			}
		}
	}

	if (selectedIndex < 0 || selectedIndex >= size()) {
		return -1;
	}
	return selectedIndex;

}

void List::setFireOnClick( bool fireOnClick )
{
  this->fireOnClick = fireOnClick;
}

void List::pointerHoverReleased( shared_ptr<Vector<int> > x,shared_ptr<Vector<int> > y )
{
	pointerReleasedImpl((*x)[0], (*y)[0], true);
}

void List::pointerReleasedImpl( int x, int y, bool isHover )
{
	if (isDragActivated()) {
		if(fixedSelection < FIXED_NONE_BOUNDRY) {
			Component::pointerReleased(x, y);
		} else {
			if(isScrollableY()){
				destination += (int)Display::getInstance()->getDragSpeed(true);
			}else{
				destination += (int)Display::getInstance()->getDragSpeed(false) * 1000;
			}
			if(destination < 0) {
				destination += model->getSize();
				if(destination >= model->getSize()) {
					destination %= model->getSize();
				}
			} else {
				if(destination >= model->getSize()) {
					destination -= model->getSize();
					if(destination >= model->getSize()) {
						destination %= model->getSize();
					}
				}
			}

			initListMotion();
			setDragActivated(false);
		}
		return;
	}

	if (!isHover) {
		if (fireOnClick || fireOnRelease) {
			fireActionEvent();
		}
	}

}

void List::pointerReleased( int x, int y )
{
	  pointerReleasedImpl(x, y, false);
}

shared_ptr<Dimension> List::calcPreferredSize()
{
	return UIManager::getInstance()->getLookAndFeel()->getListPreferredSize(this->shared_from_this());
}

void List::addItem( shared_ptr<Object> item )
{
	model->addItem(item);
}

int List::getFixedSelection()
{
	return fixedSelection;
}

void List::setFixedSelection( int fixedSelection )
{
 this->fixedSelection = fixedSelection;
}

void List::deregisterAnimatedInternal()
{
	if (animationPosition == 0) {
		Component::deregisterAnimatedInternal();
	}
}

bool List::animate()
{
	// parent is performing the animation we shouldn't do anything in this case
	// this is the scrolling animation which we don't want to interfear with
	bool parentFinished = Component::animate();
	if (animationPosition != 0) {
		if (animationPosition < 0) {
			animationPosition = min(listMotion->getValue() - destination, 0);
		} else {
			animationPosition = max(destination - listMotion->getValue(), 0);
		}
		if(animationPosition == 0) {
			deregisterAnimatedInternal();
		}
		return true;
	}
	return parentFinished;

}

void List::setBorderGap( int borderGap )
{
	 this->borderGap = borderGap;
}

int List::getBorderGap()
{
	return borderGap;
}

void List::setScrollToSelected( bool scrollToSelected )
{
	 this->scrollToSelected = scrollToSelected;
}

void List::modelChanged( int status, int index )
{

}

void List::listSelectionChanged( int oldSelected, int newSelected )
{

}

shared_ptr<List> List::newV( shared_ptr<VectorArray<shared_ptr<Object> > > items)
{
	shared_ptr<List> list = new List();
	list->constructV(items);
	return list;
}

shared_ptr<List> List::newV( shared_ptr<ListModel> model /*= new DefaultListModel()*/)
{
	shared_ptr<List> list = new List();
	list->constructV(model);
	return list;
}

shared_ptr<List> List::newV( shared_ptr<Vector<shared_ptr<Object> > > items)
{
	shared_ptr<List> list = new List();
	list->constructV(items);
	return list;
}

void List::Listeners::dataChanged( int status, int index )
{
	list->dataChanged(status, index);
}

void List::Listeners::selectionChanged( int oldSelected, int newSelected )
{
	list->Component::repaint();
	list->listSelectionChanged(oldSelected, newSelected);
}

List::Listeners::Listeners( List *list )
{
	this->list = list;
}
__GUI_END_NAMESPACE
