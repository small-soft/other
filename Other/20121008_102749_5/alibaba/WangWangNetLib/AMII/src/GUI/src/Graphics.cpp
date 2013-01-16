#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

Graphics::Graphics( shared_ptr<NativeGraphics> nativeGraphics ) 
{
	xTranslate = 0;
	yTranslate = 0;
	color = 0;
	setGraphics(nativeGraphics);
	current = Font::getDefaultFont();
	impl = Display::getInstance()->getImplementation();
}

Graphics::~Graphics(void)
{
}
void Graphics::setGraphics( shared_ptr<NativeGraphics> g )
{
	 this->nativeGraphics = g;
}

shared_ptr<NativeGraphics> Graphics::getGraphics()
{
	return this->nativeGraphics;
}

void Graphics::translate(int x, int y)
{
	if(impl->isTranslationSupported()) 
	{
		impl->translate(nativeGraphics, x, y);
	} 
	else 
	{
		xTranslate += x;
		yTranslate += y;
	}
}

int Graphics::getTranslateX()
{
	if(impl->isTranslationSupported()) 
	{
		return impl->getTranslateX(nativeGraphics);
	}
	else
	{
		return xTranslate;
	}
}

int Graphics::getTranslateY()
{
	if(impl->isTranslationSupported()) 
	{
		return impl->getTranslateY(nativeGraphics);
	}
	else
	{
		return yTranslate;
	}
}

int Graphics::getColor()
{
	return this->color;
}

void Graphics::setColor(int RGB)
{
	this->color = 0xFFFFFF & RGB;
	impl->setColor(nativeGraphics, color);
}


shared_ptr<Font> Graphics::getFont()
{
	return this->current;
}

void Graphics::setFont(shared_ptr<Font> font)
{
	this->current = font;
	
	// not support customFont
	/*
	if(!(typeid(*font) == typeid(CustomFont)))
	{
		impl->setNativeFont(nativeGraphics, font->getNativeFont());
	}
	*/
	impl->setNativeFont(nativeGraphics, font->getNativeFont());
}

int Graphics::getClipX()
{
	return impl->getClipX(nativeGraphics) - xTranslate;
}

int Graphics::getClipY()
{
	return impl->getClipY(nativeGraphics) - yTranslate;
}

int Graphics::getClipWidth()
{
	return impl->getClipWidth(nativeGraphics);
}

int Graphics::getClipHeight()
{
	return impl->getClipHeight(nativeGraphics);
}

void Graphics::clipRect(int x, int y, int width, int height)
{
	impl->clipRect(nativeGraphics, xTranslate + x, yTranslate + y, width, height);
}

void Graphics::setClip(int x, int y, int width, int height)
{
	impl->setClip(nativeGraphics, xTranslate + x, yTranslate + y, width, height);
}

void Graphics::drawLine(int x1, int y1, int x2, int y2)
{	
	
	impl->drawLine(nativeGraphics, xTranslate + x1, yTranslate + y1, xTranslate + x2, yTranslate + y2);
}

void Graphics::fillRect(int x, int y, int width, int height)
{
	impl->fillRect(nativeGraphics, xTranslate + x, yTranslate + y, width, height);
}

void Graphics::drawRect(int x, int y, int width, int height)
{	
	impl->drawRect(nativeGraphics, xTranslate + x, yTranslate + y, width, height);
}

void Graphics::drawRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight)
{
	impl->drawRoundRect(nativeGraphics, xTranslate + x, yTranslate + y, width, height, arcWidth, arcHeight);
}

void Graphics::lighterColor(int factor)
{
	int color = getColor();
	int r = color >> 16 & 0xff;
	int g = color >> 8 & 0xff;
	int b = color & 0xff;
	r = min(0xff, r + factor);
	g = min(0xff, g + factor);
	b = min(0xff, b + factor);
	setColor(((r << 16) & 0xff0000) | ((g << 8) & 0xff00) | (b & 0xff));
}

void Graphics::darkerColor(int factor)
{
	int color = getColor();
	int r = color >> 16 & 0xff;
	int g = color >> 8 & 0xff;
	int b = color & 0xff;
	r = max(0, r - factor);
	g = max(0, g - factor);
	b = max(0, b - factor);
	setColor(((r << 16) & 0xff0000) | ((g << 8) & 0xff00) | (b & 0xff));
}

