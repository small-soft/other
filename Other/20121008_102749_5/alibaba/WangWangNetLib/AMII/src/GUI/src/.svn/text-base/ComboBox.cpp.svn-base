
#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

AM_IMPLEMENT_DYNAMIC(ComboBox, List)

shared_ptr<ComboBox> ComboBox::newV(shared_ptr<ListModel> model /*= new DefaultListModel()*/)
{
	shared_ptr<ComboBox> self = new ComboBox();
	self->constructV(model);
	return self;
}

shared_ptr<ComboBox> ComboBox::newV(shared_ptr<Vector<shared_ptr<Object> > > items)
{
	shared_ptr<ComboBox> self = new ComboBox();
	self->constructV(items);
	return self;
}

shared_ptr<ComboBox> ComboBox::newV( shared_ptr<VectorArray<shared_ptr<Object> > > items )
{
	shared_ptr<ComboBox> self = new ComboBox();
	self->constructV(items);
	return self;
}
void ComboBox::constructV(shared_ptr<ListModel> model)
{
	List::constructV(model);

	shared_ptr<String> id = new String(L"ComboBox");
	setUIID(id);
	// to check
	shared_ptr<ListCellRenderer> listCellRender = getRenderer();
	shared_ptr<DefaultListCellRenderer> defaultListCellRender = dynamic_pointer_cast<DefaultListCellRenderer>(listCellRender);
	defaultListCellRender->setShowNumbers(false);

	// to check
	setInputOnFocus(false);
	setIsScrollVisible(false);
	setFixedSelection(FIXED_NONE_CYCLIC);

	shared_ptr<Component> cmp = dynamic_pointer_cast<Component>(getRenderer()); 
	if( cmp.get() != NULL)
	{
		shared_ptr<String> uiid = new String(L"ComboBoxItem");
		cmp->setUIID(uiid);
	}

	shared_ptr<Component> c = getRenderer()->getListFocusComponent(this->shared_from_this());
	if(c.get() != NULL)
	{
		shared_ptr<String> uiid = new String(L"ComboBoxFocus");
		c->setUIID(uiid);
	}

}

void ComboBox::constructV(shared_ptr<Vector<shared_ptr<Object> > > items)
{
	shared_ptr<ListModel> listModel = new DefaultListModel(items);
	constructV(listModel);
}

void ComboBox::constructV( shared_ptr<VectorArray<shared_ptr<Object> > > items )
{
	shared_ptr<ListModel> listModel = new DefaultListModel(items);
	constructV(listModel);
}

ComboBox::ComboBox(void)
{
}


ComboBox::~ComboBox(void)
{
}
shared_ptr<ComboBox> ComboBox::shared_from_this()
{
	shared_ptr<Component> cmp = Component::shared_from_this();
	return dynamic_pointer_cast<ComboBox>(cmp);
}
int ComboBox::getBaseline(int width, int height)
{
	shared_ptr<Component> selected;
	shared_ptr<ComboBox> comboBoxWp = this->shared_from_this();
	shared_ptr<ComboBox> comboBoxSp = comboBoxWp;

	if ( getRenderingPrototype().get() != NULL )
	{
		selected = getRenderer()->getListCellRendererComponent(static_pointer_cast<List>(comboBoxSp), getRenderingPrototype(), 0, true);
	}
	if ( getModel()->getSize() > 0 )
	{
		selected = getRenderer()->getListCellRendererComponent(static_pointer_cast<List>(comboBoxSp), getModel()->getItemAt(0), 0, true);
	}
	else
	{
		// to do
		shared_ptr<String> xString = new String(L"XXXXXXXXXXX");
		selected = getRenderer()->getListCellRendererComponent(static_pointer_cast<List>(comboBoxSp), static_pointer_cast<Object>(xString), 0, true);
	}
	return getHeight() - getStyle()->getPadding(false, BOTTOM) - selected->getStyle()->getPadding(false, BOTTOM);
}

/**
* @inheritDoc
*/
void ComboBox::laidOut()
{
}

/**
* @inheritDoc
*/
shared_ptr<Rectangle> ComboBox::getVisibleBounds()
{
	return getBounds();
}

/**
* @inheritDoc
*/
void ComboBox::setSelectedIndex(int selection)
{
	List::setSelectedIndex(selection,false);
}

/**
* @inheritDoc
*/
void ComboBox::setSelectedIndex(int selection, bool scroll)
{
	List::setSelectedIndex(selection,false);  // check
}

/**
* @inheritDoc
*/
void ComboBox::pointerHover(shared_ptr<Vector<int> > x, shared_ptr<Vector<int> > y)
{
}

/**
* @inheritDoc
*/
void ComboBox::pointerHoverReleased(shared_ptr<Vector<int> > x, shared_ptr<Vector<int> > y)
{
}

