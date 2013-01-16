
#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

bool Style::defaultStyleCompatibilityMode =true;
/**
* Background color attribute name for the theme hashtable 
*/
const String Style::BG_COLOR = L"bgColor";

/**
* Foreground color attribute name for the theme hashtable 
*/
const String Style::FG_COLOR = L"fgColor";

/**
* Background image attribute name for the theme hashtable 
*/
const String Style::BG_IMAGE = L"bgImage";

/**
* Background attribute name for the theme hashtable
*/
const String Style::BACKGROUND_TYPE = L"bgType";


/**
* Background attribute name for the theme hashtable
*/
const String Style::BACKGROUND_ALIGNMENT = L"bgAlign";


/**
* Background attribute name for the theme hashtable
*/
const String Style::BACKGROUND_GRADIENT = L"bgGradient";

/**
* Font attribute name for the theme hashtable 
*/
const String Style::FONT = L"font";

/**
* Transparency attribute name for the theme hashtable 
*/
const String Style::TRANSPARENCY = L"transparency";

/**
* Margin attribute name for the theme hashtable 
*/
const String Style::MARGIN = L"margin";

/**
* Border attribute name for the theme hashtable 
*/
const String Style::BORDER = L"border";

/**
* Padding attribute name for the theme hashtable 
*/
const String Style::PADDING = L"padding";

Style::Style(void)
:fgColor(0x000000),bgColor(0xFFFFFF),font(Font::getDefaultFont()),
transparency(0xFF),backgroundType(/*BACKGROUND_IMAGE_SCALED to do :for no rgb create*/BACKGROUND_IMAGE_ALIGNED),backgroundAlignment(BACKGROUND_IMAGE_ALIGN_TOP)/*,border(NULL)*/
{
	init();
}

Style::Style( const Style& style )
{
	//to check
	this->fgColor = style.fgColor;
	this->bgColor = style.bgColor;
	this->font = style.font;
	this->transparency = style.transparency;
	this->backgroundType = style.backgroundType;
	this->bgImage = style.bgImage;
	setPadding(style.padding[Component::TOP],
		style.padding[Component::BOTTOM],
		style.padding[Component::LEFT],
		style.padding[Component::RIGHT]);
	setMargin(style.margin[Component::TOP],
		style.margin[Component::BOTTOM],
		style.margin[Component::LEFT],
		style.margin[Component::RIGHT]);
	setBorder(style.border);
	this->modifiedFlag = 0;
	this->backgroundType = style.backgroundType;
	this->backgroundAlignment = style.backgroundAlignment;
	if(style.backgroundGradient.get() != NULL)
	{
		this->backgroundGradient = new Vector<float >();
		for ( int i = 0; i < style.backgroundGradient->size(); i++ )
		{
			this->backgroundGradient->addElement(style.backgroundGradient->elementAt(i));
		}
	}
}
Style::Style(int fgColor, int bgColor, shared_ptr<Font> f, unsigned char transparency)
{
	shared_ptr<Image> nullImage;
	init(fgColor, bgColor, f, transparency, nullImage, BACKGROUND_IMAGE_SCALED);

}
Style::Style(int fgColor, int bgColor, shared_ptr<Font> f, unsigned char transparency, shared_ptr<Image> im, int backgroundType)
{
	init(fgColor, bgColor, f, transparency, im, backgroundType);
}
Style::Style(int fgColor, int bgColor, int fgSelectionColor, int bgSelectionColor, shared_ptr<Font> f, unsigned char transparency)
{
	shared_ptr<Image> nullImage;
	init(fgColor, bgColor, fgSelectionColor, bgSelectionColor, f, transparency, nullImage, false);
}
Style::Style(int fgColor, int bgColor, int fgSelectionColor, int bgSelectionColor, shared_ptr<Font> f, unsigned char transparency, shared_ptr<Image> im, bool scaledImage)
{
	init(fgColor, bgColor, fgSelectionColor, bgSelectionColor, f, transparency, im, scaledImage);
}
void Style::init()
{
	setPadding(3, 3, 3, 3);
	setMargin(2, 2, 2, 2);
	modifiedFlag = 0;
}
void Style::init(int fgColor, int bgColor, shared_ptr<Font> f, unsigned char transparency, shared_ptr<Image> im, int backgroundType)
{
	init();
	this->fgColor = fgColor;
	this->bgColor = bgColor;
	this->font = f;
	this->transparency = transparency;
	this->backgroundType = backgroundType;
	this->bgImage = im;
}
void Style::init(int fgColor, int bgColor, int fgSelectionColor, int bgSelectionColor, shared_ptr<Font> f, unsigned char transparency, shared_ptr<Image> im, bool scaledImage)
{
	init();
	this->fgColor = fgColor;
	this->bgColor = bgColor;
	this->font = f;
	this->transparency = transparency;
	this->bgImage = im; 
}
Style::~Style(void)
{
}

