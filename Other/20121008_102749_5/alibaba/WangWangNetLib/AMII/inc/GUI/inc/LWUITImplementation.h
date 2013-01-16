#ifndef LWUIT_IMPLEMENTATION_H
#define LWUIT_IMPLEMENTATION_H

#include "inc/Vector.h"
#include "inc/Map.h"
#include "inc/Graphics.h"
#include "inc/Form.h"
#include "inc/Animation.h"
#include "inc/Component.h"
#include "inc/InputStream.h"

#include "inc/String.h"
#include <math.h>
#include <stdio.h>

#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Form;
class Animation;
class Graphics;
class Component;
class IndexedImage;
class Image;
class Rectangle;
class Locker;
class InputStream;
class NativeImage;
class NativeFont;
class NativeGraphics;

class LWUITImplementation
{
public:
	static int MAX_COUNT ;
public:
	virtual void updateRect(int x, int y ,int width, int height) = 0 ;
	static void deinitialize();
	virtual void init(void *m) = 0;	
	virtual void playDialogSound(const int type);
	virtual void vibrate(int duration);
	virtual void flashBacklight(int duration);	
	virtual int getDisplayWidth() = 0;
	virtual int getDisplayHeight() = 0;
	bool handleEDTException(exception err);
	virtual void editString(shared_ptr<Component> cmp, int maxSize, int constraint, shared_ptr<String> text) = 0;
	virtual void saveTextEditingState();
	bool hasPendingPaints();
	shared_ptr<Object> getVideoControl(shared_ptr<Object> player);
	virtual int numAlphaLevels();
	virtual int numColors();
	virtual void paintOverlay(shared_ptr<Graphics> g);
	void paintDirty();
	virtual void edtIdle(bool enter);
	virtual void flushGraphics(int x, int y, int width, int height) = 0;
	virtual void flushGraphics() = 0;
	shared_ptr<Graphics> getLWUITGraphics();
	void setLWUITGraphics(shared_ptr<Graphics> g);
	void setDisplayLock(shared_ptr<Locker> lock);
	shared_ptr<Locker> getDispalyLock();

	void repaint(shared_ptr<Animation> cmp);
	virtual void getRGB(shared_ptr<NativeImage> nativeImage, shared_ptr<VectorArray<int> > arr, int offset, int x, int y, int width, int height) = 0;
	virtual shared_ptr<NativeImage> createImage(shared_ptr<VectorArray<int> > rgb, int width, int height) = 0;
	virtual shared_ptr<NativeImage> createImage(shared_ptr<String> path) = 0;
	virtual shared_ptr<NativeImage> createImage(shared_ptr<InputStream> i) = 0;
	virtual shared_ptr<NativeImage> createMutableImage(int width, int height,int fillColor) = 0;
	bool isAlphaMutableImageSupported();
	virtual shared_ptr<NativeImage> createImage(VectorArray<unsigned char> bytes, int offset, int len) = 0;

	virtual int getImageWidth(shared_ptr<NativeImage> i) = 0;
	virtual int getImageHeight(shared_ptr<NativeImage> i) = 0;
	
	virtual shared_ptr<NativeImage> scale(shared_ptr<NativeImage> nativeImage, int width, int height) = 0;
	static int round(double d);
	shared_ptr<NativeImage> rotate(shared_ptr<NativeImage> image, int degrees);
	
	virtual int getSoftkeyCount() = 0;
	virtual shared_ptr<Vector<int> > getSoftkeyCode(int index) = 0;
	virtual int getClearKeyCode() = 0;
	virtual int getBackspaceKeyCode() = 0;
	virtual int getBackKeyCode() = 0;
	virtual int getGameAction(int keyCode) = 0;
	virtual int getKeyCode(int gameAction) = 0;
	virtual bool isTouchDevice() = 0;

	void setCurrentForm(shared_ptr<Form> f);
	virtual void confirmControlView();
	shared_ptr<Form> getCurrentForm();
	bool isTranslationSupported();
	virtual void translate(shared_ptr<NativeGraphics> graphics, int x, int y);
	int getTranslateX(shared_ptr<NativeGraphics> graphics);
	int getTranslateY(shared_ptr<NativeGraphics> graphics);
	
