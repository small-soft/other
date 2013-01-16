#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "inc/Object.h"
#include "inc/String.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class LWUITImplementation;
class Graphics;
class Animation;
class Runnable;
class Component;
class Form;
class Transition;
class Locker;
class Thread;

class Display:public Object
{
private:
	Display(void);
public:	
	virtual ~Display(void);
public:
	typedef void *(* F)(void *);
	/**
	* Unknown keyboard type is the default indicating the software should try
	* to detect the keyboard type if necessary
	*/
	static const int KEYBOARD_TYPE_UNKNOWN = 0;

	/**
	* Numeric keypad keyboard type
	*/
	static const int KEYBOARD_TYPE_NUMERIC = 1;

	/**
	* Full QWERTY keypad keyboard type, even if a numeric keyboard also exists
	*/
	static const int KEYBOARD_TYPE_QWERTY = 2;

	/**
	* Touch device without a physical keyboard that should popup a keyboad
	*/
	static const int KEYBOARD_TYPE_VIRTUAL = 3;

	/**
	* Half QWERTY which needs software assistance for completion
	*/
	static const int KEYBOARD_TYPE_HALF_QWERTY = 4;

private:
	static const int POINTER_PRESSED = 1;
	static const int POINTER_RELEASED = 2;
	static const int POINTER_DRAGGED = 3;
	static const int POINTER_HOVER = 8;
	static const int POINTER_HOVER_RELEASED = 11;
	static const int KEY_PRESSED = 4;
	static const int KEY_RELEASED = 5;
	static const int KEY_LONG_PRESSED = 6;
	static const int SIZE_CHANGED = 7;
	static const int HIDE_NOTIFY = 9;
	static const int SHOW_NOTIFY = 10;


	shared_ptr<Graphics> lwuitGraphics;

	/**
	* Indicates whether this is a touch device
	*/
	bool touchScreen;

	/**
	* Indicates the maximum drawing speed of no more than 10 frames per second
	* by default (this can be increased or decreased) the advantage of limiting
	* framerate is to allow the CPU to perform other tasks besides drawing.
	* Notice that when no change is occurring on the screen no frame is drawn and
	* so a high/low FPS will have no effect then.
	*/
	int framerateLock;// = 20;

	/**
	* Light mode allows the UI to adapt and show less visual effects/lighter versions
	* of these visual effects to work properly on low end devices.
	*/
	bool lightMode;
public:
	/**
	* Game action for fire
	*/
	static const int GAME_FIRE = 8;

	/**
	* Game action for left key
	*/
	static const int GAME_LEFT = 2;

	/**
	* Game action for right key
	*/
	static const int GAME_RIGHT = 5;

	/**
	* Game action for UP key
	*/
	static const int GAME_UP = 1;

	/**
	* Game action for down key
	*/
	static const int GAME_DOWN = 6;

	/**
	* An attribute that encapsulates '#' int value.
	*/
	static const int KEY_POUND = '#';

//public:
//	shared_ptr<Display> INSTANCE;// = new Display();

private:
	static shared_ptr<Display> INSTANCE;// = new Display();
	static int transitionDelay ;//= -1;

	shared_ptr<LWUITImplementation> impl;

	bool lwuitRunning;// = false;


	/**
	* Contains the call serially pending elements
	*/
	shared_ptr<Vector<shared_ptr<Runnable> > > pendingSerialCalls;// = new Vector();

	/**
	* This is the instance of the EDT used internally to indicate whether
	* we are executing on the EDT or some arbitrary thread
	*/ 
	shared_ptr<Thread> edt; 

	/**
	* Contains animations that must be played in full by the EDT before anything further
	* may be processed. This is useful for transitions/intro's etc... that animate without
	* user interaction.
	*/
	shared_ptr<Vector<shared_ptr<Animation> > > animationQueue;

	/**
	* Indicates whether the 3rd softbutton should be supported on this device
	*/
	bool thirdSoftButton; //= false;

	bool editingText;
public:
	/**
	* Ignore all calls to show occurring during edit, they are discarded immediately
	*/
	static const int SHOW_DURING_EDIT_IGNORE = 1;

	/**
	* If show is called while editing text in the native text box an exception is thrown
	*/
	static const int SHOW_DURING_EDIT_EXCEPTION = 2;

	/**
	* Allow show to occur during edit and discard all user input at this moment
	*/
	static const int SHOW_DURING_EDIT_ALLOW_DISCARD = 3;

	/**
	* Allow show to occur during edit and save all user input at this moment
	*/
	static const int SHOW_DURING_EDIT_ALLOW_SAVE = 4;

	/**
	* Show will update the current form to which the OK button of the text box
	* will return
	*/
	static const int SHOW_DURING_EDIT_SET_AS_NEXT = 5;
	static shared_ptr<Locker> lock;// = new Object();
	static shared_ptr<Locker> lockThread;
private :
	int showDuringEdit;

	/**
	* Events to broadcast on the EDT
	*/
	shared_ptr<Vector<shared_ptr<VectorArray<int> > > >inputEvents;// = new Vector();

