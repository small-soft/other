#include "AMGui.h"
#include "AMHDev.h"
#include "AMGDI.h"

__GUI_BEGIN_NAMESPACE
bool AliImplementation::NOKIA = false;
int AliImplementation::backSK = -11;
int AliImplementation::clearSK = -8;
int AliImplementation::backspaceSK = -8;
bool AliImplementation::drawNegativeOffsetsInRGB = true;
shared_ptr<Vector<int> > AliImplementation::leftSK;// = new Vector<int>();
shared_ptr<Vector<int> > AliImplementation::rightSK;// = new Vector<int>();

int AliImplementation::portableKeyCodes[5] = {0};// new Vector<int>();
int AliImplementation::portableKeyCodeValues[5] = {0};// new Vector<int>();
AliImplementation::AliImplementation()
{
	minimized = false;
	alpha = 255;
	flushGraphicsBug = false;
}
int AliImplementation::getKeyboardType()
{
	int type = AMGuiGetKeyboardType();
	if(type == KEYBOARD_VIRTUAL)
	{
		return Display::KEYBOARD_TYPE_VIRTUAL;
	}
	if(type == KEYBOARD_NUMERIC)
	{
		return Display::KEYBOARD_TYPE_NUMERIC;
	}
	if(type == KEYBOARD_HALF_QWERTY)
	{
		return Display::KEYBOARD_TYPE_HALF_QWERTY;
	}
	if(type == KEYBOARD_QWERTY)
	{
		return Display::KEYBOARD_TYPE_QWERTY;
	}
	else
		return LWUITImplementation::getKeyboardType();
}

AliImplementation::~AliImplementation()
{
	leftSK.reset();
	rightSK.reset();
}
void AliImplementation::init(void *m)
{
	leftSK = new Vector<int>();
	rightSK = new Vector<int>();
	leftSK->addElement(KEY_LEFTSK);
	rightSK->addElement(KEY_RIGHTSK);

	AMGraphics g;
	AMCreateSystemGraphics(&g,m);
	screen_graphics = new NativeGraphics(g);

	GUI_CHAR platForm[32] = {0};
	AMGuiGetSysInfo(MICROEDITION_PLATFORM,platForm);
	String platform(platForm);
	int index;
	for (index = 0; index < platform.length(); ++index)
	{
		toupper(platform[index]);
	}

	if (!platform.empty() && AMWcsstr((const AMWChar*)platform.toCharArray(), (const AMWChar*)L"NOKIA") != NULL)
	{
		flushGraphicsBug = false;
		Display::getInstance()->setTransitionYield(1);
	}
	else
	{
		flushGraphicsBug = true;
		Display::getInstance()->setTransitionYield(-1);
	}
	
	setSoftKeyCodes();
	initKeyMap();
}
void AliImplementation::setSoftKeyCodes()
{
	leftSK->addElement(KEY_LEFTSK);
	rightSK->addElement(KEY_RIGHTSK);
	clearSK =(KEY_CLEARSK);
	backspaceSK =(KEY_BACKSPACESK);
}

