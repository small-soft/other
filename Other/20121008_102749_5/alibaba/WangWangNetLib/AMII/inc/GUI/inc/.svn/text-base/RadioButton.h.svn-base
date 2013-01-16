#ifndef __GUI_RADIOBUTTON_H__
#define __GUI_RADIOBUTTON_H__

#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE

class ButtonGroup;

class RadioButton :
	public Button
{
	AM_DECLARE_DYNAMIC(RadioButton)

public:
	static shared_ptr<RadioButton> newV(shared_ptr<String> text = new String(L""));
	static shared_ptr<RadioButton> newV(shared_ptr<Image> icon);
	static shared_ptr<RadioButton> newV(shared_ptr<String> text, shared_ptr<Image> icon);

	shared_ptr<RadioButton> shared_from_this();

public:
	virtual ~RadioButton(void);

	virtual shared_ptr<String> toString();
	int getAvaliableSpaceForText();
	bool isSelected();
	void setSelectedImpl(bool selected);
	void setSelected(bool selected);
	void released();
	void paint(shared_ptr<Graphics> g);
	void setGroup(shared_ptr<ButtonGroup> group);
	void fireActionEvent();

protected:
	RadioButton(void);

	void constructV(shared_ptr<String> text);
	void constructV(shared_ptr<Image> icon);
	void constructV(shared_ptr<String> text, shared_ptr<Image> icon);

	shared_ptr<Dimension> calcPreferredSize();

private:
	bool selected;//= false;
	weak_ptr<ButtonGroup> group;
};

__GUI_END_NAMESPACE

#endif
