/**
* Checkbox is a button that can be selected or deselected, and which displays
* its state to the user.
* 
* @author
*/

#ifndef __GUI_CHECK_BOX_H__
#define __GUI_CHECK_BOX_H__

#include "inc/Button.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE

class Dimension;
class CheckBox : public Button
{
	AM_DECLARE_DYNAMIC(CheckBox)
	
public:
	static shared_ptr<CheckBox> newV(shared_ptr<String> text = new String(L""));
	static shared_ptr<CheckBox> newV(shared_ptr<Image> icon);
	static shared_ptr<CheckBox> newV(shared_ptr<String> text, shared_ptr<Image> icon);

	virtual ~CheckBox(void);
	shared_ptr<CheckBox> shared_from_this();
protected:

	CheckBox(void);

	void constructV(shared_ptr<String> text);
	void constructV(shared_ptr<Image> icon);
	void constructV(shared_ptr<String> text,shared_ptr<Image> icon);

	


private:
	bool selected;

public:
	/**
	* Return true if the checkbox is selected
	* 
	* @return true if the checkbox is selected
	*/
	virtual bool isSelected();
	
	/**
	* Selects the current checkbox
	* 
	* @param selected value for selection
	*/
	virtual void setSelected(bool selected);

	/**
	* @inheritDoc
	*/
	virtual void released();
	
	/**
	* @inheritDoc
	*/
    virtual void paint(shared_ptr<Graphics> g);
	
	virtual int getAvaliableSpaceForText();
//protected:
	/**
	* @inheritDoc
	*/
	virtual shared_ptr<Dimension> calcPreferredSize();

};

__GUI_END_NAMESPACE

#endif

