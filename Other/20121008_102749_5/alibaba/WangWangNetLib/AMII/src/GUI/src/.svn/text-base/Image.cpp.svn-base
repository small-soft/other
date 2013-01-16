#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
Image::Image(void)
{
	init();
}

Image::Image( shared_ptr<NativeImage> image )
{
	init();
	this->image = image;
}

Image::Image( shared_ptr<VectorArray<int> > imageArray, int w, int h )
{
	init();
	this->image = Display::getInstance()->getImplementation()->createImage(imageArray, w, h);
}
Image::~Image(void)
{
}
void Image::init()
{
	transform = 0;
	opaqueTested = false;
	opaque = false;
	animated = false;
	imageTime = -1;
	svg = false;
}
shared_ptr<Image::image_map> Image::getScaleCache()
{
	if(scaleCache.get() == NULL)
	{
		scaleCache = new image_map();
	}
	return scaleCache;
}
shared_ptr<Image> Image::getCachedImage(const Dimension size )
{
	shared_ptr<Image> img;
	if(scaleCache.get() != NULL)
	{
		img = getScaleCache()->get(size);
	}
	return img;
}
void Image::cacheImage( Dimension size, shared_ptr<Image> i )
{
	shared_ptr<image_map> map = getScaleCache();
	map->put(size,i);
}

void Image::setImage(shared_ptr<NativeImage> image)
{
	this->image = image;
}

void Image::setOpaque(bool opaque)
{
	this->opaque = opaque;
	opaqueTested = true;
}

bool Image::isSVGSupported()
{
	return Display::getInstance()->getImplementation()->isSVGSupported();
}

shared_ptr<Object> Image::getSVGDocument()
{
	return Display::getInstance()->getImplementation()->getSVGDocument(image);
}

shared_ptr<Image> Image::createSVG(shared_ptr<String> baseURL, bool animated, VectorArray<unsigned char> data)
{
	shared_ptr<Image> i = new Image(Display::getInstance()->getImplementation()->createSVGImage(baseURL, data));
	i->animated = animated;
	i->svg = true;
	return i;
}

bool Image::isSVG()
{
	return svg;
}

shared_ptr<Object> Image::createMask()
{
	shared_ptr<VectorArray<int> >rgb = getRGBCached();
	shared_ptr<VectorArray<unsigned char> >mask = new VectorArray<unsigned char>(rgb->size());

	for(int iter = 0; iter < rgb->size(); iter++)
	{
		(*mask)[iter] = (unsigned char)((*rgb)[iter] & 0xff);
	}
	shared_ptr<VectorArray<int> > nullVector = new VectorArray<int>(0);
	return new IndexedImage(getWidth(), getHeight(), nullVector, mask);
}

shared_ptr<Image> Image::applyMask(shared_ptr<Object> mask)
{
	shared_ptr<Image> image;
	shared_ptr<VectorArray<int> > rgb = getRGB();
	shared_ptr<VectorArray<unsigned char> >maskData = ((IndexedImage*)(mask.get()))->getImageDataByte();
	int mWidth = ((IndexedImage*)(mask.get()))->getWidth();
	int mHeight = ((IndexedImage*)(mask.get()))->getHeight();

	if(mWidth != getWidth() || mHeight != getHeight())
	{
		return image;
	}

	for(int iter = 0; iter < maskData->size(); iter++)
	{
		int maskAlpha = (*maskData)[iter] & 0xff;
		maskAlpha = (maskAlpha << 24) & 0xff000000;
		(*rgb)[iter] = (*rgb)[iter] & 0xffffff | maskAlpha;
	}
	return createImageFromRGBWithRect(rgb, mWidth, mHeight);
}

