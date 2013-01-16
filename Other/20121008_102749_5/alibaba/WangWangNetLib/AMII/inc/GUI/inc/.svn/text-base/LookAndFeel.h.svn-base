#ifndef __LOOK_AND_FEEL_H__
#define __LOOK_AND_FEEL_H__

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
class Image;
class TextArea;
class TextField;
class TabbedPane;
class ListCellRenderer;
class Button;
class List;
class Label;
class Dimension;
class Style;
class Rectangle;


class LookAndFeel: public Object
{
public:
	LookAndFeel();
	virtual ~LookAndFeel();
private:
	shared_ptr<Component> verticalScroll;
	shared_ptr<Component> horizontalScroll;
	shared_ptr<Component> verticalScrollThumb;
	shared_ptr<Component> horizontalScrollThumb;

	/**
	* Right-To-Left. Default false.
	*/
	bool rtl;

	long tickerSpeed;// = 50;
	/**
	* Tint color is set when a form is partially covered be it by a menu or by a 
	* dialog. A look and feel can override this default value.
	*/
	int defaultFormTintColor ;//= 0x77000000;
	/**
	* This color is used to paint disable mode.
	*/
	int disableColor;// = 0xcccccc;
	/**
	* This member allows us to define a default animation that will draw the transition for
	* entering a form
	*/
	shared_ptr<Transition> defaultFormTransitionIn;
	/**
	* This member allows us to define a default animation that will draw the transition for
	* exiting a form
	*/
	shared_ptr<Transition> defaultFormTransitionOut;
	/**
	* This member allows us to define a default animation that will draw the transition for
	* entering a menu
	*/
	shared_ptr<Transition> defaultMenuTransitionIn;
	
	/**
	* This member allows us to define a default animation that will draw the transition for
	* exiting a menu
	*/
	shared_ptr<Transition> defaultMenuTransitionOut;

	/**
	* This member allows us to define a default animation that will draw the transition for
	* entering a dialog
	*/
	shared_ptr<Transition> defaultDialogTransitionIn;
	/**
	* This member allows us to define a default animation that will draw the transition for
	* exiting a form
	*/
	shared_ptr<Transition> defaultDialogTransitionOut;
	/**
	* Indicates whether lists and containers should have smooth scrolling by default
	*/
	bool defaultSmoothScrolling;// = true;
	/**
	* Indicates the default speed for smooth scrolling
	*/
	int defaultSmoothScrollingSpeed;// = 150;
	/**
	* Indicates whether softbuttons should be reversed from their default orientation
	*/
	bool reverseSoftButtons;
	/**
	* This renderer is assigned to all Forms Menu's by default.
	*/
	shared_ptr<ListCellRenderer> menuRenderer;
	shared_ptr<VectorArray<shared_ptr<Image> > > menuIcons;

	/**
	* Indicates whether the menu UI should target a touch based device or a
	* standard cell phone
	*/
	bool touchMenus;

