#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

AM_IMPLEMENT_DYNAMIC(Button, Label)


shared_ptr<Button> Button::newV(shared_ptr<String> text, shared_ptr<Image> icon)
{
	shared_ptr<Button> self = new Button();
	self->constructV(text,icon);
	return self;
}

shared_ptr<Button> Button::newV(shared_ptr<Command> cmd)
{
	shared_ptr<Button> self = new Button();
	self->constructV(cmd);
	return self;
}

shared_ptr<Button> Button::newV(shared_ptr<String> text/* = new String(L"")*/)
{
	shared_ptr<Button> self = new Button();
	self->constructV(text);
	return self;
}

Button::Button()
{
	state = STATE_DEFAULT;
}
shared_ptr<Button> Button::shared_from_this()
{
	shared_ptr<Component> cmp = Component::shared_from_this();
	return dynamic_pointer_cast<Button>(cmp);
}
void Button::constructV(shared_ptr<String> text, shared_ptr<Image> icon)
{
	Label::constructV(text);
	
	this->state = STATE_DEFAULT;
	shared_ptr<String> tmpString = new String(L"Button");
	setUIID(tmpString);
	setFocusable(true);
	setIcon(icon);
	this->pressedIcon = icon;
	this->rolloverIcon = icon;
	dispatcher = new EventDispatcher<ActionListener>();
}

void Button::constructV(shared_ptr<Command> cmd)
{
	constructV(cmd->getCommandName(), cmd->getIcon());
	addActionListener(cmd);
	this->cmd = cmd;
	
}

void Button::constructV(shared_ptr<String> text /*= new String(L"")*/)
{
	shared_ptr<Image> image ;
	constructV(text,image);
}


Button::~Button(void)
{
}

void Button::focusGainedInternal()
{
	Component::focusGainedInternal();
	state = STATE_ROLLOVER;
}

void Button::focusLostInternal()
{
	Component::focusLostInternal();
	state = STATE_DEFAULT;
}

int Button::getState()
{
	return state;
}

shared_ptr<Image> Button::getPressedIcon()
{
	 return pressedIcon;
}

shared_ptr<Image> Button::getRolloverIcon()
{
	  return rolloverIcon;
}

void Button::setPressedIcon(shared_ptr<Image> pressedIcon )
{
	this->pressedIcon = pressedIcon;
	setShouldCalcPreferredSize(true);
	checkAnimation();
	repaint();
}

void Button::checkAnimation()
{
	Label::checkAnimation();
	if((pressedIcon.get() != NULL && pressedIcon->isAnimation()) || (rolloverIcon.get() != NULL && rolloverIcon->isAnimation())) 
	{
			shared_ptr<Form> parent = getComponentForm();
			if(parent.get() != NULL) 
			{
				// animations are always running so the internal animation isn't
				// good enough. We never want to stop this sort of animation
				parent->registerAnimated(this->shared_from_this());
			}
	}

}

void Button::addActionListener( shared_ptr<ActionListener> l )
{	
	 dispatcher->addListener(l);
}

void Button::removeActionListener( shared_ptr<ActionListener> l )
{	
	
	 dispatcher->removeListener(l);
}

shared_ptr<Image> Button::getIconFromState()
{
	shared_ptr<Image> icon;
	switch (getState()) 
	{
	case Button::STATE_DEFAULT:
		icon = getIcon();
		break;
	case Button::STATE_PRESSED:
		icon = getPressedIcon();
		if (icon.get() == NULL) 
		{
			icon = getIcon();
		}
		break;
	case Button::STATE_ROLLOVER:
		icon = getRolloverIcon();
		if (icon.get() == NULL) 
		{
			icon = getIcon();
		}
		break;
	}
	return icon;

}

void Button::fireActionEvent()
{
	Component::fireActionEvent();
	if(cmd.get() != NULL) 
	{
		shared_ptr<ActionEvent> ev = new ActionEvent(cmd);
		dispatcher->fireActionEvent(ev);
		
		if(!ev->isConsumed()) 
		{
			shared_ptr<Form> f = getComponentForm();
			if(f.get() != NULL) 
			{
				f->actionCommandImpl(cmd);
			}
		}
	}
	else 
	{
		shared_ptr <Button> tmp = this->shared_from_this();

		dispatcher->fireActionEvent(new ActionEvent(static_pointer_cast<Object>(tmp)));
	}

}