	virtual int getColor(shared_ptr<NativeGraphics> graphics) = 0;
	virtual void setColor(shared_ptr<NativeGraphics> graphics, int RGB) = 0;
	//virtual int getBgColor(shared_ptr<NativeGraphics> graphics) = 0;
	//virtual void setBgColor(shared_ptr<NativeGraphics> graphics, int RGB) = 0;
	//virtual int getFgColor(shared_ptr<NativeGraphics> graphics) = 0;
	//virtual void setFgColor(shared_ptr<NativeGraphics> graphics, int RGB) = 0;
	virtual void setAlpha(shared_ptr<NativeGraphics> graphics, int alpha) = 0;
	virtual int getAlpha(shared_ptr<NativeGraphics> graphics) = 0;

	bool isAlphaGlobal();
	bool isAntiAliasingSupported();
	bool isAntiAliasedTextSupported();
	virtual void setAntiAliased(shared_ptr<NativeGraphics> graphics, bool a);
	bool isAntiAliased(shared_ptr<NativeGraphics> graphics);
	virtual void setAntiAliasedText(shared_ptr<NativeGraphics> graphics, bool a);
	bool isAntiAliasedText(shared_ptr<NativeGraphics> graphics);
	virtual void setNativeFont(shared_ptr<NativeGraphics> graphics, shared_ptr<NativeFont> font) = 0;
	shared_ptr<Rectangle> getClipRect(shared_ptr<NativeGraphics> graphics);
	virtual int getClipX(shared_ptr<NativeGraphics> graphics) = 0;
	virtual int getClipY(shared_ptr<NativeGraphics> graphics) = 0;
	virtual int getClipWidth(shared_ptr<NativeGraphics> graphics) = 0;
	virtual int getClipHeight(shared_ptr<NativeGraphics> graphics) = 0;

	virtual void setClipRect(shared_ptr<NativeGraphics> graphics, shared_ptr<Rectangle> rect);
	virtual void setClip(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height) = 0;
	virtual void clipRect(shared_ptr<NativeGraphics> graphics, shared_ptr<Rectangle> rect);
	virtual void clipRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height) = 0;
	
	virtual void drawLine(shared_ptr<NativeGraphics> graphics, int x1, int y1, int x2, int y2) = 0;
	virtual void fillRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height) = 0;
	virtual void drawRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height) = 0;
	virtual void drawRoundRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int arcWidth, int arcHeight) = 0;
	virtual void fillRoundRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int arcWidth, int arcHeight) = 0;
	virtual void fillArc(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int startAngle, int arcAngle) = 0;
	virtual void drawArc(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int startAngle, int arcAngle) = 0;
	virtual void drawString(shared_ptr<NativeGraphics> graphics, shared_ptr<String> str, int x, int y) = 0;
	virtual void drawImage(shared_ptr<NativeGraphics> graphics, shared_ptr<NativeImage> img, int x, int y) = 0;
	virtual void BitBlt(shared_ptr<NativeGraphics> dest, shared_ptr<NativeGraphics> src, int x, int y,int width,int height) = 0;

	void drawImageArea(shared_ptr<NativeGraphics> nativeGraphics, shared_ptr<NativeImage> img, int x, int y, int imageX, int imageY, int imageWidth, int imageHeight);
	virtual void drawImageRotated(shared_ptr<NativeGraphics> graphics, shared_ptr<NativeImage> img, int x, int y, int degrees);
	bool isRotationDrawingSupported();
	virtual void fillTriangle(shared_ptr<NativeGraphics> graphics, int x1, int y1, int x2, int y2, int x3, int y3);
	virtual void drawRGB(shared_ptr<NativeGraphics> graphics, shared_ptr<VectorArray<int> > rgbData, int offset, int x, int y, int w, int h, bool processAlpha) = 0;
	
	virtual shared_ptr<NativeGraphics> getNativeGraphics() = 0;
	virtual shared_ptr<NativeGraphics> getNativeGraphics(shared_ptr<NativeImage> image) = 0;

	virtual int charsWidth(shared_ptr<NativeFont> nativeFont, shared_ptr<String> ch, int offset, int length) = 0;
	virtual int stringWidth(shared_ptr<NativeFont> nativeFont, shared_ptr<String> str) = 0;
	virtual int charWidth(shared_ptr<NativeFont> nativeFont, char ch) = 0;
	virtual int getHeight(shared_ptr<NativeFont> nativeFont) = 0;

	virtual shared_ptr<NativeFont> getDefaultFont() = 0;
	virtual shared_ptr<NativeFont> createFont(int face, int style, int size) = 0;

	int getFace(shared_ptr<NativeFont> nativeFont);
	int getSize(shared_ptr<NativeFont> nativeFont);
	int getStyle(shared_ptr<NativeFont> nativeFont);