	/**
	* Allows defining a tactile touch device that vibrates when the user presses a component
	* that should respond with tactile feedback on a touch device (e.g. vibrate).
	* Setting this to 0 disables tactile feedback completely
	*/
	int tactileTouchDuration;// = 0;

public:
	virtual void bind(shared_ptr<Component> cmp);
	virtual void uninstall() ;
	virtual void drawButton(shared_ptr<Graphics> g, shared_ptr<Button> b) = 0;
	virtual void drawCheckBox(shared_ptr<Graphics> g, shared_ptr<Button> cb) = 0;
	virtual void drawComboBox(shared_ptr<Graphics> g, shared_ptr<List> cb) = 0;
	virtual void drawLabel(shared_ptr<Graphics> g, shared_ptr<Label> l) = 0;
	virtual void drawList(shared_ptr<Graphics> g, shared_ptr<List> l) = 0;
	virtual void drawRadioButton(shared_ptr<Graphics> g, shared_ptr<Button> rb) = 0;
	virtual void drawTextArea(shared_ptr<Graphics> g, shared_ptr<TextArea> ta) =0;
	virtual void drawTextField(shared_ptr<Graphics> g, shared_ptr<TextField> ta) = 0;
	virtual void drawTextFieldCursor(shared_ptr<Graphics> g, shared_ptr<TextArea> ta) = 0;
	virtual void drawTabbedPane(shared_ptr<Graphics> g, shared_ptr<TabbedPane> tp) = 0;
	virtual shared_ptr<Dimension> getButtonPreferredSize(shared_ptr<Button> b) = 0;
	virtual shared_ptr<Dimension> getCheckBoxPreferredSize(shared_ptr<Button> cb) = 0;
	virtual shared_ptr<Dimension> getLabelPreferredSize(shared_ptr<Label> l) = 0;
	virtual shared_ptr<Dimension> getListPreferredSize(shared_ptr<List> l) = 0;
	virtual shared_ptr<Dimension> getRadioButtonPreferredSize(shared_ptr<Button> rb)=0;
	virtual shared_ptr<Dimension> getTextAreaSize(shared_ptr<TextArea> ta, bool pref) = 0;
	virtual shared_ptr<Dimension> getTextFieldPreferredSize(shared_ptr<TextArea> ta) = 0;
	virtual shared_ptr<Dimension> getComboBoxPreferredSize(shared_ptr<List> box) = 0;
	void drawVerticalScroll(shared_ptr<Graphics> g, shared_ptr<Component> c, float offsetRatio, float blockSizeRatio) ;
	void drawHorizontalScroll(shared_ptr<Graphics> g, shared_ptr<Component> c, float offsetRatio, float blockSizeRatio) ;
	void setFG(shared_ptr<Graphics> g, shared_ptr<Component> c);
	int getVerticalScrollWidth();
	int getHorizontalScrollHeight();
	virtual  shared_ptr<Component> getTabbedPaneCell(shared_ptr<TabbedPane> tp,
		shared_ptr<String> text,  shared_ptr<Image> icon,  bool isSelected,
		bool cellHasFocus,  shared_ptr<Style> cellStyle, shared_ptr<Style> cellSelectedStyle,
		shared_ptr<Style> tabbedPaneStyle,  int cellOffsetX,
		int cellOffsetY, shared_ptr<Dimension> cellsPreferredSize,
		shared_ptr<Dimension> contentPaneSize) = 0;
	virtual void drawTabbedPaneContentPane( shared_ptr<TabbedPane> tp,
		shared_ptr<Graphics> g,  shared_ptr<Rectangle> rect,
		shared_ptr<Dimension> cellsPreferredSize,  int numOfTabs,
		int selectedTabIndex,  shared_ptr<Dimension> tabsSize,
		int cellOffsetX,  int cellOffsetY) = 0;
	shared_ptr<Transition> getDefaultFormTransitionIn();
	void setDefaultFormTransitionIn(shared_ptr<Transition> defaultFormTransitionIn);
	shared_ptr<Transition> getDefaultFormTransitionOut();
	void setDefaultFormTransitionOut(shared_ptr<Transition> defaultFormTransitionOut);
	shared_ptr<Transition> getDefaultDialogTransitionIn();
	void setDefaultDialogTransitionIn(shared_ptr<Transition> defaultDialogTransitionIn) ;
	shared_ptr<Transition> getDefaultDialogTransitionOut();
	void setDefaultDialogTransitionOut(shared_ptr<Transition> defaultDialogTransitionOut) ;
	int getDefaultFormTintColor();
	void setDefaultFormTintColor(int defaultFormTintColor);
	int getDisableColor();
	void setDisableColor(int disableColor);
	bool isDefaultSmoothScrolling();
	void setDefaultSmoothScrolling(bool defaultSmoothScrolling);
	int getDefaultSmoothScrollingSpeed();
	void setDefaultSmoothScrollingSpeed(int defaultSmoothScrollingSpeed);
	bool isReverseSoftButtons();
	void setReverseSoftButtons(bool reverseSoftButtons);
	shared_ptr<ListCellRenderer> getMenuRenderer();
	void setMenuRenderer(shared_ptr<ListCellRenderer> menuRenderer) ;
	void setMenuIcons(shared_ptr<Image> select, shared_ptr<Image> cancel, shared_ptr<Image> menu);
	shared_ptr<VectorArray<shared_ptr<Image> > > getMenuIcons();
	long getTickerSpeed();
	void setTickerSpeed(long tickerSpeed);
	void refreshTheme();
	bool isTouchMenus();
	void setTouchMenus(bool touchMenus) ;
	void setRTL(bool rtl);
	bool isRTL();
	int getTactileTouchDuration() ;
	void setTactileTouchDuration(int tactileTouchDuration);
	shared_ptr<Transition> getDefaultMenuTransitionIn() const { return defaultMenuTransitionIn; }
	void setDefaultMenuTransitionIn(shared_ptr<Transition> val) { defaultMenuTransitionIn = val; }
	shared_ptr<Transition> getDefaultMenuTransitionOut() const { return defaultMenuTransitionOut; }
	void setDefaultMenuTransitionOut(shared_ptr<Transition> val) { defaultMenuTransitionOut = val; }
private:
	void drawScroll(shared_ptr<Graphics> g, shared_ptr<Component> c, float offsetRatio,
		float blockSizeRatio, bool isVertical, int x, int y, int width, int height,
		shared_ptr<Component> scroll, shared_ptr<Component> scrollThumb);
	void initScroll();
};
__GUI_END_NAMESPACE

#endif
