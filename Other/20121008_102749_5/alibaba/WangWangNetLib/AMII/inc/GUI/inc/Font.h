#ifndef __GUI_FONT_H__
#define __GUI_FONT_H__

#include "inc/Object.h"
#include "inc/String.h"
#include "inc/Config.h"
#include "AMFont.h"
__GUI_BEGIN_NAMESPACE
class Image;
class Graphics;
class NativeFont;

class Font : public Object
{
public:
	Font(void);
	Font(shared_ptr<NativeFont>  nativeFont);
	Font(int face, int style, int size);
	virtual ~Font(void);
	static void deinitialize();
public:
	/**
	* Constant allowing us to author portable system fonts
	*/
	static const int FACE_MONOSPACE = AMFONT_FACE_MONOSPACE;

	/**
	* Constant allowing us to author portable system fonts
	*/
	static const int FACE_PROPORTIONAL = AMFONT_FACE_PROPORTIONAL;

	/**
	* Constant allowing us to author portable system fonts
	*/
	static const int FACE_SYSTEM = AMFONT_FACE_SYSTEM;

	/**
	* Constant allowing us to author portable system fonts
	*/
	static const int SIZE_LARGE = AMFONT_SIZE_LARGE;

	/**
	* Constant allowing us to author portable system fonts
	*/
	static const int SIZE_MEDIUM = AMFONT_SIZE_MEDIUM;

	/**
	* Constant allowing us to author portable system fonts
	*/
	static const int SIZE_SMALL = AMFONT_SIZE_SMALL;

	/**
	* Constant allowing us to author portable system fonts
	*/
	static const int STYLE_BOLD = AMFONT_STYLE_BOLD;

	/**
	* Constant allowing us to author portable system fonts
	*/
	static const int STYLE_ITALIC = AMFONT_STYLE_ITALIC;

	/**
	* Constant allowing us to author portable system fonts
	*/
	static const int STYLE_UNDERLINED = 4;

	/**
	* Constant allowing us to author portable system fonts
	*/
	static const int STYLE_PLAIN = AMFONT_STYLE_PLAIN;

private:
	static shared_ptr<Font> defaultFont;

	static shared_ptr<Map<String, shared_ptr<Font> > >  bitmapCache;

	static bool enableBitmapFont;

	shared_ptr<NativeFont>  font;
public:
	static shared_ptr<Font> getBitmapFont(shared_ptr<String> fontName);
	static void clearBitmapCache() ;
	static bool isTrueTypeFileSupported();
	static bool isCreationByStringSupported();
	static shared_ptr<Font> createTrueTypeFont(shared_ptr<InputStream> stream);
	static shared_ptr<Font> create(shared_ptr<String> lookup);
	void addContrast(unsigned char value);
	static shared_ptr<Font> createBitmapFont(shared_ptr<String> name, shared_ptr<Image> bitmap, shared_ptr<VectorArray<int> > cutOffsets, shared_ptr<VectorArray<int> > charWidth, shared_ptr<String> charsets);
	static shared_ptr<Font> createBitmapFont(shared_ptr<Image> bitmap, shared_ptr<VectorArray<int> > cutOffsets, shared_ptr<VectorArray<int> > charWidth, shared_ptr<String> charsets);
	static shared_ptr<Font> createSystemFont(int face, int style, int size);
	virtual int charsWidth(shared_ptr<String> ch, int offset, int length);
	virtual int substringWidth(shared_ptr<String> str, int offset, int len);
	virtual int stringWidth(shared_ptr<String> str);
	virtual int charWidth(char ch);
	virtual int getHeight();
	virtual void drawChar(shared_ptr<Graphics> g, char character, int x, int y);
	static shared_ptr<Font> getDefaultFont();
	static void setDefaultFont(shared_ptr<Font> f);
	virtual void drawChars(shared_ptr<Graphics> g, const shared_ptr<String> data, int offset, int length, int x, int y) ;
	virtual int getFace();
	virtual int getSize();
	virtual int getStyle();
	shared_ptr<String> getCharset() ;
	static void setBitmapFontEnabled(bool enabled);
	static bool isBitmapFontEnabled();
	virtual shared_ptr<NativeFont>  getNativeFont();
	bool operator ==(const Font &);
	bool operator !=(const Font &);
};
__GUI_END_NAMESPACE

#endif