	bool longPointerCharged;
	int pointerX, pointerY;
	bool keyRepeatCharged;
	bool longPressCharged;
	long longKeyPressTime;
	int longPressInterval ;//= 800;
	long nextKeyRepeatEvent;
	int keyRepeatValue;
	int keyRepeatInitialIntervalTime;// = 800;
	int keyRepeatNextIntervalTime ;//= 10;
	bool keyReleasedSinceEdit;

	bool processingSerialCalls;

	int PATHLENGTH;
	shared_ptr<VectorArray<float> > dragPathX;
	shared_ptr<VectorArray<float> > dragPathY;
	shared_ptr<VectorArray<long> > dragPathTime;
	int dragPathOffset;// = 0;
	int dragPathLength;// = 0;
	int lastInputEvent;// = -1;
	int lastInputKeyCode;// = -1;
	bool hide ;//= false;
	long time;
	int lastKeyPressed;
public:
	static shared_ptr<Display> getInstance();
	static void initStatic();
	static void deinitialize();
	int getDisplayWidth();
	int getDisplayHeight();
	float getDragSpeed(bool yAxis);
	int getLastInputEvent();
	int getLastKeyCode();
	void setHide(bool b);
	shared_ptr<Vector<shared_ptr<Animation> > > getAnimationQueue();
	static void init( void* m);
	int getDragStartPercentage();
	void setDragStartPercentage(int dragStartPercentage);
	shared_ptr<LWUITImplementation> getImplementation();
	void setFramerate(int rate);
	void vibrate(int duration) ;
	void flashBacklight(int duration);
	void setShowDuringEditBehavior(int showDuringEdit);
	int getShowDuringEditBehavior();
	int getFrameRate();
	bool isEdt() ;
	void playDialogSound(const int type);
	void callSerially(shared_ptr<Runnable> r);
	void callSeriallyAndWait(shared_ptr<Runnable> r);
	void flushEdt();
	void mainEDTLoop(); 
	void edtLoopImpl();
	bool hasNoSerialCallsPending();
	void onEditingComplete(shared_ptr<Component> c, shared_ptr<String> text);
	void processSerialCalls();
	bool isProcessingSerialCalls();
	void notifyDisplay();
	void invokeAndBlock(shared_ptr<Runnable> r);
	bool isTouchScreenDevice();
	void setTouchScreenDevice(bool touchScreen);
	void setCurrent(shared_ptr<Form> newForm, bool reverse);
	void setCurrentForm(shared_ptr<Form> newForm);
	void setTransitionYield(int transitionD);
	void editString(shared_ptr<Component> cmp, int maxSize, int constraint, shared_ptr<String> text);
	bool minimizeApplication();
	bool isMinimized();
	void restoreMinimizedApplication();
	void addInputEvent(shared_ptr<VectorArray<int> > ev);

	shared_ptr<VectorArray<int> > createKeyEvent(int keyCode, bool pressed);
	void keyPressed(const int keyCode);
	void keyReleased(const int keyCode);
	void keyRepeatedInternal(const int keyCode);
	void pointerDragged(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	void pointerHover(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	void pointerHoverReleased( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	void pointerPressed( shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	void pointerReleased(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	void sizeChanged(int w, int h);
	shared_ptr<VectorArray<int> > createSizeChangedEvent(int w, int h);
	void hideNotify();
	void showNotify();
	bool shouldEDTSleepNoFormAnimation();
	bool shouldEDTSleep();
	shared_ptr<Object> getVideoControl(shared_ptr<Object> player);
	shared_ptr<Form> getCurrentInternal();
	shared_ptr<Form> getCurrentUpcoming() ;
	shared_ptr<Form> getCurrentUpcomingForm(bool includeMenus);
	shared_ptr<Form> getCurrent();
	int numAlphaLevels();
	int numColors();
	bool isLightMode();
	void setLightMode(bool lightMode);
	void repaint(shared_ptr<Animation> cmp);
	int getGameAction(int keyCode);
	int getKeyCode(int gameAction);
	bool isThirdSoftButton();
	void setThirdSoftButton(bool thirdSoftButton);
	void setShowVirtualKeyboard(bool show);
	bool isVirtualKeyboardShowing();
	bool isVirtualKeyboardShowingSupported();
	int getKeyboardType();
	bool isNativeInputSupported();
	bool isMultiTouch();
	bool isClickTouchScreen();
	bool isBidiAlgorithm();
	void setBidiAlgorithm(bool activate);
	shared_ptr<String> convertBidiLogicalToVisual(shared_ptr<String> s);
	int getCharLocation(shared_ptr<String> source, int index);
	bool isRTL(char c);
	shared_ptr<InputStream> getResourceAsStream(shared_ptr<String> resource);
private:
	void restoreMenu(shared_ptr<Form> f);
	void paintTransitionAnimation();
	void initTransition(shared_ptr<Transition> transition, shared_ptr<Form> source, shared_ptr<Form> dest);
	void updateDragSpeedStatus(shared_ptr<VectorArray<int> > ev);
	void handleEvent(shared_ptr<VectorArray<int> > ev) ;
	shared_ptr<VectorArray<int> > pointerEvent(int off, shared_ptr<VectorArray<int> > event);
	shared_ptr<VectorArray<int> > createPointerEvent(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y, int eventType);
public :
	static void* thread_run(void*);


};


__GUI_END_NAMESPACE

#endif
