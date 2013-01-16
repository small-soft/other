#include "AMGui.h"
#include "AMGDI.h"
#include <stdlib.h>

__GUI_BEGIN_NAMESPACE

shared_ptr<Locker> LWUITImplementation::displayLock ;//= new Locker();
int LWUITImplementation::MAX_COUNT = 50 ;
const double PI = acos(-1.0);

LWUITImplementation::LWUITImplementation():dragActivationCounter(0), dragActivationX(0), dragActivationY(0), dragStartPercentage(3),paintQueueFill(0)
{
	pointerPressedX = 0;
	pointerPressedY = 0;

	bidi = false;
	this->paintQueue = new VectorArray< shared_ptr<Animation> >(50);
	this->paintQueueTemp = new VectorArray< shared_ptr<Animation> >(50);
	this->xPointerEvent = new VectorArray<int>(1);
	this->yPointerEvent = new VectorArray<int>(1);
}

void LWUITImplementation::playDialogSound(const int type)
{

}

void LWUITImplementation::vibrate(int duration)
{
}

void LWUITImplementation::flashBacklight(int duration)
{
}

bool LWUITImplementation::handleEDTException(exception err)
{
	return false;
}

void LWUITImplementation::saveTextEditingState()
{

}

bool LWUITImplementation::hasPendingPaints()
{
	return paintQueueFill != 0;
}

shared_ptr<Object> LWUITImplementation::getVideoControl(shared_ptr<Object> player)
{
	shared_ptr<Object> res;
	return res;
}

int LWUITImplementation::numAlphaLevels()
{
	return 255;
}

int LWUITImplementation::numColors()
{
	return 65536;
}

void LWUITImplementation::paintOverlay(shared_ptr<Graphics> g)
{

}

void LWUITImplementation::paintDirty()
{
	int size = 0;
	displayLock->lock();

	size = paintQueueFill;
	shared_ptr<VectorArray<shared_ptr<Animation> > >  arrayAni = paintQueue;
	paintQueue = paintQueueTemp;
	paintQueueTemp = arrayAni;
	paintQueueFill = 0;

	displayLock->unlock();

	//add by jiajing for painting speed
	for(int i = 0 ; i < size; i ++)
	{
		shared_ptr<Animation> ani = (*arrayAni)[i];
		if( ani.get() == NULL )
		{
			continue;
		}

		Component* cmp = dynamic_cast<Component*>(ani.get());
		if (cmp != NULL)
		{
			shared_ptr<Component> cmp = dynamic_pointer_cast<Component> (ani);
			Dialog* dlg = dynamic_cast<Dialog*>(cmp.get());
			if(cmp == getCurrentForm() && !(dlg != NULL))
			{
				(*paintQueueTemp)[0] = cmp;
				size = 1;
				break;
			}
		}
	}
	//end add
	if (size > 0) 
	{	
	//	printf("paint start:%d\n",System::currentTimeMillis());
		shared_ptr<Graphics>  wrapper = getLWUITGraphics();
		int topX = getDisplayWidth();
		int topY = getDisplayHeight();
		int bottomX = 0;
		int bottomY = 0;
		for (int iter = 0; iter < size; iter++)
		{
			shared_ptr<Animation> ani = (*paintQueueTemp)[iter];
			wrapper->translate(-wrapper->getTranslateX(), -wrapper->getTranslateY());
			wrapper->setClip(0, 0, getDisplayWidth(), getDisplayHeight());
			Component* cmp = dynamic_cast<Component*>(ani.get());
			if (cmp != NULL)
			{
				//to check cast failed
				//add by jiajing 
				Form* form = dynamic_cast<Form*>(cmp);
				if( form == NULL && (cmp->getParent().get() == NULL || cmp->getComponentForm().get() == NULL))
					continue;
				//end add
				shared_ptr<Rectangle> dirty = cmp->getDirtyRegion();
				if ( dirty.get() != NULL ) 
				{
					wrapper->setClip(dirty->getX(), dirty->getY(), dirty->getSize()->getWidth(), dirty->getSize()->getHeight());
					shared_ptr<Rectangle> nullRect;
					cmp->setDirtyRegion(nullRect);
				}
				//printf("paintComponent 1:%d\n",System::currentTimeMillis());
				cmp->paintComponent(wrapper);
				//printf("paintComponent2 :%d\n",System::currentTimeMillis());
				int cmpAbsX = cmp->getAbsoluteX() + cmp->getScrollX();
				topX = min(cmpAbsX, topX);
				bottomX = max(cmpAbsX + cmp->getWidth(), bottomX);
				int cmpAbsY = cmp->getAbsoluteY() + cmp->getScrollY();
				topY = min(cmpAbsY, topY);
				bottomY = max(cmpAbsY + cmp->getHeight(), bottomY);
			}
			else
			{
				bottomX = getDisplayWidth();
				bottomY = getDisplayHeight();
				topX = 0;
				topY = 0;
				ani->paint(wrapper);
			}
		}
		//paintQueueTemp->removeAllElements();
		paintOverlay(wrapper);
		
		flushGraphics(topX, topY, bottomX - topX, bottomY - topY);
	//	printf("paint end:%d\n",System::currentTimeMillis());
	}
}

void LWUITImplementation::edtIdle(bool enter)
{

}

