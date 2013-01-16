#ifndef __TABBED_PANE_H__
#define __TABBED_PANE_H__

#include "inc/Config.h"
#include "inc/Container.h"
#include "inc/ListCellRenderer.h"
#include "inc/Map.h"
#include "inc/SelectionListener.h"
#include "inc/String.h"
#include "inc/Painter.h"
__GUI_BEGIN_NAMESPACE
class Transition;
class List;
class SelectionListener;
class ListCellRenderer;
class Image;
class Button;

class TabbedPane : public Container
{
	AM_DECLARE_DYNAMIC(TabbedPane)

public:
	class TabsPainter : public Painter
	{
	public:
		TabsPainter(shared_ptr<TabbedPane> tabsTable) { this->tabbedPane = tabsTable; }

		virtual ~TabsPainter() {;}
		virtual void paint(shared_ptr<Graphics> g, shared_ptr<Rectangle> rect);
	private:
		weak_ptr<TabbedPane> tabbedPane;
	};

	class TabbedSelectionListener: public SelectionListener
	{
	public:
		TabbedSelectionListener(shared_ptr<TabbedPane> tabbedPane) { this->tabbedPane = tabbedPane; }
		virtual void selectionChanged(int oldSelected, int newSelected);
		virtual ~TabbedSelectionListener();
	private:
		weak_ptr<TabbedPane> tabbedPane;
	};

	class TabsRenderer : public ListCellRenderer
	{
	public:
		TabsRenderer(shared_ptr<TabbedPane> tabbedPane) { this->tabbedPane = tabbedPane; }
		virtual ~TabsRenderer(){}