void Graphics::fillRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight)
{
	impl->fillRoundRect(nativeGraphics, xTranslate + x, yTranslate + y, width, height, arcWidth, arcHeight);
}

void Graphics::fillArc(int x, int y, int width, int height, int startAngle, int arcAngle)
{
	impl->fillArc(nativeGraphics, xTranslate + x, yTranslate + y, width, height, startAngle, arcAngle);
}

void Graphics::drawArc(int x, int y, int width, int height, int startAngle, int arcAngle)
{
	impl->drawArc(nativeGraphics, xTranslate + x, yTranslate + y, width, height, startAngle, arcAngle);
}

void Graphics::drawString(shared_ptr<String> str, int x, int y)
{	
	//current->drawChars(this, str, 0, str->size(), x, y);
	// not support customFont
	impl->drawString(nativeGraphics, str, x + xTranslate, y + yTranslate);
	/*if(!(typeid(*current) == typeid(CustomFont))) 
	{
		impl->drawString(nativeGraphics, str, x + xTranslate, y + yTranslate);
	}
	else*/
	{
	//	current->drawChars(this, str, 0, str->size(), x, y);
	}
	
}

void Graphics::drawChar(char character, int x, int y)
{
	shared_ptr<String> str = new String(L"");
	GUI_CHAR charStr[2] = {character, L'\0'};
	*str += charStr;
	drawString(str, x, y);
}

void Graphics::drawChars(shared_ptr<String > data, int offset, int length, int x, int y)
{
	shared_ptr<String> substr = new String(data->toCharArray(), offset, length);
	drawString(substr, x, y);
	// not support customFont
	//if(!(typeid(*current) == typeid(CustomFont))) 
	//{
	//	String *substr = new String(data, offset, length);
	//	drawString(substr, x, y);
	//}
	//else
	//{
	//	CustomFont *f = (CustomFont *)current;
	//	f->drawChars(this, data, offset, length, x, y);
	//}
}

void Graphics::drawImage(shared_ptr<Image> img, int x, int y)
{
//	weak_ptr<Graphics> g = this;
	img->drawImage(this->shared_from_this(), nativeGraphics, x, y);
}

//void Graphics::drawImage(shared_ptr<NativeImage> img, int x, int y)
//{
//	impl->drawImage(nativeGraphics, img, x + xTranslate, y + yTranslate);
//}

void Graphics::drawImage(shared_ptr<NativeImage> img, int x, int y, int transform)
{
	if (transform != 0) 
	{
		impl->drawImageRotated(nativeGraphics, img, x + xTranslate, y + yTranslate, transform);
	}
	else
	{
	//	drawImage(img, x, y);
		impl->drawImage(nativeGraphics, img, x + xTranslate, y + yTranslate);
	}
}

void Graphics::fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	impl->fillTriangle(nativeGraphics, xTranslate + x1, yTranslate + y1, xTranslate + x2, yTranslate + y2, xTranslate + x3, yTranslate + y3);
}

void Graphics::drawRGB(shared_ptr<VectorArray<int> > rgbData, int offset, int x, int y, int w, int h, bool processAlpha)
{
	impl->drawRGB(nativeGraphics, rgbData, offset, x + xTranslate, y + yTranslate, w, h, processAlpha);
}

void Graphics::fillRadialGradient(int startColor, int endColor, int x, int y, int width, int height)
{
	impl->fillRadialGradient(nativeGraphics, startColor, endColor, x + xTranslate, y + yTranslate, width, height);
}

void Graphics::fillRectRadialGradient(int startColor, int endColor, int x, int y, int width, int height, float relativeX, float relativeY, float relativeSize)
{
	impl->fillRectRadialGradient(nativeGraphics, startColor, endColor, x + xTranslate, y + yTranslate, width, height, relativeX, relativeY, relativeSize);
}

void Graphics::fillLinearGradient(int startColor, int endColor, int x, int y, int width, int height, bool horizontal)
{
	impl->fillLinearGradient(nativeGraphics, startColor, endColor, x + xTranslate, y + yTranslate, width, height, horizontal);
}

void Graphics::fillRect(int x, int y, int w, int h, unsigned char alpha)
{
	if(alpha != 0) 
	{
		int oldAlpha = impl->getAlpha(nativeGraphics);
		impl->setAlpha(nativeGraphics, alpha & 0xff);
		impl->fillRect(nativeGraphics, x + xTranslate, y + yTranslate, w, h);
		impl->setAlpha(nativeGraphics, oldAlpha);
	}
}

