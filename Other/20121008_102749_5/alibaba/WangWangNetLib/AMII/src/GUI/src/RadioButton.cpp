#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

AM_IMPLEMENT_DYNAMIC(RadioButton, Button)

RadioButton::RadioButton(void) : selected (false)
{
}

RadioButton::~RadioButton(void)
{
}

void RadioButton::constructV( shared_ptr<String> text)
{
	shared_ptr<Image> nullImage;
	constructV(text, nullImage);
}

void RadioButton::constructV( shared_ptr<Image> icon )
{
	constructV(new String(L""), icon);
}

void RadioButton::constructV( shared_ptr<String> text, shared_ptr<Image> icon )
{
	Button::constructV(text, icon);
	setUIID(new String(L"RadioButton"));
}

shared_ptr<RadioButton> RadioButton::newV( shared_ptr<String> text /*= new String*/ )
{
	shared_ptr<RadioButton> self = new RadioButton();
	self->constructV(text);
	return self;
}

shared_ptr<RadioButton> RadioButton::newV( shared_ptr<Image> icon )
{
	shared_ptr<RadioButton> self = new RadioButton();
	self->constructV(icon);
	return self;
}

shared_ptr<RadioButton> RadioButton::newV( shared_ptr<String> text, shared_ptr<Image> icon )
{
	shared_ptr<RadioButton> self = new RadioButton();
	self->constructV(text, icon);
	return self;
}

shared_ptr<String> RadioButton::toString()
{
	shared_ptr<String> radioBtn = new String(L"Radio Button ");
	shared_ptr<String> res = &(*radioBtn + *getText());
	return res;
}

int RadioButton::getAvaliableSpaceForText()
{
	shared_ptr<LookAndFeel> l = UIManager::getInstance()->getLookAndFeel();
	shared_ptr<DefaultLookAndFeel> defaultLookAndFeel = dynamic_pointer_cast<DefaultLookAndFeel>(l);
	if(defaultLookAndFeel != NULL)
	{
		shared_ptr<VectorArray<shared_ptr<Image> > > rButtonImages = defaultLookAndFeel->getRadioButtonImages();
		if (rButtonImages != NULL)
		{
			int index = isSelected() ? 1 : 0;
			return Button::getAvaliableSpaceForText() - ((*rButtonImages)[index])->getWidth();
		}
	}
	return Button::getAvaliableSpaceForText() - (getHeight() + getGap());
}

bool RadioButton::isSelected()
{
	return selected;
}

void RadioButton::setSelectedImpl( bool selected )
{
	this->selected = selected;
	repaint();
}

void RadioButton::setSelected( bool selected )
{
	setSelectedImpl(selected);
	if(group.get() != NULL && selected)
	{
		group->setSelected(this->shared_from_this());
	}
}

void RadioButton::released()
{
	// prevent the radio button from being "turned off"
	if(!isSelected())
	{
		setSelected(true);
	}
	Button::released();
}

void RadioButton::paint( shared_ptr<Graphics> g )
{
	UIManager::getInstance()->getLookAndFeel()->drawRadioButton(g, this->shared_from_this());
}

shared_ptr<Dimension> RadioButton::calcPreferredSize()
{
	return UIManager::getInstance()->getLookAndFeel()->getRadioButtonPreferredSize(this->shared_from_this());
}

void RadioButton::setGroup( shared_ptr<ButtonGroup> group )
{
	this->group = group;
}

void RadioButton::fireActionEvent()
{
	if(group.get() != NULL)
	{
		group->setSelected(this->shared_from_this());
	}
	Button::fireActionEvent();
}

shared_ptr<RadioButton> RadioButton::shared_from_this()
{
	shared_ptr<Button> btn = Button::shared_from_this();
	return dynamic_pointer_cast<RadioButton>(btn);
}
__GUI_END_NAMESPACE
