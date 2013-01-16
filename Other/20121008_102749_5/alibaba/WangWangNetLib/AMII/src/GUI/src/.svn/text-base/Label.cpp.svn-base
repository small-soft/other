#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

AM_IMPLEMENT_DYNAMIC(Label, Component)


shared_ptr<Label> Label::newV(shared_ptr<String> text/* = new String(L"")*/ )
{
	shared_ptr<Label> self = new Label();
	self->constructV(text);
	return self;
}

shared_ptr<Label> Label::newV(shared_ptr<String> text, shared_ptr<String> uiid)
{
	shared_ptr<Label> self = new Label();
	self->constructV(text, uiid);
	return self;
}

shared_ptr<Label> Label::newV(shared_ptr<Image> icon)
{
	shared_ptr<Label> self = new Label();
	self->constructV(icon);
	return self;
}

Label::Label()
{
	rightToLeft = false;
	align= LEFT;
	valign = BOTTOM;
	textPosition = RIGHT;
	gap = 2;
	shiftText = 0;
	tickerRunning = false;
	tickerEnabled = true;
	tickerStartTime = 0;
	tickerDelay = 0;
	endsWith3Points = true;
}

Label::~Label()
{
}

shared_ptr<Label> Label::shared_from_this()
{
	shared_ptr<Component> cmp = Component::shared_from_this();
	return dynamic_pointer_cast<Label>(cmp);
}

void Label::constructV(shared_ptr<String> text/* = new String(L"")*/)
{	
	shared_ptr<String> tmp = new String(L"Label");
	setUIID(tmp);
	this->text = text;
	localize();
	setFocusable(false);
}

void Label::constructV(shared_ptr<String> text, shared_ptr<String> uiid)
{	
	this->text = text;
	localize();
	setFocusable(false);
	setAlignment(CENTER);
	setUIID(uiid);
}

void Label::constructV(shared_ptr<Image> icon)
{
	constructV();
	this->icon = icon;
}

int Label::getBaselineResizeBehavior()
{
	switch(valign) {
		case TOP:
			return BRB_CONSTANT_ASCENT;
		case BOTTOM:
			return BRB_CONSTANT_DESCENT;
		case CENTER:
			return BRB_CENTER_OFFSET;
	}
	return BRB_OTHER;
}

void Label::setText( shared_ptr<String> text )
{
	this->text = text;
	localize();
	setShouldCalcPreferredSize(true);
	repaint();
}

void Label::localize()
{
	shared_ptr<Map<String,shared_ptr<Object> > >  t =  UIManager::getInstance()->getResourceBundle();
	if(t.get() != NULL && text.get() != NULL) {
		shared_ptr<Object> o = t->get(*text);
		if(o.get()!= NULL) {
			this->text = static_pointer_cast<String>(o);
		}
	}
}

void Label::initComponentImpl()
{
	Component::initComponentImpl();
	if(hasFocus()) {
		shared_ptr<LookAndFeel> lf = UIManager::getInstance()->getLookAndFeel();
		DefaultLookAndFeel* dlf = dynamic_cast<DefaultLookAndFeel*>(lf.get());
		if(dlf != NULL) {
			dlf->focusGained(this->shared_from_this());
		}
	}
	// solves the case of a user starting a ticker before adding the component
	// into the container
	if(isTickerEnabled() && isTickerRunning() && !isCellRenderer()) {
		//weak_ptr<Animation> ani = (Animation*)this;
		getComponentForm()->registerAnimatedInternal(this->shared_from_this());
	}

}

shared_ptr<String> Label::getText()
{
	return text;
}

void Label::setIcon( shared_ptr<Image> icon )
{
	if(this->icon == icon) {
		return;
	}
	this->icon = icon;
	setShouldCalcPreferredSize(true);
	checkAnimation();
	repaint();

}