shared_ptr<Graphics> LWUITImplementation::getLWUITGraphics()
{
	return lwuitGraphics;
}

void LWUITImplementation::setLWUITGraphics(shared_ptr<Graphics> g)
{
	lwuitGraphics = g;
}

void LWUITImplementation::setDisplayLock(shared_ptr<Locker> lock)
{
	displayLock = lock;
}

shared_ptr<Locker> LWUITImplementation::getDispalyLock()
{
	return displayLock;
}

void LWUITImplementation::repaint(shared_ptr<Animation> cmp)
{
	displayLock->lock();
	
	for (int iter = 0; iter < paintQueueFill; iter++)
	{
		shared_ptr<Animation> ani = (*paintQueue)[iter];
		if (ani == cmp) {
			displayLock->unlock();
			return;
		}
		//add by jiajing for painting speed

		shared_ptr<Component> temp1 = dynamic_pointer_cast<Component>(cmp); 
		shared_ptr<Component> temp2 = dynamic_pointer_cast<Component>(ani);
		if(temp1 != NULL &&  temp2 != NULL )
		{
			if( (static_pointer_cast<Component>(cmp))->getParent() == ani){
				displayLock->unlock();
				return;
			}
			if( (static_pointer_cast<Component>(ani))->getParent() == cmp)
			{
				(*paintQueue)[iter] = cmp;
				displayLock->unlock();
				return;
			}

		}
		//end
	}
	// overcrowding the queue don't try to grow the array!
	if (paintQueueFill >= MAX_COUNT)
	{
		//System.out.println("Warning paint queue size exceeded, please watch the amount of repaint calls");
		displayLock->unlock();
		return;
	}

	(*paintQueue)[paintQueueFill] = cmp;
	paintQueueFill++;

	displayLock->unlock();
}

bool LWUITImplementation::isAlphaMutableImageSupported()
{
	return false;
}

int LWUITImplementation::round(double d)
{
	return (d >= 0) ? (int)(d + 0.5) : (int)(d - 0.5);
}

shared_ptr<NativeImage> LWUITImplementation::rotate(shared_ptr<NativeImage> image, int degrees)
{
	int width = getImageWidth(image);
	int height = getImageHeight(image);
	shared_ptr<VectorArray<int> > arr = new VectorArray<int>(width * height);
	shared_ptr<VectorArray<int> > dest = new VectorArray<int>(width * height);
	getRGB(image, arr, 0, 0, 0, width, height);
	int centerX = width / 2;
	int centerY = height / 2;

	double radians = (degrees / -180) * 2 * PI;
	double cosDeg = cos(radians);
	double sinDeg = sin(radians);
	for (int x = 0; x < width; x++) 
	{
		for (int y = 0; y < height; y++) 
		{
			int x2 = round(cosDeg * (x - centerX) - sinDeg * (y - centerY) + centerX);
			int y2 = round(sinDeg * (x - centerX) + cosDeg * (y - centerY) + centerY);
			if (!(x2 < 0 || y2 < 0 || x2 >= width || y2 >= height)) 
			{
				int destOffset = x2 + y2 * width;
				if (destOffset >= 0 && destOffset < dest->size()) 
				{
					(*dest)[x + y * width] = (*arr)[destOffset];
				}
			}
		}
	}

	return createImage(dest, width, height);
}

void LWUITImplementation::setCurrentForm(shared_ptr<Form> f)
{
	currentForm = f;
}

void LWUITImplementation::confirmControlView()
{

}

shared_ptr<Form> LWUITImplementation::getCurrentForm()
{
	return currentForm;
}

bool LWUITImplementation::isTranslationSupported()
{
	return false;
}

void LWUITImplementation::translate(shared_ptr<NativeGraphics> graphics, int x, int y)
{

}

int LWUITImplementation::getTranslateX(shared_ptr<NativeGraphics> graphics)
{
	return 0;
}

int LWUITImplementation::getTranslateY(shared_ptr<NativeGraphics> graphics)
{
	return 0;
}

bool LWUITImplementation::isAlphaGlobal()
{
	return false;
}

bool LWUITImplementation::isAntiAliasingSupported()
{
	return false;
}

bool LWUITImplementation::isAntiAliasedTextSupported()
{
	return false;
}

void LWUITImplementation::setAntiAliased(shared_ptr<NativeGraphics> graphics, bool a)
{

}

bool LWUITImplementation::isAntiAliased(shared_ptr<NativeGraphics> graphics)
{
	return false;
}

void LWUITImplementation::setAntiAliasedText(shared_ptr<NativeGraphics> graphics, bool a)
{

}

bool LWUITImplementation::isAntiAliasedText(shared_ptr<NativeGraphics> graphics)
{
	return false;
}

shared_ptr<Rectangle> LWUITImplementation::getClipRect(shared_ptr<NativeGraphics> graphics)
{
	AMGraphics pGraphics = (AMGraphics)graphics.get();
	int x = (int)AMGetClipX(pGraphics);
	int y = (int)AMGetClipY(pGraphics);
	int width = (int)AMGetClipWidth(pGraphics);
	int height = (int)AMGetClipHeight(pGraphics);
	return new Rectangle(x, y, width, height);
}


void LWUITImplementation::setClipRect(shared_ptr<NativeGraphics> graphics, shared_ptr<Rectangle> rect)
{

}

