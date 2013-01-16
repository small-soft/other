#ifndef __INDEXED_IMAGE_H__
#define __INDEXED_IMAGE_H__

#include "inc/Image.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class IndexedImage :public Image
{
public:
	IndexedImage(void);
	IndexedImage(int width, int height, shared_ptr<VectorArray<int> > palette, shared_ptr<VectorArray<unsigned char> > data);
	virtual ~IndexedImage(void);
	static void deinitialize();
private:
	int width;
	int height;

	// package protected for access by the resource editor
	shared_ptr<VectorArray<unsigned char> > imageDataByte;
	shared_ptr<VectorArray<int> > palette; 
	static shared_ptr<VectorArray<int> > lineCache;
private:
	void initOpaque();
	IndexedImage(int width, int height, shared_ptr<VectorArray<int> > palette,shared_ptr<VectorArray<int> > rgb);
	int paletteOffset(int rgb);
public:
	static shared_ptr<Image> pack(shared_ptr<String> imageName);
	shared_ptr<Image> subImage(int x, int y, int width, int height, bool processAlpha);
	shared_ptr<Image> modifyAlpha(unsigned char alpha);
	void getRGB(shared_ptr<VectorArray<int> > rgbData, int offset, int x, int y, int width, int height);
	static shared_ptr<Image> pack(shared_ptr<VectorArray<int> > rgb, int width, int height);
	static shared_ptr<Image> pack(shared_ptr<Image> sourceImage);
	static bool contains(shared_ptr<VectorArray<int> > array, int length, int value);
	int getWidth();
	int getHeight();
	void scale(int width, int height);
	shared_ptr<Image> scaled(int width, int height);
	virtual shared_ptr<VectorArray<int> > getRGBImpl();
	shared_ptr<VectorArray<int> > getPalette();
	shared_ptr<VectorArray<unsigned char> > getImageDataByte();
	shared_ptr<VectorArray<unsigned char> > toByteArray();
	static IndexedImage load(shared_ptr<VectorArray<unsigned char> > data);
protected:
	void drawImage(shared_ptr<Graphics> g, shared_ptr<Object> nativeGraphics, int x, int y);
	shared_ptr<VectorArray<unsigned char> > scaleArray(shared_ptr<VectorArray<unsigned char> > sourceArray, int width, int height);
};
__GUI_END_NAMESPACE

#endif