		shared_ptr<Component> getListCellRendererComponent(shared_ptr<List> list, shared_ptr<Object> value, int index, bool isSelected);
		shared_ptr<Component> getListFocusComponent(shared_ptr<List> list);
	private:
		weak_ptr<TabbedPane> tabbedPane;
	};

public:
	/**
	* Creates an empty <code>TabbedPane</code> with the specified tab placement
	* of either: <code>Component.TOP</code>, <code>Component.BOTTOM</code>,
	* <code>Component.LEFT</code>, or <code>Component.RIGHT</code>.
	*
	* @param tabPlacement the placement for the tabs relative to the content
	*/
	static shared_ptr<TabbedPane> newV(int tabPlacement = TOP);
	virtual ~TabbedPane(void);
	shared_ptr<TabbedPane> shared_from_this();
protected:
	TabbedPane();
	void constructV(int tabPlacement);
public:
	/**
	* Indicates the transition to use when switching between tabs from right to left. 
	* 
	* @param transitionLeft transition to use when switching tabs or null to avoid transition
	*/
	virtual void setTransitionLeft(shared_ptr<Transition> transitionLeft) { transitionLeft = transitionLeft; }
	/**
	* Indicates the transition to use when switching between tabs from right to left. 
	* 
	* @return the transition towards the left direction
	*/
	virtual shared_ptr<Transition> getTransitionLeft() { return transitionLeft; }
	/**
	* Indicates the transition to use when switching between tabs from left to right. 
	* 
	* @param transitionRight transition to use when switching tabs or null to avoid transition
	*/
	virtual void setTransitionRight(shared_ptr<Transition> transitionRight) { transitionRight = transitionRight; }
	/**
	* Indicates the transition to use when switching between tabs from left to right. 
	* 
	* @return the transition towards the right direction
	*/
	virtual shared_ptr<Transition> getTransitionRight() { return transitionRight; }
	/**
	* @inheritDoc
	*/
	virtual void setFocusable(bool b);
	/**
	* This method adds a listener to the tabs.
	* 
	* @param listener a selection listener to gets the selection
	* events
	*/
	virtual void addTabsListener(shared_ptr<SelectionListener> listener);
	/**
	* @inheritDoc
	*/
	virtual void requestFocus();
	/**
	* @inheritDoc
	*/
	virtual shared_ptr<Dimension> calcPreferredSize();
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
	virtual void setTabPlacement(int tabPlacement);
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
	virtual void addTab(shared_ptr<String> title, shared_ptr<Image> icon, shared_ptr<Component> component);
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
	virtual void insertTab(shared_ptr<String> title, shared_ptr<Image> icon, shared_ptr<Component> component, int index);
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
	virtual void addTab(shared_ptr<String> title, shared_ptr<Component> component);
	/**
	* Updates the information about the tab details
	* 
	* @param title the title to be displayed in this tab
	* @param icon the icon to be displayed in this tab
	* @param index the position to insert this new tab 
	*/
	virtual void setTabTitle(shared_ptr<String> title, shared_ptr<Image> icon, int index);
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
	virtual void removeTabAt(int index);
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
	virtual shared_ptr<Component> getTabComponentAt(int index);
	/**
	* Returns the index of the tab for the specified component.
	* Returns -1 if there is no tab for this component.
	*
	* @param component the component for the tab
	* @return the first tab which matches this component, or -1
	*		if there is no tab for this component
	*/
	virtual int indexOfComponent(shared_ptr<Component> component);
	/**
	* Returns the number of tabs in this <code>tabbedpane</code>.
	*
	* @return an integer specifying the number of tabbed pages
	*/
	virtual int getTabCount();
	/**
	* Returns the currently selected index for this tabbedpane.
	* Returns -1 if there is no currently selected tab.
	*
	* @return the index of the selected tab
	*/
	virtual int getSelectedIndex();
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
	virtual void setTabTitlePrototype(shared_ptr<String> title);
	/**
	* @inheritDoc
	*/
	virtual shared_ptr<String> toString();
	/**
	* @inheritDoc
	*/
	virtual void paint(shared_ptr<Graphics> g);
	/**
	* Sets the tabs selected style
	* @param style
	*/
	virtual void setTabsSelectedStyle(shared_ptr<Style> style);
	/**
	* Sets the tabs un selected style
	* @param style
	*/
	virtual void setTabsUnselectedStyle(shared_ptr<Style> unselectedStyle);
	/**
	* Sets the content pane selected style
	* @param style
	*/
	virtual void setContentPaneSelectedStyle(shared_ptr<Style> style);
	/**
	* Sets the content pane un selected style
	* @param style
	*/
	virtual void setContentPaneUnselectedStyle(shared_ptr<Style> unselectedStyle);
	/**
	* @inheritDoc
	*/
	virtual void refreshTheme();
	/**
	* Returns the placement of the tabs for this tabbedpane.
	* 
	* @return the tab placement value
	* @see #setTabPlacement
	*/
	virtual int getTabPlacement();
	/**
	* The TabbedPane surrounded border width
	* 
	* @return The TabbedPane surrounded border width
	*/
	virtual int getTabbedPaneBorderWidth();
	/**
	* Setting the TabbedPane surrounded border width
	* 
	* @param tabbedPaneBorderWidth TabbedPane surrounded border width
	*/
	virtual void setTabbedPaneBorderWidth(int tabbedPaneBorderWidth);
	/**
	* @inheritDoc
	*/
	virtual void setPadding(int top, int bottom, int left, int right);
	/**
	* @inheritDoc
	*/
	virtual void setPadding(int orientation, int gap);
	/**
	* Sets the selected index for this tabbedpane. The index must be a valid 
	* tab index.
	* @param index the index to be selected
	* @throws IndexOutOfBoundsException if index is out of range 
	* (index < 0 || index >= tab count)
	*/
	virtual void setSelectedIndex(int index);

private:
	void checkIndex(int index);

private:
	shared_ptr<Transition> transitionRight;
	shared_ptr<Transition> transitionLeft;
	shared_ptr<Container> contentPane; // = new Container(new BorderLayout());
	shared_ptr<List> tabsList; // = new List();
	shared_ptr<Map<shared_ptr<Button>, shared_ptr<Component> > > tabsTable; // = new Hashtable();

	int tabPlacement; // = -1;
	int tPBorder; // = 1;

	shared_ptr<TabbedPane::TabsPainter> tabsPainter;
	shared_ptr<ListCellRenderer> cellRender;
	shared_ptr<TabbedSelectionListener> selectionListener;


};

__GUI_END_NAMESPACE

#endif
