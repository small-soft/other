#ifndef _RGBIMAGE_H_
#define _RGBIMAGE_H_

#include "inc\Image.h"
#include "inc\Config.h"
__GUI_BEGIN_NAMESPACE

class Image;

class RGBImage :
	public Image
{
public:
	RGBImage(shared_ptr<Image> img);
	RGBImage(shared_ptr<VectorArray<int> > rgb, int width, int height);
	virtual ~RGBImage(void);
private:
	int width;
	int height;
	shared_ptr<VectorArray<int> > rgb;
	bool opaque;
public:
	virtual shared_ptr<Image> subImage(int x, int y, int width, int height, bool processAlpha);
	virtual shared_ptr<Image> scaled(int width, int height); 
	virtual void scale(int width, int height);
	virtual shared_ptr<Image> rotate(int degrees);
	virtual shared_ptr<Image> modifyAlpha(unsigned char alpha);
	virtual shared_ptr<Graphics> getGraphics();
	virtual shared_ptr<VectorArray<int> > getRGB();
	virtual void getRGB(shared_ptr<VectorArray<int> > rgbData,
		int offset,
		int x,
		int y,
		int width,
		int height);
	virtual void drawImage(shared_ptr<Graphics> g, shared_ptr<Object>  nativeGraphics, int x, int y);
	virtual void setOpaque(bool opaque);
	virtual bool isOpaque();
	virtual int getWidth();
	virtual int getHeight();
};
__GUI_END_NAMESPACE

#endif
