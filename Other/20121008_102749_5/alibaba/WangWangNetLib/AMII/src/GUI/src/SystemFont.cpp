#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
//static shared_ptr<Font> defaultFont;
SystemFont::SystemFont(shared_ptr<NativeFont> font)
:font(font)
{

}

SystemFont::SystemFont( int face, int style, int size )
{
	font = Display::getInstance()->getImplementation()->createFont(face, style, size);
}
SystemFont::~SystemFont(void)
{

}

int SystemFont::charWidth( char ch )
{
	return Display::getInstance()->getImplementation()->charWidth(font, ch);
}

int SystemFont::charsWidth(shared_ptr<String> ch, int offset, int length)
{	

	return Display::getInstance()->getImplementation()->charsWidth(font, ch, offset, length);
}

int SystemFont::substringWidth( shared_ptr<String> str, int offset, int len )
{
	shared_ptr<String> subStr = new String(str->substr(offset, offset + len));
	return Display::getInstance()->getImplementation()->stringWidth(font, subStr);
}

int SystemFont::getHeight()
{
	return Display::getInstance()->getImplementation()->getHeight(font);
}

int SystemFont::stringWidth( shared_ptr<String> str )
{
	return Display::getInstance()->getImplementation()->stringWidth(font, str);
}

void SystemFont::drawChar( shared_ptr<Graphics> g, char character, int x, int y )
{

}

void SystemFont::drawChars(shared_ptr<Graphics> g, const shared_ptr<String> data, int offset, int length, int x, int y)
//void SystemFont::drawChars( shared_ptr<Graphics> g, char* data, int offset, int length, int x, int y )
{

}

int SystemFont::getFace()
{	
	return Display::getInstance()->getImplementation()->getFace(font);
}

int SystemFont::getStyle()
{
	 return Display::getInstance()->getImplementation()->getStyle(font);
}

int SystemFont::getSize()
{
	 return Display::getInstance()->getImplementation()->getSize(font);
}

shared_ptr<NativeFont> SystemFont::getNativeFont()
{
	 return font;
}
__GUI_END_NAMESPACE
