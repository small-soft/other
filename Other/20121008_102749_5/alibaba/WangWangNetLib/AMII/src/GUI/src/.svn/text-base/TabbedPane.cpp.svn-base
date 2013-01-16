#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
class BorderLayout;
class Style;

AM_IMPLEMENT_DYNAMIC(TabbedPane, Container)

void TabbedPane::TabsPainter::paint( shared_ptr<Graphics> g, shared_ptr<Rectangle> rect )
{
	UIManager::getInstance()->getLookAndFeel()->
	drawTabbedPaneContentPane(tabbedPane, g, rect,
	tabbedPane->tabsList->getPreferredSize(), tabbedPane->tabsList->size(),
	tabbedPane->tabsList->getSelectedIndex(), tabbedPane->tabsList->getElementSize(true, true),
	tabbedPane->tabsList->getScrollX(), tabbedPane->tabsList->getScrollY());
}
void TabbedPane::TabbedSelectionListener::selectionChanged(int oldSelected, int newSelected)
{
	// to check
	shared_ptr<Component> c = dynamic_pointer_cast<Component>( tabbedPane->tabsList->getModel()->getItemAt(newSelected));
	shared_ptr<Transition> t = tabbedPane->transitionLeft;
	if(oldSelected < newSelected)
	{
		t = tabbedPane->transitionRight;
	}
	if(c.get() != NULL )
	{
		if(t.get() == NULL  || tabbedPane->contentPane->getComponentCount() == 0)
		{
			tabbedPane->contentPane->removeAll();

			shared_ptr<Button> buttonKey = dynamic_pointer_cast<Button>(c);
			tabbedPane->contentPane->addComponent(BorderLayout::CENTER, tabbedPane->tabsTable->get(buttonKey));
			if((static_pointer_cast<Component>(tabbedPane))->isInitialized())
			{
				(static_pointer_cast<Container>(tabbedPane))->revalidate();
			} else
			{
				(static_pointer_cast<Container>(tabbedPane))->setShouldCalcPreferredSize(true);
			}
		} else
		{
			tabbedPane->contentPane->flushReplace();

			shared_ptr<Button> buttonKey = dynamic_pointer_cast<Button>(c);
			tabbedPane->contentPane->replace(tabbedPane->contentPane->getComponentAt(0),  
											  tabbedPane->tabsTable->get(buttonKey), t);
		}
	}
}

