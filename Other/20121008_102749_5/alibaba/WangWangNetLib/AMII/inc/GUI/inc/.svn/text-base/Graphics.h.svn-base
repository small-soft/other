#ifndef __GUI_GRAPHICS_H__
#define __GUI_GRAPHICS_H__

#include "inc/Object.h"
#include "inc/LWUITImplementation.h"
#include "inc/String.h"

#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Font;
class Image;
class CustomFont;
class Display;
class LWUITImplementation;
class NativeGraphics;

class Graphics : public Object,public enable_shared_from_this<Graphics>
{
public:
	Graphics(shared_ptr<NativeGraphics>  nativeGraphics);
	virtual ~Graphics(void);
private:
	int xTranslate;
	int yTranslate;
	int color;
	int fgColor;
	int bgColor;
	shared_ptr<Font> current; //= Font.getDefaultFont();

private:
	shared_ptr<LWUITImplementation> impl;
	shared_ptr<NativeGraphics>  nativeGraphics;

public:
	void setGraphics(shared_ptr<NativeGraphics>  g);
	shared_ptr<NativeGraphics> getGraphics();
	void translate(int x, int y);
	int getTranslateX();
	int getTranslateY();
	int getColor();
	void setColor(int RGB);
	/*int getFgColor();
	void setFgColor(int RGB);
	int getBgColor();
	void setBgColor(int RGB);*/
	shared_ptr<Font> getFont();
	void setFont(shared_ptr<Font> font);
	int getClipX();
	int getClipY();
	int getClipWidth();
	int getClipHeight();
	void clipRect(int x, int y, int width, int height);
	void setClip(int x, int y, int width, int height);
	void drawLine(int x1, int y1, int x2, int y2);
	void fillRect(int x, int y, int width, int height);
	void drawRect(int x, int y, int width, int height);
	void drawRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight);
	void lighterColor(int factor);
	void darkerColor(int factor);
	void fillRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight);
	void fillArc(int x, int y, int width, int height, int startAngle, int arcAngle);
	void drawArc(int x, int y, int width, int height, int startAngle, int arcAngle);
	void drawString(shared_ptr<String> str, int x, int y) ;
	void drawChar(char character, int x, int y);
	void drawChars(shared_ptr<String> data, int offset, int length, int x, int y) ;

	void drawImage(shared_ptr<Image> img, int x, int y);
//	void drawImage(shared_ptr<NativeImage>  img, int x, int y);
	void drawImage(shared_ptr<NativeImage>  img, int x, int y, int transform );
	void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
	void drawRGB(shared_ptr<VectorArray<int> >rgbData, int offset, int x, int y, int w, int h, bool processAlpha);
	void fillRadialGradient(int startColor, int endColor, int x, int y, int width, int height) ;
	void fillRectRadialGradient(int startColor, int endColor, int x, int y, int width, int height, float relativeX, float relativeY, float relativeSize);
	void fillLinearGradient(int startColor, int endColor, int x, int y, int width, int height, bool horizontal);
	void fillRect(int x, int y, int w, int h, unsigned char alpha);
	void fillPolygon(shared_ptr<VectorArray<int> > xPoints, shared_ptr<VectorArray<int> > yPoints, int nPoints) ;
	
	void drawImageArea(shared_ptr<Image> img, int x, int y, int imageX, int imageY, int imageWidth, int imageHeight);
	void drawPolygon(shared_ptr<Vector<int> > xPoints, shared_ptr<Vector<int> > yPoints, int nPoints);
	bool isAlphaSupported() ;
	void setAlpha(int a);
	int getAlpha();
	bool isAntiAliasingSupported();
	bool isAntiAliasedTextSupported();
	bool isAntiAliased();
	void setAntiAliased(bool a) ;
	void setAntiAliasedText(bool a);
	bool isAntiAliasedText(bool a) ;
	bool isAffineSupported();
	void resetAffine();
	void scale(float x, float y) ;
	void rotate(float angle);
	void shear(float x, float y);
	void BitBlt(shared_ptr<Image> src,int x,int y);
};
__GUI_END_NAMESPACE

#endif