void Style::merge(shared_ptr<Style> style)
{
	short tmp = modifiedFlag;

	if ((modifiedFlag & FG_COLOR_MODIFIED) == 0) 
	{
		setFgColor(style->getFgColor());
	}
	if ((modifiedFlag & BG_COLOR_MODIFIED) == 0) {
		setBgColor(style->getBgColor());
	}
	if ((modifiedFlag & BG_IMAGE_MODIFIED) == 0) {
		setBgImage(style->getBgImage());
	}
	if ((modifiedFlag & BACKGROUND_TYPE_MODIFIED) == 0) {
		setBackgroundType(style->getBackgroundType());
	}
	if ((modifiedFlag & BACKGROUND_ALIGNMENT_MODIFIED) == 0) {
		setBackgroundAlignment(style->getBackgroundAlignment());
	}
	if ((modifiedFlag & BACKGROUND_GRADIENT_MODIFIED) == 0) {
		setBackgroundGradientStartColor(style->getBackgroundGradientStartColor());
		setBackgroundGradientEndColor(style->getBackgroundGradientEndColor());
		setBackgroundGradientRelativeX(style->getBackgroundGradientRelativeX());
		setBackgroundGradientRelativeY(style->getBackgroundGradientRelativeY());
		setBackgroundGradientRelativeSize(style->getBackgroundGradientRelativeSize());
	}
	if ((modifiedFlag & FONT_MODIFIED) == 0) {
		setFont(style->getFont());
	}

	if ((modifiedFlag & TRANSPARENCY_MODIFIED) == 0) {
		setBgTransparency(style->getBgTransparency());
	}

	if ((modifiedFlag & PADDING_MODIFIED) == 0) {
		setPadding(style->padding[Component::TOP],
			style->padding[Component::BOTTOM],
			style->padding[Component::LEFT],
			style->padding[Component::RIGHT]);
	}

	if ((modifiedFlag & MARGIN_MODIFIED) == 0) {
		setMargin(style->margin[Component::TOP],
			style->margin[Component::BOTTOM],
			style->margin[Component::LEFT],
			style->margin[Component::RIGHT]);
	}

	if ((modifiedFlag & BORDER_MODIFIED) == 0) {
		setBorder(style->getBorder());
	}

	modifiedFlag = tmp;
}
bool Style::isModified()
{
	return modifiedFlag != 0;
}

int Style::getBgColor()
{
	return bgColor;
}
shared_ptr<Image> Style::getBgImage()
{
	return bgImage;
}

unsigned char Style::getBackgroundType()
{
	return backgroundType;
}
unsigned char Style::getBackgroundAlignment()
{
	return backgroundAlignment;
}
int Style::getBackgroundGradientStartColor()
{
	if(backgroundGradient.get() != NULL && backgroundGradient->size() > 1) 
	{
		return (int)(*backgroundGradient)[0];
	}
	return 0xffffff;
}
int Style::getBackgroundGradientEndColor()
{
	if(backgroundGradient.get() != NULL && backgroundGradient->size() > 1) 
	{
		return (int)(*backgroundGradient)[1];
	}
	return 0;
}
float Style::getBackgroundGradientRelativeX()
{
	if(backgroundGradient.get() != NULL && backgroundGradient->size() > 2) {
		return (float)(*backgroundGradient)[2];
	}
	return 0.5f;
}
float Style::getBackgroundGradientRelativeY()
{
	if(backgroundGradient.get() != NULL && backgroundGradient->size() > 3) {
		return (float)(*backgroundGradient)[3];
	}
	return 0.5f;
}

