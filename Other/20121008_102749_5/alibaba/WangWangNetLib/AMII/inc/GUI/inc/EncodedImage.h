#ifndef _ENCODEDIMAGE_H_
#define _ENCODEDIMAGE_H_

#include "AMFS.h"
#include "inc\Image.h"
#include "inc\Config.h"
__GUI_BEGIN_NAMESPACE
class EncodedImage : public Image
{
private:
	shared_ptr<VectorArray<unsigned char> > imageData;
	int width;
	int height;
	bool opaqueChecked;
	bool opaque;
	shared_ptr<Image> cache;
private:
	EncodedImage();
	EncodedImage(shared_ptr<VectorArray<unsigned char> > imageData );
public:
	shared_ptr<VectorArray<unsigned char> > getImageData();
	static shared_ptr<EncodedImage> create(shared_ptr<String> data);
	static shared_ptr<EncodedImage> create(shared_ptr<InputStream> i);
	shared_ptr<Image> getInternal();
	shared_ptr<Image> getBMPImage();
	static shared_ptr<EncodedImage> create(shared_ptr<VectorArray<unsigned char> > i);

	shared_ptr<Graphics> getGraphics();
	shared_ptr<Image> subImage(int x, int y, int width, int height, bool processAlpha);
	shared_ptr<Image> rotate(int degrees);
	shared_ptr<Image> modifyAlpha(unsigned char alpha);
	shared_ptr<Image> modifyAlpha(unsigned char alpha, int removeColor);
	int getWidth();
	int getHeight();
	void drawImage(shared_ptr<Graphics> g, shared_ptr<Object> nativeGraphics, int x, int y);
	void getRGB(shared_ptr<VectorArray<int> > rgbData, int offset, int x, int y, int width, int height);
	void toRGB(shared_ptr<RGBImage> image, int destX, int destY, int x, int y, int width, int height);
	shared_ptr<Image> scaledWidth(int width);
	shared_ptr<Image> scaledHeight(int height);
	shared_ptr<Image> scaledSmallerRatio(int width, int height);
	shared_ptr<Image> scaled(int width, int height);
	void scale(int width, int height);
	bool isAnimation();
	bool isOpaque();

	virtual ~EncodedImage() {}
};
__GUI_END_NAMESPACE

#endif
