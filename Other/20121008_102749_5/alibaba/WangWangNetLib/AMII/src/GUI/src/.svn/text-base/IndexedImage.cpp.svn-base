#include "AMGui.h"

__GUI_BEGIN_NAMESPACE
shared_ptr<VectorArray<int> > IndexedImage::lineCache;
IndexedImage::IndexedImage(int width, int height, shared_ptr<VectorArray<int> > palette, shared_ptr<VectorArray<unsigned char> > data)
:width(width),height(height),palette(palette),imageDataByte(data)
{
	initOpaque();
}

IndexedImage::IndexedImage( int width, int height, shared_ptr<VectorArray<int> > palette,shared_ptr<VectorArray<int> > rgb )
:width(width),height(height),palette(palette)
{
	
	// byte based package image
	imageDataByte = new VectorArray<unsigned char>(width * height);
	for(int iter = 0 ; iter < width * height ; iter++) 
	{
		(*imageDataByte)[iter] = (unsigned char)paletteOffset((*rgb)[iter]);
	}
	initOpaque();
}
IndexedImage::~IndexedImage(void)
{
}

void IndexedImage::initOpaque()
{
	if(palette.get()!= NULL) 
	{
		for( int iter = 0 ; iter < palette->size() ; iter++) 
		{
			if(((*palette)[iter] & 0xff000000) != 0xff000000) 
			{
				setOpaque(false);
				return;
			}
		}
		setOpaque(true);
	}
	else 
	{
		setOpaque(false);
	}

}

int IndexedImage::paletteOffset( int rgb )
{
	for( int iter = 0 ; iter < palette->size() ; iter++) 
	{
		if(rgb == (*palette)[iter]) 
		{
			return iter;
		}
	}
	//exception
	return 0;
}

shared_ptr<Image> IndexedImage::pack(shared_ptr<String> imageName )
{
	return pack(Image::createImage(imageName));
}

shared_ptr<Image> IndexedImage::pack( shared_ptr<VectorArray<int> > rgb, int width, int height )
{
	int arrayLength = width * height;

	// using a Vector is slower for a small scale device and this is mission critical code
	shared_ptr<VectorArray<int> > tempPalette = new VectorArray<int>(256);

	int paletteLocation = 0;
	for(int iter = 0 ; iter < arrayLength ; iter++) 
	{
		int current = (*rgb)[iter];
		if(!contains(tempPalette, paletteLocation, current)) 
		{
			if(paletteLocation > 255) 
			{
				shared_ptr<Image> img;
				return img;
			}
			(*tempPalette)[paletteLocation] = current;
			paletteLocation++;
		}
	}

	// we need to "shrink" the palette array
	/*if(paletteLocation != tempPalette->size()) {
		int[] newArray = new int[paletteLocation];
		System.arraycopy(tempPalette, 0, newArray, 0, paletteLocation);
		tempPalette = newArray;
	}*/


	shared_ptr<Image> i = new IndexedImage(width, height, tempPalette, rgb);
	return i;

}

shared_ptr<Image> IndexedImage::pack(shared_ptr<Image> sourceImage )
{
	int width = sourceImage->getWidth();
	int height = sourceImage->getHeight();
	shared_ptr<VectorArray<int> > rgb = sourceImage->getRGBCached();

	shared_ptr<Image> i = pack(rgb, width, height);
	if(i.get() == NULL) 
	{
		return sourceImage;
	}
	return i;

}
shared_ptr<Image> IndexedImage::subImage( int x, int y, int width, int height, bool processAlpha )
{
	shared_ptr<VectorArray<unsigned char> > arr = new VectorArray<unsigned char>(width * height);
	for(int iter = 0 ; iter < width * height ; iter++) 
	{
		int destY = iter / width;
		int destX = iter % width;
		int offset = x + destX + ((y + destY) * this->width);
		(*arr)[iter] = (*imageDataByte)[offset];
	}

	return new IndexedImage(width, height, palette, arr);
}

shared_ptr<Image> IndexedImage::modifyAlpha( unsigned char alpha )
{
	shared_ptr<VectorArray<int> >  newPalette = new VectorArray<int>(palette->size());

	int alphaInt = (((int)alpha) << 24) & 0xff000000;
	for( int iter = 0 ; iter < palette->size() ; iter++) 
	{
		if(((*palette)[iter] & 0xff000000) != 0) 
		{
			(*newPalette)[iter] = ((*palette)[iter] & 0xffffff) | alphaInt;
		}
	}
	return new IndexedImage(width, height, newPalette, imageDataByte);

}