void LWUITImplementation::clipRect(shared_ptr<NativeGraphics> graphics, shared_ptr<Rectangle> rect)
{

}

void LWUITImplementation::drawImageArea(shared_ptr<NativeGraphics> nativeGraphics, shared_ptr<NativeImage> img, int x, int y, int imageX, int imageY, int imageWidth, int imageHeight)
{
	int clipX = getClipX(nativeGraphics);
	int clipY = getClipY(nativeGraphics);
	int clipWidth = getClipWidth(nativeGraphics);
	int clipHeight = getClipHeight(nativeGraphics);
	clipRect(nativeGraphics, x, y, imageWidth, imageHeight);
	if(getClipWidth(nativeGraphics) > 0 && getClipHeight(nativeGraphics) > 0) 
	{
		drawImage(nativeGraphics, img, x - imageX, y - imageY);
	}
	setClip(nativeGraphics, clipX, clipY, clipWidth, clipHeight);
}

void LWUITImplementation::drawImageRotated(shared_ptr<NativeGraphics> graphics, shared_ptr<NativeImage> img, int x, int y, int degrees)
{
	// to do
}

bool LWUITImplementation::isRotationDrawingSupported()
{
	return false;
}

void LWUITImplementation::fillTriangle(shared_ptr<NativeGraphics> graphics, int x1, int y1, int x2, int y2, int x3, int y3)
{
	shared_ptr<VectorArray<int> > xPoint = new VectorArray<int>(3);
	shared_ptr<VectorArray<int> > yPoint = new VectorArray<int>(3);
	(*xPoint)[0] = x1;
	(*xPoint)[1] = x2;
	(*xPoint)[2] = x3;

	(*yPoint)[0] = y1;
	(*yPoint)[1] = y2;
	(*yPoint)[2] = y3;
	fillPolygon(graphics, xPoint, yPoint, 3);
}

int LWUITImplementation::getFace(shared_ptr<NativeFont> nativeFont)
{
	return 0;
}

int LWUITImplementation::getSize(shared_ptr<NativeFont> nativeFont)
{
	return 0;
}

int LWUITImplementation::getStyle(shared_ptr<NativeFont> nativeFont)
{
	return 0;
}

void LWUITImplementation::keyPressed(int keyCode)
{
	Display::getInstance()->keyPressed(keyCode);
}

void LWUITImplementation::keyReleased(int keyCode)
{
	Display::getInstance()->keyReleased(keyCode);
}

void LWUITImplementation::pointerDragged(int x, int y)
{
	(*xPointerEvent)[0] = x;
	(*yPointerEvent)[0] = y;
	pointerDragged(xPointerEvent, yPointerEvent);
}

void LWUITImplementation::pointerPressed(int x, int y)
{
	(*xPointerEvent)[0] = x;
	(*yPointerEvent)[0] = y;
	pointerPressed(xPointerEvent, yPointerEvent);
}
void LWUITImplementation::pointerReleased(int x, int y)
{
	(*xPointerEvent)[0] = x;
	(*yPointerEvent)[0] = y;
	pointerReleased(xPointerEvent, yPointerEvent);
}
void LWUITImplementation::pointerHover(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y)
{
	Display::getInstance()->pointerHover(x, y);
}

void LWUITImplementation::pointerHoverReleased(shared_ptr<VectorArray<int> >x, shared_ptr<VectorArray<int> > y)
{
	Display::getInstance()->pointerHoverReleased(x, y);
}

void LWUITImplementation::pointerHoverReleased(int x, int y)
{
	(*xPointerEvent)[0] = x;
	(*yPointerEvent)[0] = y;
	pointerHoverReleased(xPointerEvent, yPointerEvent);
}
void LWUITImplementation::pointerHover(int x, int y)
{
	(*xPointerEvent)[0] = x;
	(*yPointerEvent)[0] = y;
	pointerHover(xPointerEvent, yPointerEvent);
}
void LWUITImplementation::pointerDragged(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y)
{
	if (hasDragStarted(x, y))
	{
		Display::getInstance()->pointerDragged(x, y);
	}
}
bool LWUITImplementation::hasDragStarted(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y)
{
	return hasDragStarted((*x)[0], (*y)[0]);
}
bool LWUITImplementation::hasDragStarted(int x, int y)
{
	if (dragActivationCounter == 0) 
	{
		dragActivationX = x;
		dragActivationY = y;
		dragActivationCounter++;
		return false;
	}

	dragActivationCounter++;
	if (dragActivationCounter > getDragAutoActivationThreshold()) 
	{
		return true;
	}

	if (((float) getDisplayWidth()) / 100.0f * ((float) getDragStartPercentage()) <= abs(dragActivationX - x)) 
	{
			dragActivationCounter = getDragAutoActivationThreshold() + 1;
			return true;
	}


	if (((float) getDisplayHeight()) / 100.0f * ((float) getDragStartPercentage()) <= abs(dragActivationY - y)) 
	{
			dragActivationCounter = getDragAutoActivationThreshold() + 1;
			return true;
	}

	return false;
}
int LWUITImplementation::getDragStartPercentage()
{
	return dragStartPercentage;
}
void LWUITImplementation::setDragStartPercentage(int dragStartPercentage)
{
	this->dragStartPercentage = dragStartPercentage;
}
int LWUITImplementation::getDragAutoActivationThreshold()
{
	return 7;
}
void LWUITImplementation::pointerPressed(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y)
{
	pointerPressedX = (*x)[0];
	pointerPressedY = (*y)[0];
	Display::getInstance()->pointerPressed(x, y);
}
void LWUITImplementation::pointerReleased(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y)
{
	if(dragActivationCounter == 0 && (*x)[0] != pointerPressedX && (*y)[0] != pointerPressedY) 
	{
		hasDragStarted(pointerPressedX, pointerPressedY);
		if(hasDragStarted(x, y)) 
		{
			pointerDragged(pointerPressedX, pointerPressedY);
			pointerDragged(x, y);
		}
	}
	dragActivationCounter = 0;
	Display::getInstance()->pointerReleased(x, y);
}