TabbedPane::TabbedSelectionListener::~TabbedSelectionListener()
{

}
shared_ptr<Component> TabbedPane::TabsRenderer::getListCellRendererComponent(shared_ptr<List> list, shared_ptr<Object> value, int index, bool isSelected)
{            
	// prototype value can cause this
	// to check
	shared_ptr<Button> bt = dynamic_pointer_cast<Button>(value);
	if(value.get() ==  NULL || (bt.get() == NULL))
	{
		shared_ptr<String> title = (dynamic_pointer_cast<Label>(value))->getText();
		shared_ptr<Button> button = Button::newV(title);
		value = static_pointer_cast<Object>(button);
	}
	return UIManager::getInstance()->getLookAndFeel()->getTabbedPaneCell(
		tabbedPane, (dynamic_pointer_cast<Button>( value))->getText(),
		(dynamic_pointer_cast<Button> (value))->getIcon(), isSelected,
		list->hasFocus(), list->getStyle(), list->getSelectedStyle(), tabbedPane->getStyle(),
		list->getScrollX(), list->getScrollY(),
		list->getPreferredSize(), tabbedPane->contentPane->getBounds()->getSize());
}
shared_ptr<Component> TabbedPane::TabsRenderer::getListFocusComponent(shared_ptr<List> list)
{
	shared_ptr<Component> nullComponent;
	return nullComponent;
}
/**
* Creates an empty <code>TabbedPane</code> with the specified tab placement
* of either: <code>Component.TOP</code>, <code>Component.BOTTOM</code>,
* <code>Component.LEFT</code>, or <code>Component.RIGHT</code>.
*
* @param tabPlacement the placement for the tabs relative to the content
*/
void TabbedPane::constructV(int tabPlacement/* = TOP*/)
{
	Container::constructV(new BorderLayout());

	contentPane = Container::newV(new BorderLayout());
	tabsList = List::newV();
	tabsTable = new Map<shared_ptr<Button>, shared_ptr<Component> >();

	this->tabPlacement = -1;
	this->tPBorder = 1;

	shared_ptr<String> id = new String(L"TabbedPane");
	contentPane->setUIID(id);
	
	tabsPainter= new TabbedPane::TabsPainter(this->shared_from_this());
	shared_ptr<Painter> painter = static_pointer_cast<Painter>(tabsPainter);
	contentPane->getStyle()->setBgPainter(painter);

	Container::addComponent(BorderLayout::CENTER, contentPane);

	setTabPlacement(tabPlacement);

	tabsList->getUnselectedStyle()->setPadding(0, 0, 0, 0);
	tabsList->getUnselectedStyle()->setMargin(0, 0, 0, 0);
	shared_ptr<Border> nullBorder;
	tabsList->getUnselectedStyle()->setBorder(nullBorder);
	tabsList->getSelectedStyle()->setPadding(0, 0, 0, 0);
	tabsList->getSelectedStyle()->setMargin(0, 0, 0, 0);
	tabsList->getSelectedStyle()->setBorder(nullBorder);

	cellRender = new TabsRenderer(this->shared_from_this());
	tabsList->setListCellRenderer( cellRender );
	tabsList->setItemGap(0);
	tabsList->setIsScrollVisible(false);
	tabsList->setSmoothScrolling(false);
	tabsList->setBorderGap(0);        

	selectionListener = new TabbedSelectionListener(this->shared_from_this());
	tabsList->addSelectionListener(selectionListener);

}

TabbedPane::~TabbedPane(void)
{
}
shared_ptr<TabbedPane> TabbedPane::shared_from_this()
{
	shared_ptr<Component> cmp = Component::shared_from_this();
	return dynamic_pointer_cast<TabbedPane>(cmp);
}

/**
* @inheritDoc
*/
void TabbedPane::setFocusable(bool b)
{
	if(tabsList.get() != NULL )
	{
		tabsList->setFocusable(b);
	}
	Container::setFocusable(b);
}

/**
* This method adds a listener to the tabs.
* 
* @param listener a selection listener to gets the selection
* events
*/
void TabbedPane::addTabsListener(shared_ptr<SelectionListener> listener)
{
	tabsList->addSelectionListener(listener);
}
/**
* @inheritDoc
*/
void TabbedPane::requestFocus()
{
	tabsList->requestFocus();
}

/**
* @inheritDoc
*/
shared_ptr<Dimension> TabbedPane::calcPreferredSize()
{
	int maxContentW = 0;
	int maxContentH = 0;
	int maxW = 0;
	int maxH = 0;

	for (int i = 0; i < tabsList->size(); i++)
	{
		// to check
		shared_ptr<Object> tabsObject = tabsList->getModel()->getItemAt(i);
		shared_ptr<Component> tabsComp = dynamic_pointer_cast<Component>(tabsObject);

		shared_ptr<Button> tabsButton = dynamic_pointer_cast<Button>(tabsComp);
		shared_ptr<Component> contentComp = tabsTable->get(tabsButton);

		if (contentComp->getPreferredW() > maxContentW)
		{
			maxContentW = contentComp->getPreferredW();
		}
		if (contentComp->getPreferredH() > maxContentH)
		{
			maxContentH = contentComp->getPreferredH();
		}
	}
	if (tabPlacement == TOP || tabPlacement == BOTTOM)
	{
		maxW = maxContentW;
		maxH = tabsList->getPreferredH() + maxContentH;
	} else
	{
		maxW = tabsList->getPreferredW() + maxContentW;
		maxH = maxContentH;
	}
	shared_ptr<Dimension> dimension = new Dimension(maxW, maxH);
	return dimension;
}