void AliImplementation::initKeyMap()
{
	portableKeyCodes[0] = Display::GAME_DOWN;
	portableKeyCodes[1] = Display::GAME_LEFT;
	portableKeyCodes[2] = Display::GAME_RIGHT;
	portableKeyCodes[3] = Display::GAME_UP;
	portableKeyCodes[4] = Display::GAME_FIRE;

	portableKeyCodeValues[0] = KEY_DOWN;
	portableKeyCodeValues[1] = KEY_LEFT;
	portableKeyCodeValues[2] = KEY_RIGHT;
	portableKeyCodeValues[3] = KEY_UP;
	portableKeyCodeValues[4] = KEY_OK;
}
void AliImplementation::setFireValue(int key)
{
//	getKeyCode(0);
	portableKeyCodeValues[4] = key;
}
void AliImplementation::vibrate(int duration){}
void AliImplementation::flashBacklight(int duration){}
int AliImplementation::getDisplayWidth()
{
	return AMGetGraphicWidth(screen_graphics->getNative());
}
int AliImplementation::getDisplayHeight()
{
	return AMGetGraphicHeigth(screen_graphics->getNative());
}
void AliImplementation::editString(shared_ptr<Component> cmp, int maxSize, int constraint, shared_ptr<String> text){}
void AliImplementation::saveTextEditingState(){}
void AliImplementation::setFlashGraphicsBug(bool flushGraphicsBug)
{
	this->flushGraphicsBug = flushGraphicsBug;
}
void AliImplementation::flushGraphics(int x, int y, int width, int height)
{
	AMGraphics pGraphics = (AMGraphics)screen_graphics->getNative();
	AMRect rectRect = {x, y, width, height};
	AMUpdateRect(pGraphics, &rectRect);
}
void AliImplementation::flushGraphics(){
	flushGraphics(0, 0, this->getDisplayWidth(), this->getDisplayHeight());
}
void AliImplementation::getRGB(shared_ptr<NativeImage> nativeImage, shared_ptr<VectorArray<int> > arr, int offset, int x, int y, int width, int height)
{
	AMImage image = (AMImage)nativeImage->getNative();
	int size = width * height;
	int *prgb = new int[size];
	memset(prgb, 0, sizeof(char) * size);
	AMGetImageBuffer(image, x, y, width, height, prgb);
	memcpy(arr->getDataAddress() + offset, prgb, size * sizeof(int));
	delete []prgb;
}

shared_ptr<NativeImage> AliImplementation::createImage(shared_ptr<VectorArray<int> > rgb, int width, int height)
{
	AMImage image = NULL;
	int size = width*height;
	int* pRGB = new int[size];
	memset(pRGB, 0, size*sizeof(int));
	memcpy(pRGB, rgb->getDataAddress(), size * sizeof(int));
	AMCreateImageFromRGB(&image, pRGB, width, height);
	delete[] pRGB;	
	return new NativeImage(image);
}

shared_ptr<NativeImage> AliImplementation::createImage(shared_ptr<String> path)
{
	AMImage image;
	AMCreateImageFromFile( &image, (AMWChar *)path->toCharArray());

	shared_ptr<NativeImage> res = new NativeImage(image);
	return res;
}
shared_ptr<NativeImage> AliImplementation::createImage(shared_ptr<InputStream> i)
{
	AMAssert(0);
	return new NativeImage();
}
shared_ptr<NativeImage> AliImplementation::createMutableImage(int width, int height,int fillColor)
{
	AMImage image = NULL;
	int* pRGB = new int[width*height];
	memset(pRGB, fillColor, width*height*sizeof(int));
	AMCreateImageFromRGB(&image, pRGB, width, height);
	delete[] pRGB;
	return new NativeImage(image);
}