void LWUITImplementation::sizeChanged(int w, int h)
{
	Display::getInstance()->sizeChanged(w, h);
}

void LWUITImplementation::hideNotify()
{
	Display::getInstance()->hideNotify();
}

void LWUITImplementation::showNotify()
{
	Display::getInstance()->showNotify();
}
shared_ptr<Object> LWUITImplementation::findCachedGradient(shared_ptr<Map<shared_ptr<VectorArray<int> >, shared_ptr<Object> > > cache, int startColor, int endColor, int x, int y, int width, int height, bool horizontal, int centerX, int centerY, int size) 
{
	if(cache.get() != NULL) 
	{
		Enumeration<shared_ptr<VectorArray<int> > > e = cache->keys();
		while(e.hasMoreElements()) 
		{
			shared_ptr<VectorArray<int> > current = e.nextElement();
			shared_ptr<Object> currentRef = cache->get(current);
			if(currentRef.get() == NULL) 
			{
				cache->remove(current);
				e = cache->keys();
				continue;
			}
			shared_ptr<Object> obj = currentRef;
			shared_ptr<NativeImage> img = dynamic_pointer_cast<NativeImage>(obj);
			if((*current)[0] == startColor && (*current)[1] == endColor && (*current)[2] == x &&
				(*current)[3] == y && (*current)[5] == centerX && (*current)[6] == centerY &&
				(*current)[7] == size && getImageWidth(img) == width && getImageHeight(img) == height) 
			{
				if((horizontal && (*current)[4] == 1) || ((!horizontal) && (*current)[4] == 0)) 
				{
					return currentRef;
				}
			}
		}
	}
	shared_ptr<Object> obj;
	return obj;
}
void LWUITImplementation::storeCachedGradient(shared_ptr<Object> img, shared_ptr<Map<shared_ptr<VectorArray<int> >, shared_ptr<Object> > > cache, int startColor, int endColor, int x, int y, bool horizontal, int centerX, int centerY, int size) 
{

	shared_ptr<VectorArray<int> > key = new VectorArray<int>(8);
	(*key)[0] = startColor;
	(*key)[1] = endColor;
	(*key)[2] = x;
	(*key)[3] = y;
 	if(horizontal) 
	{
		(*key)[4] = 1;
	}
	else 
	{
		(*key)[4] = 0;
	}
	(*key)[5] = centerX;
	(*key)[6] = centerY;
	(*key)[7] = size;
	//weak_ptr<Object> result = img;
	cache->put(key, img);
}

void LWUITImplementation::fillRectRadialGradient( shared_ptr<NativeGraphics> graphics, int startColor, int endColor, int x, int y, int width, int height, float relativeX, float relativeY, float relativeSize )
{

	int centerX = (int) (width * (1 - relativeX));
	int centerY = (int) (height * (1 - relativeY));
	int x2 = width / 2 - centerX;
	int y2 = height / 2 - centerY;

	int size = (int)(min(width, height) * relativeSize);

	if(cacheRadialGradients()) 
	{
		shared_ptr<Object> r = findCachedGradient(radialGradientCache, startColor, endColor, x, y, width, height, true, centerX, centerY, size);
		shared_ptr<NativeImage> nativeImage;
		if(r.get() != NULL) 
		{
			nativeImage = dynamic_pointer_cast<NativeImage>(r);
			drawImage(graphics, nativeImage, x, y);
		}
		else 
		{
			r = createMutableImage(width, height, 0xffffffff);
			nativeImage = dynamic_pointer_cast<NativeImage>(r);
			shared_ptr<NativeGraphics> imageGraphics = getNativeGraphics(nativeImage);
			setColor(imageGraphics, endColor);
			//setBgColor(imageGraphics, endColor);
			fillRect(imageGraphics, 0, 0, width, height);
			fillRadialGradientImpl(imageGraphics, startColor, endColor, x2, y2, size, size);
			drawImage(graphics, nativeImage, x, y);
			if(radialGradientCache.get() == NULL) 
			{
				radialGradientCache = new Map<shared_ptr<VectorArray<int> >, shared_ptr<Object> >();
			}
			storeCachedGradient(r, radialGradientCache, startColor, endColor, x, y, true, centerX, centerY, size);
		}
	}
	else 
	{
		setColor(graphics, endColor);
		//setBgColor(graphics, endColor);
		fillRect(graphics, x, y, width, height);

		fillRadialGradientImpl(graphics, startColor, endColor, x + x2, y + y2, size, size);
	}

}
void LWUITImplementation::fillRadialGradient(shared_ptr<NativeGraphics> graphics, int startColor, int endColor, int x, int y, int width, int height)
{
	fillRadialGradientImpl(graphics, startColor, endColor, x, y, width, height);
}
void LWUITImplementation::fillRadialGradientImpl(shared_ptr<NativeGraphics> graphics, int startColor, int endColor, int x, int y, int width, int height)
{
	int sourceR = startColor >> 16 & 0xff;
	int sourceG = startColor >> 8 & 0xff;
	int sourceB = startColor & 0xff;
	int destR = endColor >> 16 & 0xff;
	int destG = endColor >> 8 & 0xff;
	int destB = endColor & 0xff;
	int oldColor = getColor(graphics);
	//int oldColor = getFgColor(graphics);
	int originalHeight = height;
	while (width > 0 && height > 0) 
	{
		updateGradientColor(graphics, sourceR, sourceG, sourceB, destR, destG, destB, originalHeight, height);
		fillArc(graphics, x, y, width, height, 0, 360);
		x++;
		y++;
		width -= 2;
		height -= 2;
	}
	setColor(graphics, oldColor);
	//setFgColor(graphics, oldColor);
}


