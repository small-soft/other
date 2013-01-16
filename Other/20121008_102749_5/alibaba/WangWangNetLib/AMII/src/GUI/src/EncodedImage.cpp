#include "AMGui.h"
__GUI_BEGIN_NAMESPACE

EncodedImage::EncodedImage(shared_ptr<VectorArray<unsigned char> > imageData) : Image()
{
	this->imageData = imageData;
	width = -1;
	height = -1;
	opaqueChecked = false;
	opaque = false;
}

shared_ptr<VectorArray<unsigned char> > EncodedImage::getImageData()
{
	return this->imageData;
}

shared_ptr<EncodedImage> EncodedImage::create( shared_ptr<String> data )
{
	return create(Display::getInstance()->getResourceAsStream(data));
}

shared_ptr<EncodedImage> EncodedImage::create( shared_ptr<InputStream> i )
{
	//to-check
	shared_ptr<EncodedImage> nullEncodeImage;
	return nullEncodeImage;
}

shared_ptr<EncodedImage> EncodedImage::create(shared_ptr<VectorArray<unsigned char> > i )
{
	//to-check
	if( i.get() == NULL )
	{
		shared_ptr<EncodedImage> nullEncodeImage;
		return nullEncodeImage;
	}
	return new EncodedImage(i);
}
shared_ptr<Image> EncodedImage::getInternal()
{
	if(cache.get() != NULL) 
	{
		shared_ptr<Image> i = cache;
		if(i.get() != NULL )
		{
			return i;
		}
	}
	shared_ptr<Image> i = Image::createImage(*imageData, 0, imageData->size());
	cache = i;
	return i;
}

shared_ptr<Image> EncodedImage::getBMPImage()
{
	return getInternal();
}

shared_ptr<Image> EncodedImage::subImage( int x, int y, int width, int height, bool processAlpha )
{
	return getInternal()->subImage(x, y, width, height, processAlpha);
}

shared_ptr<Image> EncodedImage::rotate( int degrees )
{
	return getInternal()->rotate(degrees);
}

shared_ptr<Image> EncodedImage::modifyAlpha( unsigned char alpha )
{
	return getInternal()->modifyAlpha(alpha);
}

shared_ptr<Image> EncodedImage::modifyAlpha( unsigned char alpha, int removeColor )
{
	return getInternal()->modifyAlpha(alpha, removeColor);
}

shared_ptr<Graphics> EncodedImage::getGraphics()
{
	//to check
	//return null;
	shared_ptr<Graphics> g;
	return g;
}

int EncodedImage::getWidth()
{
	if(width > -1) 
	{
		return width;
	}
	width = getInternal()->getWidth();
	return width;
}

int EncodedImage::getHeight()
{
	if(height > -1) 
	{
		return height;
	}
	height = getInternal()->getHeight();
	return height;
}

void EncodedImage::drawImage( shared_ptr<Graphics> g, shared_ptr<Object> nativeGraphics, int x, int y )
{
	getInternal()->drawImage(g, nativeGraphics, x, y);
}

void EncodedImage::getRGB( shared_ptr<VectorArray<int> > rgbData, int offset, int x, int y, int width, int height )
{
	getInternal()->getRGB(rgbData, offset, x, y, width, height);
}

void EncodedImage::toRGB( shared_ptr<RGBImage> image, int destX, int destY, int x, int y, int width, int height )
{
	getInternal()->toRGB(image, destX, destY, x, y, width, height);
}

shared_ptr<Image> EncodedImage::scaledWidth( int width )
{
	return getInternal()->scaledWidth(width);
}

shared_ptr<Image> EncodedImage::scaledHeight( int height )
{
	return getInternal()->scaledHeight(height);
}

shared_ptr<Image> EncodedImage::scaledSmallerRatio( int width, int height )
{
	return getInternal()->scaledSmallerRatio(width, height);
}

shared_ptr<Image> EncodedImage::scaled( int width, int height )
{
	return getInternal()->scaled(width, height);
}

void EncodedImage::scale( int width, int height )
{
	getInternal()->scale(width, height);
}

bool EncodedImage::isAnimation()
{
	return false;
}

bool EncodedImage::isOpaque()
{
	if(opaqueChecked) 
	{
		return opaque;
	}
	opaque = getInternal()->isOpaque();
	return opaque;
}
__GUI_END_NAMESPACE