shared_ptr<NativeImage> AliImplementation::createImage(VectorArray<unsigned char> bytes, int offset, int len)
{
	AMImage image = NULL;
	int size = len - offset;
	char *rgb = new char[size];
	memset(rgb, 0, (size) * sizeof(char));
	memcpy(rgb, bytes.getDataAddress() + offset, (size) * sizeof(char));
	AMCreateImage(&image, rgb, size);
	delete []rgb;

	shared_ptr<NativeImage> res = new NativeImage(image);
	return res;
}
int AliImplementation::getImageWidth(shared_ptr<NativeImage> i)
{
	AMImage image = (AMImage)i->getNative();
	return AMGetWidth(image);
}
int AliImplementation::getImageHeight(shared_ptr<NativeImage> i)
{
	AMImage image = (AMImage)i->getNative();
	return AMGetHeight(image);
}
shared_ptr<NativeImage> AliImplementation::scale(shared_ptr<NativeImage> nativeImage, int width, int height)
{
	AMImage image = (AMImage)nativeImage->getNative();
	int srcWidth = AMGetWidth(image);
	int srcHeight = AMGetHeight(image);

//	weak_ptr<Object> resImage = (Object *)image;
	// no need to scale
	if (srcWidth == width && srcHeight == height) 
	{	
		return nativeImage;
	}

	shared_ptr<VectorArray<int> > currentArray = new VectorArray<int>(srcWidth);
	shared_ptr<VectorArray<int> > destinationArray = new VectorArray<int>(width * height);

	scaleArray(nativeImage, srcWidth, srcHeight, height, width, currentArray, destinationArray);

	return createImage(destinationArray, width, height);
}
void AliImplementation::scaleArray(shared_ptr<NativeImage> currentImage, int srcWidth, int srcHeight, int height, int width, shared_ptr<VectorArray<int> > currentArray, shared_ptr<VectorArray<int> > destinationArray)
{
	int yRatio = (srcHeight << 16) / height;
	int xRatio = (srcWidth << 16) / width;
	int xPos = xRatio / 2;
	int yPos = yRatio / 2;

	// if there is more than 16bit color there is no point in using mutable
	// images since they won't save any memory
	for (int y = 0; y < height; y++)
	{
		int srcY = yPos >> 16;
		getRGB(currentImage, currentArray, 0, 0, srcY, srcWidth, 1);
		for (int x = 0; x < width; x++)
		{
			int srcX = xPos >> 16;
			int destPixel = x + y * width;
			if ((destPixel >= 0 && destPixel < destinationArray->size()) && (srcX < currentArray->size()))
			{
				(*destinationArray)[destPixel] = (*currentArray)[srcX];
			}
			xPos += xRatio;
		}
		yPos += yRatio;
		xPos = xRatio / 2;
	}
}
void AliImplementation::drawImageRotated(shared_ptr<NativeGraphics> graphics, shared_ptr<Object> img, int x, int y, int degrees){}
bool AliImplementation::isRotationDrawingSupported()
{
	return true;
}
int AliImplementation::getSoftkeyCount()
{
	return 2;
}
shared_ptr<Vector<int> > AliImplementation::getSoftkeyCode(int index)
{
	shared_ptr<Vector<int> > res = new Vector<int>();
	if (index == 0)
	{
		res = leftSK;
	}

	if (index == 1)
	{
		res = rightSK;
	}
	return res;
}
int AliImplementation::getClearKeyCode()
{
	return clearSK;
}
int AliImplementation::getBackspaceKeyCode()
{
	return backspaceSK;
}
int AliImplementation::getBackKeyCode()
{
	return backSK;
}
int AliImplementation::getGameAction(int keyCode)
{
	for (int iter = 0; iter < 5; iter++) 
	{
		if (portableKeyCodeValues[iter] == keyCode) 
		{
			return portableKeyCodes[iter];
		}
	}

	return 0;
}
int AliImplementation::getKeyCode(int gameAction)
{
	for (int iter = 0; iter < 5; iter++) 
	{
		if (portableKeyCodes[iter] == gameAction) 
		{
			return portableKeyCodeValues[iter];
		}

	}
	return 0;
}
bool AliImplementation::isTouchDevice(){return false;}
void AliImplementation::setNativeFont(shared_ptr<NativeGraphics> graphics, shared_ptr<NativeFont> font)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMFont pFont = (AMFont)font->getNative();
	AMSetFont(pGraphics, pFont);
}
int AliImplementation::getClipX(shared_ptr<NativeGraphics> graphics)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	return AMGetClipX(pGraphics);
}
int AliImplementation::getClipY(shared_ptr<NativeGraphics> graphics)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	return AMGetClipY(pGraphics);
}
int AliImplementation::getClipWidth(shared_ptr<NativeGraphics> graphics)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	return AMGetClipWidth(pGraphics);
}
int AliImplementation::getClipHeight(shared_ptr<NativeGraphics> graphics)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	return AMGetClipHeight(pGraphics);
}
void AliImplementation::setClip(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMRect rectRect = {x, y, width, height};
	AMSetClip(pGraphics, &rectRect);
}
void AliImplementation::clipRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMRect rectRect = {x, y, width, height};
	AMClipRect(pGraphics, &rectRect);
}
void AliImplementation::drawLine(shared_ptr<NativeGraphics> graphics, int x1, int y1, int x2, int y2)
{
	AMPoint point1 = {x1, y1};
	AMPoint point2 = {x2, y2};

	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMSetFGColor(pGraphics,AMGetColor(pGraphics));
	AMDrawLine(pGraphics, &point1, &point2);
}
void AliImplementation::fillRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height)
{
	int alpha = getAlpha(graphics);
	if (isAlphaGlobal() )
	{
		AMRect rectRect = {x, y, width, height};
		AMGraphics pGraphics = (AMGraphics)graphics->getNative();
		AMSetBGColor(pGraphics,AMGetColor(pGraphics));
		AMFillRect(pGraphics, &rectRect);
		return;
	}

	if (alpha == 0)
	{
		return;
	}

	if (alpha == 0xff) 
	{
		AMGraphics pGraphics = (AMGraphics)graphics->getNative();
		AMRect rectRect = {x, y, width, height};
		AMSetBGColor(pGraphics,AMGetColor(pGraphics));
		AMFillRect(pGraphics, &rectRect);
	}
	else
	{
		int transparencyLevel = alpha << 24;
		int color = (getColor(graphics) & 0x00FFFFFF);
		color = (color | transparencyLevel);
	
	
		if (rgbArr.get() == NULL || rgbArr->size() < width)
		{
			rgbArr = new VectorArray<int>(width);
		}
	
		for (int i = 0; i <	width; i++)
		{
			(*rgbArr)[i] = color;
		}
	
		int rgbX = x;
		int rgbY = y;
	
	
		if (rgbX < 0 && rgbX + width > 0)
		{
			width = rgbX + width;
			rgbX = 0;
		}
	
		if (width < 0)
		{
			return;
		}
	
		int clipY = getClipY(graphics);
		int clipHeight = getClipHeight(graphics);
		int clipBottomY = clipHeight + clipY;
	
		for (int i = 0; i < height; i++)
		{
			if (rgbX >= 0 && rgbY + i >= 0)
			{
				int currentY = rgbY + i;
				if(currentY >= clipY && currentY <= clipBottomY)
				{
					drawRGB(graphics, rgbArr, 0, rgbX, currentY, width, 1, true);
				}
			}
	
		}
	}
}
void AliImplementation::drawRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height)
{
	
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMSetFGColor(pGraphics,AMGetColor(pGraphics));
	AMRect rectRect = {x, y, width, height};
	
	AMDrawRect(pGraphics, &rectRect);
}
void AliImplementation::drawRoundRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int arcWidth, int arcHeight)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMSetFGColor(pGraphics,AMGetColor(pGraphics));
	AMRect rectRect = {x, y, width, height};
	AMDrawRoundRect(pGraphics, &rectRect, arcWidth, arcHeight);
}
void AliImplementation::fillRoundRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int arcWidth, int arcHeight)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMRect rectRect = {x, y, width, height};
	AMFillRoundRect(pGraphics, &rectRect, arcWidth, arcHeight);
}
void AliImplementation::fillArc(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int startAngle, int arcAngle)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMRect rectRect = {x, y, width, height};
	AMSetBGColor(pGraphics,AMGetColor(pGraphics));
	AMFillArc(pGraphics, &rectRect, startAngle, arcAngle);
}
void AliImplementation::drawArc(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int startAngle, int arcAngle)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMSetFGColor(pGraphics,AMGetColor(pGraphics));
	AMRect rectRect = {x, y, width, height};
	AMDrawArc(pGraphics, &rectRect, startAngle, arcAngle);
}