shared_ptr<Image> Image::applyMask(shared_ptr<Object> mask, int x, int y)
{
	shared_ptr<VectorArray<int> > rgb = getRGB();
	shared_ptr<VectorArray<unsigned char> > maskData = ((IndexedImage*)(mask.get()))->getImageDataByte();
	int mWidth = ((IndexedImage*)(mask.get()))->getWidth();
	int mHeight = ((IndexedImage*)(mask.get()))->getHeight();
	int imgWidth = getWidth();
	int aWidth = imgWidth - x;
	int aHeight = getHeight() - y;
	if(aWidth> mWidth)
	{
		aWidth = mWidth;
	}
	if(aHeight> mHeight)
	{
		aHeight = mHeight;
	}

	for(int xPos = 0; xPos < aWidth; xPos++)
	{
		for(int yPos = 0; yPos < aHeight; yPos++)
		{
			int aX = x + xPos;
			int aY = y + yPos;
			int imagePos = aX + aY * imgWidth;
			int maskAlpha = maskData->elementAt(aX + aY * mWidth) & 0xff;
			maskAlpha = (maskAlpha << 24) & 0xff000000;
			rgb->elementAt(imagePos) = (rgb->elementAt(imagePos) & 0xffffff) | maskAlpha;

		}
	}
	return createImageFromRGBWithRect(rgb, imgWidth, getHeight());
}

shared_ptr<Image> Image::subImage(int x, int y, int width, int height, bool processAlpha)
{
	shared_ptr<VectorArray<int> > arr = new VectorArray<int>(width * height);
	//	arr->reserve(width * height);
	getRGB(arr, 0, x, y, width, height);

	shared_ptr<Image> i = new Image(Display::getInstance()->getImplementation()->createImage(arr, width, height));
	i->opaque = opaque;
	i->opaqueTested = opaqueTested;
	return i;
}

shared_ptr<Image> Image::rotate(int degrees)
{
	shared_ptr<LWUITImplementation> i = Display::getInstance()->getImplementation();
	if(i->isRotationDrawingSupported())
	{
		if(degrees >= 90)
		{
			int newTransform = 0;
			if(transform != 0)
			{
				newTransform = (transform + degrees) % 360;
			}
			else
			{
				newTransform = degrees % 360;
			}

			degrees %= 90;
			newTransform -= degrees;

			if(degrees != 0)
			{
				shared_ptr<Image> newImage = new Image(Display::getInstance()->getImplementation()->rotate(image, degrees));
				newImage->transform = newTransform;
				return newImage;
			}
			else
			{
				shared_ptr<Image> newImage = new Image(image);
				newImage->transform = newTransform;
				return newImage;
			}
		}
		if(degrees != 0)
		{
			return new Image(Display::getInstance()->getImplementation()->rotate(image, degrees));
		}
		return this->shared_from_this();
	}
	else
	{
		return new Image(Display::getInstance()->getImplementation()->rotate(image, degrees));
	}
}

shared_ptr<Image> Image::createIndexed(int width, int height, shared_ptr<VectorArray<int> >palette, shared_ptr<VectorArray<unsigned char> > data)
{
	shared_ptr<IndexedImage> i = new IndexedImage(width, height, palette, data);
	shared_ptr<LWUITImplementation> impl = Display::getInstance()->getImplementation();
	if(impl->isNativeIndexed())
	{
		return new Image(impl->createNativeIndexed(i));
	}
	return i;
}

shared_ptr<Image> Image::modifyAlpha(unsigned char alpha)
{
	int w = getWidth();
	int h = getHeight();
	int size = w * h;
	shared_ptr<VectorArray<int> > arr = getRGB();
	int alphaInt = (((int)alpha) << 24) & 0xff000000;
	for(int iter = 0; iter < size; iter++)
	{
		int currentAlpha = (arr->elementAt(iter) >> 24) & 0xff;
		if(currentAlpha != 0)
		{
			arr->elementAt(iter) = (arr->elementAt(iter) & 0xffffff) | alphaInt;
		}
	}
	shared_ptr<Image> i = new Image(arr, w, h);
	i->opaqueTested = true;
	i->opaque = false;
	return i;
}

shared_ptr<Image> Image::modifyAlphaWithTranslucency(unsigned char alpha)
{
	int w = getWidth();
	int h = getHeight();
	int size = w * h;
	shared_ptr<VectorArray<int> > arr = getRGB();
	int alphaInt = (((int)alpha) << 24) & 0xff000000;
	float alphaRatio = (float)(alpha & 0xff);
	alphaRatio = alpha / 255.0f;
	for(int iter = 0; iter < size; iter++)
	{
		int currentAlpha = (arr->elementAt(iter) >> 24) & 0xff;
		if(currentAlpha != 0)
		{
			if(currentAlpha == 0xff)
			{
				arr->elementAt(iter) = (arr->elementAt(iter) & 0xffffff) | alphaInt;
			}
			else
			{
				int relative = (int)((((float)(currentAlpha)) / 255.0f * alphaRatio) * 255.0f);
				relative = (relative << 24) & 0xff000000;
				arr->elementAt(iter) = (arr->elementAt(iter) & 0xffffff) | relative;
			}
		}
	}
	shared_ptr<Image> i = new Image(arr, w, h);
	i->opaqueTested = true;
	i->opaque = false;
	return i;
}