void IndexedImage::getRGB( shared_ptr<VectorArray<int> > rgbData, int offset, int x, int y, int width, int height )
{

	// need to support scanlength???
	int startPoint = y * this->width + x;
	for(int rows = 0 ; rows < height ; rows++) 
	{
		int currentRow = rows * width;
		for(int columns = 0 ; columns < width ; columns++) 
		{
			int i = (*imageDataByte)[startPoint + columns] & 0xff;
			(*rgbData)[offset + currentRow + columns] = (*palette)[i];
		}
		startPoint += this->width;
	}
}

bool IndexedImage::contains( shared_ptr<VectorArray<int> > array, int length, int value )
{
	for(int iter = 0 ; iter < length ; iter++) 
	{
		if((*array)[iter] == value) 
		{
			return true;
		}
	}
	return false;

}

void IndexedImage::drawImage( shared_ptr<Graphics> g, shared_ptr<Object> nativeGraphics, int x, int y )
{
	if(lineCache.get() == NULL/* || lineCache.get()->size() < width * 3*/) {
		lineCache = new VectorArray<int>(width *3);
	}

	// for performance we can calculate the visible drawing area so we don't have to
	// calculate the whole array
	int clipY = g->getClipY();
	int clipBottomY = g->getClipHeight() + clipY;
	int firstLine = 0;
	int lastLine = height;
	if(clipY > y) {
		firstLine = clipY - y;
	} 
	if(clipBottomY < y + height) {
		lastLine = clipBottomY - y;
	}


	for(int line = firstLine ; line < lastLine ; line += 3) {
		int currentPos = line * width;
		int rowsToDraw = min(3, height - line);
		int amount = width * rowsToDraw;
		for(int position = 0 ; position < amount ; position++) {
			int i = imageDataByte->elementAt(position + currentPos) & 0xff;                
			(*lineCache)[position] = palette.get()->elementAt(i) ;
		}
		g->drawRGB(lineCache, 0, x, y + line, width, rowsToDraw, true);
	}

}

int IndexedImage::getWidth()
{
	return width;
}

int IndexedImage::getHeight()
{
	 return height;
}

void IndexedImage::scale( int width, int height )
{
	shared_ptr<IndexedImage> p = dynamic_cast<IndexedImage*>(scaled(width, height).get());
	this->imageDataByte = p->imageDataByte;
	this->width = width;
	this->height = height;
}

shared_ptr<Image> IndexedImage::scaled( int width, int height )
{
	int srcWidth = getWidth();
	int srcHeight = getHeight();

	// no need to scale
	if(srcWidth == width && srcHeight == height){
		return this->shared_from_this();
	}
	Dimension d(width, height);
	shared_ptr<Image> i = getCachedImage(d);
	// currently we only support byte data...
	i = new IndexedImage(width, height, palette, scaleArray(imageDataByte, width, height));
	cacheImage(d, i);
	return i;

}

shared_ptr<VectorArray<unsigned char> > IndexedImage::scaleArray( shared_ptr<VectorArray<unsigned char> > sourceArray, int width, int height )
{
	int srcWidth = getWidth();
	int srcHeight = getHeight();

	// no need to scale
	if(srcWidth == width && srcHeight == height)
	{
		return sourceArray;
	}
	shared_ptr<VectorArray<unsigned char> > destinationArray = new VectorArray<unsigned char>(width * height);

	//Horizontal Resize
	int yRatio = (srcHeight << 16) / height;
	int xRatio = (srcWidth << 16) / width;
	int xPos = xRatio / 2;
	int yPos = yRatio / 2;
	for (int x = 0; x < width; x++) 
	{
		int srcX = xPos >> 16;
		for(int y = 0 ; y < height ; y++) 
		{
			int srcY = yPos >> 16;
			int destPixel = x + y * width;
			int srcPixel = srcX + srcY * srcWidth;
			if((destPixel >= 0 && destPixel < width * height) && (srcPixel >= 0 && srcPixel < sourceArray->size())) 
			{
					(*destinationArray)[destPixel] = (*sourceArray)[srcPixel];
			}
			yPos += yRatio;
		}
		yPos = yRatio / 2;
		xPos += xRatio;
	}
	return destinationArray;
}

shared_ptr<VectorArray<int> > IndexedImage::getRGBImpl()
{
	shared_ptr<VectorArray<int> > rgb = new VectorArray<int>(width * height);
	for(int iter = 0 ; iter < width * height ; iter++) 
	{
		int i = (*imageDataByte)[iter] & 0xff;
		(*rgb)[iter] = (*palette)[i] ;
	}
	return rgb;
}

shared_ptr<VectorArray<int> > IndexedImage::getPalette()
{
	return palette;
}

shared_ptr<VectorArray<unsigned char> > IndexedImage::getImageDataByte()
{
	return imageDataByte;
}

void IndexedImage::deinitialize()
{
	lineCache.reset();
}
__GUI_END_NAMESPACE