float Style::getBackgroundGradientRelativeSize()
{
	if(backgroundGradient.get() != NULL && backgroundGradient->size() > 4) 
	{
		return (float)(*backgroundGradient)[4];
	}
	return 1.0f;
}
int Style::getFgColor()
{
	return fgColor;
}
shared_ptr<Font> Style::getFont()
{
	return font;
}
void Style::setBgColor(int bgColor)
{
	setBgColor(bgColor, false);
}
void Style::setBgImage(shared_ptr<Image> bgImage)
{
	setBgImage(bgImage, false);
}
void Style::setBackgroundType(int backgroundType)
{
	setBackgroundType(backgroundType, false);
}
void Style::setBackgroundAlignment(unsigned char backgroundAlignment)
{
	setBackgroundAlignment(backgroundAlignment, false);
}
void Style::setBackgroundGradientStartColor(int backgroundGradientStartColor)
{
	setBackgroundGradientStartColor(backgroundGradientStartColor, false);
}
void Style::setBackgroundGradientEndColor(int backgroundGradientEndColor)
{
	setBackgroundGradientEndColor(backgroundGradientEndColor, false);
}
void Style::setBackgroundGradientRelativeX(float backgroundGradientRelativeX)
{
	setBackgroundGradientRelativeX(backgroundGradientRelativeX, false);
}
void Style::setBackgroundGradientRelativeY(float backgroundGradientRelativeY)
{
	setBackgroundGradientRelativeY(backgroundGradientRelativeY, false);
}
void Style::setBackgroundGradientRelativeSize(float backgroundGradientRelativeSize)
{
	setBackgroundGradientRelativeSize(backgroundGradientRelativeSize, false);
}
void Style::setFgColor(int fgColor)
{
	setFgColor(fgColor, false);
}
void Style::setFont(shared_ptr<Font> font)
{
	setFont(font, false);
}
shared_ptr<Style> Style::getSelectedStyle()
{
	shared_ptr<Style> res;
	if(listeners.get() != NULL) 
	{
		shared_ptr<Vector<weak_ptr<StyleListener> > > l = listeners->getListenerVector();
		int size = l->size();
		if(size > 0) 
		{
			Object *o = (Object *)l->elementAt(0).get();
			Component *com = dynamic_cast<Component *>(o);
			if (NULL != com)
			{
				res = com->getSelectedStyle();
			}

		}
	}
	return res;
}
unsigned char Style::getBgTransparency()
{
	if(bgImage.get() != NULL && (bgImage->isAnimation() || bgImage->isOpaque())) {
		return (unsigned char)0xff;
	}
	return transparency;
}
void Style::setBgTransparency(unsigned char transparency)
{
	setBgTransparency(transparency & 0xFF, false);
}
void Style::setBgTransparency(int transparency)
{
	setBgTransparency(transparency, false);
}

void Style::setPadding(int top, int bottom, int left, int right)
{
	if (top < 0 || left < 0 || right < 0 || bottom < 0) 
	{
		return;
	}
	if (padding[Component::TOP] != top || padding[Component::BOTTOM] != bottom || padding[Component::LEFT] != left || padding[Component::RIGHT] != right) 
	{
			padding[Component::TOP] = top;
			padding[Component::BOTTOM] = bottom;
			padding[Component::LEFT] = left;
			padding[Component::RIGHT] = right;

			modifiedFlag |= PADDING_MODIFIED;
			firePropertyChanged__(PADDING);
	}
}
void Style::setPadding(int orientation, int gap)
{
	setPadding(orientation, gap, false);
}
void Style::setMargin(int top, int bottom, int left, int right)
{
	if (top < 0 || left < 0 || right < 0 || bottom < 0) {
		return;
	}
	if (margin[Component::TOP] != top || margin[Component::BOTTOM] != bottom || margin[Component::LEFT] != left || margin[Component::RIGHT] != right) 
	{
			margin[Component::TOP] = top;
			margin[Component::BOTTOM] = bottom;
			margin[Component::LEFT] = left;
			margin[Component::RIGHT] = right;

			modifiedFlag |= MARGIN_MODIFIED;
			firePropertyChanged__(MARGIN);
	}
}

void Style::setMargin(int orientation, int gap)
{
	setMargin(orientation, gap, false);
}
int Style::getPadding(bool rtl, int orientation)
{
	if (orientation < Component::TOP || orientation > Component::RIGHT) 
	{
		return 0;
	}

	if (rtl)
	{
		switch(orientation) 
		{
		case Component::LEFT:
			orientation = Component::RIGHT;
			break;
		case Component::RIGHT:
			orientation = Component::LEFT;
			break;
		}
	}

	return padding[orientation];
}
int Style::getPadding(int orientation)
{
	return getPadding(UIManager::getInstance()->getLookAndFeel()->isRTL(), orientation);
}