shared_ptr<Image> Image::modifyAlpha(unsigned char alpha, int removeColor)
{
	removeColor = removeColor & 0xffffff;
	int w = getWidth();
	int h = getHeight();
	int size = w * h;
	VectorArray<int> *arr = new VectorArray<int>(size);

	//	arr->reserve(size);
	getRGB(arr, 0, 0, 0, w, h);
	int alphaInt = (((int)alpha) << 24) & 0xff000000;
	for(int iter = 0; iter < size; iter++)
	{
		if((arr->elementAt(iter) & 0xff000000) != 0)
		{
			arr->elementAt(iter) = (arr->elementAt(iter) & 0xffffff) | alphaInt;
			if(removeColor == (0xffffff & arr->elementAt(iter)))
			{
				arr->elementAt(iter) = 0;
			}
		}
	}
	shared_ptr<Image> i = new Image(arr, w, h);
	i->opaqueTested = true;
	i->opaque = false;
	return i;
}

shared_ptr<Image> Image::createImage(shared_ptr<String> path)
{
	return new Image(Display::getInstance()->getImplementation()->createImage(path));
}

shared_ptr<Image> Image::createImageFromStream(shared_ptr<InputStream> stream)
{
	return new Image(Display::getInstance()->getImplementation()->createImage(stream));
}

shared_ptr<Image> Image::createImageFromRGBWithRect(shared_ptr<VectorArray<int> > rgb, int width, int height)
{
	shared_ptr<Image> i = new Image(Display::getInstance()->getImplementation()->createImage(rgb, width, height));
	return i;
}

shared_ptr<Image> Image::createImage(int width, int height)
{
	return createImage(width, height, 0xffffffff);
}

bool Image::isAlphaMutableImageSupported()
{
	return Display::getInstance()->getImplementation()->isAlphaMutableImageSupported();
}

shared_ptr<Image> Image::createImage(int width, int height, int fillColor)
{
	return new Image(Display::getInstance()->getImplementation()->createMutableImage(width, height, fillColor));
}

shared_ptr<Image> Image::createImage(VectorArray<unsigned char> bytes,int offset,int len)
{
	return new Image(Display::getInstance()->getImplementation()->createImage(bytes, offset, len));
}

shared_ptr<Graphics> Image::getGraphics()
{
	if(graphic.get() == NULL){
	 graphic = new Graphics(Display::getInstance()->getImplementation()->getNativeGraphics(image));
	}
		
	return graphic;
}

int Image::getWidth()
{
	if(image.get() == NULL)
		return 0;
	return Display::getInstance()->getImplementation()->getImageWidth(image);
}

int Image::getHeight()
{
	if(image.get() == NULL)
		return 0;
	return Display::getInstance()->getImplementation()->getImageHeight(image);
}

void Image::drawImageArea(shared_ptr<Graphics> g, shared_ptr<NativeGraphics> nativeGraphics, int x, int y, int imageX, int imageY, int imageWidth, int imageHeight)
{
	Display::getInstance()->getImplementation()->drawImageArea(nativeGraphics, image, x, y, imageX, imageY, imageWidth, imageHeight);
}

void Image::getRGB(shared_ptr<VectorArray<int> >rgbData, int offset, int x, int y, int width, int height)
{
	Display::getInstance()->getImplementation()->getRGB(image, rgbData, offset, x, y, width, height);
}
void Image::toRGB( shared_ptr<RGBImage> image, int destX, int destY, int x, int y, int width, int height )
{
	getRGB(image->getRGB(), destX * destY, x, y, width, height);
}
shared_ptr<VectorArray<int> > Image::getRGB()
{
	return getRGBImpl();
}

shared_ptr<VectorArray<int> > Image::getRGBCached()
{
	shared_ptr<VectorArray<int> > r = getRGBCache();
	if(r.get() == NULL)
	{
		r = getRGBImpl();
		rgbCache = r;
	}
	return r;
}

