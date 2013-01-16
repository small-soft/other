#ifndef __GUI_COMPONENT_H__
#define __GUI_COMPONENT_H__

#include "inc/Animation.h"
#include "inc/StyleListener.h"
#include "inc/Map.h"
#include "inc/Vector.h"
#include "inc/Locker.h"
//#include "inc/EventDispatcher.h"
#include "inc/String.h"
#include "inc/Object.h"

__GUI_BEGIN_NAMESPACE
class Dimension;
class Rectangle;
class Container;
class Motion;
class Label;
class FocusListener;
class Form;
class Border;
template<class N> class EventDispatcher;

class Component : public Object, public  Animation, public  StyleListener,public enable_shared_from_this<Component>
{
	AM_DECLARE_DYNAMIC(Component)	
protected:
	Component(void);
public:
	virtual ~Component(void);
private:
	shared_ptr<String> selectText;// = UIManager.getInstance().localize(L"select", "Select");
	/**
	* Allows us to determine which component will receive focus next when traversing 
	* with the down key
	*/
	shared_ptr<Component> nextFocusDown;
	shared_ptr<Component> nextFocusUp;
	/**
	* Indicates whether component is enabled or disabled
	*/
	bool enabled;// = true;
	/**
	* Allows us to determine which component will receive focus next when traversing 
	* with the right key
	*/
	shared_ptr<Component> nextFocusRight;
	shared_ptr<Component> nextFocusLeft;

	/**
	* Indicates whether the component should "trigger" tactile touch when pressed by the user
	* in a touch screen UI.
	*/
	bool tactileTouch;

	/**
	* Baseline resize behavior constant used to properly align components. 
	* Indicates as the size of the component
	* changes the baseline remains a fixed distance from the top of the
	* component.
	* @see #getBaselineResizeBehavior
	*/
public:
	static const int BRB_CONSTANT_ASCENT = 1;
	/**
	* Baseline resize behavior constant used to properly align components. Indicates as the size of the component
	* changes the baseline remains a fixed distance from the bottom of the 
	* component.
	* @see #getBaselineResizeBehavior
	*/
	static const  int BRB_CONSTANT_DESCENT = 2;
	/**
	* Baseline resize behavior constant used to properly align components. Indicates as the size of the component
	* changes the baseline remains a fixed distance from the center of the
	* component.
	* @see #getBaselineResizeBehavior
	*/
	static const  int BRB_CENTER_OFFSET = 3;
	/**
	* Baseline resize behavior constant used to properly align components. Indicates as the size of the component
	* changes the baseline can not be determined using one of the other
	* constants.
	* @see #getBaselineResizeBehavior
	*/
	static const int BRB_OTHER = 4;

	/**
	* Used as an optimization to mark that this component is currently being
	* used as a cell renderer
	*/
protected:
	shared_ptr<Style> unSelectedStyle;
private:
	bool visible;// = true;
	bool cellRenderer;
	shared_ptr<Rectangle> bounds;// = new Rectangle(0, 0, new Dimension(0, 0));
	//WeakReference painterBounds;
	int scrollX;
	int scrollY; //modified by jiajing for protected
	bool sizeRequestedByUser;// = false;
	shared_ptr<Dimension> preferredSizeD;
	bool scrollSizeRequestedByUser ;//= false;
	shared_ptr<Dimension> scrollSize;
	
	shared_ptr<Style> selectedStyle;
	/*shared_ptr<Container>*/weak_ptr<Container> parent; // for cycle use
	bool focused;// = false;
	bool focusPainted;// = true;
	shared_ptr<EventDispatcher<FocusListener> > focusListeners;// = new EventDispatcher();
	bool isHandlesInput;// = false;
	bool shouldCalcPreferredSize;// = true;
	bool shouldCalcScrollSize;// = true;
	bool focusable;// = true;
	bool scrollVisible;// = true;
	/**
	* Indicates that moving through the component should work as an animation
	*/
	bool smoothScrolling;
	/**
	* Animation speed in milliseconds allowing a developer to slow down or accelerate
	* the smooth animation mode
	*/
	int animationSpeed;
	shared_ptr<Motion> animationMotion;
	shared_ptr<Motion> draggedMotion;
	/**
	* Allows us to flag a drag operation in action thus preventing the mouse pointer
	* release event from occurring.
	*/
	bool dragActivated;
	int initialScrollY ;//= -1;
	int destScrollY ;//= -1;
	int lastScrollY;
	int lastScrollX;