void LWUITImplementation::updateGradientColor(shared_ptr<NativeGraphics> nativeGraphics, int sourceR, int sourceG, int sourceB, int destR, int destG, int destB, int distance, int offset)
{
	int r = calculateGraidentChannel(sourceR, destR, distance, offset);
	int g = calculateGraidentChannel(sourceG, destG, distance, offset);
	int b = calculateGraidentChannel(sourceB, destB, distance, offset);
	int color = /*((a << 24) & 0xff000000) |*/ ((r << 16) & 0xff0000) |	((g << 8) & 0xff00) | (b & 0xff);
	setColor(nativeGraphics, color);
	//setFgColor(nativeGraphics, color);
}

int LWUITImplementation::calculateGraidentChannel(int sourceChannel, int destChannel, int distance, int offset)
{
	if (sourceChannel == destChannel) 
	{
		return sourceChannel;
	}

	float ratio = ((float) offset) / ((float) distance);
	int pos = (int) (abs(sourceChannel - destChannel) * ratio);
	if (sourceChannel > destChannel) 
	{
		return sourceChannel - pos;
	} else 
	{
		return sourceChannel + pos;
	}
}

void LWUITImplementation::fillLinearGradient(shared_ptr<NativeGraphics> graphics, int startColor, int endColor, int x, int y, int width, int height, bool horizontal)
{
	if(cacheLinearGradients()) 
	{
		shared_ptr<Object> r = findCachedGradient(linearGradientCache, startColor, endColor, x, y, width, height, horizontal, 0, 0, 0);
		shared_ptr<NativeImage> nativeImage = dynamic_pointer_cast<NativeImage>(r);
		if(nativeImage.get() != NULL) 
		{
			drawImage(graphics, nativeImage, x, y);
		}
		else 
		{
			nativeImage = createMutableImage(width, height, 0xffffffff);
			fillLinearGradientImpl(getNativeGraphics(nativeImage), startColor, endColor, 0, 0, width, height, horizontal);
			drawImage(graphics, nativeImage, x, y);
			if(linearGradientCache.get() == NULL) 
			{
				linearGradientCache = new Map<shared_ptr<VectorArray<int> >, shared_ptr<Object> >();
			}
			storeCachedGradient(nativeImage, linearGradientCache, startColor, endColor, x, y, horizontal, 0, 0, 0);
		}
	}
	else 
	{
		fillLinearGradientImpl(graphics, startColor, endColor, x, y, width, height, horizontal);
	}
}

void LWUITImplementation::fillLinearGradientImpl(shared_ptr<NativeGraphics> graphics, int startColor, int endColor, int x, int y, int width, int height, bool horizontal)
{
	int sourceR = startColor >> 16 & 0xff;
	int sourceG = startColor >> 8 & 0xff;
	int sourceB = startColor & 0xff;
	int destR = endColor >> 16 & 0xff;
	int destG = endColor >> 8 & 0xff;
	int destB = endColor & 0xff;
	int oldColor = getColor(graphics);
	//int oldColor = getFgColor(graphics);
	if (horizontal) 
	{
		for (int iter = 0; iter < width; iter++) 
		{
			updateGradientColor(graphics, sourceR, sourceG, sourceB, destR, destG, destB, width, iter);
			drawLine(graphics, x + iter, y, x + iter, y + height);
		}
	} 
	else
	{
		for (int iter = 0; iter < height; iter++) 
		{
			updateGradientColor(graphics, sourceR, sourceG, sourceB, destR, destG, destB, height, iter);
			drawLine(graphics, x, y + iter, x + width, y + iter);
		}
	}
	setColor(graphics, oldColor);
	//setFgColor(graphics, oldColor);
}

bool LWUITImplementation::checkIntersection(shared_ptr<NativeGraphics> g, int y0, int x1, int x2, int y1, int y2, shared_ptr<VectorArray<int> > intersections, int intersectionsCount)
{
	if (y0 > y1 && y0 < y2 || y0 > y2 && y0 < y1) 
	{
		if (y1 == y2) 
		{
			drawLine(g, x1, y0, x2, y0);
			return false;
		}
		(*intersections)[intersectionsCount] = x1 + ((y0 - y1) * (x2 - x1)) / (y2 - y1);
		return true;
	}
	return false;
}

