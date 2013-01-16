#ifndef __GUI_IMAGE_H__
#define __GUI_IMAGE_H__

#include "inc/Vector.h"
#include "inc/Map.h"
#include "inc/Object.h"
#include "inc/String.h"
#include "inc/InputStream.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE

class Graphics;
class Dimension;
class InputStream;
class RGBImage;
class NativeImage;
class NativeGraphics;

class Image : public Object,public enable_shared_from_this<Image>
{
	typedef Map<Dimension, shared_ptr<Image> > image_map;
public:
	void init();
	Image(void);
	Image(shared_ptr<NativeImage>  image);
	Image(shared_ptr<VectorArray<int> > imageArray, int w, int h);

	virtual ~Image(void);
private:
	weak_ptr<VectorArray<int> >  rgbCache;
	shared_ptr<NativeImage>  image;   
	shared_ptr<Graphics>  graphic;   
	int transform;
	bool opaqueTested;
	bool opaque;
	shared_ptr<image_map> scaleCache;
	bool animated;
	long imageTime;
	bool svg;
protected:
	shared_ptr<image_map> getScaleCache();
	shared_ptr<Image> getCachedImage(const Dimension size);
public :
	void cacheImage( Dimension size, shared_ptr<Image> i ) ;
	void setImage(shared_ptr<NativeImage>  image);
	virtual void setOpaque(bool opaque);
	void setOpaqueTested(bool opaque);
	static bool isSVGSupported();
	shared_ptr<Object>  getSVGDocument();
	static shared_ptr<Image> createSVG(shared_ptr<String> baseURL, bool animated, VectorArray<unsigned char> data);
	bool isSVG();
	shared_ptr<Object>  createMask() ;
	shared_ptr<Image> applyMask(shared_ptr<Object>  mask, int x, int y);
	shared_ptr<Image> applyMask(shared_ptr<Object>  mask);
	virtual shared_ptr<Image> subImage(int x, int y, int width, int height, bool processAlpha);
	virtual shared_ptr<Image> rotate(int degrees);
	static shared_ptr<Image> createIndexed(int width, int height, shared_ptr<VectorArray<int> > palette,  shared_ptr<VectorArray<unsigned char> > data);
	virtual shared_ptr<Image> modifyAlpha( unsigned char alpha);
	shared_ptr<Image> modifyAlphaWithTranslucency( unsigned char alpha);
	virtual shared_ptr<Image> modifyAlpha( unsigned char alpha, int removeColor);

	static shared_ptr<Image> createImage(shared_ptr<String> path);
	static shared_ptr<Image> createImageFromStream(shared_ptr<InputStream> stream);
	static shared_ptr<Image> createImageFromRGBWithRect(shared_ptr<VectorArray<int> > rgb, int width, int height);
	static shared_ptr<Image> createImage(int width, int height);
	static bool isAlphaMutableImageSupported();
	static shared_ptr<Image> createImage(int width, int height, int fillColor);
	static shared_ptr<Image> createImage(VectorArray<unsigned char> bytes,int offset,int len);

	virtual shared_ptr<Graphics> getGraphics() ;
	virtual int getWidth();
	virtual int getHeight();
	virtual void drawImageArea(shared_ptr<Graphics> g, shared_ptr<NativeGraphics>  nativeGraphics, int x, int y, int imageX, int imageY, int imageWidth, int imageHeight);
	virtual void getRGB(shared_ptr<VectorArray<int> > rgbData, int offset, int x, int y, int width, int height);
	virtual void toRGB(shared_ptr<RGBImage> image, int destX, int destY, int x, int y, int width, int height);
	virtual shared_ptr<VectorArray<int> > getRGB();
	shared_ptr<VectorArray<int> > getRGBCached();
	shared_ptr<VectorArray<int> > getRGBCache();
	virtual shared_ptr<VectorArray<int> > getRGBImpl();
	virtual shared_ptr<Image> scaledWidth(int width);
	virtual shared_ptr<Image> scaledHeight(int height);
	virtual shared_ptr<Image> scaledSmallerRatio(int width, int height);
	virtual shared_ptr<Image> scaled(int width, int height);
	shared_ptr<NativeImage>  getImage();
	virtual void scale(int width, int height);
	bool scaleArray(int srcWidth, int srcHeight, int height, int width, shared_ptr<VectorArray<int> > currentArray, shared_ptr<VectorArray<int> > destinationArray);
	virtual bool isAnimation();
	virtual bool animate() ;
	virtual bool isOpaque();
	virtual void drawImage(shared_ptr<Graphics> g, shared_ptr<Object>  nativeGraphics, int x, int y);
};
__GUI_END_NAMESPACE

#endif
