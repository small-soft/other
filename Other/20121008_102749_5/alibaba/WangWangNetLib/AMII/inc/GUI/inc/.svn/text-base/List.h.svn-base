#ifndef __LIST_H__
#define __LIST_H__

#include "inc/Component.h"
#include "inc/DataChangedListener.h"
#include "inc/SelectionListener.h"
#include "inc/EventDispatcher.h"
#include "inc/DefaultListModel.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class ListModel;
class ListCellRenderer;
class ActionListener;
class DefaultListCellRenderer;

class List:public Component
{
	AM_DECLARE_DYNAMIC(List)
	
	class Listeners :public Object,public DataChangedListener,public SelectionListener {
	private:
		List *list;
	public :
		Listeners(List *list);
		void dataChanged(int status, int index);
		void selectionChanged(int oldSelected, int newSelected) ;
	};

public:
	static shared_ptr<List> newV(shared_ptr<VectorArray<shared_ptr<Object> > > items);
	static shared_ptr<List> newV(shared_ptr<Vector<shared_ptr<Object> > > items);
	static shared_ptr<List> newV(shared_ptr<ListModel> model  = new DefaultListModel());
	virtual ~List(void);
	shared_ptr<List> shared_from_this();
protected:
	List();
	void constructV(shared_ptr<VectorArray<shared_ptr<Object> > > items);
	void constructV(shared_ptr<Vector<shared_ptr<Object> > > items);
	void constructV(shared_ptr<ListModel> model);

public:
	/**
	* Indicates the list isn't fixed and that selection is movable
	*/
	static const int FIXED_NONE = 0;
	/**
	* Indicates that the list is not fixed in place but cycles its elements
	*/
	static const int FIXED_NONE_CYCLIC = 1;
	/**
	* Indicates the list selection will only reach the edge when there are no more
	* elements in the list.
	*/
	static const int FIXED_NONE_ONE_ELEMENT_MARGIN_FROM_EDGE = 2;
	/**
	* Allows to test for fixed none
	*/
private:
	static const int FIXED_NONE_BOUNDRY = 9;
	/**
	* Indicates the list selection is fixed into place at the top of the list
	* or at the left of the list
	*/
public:
	static const int FIXED_LEAD = 10;
	/**
	* Indicates the list selection is fixed into place at the bottom of the list
	* or at the right of the list
	*/
	static const int FIXED_TRAIL = 11;
	/**
	* Indicates the list selection is fixed into place at the center of the list
	*/
	static const int FIXED_CENTER = 12;
	static const int COMBO = 2;
private:
	shared_ptr<Object> renderingPrototype;
	int fixedSelection;
	shared_ptr<ListModel> model;
	shared_ptr<DefaultListModel> defaultListModel;
	shared_ptr<DefaultListCellRenderer> defaultRenderer;
	shared_ptr<ListCellRenderer> renderer;// = new DefaultListCellRenderer();
	int orientation;// = VERTICAL;
	shared_ptr<EventDispatcher<ActionListener> > dispatcher;// = new EventDispatcher();
	weak_ptr<Object> eventSource;// = this;
	shared_ptr<Dimension> elemSize;
	shared_ptr<Dimension> selectedElemSize;
	bool inputOnFocus ;//= true;
	bool numericKeyActions;// = true;
	bool paintFocusBehindList;// = true;

	/**
	* Minimum number of elements shown in a list, this member is used to calculate
	* the list preferred size. If the number of elements in the model is smaller than
	* this then this value is used in the calculations.
	*/
	int minElementHeight;// = 0;

	/**
	* Indicates the gap between each item in the list
	*/
	int itemGap;// = 2;
	/**
	* Indicates the surrounding border gap
	*/
	int borderGap ;//= 2;
	shared_ptr<Listeners> listener;
	/**
	* Indicates the position within the current animation, 0 means no animation
	* is in progress
	*/
	int animationPosition;
	int destination;
	shared_ptr<Motion> listMotion;
	bool fireOnClick ;//= true;
	bool fireOnRelease;

	/**
	* Initial x/y positions for the fixed mode drag
	*/
	int initialFixedDrag;
	int initialFixedSelection;

	bool commandList;

	/**
	* Indicates whether the list should not paint the focus component if the list
	* itself has no focus.
	*/
	bool ignoreFocusComponentWhenUnfocused;

	/**
	* Used internally by the combo box
	*/
	bool disposeDialogOnSelection;

	/**
	* Indicates that the background of a cell renderer might mutate between one entry and the next,
	* it is recommended that this flag remains false for performance reasons.
	*/
	bool mutableRendererBackgrounds;

