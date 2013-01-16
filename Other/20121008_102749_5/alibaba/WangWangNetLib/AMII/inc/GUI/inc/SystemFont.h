#ifndef __GUI_SYSTEM_FONT_H__
#define __GUI_SYSTEM_FONT_H__

#include "inc/Font.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class SystemFont:public Font
{
public:
	SystemFont(int face, int style, int size);
	SystemFont(shared_ptr<NativeFont> font);
	virtual ~SystemFont(void);
private:
	shared_ptr<NativeFont> font;
//	static shared_ptr<Font> defaultFont;// = new SystemFont(null);
public:
	virtual int charWidth(char ch);
	virtual int charsWidth(shared_ptr<String> ch, int offset, int length);
	virtual int substringWidth(shared_ptr<String> str, int offset, int len);
	virtual int stringWidth(shared_ptr<String> str);
	virtual int getHeight();
	virtual void drawChar(shared_ptr<Graphics> g, char character, int x, int y);
	//void drawChars(shared_ptr<Graphics> g, char* data, int offset, int length, int x, int y);
	virtual void drawChars(shared_ptr<Graphics> g, const shared_ptr<String> data, int offset, int length, int x, int y) ;
	virtual int getFace();
	virtual int getStyle();
	virtual int getSize();
	virtual shared_ptr<NativeFont> getNativeFont();
};
__GUI_END_NAMESPACE

#endif