int LWUITImplementation::markIntersectionEdge(shared_ptr<NativeGraphics> g, int idx, shared_ptr<VectorArray<int> >yPoints, shared_ptr<VectorArray<int> >xPoints, int nPoints, shared_ptr<VectorArray<int> >intersections, int intersectionsCount)
{
	(*intersections)[intersectionsCount] = (*xPoints)[idx];

	if (((*yPoints)[idx] - (*yPoints)[(idx + 1) % nPoints]) * ((*yPoints)[idx] - (*yPoints)[(idx + nPoints - 1) % nPoints]) > 0) 
	{
		(*intersections)[intersectionsCount + 1] = (*xPoints)[idx];
		return 2;
	}

	//Check for special case horizontal line
	if ((*yPoints)[idx] == (*yPoints)[(idx + 1) % nPoints]) 
	{

		drawLine(g, (*xPoints)[idx], (*yPoints)[idx], (*xPoints)[(idx + 1) % nPoints], (*yPoints)[(idx + 1) % nPoints]);

		if (((*yPoints)[(idx + 1) % nPoints] - (*yPoints)[(idx + 2) % nPoints]) * ((*yPoints)[idx] - (*yPoints)[(idx + nPoints - 1) % nPoints]) > 0) 
		{
			return 1;
		}
		else
		{
			(*intersections)[intersectionsCount + 1] = (*xPoints)[idx];
			return 2;
		}

	}
	return 1;
}

void LWUITImplementation::fillPolygon(shared_ptr<NativeGraphics> graphics, shared_ptr<VectorArray<int> > xPoints, shared_ptr<VectorArray<int> > yPoints, int nPoints)
{
	shared_ptr<VectorArray<int> > intersectionsSp = new VectorArray<int>(nPoints);
	int intersectionsCount = 0;


	int yMax = (*yPoints)[0];
	int yMin = (*yPoints)[0];

	for (int i = 0; i < nPoints; i++) 
	{
		yMax = max(yMax, (*yPoints)[0]);
		yMin = min(yMin, (*yPoints)[0]);
	}

	//  Loop through the rows of the image.
	for (int row = yMin; row <= yMax; row++) 
	{

		intersectionsCount = 0;
		
		//shared_ptr<Vector<int> > intersectionsSp = &intersections;
		for (int i = 1; i < nPoints; i++) 
		{
			if (checkIntersection(graphics, row, (*xPoints)[i - 1], (*xPoints)[i], (*yPoints)[i - 1], (*yPoints)[i], intersectionsSp, intersectionsCount)) 
			{
				intersectionsCount++;
			}
		}
		if (checkIntersection(graphics, row, (*xPoints)[nPoints - 1], (*xPoints)[0], (*yPoints)[nPoints - 1], (*yPoints)[0], intersectionsSp, intersectionsCount)) 
		{
			intersectionsCount++;
		}

		for (int j = 0; j < nPoints; j++) 
		{
			if (row == (*yPoints)[j]) 
			{
				intersectionsCount += markIntersectionEdge(graphics, j, yPoints, xPoints, nPoints, intersectionsSp, intersectionsCount);
			}
		}

		int swap = 0;
		for (int i = 0; i < intersectionsCount; i++) 
		{
			for (int j = i; j < intersectionsCount; j++) 
			{
				if ((*intersectionsSp)[j] < (*intersectionsSp)[i]) 
				{
					swap = (*intersectionsSp)[i];
					(*intersectionsSp)[i] = (*intersectionsSp)[j];
					(*intersectionsSp)[j] = swap;
				}
			}
		}


		for (int i = 1; i < intersectionsCount; i = i + 2) 
		{
			drawLine(graphics, (*intersectionsSp)[i - 1], row, (*intersectionsSp)[i], row);
		}
	}
}

void LWUITImplementation::drawPolygon(shared_ptr<NativeGraphics> graphics, shared_ptr<VectorArray<int> > xPoints, shared_ptr<VectorArray<int> > yPoints, int nPoints)
{
	for (int i = 1; i < nPoints; i++) 
	{
		drawLine(graphics, (*xPoints)[i - 1], (*yPoints)[i - 1], (*xPoints)[i], (*yPoints)[i]);
	}
	drawLine(graphics, (*xPoints)[nPoints - 1], (*yPoints)[nPoints - 1], (*xPoints)[0], (*yPoints)[0]);
}

void LWUITImplementation::setShowVirtualKeyboard(bool show)
{

}

bool LWUITImplementation::isVirtualKeyboardShowing()
{
	return false;
}

bool LWUITImplementation::isVirtualKeyboardShowingSupported()
{
	return false;
}

int LWUITImplementation::getKeyboardType()
{
	return Display::KEYBOARD_TYPE_UNKNOWN;
}

bool LWUITImplementation::isNativeInputSupported()
{
	return false;
}

bool LWUITImplementation::isMultiTouch()
{
	return false;
}

bool LWUITImplementation::isClickTouchScreen()
{
	return false;
}

bool LWUITImplementation::isNativeIndexed()
{
	return false;
}

