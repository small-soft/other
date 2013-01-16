#ifndef __GUI_STYLE_H__
#define __GUI_STYLE_H__

#include "inc/String.h"

#include "inc/Config.h"
#include "inc/EventDispatcher.h"
#include "inc/Object.h"
__GUI_BEGIN_NAMESPACE
class Painter;
class Image;
class Font;
class Border;
class StyleListener;

class Style:public Object,public enable_shared_from_this<Style>
{
public:
	Style(void);
	Style(const Style& style);
	Style(int fgColor, int bgColor, shared_ptr<Font> f, unsigned char transparency);
	Style(int fgColor, int bgColor, shared_ptr<Font> f, unsigned char transparency, shared_ptr<Image> im, int backgroundType);
	virtual ~Style(void);
private:
	Style(int fgColor, int bgColor, int fgSelectionColor, int bgSelectionColor, shared_ptr<Font> f, unsigned char transparency);
	Style(int fgColor, int bgColor, int fgSelectionColor, int bgSelectionColor, shared_ptr<Font> f, unsigned char transparency, shared_ptr<Image> im, bool scaledImage) ;

	void init();
	void init(int fgColor, int bgColor, shared_ptr<Font> f, unsigned char transparency, shared_ptr<Image> im, int backgroundType);
	void init(int fgColor, int bgColor, int fgSelectionColor, int bgSelectionColor, shared_ptr<Font> f, unsigned char transparency, shared_ptr<Image> im, bool scaledImage);

private:
	/**
	* Indicates a special compatibilty mode for LWUIT allowing easy transition to
	* the new style model
	*/
	static bool defaultStyleCompatibilityMode; //= true;
public:
	/**
	* Background color attribute name for the theme hashtable 
	*/
	static const String BG_COLOR;// = "bgColor";

	/**
	* Foreground color attribute name for the theme hashtable 
	*/
	static const String FG_COLOR ;//= "fgColor";

	/**
	* Background image attribute name for the theme hashtable 
	*/
	static const String BG_IMAGE ;//= "bgImage";

	/**
	* Background attribute name for the theme hashtable
	*/
	static const String BACKGROUND_TYPE;// = "bgType";


	/**
	* Background attribute name for the theme hashtable
	*/
	static const String BACKGROUND_ALIGNMENT;// = "bgAlign";


	/**
	* Background attribute name for the theme hashtable
	*/
	static const String BACKGROUND_GRADIENT ;//= "bgGradient";

	/**
	* Font attribute name for the theme hashtable 
	*/
	static const String FONT ;//= "font";

	/**
	* Transparency attribute name for the theme hashtable 
	*/
	static const String TRANSPARENCY ;//= "transparency";

	/**
	* Margin attribute name for the theme hashtable 
	*/
	static const String MARGIN;// = "margin";

	/**
	* Border attribute name for the theme hashtable 
	*/
	static const String BORDER;// = "border";

	/**
	* Padding attribute name for the theme hashtable 
	*/
	static const String PADDING;// = "padding";

	/**
	* Indicates the background for the style would use a scaled image
	*/
	static const int BACKGROUND_IMAGE_SCALED = 1;

	/**
	* Indicates the background for the style would use a tiled image on both axis
	*/
	static const int BACKGROUND_IMAGE_TILE_BOTH = 2;

	/**
	* Indicates the background for the style would use a vertical tiled image
	*/
	static const int BACKGROUND_IMAGE_TILE_VERTICAL = 3;

	/**
	* Indicates the background for the style would use a horizontal tiled image
	*/
	static const int BACKGROUND_IMAGE_TILE_HORIZONTAL = 4;

	/**
	* Indicates the background for the style would use an unscaled image with an alignment
	*/
	static const int BACKGROUND_IMAGE_ALIGNED = 5;

	/**
	* Indicates the background for the style would use a linear gradient
	*/
	static const int BACKGROUND_GRADIENT_LINEAR_VERTICAL = 6;

	/**
	* Indicates the background for the style would use a linear gradient
	*/
	static const int BACKGROUND_GRADIENT_LINEAR_HORIZONTAL = 7;

	/**
	* Indicates the background for the style would use a radial gradient
	*/
	static const int BACKGROUND_GRADIENT_RADIAL = 8;

	/**
	* Indicates the background alignment for use in tiling or aligned images
	*/
	static const int BACKGROUND_IMAGE_ALIGN_TOP = 0xa1;
	/**
	* Indicates the background alignment for use in tiling or aligned images
	*/
	static const int BACKGROUND_IMAGE_ALIGN_BOTTOM = 0xa2;
	/**
	* Indicates the background alignment for use in tiling or aligned images
	*/
	static const int BACKGROUND_IMAGE_ALIGN_LEFT = 0xa3;
	/**
	* Indicates the background alignment for use in tiling or aligned images
	*/
	static const int BACKGROUND_IMAGE_ALIGN_RIGHT = 0xa4;
	/**
	* Indicates the background alignment for use in tiling or aligned images
	*/
	static const int BACKGROUND_IMAGE_ALIGN_CENTER = 0xa5;

private:
	int fgColor;// = 0x000000;
	int bgColor;// = 0xFFFFFF;
	shared_ptr<Font> font ;//= Font.getDefaultFont();
	shared_ptr<Image> bgImage;
	int padding[4];
	int margin[4];
	unsigned char transparency;// = (unsigned char) 0xFF; //no transparency
	shared_ptr<Painter> bgPainter;

