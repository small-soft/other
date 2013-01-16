#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

shared_ptr<Font> Font::defaultFont ;//= new Font(FACE_MONOSPACE, STYLE_PLAIN, SIZE_MEDIUM);

shared_ptr<Map<String, shared_ptr<Font> > >  Font::bitmapCache = new Map<String, shared_ptr<Font> >();

bool Font::enableBitmapFont = true;

Font::Font(void)
{
}

Font::Font( shared_ptr<NativeFont>  nativeFont )
: font(nativeFont)
{

}

Font::Font( int face, int style, int size )
{
	font = Display::getInstance()->getImplementation()->createFont(face, style, size);
}
Font::~Font(void)
{

}
void Font::deinitialize()
{
	defaultFont.reset();
	bitmapCache.reset();

}
shared_ptr<Font> Font::getBitmapFont(shared_ptr<String> fontName )
{
	 return (*bitmapCache)[*fontName];
}

void Font::clearBitmapCache()
{
	bitmapCache->clear();
}

bool Font::isTrueTypeFileSupported()
{
	return Display::getInstance()->getImplementation()->isTrueTypeSupported();
}

bool Font::isCreationByStringSupported()
{
	return Display::getInstance()->getImplementation()->isLookupFontSupported();
}

shared_ptr<Font> Font::createTrueTypeFont(shared_ptr<InputStream> stream)
{
	// to check iostream的问题
	//shared_ptr<Object> trueTypeFont = Display::getInstance()->getImplementation()->loadTrueTypeFont(*stream);
	shared_ptr<Font> resFont;// = new Font(trueTypeFont);
	return resFont;
}

shared_ptr<Font> Font::create(shared_ptr<String> lookup)
{
	shared_ptr<NativeFont> nativeFont = Display::getInstance()->getImplementation()->loadNativeFont(lookup);
	shared_ptr<Font> resFont = new Font(nativeFont);
	return resFont;
}

void Font::addContrast(unsigned char value)
{
}

shared_ptr<Font> Font::createBitmapFont(shared_ptr<String> name, shared_ptr<Image> bitmap, 
					shared_ptr<VectorArray<int> > cutOffsets, shared_ptr<VectorArray<int> > charWidth, shared_ptr<String> charsets)
{
	shared_ptr<Font> f = createBitmapFont(bitmap, cutOffsets, charWidth, charsets);
	bitmapCache->put(*name, f);
	return f;
}
shared_ptr<Font> Font::createBitmapFont(shared_ptr<Image> bitmap, shared_ptr<VectorArray<int> > cutOffsets, 
										shared_ptr<VectorArray<int> > charWidth, shared_ptr<String> charsets)
{
	// to check CustomFont类不存在
	shared_ptr<Font> font;// = new CustomFont(bitmap, cutOffsets, charWidth, charsets);
	return font;
}

shared_ptr<Font> Font::createSystemFont(int face, int style, int size)
{
	shared_ptr<Font> resFont = new Font(face, style, size);
	return resFont;
}

int Font::charsWidth(shared_ptr<String> ch, int offset, int length)
{
	return Display::getInstance()->getImplementation()->charsWidth(font, ch, offset, length);
}

int Font::substringWidth(shared_ptr<String> str, int offset, int len)
{
	shared_ptr<String> subString = &(str->substr(offset, offset + len));
	return Display::getInstance()->getImplementation()->stringWidth(font, subString);
}

int Font::stringWidth(shared_ptr<String> str)
{
	shared_ptr<LWUITImplementation> lwuitImp = Display::getInstance()->getImplementation();

	int width =  lwuitImp->stringWidth(font, str);

	return width;
}

int Font::charWidth(char ch)
{
	return Display::getInstance()->getImplementation()->charWidth(font, ch);
}

int Font::getHeight()
{
	return Display::getInstance()->getImplementation()->getHeight(font);
}

void Font::drawChar(shared_ptr<Graphics> g, char character, int x, int y)
{
}

shared_ptr<Font> Font::getDefaultFont()
{
	if ( defaultFont.get() == NULL )
	{
		defaultFont = new Font();
	}
	return defaultFont;
}

void Font::setDefaultFont(shared_ptr<Font> f)
{
	if(f.get() != NULL) {
		defaultFont = f;
	}
}

void Font::drawChars(shared_ptr<Graphics> g, const shared_ptr<String> data,int offset, int length, int x, int y) 
{

}

int Font::getFace()
{
	return Display::getInstance()->getImplementation()->getFace(font);
}

int Font::getSize()
{
	return Display::getInstance()->getImplementation()->getSize(font);
}

int Font::getStyle()
{
	return Display::getInstance()->getImplementation()->getStyle(font);
}

shared_ptr<String> Font::getCharset()
{
	shared_ptr<String> nullString;
	return nullString;
}

void Font::setBitmapFontEnabled(bool enabled)
{
	enableBitmapFont = enabled;
}

bool Font::isBitmapFontEnabled()
{
	return enableBitmapFont;
}

shared_ptr<NativeFont> Font::getNativeFont()
{
	return font;
}

bool Font::operator!=( const Font & f)
{
	return !(font == f.font);
}

bool Font::operator ==(const Font& f)
{
	return (font == f.font);
}


__GUI_END_NAMESPACE

