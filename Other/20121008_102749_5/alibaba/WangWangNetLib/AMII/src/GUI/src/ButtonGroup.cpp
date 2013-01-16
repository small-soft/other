#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

ButtonGroup::ButtonGroup(void) : selectedIndex (-1)
{
	buttons = new Vector<shared_ptr<RadioButton> >;
}

ButtonGroup::~ButtonGroup(void)
{
}

void ButtonGroup::add( shared_ptr<RadioButton> rb )
{
	if(rb.get() ==NULL)
	{
		return;
	}

	if(!buttons->contains(rb))
	{
		buttons->addElement(rb);
		if(rb->isSelected())
		{
			setSelected(buttons->indexOf(rb));
		}
		rb->setGroup(this->shared_from_this());
	}
}

void ButtonGroup::remove( shared_ptr<RadioButton> rb )
{
	if(rb.get() ==NULL)
	{
		return;
	}
	buttons->removeElement(rb);
	if(rb->isSelected())
	{
		clearSelection();
	}
	rb->setGroup(NULL);
}

void ButtonGroup::clearSelection()
{
	if(selectedIndex!=-1)
	{
		if(selectedIndex < buttons->size())
		{
			(buttons->elementAt(selectedIndex))->setSelected(false);
		}
		selectedIndex=-1;
	}
}

int ButtonGroup::getButtonCount()
{
	return buttons->size();
}

bool ButtonGroup::isSelected()
{
	if(selectedIndex!= -1)
	{
		return true;
	}
	return false;
}

int ButtonGroup::getSelectedIndex()
{
	return selectedIndex;
}

shared_ptr<RadioButton> ButtonGroup::getRadioButton( int index )
{
	if(index >=0 && index < getButtonCount())
	{
		return buttons->elementAt(index);
	}
	shared_ptr<RadioButton> nullBtn;
	return nullBtn;
}

void ButtonGroup::setSelected( shared_ptr<RadioButton> rb )
{
	if (rb != NULL)
	{
		int index = buttons->indexOf(rb);
		if(index < 0)
		{
			add(rb);
			index = buttons->indexOf(rb);
		}
		setSelected(index);
	} else
	{
		clearSelection();
	}
}

void ButtonGroup::setSelected( int index )
{
	if(index < 0  ||  index >= getButtonCount() )
	{
		//throw new IllegalArgumentException("Index out of bounds");
		return;
	}
	if(selectedIndex!=-1)
	{
		//unselect last selected Radio button
		(buttons->elementAt(selectedIndex))->setSelectedImpl(false);
	}
	(buttons->elementAt(index))->setSelectedImpl(true);
	selectedIndex=index;
}

__GUI_END_NAMESPACE