	/**
	* Indicates if the component is in the initialized state, a component is initialized
	* when its initComponent() method was invoked. The initMethod is invoked before showing the
	* component to the user.
	*/
	bool initialized;

public:
	/**
	* Indicates a Component center alignment
	*/
	static const int CENTER = 4;
	/** 
	* Box-orientation constant used to specify the top of a box.
	*/
	static const int TOP = 0;
	/** 
	* Box-orientation constant used to specify the left side of a box.
	*/
	static const int LEFT = 1;
	/** 
	* Box-orientation constant used to specify the bottom of a box.
	*/
	static const int BOTTOM = 2;
	/** 
	* Box-orientation constant used to specify the right side of a box.
	*/
	static const int RIGHT = 3;
private :
	shared_ptr<Map<String,shared_ptr<Object> > > clientProperties;
	shared_ptr<Rectangle> dirtyRegion;// = null;
	shared_ptr<Locker> dirtyRegionLock;// = new Object();
	shared_ptr<Label> componentLabel;
	shared_ptr<String> id;

	/**
	* Is the component a bidi RTL component
	*/
	bool rtl;
private:
	void initStyle();
public:
	 int getX();
	 int getY();
	 bool isVisible();
	 shared_ptr<Object> getClientProperty(shared_ptr<String> key);
	 void putClientProperty(shared_ptr<String>key,shared_ptr<Object> value);
	 shared_ptr<Rectangle> getDirtyRegion() const;
	 void setDirtyRegion(shared_ptr<Rectangle> dirty);
	 virtual void setVisible(bool visible);
	 int getWidth();
	 int getHeight() ;
	 void setX(int x);
	 void setY(int y);
	 virtual int getBaseline(int width, int height);
	 virtual int getBaselineResizeBehavior();
	 void setPreferredSize(shared_ptr<Dimension> d);
	 shared_ptr<Dimension> getPreferredSize();
	 shared_ptr<Dimension> getPreferredSizeWithMargin();
	 shared_ptr<Dimension> getScrollDimension();
	 void setScrollSize(shared_ptr<Dimension> d);
	 void setPreferredW(int preferredW);
	 void setPreferredH(int preferredH);
	 int getPreferredW();
	 int getPreferredH(); 
	 virtual void setWidth(int width);
	 virtual void setHeight(int height);
	 virtual void setSize(shared_ptr<Dimension> d);
	 virtual shared_ptr<String> getUIID();

	shared_ptr<Container> getParent();
	void setParent(shared_ptr<Container> parent);
	 void addFocusListener(weak_ptr<FocusListener> l);
	 void removeFocusListener(weak_ptr<FocusListener> l);

	 void setSelectCommandText(shared_ptr<String> selectText);
	shared_ptr<String> getSelectCommandText();
	 void fireFocusLost(shared_ptr<Component> cmp) ;
	 virtual void fireActionEvent();
	void setLabelForComponent(shared_ptr<Label> componentLabel);
	
	 void paintBackgrounds(shared_ptr<Graphics> g);
	 int getAbsoluteX();
	 int getAbsoluteY();
	 void paintInternal(shared_ptr<Graphics> );
	 void paintInternal(shared_ptr<Graphics> , bool paintIntersects);
	 void paintComponent(shared_ptr<Graphics> );
	 void paintComponent(shared_ptr<Graphics> , bool background);
	 virtual void paint(shared_ptr<Graphics>  g);
	 virtual bool isScrollableX();
	 virtual bool isScrollableY();
	 int getScrollX() ;
	 int getScrollY();
	 int getBottomGap();
	 int getSideGap();
	 bool contains(int x, int y);
	 bool isFocusable();
	 void setFocusable(bool focusable);
	 bool isFocusPainted();
	 void setFocusPainted(bool focusPainted);
	 bool handlesInput();
	 void setHandlesInput(bool handlesInput);
	 bool hasFocus();
	 void setFocus(bool focused);
	

	 virtual int getScrollAnimationSpeed();
	 virtual void setScrollAnimationSpeed(int animationSpeed);
	 virtual bool isSmoothScrolling();
	 virtual void setSmoothScrolling(bool smoothScrolling);	
	 void clearDrag();	
	virtual shared_ptr<Style> getStyle();
	shared_ptr<Style> getUnselectedStyle();
	shared_ptr<Style> getSelectedStyle();
	virtual void setUnSelectedStyle(shared_ptr<Style> style);
	virtual void setSelectedStyle(shared_ptr<Style> style);
	virtual void requestFocus();
	
	shared_ptr<Style> mergeStyle(shared_ptr<Style> toMerge, shared_ptr<Style> newStyle);
	bool isDragActivated();
	void setDragActivated(bool dragActivated);
	
	virtual void deregisterAnimatedInternal();
	virtual bool animate();
	bool isBorderPainted();

	bool isCellRenderer();
	bool isScrollVisible();
	void setIsScrollVisible(bool isScrollVisible);
	
