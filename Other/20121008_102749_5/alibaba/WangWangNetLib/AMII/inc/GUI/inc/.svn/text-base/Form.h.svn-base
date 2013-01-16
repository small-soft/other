#ifndef __GUI_FORM_H__
#define __GUI_FORM_H__

#include "inc/String.h"

#include "inc/Map.h"
#include "inc/Container.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Command;
class Painter;
class ActionListener;
class MenuBar;
class Style;
class Button;
class LookAndFeel;
class Image;
class ActionEvent;
class ListCellRenderer;
class Dialog;
class List;

typedef Map<int,shared_ptr<Vector<shared_ptr<ActionListener> > > >ActionListenerMap;

class Form : public Container,public ActionListener,public SelectionListener
{
	AM_DECLARE_DYNAMIC(Form)	
public:
	static shared_ptr<Form> newV(void);
	static shared_ptr<Form> newV(shared_ptr<String> title);
	virtual ~Form(void);
	shared_ptr<Form> shared_from_this();
protected:
	Form(void);
	void constructV(void);
	void constructV(shared_ptr<String> title);
private:
	void init();
private:
	shared_ptr<Command> selectMenuItem;
	shared_ptr<Command> cancelMenuItem;
	shared_ptr<Painter> glassPane;
	shared_ptr<Container> contentPane;// = new Container(new FlowLayout());
	shared_ptr<Label> title ;//= new Label(L"", "Title");
	shared_ptr<MenuBar> menuBar;// = new MenuBar();//modified by jiajiang for private to protected
	shared_ptr<Command> selectCommand;
	shared_ptr<Command> defaultCommand;
	shared_ptr<Component> dragged;
	shared_ptr<Command> backCommand;
	