	/**
	* This flag indicates if the List should automatically scroll to the
	* selected element when it's been initialized.
	*/
	bool scrollToSelected;// = true;
public:
	/**
	* Indicates the list orientation is VERTICAL
	*/
	static const int VERTICAL = 0;
	/**
	* Indicates the list orientation is HORIZONTAL
	*/
	static const int HORIZONTAL = 1;
public:
	virtual void initComponentImpl();
	virtual void deinitializeImpl() ;
	virtual bool isScrollableY();
	virtual bool isScrollableX();
	int getMinElementHeight();
	void setMinElementHeight(int minElementHeight);
	int size();
	int getSelectedIndex();
	void setSelectedIndex(int index);
	void setSelectedIndex(int index, bool scrollToSelection);
	shared_ptr<Object> getSelectedItem();
	void setSelectedItem(shared_ptr<Object> item);
	shared_ptr<ListModel> getModel();
	void dataChanged(int status, int index);
	void setModel(shared_ptr<ListModel> model);
	bool isNumericKeyActions();
	void setNumericKeyActions(bool numericKeyActions);
	bool isCommandList();
	void setCommandList(bool commandList);
	bool isIgnoreFocusComponentWhenUnfocused();
	void setIgnoreFocusComponentWhenUnfocused(bool ignoreFocusComponentWhenUnfocused);
	bool isMutableRendererBackgrounds();
	void setMutableRendererBackgrounds(bool mutableRendererBackgrounds);
	void setListCellRenderer(shared_ptr<ListCellRenderer> renderer);
	shared_ptr<ListCellRenderer> getRenderer();
	virtual int getOrientation();
	virtual void refreshTheme();
	void setOrientation(int orientation);
	virtual void scrollRectToVisible(shared_ptr<Rectangle> rect);
	void setHandlesInput(bool b);
	void setHandlesInputParent(bool b);
	virtual void keyReleased(int keyCode);
	virtual void keyPressed(int keyCode);
	virtual void paint(shared_ptr<Graphics> g);
	void addSelectionListener(shared_ptr<SelectionListener> l) ;
	void removeSelectionListener(shared_ptr<SelectionListener> l);
	void addActionListener(shared_ptr<ActionListener> l);
	void removeActionListener(shared_ptr<ActionListener> l);
	void setInputOnFocus(bool inputOnFocus);
	void setPaintFocusBehindList(bool paintFocusBehindList);
	virtual void focusGainedInternal();
	virtual void focusLostInternal() ;
	int getItemGap();
	void setItemGap(int itemGap);
	void setRenderingPrototype(shared_ptr<Object> renderingPrototype);
	shared_ptr<Object> getRenderingPrototype();
	shared_ptr<Dimension> getElementSize(bool selected, bool addMargin);
	virtual void pointerDragged(int x, int y) ;
	void setFireOnClick(bool fireOnClick);
	virtual void pointerPressed(int x, int y) ;
	virtual void pointerHover(shared_ptr<Vector<int> > x,shared_ptr<Vector<int> > y);
	virtual void pointerHoverReleased(shared_ptr<Vector<int> > x,shared_ptr<Vector<int> > y);
	virtual void pointerReleased(int x, int y);
	virtual shared_ptr<Dimension> calcPreferredSize();
	void addItem(shared_ptr<Object> item);
	int getFixedSelection();
	void setFixedSelection(int fixedSelection);
	virtual void deregisterAnimatedInternal();
	virtual bool animate();
	void setBorderGap(int borderGap);
	int getBorderGap() ;
	void setScrollToSelected(bool scrollToSelected);

	shared_ptr<EventDispatcher<ActionListener> > Dispatcher() const { return dispatcher; }
	void Dispatcher(shared_ptr<EventDispatcher<ActionListener> > val) { dispatcher = val; }
	shared_ptr<Object> EventSource() const { return eventSource; }
	void EventSource(shared_ptr<Object> val) { eventSource = val; }
	bool DisposeDialogOnSelection() const { return disposeDialogOnSelection; }
	void DisposeDialogOnSelection(bool val) { disposeDialogOnSelection = val; }
	virtual void setShouldCalcPreferredSize(bool shouldCalcPreferredSize);

	virtual void fireActionEvent();
	virtual void selectElement(int selectedIndex);
	virtual void laidOut();

//protected:
	
	void modelChanged(int status, int index);
	void listSelectionChanged(int oldSelected, int newSelected);
	virtual shared_ptr<Rectangle> getVisibleBounds();
	virtual void fireClicked();
	virtual bool isSelectableInteraction();
	
	virtual void longPointerPress(int x, int y);


private:
	void bindListeners();
	
	void updateAnimationPosition(int direction);
	void initListMotion();
	void calculateComponentPosition(int index, int defaultWidth, shared_ptr<Rectangle> rect, shared_ptr<Dimension> rendererSize, shared_ptr<Dimension> selectedSize, bool beforeSelected);
	int recalcOffset(int offset, int totalSize, int viewSize, int componentSize);
	void paintFocus(shared_ptr<Graphics> g, int width, shared_ptr<Rectangle> pos, shared_ptr<Dimension> rendererSize);
	void renderComponent(shared_ptr<Graphics> g, shared_ptr<Component> cmp, int x, int y, int width, int height) ;
	void renderComponentBackground(shared_ptr<Graphics> g, shared_ptr<Component> cmp, int x, int y, int width, int height);
	shared_ptr<Dimension> calculateElementSize(bool selected, bool addMargin) ;
	void pointerDraggedImpl(int x, int y);
	int pointerSelect(int x, int y);
	void pointerReleasedImpl(int x, int y, bool isHover);
};

__GUI_END_NAMESPACE

#endif