shared_ptr<NativeImage> LWUITImplementation::createNativeIndexed(shared_ptr<IndexedImage> image)
{
	shared_ptr<NativeImage> res;
	return res;
}

shared_ptr<Object> LWUITImplementation::createVideoComponent(shared_ptr<Object> player)
{
	shared_ptr<Object> res;
	return res;
}

int LWUITImplementation::getVideoWidth(shared_ptr<Object> videoControl)
{
	return 0;
}

int LWUITImplementation::getVideoHeight(shared_ptr<Object> videoControl)
{
	return 0;
}

void LWUITImplementation::setVideoVisible(shared_ptr<Object> vc, bool visible)
{

}

void LWUITImplementation::startVideo(shared_ptr<Object> player, shared_ptr<Object> videoControl)
{

}

void LWUITImplementation::stopVideo(shared_ptr<Object> player, shared_ptr<Object> videoControl)
{

}

void LWUITImplementation::setVideoLoopCount(shared_ptr<Object> player, int count)
{
}

long LWUITImplementation::getMediaTime(shared_ptr<Object> player)
{
	return 0;
}

long LWUITImplementation::setMediaTime(shared_ptr<Object> player, long now)
{
	return 0;
}

void LWUITImplementation::setVideoFullScreen(shared_ptr<Object> player, bool fullscreen)
{

}

void LWUITImplementation::paintVideo(shared_ptr<Component> cmp, bool fullScreen, shared_ptr<NativeGraphics> nativeGraphics, shared_ptr<Object> video, shared_ptr<Object> player)
{

}

bool LWUITImplementation::isOpaque(shared_ptr<Image> lwuitImage, shared_ptr<NativeImage> nativeImage)
{
	shared_ptr<VectorArray<int> >rgb = lwuitImage->getRGBCached();
	int iter;
	for (iter = 0; iter < rgb->size(); iter++) 
	{
		if (((*rgb)[iter] & 0xff000000) != 0xff000000) {
			return false;
		}
	}
	return true;
}

bool LWUITImplementation::isAffineSupported()
{
	return false;
}

void LWUITImplementation::resetAffine(shared_ptr<NativeGraphics> nativeGraphics)
{
	//System.out.println("Affine unsupported");
}

void LWUITImplementation::scale(shared_ptr<NativeGraphics> nativeGraphics, float x, float y)
{
	//System.out.println("Affine unsupported");
}

void LWUITImplementation::rotate(shared_ptr<NativeGraphics> nativeGraphics, float angle)
{
	//System.out.println("Affine unsupported");
}

void LWUITImplementation::shear(shared_ptr<NativeGraphics> nativeGraphics, float x, float y)
{
	//System.out.println("Affine unsupported");
}

bool LWUITImplementation::isSVGSupported()
{
	return false;
}

shared_ptr<NativeImage> LWUITImplementation::createSVGImage(shared_ptr<String> baseURL, VectorArray<unsigned char>  data)
{
	//exception
	//throw new IOException("SVG is not supported by this implementation");
	shared_ptr<NativeImage> res;
	return res;
}

shared_ptr<Object> LWUITImplementation::getSVGDocument(shared_ptr<NativeImage> svgImage)
{
	//exception
	//throw new RuntimeException("SVG is not supported by this implementation")
	shared_ptr<Object> res;
	return res;
}

bool LWUITImplementation::animateImage(shared_ptr<NativeImage> nativeImage, long lastFrame)
{
	return false;
}

shared_ptr<VectorArray<String> > LWUITImplementation::getFontPlatformNames()
{
	shared_ptr<VectorArray<String> > platformName = new VectorArray<String>(2);
	(*platformName)[0] = L"MIDP";
	(*platformName)[1] = L"MIDP2";
	return platformName;
}

shared_ptr<NativeFont> LWUITImplementation::loadTrueTypeFont(shared_ptr<InputStream> stream)
{
	//exception
	//throw new IOException("Unsupported operation")
	shared_ptr<NativeFont> res;
	return res;
}

bool LWUITImplementation::isTrueTypeSupported()
{
	return false;
}

shared_ptr<NativeFont> LWUITImplementation::loadNativeFont(shared_ptr<String> lookup)
{
	shared_ptr<NativeFont> res;
	return res;
}

bool LWUITImplementation::isLookupFontSupported()
{
	return false;
}

bool LWUITImplementation::minimizeApplication()
{
	return false;
}

void LWUITImplementation::restoreMinimizedApplication()
{

}

bool LWUITImplementation::isMinimized()
{
	return false;
}

bool LWUITImplementation::cacheRadialGradients() 
{
	return true;
}

bool LWUITImplementation::cacheLinearGradients()
{
	return true;
}

