#ifndef __GUI_BUTTONGROUP_H__
#define __GUI_BUTTONGROUP_H__

#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE

class ButtonGroup : public enable_shared_from_this<ButtonGroup>
{
public:
	ButtonGroup(void);
	virtual ~ButtonGroup(void);

public:
	void add(shared_ptr<RadioButton> rb);
	void remove(shared_ptr<RadioButton> rb);
	void clearSelection();
	int getButtonCount();
	bool isSelected();
	int getSelectedIndex();
	shared_ptr<RadioButton> getRadioButton(int index);
	void setSelected(shared_ptr<RadioButton> rb);
	void setSelected(int index);

private:
	shared_ptr<Vector<shared_ptr<RadioButton> > > buttons;// = new java.util.Vector();
	int selectedIndex;//=-1;
};

__GUI_END_NAMESPACE

#endif
