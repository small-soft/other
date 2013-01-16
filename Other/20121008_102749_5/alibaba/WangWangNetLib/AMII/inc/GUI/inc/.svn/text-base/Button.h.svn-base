
#ifndef __GUI_BUTTON_H__
#define __GUI_BUTTON_H__

#include "inc/Label.h"
#include "inc/Config.h"
#include "inc/String.h"

__GUI_BEGIN_NAMESPACE

class Command;
class Image;
class ActionListener;

class Button:public Label
{
	AM_DECLARE_DYNAMIC(Button)
	
public:
	static shared_ptr<Button> newV(shared_ptr<String> text, shared_ptr<Image> icon);
	static shared_ptr<Button> newV(shared_ptr<Command> cmd);
	static shared_ptr<Button> newV(shared_ptr<String> text = new String(L""));
	virtual ~Button(void);
	shared_ptr<Button> shared_from_this();
protected:
	Button();

	void constructV(shared_ptr<String> text, shared_ptr<Image> icon);
	void constructV(shared_ptr<Command> cmd);
	void constructV(shared_ptr<String> text = new String(L""));

public:
	/**
	* Indicates the rollover state of a button which is equivalent to focused for
	* most uses
	*/
	const static  int STATE_ROLLOVER = 0;

	/**
	* Indicates the pressed state of a button 
	*/
	const static  int STATE_PRESSED = 1;

	/**
	* Indicates the default state of a button which is neither pressed nor focused
	*/
	const static  int STATE_DEFAULT = 2;
private:
	shared_ptr<EventDispatcher<ActionListener> > dispatcher;

	int state;// = STATE_DEFAULT;

	shared_ptr<Image> pressedIcon;

	shared_ptr<Image> rolloverIcon;

	shared_ptr<Command> cmd;

	shared_ptr<Style> pressedStyle;

public:
	virtual void focusGainedInternal();
	virtual void focusLostInternal();
	int getState();
	shared_ptr<Image> getPressedIcon();
	shared_ptr<Image> getRolloverIcon();
	void setRolloverIcon(shared_ptr<Image> rolloverIcon);
	void setPressedIcon(shared_ptr<Image> pressedIcon);
	virtual void checkAnimation();
	void addActionListener(shared_ptr<ActionListener> l);
	void removeActionListener(shared_ptr<ActionListener> l);
	virtual shared_ptr<Image> getIconFromState();
	virtual void fireActionEvent();
	virtual void pressed();
	virtual void released();
	virtual void keyPressed(int keyCode);
	virtual void keyReleased(int keyCode);
	virtual void keyRepeated(int keyCode);
	virtual void fireClicked();
	virtual bool isSelectableInteraction();
	virtual void pointerHover(shared_ptr<Vector<int> > x, shared_ptr<Vector<int> > y);
	virtual void pointerHoverReleased(shared_ptr<Vector<int> > x, shared_ptr<Vector<int> > y);
	virtual void pointerPressed(int x, int y) ;
	virtual void pointerReleased(int x, int y);
	virtual void paint(shared_ptr<Graphics> g);
	virtual shared_ptr<Dimension> calcPreferredSize();
	virtual shared_ptr<Border> getBorder();
	shared_ptr<Style> getPressedStyle();
	void setPressedStyle(shared_ptr<Style> style);
	virtual void refreshTheme(shared_ptr<String> id);
	virtual shared_ptr<Style> getStyle();
	shared_ptr<Command> getCommand();	
	virtual bool isSelected();
	/* for the use of Map<Shared_ptr<Button>, TypeName N> */
	
	bool operator < (Button button2);  
};

__GUI_END_NAMESPACE

#endif
