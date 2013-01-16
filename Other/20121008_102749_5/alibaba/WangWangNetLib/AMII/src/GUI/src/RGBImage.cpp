#include "AMGui.h"
__GUI_BEGIN_NAMESPACE


RGBImage::RGBImage( shared_ptr<VectorArray<int> > rgb, int width, int height )
{
	this->width = width;
	this->height = height;
	this->rgb = rgb;
}

RGBImage::RGBImage( shared_ptr<Image> img )
{
	width = img->getWidth();
	height = img->getHeight();
	rgb = img->getRGBCached();
}
RGBImage::~RGBImage(void)
{
}

shared_ptr<Image> RGBImage::subImage( int x, int y, int width, int height, bool processAlpha )
{
	int size = width * height;
	shared_ptr<VectorArray<int > > arr = new VectorArray<int> (size);
	for(int iter = 0 ; iter < size ; iter++) {
		int destY = iter / width;
		int destX = iter % width;
		int offset = x + destX + ((y + destY) * this->width);
		(*arr)[iter] = (*rgb)[offset];
	}
	shared_ptr<Image> image = new RGBImage(arr, width, height);
	return image;

}

shared_ptr<Image> RGBImage::scaled( int width, int height )
{

	int srcWidth = getWidth();
	int srcHeight = getHeight();

	// no need to scale
	if(srcWidth == width && srcHeight == height){
		return this->shared_from_this();
	}
	shared_ptr<VectorArray<int > >  currentArray = new VectorArray<int >(srcWidth);
	shared_ptr<VectorArray<int > >  destinationArray = new VectorArray<int >(width * height);
	scaleArray(srcWidth, srcHeight, height, width, currentArray, destinationArray);

	// currently we only support byte data...
	shared_ptr<Image> image = new RGBImage(destinationArray, width, height);
	return image;

}

void RGBImage::scale( int width, int height )
{

	int srcWidth = getWidth();
	int srcHeight = getHeight();

	// no need to scale
	if(srcWidth == width && srcHeight == height){
		return;
	}
	shared_ptr<VectorArray<int > >  currentArray = new VectorArray<int >(srcWidth);
	shared_ptr<VectorArray<int > >  destinationArray = new VectorArray<int >(width * height);
	scaleArray(srcWidth, srcHeight, height, width, currentArray, destinationArray);

	this->width = width;
	this->height = height;
	this->rgb = destinationArray;

}

shared_ptr<Image> RGBImage::rotate( int degrees )
{
	// not support
	shared_ptr<Image> image;
	return image;
}

shared_ptr<Image> RGBImage::modifyAlpha( unsigned char alpha )
{
	shared_ptr<VectorArray<int > > arr = new VectorArray<int >(rgb->size());
//	System.arraycopy(rgb, 0, arr, 0, rgb->size());
	for(int i = 0 ; i < rgb->size() ; i ++)
		(*arr)[i] = (*rgb)[i];
	
	int alphaInt = (((int)alpha) << 24) & 0xff000000;
	for(int iter = 0 ; iter < rgb->size() ; iter++) {
		if(((*arr)[iter] & 0xff000000) != 0) {
			(*arr)[iter] = ((*arr)[iter] & 0xffffff) | alphaInt;
		}
	}
	shared_ptr<Image> image = new RGBImage(arr, width, height);
	return image;

}

shared_ptr<Graphics> RGBImage::getGraphics()
{
	//not support
	shared_ptr<Graphics> g;
	return g;
}

shared_ptr<VectorArray<int> > RGBImage::getRGB()
{
	return rgb;
}

void RGBImage::getRGB( shared_ptr<VectorArray<int> > rgbData, int offset, int x, int y, int width, int height )
{

	int startPoint = y * this->width + x;
	for(int rows = 0 ; rows < height ; rows++) {
		int currentRow = rows * width;
		for(int columns = 0 ; columns < width ; columns++) {
			(*rgbData)[offset + currentRow + columns] = (*rgb)[startPoint + columns];
		}
		startPoint += this->width;
	}

}

void RGBImage::drawImage( shared_ptr<Graphics> g, shared_ptr<Object> nativeGraphics, int x, int y )
{
	  g->drawRGB(rgb, 0, x, y, width, height, !opaque);
}

void RGBImage::setOpaque( bool opaque )
{
	 this->opaque = opaque;
}

bool RGBImage::isOpaque()
{
	 return opaque;
}

int RGBImage::getWidth()
{
	 return width;
}

int RGBImage::getHeight()
{
	 return height;
}
__GUI_END_NAMESPACE