public:
	void keyPressed(int keyCode);
	void keyReleased(int keyCode);
	void pointerDragged(int x, int y);
	void pointerPressed(int x, int y);
	void pointerReleased(int x, int y);
	void pointerHover(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	void pointerHoverReleased(shared_ptr<VectorArray<int> >x, shared_ptr<VectorArray<int> > y);
	void pointerHoverReleased(int x, int y);
	void pointerHover(int x, int y);
	void pointerDragged(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	bool hasDragStarted(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	bool hasDragStarted(int x, int y);
	int getDragStartPercentage();
	void setDragStartPercentage(int dragStartPercentage);
	int getDragAutoActivationThreshold();
	void pointerPressed(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	void pointerReleased(shared_ptr<VectorArray<int> > x, shared_ptr<VectorArray<int> > y);
	void sizeChanged(int w, int h);
	void hideNotify();
	void showNotify();

public:	
	shared_ptr<Object> findCachedGradient(shared_ptr<Map<shared_ptr<VectorArray<int> >, shared_ptr<Object> > > cache, int startColor, int endColor, int x, int y, int width, int height, bool horizontal, int centerX, int centerY, int size);
	void storeCachedGradient(shared_ptr<Object> img, shared_ptr<Map<shared_ptr<VectorArray<int> >, shared_ptr<Object> > > cache, int startColor, int endColor, int x, int y, bool horizontal, int centerX, int centerY, int size);
	void fillRectRadialGradient(shared_ptr<NativeGraphics> graphics, int startColor, int endColor, int x, int y, int width, int height, float relativeX, float relativeY, float relativeSize);
	void fillRadialGradient(shared_ptr<NativeGraphics> graphics, int startColor, int endColor, int x, int y, int width, int height);

public:
	void fillRadialGradientImpl(shared_ptr<NativeGraphics> graphics, int startColor, int endColor, int x, int y, int width, int height);
	void updateGradientColor(shared_ptr<NativeGraphics> nativeGraphics, int sourceR, int sourceG, int sourceB, int destR, int destG, int destB, int distance, int offset);
	int calculateGraidentChannel(int sourceChannel, int destChannel, int distance, int offset);
	void fillLinearGradient(shared_ptr<NativeGraphics> graphics, int startColor, int endColor, int x, int y, int width, int height, bool horizontal);

private:
	void fillLinearGradientImpl(shared_ptr<NativeGraphics> graphics, int startColor, int endColor, int x, int y, int width, int height, bool horizontal);
	bool checkIntersection(shared_ptr<NativeGraphics> g, int y0, int x1, int x2, int y1, int y2, shared_ptr<VectorArray<int> > intersections, int intersectionsCount);
	int markIntersectionEdge(shared_ptr<NativeGraphics> g, int idx, shared_ptr<VectorArray<int> > yPoints, shared_ptr<VectorArray<int> > xPoints, int nPoints, shared_ptr<VectorArray<int> > intersections, int intersectionsCount);

public:
	void fillPolygon(shared_ptr<NativeGraphics> graphics, shared_ptr<VectorArray<int> > xPoints, shared_ptr<VectorArray<int> > yPoints, int nPoints);
	void drawPolygon(shared_ptr<NativeGraphics> graphics, shared_ptr<VectorArray<int> > xPoints, shared_ptr<VectorArray<int> > yPoints, int nPoints);

	virtual void setShowVirtualKeyboard(bool show);
	bool isVirtualKeyboardShowing();
	bool isVirtualKeyboardShowingSupported();
	int getKeyboardType();
	bool isNativeInputSupported();
	bool isMultiTouch();
	bool isClickTouchScreen();
	bool isNativeIndexed();

	shared_ptr<NativeImage> createNativeIndexed(shared_ptr<IndexedImage> image);
	shared_ptr<Object> createVideoComponent(shared_ptr<Object> player);
	int getVideoWidth(shared_ptr<Object> videoControl);
	int getVideoHeight(shared_ptr<Object> videoControl);
	virtual void setVideoVisible(shared_ptr<Object> vc, bool visible);
	virtual void startVideo(shared_ptr<Object> player, shared_ptr<Object> videoControl);
	virtual void stopVideo(shared_ptr<Object> player, shared_ptr<Object> videoControl);
	virtual void setVideoLoopCount(shared_ptr<Object> player, int count);
	long getMediaTime(shared_ptr<Object> player);
	long setMediaTime(shared_ptr<Object> player, long now);
	virtual void setVideoFullScreen(shared_ptr<Object> player, bool fullscreen);
	virtual void paintVideo(shared_ptr<Component> cmp, bool fullScreen, shared_ptr<NativeGraphics> nativeGraphics, shared_ptr<Object> video, shared_ptr<Object> player);

	bool isOpaque(shared_ptr<Image> lwuitImage, shared_ptr<NativeImage> nativeImage);
	bool isAffineSupported();
	void resetAffine(shared_ptr<NativeGraphics> nativeGraphics);
	void scale(shared_ptr<NativeGraphics> nativeGraphics, float x, float y);
	void rotate(shared_ptr<NativeGraphics> nativeGraphics, float angle);
	void shear(shared_ptr<NativeGraphics> nativeGraphics, float x, float y);
	bool isSVGSupported();
	shared_ptr<NativeImage> createSVGImage(shared_ptr<String> baseURL, VectorArray<unsigned char> data);
	shared_ptr<Object> getSVGDocument(shared_ptr<NativeImage> svgImage);
	bool animateImage(shared_ptr<NativeImage> nativeImage, long lastFrame);
	shared_ptr<VectorArray<String> > getFontPlatformNames();
	shared_ptr<NativeFont> loadTrueTypeFont(shared_ptr<InputStream> stream);
	bool isTrueTypeSupported();
	shared_ptr<NativeFont> loadNativeFont(shared_ptr<String> lookup);
	bool isLookupFontSupported();
	bool minimizeApplication();
	virtual void restoreMinimizedApplication();
	bool isMinimized();
	
protected:
	bool cacheRadialGradients();
	bool cacheLinearGradients();

public:
	bool isThirdSoftButton();
	int getDragPathLength();
	int getDragPathTime();
	float getDragSpeed(shared_ptr<VectorArray<float> >points, shared_ptr<VectorArray<long> > dragPathTime, int dragPathOffset, int dragPathLength);
	bool isBidiAlgorithm();
	void setBidiAlgorithm(bool activate);
	shared_ptr<String> convertBidiLogicalToVisual(shared_ptr<String> s);
	int getCharLocation(shared_ptr<String> source, int index);
	bool isRTLOrWhitespace(GUI_CHAR c);
	bool isRTL(GUI_CHAR c);
	int swapBidiChars(shared_ptr<String>chars, int ixStart, int len,int index);
	bool isRTLBreak(GUI_CHAR ch1);
	bool isLTR(GUI_CHAR c);
	int scanSecond(shared_ptr<String> chars, int ixStart, int ixEnd);
	int scanBackFirst(shared_ptr<String> chars, int ixStart, int ixEnd);

public:
	LWUITImplementation();
	virtual ~LWUITImplementation() {}
private:
	static const short RTL_RANGE_BEGIN = 0x590;
	static const short RTL_RANGE_END = 0x7BF;

	shared_ptr<Map<shared_ptr<VectorArray<int> >, shared_ptr<Object> > > linearGradientCache;
	shared_ptr<Map<shared_ptr<VectorArray<int> >, shared_ptr<Object> > > radialGradientCache;

	int dragActivationCounter;
	int dragActivationX;
	int dragActivationY;
	int dragStartPercentage;

	shared_ptr<Form> currentForm;
	static shared_ptr<Locker> displayLock;
	shared_ptr< VectorArray< shared_ptr<Animation> > > paintQueue;
	shared_ptr< VectorArray< shared_ptr<Animation> > > paintQueueTemp;
	int paintQueueFill;
	weak_ptr<Graphics> lwuitGraphics;

	bool bidi;

	shared_ptr<VectorArray<int> > xPointerEvent;
	shared_ptr<VectorArray<int> > yPointerEvent;	

	int pointerPressedX;
	int pointerPressedY;
};
__GUI_END_NAMESPACE

#endif