/**
* Sets the tab placement for this tabbedpane.
* Possible values are:<ul>
* <li><code>Component.TOP</code>
* <li><code>Component.BOTTOM</code>
* <li><code>Component.LEFT</code>
* <li><code>Component.RIGHT</code>
* </ul>
* The default value, if not set, is <code>Component.TOP</code>.
* 
* @param tabPlacement the placement for the tabs relative to the content
*/
void TabbedPane::setTabPlacement(int tabPlacement)
{
	if (tabPlacement != TOP && tabPlacement != LEFT &&
		tabPlacement != BOTTOM && tabPlacement != RIGHT)
	{
		return;
	}
	if (this->tabPlacement == tabPlacement)
	{
		return;
	}
	this->tabPlacement = tabPlacement;
	removeComponent(tabsList);

	if (tabPlacement == TOP || tabPlacement == BOTTOM)
	{
		tabsList->setOrientation(List::HORIZONTAL);
		if (tabPlacement == TOP) {
			Container::addComponent(BorderLayout::NORTH, tabsList);
		} 
		else if (tabPlacement == BOTTOM)
		{
			Container::addComponent(BorderLayout::SOUTH, tabsList);
		}
	}
	else
	{// LEFT Or RIGHT
		tabsList->setOrientation(List::VERTICAL);
		if (tabPlacement == LEFT)
		{
			Container::addComponent(BorderLayout::WEST, tabsList);
		}
		else
		{// RIGHT
			Container::addComponent(BorderLayout::EAST, tabsList);
		}
	}
	tabsList->setShouldCalcPreferredSize(true);
	contentPane->setShouldCalcPreferredSize(true);

	revalidate();
}

/**
* Adds a <code>component</code> 
* represented by a <code>title</code> and/or <code>icon</code>,
* either of which can be <code>null</code>.
* Cover method for <code>insertTab</code>.
* 
* @param title the title to be displayed in this tab
* @param icon the icon to be displayed in this tab
* @param component the component to be displayed when this tab is clicked
* 
* @see #insertTab
* @see #removeTabAt
*/
void TabbedPane::addTab(shared_ptr<String> title, shared_ptr<Image> icon, shared_ptr<Component> component)
{
	insertTab(title, icon, component, tabsList->size());
}

/**
* Adds a <code>component</code> 
* represented by a <code>title</code> and no <code>icon</code>.
* Cover method for <code>insertTab</code>.
* 
* @param title the title to be displayed in this tab
* @param component the component to be displayed when this tab is clicked
* 
* @see #insertTab
* @see #removeTabAt
*/
void TabbedPane::addTab(shared_ptr<String> title, shared_ptr<Component> component)
{
	shared_ptr<Image> nullImage;
	insertTab(title, nullImage, component, tabsList->size());
}
/**
* Inserts a <code>component</code>, at <code>index</code>,
* represented by a <code>title</code> and/or <code>icon</code>,
* either of which may be <code>null</code>.
* Uses java.util.Vector internally, see <code>insertElementAt</code>
* for details of insertion conventions. 
*
* @param title the title to be displayed in this tab
* @param icon the icon to be displayed in this tab
* @param component The component to be displayed when this tab is clicked.
* @param index the position to insert this new tab 
*
* @see #addTab
* @see #removeTabAt
*/
void TabbedPane::insertTab(shared_ptr<String> title, shared_ptr<Image> icon, shared_ptr<Component> component,
					  int index)
{
	checkIndex(index);
	if (component.get() == NULL)
	{
	  return;
	}
	shared_ptr<String> nullString = new String(L"");
	shared_ptr<Button> b = Button::newV(title.get() != NULL  ? title : nullString, icon);

	(dynamic_pointer_cast<DefaultListModel>(tabsList->getModel()))->addItemAtIndex(b, index);
	tabsTable->put(b, component);

	if (tabsList->size() == 1)
	{
		contentPane->addComponent(BorderLayout::CENTER, component);
	}

}

