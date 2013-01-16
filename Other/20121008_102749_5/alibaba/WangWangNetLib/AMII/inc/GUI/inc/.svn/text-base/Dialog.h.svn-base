#ifndef __GUI_DIALOG_H__
#define __GUI_DIALOG_H__

#include "inc/Form.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Dialog :public Form
{
	AM_DECLARE_DYNAMIC(Dialog)

public:
	static shared_ptr<Dialog> newV(shared_ptr<String> dialogUIID, shared_ptr<String> dialogTitleUIID);
	static shared_ptr<Dialog> newV(shared_ptr<String> title);
	static shared_ptr<Dialog> newV();

	virtual ~Dialog(void);
	shared_ptr<Dialog> shared_from_this();
	
protected:	
	Dialog();
	void constructV(shared_ptr<String> dialogUIID, shared_ptr<String> dialogTitleUIID);
	void constructV(shared_ptr<String> title);
	void constructV();
private:
	/**
	* Indicates whether the dialog has been disposed
	*/
	bool disposed;
public:
	/**
	* Constant indicating the type of alert to indicate the sound to play or
	* icon if none are explicitly set
	*/
	static const int TYPE_ALARM = 1;
	/**
	* Constant indicating the type of alert to indicate the sound to play or
	* icon if none are explicitly set
	*/
	static const int TYPE_CONFIRMATION = 2;
	/**
	* Constant indicating the type of alert to indicate the sound to play or
	* icon if none are explicitly set
	*/
	static const int TYPE_ERROR = 3;
	/**
	* Constant indicating the type of alert to indicate the sound to play or
	* icon if none are explicitly set
	*/
	static const int TYPE_INFO = 4;
	/**
	* Constant indicating the type of alert to indicate the sound to play or
	* icon if none are explicitly set
	*/
	static const int TYPE_WARNING = 5;
private:
	/**
	* Indicates the time in which the alert should be disposed
	*/
	long time;
	/**
	* Indicates the last command selected by the user in this form
	*/
	shared_ptr<Command> lastCommandPressed;
	/**
	* Indicates that this is a menu preventing getCurrent() from ever returning this class
	*/
	bool menu;
	shared_ptr<String> dialogUIID;
	shared_ptr<String> dialogTitleUIID;
	int dialogType;
	int top;// = -1;
	int bottom;
	int left;
	int right;
	bool includeTitle;
	int position;

	/**
	* Indicates whether LWUIT should try to automatically adjust a showing dialog size
	* when a screen size change event occurs
	*/
	static bool autoAdjustDialogSize;// = true;

	/**
	* Default screen orientation position for the upcoming dialog. By default
	* the dialog will be shown at hardcoded coordinates, this method allows us 
	* to pack the dialog appropriately in one of the border layout based locations
	* see BorderLayout for futher details.
	*/
	static int defaultDialogPosition;

	/**
	* Allows a developer to indicate his interest that the dialog should no longer
	* scroll on its own but rather rely on the scrolling properties of internal 
	* scrollable containers. This flag only affects the static show methods within
	* this class.
	*/
	static bool disableStaticDialogScrolling;

	/**
	* Determines whether the execution of a command on this dialog implicitly 
	* disposes the dialog. This defaults to true which is a sensible default for
	* simple dialogs.
	*/
	bool autoDispose;// = true;

	bool modal;// = true;

	/**
	* The default type for dialogs
	*/
	static int defaultDialogType;// = TYPE_INFO;

	/**
	* Places commands as buttons at the bottom of the standard static dialogs rather than
	* as softbuttons. This is especially appropriate for devices such as touch devices and
	* devices without the common softbuttons (e.g. blackberries). 
	* The default value is false
	*/
	static bool commandsAsButtons;

	bool disposeWhenPointerOutOfBounds;// = false;

	bool paintBG;// = false;
	bool preFormTint;// = false;
	shared_ptr<Rectangle> bgRect;// = null;
public:
	bool isPaintBG();
	void setPaintBG(bool b);
	bool getPreFormTint();
	void setPreFormTint(bool b);
	shared_ptr<Rectangle> getBGRect();
	void setBGRect(shared_ptr<Rectangle> r);
	void setDialogStyle(shared_ptr<Style> style);
	shared_ptr<Style> getDialogStyle();
	virtual void initLaf(shared_ptr<LookAndFeel> laf);
	shared_ptr<Command> show(int top, int bottom, int left, int right, bool includeTitle);
	shared_ptr<Command> show(int top, int bottom, int left, int right, bool includeTitle, bool modal);
	void setTimeout(long time);
	static bool show(shared_ptr<String> title, shared_ptr<String> text, int type, shared_ptr<Image> icon, shared_ptr<String> okText, shared_ptr<String> cancelText) ;
	virtual void sizeChangedInternal(int w, int h);
	static bool show(shared_ptr<String> title, shared_ptr<String> text, int type, shared_ptr<Image> icon, shared_ptr<String> okText, shared_ptr<String> cancelText, long timeout) ;
	static shared_ptr<Command> show(shared_ptr<String> title, shared_ptr<String> text,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout) ;
	static shared_ptr<Command> show(shared_ptr<String> title, shared_ptr<String> text, shared_ptr<Command> defaultCommand,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout);
	static shared_ptr<Command> show(shared_ptr<String> title, shared_ptr<String> text,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout, shared_ptr<Transition> transition);
	static shared_ptr<Command> show(shared_ptr<String> title, shared_ptr<String> text, shared_ptr<Command> defaultCommand,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout, shared_ptr<Transition> transition);
	static bool show(shared_ptr<String> title, shared_ptr<String> text, shared_ptr<String> okText, shared_ptr<String> cancelText);
	static shared_ptr<Command> show(shared_ptr<String> title, shared_ptr<Component> body,  shared_ptr<Vector<shared_ptr<Command> > > cmds);
	static shared_ptr<Command> show(shared_ptr<String> title, shared_ptr<Component> body,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon) ;
	static shared_ptr<Command> show(shared_ptr<String> title, shared_ptr<Component> body,  shared_ptr<Vector<shared_ptr<Command> > > cmds, const int type, shared_ptr<Image> icon, long timeout);
	static shared_ptr<Command> show(shared_ptr<String> title, shared_ptr<Component> body,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout, shared_ptr<Transition> transition);
	static shared_ptr<Command> show(shared_ptr<String> title, shared_ptr<Component> body, shared_ptr<Command> defaultCommand, shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout, shared_ptr<Transition> transition);

	virtual void show();
	virtual void showBack();
	void showModeless();
	shared_ptr<Command> showPacked(int position, bool modal);
	virtual void dispose();
	shared_ptr<Command> showDialog();
	virtual bool animate();
	virtual bool isMenu() ;
	void setMenu(bool menu);
	void addSelectCommand();
	virtual bool isDisposed();
	void setDisposed(bool disposed);
	bool isAutoDispose();
	void setAutoDispose(bool autoDispose);
	static void setDefaultDialogPosition(int p);
	static int getDefaultDialogPosition();
	int getDialogType();
	void setDialogType(int dialogType);
	static void setDefaultDialogType(int d);
	static int getDefaultDialogType() ;
	static void setAutoAdjustDialogSize(bool a);
	static void setDisableStaticDialogScrolling(bool d);
	static bool isDisableStaticDialogScrolling() ;
	static void setCommandsAsButtons(bool c);
	static bool isCommandsAsButtons() ;
	void setDisposeWhenPointerOutOfBounds(bool disposeWhenPointerOutOfBounds);
	virtual void pointerReleased(int x, int y);
	virtual void actionCommand(shared_ptr<Command> cmd);

protected:
	virtual void onShow();
	
private:
	void showImpl(bool reverse) ;
	bool isTimedOut();

};

__GUI_END_NAMESPACE

#endif