void Label::checkAnimation()
{
	Component::checkAnimation();
	if(icon.get() != NULL && icon->isAnimation()) 
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

shared_ptr<Image> Label::getIcon()
{
	return icon;
}

void Label::setAlignment( int align )
{
	if(align != CENTER && align != RIGHT && align != LEFT)
	{
		return;//throw new IllegalArgumentException("Alignment can't be set to " + align);
	}
	this->align = align;
}

void Label::setVerticalAlignment( int valign )
{
	if(valign != CENTER && valign != TOP && valign != BOTTOM)
	{
		return;//throw new IllegalArgumentException("Alignment can't be set to " + valign);
	}
	this->valign = valign;
}

int Label::getVerticalAlignment()
{
	 return valign;
}

int Label::getAlignment()
{
	 return align;
}

void Label::setTextPosition( int textPosition )
{
	if (textPosition != LEFT && textPosition != RIGHT && textPosition != BOTTOM && textPosition != TOP) 
	{
		return;//throw new IllegalArgumentException("Text position can't be set to " + textPosition);
	}
	this->textPosition = textPosition;
}

int Label::getTextPosition()
{
	return textPosition;
}

void Label::setGap( int gap )
{
	 this->gap = gap;
}

int Label::getGap()
{
	return gap;
}

void Label::paint( shared_ptr<Graphics> g )
{
	//weak_ptr<Label> label = this;	
	UIManager::getInstance()->getLookAndFeel()->drawLabel(g, this->shared_from_this());
}

shared_ptr<Dimension> Label::calcPreferredSize()
{	
	//weak_ptr<Label> label = this;
	return UIManager::getInstance()->getLookAndFeel()->getLabelPreferredSize(this->shared_from_this());
}

int Label::getShiftText()
{
	return shiftText;
}

void Label::setShiftText( int shiftText )
{
	this->shiftText = shiftText;
}

bool Label::shouldTickerStart()
{
	shared_ptr<Style> style = getStyle();
	int txtW = style->getFont()->stringWidth(getText());
	int textSpaceW = getAvaliableSpaceForText();
	return txtW > textSpaceW && textSpaceW > 0;

}

shared_ptr<Image> Label::getIconFromState()
{
	 return getIcon();
}

int Label::getAvaliableSpaceForText()
{
	shared_ptr<Style> style = getStyle();
	int textSpaceW = getWidth() - style->getPadding(isRTL(), RIGHT) - style->getPadding(isRTL(), LEFT);
	shared_ptr<Image> icon = getIconFromState();

	if (icon.get() != NULL && (getTextPosition() == RIGHT || getTextPosition() == LEFT)) {
		textSpaceW = textSpaceW - icon->getWidth();
	}
	int preserveSpaceForState = 0;

	textSpaceW = textSpaceW - preserveSpaceForState;
	return textSpaceW;

}

void Label::startTicker( long delay, bool rightToLeft )
{
	//return if ticker is not enabled
	if(!tickerEnabled){
		return;
	}
	if(!isCellRenderer()){
		shared_ptr<Form> parent = getComponentForm();
		if(parent.get() != NULL) 
		{
			parent->registerAnimatedInternal(dynamic_pointer_cast<Animation>(this->shared_from_this()));
		}
	}
	tickerStartTime = System::currentTimeMillis();
	tickerDelay = delay;
	tickerRunning = true;
	this->rightToLeft = rightToLeft;
	if (isRTL()) 
	{
		this->rightToLeft = !this->rightToLeft;
	}

}

void Label::stopTicker()
{
	tickerRunning = false;
	setShiftText(0);
	deregisterAnimatedInternal();
}

bool Label::isTickerRunning()
{
	 return tickerRunning;
}

void Label::setTickerEnabled( bool tickerEnabled )
{
	this->tickerEnabled = tickerEnabled;
}

bool Label::isTickerEnabled()
{
	 return tickerEnabled;
}

void Label::setEndsWith3Points( bool endsWith3Points )
{
	 this->endsWith3Points = endsWith3Points;
}

bool Label::isEndsWith3Points()
{
	 return endsWith3Points;
}

bool Label::animate()
{
	bool animateTicker = false;
	if(tickerRunning && tickerStartTime + tickerDelay < System::currentTimeMillis()){
		tickerStartTime = System::currentTimeMillis();
		if(rightToLeft){
			shiftText-=2;
		}else{
			shiftText+=2;
		}     
		animateTicker = true;
	}                
	// if we have an animated icon then just let it do its thing...
	bool val = icon.get() != NULL && icon->isAnimation() /*&& ((Animation)icon).animate()*/;
	bool parent = Component::animate();
	return  val || parent || animateTicker;

}
__GUI_END_NAMESPACE