	virtual void styleChanged(shared_ptr<String> propertyName, shared_ptr<Style> source);
	shared_ptr<Component> getNextFocusDown();
	void setNextFocusDown(shared_ptr<Component> nextFocusDown);
	shared_ptr<Component> getNextFocusUp() ;
	void setNextFocusUp(shared_ptr<Component> nextFocusUp);
	shared_ptr<Component> getNextFocusLeft(); 
	void setNextFocusLeft(shared_ptr<Component> nextFocusLeft);
	shared_ptr<Component> getNextFocusRight();
	void setNextFocusRight(shared_ptr<Component> nextFocusRight);
	bool isEnabled();
	void setEnabled(bool enabled);
	bool isRTL();
	void setRTL(bool rtl);
	bool isTactileTouch();
	void setTactileTouch(bool tactileTouch);

	shared_ptr<Rectangle> getBounds();
	
	virtual void laidOut();
	virtual void fireClicked() ;
	bool isScrollable();
	bool isInitialized();
	
public:
	virtual shared_ptr<Rectangle> getVisibleBounds();
	virtual void repaint();
	virtual void focusGainedInternal();
	virtual void focusLostInternal();
	virtual void fireFocusGained() ;
	virtual void fireFocusLost();
	virtual void fireFocusGained(shared_ptr<Component> cmp);
	virtual shared_ptr<Form> getComponentForm();
	virtual void setShouldCalcPreferredSize(bool shouldCalcPreferredSize);
	virtual void repaint(shared_ptr<Component>cmp);
	virtual void setUIID(shared_ptr<String> id);
	
	virtual void repaint(int x, int y, int w, int h);
	virtual void keyPressed(int keyCode);
	virtual void keyReleased(int keyCode);
	virtual void keyRepeated(int keyCode) ;
	virtual void checkAnimation();
	virtual void refreshTheme();
	virtual void setCellRenderer(bool cellRenderer);
	virtual void initComponentImpl();
	virtual void deinitializeImpl();
	virtual void pointerHoverReleased(shared_ptr<VectorArray<int> > x,shared_ptr<VectorArray<int> > y);
	virtual void pointerDragged(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	virtual void pointerDragged(int x, int y);
	virtual void pointerPressed(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	virtual void pointerPressed(int x, int y);
	virtual void pointerReleased(shared_ptr<VectorArray<int> > x,shared_ptr<VectorArray<int> > y);
	virtual void pointerReleased(int x, int y);
	virtual void longKeyPress(int keyCode);
	virtual void longPointerPress(int x, int y) ;
	virtual void refreshTheme(shared_ptr<String> id);
	virtual void pointerHover(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	virtual shared_ptr<Dimension> calcPreferredSize();
	virtual shared_ptr<Dimension> calcScrollSize();

	virtual bool isSelectableInteraction();
	virtual void focusGained();
	virtual void focusLost();
	virtual void paintScrollbars(shared_ptr<Graphics> g);
	virtual void paintScrollbarX(shared_ptr<Graphics> g) ;
	virtual void paintScrollbarY(shared_ptr<Graphics> g) ;
	virtual shared_ptr<Border> getBorder();
	virtual void paintBackground(shared_ptr<Graphics> g);

	virtual void setScrollX(int scrollX);
	virtual void setScrollY(int scrollY);

	virtual void scrollRectToVisible(shared_ptr<Rectangle> rect, shared_ptr<Component> coordinateSpace) ;
	virtual void scrollRectToVisible(int x, int y, int width, int height, shared_ptr<Component> coordinateSpace); 
	virtual void paintBorder(shared_ptr<Graphics> g);

	virtual void deinitialize();
	virtual void initComponent();
	 
	virtual void setInitialized(bool initialized);
	virtual void onEditComplete(shared_ptr<String> text);
	virtual void initCustomStyle(shared_ptr<Style> s);
	virtual void deinitializeCustomStyle(shared_ptr<Style> s);
private:
	void paintIntersectingComponentsAbove(shared_ptr<Graphics> g);
	void drawPainters(shared_ptr<Graphics> g, shared_ptr<Component>  par, shared_ptr<Component> c,int x, int y, int w, int h);
	shared_ptr<Dimension> preferredSize() ;
	void setAnimationMotion(shared_ptr<Motion> motion);
	shared_ptr<Motion> getAnimationMotion();
	void initScrollMotion();
	void pointerReleaseImpl(int x, int y);
// add by jiajing
private:
	bool canLeftRight;// = true;
	bool canUpDown;// = true;
	bool scrollToVisible;// = true;
public:
	void setScrollToVisible(bool b);
	void setLeftRight(bool b);
	void setUpDown(bool b);
	bool getLeftRight();
	bool getUpDown();
	int getAbsoluteYModified();
	bool pointerPressedVerticalScroll(int x,int y);
	void scrollBottom();
	void scrollTop();
};

__GUI_END_NAMESPACE

#endif