	shared_ptr<Command> clearCommand;
	shared_ptr<Vector<shared_ptr<Animation> > >animatableComponents;
	shared_ptr<Vector<shared_ptr<Animation> > > internalAnimatableComponents;
	shared_ptr<Component> lastPointFocused;
	shared_ptr<Component> lastFocused;
public: 
	static bool comboLock;
	static int leftSK ;
	static int rightSK ;
	static int rightSK2;
	static int backSK ;
	static int clearSK ;
	static int backspaceSK ;
private:
	shared_ptr<Component> focused;
	shared_ptr<Vector<shared_ptr<Component> > >mediaComponents;
	shared_ptr<Transition> transitionInAnimator;
	shared_ptr<Transition> transitionOutAnimator;
	shared_ptr<EventDispatcher<ActionListener> > commandListener;
	shared_ptr<EventDispatcher<ActionListener> > pointerPressedListeners;
	shared_ptr<EventDispatcher<ActionListener> > pointerReleasedListeners;
	shared_ptr<EventDispatcher<ActionListener> > pointerDraggedListeners;
	shared_ptr<Form> previousForm;
	bool tint;
	int tintColor;
	shared_ptr<Vector<shared_ptr<Component> > > focusDownSequence;
	shared_ptr<Vector<shared_ptr<Component> > > focusRightSequence;
	shared_ptr<ActionListenerMap> keyListeners;
	shared_ptr<ActionListenerMap> gameKeyListeners;
	bool cyclicFocus;// = true;
	int tactileTouchDuration;
	shared_ptr<Locker>  lock;
	//add for menu
	shared_ptr<Dialog> menuDialog;
	shared_ptr<Command> lastCmd;
	shared_ptr<List> commandList;
// virtual function
public:
	virtual void refreshTheme();
	virtual void initComponentImpl();
	virtual void repaint(shared_ptr<Component> cmp) ;
	virtual void longKeyPress(int keyCode);
	virtual void longPointerPress(int x, int y);
	virtual void keyPressed(int keyCode);
	virtual void keyReleased(int keyCode);
	virtual void pointerPressed(int x, int y);
	virtual void pointerDragged(int x, int y);
	virtual void pointerHoverReleased(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	virtual void pointerHover(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	virtual void paint(shared_ptr<Graphics> g);
	virtual void keyRepeated( int keyCode );
public:
	void selectionChanged(int oldSelected, int newSelected);
	void actionPerformed(shared_ptr<ActionEvent> evt);
	shared_ptr<Command> getSelectMenuItem();
	shared_ptr<Command> getCancelMenuItem();

	void setSoftButtonStyle(shared_ptr<Style> s) ;
	shared_ptr<Style> getSoftButtonStyle();
	void hideNotify();
	void showNotify();
	virtual void sizeChangedInternal(int w, int h) ;
	void setGlassPane(shared_ptr<Painter> glassPane);
	shared_ptr<Painter> getGlassPane();
	shared_ptr<Label> getTitleComponent();
	void setTitleComponent(shared_ptr<Label> title);
	void setTitleComponent(shared_ptr<Label> title, shared_ptr<Transition> t);
	void addKeyListener(int keyCode, shared_ptr<ActionListener> listener);
	void removeKeyListener(int keyCode, shared_ptr<ActionListener> listener);
	void removeGameKeyListener(int keyCode, shared_ptr<ActionListener> listener);
	void addGameKeyListener(int keyCode, shared_ptr<ActionListener> listener);
	int getSoftButtonCount();
	shared_ptr<Button> getSoftButton(int offset);
	shared_ptr<Style> getMenuStyle();
	shared_ptr<Style> getTitleStyle();
	shared_ptr<Form> getPreviousForm();
	virtual void initLaf(shared_ptr<LookAndFeel> laf);
	void clearFocusVectors();
	void setDraggedComponent(shared_ptr<Component> dragged);
	void initFocusRight();
	void initFocusDown();
	void setDefaultCommand(shared_ptr<Command> defaultCommand);
	shared_ptr<Command> getDefaultCommand();
	void setClearCommand(shared_ptr<Command> clearCommand);
	shared_ptr<Command> getClearCommand();
	void setBackCommand(shared_ptr<Command> backCommand);
	shared_ptr<Command> getBackCommand();
	shared_ptr<Container> getContentPane();
	virtual void removeAll();
	void setBgImage(shared_ptr<Image> bgImage);
	virtual void setLayout(shared_ptr<Layout> layout);
	void setTitle(shared_ptr<String> title);
	shared_ptr<String> getTitle();
	virtual void addComponent(shared_ptr<Component> cmp);
	virtual void addComponent(int constraints, shared_ptr<Component> cmp);
	virtual void addComponent(int index, int constraints, shared_ptr<Component> cmp);
	virtual void addComponent( shared_ptr<Component> cmp,int index);
	virtual void replace(shared_ptr<Component> current, shared_ptr<Component> next, shared_ptr<Transition> t);
	virtual void replaceAndWait(shared_ptr<Component> current, shared_ptr<Component> next, shared_ptr<Transition> t);
	virtual void removeComponent(shared_ptr<Component> cmp) ;
	void registerMediaComponent(shared_ptr<Component> mediaCmp);
	bool hasMedia();
	void deregisterMediaComponent(shared_ptr<Component> mediaCmp);
	void registerAnimated(shared_ptr<Animation> cmp);
	void registerAnimatedInternal(shared_ptr<Animation> cmp);
	virtual void deregisterAnimatedInternal(shared_ptr<Animation> cmp);
	void deregisterAnimated(shared_ptr<Animation> cmp);
	int getFocusPosition(shared_ptr<Component> c);
	int getFocusCount();
	void repaintAnimations();
	bool hasAnimations();

	virtual void paintBackground(shared_ptr<Graphics> g);
	shared_ptr<Transition> getTransitionInAnimator();
	void setTransitionInAnimator(shared_ptr<Transition> transitionInAnimator);
	shared_ptr<Transition> getTransitionOutAnimator() ;
	void setTransitionOutAnimator(shared_ptr<Transition> transitionOutAnimator);
	void addCommandListener(shared_ptr<ActionListener> l);
	void removeCommandListener(shared_ptr<ActionListener> l);
	virtual void actionCommand(shared_ptr<Command> cmd) ;
	void dispatchCommand(shared_ptr<Command> cmd, shared_ptr<ActionEvent> ev);
	void actionCommandImpl(shared_ptr<Command> cmd);
	void actionCommandImpl(shared_ptr<Command> cmd, shared_ptr<ActionEvent> ev);
	void initFocused();
	virtual void show();
	virtual void showBack();
	
	virtual void setSmoothScrolling(bool smoothScrolling);
	virtual bool isSmoothScrolling();
	virtual int getScrollAnimationSpeed();
	virtual void setScrollAnimationSpeed(int animationSpeed);
	virtual void onShow();
	void onShowCompleted();
	void showModal(int top, int bottom, int left, int right, bool includeTitle, bool modal, bool reverse) ;
	void showModal(bool reverse);
	void showDialog(bool modal, bool reverse);
	virtual void dispose();
	virtual bool isDisposed();
	void disposeImpl();
	virtual bool isMenu();
	
	virtual shared_ptr<Form> getComponentForm() ;
	void restoreMenu();
	void setFocused(shared_ptr<Component> focused);
	shared_ptr<Component> findFirstFocusable(shared_ptr<Container> c);
	shared_ptr<Component> getFocused();
	
	virtual shared_ptr<Layout> getLayout();

	void addPointerPressedListener(shared_ptr<ActionListener> l);
	void removePointerPressedListener(shared_ptr<ActionListener> l);
	void addPointerReleasedListener(shared_ptr<ActionListener> l);
	void removePointerReleasedListener(shared_ptr<ActionListener> l);
	void addPointerDraggedListener(shared_ptr<ActionListener> l);
	void removePointerDraggedListener(shared_ptr<ActionListener> l);

	bool isSingleFocusMode();
	virtual void pointerReleased(int x, int y);
	virtual void setScrollableY(bool scrollableY);
	virtual void setScrollableX(bool scrollableX);
	virtual int getComponentIndex(shared_ptr<Component> cmp) ;
	void addCommand(shared_ptr<Command> cmd, int offset) ;
	int getCommandCount() ;
	shared_ptr<Command> getCommand(int index);
	void addCommand(shared_ptr<Command> cmd);
	void removeCommand(shared_ptr<Command> cmd);
	void setCyclicFocus(bool cyclicFocus);
	bool isCyclicFocus();
	virtual bool moveScrollTowards(int direction, shared_ptr<Component> c);
	virtual void scrollComponentToVisible(shared_ptr<Component> c);
	void setMenuCellRenderer(shared_ptr<ListCellRenderer> menuCellRenderer);
	void removeAllCommands() ;
	void requestFocus(shared_ptr<Component> cmp);
	void setRTL(bool r);
	
	virtual void setScrollable(bool scrollable);
	virtual void setVisible(bool visible);
	int getTintColor();
	void setTintColor(int tintColor);
	void addSelectCommand(shared_ptr<String> selectText);
	void removeSelectCommand();
	void setMenuTransitions(shared_ptr<Transition> transitionIn, shared_ptr<Transition> transitionOut);
	shared_ptr<Command> showMenuDialog(shared_ptr<Dialog> menu);
	bool isReverseSoftButtons();
	shared_ptr<Component> createCommandComponent(shared_ptr<Vector<shared_ptr<Command> > > commands);
	shared_ptr<Command> getComponentSelectedCommand(shared_ptr<Component> cmp);
	shared_ptr<MenuBar> getMenuBar();
		
	// add by Duan shaopeng
	shared_ptr<Command> SelectMenuItem() const { return selectMenuItem; }
	void SelectMenuItem(shared_ptr<Command> val) { selectMenuItem = val; }
	shared_ptr<Command> CancelMenuItem() const { return cancelMenuItem; }
	void CancelMenuItem(shared_ptr<Command> val) { cancelMenuItem = val; }
	shared_ptr<Component> getLastPointFocused() { return lastPointFocused; }
protected:
	void sizeChanged(int w, int h);
	shared_ptr<Command> createSelectCommand();
	shared_ptr<Command> createMenuSelectCommand();
	shared_ptr<Command> createMenuCancelCommand();
	int calculateTouchCommandGridColumns(shared_ptr<Container> grid);
	shared_ptr<Button> createTouchCommandButton(shared_ptr<Command> c);
	shared_ptr<List> createCommandList(shared_ptr<Vector<shared_ptr<Command> > > commands);
private:
	void addKeyListener(int keyCode, shared_ptr<ActionListener> listener, shared_ptr<ActionListenerMap> keyListeners);
	void removeKeyListener(int keyCode, shared_ptr<ActionListener> listener, shared_ptr<ActionListenerMap> keyListeners);
	void addSortedComponentRight(shared_ptr<Vector<shared_ptr<Component> > > components, shared_ptr<Component> c);
	shared_ptr<Component> findScrollableAncestor(shared_ptr<Component> c) ;
	void addSortedComponentDown(shared_ptr<Vector<shared_ptr<Component> > > components, shared_ptr<Component> c);
	bool isInSameColumn(shared_ptr<Component> source, shared_ptr<Component> dest);
	bool isInSameRow(shared_ptr<Component> source, shared_ptr<Component> dest);
	void addSortedComponent(shared_ptr<Vector<shared_ptr<Component> > > components, shared_ptr<Component> c, bool toTheRight);
	void findAllFocusable(shared_ptr<Container> c, shared_ptr<Vector<shared_ptr<Component> > > v, bool toTheRight);
	void loopAnimations(shared_ptr<Vector<shared_ptr<Animation> > > v, shared_ptr<Vector<shared_ptr<Animation> > > notIn) ;
	void show(bool reverse);
	bool changeFocusState(shared_ptr<Component> cmp, bool gained);
	void fireKeyEvent(shared_ptr<ActionListenerMap> keyListeners, int keyCode) ;
	void tactileTouchVibe(shared_ptr<Component> cmp);
	void updateFocus(int gameAction);

};

__GUI_END_NAMESPACE

#endif