void Graphics::fillPolygon(shared_ptr<VectorArray<int> > xPoints, shared_ptr<VectorArray<int> > yPoints, int nPoints)
{
	shared_ptr<VectorArray<int> > cX = new VectorArray<int>(nPoints);
	shared_ptr<VectorArray<int> > cY = new VectorArray<int>(nPoints);
	if((!impl->isTranslationSupported()) && (xTranslate != 0 || yTranslate != 0)) 
	{
		for(int iter = 0 ; iter < nPoints ; iter++) 
		{
			(*cX)[iter] = (*xPoints)[iter];
			(*cY)[iter] = (*yPoints)[iter];

			(*cX)[iter] += xTranslate;
			(*cY)[iter] += yTranslate;
		}
	}
	impl->fillPolygon(nativeGraphics, cX, cY, nPoints);
}

void Graphics::drawImageArea(shared_ptr<Image> img, int x, int y, int imageX, int imageY, int imageWidth, int imageHeight)
{
	img->drawImageArea(this->shared_from_this(), nativeGraphics, x, y, imageX, imageY, imageWidth, imageHeight);
}

void Graphics::drawPolygon(shared_ptr<Vector<int> > xPoints, shared_ptr<Vector<int> > yPoints, int nPoints)
{
	shared_ptr<VectorArray<int> > cX = new VectorArray<int>(nPoints);
	shared_ptr<VectorArray<int> > cY = new VectorArray<int>(nPoints);
	if((!impl->isTranslationSupported()) && (xTranslate != 0 || yTranslate != 0)) 
	{
		for(int iter = 0 ; iter < nPoints ; iter++) 
		{
			(*cX)[iter] = xPoints->elementAt(iter);
			(*cY)[iter] = yPoints->elementAt(iter);

			(*cX)[iter] += xTranslate;
			(*cY)[iter] += yTranslate;
		}
	}
	impl->drawPolygon(nativeGraphics, cX, cY, nPoints);
}

bool Graphics::isAlphaSupported()
{
	return impl->isAlphaGlobal();
}

void Graphics::setAlpha(int a)
{
	impl->setAlpha(nativeGraphics, a);
}

int Graphics::getAlpha()
{
	return impl->getAlpha(nativeGraphics);
}

bool Graphics::isAntiAliasingSupported()
{
	return impl->isAntiAliasingSupported();
}

bool Graphics::isAntiAliasedTextSupported()
{
	return impl->isAntiAliasedTextSupported();
}

bool Graphics::isAntiAliased()
{
	return impl->isAntiAliased(nativeGraphics);
}

void Graphics::setAntiAliased(bool a)
{
	impl->setAntiAliased(nativeGraphics, a);
}

void Graphics::setAntiAliasedText(bool a)
{
	impl->setAntiAliasedText(nativeGraphics, a);
}

bool Graphics::isAntiAliasedText(bool a)
{
	return impl->isAntiAliasedText(nativeGraphics);
}

bool Graphics::isAffineSupported()
{
	return impl->isAffineSupported();
}

void Graphics::resetAffine()
{
	impl->resetAffine(nativeGraphics);
}

void Graphics::scale(float x, float y)
{
	impl->scale(nativeGraphics, x, y);
}

void Graphics::rotate(float angle)
{
	impl->rotate(nativeGraphics, angle);
}

void Graphics::shear(float x, float y)
{
	impl->shear(nativeGraphics, x, y);
}
void Graphics::BitBlt( shared_ptr<Image> src,int x,int y )
{
	impl->BitBlt(nativeGraphics, src->getGraphics()->getGraphics(), x ,y ,src->getWidth(),src->getHeight());
}
//int Graphics::getFgColor()
//{
//	return fgColor;
//}
//
//void Graphics::setFgColor( int RGB )
//{
//	this->fgColor = 0xFFFFFF & RGB;
//	impl->setFgColor(nativeGraphics, fgColor);
//}
//
//int Graphics::getBgColor()
//{
//	return this->bgColor;
//}
//
//void Graphics::setBgColor( int RGB )
//{
//	this->bgColor = 0xFFFFFF & RGB;
//	impl->setBgColor(nativeGraphics, bgColor);
//}
__GUI_END_NAMESPACE

