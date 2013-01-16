#ifndef ALI_IMPLEMENTATION_H
#define ALI_IMPLEMENTATION_H


#include "inc/Vector.h"
#include "inc/Component.h"
#include "inc/Font.h"
#include "inc/LWUITImplementation.h"
#include "inc/Object.h"
#include "inc/InputStream.h"
#include "AMGDI.h"


__GUI_BEGIN_NAMESPACE
//class TextBox;
class Component;
class InputStream;
class Font;
class Command;
class NativeImage;
class NativeFont;
class NativeGraphics;

class AliImplementation : public LWUITImplementation
{

private:
	shared_ptr<NativeGraphics> screen_graphics;

private:
	static bool NOKIA;
	bool minimized;
	int alpha;

	static int portableKeyCodes[5];
	static int portableKeyCodeValues[5];
	
	shared_ptr<VectorArray<int> > rgbArr;

private:
	static shared_ptr<Command> CONFIRM_COMMAND;
	static shared_ptr<Command> CANCEL_COMMAND;

//	shared_ptr<TextBox> currentTextBox;
	shared_ptr<Component> currentTextComponent;

	bool flushGraphicsBug;	

private:
	static shared_ptr<Vector<int> > leftSK;
	static shared_ptr<Vector<int> > rightSK;

	static int backSK;
	static int clearSK;
	static int backspaceSK;
	static bool drawNegativeOffsetsInRGB;
	
public:
	AliImplementation();
	virtual ~AliImplementation();
public:
	void init(void *m);
	int getKeyboardType();

private:
	void setSoftKeyCodes();
	void setFireValue(int key);
	static void initKeyMap();
public:
	void vibrate(int duration);
	void flashBacklight(int duration);	
	int getDisplayWidth();
	int getDisplayHeight();
	void editString(shared_ptr<Component> cmp, int maxSize, int constraint, shared_ptr<String> text);
	void saveTextEditingState();
	void setFlashGraphicsBug(bool flushGraphicsBug);

public:
	virtual void updateRect(int x, int y ,int width, int height);
	virtual void BitBlt(shared_ptr<NativeGraphics> dest, shared_ptr<NativeGraphics> src, int x, int y,int width,int height);
	void flushGraphics(int x, int y, int width, int height);
	void flushGraphics();

	void getRGB(shared_ptr<NativeImage> nativeImage, shared_ptr<VectorArray<int> > arr, int offset, int x, int y, int width, int height);
	shared_ptr<NativeImage> createImage(shared_ptr<VectorArray<int> > rgb, int width, int height);
	shared_ptr<NativeImage> createImage(shared_ptr<String> path);
	shared_ptr<NativeImage> createImage(shared_ptr<InputStream> i);
	shared_ptr<NativeImage> createMutableImage(int width, int height,int fillColor);
	shared_ptr<NativeImage> createImage(VectorArray<unsigned char> bytes, int offset, int len);
	int getImageWidth(shared_ptr<NativeImage> i);
	int getImageHeight(shared_ptr<NativeImage> i);

	shared_ptr<NativeImage> scale(shared_ptr<NativeImage> nativeImage, int width, int height);
	void scaleArray(shared_ptr<NativeImage> currentImage, int srcWidth, int srcHeight, int height, int width, shared_ptr<VectorArray<int> > currentArray, shared_ptr<VectorArray<int> > destinationArray);
	void drawImageRotated(shared_ptr<NativeGraphics> graphics, shared_ptr<Object> img, int x, int y, int degrees);
	bool isRotationDrawingSupported();
	int getSoftkeyCount();
	shared_ptr<Vector<int> > getSoftkeyCode(int index);
	int getClearKeyCode();
	int getBackspaceKeyCode();
	int getBackKeyCode();
	int getGameAction(int keyCode);
	int getKeyCode(int gameAction);
	bool isTouchDevice();