/**
* Updates the information about the tab details
* 
* @param title the title to be displayed in this tab
* @param icon the icon to be displayed in this tab
* @param index the position to insert this new tab 
*/
void TabbedPane::setTabTitle(shared_ptr<String> title, shared_ptr<Image> icon, int index)
{
	checkIndex(index);
	// to check
	shared_ptr<Button> b = dynamic_pointer_cast<Button>(tabsList->getModel()->getItemAt(index));
	b->setText(title);
	b->setIcon(icon);
	(dynamic_pointer_cast<DefaultListModel>(tabsList->getModel()))->setItem(index, b);
}

/**
* Removes the tab at <code>index</code>.
* After the component associated with <code>index</code> is removed,
* its visibility is reset to true to ensure it will be visible
* if added to other containers.
* @param index the index of the tab to be removed
* @exception IndexOutOfBoundsException if index is out of range 
*            (index < 0 || index >= tab count)
*
* @see #addTab
* @see #insertTab  
*/
void TabbedPane::removeTabAt(int index)
{
	checkIndex(index);

	shared_ptr<Object> key = tabsList->getModel()->getItemAt(index);
	// to check
	(dynamic_pointer_cast<DefaultListModel>( tabsList->getModel()))->removeItem(index);

	shared_ptr<Button> keyButton = dynamic_pointer_cast<Button>(key);
	tabsTable->remove(keyButton);
}

/**
* Returns the tab at <code>index</code>.
* 
* @param index the index of the tab to be removed
* @exception IndexOutOfBoundsException if index is out of range 
*            (index < 0 || index >= tab count)
* @return the component at the given tab location
* @see #addTab
* @see #insertTab  
*/
shared_ptr<Component> TabbedPane::getTabComponentAt(int index)
{
	checkIndex(index);

	// to check
	shared_ptr<Button> button = dynamic_pointer_cast<Button>( tabsList->getModel()->getItemAt(index));
	return tabsTable->get(button);
}

