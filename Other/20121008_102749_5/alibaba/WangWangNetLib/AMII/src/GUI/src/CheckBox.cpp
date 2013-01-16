/**
* Checkbox is a button that can be selected or deselected, and which displays
* its state to the user.
* 
* @author
*/

#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

AM_IMPLEMENT_DYNAMIC(CheckBox, Button)


shared_ptr<CheckBox> CheckBox::newV(shared_ptr<String> text)
{
	shared_ptr<CheckBox> self = new CheckBox();
	self->constructV(text);
	return self;
}
shared_ptr<CheckBox> CheckBox::newV(shared_ptr<Image> icon)
{
	shared_ptr<CheckBox> self = new CheckBox();
	self->constructV(icon);
	return self;
}
shared_ptr<CheckBox> CheckBox::newV(shared_ptr<String> text,shared_ptr<Image> icon)
{
	shared_ptr<CheckBox> self = new CheckBox();
	self->constructV(text, icon);
	return self;
}

CheckBox::CheckBox(void)
{
	selected = false;
}

shared_ptr<CheckBox> CheckBox::shared_from_this()
{
	shared_ptr<Component> cmp = Component::shared_from_this();
	return dynamic_pointer_cast<CheckBox>(cmp);
}

void CheckBox::constructV(shared_ptr<String> text)
{
	shared_ptr<Image> nullImage;
	constructV(text, nullImage);
}
void CheckBox::constructV(shared_ptr<Image> icon)
{
	shared_ptr<String> nullString = new String(L"");
	constructV(nullString, icon);
}
void CheckBox::constructV(shared_ptr<String> text,shared_ptr<Image> icon)
{
	Button::constructV(text,icon);

	shared_ptr<String> tmpString = new String(L"CheckBox");
	setUIID(tmpString);
}

CheckBox::~CheckBox(void)
{
}

/**
* Return true if the checkbox is selected
* 
* @return true if the checkbox is selected
*/
bool CheckBox::isSelected()
{
	return selected;
}

/**
* Selects the current checkbox
* 
* @param selected value for selection
*/
void CheckBox::setSelected(bool selected)
{
	this->selected = selected;
	repaint();
}

/**
* @inheritDoc
*/
void CheckBox::released()
{
	if ( isEnabled() )
	{
		selected = !isSelected();
	}
	Button::released();
}

/**
* @inheritDoc
*/
void CheckBox::paint(shared_ptr<Graphics> g)
{

	UIManager::getInstance()->getLookAndFeel()->drawCheckBox(g, static_pointer_cast<Button>(this->shared_from_this()));
}

int CheckBox::getAvaliableSpaceForText()
{
	shared_ptr<LookAndFeel> l = UIManager::getInstance()->getLookAndFeel();
	//to do
	/*if(l instanceof DefaultLookAndFeel) {
		Image[] rButtonImages = ((DefaultLookAndFeel)l).getCheckBoxImages();
		if (rButtonImages != null) {
			int index = isSelected() ? 1 : 0;
			return super.getAvaliableSpaceForText() - rButtonImages[index].getWidth();
		}
	}*/
	// to check
	DefaultLookAndFeel* dl = dynamic_cast< DefaultLookAndFeel* >(l.get());
	if ( dl != NULL )
	{
		shared_ptr<VectorArray<shared_ptr<Image> > > rButtonImages = 
											(dynamic_pointer_cast<DefaultLookAndFeel>(l))->getCheckBoxImages();
		if ( rButtonImages.get() != NULL )
		{
			int index = isSelected() ? 1 : 0;
			return Button::getAvaliableSpaceForText() - (*rButtonImages)[index]->getWidth();
		}
	}

	return Button::getAvaliableSpaceForText() - ( getHeight() + getGap() );
}
/**
* @inheritDoc
*/
shared_ptr<Dimension> CheckBox::calcPreferredSize()
{
	return UIManager::getInstance()->getLookAndFeel()->getCheckBoxPreferredSize(this->shared_from_this());
}

__GUI_END_NAMESPACE