int AliImplementation::getColor(shared_ptr<NativeGraphics> graphics)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	return AMGetColor(pGraphics);
}
void AliImplementation::setColor(shared_ptr<NativeGraphics> graphics, int RGB)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMSetColor(pGraphics, RGB);
}

void AliImplementation::setAlpha(shared_ptr<NativeGraphics> graphics, int alpha)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMSetAlpha(pGraphics, alpha);
}
int AliImplementation::getAlpha(shared_ptr<NativeGraphics> graphics)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	return AMGetAlpha(pGraphics);
}
void AliImplementation::drawString(shared_ptr<NativeGraphics> graphics, shared_ptr<String> str, int x, int y)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMPoint point = {x, y};
	AMSetFGColor(pGraphics,AMGetColor(pGraphics));
	AMDrawText(pGraphics, (AMWChar *)str->toCharArray(), &point, 0, str->size());
}
void AliImplementation::drawImage(shared_ptr<NativeGraphics> graphics, shared_ptr<NativeImage> img, int x, int y)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMPoint point = {x, y};
	AMImage pImage = (AMImage)img->getNative();
	AMDrawImage(pGraphics, &point, pImage, AMDM_SCR);
}
void AliImplementation::fillTriangle(shared_ptr<NativeGraphics> graphics, int x1, int y1, int x2, int y2, int x3, int y3)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMPoint point1 = {x1, y1};
	AMPoint point2 = {x2, y2};
	AMPoint point3 = {x3, y3};
	AMSetBGColor(pGraphics,AMGetColor(pGraphics));
	AMFillTriangle(pGraphics, &point1, &point2, &point3);
}
void AliImplementation::drawRGB(shared_ptr<NativeGraphics> graphics, shared_ptr<VectorArray<int> > rgbData, int offset, int x, int y, int w, int h, bool processAlpha)
{
	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMPoint point = {x, y};
	shared_ptr<NativeImage> img = createImage(rgbData, w,  h);
	AMImage pImage = (AMImage)img->getNative();	
	AMDrawImage(pGraphics, &point, pImage, AMDM_SCR);
}
shared_ptr<Object> AliImplementation::getVideoControl(shared_ptr<Object> player)
{
	shared_ptr<Object> res;
	return res;
}
int AliImplementation::numAlphaLevels(){return 0;}
int AliImplementation::numColors(){return 0;}
void AliImplementation::playDialogSound(const int type){}
void AliImplementation::confirmControlView(){}
//void AliImplementation::setCurrent(shared_ptr<Object> d){}
shared_ptr<NativeGraphics> AliImplementation::getNativeGraphics()
{
	
	return screen_graphics;
}
shared_ptr<NativeGraphics> AliImplementation::getNativeGraphics(shared_ptr<NativeImage> image)
{
	AMGraphics graphics = NULL;
	AMCreateImageGraphics(&graphics, (AMImage)(image->getNative()));
	shared_ptr<NativeGraphics> res = new NativeGraphics(graphics);
	return res;
}
void AliImplementation::translate(shared_ptr<NativeGraphics> graphics, int x, int y)
{
	// does nothing, we expect translate to occur in the graphics for
	// better device portability
	//AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	//AMTranslate(pGraphics, x, y);
}
int AliImplementation::getTranslateX(shared_ptr<NativeGraphics> graphics)
{	
	/*AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	AMGetTranslateX(pGraphics);*/
	return 0;
}
int AliImplementation::getTranslateY(shared_ptr<NativeGraphics> graphics)
{	
	//AMGraphics pGraphics = (AMGraphics)graphics->getNative();
	//AMGetTranslateY(pGraphics);
	return 0;
}
int AliImplementation::charsWidth(shared_ptr<NativeFont> nativeFont, shared_ptr<String> ch, int offset, int length)
{
	AMFont font = (AMFont)nativeFont->getNative();
	return AMCharsWidth(font, (AMWChar *)(ch->toCharArray() + offset), length);
}
int AliImplementation::stringWidth(shared_ptr<NativeFont> nativeFont, shared_ptr<String> str)
{
	return charsWidth(nativeFont, str, 0, str->length());
}
int AliImplementation::charWidth(shared_ptr<NativeFont> nativeFont, char ch)
{
	shared_ptr<String> str;
	GUI_CHAR chars[2] = {ch, '\0'};
	*str += chars;
	return charsWidth(nativeFont, str, 0, 1);
}
int AliImplementation::getHeight(shared_ptr<NativeFont> nativeFont){
	return AMCharHeight(nativeFont->getNative());
}
shared_ptr<NativeFont> AliImplementation::createFont(int face, int style, int size)
{
	AMFont font;
	AMCreateSystemFont(&font, (AMFontFace)face, (AMFontStyle)style, (AMFontSize)size);

	shared_ptr<NativeFont> res = new NativeFont(font);
	return res;
}
shared_ptr<NativeFont> AliImplementation::getDefaultFont()
{
	shared_ptr<NativeFont> res = new NativeFont(AMGetFont(screen_graphics->getNative()));
	return res;
}
int AliImplementation::getFace(shared_ptr<NativeFont> nativeFont)
{
	AMFont font = (AMFont)nativeFont->getNative();
	return AMGetFace(font);
}
int AliImplementation::getSize(shared_ptr<NativeFont> nativeFont)
{
	AMFont font = (AMFont)nativeFont->getNative();
	return AMGetSize(font);
}
int AliImplementation::getStyle(shared_ptr<NativeFont> nativeFont)
{
	AMFont font = (AMFont)nativeFont->getNative();
	return AMGetStyle(font);
}
shared_ptr<Font> AliImplementation::font(shared_ptr<NativeFont> f)
{
	if (f.get() == NULL)
	{
		f = getDefaultFont();
	}
	return dynamic_pointer_cast<Font>(f);
}
shared_ptr<Object> AliImplementation::createVideoComponent(shared_ptr<Object> player){return player;}
int AliImplementation::getVideoWidth(shared_ptr<Object> videoControl){return 0;}
int AliImplementation::getVideoHeight(shared_ptr<Object> videoControl){return 0;}
void AliImplementation::setVideoVisible(shared_ptr<Object> vc, bool visible){}
void AliImplementation::startVideo(shared_ptr<Object> player, shared_ptr<Object> videoControl){}
void AliImplementation::stopVideo(shared_ptr<Object> player, shared_ptr<Object> videoControl){}
void AliImplementation::setVideoLoopCount(shared_ptr<Object> player, int count){}
long AliImplementation::getMediaTime(shared_ptr<Object> player){return 0;}
long AliImplementation::setMediaTime(shared_ptr<Object> player, long now){return 0;}
void AliImplementation::paintVideo(shared_ptr<Component> cmp, bool fullScreen, shared_ptr<Object> nativeGraphics, shared_ptr<Object> video, shared_ptr<Object> player){}