/**
* @inheritDoc
*/
void ComboBox::fireClicked()
{
	shared_ptr<String> dialogUIID = new String(L"ComboBoxPopup");
	shared_ptr<String> dialogTitleUIID = new String(L"");
	popupDialog = Dialog::newV(dialogUIID, dialogTitleUIID);

	/*popupDialog->setDisposeWhenPointerOutOfBounds(true);
	popupDialog->setTransitionInAnimator(CommonTransitions::createEmpty());
	popupDialog->setTransitionOutAnimator(CommonTransitions::createEmpty());*/

	// to check
	shared_ptr<Layout> tempLayout = new BorderLayout();
	popupDialog->setLayout(tempLayout);

	shared_ptr<List> l = createPopupList();
	l->Dispatcher(this->Dispatcher());

	
	l->EventSource(this->shared_from_this());

	popupDialog->addComponent(BorderLayout::CENTER, l);
	shared_ptr<Form> parentForm = getComponentForm();

	// to check
	shared_ptr<Border> nullBorder;
	l->getSelectedStyle()->setBorder(nullBorder);

	popupDialogStyle = popupDialog->getContentPane()->getStyle();
	int listW = min(getWidth() + UIManager::getInstance()->getLookAndFeel()->getVerticalScrollWidth(), parentForm->getContentPane()->getWidth());
	int listH = popupDialog->getContentPane()->getPreferredH() 
		+ popupDialogStyle->getPadding(false, TOP) + popupDialogStyle->getPadding(false, BOTTOM);
	int bottom = 0;
	int top = getAbsoluteY();
	int formHeight = parentForm->getHeight();
	if(parentForm->getSoftButtonCount() > 1) 
	{
		shared_ptr<Component> c = parentForm->getSoftButton(0)->getParent();
		formHeight -= c->getHeight();
		shared_ptr<Style> s = c->getStyle();
		formHeight -= (s->getMargin(TOP) + s->getMargin(BOTTOM));
	}

	if(listH < formHeight) 
	{
		// pop up or down?
		if(top > formHeight / 2) 
		{
			bottom = formHeight - top;
			top = top - listH;
		} else 
		{
			top +=  getHeight();
			bottom = formHeight - top - listH;
		}
	} else 
	{
		top = 0;
	}

	int left = getAbsoluteX();
	int right = parentForm->getWidth() - left - listW;
	if(right < 0)
	{
		left += right;
		right = 0;
	}
	l->DisposeDialogOnSelection (true );
	popupDialog->setBackCommand(popupDialog->CancelMenuItem());
	popupDialog->setScrollable(false);
	if (Display::getInstance()->isThirdSoftButton()) 
	{
		popupDialog->addCommand(popupDialog->SelectMenuItem());
		popupDialog->addCommand(popupDialog->CancelMenuItem());
	} 
	else 
	{
		popupDialog->addCommand(popupDialog->CancelMenuItem());
		popupDialog->addCommand(popupDialog->SelectMenuItem());
	}
	int originalSel = getSelectedIndex();
	int tint = parentForm->getTintColor();
	parentForm->setTintColor(0);
	Form::comboLock = true;
	shared_ptr<Command> result = popupDialog->show(max(top, 0), 
		max(bottom, 0), 
		max(left, 0), 
		max(right, 0), false, false);
	Form::comboLock = false;
	parentForm->setTintColor(tint);
	
	if(result == popupDialog->CancelMenuItem()) 
	{
		setSelectedIndex(originalSel);
	}
}

/**
* Creates the list object used within the popup dialog. This method allows subclasses
* to customize the list creation for the popup dialog shown when the combo box is pressed.
* 
* @return a newly created list object used when the user presses the combo box.
*/
shared_ptr<List> ComboBox::createPopupList()
{
	l = List::newV(getModel());
	l->setSmoothScrolling(isSmoothScrolling());
	l->setFixedSelection(getFixedSelection());
	l->setListCellRenderer(getRenderer());
	l->setItemGap(getItemGap());
	shared_ptr<String> id = new String(L"ComboBoxList");
	l->setUIID(id);
	return l;
}

/**
* @inheritDoc
*/
void ComboBox::keyReleased(int keyCode)
{
	// other events are in keyReleased to prevent the next event from reaching the next form
	int gameAction = Display::getInstance()->getGameAction(keyCode);
	if (gameAction == Display::GAME_FIRE) {
		fireClicked();
		return;
	}
	List::keyPressed(keyCode);
}

/**
* Prevent the combo box from losing selection in some use cases
*/
void ComboBox::selectElement(int selectedIndex)
{
}

/**
* @inheritDoc
*/
void ComboBox::pointerReleased(int x, int y)
{
	if(isEnabled())
	{
		fireClicked();
	}
}

/**
* @inheritDoc
*/
void ComboBox::paint(shared_ptr<Graphics> g)
{
	UIManager::getInstance()->getLookAndFeel()->drawComboBox(g, this->shared_from_this());
}

/**
* @inheritDoc
*/
shared_ptr<Dimension> ComboBox::calcPreferredSize()
{

	return UIManager::getInstance()->getLookAndFeel()->getComboBoxPreferredSize(this->shared_from_this());
}

/**
* @inheritDoc
*/
int ComboBox::getOrientation()
{
	return COMBO;
}
__GUI_END_NAMESPACE