int Style::getMargin(int orientation)
{
	return getMargin(UIManager::getInstance()->getLookAndFeel()->isRTL(), orientation);
}
int Style::getMargin(bool rtl, int orientation)
{
	if (orientation < Component::TOP || orientation > Component::RIGHT) {
		return -1;
	}
	if (rtl) 
	{
		switch(orientation) 
		{
		case Component::LEFT:
			orientation = Component::RIGHT;
			break;
		case Component::RIGHT:
			orientation = Component::LEFT;
			break;
		}
	}
	return margin[orientation];
}
void Style::setBgColor(int bgColor, bool override)
{
	if (this->bgColor != bgColor) 
	{
		this->bgColor = bgColor;
		if (!override) 
		{
			modifiedFlag |= BG_COLOR_MODIFIED;
		}
		firePropertyChanged__(BG_COLOR);
	}
}

void Style::setBgImage(shared_ptr<Image> bgImage, bool override)
{
	if (this->bgImage != bgImage) 
	{
		this->bgImage = bgImage;
		if(!override)
		{
			modifiedFlag |= BG_IMAGE_MODIFIED;
		}
		firePropertyChanged__(BG_IMAGE);
	}
}
void Style::setBackgroundType(int backgroundType, bool override)
{
	if (this->backgroundType != backgroundType)
	{
		this->backgroundType = backgroundType;
		if(!override)
		{
			modifiedFlag |= BACKGROUND_TYPE_MODIFIED;
		}
		firePropertyChanged__(BACKGROUND_TYPE);
	}
}
void Style::setBackgroundAlignment(unsigned char backgroundAlignment, bool override)
{
	if (this->backgroundAlignment != backgroundAlignment) 
	{
		this->backgroundAlignment = backgroundAlignment;
		if(!override)
		{
			modifiedFlag |= BACKGROUND_ALIGNMENT_MODIFIED;
		}
		firePropertyChanged__(BACKGROUND_ALIGNMENT);
	}
}
shared_ptr<Vector<float> > Style::getBackgroundGradient()
{
	if(backgroundGradient.get() == NULL) 
	{
		float tmp[5] = {0xffffff, 0, 0.5f, 0.5f, 1.0f};
		backgroundGradient = new Vector<float>();
		backgroundGradient->push_back(0xffffff);
		backgroundGradient->push_back(0);
		backgroundGradient->push_back(0.5f);
		backgroundGradient->push_back(0.5f);
		backgroundGradient->push_back(1.0f);
	}
	return backgroundGradient;
}
void Style::setBackgroundGradient(shared_ptr<Vector<float> > backgroundGradient)
{
	this->backgroundGradient = backgroundGradient;
}
void Style::setBackgroundGradientStartColor(int backgroundGradientStartColor, bool override)
{
	if (((int) (*getBackgroundGradient())[0]) != backgroundGradientStartColor) 
	{
		(*getBackgroundGradient())[0] = (float)backgroundGradientStartColor;
		if (!override) 
		{
			modifiedFlag |= BACKGROUND_GRADIENT_MODIFIED;
		}
		firePropertyChanged__(BACKGROUND_GRADIENT);
	}
}
void Style::setBackgroundGradientEndColor(int backgroundGradientEndColor, bool override)
{
	if (((int) (*getBackgroundGradient())[1]) != backgroundGradientEndColor) 
	{
		(*getBackgroundGradient())[1] = (float)backgroundGradientEndColor;
		if (!override) 
		{
			modifiedFlag |= BACKGROUND_GRADIENT_MODIFIED;
		}
		firePropertyChanged__(BACKGROUND_GRADIENT);
	}
}
void Style::setBackgroundGradientRelativeX(float backgroundGradientRelativeX, bool override)
{
	if (((float) (*getBackgroundGradient())[2]) != backgroundGradientRelativeX) 
	{
		(*getBackgroundGradient())[2] = backgroundGradientRelativeX;
		if (!override) {
			modifiedFlag |= BACKGROUND_GRADIENT_MODIFIED;
		}
		firePropertyChanged__(BACKGROUND_GRADIENT);
	}
}
void Style::setBackgroundGradientRelativeY(float backgroundGradientRelativeY, bool override)
{
	if (((float)(*getBackgroundGradient())[3]) != backgroundGradientRelativeY) 
	{
		(*getBackgroundGradient())[3] = backgroundGradientRelativeY;
		if (!override) 
		{
			modifiedFlag |= BACKGROUND_GRADIENT_MODIFIED;
		}
		firePropertyChanged__(BACKGROUND_GRADIENT);
	}
}
void Style::setBackgroundGradientRelativeSize(float backgroundGradientRelativeSize, bool override)
{
	if (((float) (*getBackgroundGradient())[4]) != backgroundGradientRelativeSize) 
	{
		(*getBackgroundGradient())[4] = backgroundGradientRelativeSize;
		if (!override) 
		{
			modifiedFlag |= BACKGROUND_GRADIENT_MODIFIED;
		}
		firePropertyChanged__(BACKGROUND_GRADIENT);
	}
}
void Style::setFgColor(int fgColor, bool override)
{
	if (this->fgColor != fgColor) 
	{
		this->fgColor = fgColor;
		if (!override) 
		{
			modifiedFlag |= FG_COLOR_MODIFIED;
		}
		firePropertyChanged__(FG_COLOR);
	}
}
void Style::setFont(shared_ptr<Font> font, bool override)
{
	if (this->font.get() == NULL && font.get() != NULL || (this->font.get() != NULL && !(this->font == font))) 
	{
			this->font = font;
			if (!override) 
			{
				modifiedFlag |= FONT_MODIFIED;
			}
			firePropertyChanged__(FONT);
	}
}