void AliImplementation::BitBlt( shared_ptr<NativeGraphics> dest, shared_ptr<NativeGraphics> src, int x, int y,int width,int height )
{
	AMPoint point = {0, 0};
	AMGraphics destG = (AMGraphics)dest->getNative();
	AMGraphics srcG = (AMGraphics)src->getNative();
	AMRect rect =  {0, 0, width, height};
	AMBitBlt(destG, &rect, srcG, &point, AMDM_SCR);
}

void AliImplementation::updateRect( int x, int y ,int width, int height )
{
	AMRect rect = {x, y ,width, height};
	AMGraphics g = (AMGraphics)screen_graphics->getNative();
	AMUpdateRect(g,&rect);
}
//int AliImplementation::getBgColor( shared_ptr<NativeGraphics> graphics )
//{
//	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
//	return AMGetBGColor(pGraphics);
//}
//
//void AliImplementation::setBgColor( shared_ptr<NativeGraphics> graphics, int RGB )
//{
//	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
//	AMSetBGColor(pGraphics, RGB);
//}
//
//int AliImplementation::getFgColor( shared_ptr<NativeGraphics> graphics )
//{
//	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
//	return AMGetFGColor(pGraphics);
//}
//
//void AliImplementation::setFgColor( shared_ptr<NativeGraphics> graphics, int RGB )
//{
//	AMGraphics pGraphics = (AMGraphics)graphics->getNative();
//	AMSetFGColor(pGraphics, RGB);
//}
__GUI_END_NAMESPACE