void Button::pressed()
{
	if(isEnabled()) {
		state=STATE_PRESSED;
		repaint();
	}

}

void Button::released()
{
	if(isEnabled()) {
		state=STATE_ROLLOVER;
		repaint();
		fireActionEvent();
	}

}

void Button::keyPressed( int keyCode )
{
	if (Display::getInstance()->getGameAction(keyCode) == Display::GAME_FIRE){
		pressed();
	}

}

void Button::keyReleased( int keyCode )
{
	if (Display::getInstance()->getGameAction(keyCode) == Display::GAME_FIRE){
		released();
	}

}

void Button::keyRepeated( int keyCode )
{
	pressed();
	released();
}

bool Button::isSelectableInteraction()
{
	return true;
}

void Button::pointerHover( shared_ptr<Vector<int> > x, shared_ptr<Vector<int> > y )
{
	 requestFocus();
}

void Button::pointerHoverReleased(shared_ptr<Vector<int> > x, shared_ptr<Vector<int> > y)
{
	 requestFocus();
}

void Button::pointerPressed( int x, int y )
{
	clearDrag();
	setDragActivated(false);
	pressed();
}

void Button::pointerReleased( int x, int y )
{
	 released();
}

void Button::paint( shared_ptr<Graphics> g )
{
	UIManager::getInstance()->getLookAndFeel()->drawButton(g, this->shared_from_this());
}

shared_ptr<Dimension> Button::calcPreferredSize()
{	
	return UIManager::getInstance()->getLookAndFeel()->getButtonPreferredSize(this->shared_from_this());	
}

shared_ptr<Border> Button::getBorder()
{
	 return getStyle()->getBorder();
}

shared_ptr<Style> Button::getPressedStyle()
{
	shared_ptr<Button> btn = this->shared_from_this();
	if (pressedStyle.get() == NULL) 
	{
		String str(L"press");
		pressedStyle = UIManager::getInstance()->getComponentCustomStyle(*getUIID(), str);
		pressedStyle->addStyleListener(btn);

		if(pressedStyle->getBgPainter().get() == NULL)
		{
			shared_ptr<Component> cmp   = static_pointer_cast<Component>(btn);
			shared_ptr<BGPainter> tmp = new BGPainter(cmp);
			pressedStyle->setBgPainter(tmp);
		}
	}
	return pressedStyle;

}

void Button::setPressedStyle( shared_ptr<Style> style )
{
	shared_ptr<Button> btn = this->shared_from_this();
	if (pressedStyle.get() != NULL) {
		pressedStyle->removeStyleListener(btn);
	}
	pressedStyle = style;
	pressedStyle->addStyleListener(btn);

	if (pressedStyle->getBgPainter().get() == NULL) 
	{
		shared_ptr<Component> cmp = static_pointer_cast<Component>(btn);
		shared_ptr<BGPainter> tmp = new BGPainter(cmp);
		pressedStyle->setBgPainter(tmp);
	}
	setShouldCalcPreferredSize(true);
	checkAnimation();

}

void Button::refreshTheme( shared_ptr<String> id )
{
	if(pressedStyle.get() != NULL) 
	{
		String tmp(L"press");
		setPressedStyle(mergeStyle(pressedStyle, UIManager::getInstance()->getComponentCustomStyle(*id, tmp)));
	}
	Component::refreshTheme(id);

}

shared_ptr<Style> Button::getStyle()
{
	if(state == STATE_PRESSED) 
	{
		return getPressedStyle();
	}
	return Component::getStyle();

}

shared_ptr<Command> Button::getCommand()
{
	 return cmd;
}

bool Button::isSelected()
{
	return false;
}

void Button::fireClicked()
{
	pressed();
	released();
}

void Button::setRolloverIcon( shared_ptr<Image> rolloverIcon )
{
	this->rolloverIcon = rolloverIcon;
}
/* for the use of Map<Shared_ptr<Button>, TypeName N> */
bool Button::operator < (Button button2)  
{ 
	return  *(this->getText()) < *(button2.getText());
}

__GUI_END_NAMESPACE