void Style::setBgTransparency(int transparency, bool override)
{
	if (transparency < 0 || transparency > 255) 
	{
		return;
	}
	if (this->transparency != (unsigned char) transparency) 
	{
		this->transparency = (unsigned char) transparency;

		if (!override) 
		{
			modifiedFlag |= TRANSPARENCY_MODIFIED;
		}
		firePropertyChanged__(TRANSPARENCY);
	}
}
void Style::setPadding(int orientation, int gap,bool override)
{
	if (orientation < Component::TOP || orientation > Component::RIGHT) 
	{
		return;
	}
	if (gap < 0) {
		return;
	}
	if (padding[orientation] != gap) 
	{
		padding[orientation] = gap;

		if (!override) 
		{
			modifiedFlag |= PADDING_MODIFIED;
		}
		firePropertyChanged__(PADDING);
	}
}
void Style::setMargin(int orientation, int gap, bool override)
{
	if (orientation < Component::TOP || orientation > Component::RIGHT) 
	{
		return;
	}
	if (gap < 0) {
		return;
	}

	if (margin[orientation] != gap) 
	{
		margin[orientation] = gap;
		if (!override) 
		{
			modifiedFlag |= MARGIN_MODIFIED;
		}
		firePropertyChanged__(MARGIN);
	}
}

void Style::firePropertyChanged(shared_ptr<String> propertName)
{

	if (listeners.get() == NULL) 
	{
		return;
	}
	
	listeners->fireStyleChangeEvent(propertName, this->shared_from_this());
}

void Style::firePropertyChanged__(String propertName)
{
	shared_ptr<String> propert = new String(propertName);
	firePropertyChanged(propert);
}

void Style::addStyleListener(shared_ptr<StyleListener> l)
{
	if (listeners.get() == NULL) 
	{
		listeners = new EventDispatcher<StyleListener>();
	}
	listeners->addListener(l);
}
void Style::removeStyleListener(shared_ptr<StyleListener> l)
{
	if (listeners.get() != NULL) 
	{
		listeners->removeListener(l);
	}
}
void Style::resetModifiedFlag()
{
	modifiedFlag = 0;
}
void Style::setBorder(shared_ptr<Border> border)
{
	setBorder(border, false);
}
void Style::setBorder(shared_ptr<Border> border, bool override)
{
	if ((this->border.get() == NULL && border.get() != NULL) || (this->border.get() != NULL && !(this->border == border))) 
	{
			this->border = border;
			if (!override) 
			{
				modifiedFlag |= BORDER_MODIFIED;
			}
			firePropertyChanged__(BORDER);
	}
}
shared_ptr<Border> Style::getBorder()
{
	return border;
}
shared_ptr<Painter> Style::getBgPainter()
{
	return bgPainter;
}
void Style::setBgPainter(shared_ptr<Painter> bgPainter)
{
	this->bgPainter = bgPainter;
}

void Style::setStyleCompatibilityMode(bool defaultMode)
{
	defaultStyleCompatibilityMode = defaultMode;
}
bool Style::isStyleCompatibilityMode()
{
	return defaultStyleCompatibilityMode;
}
__GUI_END_NAMESPACE