shared_ptr<VectorArray<int> > Image::getRGBCache()
{
	return rgbCache;
}

shared_ptr<VectorArray<int> > Image::getRGBImpl()
{
	int width = getWidth();
	int height = getHeight();

	shared_ptr<VectorArray<int> > rgbData = new VectorArray<int>(width * height);

	getRGB(rgbData, 0, 0, 0, width, height);
	return rgbData;
}

shared_ptr<Image> Image::scaledWidth(int width)
{
	float ratio = ((float)width) / ((float)getWidth());
	return scaled(width, (int)(getHeight() * ratio));
}

shared_ptr<Image> Image::scaledHeight(int height)
{
	float ratio = ((float)height) / ((float)getHeight());
	return scaled((int)(getWidth() * ratio), height);
}

shared_ptr<Image> Image::scaledSmallerRatio(int width, int height)
{
	float hRatio = ((float)height) / ((float)getHeight());
	float wRatio = ((float)width) / ((float)getWidth());
	if(hRatio < wRatio)
	{
		return scaled(width, (int)(getHeight() * hRatio));
	}
	else
	{
		return scaled((int)(getWidth() * wRatio), height);
	}
}

shared_ptr<Image> Image::scaled(int width, int height)
{
	if(width == getWidth() && height == getHeight())
	{
		return this->shared_from_this();
	}
	if(width == -1)
	{
		return scaledHeight(height);
	}
	if(height == -1)
	{
		return scaledWidth(width);
	}

	Dimension d(width, height);
	shared_ptr<Image> i = getCachedImage(d);
	if(i.get() != NULL)
	{
		return i;
	}
	d.setWidth(getWidth());
	d.setHeight(getHeight());
	
	cacheImage(d, this->shared_from_this());

	i = new Image(this->image);
	i->scaleCache = scaleCache;
	i->scale(width, height);
	i->transform = this->transform;
	i->animated = animated;
	i->svg = svg;

	return i;
}

shared_ptr<NativeImage> Image::getImage()
{
	return image;
}

void Image::scale(int width, int height)
{
	image = Display::getInstance()->getImplementation()->scale(image, width, height);
}

bool Image::scaleArray(int srcWidth, int srcHeight, int height, int width, shared_ptr<VectorArray<int> > currentArray, shared_ptr<VectorArray<int> > destinationArray)
{
	int yRatio = (srcHeight << 16) / height;
	int xRatio = (srcWidth << 16) / width;
	int xPos = xRatio / 2;
	int yPos = yRatio / 2;

	bool testOpaque = Display::getInstance()->numColors() <= 65536 && (!opaqueTested);
	bool currentOpaque = true;
	for (int y = 0; y < height; y++)
	{
		int srcY = yPos >> 16;
		getRGB(currentArray, 0, 0, srcY, srcWidth, 1);
		for (int x = 0; x < width; x++)
		{
			int srcX = xPos >> 16;
			int destPixel = x + y * width;
			if ((destPixel >= 0 && destPixel < destinationArray->size()) && (srcX < currentArray->size()))
			{
				destinationArray->elementAt(destPixel) = currentArray->elementAt(srcX);

				currentOpaque = testOpaque && currentOpaque && (currentArray->elementAt(srcX) & 0xff000000) == 0xff000000;
			}
			xPos += xRatio;
		}
		yPos += yRatio;
		xPos = xRatio / 2;
	}
	if(testOpaque)
	{
		this->opaque = currentOpaque;
	}
	return opaque;
}

bool Image::isAnimation()
{
	return animated;
}

bool Image::animate()
{
	if(imageTime == -1) 
	{
		imageTime = System::currentTimeMillis();
	}
	bool val = Display::getInstance()->getImplementation()->animateImage(image, imageTime);
	imageTime = System::currentTimeMillis();
	return val;
}

bool Image::isOpaque()
{
	if(!opaqueTested)
	{
		opaque = Display::getInstance()->getImplementation()->isOpaque(this->shared_from_this(), image);
		opaqueTested = true;
	}
	return opaque;
}

void Image::drawImage(shared_ptr<Graphics> g, shared_ptr<Object> nativeGraphics, int x, int y)
{
	g->drawImage(image, x, y, transform);
}
__GUI_END_NAMESPACE