	void setNativeFont(shared_ptr<NativeGraphics> graphics, shared_ptr<NativeFont> font);
	int getClipX(shared_ptr<NativeGraphics> graphics);
	int getClipY(shared_ptr<NativeGraphics> graphics);
	int getClipWidth(shared_ptr<NativeGraphics> graphics);
	int getClipHeight(shared_ptr<NativeGraphics> graphics);
	void setClip(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height);
	void clipRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height);

	void drawLine(shared_ptr<NativeGraphics> graphics, int x1, int y1, int x2, int y2);
	void fillRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height);
	void drawRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height);
	void drawRoundRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int arcWidth, int arcHeight);
	void fillRoundRect(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int arcWidth, int arcHeight);
	void fillArc(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int startAngle, int arcAngle);
	void drawArc(shared_ptr<NativeGraphics> graphics, int x, int y, int width, int height, int startAngle, int arcAngle);

	int getColor(shared_ptr<NativeGraphics> graphics);
	void setColor(shared_ptr<NativeGraphics> graphics, int RGB);
	//int getBgColor(shared_ptr<NativeGraphics> graphics) ;
	//void setBgColor(shared_ptr<NativeGraphics> graphics, int RGB) ;
	//int getFgColor(shared_ptr<NativeGraphics> graphics);
	//void setFgColor(shared_ptr<NativeGraphics> graphics, int RGB) ;

	void setAlpha(shared_ptr<NativeGraphics> graphics, int alpha);
	int getAlpha(shared_ptr<NativeGraphics> graphics);

	void drawString(shared_ptr<NativeGraphics> graphics, shared_ptr<String> str, int x, int y);
	void drawImage(shared_ptr<NativeGraphics> graphics, shared_ptr<NativeImage> img, int x, int y);
	
	void fillTriangle(shared_ptr<NativeGraphics> graphics, int x1, int y1, int x2, int y2, int x3, int y3);
	void drawRGB(shared_ptr<NativeGraphics> graphics, shared_ptr<VectorArray<int> > rgbData, int offset, int x, int y, int w, int h, bool processAlpha);

	shared_ptr<Object> getVideoControl(shared_ptr<Object> player);
	int numAlphaLevels();
	int numColors();
	void playDialogSound(const int type);
	void confirmControlView();
	void setCurrent(shared_ptr<Object> d);
	shared_ptr<NativeGraphics> getNativeGraphics();
	shared_ptr<NativeGraphics> getNativeGraphics(shared_ptr<NativeImage> image);
	
	void translate(shared_ptr<NativeGraphics> graphics, int x, int y);
	int getTranslateX(shared_ptr<NativeGraphics> graphics);
	int getTranslateY(shared_ptr<NativeGraphics> graphics);

	int charsWidth(shared_ptr<NativeFont> nativeFont, shared_ptr<String> ch, int offset, int length);
	int stringWidth(shared_ptr<NativeFont> nativeFont, shared_ptr<String> str);
	int charWidth(shared_ptr<NativeFont> nativeFont, char ch);
	int getHeight(shared_ptr<NativeFont> nativeFont);
	shared_ptr<NativeFont> createFont(int face, int style, int size);
	shared_ptr<NativeFont> getDefaultFont();
	int getFace(shared_ptr<NativeFont> nativeFont);
	int getSize(shared_ptr<NativeFont> nativeFont);
	int getStyle(shared_ptr<NativeFont> nativeFont);
	shared_ptr<Font> font(shared_ptr<NativeFont> f);
		
public:
	shared_ptr<Object> createVideoComponent(shared_ptr<Object> player);
	int getVideoWidth(shared_ptr<Object> videoControl);
	int getVideoHeight(shared_ptr<Object> videoControl);
	void setVideoVisible(shared_ptr<Object> vc, bool visible);
	void startVideo(shared_ptr<Object> player, shared_ptr<Object> videoControl);
	void stopVideo(shared_ptr<Object> player, shared_ptr<Object> videoControl);
	void setVideoLoopCount(shared_ptr<Object> player, int count);
	long getMediaTime(shared_ptr<Object> player);
	long setMediaTime(shared_ptr<Object> player, long now);
	void paintVideo(shared_ptr<Component> cmp, bool fullScreen, shared_ptr<Object> nativeGraphics, shared_ptr<Object> video, shared_ptr<Object> player);
};

__GUI_END_NAMESPACE
#endif