	int backgroundType;// = BACKGROUND_IMAGE_SCALED;
	unsigned char backgroundAlignment;// = BACKGROUND_IMAGE_ALIGN_TOP;
	shared_ptr<Vector<float> > backgroundGradient;

	shared_ptr<Border> border; //= null;

	short modifiedFlag;

	static const short FG_COLOR_MODIFIED = 1;
	/**
	* Used for modified flag
	*/
	static const short BG_COLOR_MODIFIED = 2;

	/**
	* Used for modified flag
	*/
	static const short FONT_MODIFIED = 16;
	/**
	* Used for modified flag
	*/
	static const short BG_IMAGE_MODIFIED = 32;
	/**
	* Used for modified flag
	*/
	//private static const short SCALE_IMAGE_MODIFIED = 64;
	/**
	* Used for modified flag
	*/
	static const short TRANSPARENCY_MODIFIED = 128;
	/**
	* Used for modified flag
	*/
	static const short PADDING_MODIFIED = 256;
	/**
	* Used for modified flag
	*/
	static const short MARGIN_MODIFIED = 512;

	/**
	* Used for modified flag
	*/
	static const short BORDER_MODIFIED = 1024;

	static const short BACKGROUND_TYPE_MODIFIED = 2048;

	static const short BACKGROUND_ALIGNMENT_MODIFIED = 4096;

	static const short BACKGROUND_GRADIENT_MODIFIED = 8192;

	shared_ptr<EventDispatcher<StyleListener> > listeners;
public :
	void merge(shared_ptr<Style> style);
	bool isModified();
	int getBgColor();
	shared_ptr<Image> getBgImage();
	unsigned char getBackgroundType();
	unsigned char getBackgroundAlignment();
	int getBackgroundGradientStartColor();
	int getBackgroundGradientEndColor();
	float getBackgroundGradientRelativeX();
	float getBackgroundGradientRelativeY() ;
	float getBackgroundGradientRelativeSize();
	int getFgColor();
	shared_ptr<Font> getFont();
	void setBgColor(int bgColor);
	void setBgImage(shared_ptr<Image> bgImage);
	void setBackgroundType(int backgroundType);
	void setBackgroundAlignment(unsigned char backgroundAlignment);
	void setBackgroundGradientStartColor(int backgroundGradientStartColor);
	void setBackgroundGradientEndColor(int backgroundGradientEndColor);
	void setBackgroundGradientRelativeX(float backgroundGradientRelativeX);
	void setBackgroundGradientRelativeY(float backgroundGradientRelativeY) ;
	void setBackgroundGradientRelativeSize(float backgroundGradientRelativeSize);
	void setFgColor(int fgColor);
	void setFont(shared_ptr<Font> font);
	shared_ptr<Style> getSelectedStyle() ;
	unsigned char getBgTransparency();
	void setBgTransparency(unsigned char transparency);
	void setBgTransparency(int transparency);
	void setPadding(int top, int bottom, int left, int right);
	void setPadding(int orientation, int gap) ;
	void setMargin(int top, int bottom, int left, int right);
	void setMargin(int orientation, int gap);
	int getPadding(bool rtl, int orientation);
	int getPadding(int orientation);
	int getMargin(int orientation);
	int getMargin(bool rtl, int orientation);
	void setBgColor(int bgColor, bool override);
	void setBgImage(shared_ptr<Image> bgImage, bool override);
	void setBackgroundType(int backgroundType, bool override);
	void setBackgroundAlignment(unsigned char backgroundAlignment, bool override);
	shared_ptr<Vector<float> > getBackgroundGradient(); 
	void setBackgroundGradient(shared_ptr<Vector<float> > backgroundGradient);
	void setBackgroundGradientStartColor(int backgroundGradientStartColor, bool override);
	void setBackgroundGradientEndColor(int backgroundGradientEndColor, bool override);
	void setBackgroundGradientRelativeX(float backgroundGradientRelativeX, bool override);
	void setBackgroundGradientRelativeY(float backgroundGradientRelativeY, bool override);
	void setBackgroundGradientRelativeSize(float backgroundGradientRelativeSize, bool override);
	void setFgColor(int fgColor, bool override);
	void setFont(shared_ptr<Font> font, bool override);
	void setBgTransparency(int transparency, bool override);
	void setPadding(int orientation, int gap,bool override);
	void setMargin(int orientation, int gap, bool override);
	void addStyleListener(shared_ptr<StyleListener> l);
	void removeStyleListener(shared_ptr<StyleListener> l);
	void resetModifiedFlag();
	void setBorder(shared_ptr<Border> border);
	void setBorder(shared_ptr<Border> border, bool override) ;
	shared_ptr<Border> getBorder();
	shared_ptr<Painter> getBgPainter();
	void setBgPainter(shared_ptr<Painter> bgPainter);
	static void setStyleCompatibilityMode(bool defaultMode);
	static bool isStyleCompatibilityMode();
private:
	void firePropertyChanged(shared_ptr<String> propertName);
	void firePropertyChanged__(String propertName);
};
__GUI_END_NAMESPACE

#endif