void TabbedPane::checkIndex(int index)
{
	if (index < 0 || index > tabsList->size())
	{
		// to check
		//throw new IndexOutOfBoundsException("Index: " + index);
		return;
	}
}
/**
* Returns the index of the tab for the specified component.
* Returns -1 if there is no tab for this component.
*
* @param component the component for the tab
* @return the first tab which matches this component, or -1
*		if there is no tab for this component
*/
int TabbedPane::indexOfComponent(shared_ptr<Component> component)
{
	for (int i = 0; i < getTabCount(); i++)
	{
		// to check
		shared_ptr<Button> c = dynamic_pointer_cast<Button>( tabsList->getModel()->getItemAt(i));
		shared_ptr<Component> content = tabsTable->get(c);

		if(component == content)
		{
			return i;
		}
	}
	return -1;
}
/**
* Returns the number of tabs in this <code>tabbedpane</code>.
*
* @return an integer specifying the number of tabbed pages
*/
int TabbedPane::getTabCount()
{
	return tabsList->size();
}
/**
* Returns the currently selected index for this tabbedpane.
* Returns -1 if there is no currently selected tab.
*
* @return the index of the selected tab
*/
int TabbedPane::getSelectedIndex()
{
	return tabsList->getSelectedIndex();
}
/**
* The prototype is optionally used in calculating the size of an individual
* tab and is recommended for performance reasons. You should invoke it with a String
* representing the width/height which will be used to calculate
* the size required for each element in the list.\
* <p>This operation is not essential and if it isn't invoked the size of the first
* few tabs is used to determine the overall size of a tab.
* <p>This allows the size calculations to work across look and feels and allows
* developers to predetermin size for the tabs. 
* <p>e.g. For tabs which you would like to always be 5 characters wide
* you can use a prototype "XXXXX" which would use the preferred size of the XXXXX 
* String to determine the size of the tabs..
* 
* @param title a String to determine the size.
*/
void TabbedPane::setTabTitlePrototype(shared_ptr<String> title)
{
	shared_ptr<Object> titleObject = static_pointer_cast<Object>(title);
	tabsList->setRenderingPrototype(titleObject);
}
/**
* @inheritDoc
*/
shared_ptr<String> TabbedPane::toString()
{
	// to check
	/*String className = getClass().getName();
	className = className.substring(className.lastIndexOf('.') + 1);
	return className + "[x=" + getX() + " y=" + getY() + " width=" +
		getWidth() + L" height=" + getHeight() + ", tab placement = " +
		tabPlacement + ", tab count = " + getTabCount() +
		", selected index = " + getSelectedIndex() + "]";*/
	shared_ptr<String> nullString = new String(L"");
	return nullString;
}
/**
* @inheritDoc
*/
void TabbedPane::paint(shared_ptr<Graphics> g)
{
	Container::paint(g);

	UIManager::getInstance()->getLookAndFeel()->drawTabbedPane(g, this->shared_from_this());
}
/**
* Sets the tabs selected style
* @param style
*/
void TabbedPane::setTabsSelectedStyle(shared_ptr<Style> style)
{
	tabsList->setSelectedStyle(style);
}
/**
* Sets the tabs un selected style
* @param style
*/
void TabbedPane::setTabsUnselectedStyle(shared_ptr<Style> unselectedStyle)
{
	tabsList->setUnSelectedStyle(unselectedStyle);
}
/**
* Sets the content pane selected style
* @param style
*/
void TabbedPane::setContentPaneSelectedStyle(shared_ptr<Style> style)
{
	contentPane->setSelectedStyle(style);
}
/**
* Sets the content pane un selected style
* @param style
*/
void TabbedPane::setContentPaneUnselectedStyle(shared_ptr<Style> unselectedStyle)
{
	contentPane->setUnSelectedStyle(unselectedStyle);
}
/**
* @inheritDoc
*/
void TabbedPane::refreshTheme()
{
	shared_ptr<Painter> p = contentPane->getStyle()->getBgPainter();
	Container::refreshTheme();
	contentPane->getStyle()->setBgPainter(p);
	
	Enumeration<shared_ptr<Component> > e = tabsTable->elements();
	while( e.hasMoreElements() )
	{
		shared_ptr<Component> c = e.nextElement();
		c->refreshTheme();
	}
}
/**
* Returns the placement of the tabs for this tabbedpane.
* 
* @return the tab placement value
* @see #setTabPlacement
*/
int TabbedPane::getTabPlacement()
{
	return tabPlacement;
}
/**
* The TabbedPane surrounded border width
* 
* @return The TabbedPane surrounded border width
*/
int TabbedPane::getTabbedPaneBorderWidth()
{
	return tPBorder;
}
/**
* Setting the TabbedPane surrounded border width
* 
* @param tabbedPaneBorderWidth TabbedPane surrounded border width
*/
void TabbedPane::setTabbedPaneBorderWidth(int tabbedPaneBorderWidth)
{
	this->tPBorder = tabbedPaneBorderWidth;
}
/**
* @inheritDoc
*/
void TabbedPane::setPadding(int top, int bottom, int left, int right)
{
	if (contentPane.get() != NULL )
	{
		contentPane->getStyle()->setPadding(top, bottom, left, right);
	}
}
/**
* @inheritDoc
*/
void TabbedPane::setPadding(int orientation, int gap)
{
	if ( contentPane.get() != NULL )
	{
		contentPane->getStyle()->setPadding(orientation, gap);
	}
}
/**
* Sets the selected index for this tabbedpane. The index must be a valid 
* tab index.
* @param index the index to be selected
* @throws IndexOutOfBoundsException if index is out of range 
* (index < 0 || index >= tab count)
*/
void TabbedPane::setSelectedIndex(int index)
{
	if (index < 0 || index >= tabsList->size())
	{
		return;
	}
	tabsList->setSelectedIndex(index);
}

shared_ptr<TabbedPane> TabbedPane::newV( int tabPlacement /*= TOP*/ )
{
	shared_ptr<TabbedPane> pane = new TabbedPane();
	pane->constructV(tabPlacement);
	return pane;
}

TabbedPane::TabbedPane()
{

}
__GUI_END_NAMESPACE