bool LWUITImplementation::isThirdSoftButton()
{
	return getSoftkeyCount() < 2 && isTouchDevice();
}
int LWUITImplementation::getDragPathLength()
{
	return 10;
}
int LWUITImplementation::getDragPathTime()
{
	return 200;
}
float LWUITImplementation::getDragSpeed(shared_ptr<VectorArray<float> >points, shared_ptr<VectorArray<long> > dragPathTime,	int dragPathOffset, int dragPathLength)
{
	long now = System::currentTimeMillis();
	const long tooold = now - getDragPathTime();
	int offset = dragPathOffset - dragPathLength;
	if (offset < 0) 
	{
		offset = getDragPathLength() + offset;
	}
	long old = 0;
	float oldPoint = 0;
	float speed = 0;
	long timediff;
	float diff;
	float velocity;
	float f = (float)dragPathLength;
	while (dragPathLength > 0) 
	{
		if ((*dragPathTime)[offset] > tooold) 
		{
			if (old == 0) 
			{
				old = (*dragPathTime)[offset];
				oldPoint = (*points)[offset];
			}
			timediff = now - old;
			diff = (*points)[offset] - oldPoint;
			if (timediff > 0) 
			{
				velocity = (diff / timediff) * 1.5f;
				speed += velocity;
			}
		}
		dragPathLength--;
		offset++;
		if (offset >= getDragPathLength()) 
		{
			offset = 0;
		}
	}
	f = max(1.0f, f);
	return -speed / f;
}
bool LWUITImplementation::isBidiAlgorithm()
{
	return bidi;
}
void LWUITImplementation::setBidiAlgorithm(bool activate)
{
	bidi = activate;
}
shared_ptr<String> LWUITImplementation::convertBidiLogicalToVisual(shared_ptr<String> s)
{
	if(bidi) 
	{
		if (s->length() >= 2) 
		{
			swapBidiChars(s, 0, s->size(), -1);
			return new String(*s);
		}
	}
	return s;
}
int LWUITImplementation::getCharLocation(shared_ptr<String> source, int index)
{
	if(bidi) 
	{
		return swapBidiChars(source, 0, source->size(), index);
	}
	return index;
}
bool LWUITImplementation::isRTLOrWhitespace(GUI_CHAR c)
{
	if(bidi)
	{
		return isRTL(c) || c == L' ';
	}
	return false;
}
bool LWUITImplementation::isRTL(GUI_CHAR c)
{
	return (c >= RTL_RANGE_BEGIN && c <= RTL_RANGE_END);
}
int LWUITImplementation::swapBidiChars(shared_ptr<String> chars, int ixStart, int len,int index)
{
	int destIndex = -1;

	int ixEnd = ixStart + len;
	int ix0, ix1;

	ix0 = ix1 = ixStart;

	bool doSwap = false;
	for ( int i1 = ixStart; i1 < ixEnd; i1++ )
	{
		if ( isRTL((*chars)[i1]) ) 
		{
			doSwap = true;
			break;
		}
	}

	if ( doSwap ) 
	{
		while ( ix0 < ixEnd )
		{
			if ( (ix1 = scanSecond(chars, ix0, ixEnd)) < 0 ) 
			{
				break;
			}
			else
			{
				ix0 = ix1;
				ix1 = scanBackFirst(chars, ix0, ixEnd);
				// swap
				for ( int iy0 = ix0, iy1 = ix1-1; iy0 < iy1; iy0++, iy1--) 
				{
					GUI_CHAR* charsPt = chars->toCharArray();
					GUI_CHAR tmp = charsPt[iy0];
					charsPt[iy0] = charsPt[iy1];
					charsPt[iy1] = tmp;

					if (index==iy1)
					{
						//System.out.println("IY: Found char: new index="+iy0);
						destIndex=iy0;
						index=iy0;
					}
				}
				ix0 = ix1;
			}
		}
	}

	if ( doSwap ) 
	{
		// swap the line
		for (ix0 = ixStart, ix1 = ixEnd - 1 ; ix0 <= ix1 ; ix0++, ix1--) 
		{
			GUI_CHAR* charsPt = chars->toCharArray();
			GUI_CHAR ch0 = charsPt[ix0];
			GUI_CHAR ch1 = charsPt[ix1];

			charsPt[ix0] = ch1;
			charsPt[ix1] = ch0;

			if (index==ix0) 
			{
				destIndex=ix1;
			}
			else
			{
				if (index==ix1) 
				{
					destIndex=ix0;
				}
			}
		}
	}

	return destIndex;
}
bool LWUITImplementation::isRTLBreak(GUI_CHAR ch1)
{
	return ch1 == ')' || ch1 == ']' || ch1 == '}' || ch1 == '(' || ch1 == '[' || ch1 == '{' ;
}
bool LWUITImplementation::isLTR(GUI_CHAR c)
{
	return !isRTL(c) && !isRTLBreak(c);
}

int LWUITImplementation::scanSecond(shared_ptr<String> chars, int ixStart, int ixEnd)
{
	int ixFound = -1;
	for ( int ix = ixStart; ixFound < 0 && ix < ixEnd; ix++ ) 
	{
		if (!isRTL((*chars)[ix])) 
		{
			ixFound = ix;
		} 
	}
	return ixFound;
}

int LWUITImplementation::scanBackFirst(shared_ptr<String> chars, int ixStart, int ixEnd)
{
	int ix, ixFound = ixEnd;
	for ( ix = ixStart+1; ix < ixEnd; ix++ ) 
	{
		if ( isRTLBreak((*chars)[ix])) 
		{
			ixFound = ix;
			break;
		}
	}

	for (ix = ixFound-1; ix >= ixStart; ix-- ) 
	{
		if ( isLTR((*chars)[ix]) ) 
		{
			ixFound = ix + 1;
			break;
		}
	}

	return ixFound;
}
void LWUITImplementation::deinitialize()
{
	displayLock.reset();
}
__GUI_END_NAMESPACE

